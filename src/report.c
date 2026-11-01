#include "report.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char *nombre, *tipo; int linea, columna; } Variable;
typedef struct { char *nombre, *parametros, *retorno; int linea, es_definicion; } Funcion;
typedef struct { char *texto; int linea, columna; } ErrorSemantico;
typedef struct { char *texto; int linea; } ErrorSintactico;
typedef struct { char *texto; int linea, columna; } ErrorLexico;

#define DECLARAR_VECTOR(T, n) static T *n; static size_t cantidad_##n, capacidad_##n

DECLARAR_VECTOR(Variable, variables);
DECLARAR_VECTOR(Funcion, funciones);
DECLARAR_VECTOR(ErrorSemantico, errores_semanticos);
DECLARAR_VECTOR(ErrorSintactico, errores_sintacticos);
DECLARAR_VECTOR(ErrorLexico, errores_lexicos);
static char *fuente_completa;

static void *crecer(void *vector, size_t *capacidad, size_t tam_elemento) {
    size_t nueva = *capacidad ? *capacidad * 2 : 8;
    void *ampliado = realloc(vector, nueva * tam_elemento);
    if (!ampliado) {
        fprintf(stderr, "tp4: memoria insuficiente\n");
        exit(EXIT_FAILURE);
    }
    *capacidad = nueva;
    return ampliado;
}

static char *duplicar(const char *texto) {
    size_t longitud;
    char *copia;
    if (!texto) texto = "";
    longitud = strlen(texto) + 1;
    copia = malloc(longitud);
    if (!copia) {
        fprintf(stderr, "tp4: memoria insuficiente\n");
        exit(EXIT_FAILURE);
    }
    memcpy(copia, texto, longitud);
    return copia;
}

void establecerFuente(const char *fuente) {
    free(fuente_completa);
    fuente_completa = duplicar(fuente);
}

void registrarVariable(const char *nombre, const char *tipo, int linea, int columna) {
    if (cantidad_variables == capacidad_variables)
        variables = crecer(variables, &capacidad_variables, sizeof(*variables));
    variables[cantidad_variables++] = (Variable){duplicar(nombre), duplicar(tipo), linea, columna};
}

void registrarFuncion(const char *nombre, const char *parametros, const char *retorno,
                      int linea, int es_definicion) {
    if (cantidad_funciones == capacidad_funciones)
        funciones = crecer(funciones, &capacidad_funciones, sizeof(*funciones));
    funciones[cantidad_funciones++] = (Funcion){duplicar(nombre), duplicar(parametros),
                                                duplicar(retorno), linea, es_definicion};
}

void registrarErrorSemantico(int linea, int columna, const char *formato, ...) {
    va_list argumentos, copia;
    int longitud;
    char *mensaje;
    va_start(argumentos, formato);
    va_copy(copia, argumentos);
    longitud = vsnprintf(NULL, 0, formato, argumentos);
    va_end(argumentos);
    if (longitud < 0) {
        va_end(copia);
        return;
    }
    mensaje = malloc((size_t)longitud + 1);
    if (!mensaje) {
        va_end(copia);
        fprintf(stderr, "tp4: memoria insuficiente\n");
        exit(EXIT_FAILURE);
    }
    vsnprintf(mensaje, (size_t)longitud + 1, formato, copia);
    va_end(copia);
    if (cantidad_errores_semanticos == capacidad_errores_semanticos)
        errores_semanticos = crecer(errores_semanticos, &capacidad_errores_semanticos,
                                   sizeof(*errores_semanticos));
    errores_semanticos[cantidad_errores_semanticos++] = (ErrorSemantico){mensaje, linea, columna};
}

static char *texto_linea(int linea) {
    const char *inicio, *fin;
    size_t longitud;
    char *resultado;
    int actual = 1;
    if (!fuente_completa || linea < 1) return duplicar("");
    inicio = fuente_completa;
    while (actual < linea && *inicio) {
        if (*inicio++ == '\n') actual++;
    }
    fin = inicio;
    while (*fin && *fin != '\n' && *fin != '\r') fin++;
    while (inicio < fin && (*inicio == ' ' || *inicio == '\t')) inicio++;
    while (fin > inicio && (fin[-1] == ' ' || fin[-1] == '\t')) fin--;
    longitud = (size_t)(fin - inicio);
    resultado = malloc(longitud + 3);
    if (!resultado) {
        fprintf(stderr, "tp4: memoria insuficiente\n");
        exit(EXIT_FAILURE);
    }
    resultado[0] = '"';
    memcpy(resultado + 1, inicio, longitud);
    resultado[longitud + 1] = '"';
    resultado[longitud + 2] = '\0';
    return resultado;
}

void registrarErrorSintactico(int linea, const char *texto) {
    char *fragmento;
    if (cantidad_errores_sintacticos &&
        errores_sintacticos[cantidad_errores_sintacticos - 1].linea == linea)
        return;
    fragmento = (texto && *texto) ? duplicar(texto) : texto_linea(linea);
    if (cantidad_errores_sintacticos == capacidad_errores_sintacticos)
        errores_sintacticos = crecer(errores_sintacticos, &capacidad_errores_sintacticos,
                                     sizeof(*errores_sintacticos));
    errores_sintacticos[cantidad_errores_sintacticos++] = (ErrorSintactico){fragmento, linea};
}

void registrarErrorLexico(const char *texto, int linea, int columna) {
    if (cantidad_errores_lexicos == capacidad_errores_lexicos)
        errores_lexicos = crecer(errores_lexicos, &capacidad_errores_lexicos,
                                 sizeof(*errores_lexicos));
    errores_lexicos[cantidad_errores_lexicos++] = (ErrorLexico){duplicar(texto), linea, columna};
}

void imprimirReporte(void) {
    size_t i;
    puts("* Listado de variables declaradas (tipo de dato y numero de linea):");
    if (!cantidad_variables) puts("-");
    for (i = 0; i < cantidad_variables; i++)
        printf("%s: %s, linea %d, columna %d\n", variables[i].nombre, variables[i].tipo,
               variables[i].linea, variables[i].columna);

    puts("\n* Listado de funciones declaradas y definidas:");
    if (!cantidad_funciones) puts("-");
    for (i = 0; i < cantidad_funciones; i++)
        printf("%s: %s, input: %s, retorna: %s, linea %d\n", funciones[i].nombre,
               funciones[i].es_definicion ? "definicion" : "declaracion",
               funciones[i].parametros, funciones[i].retorno, funciones[i].linea);

    puts("\n* Listado de errores semanticos:");
    if (!cantidad_errores_semanticos) puts("-");
    for (i = 0; i < cantidad_errores_semanticos; i++)
        printf("%d:%d: %s\n", errores_semanticos[i].linea,
               errores_semanticos[i].columna, errores_semanticos[i].texto);

    puts("\n* Listado de errores sintacticos:");
    if (!cantidad_errores_sintacticos) puts("-");
    for (i = 0; i < cantidad_errores_sintacticos; i++)
        printf("%s: linea %d\n", errores_sintacticos[i].texto, errores_sintacticos[i].linea);

    puts("\n* Listado de errores lexicos:");
    if (!cantidad_errores_lexicos) puts("-");
    for (i = 0; i < cantidad_errores_lexicos; i++)
        printf("%s: linea %d, columna %d\n", errores_lexicos[i].texto,
               errores_lexicos[i].linea, errores_lexicos[i].columna);
}

void liberarReporte(void) {
    size_t i;
    for (i = 0; i < cantidad_variables; i++) {
        free(variables[i].nombre);
        free(variables[i].tipo);
    }
    for (i = 0; i < cantidad_funciones; i++) {
        free(funciones[i].nombre);
        free(funciones[i].parametros);
        free(funciones[i].retorno);
    }
    for (i = 0; i < cantidad_errores_semanticos; i++) free(errores_semanticos[i].texto);
    for (i = 0; i < cantidad_errores_sintacticos; i++) free(errores_sintacticos[i].texto);
    for (i = 0; i < cantidad_errores_lexicos; i++) free(errores_lexicos[i].texto);
    free(variables);
    free(funciones);
    free(errores_semanticos);
    free(errores_sintacticos);
    free(errores_lexicos);
    free(fuente_completa);
    variables = NULL;
    funciones = NULL;
    errores_semanticos = NULL;
    errores_sintacticos = NULL;
    errores_lexicos = NULL;
    fuente_completa = NULL;
    cantidad_variables = capacidad_variables = 0;
    cantidad_funciones = capacidad_funciones = 0;
    cantidad_errores_semanticos = capacidad_errores_semanticos = 0;
    cantidad_errores_sintacticos = capacidad_errores_sintacticos = 0;
    cantidad_errores_lexicos = capacidad_errores_lexicos = 0;
}
