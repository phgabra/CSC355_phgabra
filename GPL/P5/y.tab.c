/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "gpl.y"


// there is a compatibility problem with my current cygwin environment
// this appears to fix the problem
#undef __GNUC_MINOR__

#include "error.h"
#include "gpl_assert.h"
#include "symbol_table.h"
#include "symbol.h"
#include "gpl_type.h"
#include "expression.h"
#include "variable.h"
#include "constant.h"
#include <iostream>
#include <sstream>
#include <cmath> // for floor()
#include <stack>
using namespace std;

extern int yylex();
extern int yyerror(const char *);
extern int line_count;  // from gpl.l, used for statement blocks

int undeclared = 0;
Symbol_table *symbol_table = Symbol_table::instance();


#line 100 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_INT = 258,                   /* "int"  */
    T_DOUBLE = 259,                /* "double"  */
    T_STRING = 260,                /* "string"  */
    T_TRIANGLE = 261,              /* "triangle"  */
    T_PIXMAP = 262,                /* "pixmap"  */
    T_CIRCLE = 263,                /* "circle"  */
    T_RECTANGLE = 264,             /* "rectangle"  */
    T_TEXTBOX = 265,               /* "textbox"  */
    T_FORWARD = 266,               /* "forward"  */
    T_INITIALIZATION = 267,        /* "initialization"  */
    T_TERMINATION = 268,           /* "termination"  */
    T_TRUE = 269,                  /* "true"  */
    T_FALSE = 270,                 /* "false"  */
    T_ON = 271,                    /* "on"  */
    T_SPACE = 272,                 /* "space"  */
    T_LEFTARROW = 273,             /* "leftarrow"  */
    T_RIGHTARROW = 274,            /* "rightarrow"  */
    T_UPARROW = 275,               /* "uparrow"  */
    T_DOWNARROW = 276,             /* "downarrow"  */
    T_LEFTMOUSE_DOWN = 277,        /* "leftmouse_down"  */
    T_MIDDLEMOUSE_DOWN = 278,      /* "middlemouse_down"  */
    T_RIGHTMOUSE_DOWN = 279,       /* "rightmouse_down"  */
    T_LEFTMOUSE_UP = 280,          /* "leftmouse_up"  */
    T_MIDDLEMOUSE_UP = 281,        /* "middlemouse_up"  */
    T_RIGHTMOUSE_UP = 282,         /* "rightmouse_up"  */
    T_MOUSE_MOVE = 283,            /* "mouse_move"  */
    T_MOUSE_DRAG = 284,            /* "mouse_drag"  */
    T_F1 = 285,                    /* "f1"  */
    T_AKEY = 286,                  /* "akey"  */
    T_SKEY = 287,                  /* "skey"  */
    T_DKEY = 288,                  /* "dkey"  */
    T_FKEY = 289,                  /* "fkey"  */
    T_HKEY = 290,                  /* "hkey"  */
    T_JKEY = 291,                  /* "jkey"  */
    T_KKEY = 292,                  /* "kkey"  */
    T_LKEY = 293,                  /* "lkey"  */
    T_WKEY = 294,                  /* "wkey"  */
    T_ZKEY = 295,                  /* "zkey"  */
    T_TOUCHES = 296,               /* "touches"  */
    T_NEAR = 297,                  /* "near"  */
    T_ANIMATION = 298,             /* "animation"  */
    T_IF = 299,                    /* "if"  */
    T_FOR = 300,                   /* "for"  */
    T_ELSE = 301,                  /* "else"  */
    T_PRINT = 302,                 /* "print"  */
    T_EXIT = 303,                  /* "exit"  */
    T_LPAREN = 304,                /* "("  */
    T_RPAREN = 305,                /* ")"  */
    T_LBRACE = 306,                /* "{"  */
    T_RBRACE = 307,                /* "}"  */
    T_LBRACKET = 308,              /* "["  */
    T_RBRACKET = 309,              /* "]"  */
    T_SEMIC = 310,                 /* ";"  */
    T_COMMA = 311,                 /* ","  */
    T_PERIOD = 312,                /* "."  */
    T_ASSIGN = 313,                /* "="  */
    T_PLUS_ASSIGN = 314,           /* "+="  */
    T_MINUS_ASSIGN = 315,          /* "-="  */
    T_PLUS_PLUS = 316,             /* "++"  */
    T_MINUS_MINUS = 317,           /* "--"  */
    T_MULTIPLY = 318,              /* "*"  */
    T_DIVIDE = 319,                /* "/"  */
    T_MOD = 320,                   /* "%"  */
    T_PLUS = 321,                  /* "+"  */
    T_MINUS = 322,                 /* "-"  */
    T_SIN = 323,                   /* "sin"  */
    T_COS = 324,                   /* "cos"  */
    T_TAN = 325,                   /* "tan"  */
    T_ASIN = 326,                  /* "asin"  */
    T_ACOS = 327,                  /* "acos"  */
    T_ATAN = 328,                  /* "atan"  */
    T_SQRT = 329,                  /* "sqrt"  */
    T_FLOOR = 330,                 /* "floor"  */
    T_ABS = 331,                   /* "abs"  */
    T_RANDOM = 332,                /* "random"  */
    T_LESS = 333,                  /* "<"  */
    T_GREATER = 334,               /* ">"  */
    T_LESS_EQUAL = 335,            /* "<="  */
    T_GREATER_EQUAL = 336,         /* ">="  */
    T_EQUAL = 337,                 /* "=="  */
    T_NOT_EQUAL = 338,             /* "!="  */
    T_AND = 339,                   /* "&&"  */
    T_OR = 340,                    /* "||"  */
    T_NOT = 341,                   /* "!"  */
    T_ID = 342,                    /* "identifier"  */
    T_INT_CONSTANT = 343,          /* "int constant"  */
    T_DOUBLE_CONSTANT = 344,       /* "double constant"  */
    T_STRING_CONSTANT = 345,       /* "string constant"  */
    T_ERROR = 346,                 /* "error"  */
    IF_NO_ELSE = 347,              /* IF_NO_ELSE  */
    UNARY_OPS = 348                /* UNARY_OPS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define T_INT 258
#define T_DOUBLE 259
#define T_STRING 260
#define T_TRIANGLE 261
#define T_PIXMAP 262
#define T_CIRCLE 263
#define T_RECTANGLE 264
#define T_TEXTBOX 265
#define T_FORWARD 266
#define T_INITIALIZATION 267
#define T_TERMINATION 268
#define T_TRUE 269
#define T_FALSE 270
#define T_ON 271
#define T_SPACE 272
#define T_LEFTARROW 273
#define T_RIGHTARROW 274
#define T_UPARROW 275
#define T_DOWNARROW 276
#define T_LEFTMOUSE_DOWN 277
#define T_MIDDLEMOUSE_DOWN 278
#define T_RIGHTMOUSE_DOWN 279
#define T_LEFTMOUSE_UP 280
#define T_MIDDLEMOUSE_UP 281
#define T_RIGHTMOUSE_UP 282
#define T_MOUSE_MOVE 283
#define T_MOUSE_DRAG 284
#define T_F1 285
#define T_AKEY 286
#define T_SKEY 287
#define T_DKEY 288
#define T_FKEY 289
#define T_HKEY 290
#define T_JKEY 291
#define T_KKEY 292
#define T_LKEY 293
#define T_WKEY 294
#define T_ZKEY 295
#define T_TOUCHES 296
#define T_NEAR 297
#define T_ANIMATION 298
#define T_IF 299
#define T_FOR 300
#define T_ELSE 301
#define T_PRINT 302
#define T_EXIT 303
#define T_LPAREN 304
#define T_RPAREN 305
#define T_LBRACE 306
#define T_RBRACE 307
#define T_LBRACKET 308
#define T_RBRACKET 309
#define T_SEMIC 310
#define T_COMMA 311
#define T_PERIOD 312
#define T_ASSIGN 313
#define T_PLUS_ASSIGN 314
#define T_MINUS_ASSIGN 315
#define T_PLUS_PLUS 316
#define T_MINUS_MINUS 317
#define T_MULTIPLY 318
#define T_DIVIDE 319
#define T_MOD 320
#define T_PLUS 321
#define T_MINUS 322
#define T_SIN 323
#define T_COS 324
#define T_TAN 325
#define T_ASIN 326
#define T_ACOS 327
#define T_ATAN 328
#define T_SQRT 329
#define T_FLOOR 330
#define T_ABS 331
#define T_RANDOM 332
#define T_LESS 333
#define T_GREATER 334
#define T_LESS_EQUAL 335
#define T_GREATER_EQUAL 336
#define T_EQUAL 337
#define T_NOT_EQUAL 338
#define T_AND 339
#define T_OR 340
#define T_NOT 341
#define T_ID 342
#define T_INT_CONSTANT 343
#define T_DOUBLE_CONSTANT 344
#define T_STRING_CONSTANT 345
#define T_ERROR 346
#define IF_NO_ELSE 347
#define UNARY_OPS 348

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 30 "gpl.y"

  int                           union_int;
  double                        union_double;
  std::string                   *union_string;  // MUST be a pointer to a string ARG!
  int                           gpl_type;
  Expression                    *union_expression;
  Variable                      *union_variable;

#line 348 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_INT = 3,                      /* "int"  */
  YYSYMBOL_T_DOUBLE = 4,                   /* "double"  */
  YYSYMBOL_T_STRING = 5,                   /* "string"  */
  YYSYMBOL_T_TRIANGLE = 6,                 /* "triangle"  */
  YYSYMBOL_T_PIXMAP = 7,                   /* "pixmap"  */
  YYSYMBOL_T_CIRCLE = 8,                   /* "circle"  */
  YYSYMBOL_T_RECTANGLE = 9,                /* "rectangle"  */
  YYSYMBOL_T_TEXTBOX = 10,                 /* "textbox"  */
  YYSYMBOL_T_FORWARD = 11,                 /* "forward"  */
  YYSYMBOL_T_INITIALIZATION = 12,          /* "initialization"  */
  YYSYMBOL_T_TERMINATION = 13,             /* "termination"  */
  YYSYMBOL_T_TRUE = 14,                    /* "true"  */
  YYSYMBOL_T_FALSE = 15,                   /* "false"  */
  YYSYMBOL_T_ON = 16,                      /* "on"  */
  YYSYMBOL_T_SPACE = 17,                   /* "space"  */
  YYSYMBOL_T_LEFTARROW = 18,               /* "leftarrow"  */
  YYSYMBOL_T_RIGHTARROW = 19,              /* "rightarrow"  */
  YYSYMBOL_T_UPARROW = 20,                 /* "uparrow"  */
  YYSYMBOL_T_DOWNARROW = 21,               /* "downarrow"  */
  YYSYMBOL_T_LEFTMOUSE_DOWN = 22,          /* "leftmouse_down"  */
  YYSYMBOL_T_MIDDLEMOUSE_DOWN = 23,        /* "middlemouse_down"  */
  YYSYMBOL_T_RIGHTMOUSE_DOWN = 24,         /* "rightmouse_down"  */
  YYSYMBOL_T_LEFTMOUSE_UP = 25,            /* "leftmouse_up"  */
  YYSYMBOL_T_MIDDLEMOUSE_UP = 26,          /* "middlemouse_up"  */
  YYSYMBOL_T_RIGHTMOUSE_UP = 27,           /* "rightmouse_up"  */
  YYSYMBOL_T_MOUSE_MOVE = 28,              /* "mouse_move"  */
  YYSYMBOL_T_MOUSE_DRAG = 29,              /* "mouse_drag"  */
  YYSYMBOL_T_F1 = 30,                      /* "f1"  */
  YYSYMBOL_T_AKEY = 31,                    /* "akey"  */
  YYSYMBOL_T_SKEY = 32,                    /* "skey"  */
  YYSYMBOL_T_DKEY = 33,                    /* "dkey"  */
  YYSYMBOL_T_FKEY = 34,                    /* "fkey"  */
  YYSYMBOL_T_HKEY = 35,                    /* "hkey"  */
  YYSYMBOL_T_JKEY = 36,                    /* "jkey"  */
  YYSYMBOL_T_KKEY = 37,                    /* "kkey"  */
  YYSYMBOL_T_LKEY = 38,                    /* "lkey"  */
  YYSYMBOL_T_WKEY = 39,                    /* "wkey"  */
  YYSYMBOL_T_ZKEY = 40,                    /* "zkey"  */
  YYSYMBOL_T_TOUCHES = 41,                 /* "touches"  */
  YYSYMBOL_T_NEAR = 42,                    /* "near"  */
  YYSYMBOL_T_ANIMATION = 43,               /* "animation"  */
  YYSYMBOL_T_IF = 44,                      /* "if"  */
  YYSYMBOL_T_FOR = 45,                     /* "for"  */
  YYSYMBOL_T_ELSE = 46,                    /* "else"  */
  YYSYMBOL_T_PRINT = 47,                   /* "print"  */
  YYSYMBOL_T_EXIT = 48,                    /* "exit"  */
  YYSYMBOL_T_LPAREN = 49,                  /* "("  */
  YYSYMBOL_T_RPAREN = 50,                  /* ")"  */
  YYSYMBOL_T_LBRACE = 51,                  /* "{"  */
  YYSYMBOL_T_RBRACE = 52,                  /* "}"  */
  YYSYMBOL_T_LBRACKET = 53,                /* "["  */
  YYSYMBOL_T_RBRACKET = 54,                /* "]"  */
  YYSYMBOL_T_SEMIC = 55,                   /* ";"  */
  YYSYMBOL_T_COMMA = 56,                   /* ","  */
  YYSYMBOL_T_PERIOD = 57,                  /* "."  */
  YYSYMBOL_T_ASSIGN = 58,                  /* "="  */
  YYSYMBOL_T_PLUS_ASSIGN = 59,             /* "+="  */
  YYSYMBOL_T_MINUS_ASSIGN = 60,            /* "-="  */
  YYSYMBOL_T_PLUS_PLUS = 61,               /* "++"  */
  YYSYMBOL_T_MINUS_MINUS = 62,             /* "--"  */
  YYSYMBOL_T_MULTIPLY = 63,                /* "*"  */
  YYSYMBOL_T_DIVIDE = 64,                  /* "/"  */
  YYSYMBOL_T_MOD = 65,                     /* "%"  */
  YYSYMBOL_T_PLUS = 66,                    /* "+"  */
  YYSYMBOL_T_MINUS = 67,                   /* "-"  */
  YYSYMBOL_T_SIN = 68,                     /* "sin"  */
  YYSYMBOL_T_COS = 69,                     /* "cos"  */
  YYSYMBOL_T_TAN = 70,                     /* "tan"  */
  YYSYMBOL_T_ASIN = 71,                    /* "asin"  */
  YYSYMBOL_T_ACOS = 72,                    /* "acos"  */
  YYSYMBOL_T_ATAN = 73,                    /* "atan"  */
  YYSYMBOL_T_SQRT = 74,                    /* "sqrt"  */
  YYSYMBOL_T_FLOOR = 75,                   /* "floor"  */
  YYSYMBOL_T_ABS = 76,                     /* "abs"  */
  YYSYMBOL_T_RANDOM = 77,                  /* "random"  */
  YYSYMBOL_T_LESS = 78,                    /* "<"  */
  YYSYMBOL_T_GREATER = 79,                 /* ">"  */
  YYSYMBOL_T_LESS_EQUAL = 80,              /* "<="  */
  YYSYMBOL_T_GREATER_EQUAL = 81,           /* ">="  */
  YYSYMBOL_T_EQUAL = 82,                   /* "=="  */
  YYSYMBOL_T_NOT_EQUAL = 83,               /* "!="  */
  YYSYMBOL_T_AND = 84,                     /* "&&"  */
  YYSYMBOL_T_OR = 85,                      /* "||"  */
  YYSYMBOL_T_NOT = 86,                     /* "!"  */
  YYSYMBOL_T_ID = 87,                      /* "identifier"  */
  YYSYMBOL_T_INT_CONSTANT = 88,            /* "int constant"  */
  YYSYMBOL_T_DOUBLE_CONSTANT = 89,         /* "double constant"  */
  YYSYMBOL_T_STRING_CONSTANT = 90,         /* "string constant"  */
  YYSYMBOL_T_ERROR = 91,                   /* "error"  */
  YYSYMBOL_IF_NO_ELSE = 92,                /* IF_NO_ELSE  */
  YYSYMBOL_UNARY_OPS = 93,                 /* UNARY_OPS  */
  YYSYMBOL_YYACCEPT = 94,                  /* $accept  */
  YYSYMBOL_program = 95,                   /* program  */
  YYSYMBOL_declaration_list = 96,          /* declaration_list  */
  YYSYMBOL_declaration = 97,               /* declaration  */
  YYSYMBOL_variable_declaration = 98,      /* variable_declaration  */
  YYSYMBOL_simple_type = 99,               /* simple_type  */
  YYSYMBOL_optional_initializer = 100,     /* optional_initializer  */
  YYSYMBOL_object_declaration = 101,       /* object_declaration  */
  YYSYMBOL_object_type = 102,              /* object_type  */
  YYSYMBOL_parameter_list_or_empty = 103,  /* parameter_list_or_empty  */
  YYSYMBOL_parameter_list = 104,           /* parameter_list  */
  YYSYMBOL_parameter = 105,                /* parameter  */
  YYSYMBOL_forward_declaration = 106,      /* forward_declaration  */
  YYSYMBOL_block_list = 107,               /* block_list  */
  YYSYMBOL_block = 108,                    /* block  */
  YYSYMBOL_initialization_block = 109,     /* initialization_block  */
  YYSYMBOL_termination_block = 110,        /* termination_block  */
  YYSYMBOL_animation_block = 111,          /* animation_block  */
  YYSYMBOL_animation_parameter = 112,      /* animation_parameter  */
  YYSYMBOL_check_animation_parameter = 113, /* check_animation_parameter  */
  YYSYMBOL_on_block = 114,                 /* on_block  */
  YYSYMBOL_keystroke = 115,                /* keystroke  */
  YYSYMBOL_if_block = 116,                 /* if_block  */
  YYSYMBOL_statement_block = 117,          /* statement_block  */
  YYSYMBOL_statement_block_creator = 118,  /* statement_block_creator  */
  YYSYMBOL_end_of_statement_block = 119,   /* end_of_statement_block  */
  YYSYMBOL_statement_list = 120,           /* statement_list  */
  YYSYMBOL_statement = 121,                /* statement  */
  YYSYMBOL_if_statement = 122,             /* if_statement  */
  YYSYMBOL_for_statement = 123,            /* for_statement  */
  YYSYMBOL_print_statement = 124,          /* print_statement  */
  YYSYMBOL_exit_statement = 125,           /* exit_statement  */
  YYSYMBOL_assign_statement_or_empty = 126, /* assign_statement_or_empty  */
  YYSYMBOL_assign_statement = 127,         /* assign_statement  */
  YYSYMBOL_variable = 128,                 /* variable  */
  YYSYMBOL_expression = 129,               /* expression  */
  YYSYMBOL_primary_expression = 130,       /* primary_expression  */
  YYSYMBOL_math_operator = 131,            /* math_operator  */
  YYSYMBOL_empty = 132                     /* empty  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   400

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  126
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  217

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   348


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   167,   167,   172,   173,   178,   179,   180,   185,   242,
     243,   244,   249,   253,   260,   261,   266,   267,   268,   269,
     270,   275,   276,   281,   282,   287,   292,   297,   298,   303,
     304,   305,   306,   311,   316,   321,   326,   331,   336,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   369,   370,   375,   379,   384,   390,   391,
     396,   397,   398,   399,   400,   405,   406,   411,   416,   421,
     426,   427,   432,   433,   434,   435,   436,   441,   456,   484,
     492,   506,   520,   524,   528,   532,   536,   540,   544,   555,
     569,   583,   597,   611,   622,   633,   648,   652,   656,   660,
     664,   672,   673,   674,   675,   676,   677,   678,   679,   680,
     681,   682,   683,   684,   685,   686,   690
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"int\"",
  "\"double\"", "\"string\"", "\"triangle\"", "\"pixmap\"", "\"circle\"",
  "\"rectangle\"", "\"textbox\"", "\"forward\"", "\"initialization\"",
  "\"termination\"", "\"true\"", "\"false\"", "\"on\"", "\"space\"",
  "\"leftarrow\"", "\"rightarrow\"", "\"uparrow\"", "\"downarrow\"",
  "\"leftmouse_down\"", "\"middlemouse_down\"", "\"rightmouse_down\"",
  "\"leftmouse_up\"", "\"middlemouse_up\"", "\"rightmouse_up\"",
  "\"mouse_move\"", "\"mouse_drag\"", "\"f1\"", "\"akey\"", "\"skey\"",
  "\"dkey\"", "\"fkey\"", "\"hkey\"", "\"jkey\"", "\"kkey\"", "\"lkey\"",
  "\"wkey\"", "\"zkey\"", "\"touches\"", "\"near\"", "\"animation\"",
  "\"if\"", "\"for\"", "\"else\"", "\"print\"", "\"exit\"", "\"(\"",
  "\")\"", "\"{\"", "\"}\"", "\"[\"", "\"]\"", "\";\"", "\",\"", "\".\"",
  "\"=\"", "\"+=\"", "\"-=\"", "\"++\"", "\"--\"", "\"*\"", "\"/\"",
  "\"%\"", "\"+\"", "\"-\"", "\"sin\"", "\"cos\"", "\"tan\"", "\"asin\"",
  "\"acos\"", "\"atan\"", "\"sqrt\"", "\"floor\"", "\"abs\"", "\"random\"",
  "\"<\"", "\">\"", "\"<=\"", "\">=\"", "\"==\"", "\"!=\"", "\"&&\"",
  "\"||\"", "\"!\"", "\"identifier\"", "\"int constant\"",
  "\"double constant\"", "\"string constant\"", "\"error\"", "IF_NO_ELSE",
  "UNARY_OPS", "$accept", "program", "declaration_list", "declaration",
  "variable_declaration", "simple_type", "optional_initializer",
  "object_declaration", "object_type", "parameter_list_or_empty",
  "parameter_list", "parameter", "forward_declaration", "block_list",
  "block", "initialization_block", "termination_block", "animation_block",
  "animation_parameter", "check_animation_parameter", "on_block",
  "keystroke", "if_block", "statement_block", "statement_block_creator",
  "end_of_statement_block", "statement_list", "statement", "if_statement",
  "for_statement", "print_statement", "exit_statement",
  "assign_statement_or_empty", "assign_statement", "variable",
  "expression", "primary_expression", "math_operator", "empty", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-181)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -181,    17,    59,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,   -15,  -181,   -20,   -56,   -18,   -49,   -16,
      11,  -181,   -43,  -181,   -12,  -181,   -24,  -181,    -3,    -3,
     331,   -36,  -181,  -181,  -181,  -181,  -181,     1,    86,  -181,
    -181,   -34,    86,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
      -3,    43,    92,    86,  -181,  -181,  -181,  -181,    86,  -181,
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,    86,
      40,  -181,  -181,  -181,  -181,   309,  -181,    46,    38,    54,
      47,  -181,  -181,   208,  -181,  -181,    92,    34,    80,    44,
    -181,  -181,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,  -181,   -34,
    -181,   -38,  -181,    45,    81,  -181,  -181,  -181,   231,  -181,
    -181,  -181,    49,    49,    53,    53,    53,    53,    -7,    -7,
     317,   240,   114,   309,  -181,    84,    88,    91,    93,  -181,
    -181,  -181,  -181,   127,   128,   129,  -181,   107,  -181,  -181,
      90,  -181,  -181,    86,  -181,    86,    86,  -181,  -181,  -181,
    -181,    86,    86,    86,  -181,  -181,  -181,   139,    56,   162,
     185,   309,   309,   309,   -32,    -3,  -181,  -181,  -181,  -181,
     101,  -181,   -26,   130,  -181,    -3,  -181,    86,  -181,  -181,
     262,  -181,    56,  -181,    98,    -3,  -181
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
     126,     0,   126,     4,     1,     9,    10,    11,    16,    17,
      18,    19,    20,     0,     3,     0,     0,     0,     0,     0,
       2,    28,     0,     5,   126,     6,     0,     7,     0,     0,
       0,     0,    27,    29,    30,    31,    32,     0,     0,     8,
      13,   126,     0,    66,    33,    34,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
       0,     0,     0,     0,   111,   112,   115,   113,     0,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,     0,
      87,   108,   109,   110,   107,    12,    89,     0,     0,     0,
      21,    24,    22,     0,   126,    38,     0,     0,     0,     0,
     103,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    14,     0,
      15,   126,    69,     0,     0,    36,    26,   106,     0,   100,
     101,   102,    98,    99,    94,    95,    92,    93,    96,    97,
      91,    90,     0,    25,    23,     0,     0,     0,     0,    67,
      68,    70,    71,     0,     0,     0,    80,     0,    81,    37,
       0,    88,   105,     0,    66,     0,     0,    65,    72,    73,
      74,     0,     0,     0,    85,    86,   126,     0,   126,     0,
       0,    82,    83,    84,   126,    66,    67,    78,    79,    67,
      75,    64,   126,     0,    35,    66,    67,     0,    76,    63,
       0,    66,   126,    67,     0,     0,    77
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,   -61,  -181,
    -181,    57,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,   -14,   -28,   -40,  -166,     4,    -2,  -181,  -181,
    -181,  -181,  -180,  -181,   -97,   -37,  -181,  -181,     2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    14,    15,    16,    39,    17,    18,    99,
     100,   101,    19,    20,    32,    33,    34,    35,   108,   134,
      36,    70,   200,   201,   202,   177,   131,   160,   161,   162,
     163,   164,   165,   166,    94,    95,    96,    97,   168
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      44,    45,     3,   104,    21,   103,   155,   156,   196,   157,
     158,   107,   155,   156,   159,   157,   158,     4,   155,   156,
     199,   157,   158,    28,    29,    41,    40,    30,    22,    42,
     203,    24,   213,   204,   167,    23,   109,    25,    26,    27,
     209,   110,   105,   102,    37,   133,    38,   214,    43,    90,
      72,    71,   111,    98,    31,    90,   113,   114,   115,   116,
     117,    90,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   118,   119,   120,   121,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   167,   106,   112,   137,   126,   127,   167,     8,     9,
      10,    11,    12,   129,   128,   167,   132,   113,   114,   115,
     116,   117,   113,   114,   115,   167,   113,   114,   115,   116,
     117,   135,   118,   119,   120,   121,   122,   123,   124,   125,
     136,   170,   169,   173,   188,    73,   187,   174,   189,   190,
     175,   186,   176,    90,   191,   192,   193,   205,   215,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,   172,   181,   182,   183,   184,   185,
     210,   212,    89,    90,    91,    92,    93,   113,   114,   115,
     116,   117,   178,   179,   180,   207,   154,   216,   132,   195,
     194,   208,   118,   119,   120,   121,   122,   123,   124,   125,
     206,     0,   113,   114,   115,   116,   117,     0,     0,     0,
       0,     0,   197,     0,     0,     0,     0,   118,   119,   120,
     121,   122,   123,   124,   125,   113,   114,   115,   116,   117,
       0,     0,     0,     0,     0,   198,     0,     0,     0,     0,
     118,   119,   120,   121,   122,   123,   124,   125,   113,   114,
     115,   116,   117,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,   118,   119,   120,   121,   122,   123,   124,
     125,   113,   114,   115,   116,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   171,   118,   119,   120,   121,
     122,   123,   124,   125,   113,   114,   115,   116,   117,     0,
       0,     0,     0,   113,   114,   115,   116,   117,     0,   118,
     119,   120,   121,   122,   123,   124,   125,   211,   118,   119,
     120,   121,   122,   123,   124,   113,   114,   115,   116,   117,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     118,   119,   120,   121,   122,   123,   124,   125,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,   113,   114,   115,   116,   117,     0,     0,     0,
     113,   114,   115,   116,   117,     0,     0,   118,   119,   120,
     121,   122,   123,   124,   125,   118,   119,   120,   121,   122,
     123
};

static const yytype_int16 yycheck[] =
{
      28,    29,     0,    43,     2,    42,    44,    45,   188,    47,
      48,    72,    44,    45,    52,    47,    48,     0,    44,    45,
      52,    47,    48,    12,    13,    49,    24,    16,    43,    53,
     196,    87,   212,   199,   131,    55,    73,    55,    87,    55,
     206,    78,    70,    41,    87,   106,    58,   213,    51,    87,
      49,    87,    89,    87,    43,    87,    63,    64,    65,    66,
      67,    87,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    78,    79,    80,    81,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   188,    49,    53,    50,    49,    58,   194,     6,     7,
       8,     9,    10,    56,    50,   202,   104,    63,    64,    65,
      66,    67,    63,    64,    65,   212,    63,    64,    65,    66,
      67,    87,    78,    79,    80,    81,    82,    83,    84,    85,
      50,    50,    87,    49,   174,    49,   173,    49,   175,   176,
      49,    51,    49,    87,   181,   182,   183,    46,    50,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    50,    58,    59,    60,    61,    62,
     207,   211,    86,    87,    88,    89,    90,    63,    64,    65,
      66,    67,    55,    55,    55,    55,   129,   215,   186,    50,
     186,   205,    78,    79,    80,    81,    82,    83,    84,    85,
     202,    -1,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    78,    79,    80,
      81,    82,    83,    84,    85,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      78,    79,    80,    81,    82,    83,    84,    85,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    78,    79,    80,    81,    82,    83,    84,
      85,    63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    78,    79,    80,    81,
      82,    83,    84,    85,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    67,    -1,    78,
      79,    80,    81,    82,    83,    84,    85,    55,    78,    79,
      80,    81,    82,    83,    84,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    80,    81,    82,    83,    84,    85,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      63,    64,    65,    66,    67,    -1,    -1,    78,    79,    80,
      81,    82,    83,    84,    85,    78,    79,    80,    81,    82,
      83
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    95,    96,   132,     0,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    97,    98,    99,   101,   102,   106,
     107,   132,    43,    55,    87,    55,    87,    55,    12,    13,
      16,    43,   108,   109,   110,   111,   114,    87,    58,   100,
     132,    49,    53,    51,   117,   117,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
     115,    87,    49,    49,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    86,
      87,    88,    89,    90,   128,   129,   130,   131,    87,   103,
     104,   105,   132,   129,   118,   117,    49,   102,   112,   129,
     129,   129,    53,    63,    64,    65,    66,    67,    78,    79,
      80,    81,    82,    83,    84,    85,    49,    58,    50,    56,
      54,   120,   132,   102,   113,    87,    50,    50,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   105,    44,    45,    47,    48,    52,
     121,   122,   123,   124,   125,   126,   127,   128,   132,    87,
      50,    54,    50,    49,    49,    49,    49,   119,    55,    55,
      55,    58,    59,    60,    61,    62,    51,   129,   118,   129,
     129,   129,   129,   129,   120,    50,   126,    50,    50,    52,
     116,   117,   118,   119,   119,    46,   121,    55,   116,   119,
     129,    55,   118,   126,   119,    50,   117
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    96,    96,    97,    97,    97,    98,    99,
      99,    99,   100,   100,   101,   101,   102,   102,   102,   102,
     102,   103,   103,   104,   104,   105,   106,   107,   107,   108,
     108,   108,   108,   109,   110,   111,   112,   113,   114,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   116,   116,   117,   118,   119,   120,   120,
     121,   121,   121,   121,   121,   122,   122,   123,   124,   125,
     126,   126,   127,   127,   127,   127,   127,   128,   128,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   130,   130,   130,   130,
     130,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   132
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     2,     2,     2,     3,     1,
       1,     1,     2,     1,     5,     5,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     6,     2,     1,     1,
       1,     1,     1,     2,     2,     9,     2,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     5,     0,     0,     2,     1,
       1,     1,     2,     2,     2,     5,     7,    13,     4,     4,
       1,     1,     3,     3,     3,     2,     2,     1,     4,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     4,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 8: /* variable_declaration: simple_type "identifier" optional_initializer  */
#line 186 "gpl.y"
    {
        std::string var_name = *(yyvsp[-1].union_string);
        int declared_type = (yyvsp[-2].gpl_type);
        Symbol *new_symbol = nullptr;

        if ((yyvsp[0].union_expression)) {
            Expression *initializer_expr = (yyvsp[0].union_expression);
            int initializer_type = initializer_expr->get_type();

            // Ensure initializer type matches the declared variable type
            if (initializer_type != declared_type) {
                std::string declared_type_str = gpl_type_to_string(static_cast<Gpl_type>(declared_type));
                std::string initializer_type_str = gpl_type_to_string(static_cast<Gpl_type>(initializer_type));

                Error::error(Error::ASSIGNMENT_TYPE_ERROR, "Cannot assign an expression of type '" 
                             + initializer_type_str + "' to a variable of type '" + declared_type_str + "'");
                
                // Use default value for recovery based on declared type
                if (declared_type == INT) {
                    new_symbol = new Symbol(var_name, 0);
                } else if (declared_type == DOUBLE) {
                    new_symbol = new Symbol(var_name, 0.0);
                } else if (declared_type == STRING) {
                    new_symbol = new Symbol(var_name, std::string(""));
                }
            } else {
                // Initialize with evaluated value based on the matching type
                if (declared_type == INT) {
                    new_symbol = new Symbol(var_name, initializer_expr->eval_int());
                } else if (declared_type == DOUBLE) {
                    new_symbol = new Symbol(var_name, initializer_expr->eval_double());
                } else if (declared_type == STRING) {
                    new_symbol = new Symbol(var_name, initializer_expr->eval_string());
                }
            }
        } else {
            // No initializer provided; assign default value based on type
            if (declared_type == INT) {
                new_symbol = new Symbol(var_name, 0);
            } else if (declared_type == DOUBLE) {
                new_symbol = new Symbol(var_name, 0.0);
            } else if (declared_type == STRING) {
                new_symbol = new Symbol(var_name, std::string(""));
            }
        }

        // Insert the symbol into the symbol table and handle re-declaration error
        if (new_symbol && !symbol_table->insert(new_symbol)) {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, var_name);
            delete new_symbol;
        }
    }
#line 1987 "y.tab.c"
    break;

  case 9: /* simple_type: "int"  */
#line 242 "gpl.y"
          { (yyval.gpl_type) = INT; }
#line 1993 "y.tab.c"
    break;

  case 10: /* simple_type: "double"  */
#line 243 "gpl.y"
               { (yyval.gpl_type) = DOUBLE; }
#line 1999 "y.tab.c"
    break;

  case 11: /* simple_type: "string"  */
#line 244 "gpl.y"
               { (yyval.gpl_type) = STRING; }
#line 2005 "y.tab.c"
    break;

  case 12: /* optional_initializer: "=" expression  */
#line 250 "gpl.y"
    {
        (yyval.union_expression) = (yyvsp[0].union_expression);
    }
#line 2013 "y.tab.c"
    break;

  case 13: /* optional_initializer: empty  */
#line 254 "gpl.y"
    {
        (yyval.union_expression) = nullptr;
    }
#line 2021 "y.tab.c"
    break;

  case 87: /* variable: "identifier"  */
#line 442 "gpl.y"
    {
        Symbol *sym = Symbol_table::instance()->lookup(*(yyvsp[0].union_string));
        if (!sym) {
            Error::error(Error::UNDECLARED_VARIABLE, *(yyvsp[0].union_string));
            (yyval.union_variable) = nullptr;
        } else if (sym->is_array()) {
            // Error if trying to use an array without indexing
            Error::error(Error::VARIABLE_IS_AN_ARRAY, *(yyvsp[0].union_string));
            (yyval.union_variable) = nullptr;
        } else {
            (yyval.union_variable) = new Variable(sym);  // Regular variable handling
        }
        delete (yyvsp[0].union_string);
    }
#line 2040 "y.tab.c"
    break;

  case 88: /* variable: "identifier" "[" expression "]"  */
#line 457 "gpl.y"
    {
        Symbol *sym = Symbol_table::instance()->lookup(*(yyvsp[-3].union_string));
        if (!sym) {
            Error::error(Error::UNDECLARED_VARIABLE, *(yyvsp[-3].union_string)+"[]");
            (yyval.union_variable) = nullptr;
        } else if (!sym->is_array()) {
            // Error if trying to index a non-array variable
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, *(yyvsp[-3].union_string));
            (yyval.union_variable) = nullptr;
        } else {
            Gpl_type index_type = (yyvsp[-1].union_expression)->get_type();

            // Check if the index expression is not an integer
            if (index_type != INT) {
                // Error: non-integer type used as array index
                Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *(yyvsp[-3].union_string), "A " + gpl_type_to_string(index_type) + " expression");
                (yyval.union_variable) = nullptr;
            } else {
                // Valid array element access
                (yyval.union_variable) = new Variable(sym, (yyvsp[-1].union_expression));
            }
    }
        delete (yyvsp[-3].union_string);
    }
#line 2069 "y.tab.c"
    break;

  case 89: /* expression: primary_expression  */
#line 485 "gpl.y"
    {
        if (!(yyvsp[0].union_expression)) {
            (yyval.union_expression) = new Expression(0);  // Default to error state
        } else {
            (yyval.union_expression) = (yyvsp[0].union_expression);
        }
    }
#line 2081 "y.tab.c"
    break;

  case 90: /* expression: expression "||" expression  */
#line 493 "gpl.y"
    {
        bool valid_left = ((yyvsp[-2].union_expression) && (yyvsp[-2].union_expression)->get_type() != STRING);
        bool valid_right = ((yyvsp[0].union_expression) && (yyvsp[0].union_expression)->get_type() != STRING);

        if (!valid_left) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "||", gpl_type_to_string((yyvsp[-2].union_expression)->get_type()));
        }
        if (!valid_right) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "||", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
        }

        (yyval.union_expression) = (valid_left && valid_right) ? new Expression(OR, (yyvsp[-2].union_expression), (yyvsp[0].union_expression)) : new Expression(0);
    }
#line 2099 "y.tab.c"
    break;

  case 91: /* expression: expression "&&" expression  */
#line 507 "gpl.y"
    {
        bool valid_left = ((yyvsp[-2].union_expression) && (yyvsp[-2].union_expression)->get_type() != STRING);
        bool valid_right = ((yyvsp[0].union_expression) && (yyvsp[0].union_expression)->get_type() != STRING);

        if (!valid_left) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "&&", gpl_type_to_string((yyvsp[-2].union_expression)->get_type()));
        }
        if (!valid_right) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "&&", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
        }

        (yyval.union_expression) = (valid_left && valid_right) ? new Expression(AND, (yyvsp[-2].union_expression), (yyvsp[0].union_expression)) : new Expression(0);
    }
#line 2117 "y.tab.c"
    break;

  case 92: /* expression: expression "<=" expression  */
#line 521 "gpl.y"
    {
        (yyval.union_expression) = ((yyvsp[-2].union_expression) && (yyvsp[0].union_expression)) ? new Expression(LESS_EQUAL, (yyvsp[-2].union_expression), (yyvsp[0].union_expression)) : new Expression(0);
    }
#line 2125 "y.tab.c"
    break;

  case 93: /* expression: expression ">=" expression  */
#line 525 "gpl.y"
    {
        (yyval.union_expression) = ((yyvsp[-2].union_expression) && (yyvsp[0].union_expression)) ? new Expression(GREATER_EQUAL, (yyvsp[-2].union_expression), (yyvsp[0].union_expression)) : new Expression(0);
    }
#line 2133 "y.tab.c"
    break;

  case 94: /* expression: expression "<" expression  */
#line 529 "gpl.y"
    {
        (yyval.union_expression) = ((yyvsp[-2].union_expression) && (yyvsp[0].union_expression)) ? new Expression(LESS_THAN, (yyvsp[-2].union_expression), (yyvsp[0].union_expression)) : new Expression(0);
    }
#line 2141 "y.tab.c"
    break;

  case 95: /* expression: expression ">" expression  */
#line 533 "gpl.y"
    {
        (yyval.union_expression) = ((yyvsp[-2].union_expression) && (yyvsp[0].union_expression)) ? new Expression(GREATER_THAN, (yyvsp[-2].union_expression), (yyvsp[0].union_expression)) : new Expression(0);
    }
#line 2149 "y.tab.c"
    break;

  case 96: /* expression: expression "==" expression  */
#line 537 "gpl.y"
    {
        (yyval.union_expression) = ((yyvsp[-2].union_expression) && (yyvsp[0].union_expression)) ? new Expression(EQUAL, (yyvsp[-2].union_expression), (yyvsp[0].union_expression)) : new Expression(0);
    }
#line 2157 "y.tab.c"
    break;

  case 97: /* expression: expression "!=" expression  */
#line 541 "gpl.y"
    {
        (yyval.union_expression) = ((yyvsp[-2].union_expression) && (yyvsp[0].union_expression)) ? new Expression(NOT_EQUAL, (yyvsp[-2].union_expression), (yyvsp[0].union_expression)) : new Expression(0);
    }
#line 2165 "y.tab.c"
    break;

  case 98: /* expression: expression "+" expression  */
#line 545 "gpl.y"
    {
        if (!(yyvsp[-2].union_expression) || !(yyvsp[0].union_expression)) {
            (yyval.union_expression) = new Expression(0);
        } else if ((yyvsp[-2].union_expression)->get_type() == STRING || (yyvsp[0].union_expression)->get_type() == STRING) {
            std::string* combined_string = new std::string((yyvsp[-2].union_expression)->eval_string() + (yyvsp[0].union_expression)->eval_string());
            (yyval.union_expression) = new Expression(combined_string);
        } else {
            (yyval.union_expression) = new Expression(PLUS, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
        }
    }
#line 2180 "y.tab.c"
    break;

  case 99: /* expression: expression "-" expression  */
#line 556 "gpl.y"
    {
        bool valid_left = ((yyvsp[-2].union_expression) && (yyvsp[-2].union_expression)->get_type() != STRING);
        bool valid_right = ((yyvsp[0].union_expression) && (yyvsp[0].union_expression)->get_type() != STRING);

        if (!valid_left) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "-", gpl_type_to_string((yyvsp[-2].union_expression)->get_type()));
        }
        if (!valid_right) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
        }

        (yyval.union_expression) = (valid_left && valid_right) ? new Expression(MINUS, (yyvsp[-2].union_expression), (yyvsp[0].union_expression)) : new Expression(0);
    }
#line 2198 "y.tab.c"
    break;

  case 100: /* expression: expression "*" expression  */
#line 570 "gpl.y"
    {
        bool valid_left = ((yyvsp[-2].union_expression) && (yyvsp[-2].union_expression)->get_type() != STRING);
        bool valid_right = ((yyvsp[0].union_expression) && (yyvsp[0].union_expression)->get_type() != STRING);

        if (!valid_left) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "*", gpl_type_to_string((yyvsp[-2].union_expression)->get_type()));
        }
        if (!valid_right) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "*", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
        }

        (yyval.union_expression) = (valid_left && valid_right) ? new Expression(MULTIPLY, (yyvsp[-2].union_expression), (yyvsp[0].union_expression)) : new Expression(0);
    }
#line 2216 "y.tab.c"
    break;

  case 101: /* expression: expression "/" expression  */
#line 584 "gpl.y"
    {
        bool valid_left = ((yyvsp[-2].union_expression) && (yyvsp[-2].union_expression)->get_type() != STRING);
        bool valid_right = ((yyvsp[0].union_expression) && (yyvsp[0].union_expression)->get_type() != STRING);

        if (!valid_left) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "/", gpl_type_to_string((yyvsp[-2].union_expression)->get_type()));
        }
        if (!valid_right) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "/", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
        }

        (yyval.union_expression) = (valid_left && valid_right) ? new Expression(DIVIDE, (yyvsp[-2].union_expression), (yyvsp[0].union_expression)) : new Expression(0);
    }
#line 2234 "y.tab.c"
    break;

  case 102: /* expression: expression "%" expression  */
#line 598 "gpl.y"
    {
        bool valid_left = ((yyvsp[-2].union_expression) && (yyvsp[-2].union_expression)->get_type() == INT);
        bool valid_right = ((yyvsp[0].union_expression) && (yyvsp[0].union_expression)->get_type() == INT);

        if (!valid_left) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "%", gpl_type_to_string((yyvsp[-2].union_expression)->get_type()));
        }
        if (!valid_right) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "%", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
        }

        (yyval.union_expression) = (valid_left && valid_right) ? new Expression(MOD, (yyvsp[-2].union_expression), (yyvsp[0].union_expression)) : new Expression(0);
    }
#line 2252 "y.tab.c"
    break;

  case 103: /* expression: "-" expression  */
#line 612 "gpl.y"
    {
        if (!(yyvsp[0].union_expression)) {
            (yyval.union_expression) = new Expression(0);
        } else if ((yyvsp[0].union_expression)->get_type() == STRING) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
            (yyval.union_expression) = new Expression(0);
        } else {
            (yyval.union_expression) = new Expression(UNARY_MINUS, (yyvsp[0].union_expression));
        }
    }
#line 2267 "y.tab.c"
    break;

  case 104: /* expression: "!" expression  */
#line 623 "gpl.y"
    {
        if (!(yyvsp[0].union_expression)) {
            (yyval.union_expression) = new Expression(0);
        } else if ((yyvsp[0].union_expression)->get_type() == STRING) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "!", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
            (yyval.union_expression) = new Expression(0);
        } else {
            (yyval.union_expression) = new Expression(NOT, (yyvsp[0].union_expression));
        }
    }
#line 2282 "y.tab.c"
    break;

  case 105: /* expression: math_operator "(" expression ")"  */
#line 634 "gpl.y"
    {
        if (!(yyvsp[-1].union_expression)) {
            (yyval.union_expression) = new Expression(0);
        } else if ((yyvsp[-1].union_expression)->get_type() == STRING) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string(static_cast<Operator_type>((yyvsp[-3].gpl_type))), gpl_type_to_string((yyvsp[-1].union_expression)->get_type()));
            (yyval.union_expression) = new Expression(0);
        } else {
            (yyval.union_expression) = new Expression(static_cast<Operator_type>((yyvsp[-3].gpl_type)), (yyvsp[-1].union_expression));
        }
    }
#line 2297 "y.tab.c"
    break;

  case 106: /* primary_expression: "(" expression ")"  */
#line 649 "gpl.y"
    {
        (yyval.union_expression) = (yyvsp[-1].union_expression);
    }
#line 2305 "y.tab.c"
    break;

  case 107: /* primary_expression: variable  */
#line 653 "gpl.y"
    {
        (yyval.union_expression) = new Expression((yyvsp[0].union_variable));
    }
#line 2313 "y.tab.c"
    break;

  case 108: /* primary_expression: "int constant"  */
#line 657 "gpl.y"
    {
        (yyval.union_expression) = new Expression((yyvsp[0].union_int));
    }
#line 2321 "y.tab.c"
    break;

  case 109: /* primary_expression: "double constant"  */
#line 661 "gpl.y"
    {
        (yyval.union_expression) = new Expression((yyvsp[0].union_double));
    }
#line 2329 "y.tab.c"
    break;

  case 110: /* primary_expression: "string constant"  */
#line 665 "gpl.y"
    {
        (yyval.union_expression) = new Expression((yyvsp[0].union_string));
    }
#line 2337 "y.tab.c"
    break;

  case 111: /* math_operator: "*"  */
#line 672 "gpl.y"
               { (yyval.gpl_type) = MULTIPLY; }
#line 2343 "y.tab.c"
    break;

  case 112: /* math_operator: "/"  */
#line 673 "gpl.y"
               { (yyval.gpl_type) = DIVIDE; }
#line 2349 "y.tab.c"
    break;

  case 113: /* math_operator: "+"  */
#line 674 "gpl.y"
             { (yyval.gpl_type) = PLUS; }
#line 2355 "y.tab.c"
    break;

  case 114: /* math_operator: "-"  */
#line 675 "gpl.y"
              { (yyval.gpl_type) = MINUS; }
#line 2361 "y.tab.c"
    break;

  case 115: /* math_operator: "%"  */
#line 676 "gpl.y"
            { (yyval.gpl_type) = MOD; }
#line 2367 "y.tab.c"
    break;

  case 116: /* math_operator: "sin"  */
#line 677 "gpl.y"
            { (yyval.gpl_type) = SIN; }
#line 2373 "y.tab.c"
    break;

  case 117: /* math_operator: "cos"  */
#line 678 "gpl.y"
            { (yyval.gpl_type) = COS; }
#line 2379 "y.tab.c"
    break;

  case 118: /* math_operator: "tan"  */
#line 679 "gpl.y"
            { (yyval.gpl_type) = TAN; }
#line 2385 "y.tab.c"
    break;

  case 119: /* math_operator: "asin"  */
#line 680 "gpl.y"
             { (yyval.gpl_type) = ASIN; }
#line 2391 "y.tab.c"
    break;

  case 120: /* math_operator: "acos"  */
#line 681 "gpl.y"
             { (yyval.gpl_type) = ACOS; }
#line 2397 "y.tab.c"
    break;

  case 121: /* math_operator: "atan"  */
#line 682 "gpl.y"
             { (yyval.gpl_type) = ATAN; }
#line 2403 "y.tab.c"
    break;

  case 122: /* math_operator: "sqrt"  */
#line 683 "gpl.y"
             { (yyval.gpl_type) = SQRT; }
#line 2409 "y.tab.c"
    break;

  case 123: /* math_operator: "floor"  */
#line 684 "gpl.y"
              { (yyval.gpl_type) = FLOOR; }
#line 2415 "y.tab.c"
    break;

  case 124: /* math_operator: "abs"  */
#line 685 "gpl.y"
            { (yyval.gpl_type) = ABS; }
#line 2421 "y.tab.c"
    break;

  case 125: /* math_operator: "random"  */
#line 686 "gpl.y"
               { (yyval.gpl_type) = RANDOM; }
#line 2427 "y.tab.c"
    break;


#line 2431 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

