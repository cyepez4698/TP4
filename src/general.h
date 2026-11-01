#ifndef GENERAL_H
#define GENERAL_H

/* Ubicación compartida por el scanner y el parser (plantilla de clase). */
#define YYLTYPE YYLTYPE
typedef struct YYLTYPE {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
} YYLTYPE;

#define INICIO_CONTEO_LINEA 1
#define INICIO_CONTEO_COLUMNA 1

void inicializarUbicacion(void);
void reinicializarUbicacion(void);
void actualizarUbicacion(const char *texto, int longitud);

#endif
