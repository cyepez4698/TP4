#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Simbolo *simbolos;
static size_t cantidad, capacidad;
static int id_ambito, contador_ambitos;
static int *pila_ambitos;
static size_t cantidad_ambitos, capacidad_ambitos;

char *duplicar_cadena_simbolo(const char *texto) {
    size_t n = strlen(texto ? texto : "") + 1;
    char *p = malloc(n);
    if (!p) { fputs("tp4: memoria insuficiente\n", stderr); exit(EXIT_FAILURE); }
    memcpy(p, texto ? texto : "", n);
    return p;
}

const Simbolo *buscar_simbolo(const char *nombre) {
    size_t i = cantidad;
    while (i--) if (simbolos[i].activo && strcmp(simbolos[i].nombre, nombre) == 0)
        return &simbolos[i];
    return NULL;
}
Simbolo *buscar_simbolo_mutable(const char *nombre) { return (Simbolo *)buscar_simbolo(nombre); }
const Simbolo *buscar_simbolo_ambito_actual(const char *nombre) {
    size_t i = cantidad;
    while (i--) if (simbolos[i].activo && simbolos[i].ambito == id_ambito &&
                   strcmp(simbolos[i].nombre, nombre) == 0) return &simbolos[i];
    return NULL;
}
Simbolo *insertar_simbolo(const Simbolo *elemento) {
    size_t i;
    Simbolo *destino;
    if (cantidad == capacidad) {
        size_t nueva_capacidad = capacidad ? capacidad * 2 : 16;
        void *p = realloc(simbolos, nueva_capacidad * sizeof(*simbolos));
        if (!p) { fputs("tp4: memoria insuficiente\n", stderr); exit(EXIT_FAILURE); }
        simbolos = p; capacidad = nueva_capacidad;
    }
    destino = &simbolos[cantidad++];
    *destino = *elemento;
    destino->nombre = duplicar_cadena_simbolo(elemento->nombre);
    destino->tipo = duplicar_cadena_simbolo(elemento->tipo);
    destino->firma = duplicar_cadena_simbolo(elemento->firma ? elemento->firma : "");
    destino->parametros = NULL;
    if (elemento->cantidad_parametros) {
        destino->parametros = calloc(elemento->cantidad_parametros, sizeof(*destino->parametros));
        if (!destino->parametros) { fputs("tp4: memoria insuficiente\n", stderr); exit(EXIT_FAILURE); }
        for (i = 0; i < elemento->cantidad_parametros; i++) {
            destino->parametros[i].nombre = duplicar_cadena_simbolo(elemento->parametros[i].nombre);
            destino->parametros[i].tipo = duplicar_cadena_simbolo(elemento->parametros[i].tipo);
            destino->parametros[i].linea = elemento->parametros[i].linea;
            destino->parametros[i].columna = elemento->parametros[i].columna;
        }
    }
    destino->ambito = id_ambito;
    destino->activo = 1;
    return destino;
}
void entrar_ambito(void) {
    if (cantidad_ambitos == capacidad_ambitos) {
        size_t nueva_capacidad = capacidad_ambitos ? capacidad_ambitos * 2 : 8;
        void *p = realloc(pila_ambitos, nueva_capacidad * sizeof(*pila_ambitos));
        if (!p) { fputs("tp4: memoria insuficiente\n", stderr); exit(EXIT_FAILURE); }
        pila_ambitos = p; capacidad_ambitos = nueva_capacidad;
    }
    pila_ambitos[cantidad_ambitos++] = id_ambito;
    id_ambito = ++contador_ambitos;
}
void salir_ambito(void) {
    size_t i;
    if (!cantidad_ambitos) return;
    for (i = 0; i < cantidad; i++) if (simbolos[i].ambito == id_ambito) simbolos[i].activo = 0;
    id_ambito = pila_ambitos[--cantidad_ambitos];
}
void limpiar_tabla_simbolos(void) {
    size_t i, j;
    for (i = 0; i < cantidad; i++) {
        free(simbolos[i].nombre); free(simbolos[i].tipo); free(simbolos[i].firma);
        for (j = 0; j < simbolos[i].cantidad_parametros; j++) {
            free(simbolos[i].parametros[j].nombre); free(simbolos[i].parametros[j].tipo);
        }
        free(simbolos[i].parametros);
    }
    free(simbolos); free(pila_ambitos);
    simbolos = NULL; pila_ambitos = NULL;
    cantidad = capacidad = cantidad_ambitos = capacidad_ambitos = 0;
    id_ambito = contador_ambitos = 0;
}
