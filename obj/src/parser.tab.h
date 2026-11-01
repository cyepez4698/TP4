/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFICADOR = 258,
     CONSTANTE = 259,
     REAL = 260,
     LITERAL_CADENA = 261,
     CONSTANTE_CARACTER = 262,
     VOID = 263,
     CHAR = 264,
     SHORT = 265,
     INT = 266,
     LONG = 267,
     FLOAT = 268,
     DOUBLE = 269,
     SIGNED = 270,
     UNSIGNED = 271,
     IF = 272,
     ELSE = 273,
     SWITCH = 274,
     CASE = 275,
     DEFAULT = 276,
     WHILE = 277,
     DO = 278,
     FOR = 279,
     BREAK = 280,
     CONTINUE = 281,
     RETURN = 282,
     AUTO = 283,
     REGISTER = 284,
     STATIC = 285,
     EXTERN = 286,
     TYPEDEF = 287,
     CONST = 288,
     VOLATILE = 289,
     STRUCT = 290,
     UNION = 291,
     ENUM = 292,
     GOTO = 293,
     SIZEOF = 294,
     OP_O_LOGICO = 295,
     OP_Y_LOGICO = 296,
     OP_IGUAL = 297,
     OP_DISTINTO = 298,
     OP_MENOR_IGUAL = 299,
     OP_MAYOR_IGUAL = 300,
     OP_INCREMENTO = 301,
     OP_DECREMENTO = 302,
     ASIGNACION_SUMA = 303,
     ASIGNACION_RESTA = 304,
     ASIGNACION_MULTIPLICACION = 305,
     ASIGNACION_DIVISION = 306,
     SALTO_LINEA = 307,
     MENOR_QUE_ELSE = 308
   };
#endif
/* Tokens.  */
#define IDENTIFICADOR 258
#define CONSTANTE 259
#define REAL 260
#define LITERAL_CADENA 261
#define CONSTANTE_CARACTER 262
#define VOID 263
#define CHAR 264
#define SHORT 265
#define INT 266
#define LONG 267
#define FLOAT 268
#define DOUBLE 269
#define SIGNED 270
#define UNSIGNED 271
#define IF 272
#define ELSE 273
#define SWITCH 274
#define CASE 275
#define DEFAULT 276
#define WHILE 277
#define DO 278
#define FOR 279
#define BREAK 280
#define CONTINUE 281
#define RETURN 282
#define AUTO 283
#define REGISTER 284
#define STATIC 285
#define EXTERN 286
#define TYPEDEF 287
#define CONST 288
#define VOLATILE 289
#define STRUCT 290
#define UNION 291
#define ENUM 292
#define GOTO 293
#define SIZEOF 294
#define OP_O_LOGICO 295
#define OP_Y_LOGICO 296
#define OP_IGUAL 297
#define OP_DISTINTO 298
#define OP_MENOR_IGUAL 299
#define OP_MAYOR_IGUAL 300
#define OP_INCREMENTO 301
#define OP_DECREMENTO 302
#define ASIGNACION_SUMA 303
#define ASIGNACION_RESTA 304
#define ASIGNACION_MULTIPLICACION 305
#define ASIGNACION_DIVISION 306
#define SALTO_LINEA 307
#define MENOR_QUE_ELSE 308




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 66 "src/parser.y"
{
    char *texto;
    ExpresionSemantica *expresion_semantica;
    ParametrosSemanticos *parametros;
    ArgumentosSemanticos *argumentos;
}
/* Line 1529 of yacc.c.  */
#line 162 "obj/src/parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
