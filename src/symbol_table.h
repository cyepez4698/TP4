#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H
#include <stddef.h>

typedef enum { SIMBOLO_VARIABLE, SIMBOLO_FUNCION } ClaseSimbolo;
typedef struct {
    char *nombre;
    char *tipo;
    int linea, columna;
} ParametroSimbolo;
typedef struct {
    char *nombre;
    char *tipo;
    char *firma;
    ClaseSimbolo clase;
    ParametroSimbolo *parametros;
    size_t cantidad_parametros;
    int linea, columna;
    int linea_definicion, columna_definicion;
    int definido;
    int ambito;
    int activo;
} Simbolo;

const Simbolo *buscar_simbolo(const char *nombre);
Simbolo *buscar_simbolo_mutable(const char *nombre);
const Simbolo *buscar_simbolo_ambito_actual(const char *nombre);
Simbolo *insertar_simbolo(const Simbolo *elemento);
void entrar_ambito(void);
void salir_ambito(void);
void limpiar_tabla_simbolos(void);
char *duplicar_cadena_simbolo(const char *texto);
#endif
