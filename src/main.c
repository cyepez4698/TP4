#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "general.h"
#include "report.h"
#include "semantic.h"

struct yy_buffer_state;
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_bytes(const char *datos, int longitud);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern int yyparse(void);

static char *leerArchivo(FILE *archivo, size_t *longitud) {

    size_t usados = 0, capacidad = 4096;
    char *contenido = malloc(capacidad);
    int caracter;
    if (!contenido) return NULL;

    while ((caracter = fgetc(archivo)) != EOF) {
        if (usados + 1 >= capacidad) {
            size_t nueva = capacidad * 2;
            char *ampliado;

            if (nueva <= capacidad) { 
                free(contenido); 
                return NULL; 
            }

            ampliado = realloc(contenido, nueva);

            if (!ampliado) { 
                free(contenido); 
                return NULL; 
            }

            contenido = ampliado;
            capacidad = nueva;
        }
        contenido[usados++] = (char)caracter;
    }
    if (ferror(archivo)) { 
        free(contenido); 
        return NULL; 
    }
    
    contenido[usados] = '\0';
    *longitud = usados;
    return contenido;
}

int main(int cantidad_argumentos, char **argumentos) {
    FILE *archivo;
    char *fuente;
    size_t longitud;
    YY_BUFFER_STATE buffer;
    int resultado;

    if (cantidad_argumentos != 2) {
        fprintf(stderr, "Uso: %s <archivo.i>\n", argumentos[0]);
        return EXIT_FAILURE;
    }
    archivo = fopen(argumentos[1], "rb");
    if (!archivo) {
        fprintf(stderr, "%s: %s\n", argumentos[1], strerror(errno));
        return EXIT_FAILURE;
    }
    fuente = leerArchivo(archivo, &longitud);
    fclose(archivo);
    if (!fuente) {
        fprintf(stderr, "No se pudo leer el archivo de entrada o no hay memoria suficiente.\n");
        return EXIT_FAILURE;
    }
    if (longitud > INT_MAX) {
        fprintf(stderr, "El archivo de entrada excede el tamaño máximo admitido.\n");
        free(fuente);
        return EXIT_FAILURE;
    }

    establecerFuente(fuente);
    inicializarUbicacion();
    buffer = yy_scan_bytes(fuente, (int)longitud);
    if (!buffer) {
        fprintf(stderr, "No se pudo crear el buffer del analizador léxico.\n");
        free(fuente);
        liberarReporte();
        return EXIT_FAILURE;
    }
    resultado = yyparse();
    yy_delete_buffer(buffer);
    imprimirReporte();
    liberarReporte();
    semantica_liberar();
    free(fuente);
    return resultado == 2 ? EXIT_FAILURE : EXIT_SUCCESS;
}
