/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



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




/* Copy the first part of user declarations.  */
#line 1 "src/parser.y"

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

typedef struct {
    char *nombre;
    int linea, columna;
    ExpresionSemantica *inicializador;
} DeclaracionPendiente;
static DeclaracionPendiente *declaraciones_pendientes;
static size_t cantidad_declaraciones_pendientes, capacidad_declaraciones_pendientes;

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
static void descartar_declaraciones_pendientes(void) {
    size_t i;
    for (i=0;i<cantidad_declaraciones_pendientes;i++) {
        free(declaraciones_pendientes[i].nombre);
        semantica_liberar_expresion(declaraciones_pendientes[i].inicializador);
    }
    free(declaraciones_pendientes);declaraciones_pendientes=NULL;cantidad_declaraciones_pendientes=capacidad_declaraciones_pendientes=0;
}
static void agregar_declaracion_pendiente(char *nombre, int linea,int columna,ExpresionSemantica *valor) {
    if (cantidad_declaraciones_pendientes==capacidad_declaraciones_pendientes) {
        size_t n=capacidad_declaraciones_pendientes?capacidad_declaraciones_pendientes*2:8;
        void *p=realloc(declaraciones_pendientes,n*sizeof(*declaraciones_pendientes));
        if (!p) {fputs("tp4: memoria insuficiente\n",stderr);exit(EXIT_FAILURE);}
        declaraciones_pendientes=p;capacidad_declaraciones_pendientes=n;
    }
    /* Registrar cada declarador en orden permite usarlo en inicializadores posteriores
       de la misma declaracion: int a=1, b=a*2; */
    semantica_declarar_variable(nombre,linea,columna,valor);
    declaraciones_pendientes[cantidad_declaraciones_pendientes++]=(DeclaracionPendiente){nombre,linea,columna,NULL};
}
static void confirmar_declaraciones_pendientes(const char *tipo) {
    (void)tipo;
    semantica_limpiar_tipo_declaracion();
    descartar_declaraciones_pendientes();
}


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 66 "src/parser.y"
{
    char *texto;
    ExpresionSemantica *expresion_semantica;
    ParametrosSemanticos *parametros;
    ArgumentosSemanticos *argumentos;
}
/* Line 193 of yacc.c.  */
#line 272 "obj/src/parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 297 "obj/src/parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   320

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  113
/* YYNRULES -- Number of states.  */
#define YYNSTATES  201

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    68,     2,     2,     2,     2,     2,     2,
      55,    56,    66,    64,    59,    65,     2,    67,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,    54,
      62,    60,    63,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,     2,    58,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    14,    17,    21,
      28,    29,    37,    41,    43,    46,    49,    52,    55,    58,
      61,    62,    64,    66,    68,    70,    72,    74,    76,    78,
      80,    84,    86,    90,    91,    93,    95,    99,   102,   104,
     105,   110,   111,   113,   115,   118,   120,   122,   125,   128,
     133,   138,   143,   152,   155,   157,   160,   165,   168,   171,
     179,   182,   187,   191,   194,   197,   201,   202,   204,   206,
     208,   212,   216,   220,   224,   228,   230,   234,   236,   240,
     242,   246,   250,   252,   256,   260,   264,   268,   270,   274,
     278,   280,   284,   288,   290,   293,   296,   299,   302,   305,
     308,   310,   315,   318,   321,   323,   325,   327,   329,   331,
     335,   336,   338,   340
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      70,     0,    -1,    -1,    70,    71,    -1,    72,    -1,    73,
      -1,     1,    54,    -1,     1,    52,    -1,    76,    79,    54,
      -1,    76,     3,    55,    81,    56,    54,    -1,    -1,    76,
       3,    55,    81,    56,    74,    75,    -1,    57,    86,    58,
      -1,    78,    -1,    10,    77,    -1,    12,    77,    -1,    15,
      77,    -1,    16,    77,    -1,    33,    76,    -1,    34,    76,
      -1,    -1,    78,    -1,    12,    -1,    10,    -1,     8,    -1,
       9,    -1,    11,    -1,    13,    -1,    14,    -1,    80,    -1,
      79,    59,    80,    -1,     3,    -1,     3,    60,    95,    -1,
      -1,    82,    -1,    83,    -1,    82,    59,    83,    -1,    76,
       3,    -1,    76,    -1,    -1,    57,    85,    86,    58,    -1,
      -1,    87,    -1,    88,    -1,    87,    88,    -1,    72,    -1,
      93,    -1,     1,    54,    -1,     1,    52,    -1,    17,    55,
      95,    56,    -1,    19,    55,    95,    56,    -1,    22,    55,
      95,    56,    -1,    24,    55,    94,    54,    94,    54,    94,
      56,    -1,    94,    54,    -1,    84,    -1,    89,    93,    -1,
      89,    93,    18,    93,    -1,    90,    93,    -1,    91,    93,
      -1,    23,    93,    22,    55,    95,    56,    54,    -1,    92,
      93,    -1,    20,     4,    61,    93,    -1,    21,    61,    93,
      -1,    25,    54,    -1,    26,    54,    -1,    27,    94,    54,
      -1,    -1,    95,    -1,    96,    -1,    97,    -1,   103,    60,
      96,    -1,   103,    48,    96,    -1,   103,    49,    96,    -1,
     103,    50,    96,    -1,   103,    51,    96,    -1,    98,    -1,
      97,    40,    98,    -1,    99,    -1,    98,    41,    99,    -1,
     100,    -1,    99,    42,   100,    -1,    99,    43,   100,    -1,
     101,    -1,   100,    62,   101,    -1,   100,    63,   101,    -1,
     100,    44,   101,    -1,   100,    45,   101,    -1,   102,    -1,
     101,    64,   102,    -1,   101,    65,   102,    -1,   103,    -1,
     102,    66,   103,    -1,   102,    67,   103,    -1,   104,    -1,
      46,   103,    -1,    47,   103,    -1,    64,   103,    -1,    65,
     103,    -1,    68,   103,    -1,    39,   103,    -1,   105,    -1,
     104,    55,   106,    56,    -1,   104,    46,    -1,   104,    47,
      -1,     3,    -1,     4,    -1,     5,    -1,     6,    -1,     7,
      -1,    55,    95,    56,    -1,    -1,   107,    -1,    95,    -1,
     107,    59,    95,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   100,   100,   102,   106,   107,   108,   109,   113,   115,
     124,   123,   135,   138,   139,   140,   141,   142,   143,   144,
     147,   148,   149,   150,   153,   154,   155,   156,   157,   161,
     162,   165,   166,   171,   172,   175,   176,   185,   187,   192,
     192,   194,   196,   199,   200,   203,   204,   205,   206,   211,
     214,   217,   220,   227,   228,   229,   230,   231,   232,   233,
     235,   236,   237,   238,   239,   240,   243,   243,   244,   246,
     247,   248,   249,   250,   251,   254,   255,   258,   259,   262,
     263,   264,   267,   268,   269,   270,   271,   274,   275,   276,
     279,   280,   281,   284,   285,   286,   287,   288,   289,   290,
     293,   294,   296,   297,   300,   301,   302,   303,   304,   305,
     308,   309,   312,   313
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFICADOR", "CONSTANTE", "REAL",
  "LITERAL_CADENA", "CONSTANTE_CARACTER", "VOID", "CHAR", "SHORT", "INT",
  "LONG", "FLOAT", "DOUBLE", "SIGNED", "UNSIGNED", "IF", "ELSE", "SWITCH",
  "CASE", "DEFAULT", "WHILE", "DO", "FOR", "BREAK", "CONTINUE", "RETURN",
  "AUTO", "REGISTER", "STATIC", "EXTERN", "TYPEDEF", "CONST", "VOLATILE",
  "STRUCT", "UNION", "ENUM", "GOTO", "SIZEOF", "OP_O_LOGICO",
  "OP_Y_LOGICO", "OP_IGUAL", "OP_DISTINTO", "OP_MENOR_IGUAL",
  "OP_MAYOR_IGUAL", "OP_INCREMENTO", "OP_DECREMENTO", "ASIGNACION_SUMA",
  "ASIGNACION_RESTA", "ASIGNACION_MULTIPLICACION", "ASIGNACION_DIVISION",
  "SALTO_LINEA", "MENOR_QUE_ELSE", "';'", "'('", "')'", "'{'", "'}'",
  "','", "'='", "':'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'!'",
  "$accept", "unidad_traduccion", "declaracion_externa", "declaracion",
  "definicion_funcion", "@1", "cuerpo_funcion",
  "especificadores_declaracion", "tipo_basico_optativo", "tipo_basico",
  "lista_declaradores", "declarador_inicializado", "parametros_optativos",
  "lista_parametros", "declaracion_parametro", "sentencia_compuesta", "@2",
  "lista_elementos_optativa", "lista_elementos", "elemento",
  "encabezado_if", "encabezado_switch", "encabezado_while",
  "encabezado_for", "sentencia", "expresion_optativa", "expresion",
  "expresion_asignacion", "expresion_logica_o", "expresion_logica_y",
  "expresion_igualdad", "expresion_relacional", "expresion_aditiva",
  "expresion_multiplicativa", "expresion_unaria", "expresion_postfija",
  "expresion_primaria", "argumentos_optativos", "lista_argumentos", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,    59,    40,    41,   123,   125,    44,
      61,    58,    60,    62,    43,    45,    42,    47,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    70,    71,    71,    71,    71,    72,    72,
      74,    73,    75,    76,    76,    76,    76,    76,    76,    76,
      77,    77,    77,    77,    78,    78,    78,    78,    78,    79,
      79,    80,    80,    81,    81,    82,    82,    83,    83,    85,
      84,    86,    86,    87,    87,    88,    88,    88,    88,    89,
      90,    91,    92,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    94,    94,    95,    96,
      96,    96,    96,    96,    96,    97,    97,    98,    98,    99,
      99,    99,   100,   100,   100,   100,   100,   101,   101,   101,
     102,   102,   102,   103,   103,   103,   103,   103,   103,   103,
     104,   104,   104,   104,   105,   105,   105,   105,   105,   105,
     106,   106,   107,   107
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     2,     2,     3,     6,
       0,     7,     3,     1,     2,     2,     2,     2,     2,     2,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     0,     1,     1,     3,     2,     1,     0,
       4,     0,     1,     1,     2,     1,     1,     2,     2,     4,
       4,     4,     8,     2,     1,     2,     4,     2,     2,     7,
       2,     4,     3,     2,     2,     3,     0,     1,     1,     1,
       3,     3,     3,     3,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     2,     2,     2,     2,     2,     2,
       1,     4,     2,     2,     1,     1,     1,     1,     1,     3,
       0,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,    24,    25,    20,    26,    20,    27,
      28,    20,    20,     0,     0,     3,     4,     5,     0,    13,
       7,     6,    23,    22,    14,    21,    15,    16,    17,    18,
      19,    31,     0,    29,    33,     0,     8,     0,    38,     0,
      34,    35,   104,   105,   106,   107,   108,     0,     0,     0,
       0,     0,     0,     0,    32,    68,    69,    75,    77,    79,
      82,    87,    90,    93,   100,    31,    30,    37,    10,     0,
      99,    94,    95,     0,    96,    97,    98,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   102,   103,   110,     9,     0,    36,
     109,    76,    90,    78,    80,    81,    85,    86,    83,    84,
      88,    89,    91,    92,    71,    72,    73,    74,    70,   112,
       0,   111,     0,    11,   101,     0,     0,     0,     0,     0,
       0,     0,    66,     0,     0,     0,    66,    39,    45,     0,
      54,     0,     0,    43,    66,    66,    66,    66,    46,     0,
      67,   113,    48,    47,     0,     0,     0,    66,     0,     0,
      66,    63,    64,     0,     0,    31,    12,    44,    55,    57,
      58,    60,    53,     0,     0,    66,    62,     0,     0,     0,
      65,     0,    33,    66,    49,    50,    61,    51,     0,    66,
      40,     0,    56,     0,     0,     0,     0,    66,    59,     0,
      52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    15,   138,    17,    98,   123,    38,    24,    19,
      32,    33,    39,    40,    41,   140,   164,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,   120,   121
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -103
static const yytype_int16 yypact[] =
{
    -103,   259,  -103,    -8,  -103,  -103,   125,  -103,   125,  -103,
    -103,   125,   125,   286,   286,  -103,  -103,  -103,     5,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,   -46,     0,  -103,   286,   198,  -103,     8,    42,   -41,
      -7,  -103,  -103,  -103,  -103,  -103,  -103,   198,   198,   198,
     198,   198,   198,   198,  -103,  -103,    43,    53,    18,     3,
       4,    34,   -44,   -45,  -103,    69,  -103,  -103,    76,   286,
    -103,  -103,  -103,    87,  -103,  -103,  -103,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,  -103,  -103,   198,  -103,    88,  -103,
    -103,    53,  -103,    18,     3,     3,     4,     4,     4,     4,
      34,    34,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
      91,    89,    16,  -103,  -103,   198,    73,    96,    97,   140,
      94,   102,    85,   103,   105,   106,   198,  -103,  -103,   158,
    -103,   121,   161,  -103,    85,    85,    85,    85,  -103,   135,
    -103,  -103,  -103,  -103,   198,   198,   129,    85,   198,   169,
     198,  -103,  -103,   138,    16,    12,  -103,  -103,   175,  -103,
    -103,  -103,  -103,   141,   142,    85,  -103,   143,   151,   155,
    -103,   152,   286,    85,  -103,  -103,  -103,  -103,   198,   198,
    -103,   156,  -103,   157,   160,    76,   163,   198,  -103,   164,
    -103
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -103,  -103,  -103,   195,  -103,  -103,  -103,    -1,    74,    45,
    -103,   174,    39,  -103,   153,  -103,  -103,    59,  -103,    82,
    -103,  -103,  -103,  -103,   -29,  -102,   -32,   -14,  -103,   150,
     154,    40,    15,    28,   199,  -103,  -103,  -103,  -103
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -67
static const yytype_int16 yytable[] =
{
      18,    94,    95,    54,    89,    90,    91,    92,    31,    34,
      96,    65,    29,    30,    35,    68,    93,   126,    73,    42,
      43,    44,    45,    46,     4,     5,     6,     7,     8,     9,
      10,    11,    12,   127,   163,   128,   129,   130,   131,   132,
     133,   134,   135,   136,    20,    67,    21,    81,    82,    13,
      14,    25,    69,    25,    36,    47,    25,    25,   179,    37,
      79,    80,    48,    49,   119,    83,    84,   182,    85,    86,
     -66,    50,    35,   137,   -41,   114,   115,   116,   117,   118,
      51,    52,    26,    77,    53,    27,    28,   194,    42,    43,
      44,    45,    46,   151,    78,   199,   106,   107,   108,   109,
      87,    88,   127,   159,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   110,   111,   168,   169,   170,   171,   104,
     105,   139,   173,   174,    47,   152,   177,   153,   176,    35,
      97,    48,    49,     4,     5,    22,     7,    23,     9,    10,
      50,   139,   137,   100,   156,   122,   186,   124,   125,    51,
      52,   154,   155,    53,   192,   157,   193,   158,   160,   161,
     162,   165,   126,   139,    42,    43,    44,    45,    46,     4,
       5,     6,     7,     8,     9,    10,    11,    12,   127,   166,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   172,
     175,   178,   180,   183,    13,    14,    16,   184,   185,   187,
      47,    42,    43,    44,    45,    46,   188,    48,    49,   189,
     190,    66,   195,   196,   197,   -66,    50,   198,   137,   -42,
     200,   191,    99,   181,   167,    51,    52,   101,     0,    53,
       0,     0,   103,     0,     0,     0,     0,    47,     0,     0,
       0,     0,     0,     0,    48,    49,    70,    71,    72,     0,
      74,    75,    76,    50,     0,     0,     0,     0,     0,     2,
       3,     0,    51,    52,     0,     0,    53,     4,     5,     6,
       7,     8,     9,    10,    11,    12,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   112,   113,     0,     0,
       0,     0,    13,    14,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
      14
};

static const yytype_int16 yycheck[] =
{
       1,    46,    47,    35,    48,    49,    50,    51,     3,    55,
      55,     3,    13,    14,    60,    56,    60,     1,    50,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,   136,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    52,     3,    54,    44,    45,    33,
      34,     6,    59,     8,    54,    39,    11,    12,   160,    59,
      42,    43,    46,    47,    96,    62,    63,    55,    64,    65,
      54,    55,    60,    57,    58,    89,    90,    91,    92,    93,
      64,    65,     8,    40,    68,    11,    12,   189,     3,     4,
       5,     6,     7,   125,    41,   197,    81,    82,    83,    84,
      66,    67,    17,   132,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    85,    86,   144,   145,   146,   147,    79,
      80,   122,   154,   155,    39,    52,   158,    54,   157,    60,
      54,    46,    47,     8,     9,    10,    11,    12,    13,    14,
      55,   142,    57,    56,     4,    57,   175,    56,    59,    64,
      65,    55,    55,    68,   183,    61,   188,    55,    55,    54,
      54,     3,     1,   164,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    58,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    54,
      61,    22,    54,    18,    33,    34,     1,    56,    56,    56,
      39,     3,     4,     5,     6,     7,    55,    46,    47,    54,
      58,    37,    56,    56,    54,    54,    55,    54,    57,    58,
      56,   182,    69,   164,   142,    64,    65,    77,    -1,    68,
      -1,    -1,    78,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    47,    47,    48,    49,    -1,
      51,    52,    53,    55,    -1,    -1,    -1,    -1,    -1,     0,
       1,    -1,    64,    65,    -1,    -1,    68,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    -1,    -1,
      -1,    -1,    33,    34,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    70,     0,     1,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    33,    34,    71,    72,    73,    76,    78,
      52,    54,    10,    12,    77,    78,    77,    77,    77,    76,
      76,     3,    79,    80,    55,    60,    54,    59,    76,    81,
      82,    83,     3,     4,     5,     6,     7,    39,    46,    47,
      55,    64,    65,    68,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,     3,    80,     3,    56,    59,
     103,   103,   103,    95,   103,   103,   103,    40,    41,    42,
      43,    44,    45,    62,    63,    64,    65,    66,    67,    48,
      49,    50,    51,    60,    46,    47,    55,    54,    74,    83,
      56,    98,   103,    99,   100,   100,   101,   101,   101,   101,
     102,   102,   103,   103,    96,    96,    96,    96,    96,    95,
     106,   107,    57,    75,    56,    59,     1,    17,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    57,    72,    76,
      84,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    95,    52,    54,    55,    55,     4,    61,    55,    93,
      55,    54,    54,    94,    85,     3,    58,    88,    93,    93,
      93,    93,    54,    95,    95,    61,    93,    95,    22,    94,
      54,    86,    55,    18,    56,    56,    93,    56,    55,    54,
      58,    81,    93,    95,    94,    56,    56,    54,    54,    94,
      56
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 3: /* "IDENTIFICADOR" */
#line 87 "src/parser.y"
	{ free((yyvaluep->texto)); };
#line 1421 "obj/src/parser.tab.c"
	break;
      case 4: /* "CONSTANTE" */
#line 87 "src/parser.y"
	{ free((yyvaluep->texto)); };
#line 1426 "obj/src/parser.tab.c"
	break;
      case 5: /* "REAL" */
#line 87 "src/parser.y"
	{ free((yyvaluep->texto)); };
#line 1431 "obj/src/parser.tab.c"
	break;
      case 6: /* "LITERAL_CADENA" */
#line 87 "src/parser.y"
	{ free((yyvaluep->texto)); };
#line 1436 "obj/src/parser.tab.c"
	break;
      case 7: /* "CONSTANTE_CARACTER" */
#line 87 "src/parser.y"
	{ free((yyvaluep->texto)); };
#line 1441 "obj/src/parser.tab.c"
	break;
      case 76: /* "especificadores_declaracion" */
#line 88 "src/parser.y"
	{ free((yyvaluep->texto)); };
#line 1446 "obj/src/parser.tab.c"
	break;
      case 77: /* "tipo_basico_optativo" */
#line 88 "src/parser.y"
	{ free((yyvaluep->texto)); };
#line 1451 "obj/src/parser.tab.c"
	break;
      case 78: /* "tipo_basico" */
#line 88 "src/parser.y"
	{ free((yyvaluep->texto)); };
#line 1456 "obj/src/parser.tab.c"
	break;
      case 81: /* "parametros_optativos" */
#line 89 "src/parser.y"
	{ semantica_liberar_parametros((yyvaluep->parametros)); };
#line 1461 "obj/src/parser.tab.c"
	break;
      case 82: /* "lista_parametros" */
#line 89 "src/parser.y"
	{ semantica_liberar_parametros((yyvaluep->parametros)); };
#line 1466 "obj/src/parser.tab.c"
	break;
      case 83: /* "declaracion_parametro" */
#line 89 "src/parser.y"
	{ semantica_liberar_parametros((yyvaluep->parametros)); };
#line 1471 "obj/src/parser.tab.c"
	break;
      case 94: /* "expresion_optativa" */
#line 90 "src/parser.y"
	{ semantica_liberar_expresion((yyvaluep->expresion_semantica)); };
#line 1476 "obj/src/parser.tab.c"
	break;
      case 95: /* "expresion" */
#line 90 "src/parser.y"
	{ semantica_liberar_expresion((yyvaluep->expresion_semantica)); };
#line 1481 "obj/src/parser.tab.c"
	break;
      case 96: /* "expresion_asignacion" */
#line 90 "src/parser.y"
	{ semantica_liberar_expresion((yyvaluep->expresion_semantica)); };
#line 1486 "obj/src/parser.tab.c"
	break;
      case 97: /* "expresion_logica_o" */
#line 90 "src/parser.y"
	{ semantica_liberar_expresion((yyvaluep->expresion_semantica)); };
#line 1491 "obj/src/parser.tab.c"
	break;
      case 98: /* "expresion_logica_y" */
#line 91 "src/parser.y"
	{ semantica_liberar_expresion((yyvaluep->expresion_semantica)); };
#line 1496 "obj/src/parser.tab.c"
	break;
      case 99: /* "expresion_igualdad" */
#line 91 "src/parser.y"
	{ semantica_liberar_expresion((yyvaluep->expresion_semantica)); };
#line 1501 "obj/src/parser.tab.c"
	break;
      case 100: /* "expresion_relacional" */
#line 91 "src/parser.y"
	{ semantica_liberar_expresion((yyvaluep->expresion_semantica)); };
#line 1506 "obj/src/parser.tab.c"
	break;
      case 101: /* "expresion_aditiva" */
#line 92 "src/parser.y"
	{ semantica_liberar_expresion((yyvaluep->expresion_semantica)); };
#line 1511 "obj/src/parser.tab.c"
	break;
      case 102: /* "expresion_multiplicativa" */
#line 92 "src/parser.y"
	{ semantica_liberar_expresion((yyvaluep->expresion_semantica)); };
#line 1516 "obj/src/parser.tab.c"
	break;
      case 103: /* "expresion_unaria" */
#line 92 "src/parser.y"
	{ semantica_liberar_expresion((yyvaluep->expresion_semantica)); };
#line 1521 "obj/src/parser.tab.c"
	break;
      case 104: /* "expresion_postfija" */
#line 93 "src/parser.y"
	{ semantica_liberar_expresion((yyvaluep->expresion_semantica)); };
#line 1526 "obj/src/parser.tab.c"
	break;
      case 105: /* "expresion_primaria" */
#line 93 "src/parser.y"
	{ semantica_liberar_expresion((yyvaluep->expresion_semantica)); };
#line 1531 "obj/src/parser.tab.c"
	break;
      case 106: /* "argumentos_optativos" */
#line 94 "src/parser.y"
	{ semantica_liberar_argumentos((yyvaluep->argumentos)); };
#line 1536 "obj/src/parser.tab.c"
	break;
      case 107: /* "lista_argumentos" */
#line 94 "src/parser.y"
	{ semantica_liberar_argumentos((yyvaluep->argumentos)); };
#line 1541 "obj/src/parser.tab.c"
	break;

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 6:
#line 108 "src/parser.y"
    { descartar_declaraciones_pendientes();analizador_finalizar_recuperacion();yyerrok; ;}
    break;

  case 7:
#line 109 "src/parser.y"
    { descartar_declaraciones_pendientes();analizador_finalizar_recuperacion();yyerrok; ;}
    break;

  case 8:
#line 114 "src/parser.y"
    { confirmar_declaraciones_pendientes((yyvsp[(1) - (3)].texto)); free((yyvsp[(1) - (3)].texto)); ;}
    break;

  case 9:
#line 116 "src/parser.y"
    {
          semantica_registrar_funcion((yyvsp[(2) - (6)].texto),(yyvsp[(1) - (6)].texto),(yyvsp[(4) - (6)].parametros),0,(yylsp[(2) - (6)]).first_line,(yylsp[(2) - (6)]).first_column);
          free((yyvsp[(1) - (6)].texto));free((yyvsp[(2) - (6)].texto));semantica_liberar_parametros((yyvsp[(4) - (6)].parametros));
      ;}
    break;

  case 10:
#line 124 "src/parser.y"
    {
          semantica_iniciar_funcion((yyvsp[(2) - (5)].texto),(yyvsp[(1) - (5)].texto),(yyvsp[(4) - (5)].parametros),(yylsp[(2) - (5)]).first_line,(yylsp[(2) - (5)]).first_column);
      ;}
    break;

  case 11:
#line 128 "src/parser.y"
    {
          semantica_finalizar_funcion();
          free((yyvsp[(1) - (7)].texto));free((yyvsp[(2) - (7)].texto));semantica_liberar_parametros((yyvsp[(4) - (7)].parametros));
      ;}
    break;

  case 13:
#line 138 "src/parser.y"
    { (yyval.texto)=(yyvsp[(1) - (1)].texto); semantica_establecer_tipo_declaracion((yyval.texto)); ;}
    break;

  case 14:
#line 139 "src/parser.y"
    {(yyval.texto)=unir_tipo("short",(yyvsp[(2) - (2)].texto));free((yyvsp[(2) - (2)].texto));semantica_establecer_tipo_declaracion((yyval.texto));;}
    break;

  case 15:
#line 140 "src/parser.y"
    {(yyval.texto)=unir_tipo("long",(yyvsp[(2) - (2)].texto));free((yyvsp[(2) - (2)].texto));semantica_establecer_tipo_declaracion((yyval.texto));;}
    break;

  case 16:
#line 141 "src/parser.y"
    {(yyval.texto)=unir_tipo("signed",(yyvsp[(2) - (2)].texto));free((yyvsp[(2) - (2)].texto));semantica_establecer_tipo_declaracion((yyval.texto));;}
    break;

  case 17:
#line 142 "src/parser.y"
    {(yyval.texto)=unir_tipo("unsigned",(yyvsp[(2) - (2)].texto));free((yyvsp[(2) - (2)].texto));semantica_establecer_tipo_declaracion((yyval.texto));;}
    break;

  case 18:
#line 143 "src/parser.y"
    {(yyval.texto)=unir_tipo("const",(yyvsp[(2) - (2)].texto));free((yyvsp[(2) - (2)].texto));semantica_establecer_tipo_declaracion((yyval.texto));;}
    break;

  case 19:
#line 144 "src/parser.y"
    {(yyval.texto)=unir_tipo("volatile",(yyvsp[(2) - (2)].texto));free((yyvsp[(2) - (2)].texto));semantica_establecer_tipo_declaracion((yyval.texto));;}
    break;

  case 20:
#line 147 "src/parser.y"
    {(yyval.texto)=duplicar_texto("");;}
    break;

  case 21:
#line 148 "src/parser.y"
    {(yyval.texto)=(yyvsp[(1) - (1)].texto);;}
    break;

  case 22:
#line 149 "src/parser.y"
    {(yyval.texto)=duplicar_texto("long");;}
    break;

  case 23:
#line 150 "src/parser.y"
    {(yyval.texto)=duplicar_texto("short");;}
    break;

  case 24:
#line 153 "src/parser.y"
    {(yyval.texto)=duplicar_texto("void");;}
    break;

  case 25:
#line 154 "src/parser.y"
    {(yyval.texto)=duplicar_texto("char");;}
    break;

  case 26:
#line 155 "src/parser.y"
    {(yyval.texto)=duplicar_texto("int");;}
    break;

  case 27:
#line 156 "src/parser.y"
    {(yyval.texto)=duplicar_texto("float");;}
    break;

  case 28:
#line 157 "src/parser.y"
    {(yyval.texto)=duplicar_texto("double");;}
    break;

  case 31:
#line 165 "src/parser.y"
    {agregar_declaracion_pendiente((yyvsp[(1) - (1)].texto),(yylsp[(1) - (1)]).first_line,(yylsp[(1) - (1)]).first_column,NULL);;}
    break;

  case 32:
#line 167 "src/parser.y"
    {agregar_declaracion_pendiente((yyvsp[(1) - (3)].texto),(yylsp[(1) - (3)]).first_line,(yylsp[(1) - (3)]).first_column,(yyvsp[(3) - (3)].expresion_semantica));;}
    break;

  case 33:
#line 171 "src/parser.y"
    {(yyval.parametros)=semantica_crear_parametros();;}
    break;

  case 34:
#line 172 "src/parser.y"
    {(yyval.parametros)=(yyvsp[(1) - (1)].parametros);;}
    break;

  case 35:
#line 175 "src/parser.y"
    {(yyval.parametros)=(yyvsp[(1) - (1)].parametros);;}
    break;

  case 36:
#line 177 "src/parser.y"
    {
          size_t i;
          for (i=0;i<(yyvsp[(3) - (3)].parametros)->cantidad;i++) semantica_agregar_parametro((yyvsp[(1) - (3)].parametros),(yyvsp[(3) - (3)].parametros)->elementos[i].tipo,
              (yyvsp[(3) - (3)].parametros)->elementos[i].nombre,(yyvsp[(3) - (3)].parametros)->elementos[i].linea,(yyvsp[(3) - (3)].parametros)->elementos[i].columna);
          (yyval.parametros)=(yyvsp[(1) - (3)].parametros);semantica_liberar_parametros((yyvsp[(3) - (3)].parametros));
      ;}
    break;

  case 37:
#line 186 "src/parser.y"
    {(yyval.parametros)=semantica_agregar_parametro(NULL,(yyvsp[(1) - (2)].texto),(yyvsp[(2) - (2)].texto),(yylsp[(2) - (2)]).first_line,(yylsp[(2) - (2)]).first_column);free((yyvsp[(1) - (2)].texto));free((yyvsp[(2) - (2)].texto));;}
    break;

  case 38:
#line 188 "src/parser.y"
    {(yyval.parametros)=semantica_agregar_parametro(NULL,(yyvsp[(1) - (1)].texto),"",(yylsp[(1) - (1)]).first_line,(yylsp[(1) - (1)]).first_column);free((yyvsp[(1) - (1)].texto));;}
    break;

  case 39:
#line 192 "src/parser.y"
    {semantica_entrar_bloque();;}
    break;

  case 40:
#line 192 "src/parser.y"
    {semantica_salir_bloque();;}
    break;

  case 47:
#line 205 "src/parser.y"
    {descartar_declaraciones_pendientes();analizador_finalizar_recuperacion();yyerrok;;}
    break;

  case 48:
#line 206 "src/parser.y"
    {descartar_declaraciones_pendientes();analizador_finalizar_recuperacion();yyerrok;;}
    break;

  case 49:
#line 211 "src/parser.y"
    {semantica_resolver((yyvsp[(3) - (4)].expresion_semantica));semantica_liberar_expresion((yyvsp[(3) - (4)].expresion_semantica));;}
    break;

  case 50:
#line 214 "src/parser.y"
    {semantica_resolver((yyvsp[(3) - (4)].expresion_semantica));semantica_liberar_expresion((yyvsp[(3) - (4)].expresion_semantica));;}
    break;

  case 51:
#line 217 "src/parser.y"
    {semantica_resolver((yyvsp[(3) - (4)].expresion_semantica));semantica_liberar_expresion((yyvsp[(3) - (4)].expresion_semantica));;}
    break;

  case 52:
#line 221 "src/parser.y"
    {
          semantica_resolver((yyvsp[(3) - (8)].expresion_semantica));semantica_resolver((yyvsp[(5) - (8)].expresion_semantica));semantica_resolver((yyvsp[(7) - (8)].expresion_semantica));
          semantica_liberar_expresion((yyvsp[(3) - (8)].expresion_semantica));semantica_liberar_expresion((yyvsp[(5) - (8)].expresion_semantica));semantica_liberar_expresion((yyvsp[(7) - (8)].expresion_semantica));
      ;}
    break;

  case 53:
#line 227 "src/parser.y"
    {semantica_resolver((yyvsp[(1) - (2)].expresion_semantica));semantica_liberar_expresion((yyvsp[(1) - (2)].expresion_semantica));;}
    break;

  case 59:
#line 234 "src/parser.y"
    {semantica_resolver((yyvsp[(5) - (7)].expresion_semantica));semantica_liberar_expresion((yyvsp[(5) - (7)].expresion_semantica));;}
    break;

  case 61:
#line 236 "src/parser.y"
    {free((yyvsp[(2) - (4)].texto));;}
    break;

  case 65:
#line 241 "src/parser.y"
    {semantica_retorno((yyvsp[(2) - (3)].expresion_semantica),(yylsp[(1) - (3)]).first_line,(yylsp[(1) - (3)]).first_column);;}
    break;

  case 66:
#line 243 "src/parser.y"
    {(yyval.expresion_semantica)=NULL;;}
    break;

  case 67:
#line 243 "src/parser.y"
    {(yyval.expresion_semantica)=(yyvsp[(1) - (1)].expresion_semantica);;}
    break;

  case 68:
#line 244 "src/parser.y"
    {(yyval.expresion_semantica)=(yyvsp[(1) - (1)].expresion_semantica);;}
    break;

  case 69:
#line 246 "src/parser.y"
    {(yyval.expresion_semantica)=(yyvsp[(1) - (1)].expresion_semantica);;}
    break;

  case 70:
#line 247 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_asignar("=",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 71:
#line 248 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_asignar("+=",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 72:
#line 249 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_asignar("-=",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 73:
#line 250 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_asignar("*=",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 74:
#line 251 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_asignar("/=",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 75:
#line 254 "src/parser.y"
    {(yyval.expresion_semantica)=(yyvsp[(1) - (1)].expresion_semantica);;}
    break;

  case 76:
#line 255 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_binaria("||",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 77:
#line 258 "src/parser.y"
    {(yyval.expresion_semantica)=(yyvsp[(1) - (1)].expresion_semantica);;}
    break;

  case 78:
#line 259 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_binaria("&&",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 79:
#line 262 "src/parser.y"
    {(yyval.expresion_semantica)=(yyvsp[(1) - (1)].expresion_semantica);;}
    break;

  case 80:
#line 263 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_binaria("==",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 81:
#line 264 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_binaria("!=",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 82:
#line 267 "src/parser.y"
    {(yyval.expresion_semantica)=(yyvsp[(1) - (1)].expresion_semantica);;}
    break;

  case 83:
#line 268 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_binaria("<",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 84:
#line 269 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_binaria(">",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 85:
#line 270 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_binaria("<=",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 86:
#line 271 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_binaria(">=",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 87:
#line 274 "src/parser.y"
    {(yyval.expresion_semantica)=(yyvsp[(1) - (1)].expresion_semantica);;}
    break;

  case 88:
#line 275 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_binaria("+",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 89:
#line 276 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_binaria("-",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 90:
#line 279 "src/parser.y"
    {(yyval.expresion_semantica)=(yyvsp[(1) - (1)].expresion_semantica);;}
    break;

  case 91:
#line 280 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_binaria("*",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 92:
#line 281 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_binaria("/",(yyvsp[(1) - (3)].expresion_semantica),(yyvsp[(3) - (3)].expresion_semantica),(yylsp[(2) - (3)]).first_line,(yylsp[(2) - (3)]).first_column);;}
    break;

  case 93:
#line 284 "src/parser.y"
    {(yyval.expresion_semantica)=(yyvsp[(1) - (1)].expresion_semantica);;}
    break;

  case 94:
#line 285 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_unaria("++",(yyvsp[(2) - (2)].expresion_semantica),(yylsp[(1) - (2)]).first_line,(yylsp[(1) - (2)]).first_column);;}
    break;

  case 95:
#line 286 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_unaria("--",(yyvsp[(2) - (2)].expresion_semantica),(yylsp[(1) - (2)]).first_line,(yylsp[(1) - (2)]).first_column);;}
    break;

  case 96:
#line 287 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_unaria("+",(yyvsp[(2) - (2)].expresion_semantica),(yylsp[(1) - (2)]).first_line,(yylsp[(1) - (2)]).first_column);;}
    break;

  case 97:
#line 288 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_unaria("-",(yyvsp[(2) - (2)].expresion_semantica),(yylsp[(1) - (2)]).first_line,(yylsp[(1) - (2)]).first_column);;}
    break;

  case 98:
#line 289 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_unaria("!",(yyvsp[(2) - (2)].expresion_semantica),(yylsp[(1) - (2)]).first_line,(yylsp[(1) - (2)]).first_column);;}
    break;

  case 99:
#line 290 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_unaria("sizeof",(yyvsp[(2) - (2)].expresion_semantica),(yylsp[(1) - (2)]).first_line,(yylsp[(1) - (2)]).first_column);;}
    break;

  case 100:
#line 293 "src/parser.y"
    {(yyval.expresion_semantica)=(yyvsp[(1) - (1)].expresion_semantica);;}
    break;

  case 101:
#line 295 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_invocar((yyvsp[(1) - (4)].expresion_semantica),(yyvsp[(3) - (4)].argumentos),(yylsp[(2) - (4)]).first_line,(yylsp[(2) - (4)]).first_column);;}
    break;

  case 102:
#line 296 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_postfija((yyvsp[(1) - (2)].expresion_semantica));;}
    break;

  case 103:
#line 297 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_postfija((yyvsp[(1) - (2)].expresion_semantica));;}
    break;

  case 104:
#line 300 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_identificador((yyvsp[(1) - (1)].texto),(yylsp[(1) - (1)]).first_line,(yylsp[(1) - (1)]).first_column);free((yyvsp[(1) - (1)].texto));;}
    break;

  case 105:
#line 301 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_literal((yyvsp[(1) - (1)].texto),0,(yylsp[(1) - (1)]).first_line,(yylsp[(1) - (1)]).first_column);free((yyvsp[(1) - (1)].texto));;}
    break;

  case 106:
#line 302 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_literal((yyvsp[(1) - (1)].texto),1,(yylsp[(1) - (1)]).first_line,(yylsp[(1) - (1)]).first_column);free((yyvsp[(1) - (1)].texto));;}
    break;

  case 107:
#line 303 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_literal((yyvsp[(1) - (1)].texto),2,(yylsp[(1) - (1)]).first_line,(yylsp[(1) - (1)]).first_column);free((yyvsp[(1) - (1)].texto));;}
    break;

  case 108:
#line 304 "src/parser.y"
    {(yyval.expresion_semantica)=semantica_literal((yyvsp[(1) - (1)].texto),3,(yylsp[(1) - (1)]).first_line,(yylsp[(1) - (1)]).first_column);free((yyvsp[(1) - (1)].texto));;}
    break;

  case 109:
#line 305 "src/parser.y"
    {(yyval.expresion_semantica)=(yyvsp[(2) - (3)].expresion_semantica);;}
    break;

  case 110:
#line 308 "src/parser.y"
    {(yyval.argumentos)=semantica_crear_argumentos();;}
    break;

  case 111:
#line 309 "src/parser.y"
    {(yyval.argumentos)=(yyvsp[(1) - (1)].argumentos);;}
    break;

  case 112:
#line 312 "src/parser.y"
    {(yyval.argumentos)=semantica_agregar_argumento(NULL,(yyvsp[(1) - (1)].expresion_semantica));;}
    break;

  case 113:
#line 313 "src/parser.y"
    {(yyval.argumentos)=semantica_agregar_argumento((yyvsp[(1) - (3)].argumentos),(yyvsp[(3) - (3)].expresion_semantica));;}
    break;


/* Line 1267 of yacc.c.  */
#line 2331 "obj/src/parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 315 "src/parser.y"

void yyerror(const char *mensaje) {
    int linea_error = analizador_linea_token_anterior();
    (void)mensaje;
    descartar_declaraciones_pendientes();
    semantica_limpiar_tipo_declaracion();
    if (linea_error < 1 || linea_error > yylloc.first_line)
        linea_error = yylloc.first_line;
    registrarErrorSintactico(linea_error, "");
    analizador_iniciar_recuperacion();
}

