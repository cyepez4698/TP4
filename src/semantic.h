#ifndef SEMANTICA_H
#define SEMANTICA_H
#include <stddef.h>

typedef struct ExpresionSemantica {
    char *tipo, *nombre;
    int linea, columna;
    int pendiente_resolver, valor_izquierdo, solo_lectura, es_funcion, llamada_sin_retorno, erronea;
} ExpresionSemantica;

typedef struct {
    char *tipo, *nombre;
    int linea, columna;
} ParametroSemantico;
typedef struct ParametrosSemanticos {
    ParametroSemantico *elementos;
    size_t cantidad, capacidad;
    char *representacion;
    int sin_parametros_explicito;
} ParametrosSemanticos;

typedef struct {
    char *tipo;
    int linea, columna;
} ArgumentoSemantico;
typedef struct ArgumentosSemanticos {
    ArgumentoSemantico *elementos;
    size_t cantidad, capacidad;
} ArgumentosSemanticos;

ExpresionSemantica *semantica_identificador(const char *nombre, int linea, int columna);
ExpresionSemantica *semantica_literal(const char *lexema, int clase, int linea, int columna);
ExpresionSemantica *semantica_resolver(ExpresionSemantica *e);
ExpresionSemantica *semantica_unaria(const char *operador, ExpresionSemantica *e, int linea, int columna);
ExpresionSemantica *semantica_binaria(const char *operador, ExpresionSemantica *l, ExpresionSemantica *r, int linea, int columna);
ExpresionSemantica *semantica_asignar(const char *operador, ExpresionSemantica *l, ExpresionSemantica *r, int linea, int columna);
ExpresionSemantica *semantica_invocar(ExpresionSemantica *invocada, ArgumentosSemanticos *argumentos, int linea, int columna);
ExpresionSemantica *semantica_postfija(ExpresionSemantica *e);
void semantica_liberar_expresion(ExpresionSemantica *e);

ParametrosSemanticos *semantica_crear_parametros(void);
ParametrosSemanticos *semantica_parametros_vacios_explicitos(void);
ParametrosSemanticos *semantica_agregar_parametro(ParametrosSemanticos *p, const char *tipo, const char *nombre,
                                    int linea, int columna);
void semantica_liberar_parametros(ParametrosSemanticos *p);
ArgumentosSemanticos *semantica_crear_argumentos(void);
ArgumentosSemanticos *semantica_agregar_argumento(ArgumentosSemanticos *a, ExpresionSemantica *valor);
void semantica_liberar_argumentos(ArgumentosSemanticos *a);

void semantica_establecer_tipo_declaracion(const char *tipo);
void semantica_limpiar_tipo_declaracion(void);
void semantica_declarar_variable(const char *nombre, int linea, int columna, ExpresionSemantica *inicializador);
void semantica_registrar_funcion(const char *nombre, const char *tipo_retorno, ParametrosSemanticos *parametros,
                                int es_definicion, int linea, int columna);
void semantica_iniciar_funcion(const char *nombre, const char *tipo_retorno, ParametrosSemanticos *parametros,
                             int linea, int columna);
void semantica_finalizar_funcion(void);
void semantica_entrar_bloque(void);
void semantica_salir_bloque(void);
void semantica_retorno(ExpresionSemantica *e, int linea, int columna);
void semantica_liberar(void);
#endif
