#include "semantic.h"
#include "symbol_table.h"
#include "report.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *tipo_declaracion;
static char *tipo_retorno_actual;
static int linea_funcion_actual, columna_funcion_actual;

static void *redimensionar_o_fallar(void *p, size_t n) {
    void *r = realloc(p, n);
    if (!r) { fputs("tp4: memoria insuficiente\n", stderr); exit(EXIT_FAILURE); }
    return r;
}
static char *concatenar_tres(const char *a, const char *b, const char *c) {
    size_t x = strlen(a), y = strlen(b), z = strlen(c);
    char *p = malloc(x + y + z + 1);
    if (!p) { fputs("tp4: memoria insuficiente\n", stderr); exit(EXIT_FAILURE); }
    memcpy(p, a, x); memcpy(p+x, b, y); memcpy(p+x+y, c, z+1);
    return p;
}
static const char *tipo_valor(const char *t) {
    if (!t) return "error";
    while (!strncmp(t, "const ", 6)) t += 6;
    while (!strncmp(t, "volatile ", 9)) t += 9;
    return t;
}
static int es_numerico(const char *t) {
    t = tipo_valor(t);
    return strcmp(t, "char") == 0 || strcmp(t, "short") == 0 ||
           strcmp(t, "short int") == 0 || strcmp(t, "int") == 0 ||
           strcmp(t, "long") == 0 || strcmp(t, "long int") == 0 ||
           strcmp(t, "signed") == 0 || strcmp(t, "signed int") == 0 ||
           strcmp(t, "unsigned") == 0 || strcmp(t, "unsigned int") == 0 ||
           strcmp(t, "unsigned long") == 0 || strcmp(t, "unsigned long int") == 0 ||
           strcmp(t, "unsigned short") == 0 || strcmp(t, "unsigned short int") == 0 ||
           strcmp(t, "signed long") == 0 || strcmp(t, "signed short") == 0 ||
           strcmp(t, "float") == 0 || strcmp(t, "double") == 0 ||
           strcmp(t, "long double") == 0;
}
static int compatible(const char *esperado, const char *obtenido) {
    esperado = tipo_valor(esperado); obtenido = tipo_valor(obtenido);
    if (!strcmp(esperado, "error") || !strcmp(obtenido, "error")) return 1;
    if (es_numerico(esperado) && es_numerico(obtenido)) return 1;
    return strcmp(esperado, obtenido) == 0;
}
static const char *tipo_promovido(const char *a, const char *b) {
    a = tipo_valor(a); b = tipo_valor(b);
    if (!strcmp(a, "error") || !strcmp(b, "error")) return "error";
    if (!es_numerico(a) || !es_numerico(b)) return "error";
    if (!strcmp(a,"long double") || !strcmp(b,"long double")) return "long double";
    if (!strcmp(a,"double") || !strcmp(b,"double")) return "double";
    if (!strcmp(a,"float") || !strcmp(b,"float")) return "float";
    if (!strncmp(a,"unsigned long",13) || !strncmp(b,"unsigned long",13)) return "unsigned long";
    if (!strncmp(a,"long",4) || !strncmp(b,"long",4)) return "long";
    if (!strncmp(a,"unsigned",8) || !strncmp(b,"unsigned",8)) return "unsigned int";
    return "int";
}
static ExpresionSemantica *crear_expresion(const char *tipo, int linea, int columna) {
    ExpresionSemantica *e = calloc(1, sizeof(*e));
    if (!e) { fputs("tp4: memoria insuficiente\n", stderr); exit(EXIT_FAILURE); }
    e->tipo = duplicar_cadena_simbolo(tipo);
    e->linea = linea; e->columna = columna;
    return e;
}
static void establecer_tipo(ExpresionSemantica *e, const char *tipo) {
    free(e->tipo); e->tipo = duplicar_cadena_simbolo(tipo);
}
void semantica_liberar_expresion(ExpresionSemantica *e) {
    if (!e) return;
    free(e->tipo); free(e->nombre); free(e);
}
ExpresionSemantica *semantica_identificador(const char *nombre, int linea, int columna) {
    ExpresionSemantica *e = crear_expresion("error", linea, columna);
    e->nombre = duplicar_cadena_simbolo(nombre); e->pendiente_resolver = 1;
    return e;
}
ExpresionSemantica *semantica_literal(const char *texto, int clase, int linea, int columna) {
    const char *tipo = "int";
    size_t n = strlen(texto);
    if (clase == 1) tipo = n && (texto[n-1] == 'f' || texto[n-1] == 'F') ? "float" : "double";
    else if (clase == 2) tipo = "char *";
    else if (clase == 0 && n) {
        if (strchr(texto, 'l') || strchr(texto, 'L'))
            tipo = (strchr(texto, 'u') || strchr(texto, 'U')) ? "unsigned long" : "long";
        else if (strchr(texto, 'u') || strchr(texto, 'U')) tipo = "unsigned int";
    }
    return crear_expresion(tipo, linea, columna);
}
static char *tipo_puntero_funcion(const Simbolo *s) {
    char *p = concatenar_tres(s->tipo, " (*)", "");
    char *r = concatenar_tres(p, "(", s->cantidad_parametros ? "" : "void");
    size_t i;
    free(p);
    for (i = 0; i < s->cantidad_parametros; i++) {
        char *siguiente = concatenar_tres(r, i ? ", " : "", s->parametros[i].tipo);
        free(r); r = siguiente;
    }
    p = concatenar_tres(r, ")", ""); free(r); return p;
}
ExpresionSemantica *semantica_resolver(ExpresionSemantica *e) {
    const Simbolo *s;
    if (!e || !e->pendiente_resolver) return e;
    e->pendiente_resolver = 0;
    s = buscar_simbolo(e->nombre);
    if (!s) {
        registrarErrorSemantico(e->linea, e->columna, "'%s' sin declarar", e->nombre);
        e->erronea = 1;
        return e;
    }
    if (s->clase == SIMBOLO_FUNCION) {
        char *t = tipo_puntero_funcion(s);
        establecer_tipo(e, t); free(t);
        e->es_funcion = 1;
    } else {
        establecer_tipo(e, tipo_valor(s->tipo));
        e->valor_izquierdo = 1;
        e->solo_lectura = !strncmp(s->tipo, "const ", 6);
    }
    return e;
}
static void exigir_valor(ExpresionSemantica *e) {
    if (e && e->llamada_sin_retorno && !e->erronea) {
        registrarErrorSemantico(e->linea, e->columna,
              "No se ignora el valor de retorno void como deberia ser");
        e->llamada_sin_retorno = 0;
        e->erronea = 1;
    }
}
ExpresionSemantica *semantica_unaria(const char *operador, ExpresionSemantica *e, int linea, int columna) {
    (void)linea; (void)columna;
    if (!e) return crear_expresion("error", linea, columna);
    semantica_resolver(e);
    if (!strcmp(operador,"sizeof")) {
        /* sizeof no evalua el operando; en el subconjunto requerido devuelve unsigned int. */
        establecer_tipo(e, "unsigned int"); e->valor_izquierdo = e->solo_lectura = e->es_funcion = 0;
        e->llamada_sin_retorno = 0;
    } else {
        exigir_valor(e);
        if (!strcmp(operador,"!")) establecer_tipo(e, "int");
        e->valor_izquierdo = e->solo_lectura = e->es_funcion = 0;
    }
    return e;
}
ExpresionSemantica *semantica_postfija(ExpresionSemantica *e) {
    semantica_resolver(e); exigir_valor(e);
    if (e) e->valor_izquierdo = e->solo_lectura = e->es_funcion = 0;
    return e;
}
ExpresionSemantica *semantica_binaria(const char *operador, ExpresionSemantica *l, ExpresionSemantica *r, int linea, int columna) {
    ExpresionSemantica *resultado;
    const char *tipo;
    semantica_resolver(l); semantica_resolver(r);
    exigir_valor(l); exigir_valor(r);
    if (l->erronea || r->erronea) tipo = "error";
    else if (!strcmp(operador, "*") && (!es_numerico(l->tipo) || !es_numerico(r->tipo))) {
        registrarErrorSemantico(linea, columna,
          "Operandos invalidos del operador binario * (tienen '%s' y '%s')", l->tipo, r->tipo);
        tipo = "error";
    } else if (!strcmp(operador, "&&") || !strcmp(operador, "||") || !strcmp(operador, "==") ||
               !strcmp(operador, "!=") || !strcmp(operador,"<") || !strcmp(operador,">") ||
               !strcmp(operador,"<=") || !strcmp(operador,">=")) tipo = "int";
    else tipo = tipo_promovido(l->tipo, r->tipo);
    resultado = crear_expresion(tipo, l->linea, l->columna);
    semantica_liberar_expresion(l); semantica_liberar_expresion(r);
    return resultado;
}
ExpresionSemantica *semantica_asignar(const char *operador, ExpresionSemantica *l, ExpresionSemantica *r, int linea, int columna) {
    ExpresionSemantica *resultado;
    (void)operador;
    semantica_resolver(l); semantica_resolver(r);
    exigir_valor(l);
    if (r && r->llamada_sin_retorno && !r->erronea) {
        registrarErrorSemantico(linea, columna,
              "No se ignora el valor de retorno void como deberia ser");
        r->llamada_sin_retorno = 0;
        r->erronea = 1;
    } else {
        exigir_valor(r);
    }
    if (!l->erronea) {
        if (l->solo_lectura && l->nombre)
            registrarErrorSemantico(linea,columna,"Asignacion de la variable de solo lectura '%s'",l->nombre);
        else if (!l->valor_izquierdo)
            registrarErrorSemantico(linea,columna,
                  "Se requiere un valor-L modificable como operando izquierdo de la asignacion");
        else if (!r->erronea && !compatible(l->tipo,r->tipo))
            registrarErrorSemantico(linea,columna,
                  "Incompatibilidad de tipos al asignar el tipo '%s' usando el tipo '%s'",
                  l->tipo,r->tipo);
    }
    resultado = crear_expresion(l->tipo, l->linea, l->columna);
    semantica_liberar_expresion(l); semantica_liberar_expresion(r);
    return resultado;
}
ArgumentosSemanticos *semantica_crear_argumentos(void) {
    ArgumentosSemanticos *a = calloc(1,sizeof(*a));
    if (!a) { fputs("tp4: memoria insuficiente\n", stderr); exit(EXIT_FAILURE); }
    return a;
}
ArgumentosSemanticos *semantica_agregar_argumento(ArgumentosSemanticos *a, ExpresionSemantica *e) {
    if (!a) a = semantica_crear_argumentos();
    semantica_resolver(e); exigir_valor(e);
    if (a->cantidad == a->capacidad) {
        a->capacidad = a->capacidad ? a->capacidad * 2 : 4;
        a->elementos = redimensionar_o_fallar(a->elementos, a->capacidad * sizeof(*a->elementos));
    }
    a->elementos[a->cantidad++] = (ArgumentoSemantico){duplicar_cadena_simbolo(e->tipo), e->linea, e->columna};
    semantica_liberar_expresion(e);
    return a;
}
void semantica_liberar_argumentos(ArgumentosSemanticos *a) {
    size_t i;
    if (!a) return;
    for (i=0;i<a->cantidad;i++) free(a->elementos[i].tipo);
    free(a->elementos); free(a);
}
ExpresionSemantica *semantica_invocar(ExpresionSemantica *invocada, ArgumentosSemanticos *argumentos, int linea, int columna) {
    const Simbolo *funcion = NULL;
    ExpresionSemantica *resultado;
    size_t i;
    if (!argumentos) argumentos = semantica_crear_argumentos();
    if (invocada->nombre) funcion = buscar_simbolo(invocada->nombre);
    if (!funcion && invocada->pendiente_resolver && invocada->nombre) {
        registrarErrorSemantico(invocada->linea, invocada->columna,
                "Funcion '%s' sin declarar", invocada->nombre);
    } else if (funcion && funcion->clase != SIMBOLO_FUNCION) {
        registrarErrorSemantico(invocada->linea, invocada->columna,
                "El objeto invocado '%s' no es una funcion o un puntero a una funcion\nNota: declarado aqui: %d:%d",
                invocada->nombre, funcion->linea, funcion->columna);
    } else if (funcion) {
        if (argumentos->cantidad < funcion->cantidad_parametros) {
            registrarErrorSemantico(invocada->linea, invocada->columna,
                "Insuficientes argumentos para la funcion '%s'\nNota: declarado aqui: %d:%d",
                funcion->nombre,funcion->linea,funcion->columna);
        } else if (argumentos->cantidad > funcion->cantidad_parametros) {
            registrarErrorSemantico(invocada->linea, invocada->columna,
                "Demasiados argumentos para la funcion '%s'\nNota: declarado aqui: %d:%d",
                funcion->nombre,funcion->linea,funcion->columna);
        } else {
            for (i=0;i<argumentos->cantidad;i++) if (!compatible(funcion->parametros[i].tipo,argumentos->elementos[i].tipo)) {
                registrarErrorSemantico(argumentos->elementos[i].linea,argumentos->elementos[i].columna,
                    "Incompatibilidad de tipos para el argumento %zu de '%s'\nNota: se esperaba '%s' pero el argumento es de tipo '%s': %d:%d",
                    i+1,funcion->nombre,funcion->parametros[i].tipo,argumentos->elementos[i].tipo,
                    funcion->parametros[i].linea,funcion->parametros[i].columna);
            }
        }
    }
    resultado = crear_expresion(funcion && funcion->clase == SIMBOLO_FUNCION ? funcion->tipo : "error",
                    invocada->linea, invocada->columna);
    resultado->erronea = !funcion || funcion->clase != SIMBOLO_FUNCION;
    resultado->llamada_sin_retorno = funcion && funcion->clase == SIMBOLO_FUNCION && !strcmp(funcion->tipo,"void");
    semantica_liberar_expresion(invocada); semantica_liberar_argumentos(argumentos);
    (void)linea;(void)columna;
    return resultado;
}
ParametrosSemanticos *semantica_crear_parametros(void) {
    ParametrosSemanticos *p = calloc(1,sizeof(*p));
    if (!p) { fputs("tp4: memoria insuficiente\n", stderr); exit(EXIT_FAILURE); }
    p->representacion = duplicar_cadena_simbolo(""); return p;
}
ParametrosSemanticos *semantica_parametros_vacios_explicitos(void) {
    ParametrosSemanticos *p = semantica_crear_parametros();
    p->sin_parametros_explicito = 1;
    free(p->representacion); p->representacion = duplicar_cadena_simbolo("void"); return p;
}
ParametrosSemanticos *semantica_agregar_parametro(ParametrosSemanticos *p,const char *tipo,const char *nombre,int linea,int columna) {
    char *pieza, *completo;
    if (!p) p = semantica_crear_parametros();
    if (!p->cantidad && !strcmp(tipo,"void") && (!nombre || !*nombre)) {
        p->sin_parametros_explicito = 1;
        free(p->representacion);p->representacion = duplicar_cadena_simbolo("void");
        return p;
    }
    if (p->sin_parametros_explicito) {
        p->sin_parametros_explicito = 0;
        free(p->representacion);p->representacion = duplicar_cadena_simbolo("");
    }
    if (p->cantidad == p->capacidad) {
        p->capacidad = p->capacidad ? p->capacidad * 2 : 4;
        p->elementos = redimensionar_o_fallar(p->elementos,p->capacidad * sizeof(*p->elementos));
    }
    p->elementos[p->cantidad++] = (ParametroSemantico){duplicar_cadena_simbolo(tipo),duplicar_cadena_simbolo(nombre?nombre:""),linea,columna};
    pieza = nombre && *nombre ? concatenar_tres(tipo," ",nombre) : duplicar_cadena_simbolo(tipo);
    completo = concatenar_tres(p->representacion,p->cantidad > 1 ? ", " : "",pieza);
    free(p->representacion);free(pieza);p->representacion = completo;
    return p;
}
void semantica_liberar_parametros(ParametrosSemanticos *p) {
    size_t i;
    if (!p) return;
    for (i=0;i<p->cantidad;i++) {free(p->elementos[i].tipo);free(p->elementos[i].nombre);}
    free(p->elementos);free(p->representacion);free(p);
}
static char *construir_firma(const char *retorno, const ParametrosSemanticos *p) {
    size_t i; char *s = concatenar_tres(retorno,"(","");
    if (!p || !p->cantidad) { char *n = concatenar_tres(s,"void","");free(s);s=n; }
    else for (i=0;i<p->cantidad;i++) {
        char *n = concatenar_tres(s,i ? ", " : "",p->elementos[i].tipo);
        free(s);s=n;
    }
    { char *n = concatenar_tres(s,")","");free(s);return n; }
}
void semantica_establecer_tipo_declaracion(const char *tipo) {
    free(tipo_declaracion); tipo_declaracion = duplicar_cadena_simbolo(tipo);
}
void semantica_limpiar_tipo_declaracion(void) {free(tipo_declaracion);tipo_declaracion=NULL;}
void semantica_declarar_variable(const char *nombre,int linea,int columna,ExpresionSemantica *inicializador) {
    const Simbolo *previo = buscar_simbolo_ambito_actual(nombre);
    Simbolo nuevo_simbolo;
    const char *tipo = tipo_declaracion ? tipo_declaracion : "int";
    if (previo) {
        if (previo->clase != SIMBOLO_VARIABLE)
            registrarErrorSemantico(linea,columna,
               "'%s' redeclarado como un tipo diferente de simbolo\nNota: la declaracion previa de '%s' es de tipo '%s': %d:%d",
               nombre,nombre,previo->firma,previo->linea,previo->columna);
        else if (strcmp(previo->tipo,tipo))
            registrarErrorSemantico(linea,columna,
               "conflicto de tipos para '%s'; la ultima es de tipo '%s'\nNota: la declaracion previa de '%s' es de tipo '%s': %d:%d",
               nombre,tipo,nombre,previo->tipo,previo->linea,previo->columna);
        else
            registrarErrorSemantico(linea,columna,
               "Redeclaracion de '%s'\nNota: la declaracion previa de '%s' es de tipo '%s': %d:%d",
               nombre,nombre,previo->tipo,previo->linea,previo->columna);
    } else {
        memset(&nuevo_simbolo,0,sizeof(nuevo_simbolo));
        nuevo_simbolo.nombre=(char*)nombre;nuevo_simbolo.tipo=(char*)tipo;
        nuevo_simbolo.clase=SIMBOLO_VARIABLE;nuevo_simbolo.linea=linea;nuevo_simbolo.columna=columna;
        insertar_simbolo(&nuevo_simbolo);
        registrarVariable(nombre,tipo,linea,columna);
    }
    if (inicializador) {
        semantica_resolver(inicializador);exigir_valor(inicializador);
        if (!inicializador->erronea && !compatible(tipo,inicializador->tipo))
            registrarErrorSemantico(inicializador->linea,inicializador->columna,
                "Incompatibilidad de tipos al inicializar el tipo '%s' usando el tipo '%s'",
                tipo_valor(tipo),inicializador->tipo);
    }
    semantica_liberar_expresion(inicializador);
}
void semantica_registrar_funcion(const char *nombre,const char *retorno,ParametrosSemanticos *parametros,
                                int es_definicion,int linea,int columna) {
    const Simbolo *previo = buscar_simbolo_ambito_actual(nombre);
    char *firma = construir_firma(retorno,parametros);
    Simbolo elemento;
    size_t i;
    if (previo) {
        if (previo->clase != SIMBOLO_FUNCION) {
            registrarErrorSemantico(linea,columna,
                "'%s' redeclarado como un tipo diferente de simbolo\nNota: la declaracion previa de '%s' es de tipo '%s': %d:%d",
                nombre,nombre,previo->tipo,previo->linea,previo->columna);
        } else if (strcmp(previo->firma,firma)) {
            registrarErrorSemantico(linea,columna,
                "conflicto de tipos para '%s'; la ultima es de tipo '%s'\nNota: la declaracion previa de '%s' es de tipo '%s': %d:%d",
                nombre,firma,nombre,previo->firma,previo->linea,previo->columna);
        } else if (es_definicion && previo->definido) {
            registrarErrorSemantico(linea,columna,
                "Redefinicion de '%s'\nNota: la definicion previa de '%s' es de tipo '%s': %d:%d",
                nombre,nombre,firma,previo->linea_definicion,previo->columna_definicion);
        } else if (es_definicion) {
            Simbolo *editable = buscar_simbolo_mutable(nombre);
            editable->definido = 1; editable->linea_definicion=linea;editable->columna_definicion=columna;
            registrarFuncion(nombre,parametros->representacion,retorno,linea,1);
        }
    } else {
        memset(&elemento,0,sizeof(elemento));
        elemento.nombre=(char*)nombre;elemento.tipo=(char*)retorno;elemento.firma=firma;
        elemento.clase=SIMBOLO_FUNCION;elemento.linea=linea;elemento.columna=columna;
        elemento.definido=es_definicion;elemento.linea_definicion=linea;elemento.columna_definicion=columna;
        if (parametros && parametros->cantidad) {
            elemento.parametros=calloc(parametros->cantidad,sizeof(*elemento.parametros));
            if (!elemento.parametros) { fputs("tp4: memoria insuficiente\n", stderr); exit(EXIT_FAILURE); }
            elemento.cantidad_parametros=parametros->cantidad;
            for (i=0;i<parametros->cantidad;i++) {
                elemento.parametros[i].nombre=parametros->elementos[i].nombre;
                elemento.parametros[i].tipo=parametros->elementos[i].tipo;
                elemento.parametros[i].linea=parametros->elementos[i].linea;
                elemento.parametros[i].columna=parametros->elementos[i].columna;
            }
        }
        insertar_simbolo(&elemento);
        free(elemento.parametros);
        registrarFuncion(nombre,parametros ? parametros->representacion : "",retorno,linea,es_definicion);
    }
    free(firma);
}
void semantica_iniciar_funcion(const char *nombre,const char *retorno,ParametrosSemanticos *parametros,int linea,int columna) {
    size_t i;
    semantica_registrar_funcion(nombre,retorno,parametros,1,linea,columna);
    free(tipo_retorno_actual);tipo_retorno_actual=duplicar_cadena_simbolo(retorno);
    linea_funcion_actual=linea;columna_funcion_actual=columna;
    entrar_ambito();
    for (i=0;parametros && i<parametros->cantidad;i++) {
        Simbolo s;
        if (!parametros->elementos[i].nombre[0]) continue;
        memset(&s,0,sizeof(s));
        s.nombre=parametros->elementos[i].nombre; s.tipo=parametros->elementos[i].tipo;
        s.clase=SIMBOLO_VARIABLE;s.linea=parametros->elementos[i].linea;s.columna=parametros->elementos[i].columna;
        insertar_simbolo(&s);
    }
}
void semantica_finalizar_funcion(void) {
    salir_ambito();free(tipo_retorno_actual);tipo_retorno_actual=NULL;
}
void semantica_entrar_bloque(void) {entrar_ambito();}
void semantica_salir_bloque(void) {salir_ambito();}
void semantica_retorno(ExpresionSemantica *e,int linea,int columna) {
    const char *esperado = tipo_retorno_actual ? tipo_valor(tipo_retorno_actual) : "void";
    if (!e) {
        if (strcmp(esperado,"void"))
            registrarErrorSemantico(linea,columna,
              "'return' sin valor en una funcion que no retorna void\nNota: declarado aqui: %d:%d",
              linea_funcion_actual,columna_funcion_actual);
        return;
    }
    semantica_resolver(e);exigir_valor(e);
    if (!e->erronea && (!compatible(esperado,e->tipo) || !strcmp(esperado,"void")))
        registrarErrorSemantico(e->linea,e->columna,
            "Incompatibilidad de tipos al retornar el tipo '%s' pero se esperaba '%s'",
            e->tipo,esperado);
    semantica_liberar_expresion(e);
}
void semantica_liberar(void) {
    semantica_limpiar_tipo_declaracion();free(tipo_retorno_actual);tipo_retorno_actual=NULL;
    limpiar_tabla_simbolos();
}
