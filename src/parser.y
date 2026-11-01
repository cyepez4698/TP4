%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include "report.h"
#include "semantic.h"

int yylex(void);
void yyerror(const char *mensaje);
void analizador_iniciar_recuperacion(void);
void analizador_finalizar_recuperacion(void);
int analizador_linea_token_anterior(void);

static char *duplicar_texto(const char *s) {
    size_t n = strlen(s) + 1;
    char *p = malloc(n);
    if (!p) { fputs("tp4: memoria insuficiente\n",stderr); exit(EXIT_FAILURE); }
    memcpy(p,s,n); return p;
}
static char *unir_tipo(const char *a, const char *b) {
    size_t x=strlen(a), y=strlen(b);
    char *p=malloc(x+y+(y>0?2:1));
    if (!p) { fputs("tp4: memoria insuficiente\n",stderr); exit(EXIT_FAILURE); }
    memcpy(p,a,x);
    if (y) {p[x++]=' ';memcpy(p+x,b,y);x+=y;}
    p[x]='\0';return p;
}
%}

%error-verbose
%locations
%union {
    char *texto;
    ExpresionSemantica *expresion_semantica;
    ParametrosSemanticos *parametros;
    ArgumentosSemanticos *argumentos;
}
%token <texto> IDENTIFICADOR CONSTANTE REAL LITERAL_CADENA CONSTANTE_CARACTER
%token VOID CHAR SHORT INT LONG FLOAT DOUBLE SIGNED UNSIGNED
%token IF ELSE SWITCH CASE DEFAULT WHILE DO FOR BREAK CONTINUE RETURN
%token AUTO REGISTER STATIC EXTERN TYPEDEF CONST VOLATILE STRUCT UNION ENUM GOTO SIZEOF
%token OP_O_LOGICO OP_Y_LOGICO OP_IGUAL OP_DISTINTO OP_MENOR_IGUAL OP_MAYOR_IGUAL OP_INCREMENTO OP_DECREMENTO
%token ASIGNACION_SUMA ASIGNACION_RESTA ASIGNACION_MULTIPLICACION ASIGNACION_DIVISION
%token SALTO_LINEA
%type <texto> especificadores_declaracion tipo_basico tipo_basico_optativo
%type <parametros> parametros_optativos lista_parametros declaracion_parametro
%type <expresion_semantica> expresion_optativa expresion expresion_asignacion expresion_logica_o
%type <expresion_semantica> expresion_logica_y expresion_igualdad expresion_relacional
%type <expresion_semantica> expresion_aditiva expresion_multiplicativa expresion_unaria
%type <expresion_semantica> expresion_postfija expresion_primaria
%type <argumentos> argumentos_optativos lista_argumentos

%destructor { free($$); } IDENTIFICADOR CONSTANTE REAL LITERAL_CADENA CONSTANTE_CARACTER
%destructor { free($$); } especificadores_declaracion tipo_basico tipo_basico_optativo
%destructor { semantica_liberar_parametros($$); } parametros_optativos lista_parametros declaracion_parametro
%destructor { semantica_liberar_expresion($$); } expresion_optativa expresion expresion_asignacion expresion_logica_o
%destructor { semantica_liberar_expresion($$); } expresion_logica_y expresion_igualdad expresion_relacional
%destructor { semantica_liberar_expresion($$); } expresion_aditiva expresion_multiplicativa expresion_unaria
%destructor { semantica_liberar_expresion($$); } expresion_postfija expresion_primaria
%destructor { semantica_liberar_argumentos($$); } argumentos_optativos lista_argumentos

%nonassoc MENOR_QUE_ELSE
%nonassoc ELSE
%start unidad_traduccion
%%
unidad_traduccion
    : /* vacia */
    | unidad_traduccion declaracion_externa
    ;

declaracion_externa
    : declaracion
    | definicion_funcion
    | error ';' { analizador_finalizar_recuperacion();yyerrok; }
    | error SALTO_LINEA { analizador_finalizar_recuperacion();yyerrok; }
    ;

declaracion
    : especificadores_declaracion lista_declaradores ';'
      { semantica_limpiar_tipo_declaracion(); free($1); }
    | especificadores_declaracion IDENTIFICADOR '(' parametros_optativos ')' ';'
      {
          semantica_registrar_funcion($2,$1,$4,0,@2.first_line,@2.first_column);
          free($1);free($2);semantica_liberar_parametros($4);
      }
    ;

definicion_funcion
    : especificadores_declaracion IDENTIFICADOR '(' parametros_optativos ')'
      {
          semantica_iniciar_funcion($2,$1,$4,@2.first_line,@2.first_column);
      }
      cuerpo_funcion
      {
          semantica_finalizar_funcion();
          free($1);free($2);semantica_liberar_parametros($4);
      }
    ;

/* El ambito de la funcion comienza antes del cuerpo para que sus parametros sean visibles. */
cuerpo_funcion : '{' lista_elementos_optativa '}' ;

especificadores_declaracion
    : tipo_basico { $$=$1; semantica_establecer_tipo_declaracion($$); }
    | SHORT tipo_basico_optativo {$$=unir_tipo("short",$2);free($2);semantica_establecer_tipo_declaracion($$);}
    | LONG tipo_basico_optativo {$$=unir_tipo("long",$2);free($2);semantica_establecer_tipo_declaracion($$);}
    | SIGNED tipo_basico_optativo {$$=unir_tipo("signed",$2);free($2);semantica_establecer_tipo_declaracion($$);}
    | UNSIGNED tipo_basico_optativo {$$=unir_tipo("unsigned",$2);free($2);semantica_establecer_tipo_declaracion($$);}
    | CONST especificadores_declaracion {$$=unir_tipo("const",$2);free($2);semantica_establecer_tipo_declaracion($$);}
    | VOLATILE especificadores_declaracion {$$=unir_tipo("volatile",$2);free($2);semantica_establecer_tipo_declaracion($$);}
    ;
tipo_basico_optativo
    : /* vacio */ {$$=duplicar_texto("");}
    | tipo_basico {$$=$1;}
    | LONG {$$=duplicar_texto("long");}
    | SHORT {$$=duplicar_texto("short");}
    ;
tipo_basico
    : VOID {$$=duplicar_texto("void");}
    | CHAR {$$=duplicar_texto("char");}
    | INT {$$=duplicar_texto("int");}
    | FLOAT {$$=duplicar_texto("float");}
    | DOUBLE {$$=duplicar_texto("double");}
    ;

lista_declaradores
    : declarador_inicializado
    | lista_declaradores ',' declarador_inicializado
    ;
declarador_inicializado
    : IDENTIFICADOR
      {semantica_declarar_variable($1,@1.first_line,@1.first_column,NULL);free($1);}
    | IDENTIFICADOR '=' expresion
      {semantica_declarar_variable($1,@1.first_line,@1.first_column,$3);free($1);}
    ;

parametros_optativos
    : /* vacio */ {$$=semantica_crear_parametros();}
    | lista_parametros {$$=$1;}
    ;
lista_parametros
    : declaracion_parametro {$$=$1;}
    | lista_parametros ',' declaracion_parametro
      {
          size_t i;
          for (i=0;i<$3->cantidad;i++) semantica_agregar_parametro($1,$3->elementos[i].tipo,
              $3->elementos[i].nombre,$3->elementos[i].linea,$3->elementos[i].columna);
          $$=$1;semantica_liberar_parametros($3);
      }
    ;
declaracion_parametro
    : especificadores_declaracion IDENTIFICADOR
      {$$=semantica_agregar_parametro(NULL,$1,$2,@2.first_line,@2.first_column);free($1);free($2);}
    | especificadores_declaracion
      {$$=semantica_agregar_parametro(NULL,$1,"",@1.first_line,@1.first_column);free($1);}
    ;

sentencia_compuesta
    : '{' {semantica_entrar_bloque();} lista_elementos_optativa '}' {semantica_salir_bloque();}
    ;
lista_elementos_optativa
    : /* vacia */
    | lista_elementos
    ;
lista_elementos
    : elemento
    | lista_elementos elemento
    ;
elemento
    : declaracion
    | sentencia
    | error ';' {analizador_finalizar_recuperacion();yyerrok;}
    | error SALTO_LINEA {analizador_finalizar_recuperacion();yyerrok;}
    ;

/* Las condiciones se verifican ANTES de analizar los cuerpos. */
encabezado_if
    : IF '(' expresion ')' {semantica_resolver($3);semantica_liberar_expresion($3);}
    ;
encabezado_switch
    : SWITCH '(' expresion ')' {semantica_resolver($3);semantica_liberar_expresion($3);}
    ;
encabezado_while
    : WHILE '(' expresion ')' {semantica_resolver($3);semantica_liberar_expresion($3);}
    ;
encabezado_for
    : FOR '(' expresion_optativa ';' expresion_optativa ';' expresion_optativa ')'
      {
          semantica_resolver($3);semantica_resolver($5);semantica_resolver($7);
          semantica_liberar_expresion($3);semantica_liberar_expresion($5);semantica_liberar_expresion($7);
      }
    ;
sentencia
    : expresion_optativa ';' {semantica_resolver($1);semantica_liberar_expresion($1);}
    | sentencia_compuesta
    | encabezado_if sentencia %prec MENOR_QUE_ELSE
    | encabezado_if sentencia ELSE sentencia
    | encabezado_switch sentencia
    | encabezado_while sentencia
    | DO sentencia WHILE '(' expresion ')' ';'
      {semantica_resolver($5);semantica_liberar_expresion($5);}
    | encabezado_for sentencia
    | CASE CONSTANTE ':' sentencia {free($2);}
    | DEFAULT ':' sentencia
    | BREAK ';'
    | CONTINUE ';'
    | RETURN expresion_optativa ';'
      {semantica_retorno($2,@1.first_line,@1.first_column);}
    ;
expresion_optativa : /* vacia */ {$$=NULL;} | expresion {$$=$1;} ;
expresion : expresion_asignacion {$$=$1;} ;
expresion_asignacion
    : expresion_logica_o {$$=$1;}
    | expresion_unaria '=' expresion_asignacion {$$=semantica_asignar("=",$1,$3,@2.first_line,@2.first_column);}
    | expresion_unaria ASIGNACION_SUMA expresion_asignacion {$$=semantica_asignar("+=",$1,$3,@2.first_line,@2.first_column);}
    | expresion_unaria ASIGNACION_RESTA expresion_asignacion {$$=semantica_asignar("-=",$1,$3,@2.first_line,@2.first_column);}
    | expresion_unaria ASIGNACION_MULTIPLICACION expresion_asignacion {$$=semantica_asignar("*=",$1,$3,@2.first_line,@2.first_column);}
    | expresion_unaria ASIGNACION_DIVISION expresion_asignacion {$$=semantica_asignar("/=",$1,$3,@2.first_line,@2.first_column);}
    ;
expresion_logica_o
    : expresion_logica_y {$$=$1;}
    | expresion_logica_o OP_O_LOGICO expresion_logica_y {$$=semantica_binaria("||",$1,$3,@2.first_line,@2.first_column);}
    ;
expresion_logica_y
    : expresion_igualdad {$$=$1;}
    | expresion_logica_y OP_Y_LOGICO expresion_igualdad {$$=semantica_binaria("&&",$1,$3,@2.first_line,@2.first_column);}
    ;
expresion_igualdad
    : expresion_relacional {$$=$1;}
    | expresion_igualdad OP_IGUAL expresion_relacional {$$=semantica_binaria("==",$1,$3,@2.first_line,@2.first_column);}
    | expresion_igualdad OP_DISTINTO expresion_relacional {$$=semantica_binaria("!=",$1,$3,@2.first_line,@2.first_column);}
    ;
expresion_relacional
    : expresion_aditiva {$$=$1;}
    | expresion_relacional '<' expresion_aditiva {$$=semantica_binaria("<",$1,$3,@2.first_line,@2.first_column);}
    | expresion_relacional '>' expresion_aditiva {$$=semantica_binaria(">",$1,$3,@2.first_line,@2.first_column);}
    | expresion_relacional OP_MENOR_IGUAL expresion_aditiva {$$=semantica_binaria("<=",$1,$3,@2.first_line,@2.first_column);}
    | expresion_relacional OP_MAYOR_IGUAL expresion_aditiva {$$=semantica_binaria(">=",$1,$3,@2.first_line,@2.first_column);}
    ;
expresion_aditiva
    : expresion_multiplicativa {$$=$1;}
    | expresion_aditiva '+' expresion_multiplicativa {$$=semantica_binaria("+",$1,$3,@2.first_line,@2.first_column);}
    | expresion_aditiva '-' expresion_multiplicativa {$$=semantica_binaria("-",$1,$3,@2.first_line,@2.first_column);}
    ;
expresion_multiplicativa
    : expresion_unaria {$$=$1;}
    | expresion_multiplicativa '*' expresion_unaria {$$=semantica_binaria("*",$1,$3,@2.first_line,@2.first_column);}
    | expresion_multiplicativa '/' expresion_unaria {$$=semantica_binaria("/",$1,$3,@2.first_line,@2.first_column);}
    ;
expresion_unaria
    : expresion_postfija {$$=$1;}
    | OP_INCREMENTO expresion_unaria {$$=semantica_unaria("++",$2,@1.first_line,@1.first_column);}
    | OP_DECREMENTO expresion_unaria {$$=semantica_unaria("--",$2,@1.first_line,@1.first_column);}
    | '+' expresion_unaria {$$=semantica_unaria("+",$2,@1.first_line,@1.first_column);}
    | '-' expresion_unaria {$$=semantica_unaria("-",$2,@1.first_line,@1.first_column);}
    | '!' expresion_unaria {$$=semantica_unaria("!",$2,@1.first_line,@1.first_column);}
    | SIZEOF expresion_unaria {$$=semantica_unaria("sizeof",$2,@1.first_line,@1.first_column);}
    ;
expresion_postfija
    : expresion_primaria {$$=$1;}
    | expresion_postfija '(' argumentos_optativos ')'
      {$$=semantica_invocar($1,$3,@2.first_line,@2.first_column);}
    | expresion_postfija OP_INCREMENTO {$$=semantica_postfija($1);}
    | expresion_postfija OP_DECREMENTO {$$=semantica_postfija($1);}
    ;
expresion_primaria
    : IDENTIFICADOR {$$=semantica_identificador($1,@1.first_line,@1.first_column);free($1);}
    | CONSTANTE {$$=semantica_literal($1,0,@1.first_line,@1.first_column);free($1);}
    | REAL {$$=semantica_literal($1,1,@1.first_line,@1.first_column);free($1);}
    | LITERAL_CADENA {$$=semantica_literal($1,2,@1.first_line,@1.first_column);free($1);}
    | CONSTANTE_CARACTER {$$=semantica_literal($1,3,@1.first_line,@1.first_column);free($1);}
    | '(' expresion ')' {$$=$2;}
    ;
argumentos_optativos
    : /* vacia */ {$$=semantica_crear_argumentos();}
    | lista_argumentos {$$=$1;}
    ;
lista_argumentos
    : expresion {$$=semantica_agregar_argumento(NULL,$1);}
    | lista_argumentos ',' expresion {$$=semantica_agregar_argumento($1,$3);}
    ;
%%
void yyerror(const char *mensaje) {
    int linea_error = analizador_linea_token_anterior();
    (void)mensaje;
    semantica_limpiar_tipo_declaracion();
    if (linea_error < 1 || linea_error > yylloc.first_line)
        linea_error = yylloc.first_line;
    registrarErrorSintactico(linea_error, "");
    analizador_iniciar_recuperacion();
}
