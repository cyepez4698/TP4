#ifndef REPORT_H
#define REPORT_H
void establecerFuente(const char *fuente);
void registrarVariable(const char *nombre, const char *tipo, int linea, int columna);
void registrarFuncion(const char *nombre, const char *parametros, const char *retorno,
                      int linea, int es_definicion);
void registrarErrorSemantico(int linea, int columna, const char *formato, ...);
void registrarErrorSintactico(int linea, const char *texto);
void registrarErrorLexico(const char *texto, int linea, int columna);
void imprimirReporte(void);
void liberarReporte(void);
#endif
