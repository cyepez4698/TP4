%option noyywrap nounput noinput
%x ERROR_LEXICO RECUPERACION_SINTACTICA

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include "semantic.h"
#include "parser.tab.h"
#include "report.h"

static char *error_lexico;
static size_t longitud_error, capacidad_error;
static int linea_error, columna_error;
static int ultima_linea_token = 1;
static int linea_token_anterior = 1;
static int hay_token;

static int devolver_token(int token) {
    linea_token_anterior = hay_token ? ultima_linea_token : yylloc.first_line;
    ultima_linea_token = yylloc.first_line;
    hay_token = 1;
    return token;
}

#define DEVOLVER(token) return devolver_token(token)

static void agregar_error(const char *texto, size_t longitud) {
    size_t requerido = longitud_error + longitud + 1;
    if (requerido > capacidad_error) {
        size_t nueva = capacidad_error ? capacidad_error * 2 : 16;
        char *ampliado;
        while (nueva < requerido) nueva *= 2;
        ampliado = realloc(error_lexico, nueva);
        if (!ampliado) { fprintf(stderr, "scanner: sin memoria suficiente\n"); exit(EXIT_FAILURE); }
        error_lexico = ampliado;
        capacidad_error = nueva;
    }
    memcpy(error_lexico + longitud_error, texto, longitud);
    longitud_error += longitud;
    error_lexico[longitud_error] = '\0';
}

static void iniciar_error(const char *texto, size_t longitud) {
    longitud_error = 0;
    linea_error = yylloc.first_line;
    columna_error = yylloc.first_column;
    agregar_error(texto, longitud);
}

static void finalizar_error(void) {
    if (longitud_error)
        registrarErrorLexico(error_lexico, linea_error, columna_error);
    free(error_lexico);
    error_lexico = NULL;
    longitud_error = capacidad_error = 0;
}

static char *copiar(const char *texto, size_t longitud) {
    char *copia = malloc(longitud + 1);
    if (!copia) { fprintf(stderr, "scanner: sin memoria suficiente\n"); exit(EXIT_FAILURE); }
    memcpy(copia, texto, longitud);
    copia[longitud] = '\0';
    return copia;
}

#define YY_USER_ACTION do { \
    reinicializarUbicacion(); \
    actualizarUbicacion(yytext, (int)yyleng); \
} while (0);
%}

DIGITO                  [0-9]
OCTAL                   [0-7]
DIGITO_HEXADECIMAL      [0-9a-fA-F]
LETRA                   [_a-zA-Z]
IDENTIFICADOR_LEXICO    {LETRA}({LETRA}|{DIGITO})*
SUFIJO_ENTERO           ([uU][lL]?|[lL][uU]?)
ENTERO_DECIMAL          [1-9]{DIGITO}*{SUFIJO_ENTERO}?
ENTERO_OCTAL            0{OCTAL}*{SUFIJO_ENTERO}?
ENTERO_HEXADECIMAL      0[xX]{DIGITO_HEXADECIMAL}+{SUFIJO_ENTERO}?
EXPONENTE               [eE][+-]?{DIGITO}+
NUMERO_REAL             (({DIGITO}+\.{DIGITO}*|\.{DIGITO}+){EXPONENTE}?|{DIGITO}+{EXPONENTE})[fFlL]?
SECUENCIA_ESCAPE        \\([^\n]|x{DIGITO_HEXADECIMAL}+|{OCTAL}{1,3})
CARACTER                '([^'\\\n]|{SECUENCIA_ESCAPE})+'
CADENA                  \"([^\"\\\n]|{SECUENCIA_ESCAPE})*\"
OCTAL_INVALIDO          0{OCTAL}*[89]{DIGITO}*
NUMERO_INVALIDO         {DIGITO}+{LETRA}({LETRA}|{DIGITO})*

%%

[ \t\r\n]+              ;
"auto"                    { DEVOLVER(AUTO); }
"register"                { DEVOLVER(REGISTER); }
"static"                  { DEVOLVER(STATIC); }
"extern"                  { DEVOLVER(EXTERN); }
"typedef"                 { DEVOLVER(TYPEDEF); }
"const"                   { DEVOLVER(CONST); }
"volatile"                { DEVOLVER(VOLATILE); }
"struct"                  { DEVOLVER(STRUCT); }
"union"                   { DEVOLVER(UNION); }
"enum"                    { DEVOLVER(ENUM); }
"goto"                    { DEVOLVER(GOTO); }
"sizeof"                  { DEVOLVER(SIZEOF); }
"void"                    { DEVOLVER(VOID); }
"char"                    { DEVOLVER(CHAR); }
"short"                   { DEVOLVER(SHORT); }
"int"                     { DEVOLVER(INT); }
"long"                    { DEVOLVER(LONG); }
"float"                   { DEVOLVER(FLOAT); }
"double"                  { DEVOLVER(DOUBLE); }
"signed"                  { DEVOLVER(SIGNED); }
"unsigned"                { DEVOLVER(UNSIGNED); }
"if"                      { DEVOLVER(IF); }
"else"                    { DEVOLVER(ELSE); }
"switch"                  { DEVOLVER(SWITCH); }
"case"                    { DEVOLVER(CASE); }
"default"                 { DEVOLVER(DEFAULT); }
"while"                   { DEVOLVER(WHILE); }
"do"                      { DEVOLVER(DO); }
"for"                     { DEVOLVER(FOR); }
"break"                   { DEVOLVER(BREAK); }
"continue"                { DEVOLVER(CONTINUE); }
"return"                  { DEVOLVER(RETURN); }

"++"                      { DEVOLVER(OP_INCREMENTO); }
"--"                      { DEVOLVER(OP_DECREMENTO); }
"||"                      { DEVOLVER(OP_O_LOGICO); }
"&&"                      { DEVOLVER(OP_Y_LOGICO); }
"=="                      { DEVOLVER(OP_IGUAL); }
"!="                      { DEVOLVER(OP_DISTINTO); }
"<="                      { DEVOLVER(OP_MENOR_IGUAL); }
">="                      { DEVOLVER(OP_MAYOR_IGUAL); }
"+="                      { DEVOLVER(ASIGNACION_SUMA); }
"-="                      { DEVOLVER(ASIGNACION_RESTA); }
"*="                      { DEVOLVER(ASIGNACION_MULTIPLICACION); }
"/="                      { DEVOLVER(ASIGNACION_DIVISION); }

{NUMERO_REAL}             { yylval.texto = copiar(yytext, yyleng); DEVOLVER(REAL); }
{ENTERO_HEXADECIMAL}|{ENTERO_OCTAL}|{ENTERO_DECIMAL} { yylval.texto = copiar(yytext, yyleng); DEVOLVER(CONSTANTE); }
{OCTAL_INVALIDO}          { iniciar_error(yytext, yyleng); BEGIN(ERROR_LEXICO); }
{NUMERO_INVALIDO}         { iniciar_error(yytext, yyleng); BEGIN(ERROR_LEXICO); }
{CADENA}                  { yylval.texto = copiar(yytext, yyleng); DEVOLVER(LITERAL_CADENA); }
{CARACTER}                { yylval.texto = copiar(yytext, yyleng); DEVOLVER(CONSTANTE_CARACTER); }
{IDENTIFICADOR_LEXICO}    { yylval.texto = copiar(yytext, yyleng); DEVOLVER(IDENTIFICADOR); }
[(){};,=:<>+*/!-]         { DEVOLVER(yytext[0]); }

<INITIAL>.                { iniciar_error(yytext, yyleng); BEGIN(ERROR_LEXICO); }
<ERROR_LEXICO>[^ \t\r\n;]+ { agregar_error(yytext, yyleng); }
<ERROR_LEXICO>[ \t\r]+   { finalizar_error(); BEGIN(INITIAL); }
<ERROR_LEXICO>;           { finalizar_error(); BEGIN(INITIAL); DEVOLVER(';'); }
<ERROR_LEXICO>\r?\n      { finalizar_error(); BEGIN(INITIAL); DEVOLVER(SALTO_LINEA); }
<ERROR_LEXICO><<EOF>>     { finalizar_error(); BEGIN(INITIAL); DEVOLVER(0); }

<RECUPERACION_SINTACTICA>[^;\n]+ ;
<RECUPERACION_SINTACTICA>; { BEGIN(INITIAL); DEVOLVER(';'); }
<RECUPERACION_SINTACTICA>\r?\n { BEGIN(INITIAL); DEVOLVER(SALTO_LINEA); }
<RECUPERACION_SINTACTICA><<EOF>> { BEGIN(INITIAL); DEVOLVER(0); }

%%

void analizador_iniciar_recuperacion(void) {
    BEGIN(RECUPERACION_SINTACTICA);
}

void analizador_finalizar_recuperacion(void) {
    BEGIN(INITIAL);
}

int analizador_linea_token_anterior(void) {
    return hay_token ? linea_token_anterior : yylloc.first_line;
}
