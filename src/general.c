#include "general.h"

extern YYLTYPE yylloc;

void inicializarUbicacion(void) {
    yylloc.first_line = yylloc.last_line = INICIO_CONTEO_LINEA;
    yylloc.first_column = yylloc.last_column = INICIO_CONTEO_COLUMNA;
}

void reinicializarUbicacion(void) {
    yylloc.first_line = yylloc.last_line;
    yylloc.first_column = yylloc.last_column;
}

void actualizarUbicacion(const char *texto, int longitud) {
    int i;
    for (i = 0; i < longitud; i++) {
        if (texto[i] == '\n') {
            yylloc.last_line++;
            yylloc.last_column = INICIO_CONTEO_COLUMNA;
        } else {
            yylloc.last_column++;
        }
    }
}
