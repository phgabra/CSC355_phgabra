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
#include "expression.h"
#include "variable.h"
#include "game_object.h"
#include "animation_block.h"
#include "if_statement.h"
#include "for_statement.h"
#include "print_statement.h"
#include "exit_statement.h"
#include "assign_statement.h"
#include <iostream>
#include <sstream>
#include <cmath> // for floor()
#include <stack>
using namespace std;

extern int yylex();
extern int yyerror(const char *);
extern int line_count;  // from gpl.l, used for statement blocks

int undeclared = 0;
Symbol_table *sym_table = Symbol_table::instance();
// Global variable to make the construction of object much less complex
// Only one object can ever be under construction at one time
Game_object *cur_object_under_construction = 0;
string cur_object_under_construction_name;
std::stack<Statement_block*> statement_block_stack;



#line 111 "y.tab.c"

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
#line 41 "gpl.y"

  int                                   union_int;
  double                                union_double;
  std::string                           *union_string;  // MUST be a pointer to a string ARG!
  Expression                            *union_expression;
  Variable                              *union_variable;
  Symbol                                *symbol;
  Gpl_type                              gpl_type;
  int                                   simple_type;
  int                                   math_operator_type;
  Window::Keystroke                     keystroke;
  Statement_block                       *statement_block;

#line 364 "y.tab.c"

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
  YYSYMBOL_simple_type = 98,               /* simple_type  */
  YYSYMBOL_optional_initializer = 99,      /* optional_initializer  */
  YYSYMBOL_object_declaration = 100,       /* object_declaration  */
  YYSYMBOL_101_1 = 101,                    /* $@1  */
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
#define YYLAST   430

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  126
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  220

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
       0,   189,   189,   194,   195,   200,   275,   305,   306,   316,
     317,   318,   323,   327,   334,   333,   365,   433,   434,   435,
     436,   437,   442,   443,   448,   449,   454,   545,   565,   566,
     571,   572,   573,   574,   579,   584,   592,   597,   619,   624,
     632,   636,   640,   644,   648,   652,   656,   660,   664,   668,
     672,   676,   680,   684,   688,   692,   696,   700,   704,   708,
     712,   716,   720,   724,   732,   736,   744,   752,   761,   769,
     770,   775,   776,   777,   778,   779,   784,   794,   802,   814,
     832,   840,   841,   846,   921,   953,   983,   998,  1017,  1033,
    1060,  1091,  1120,  1124,  1138,  1152,  1158,  1164,  1170,  1176,
    1182,  1188,  1199,  1213,  1227,  1241,  1255,  1266,  1277,  1294,
    1298,  1302,  1306,  1310,  1314,  1318,  1326,  1327,  1328,  1329,
    1330,  1331,  1332,  1333,  1334,  1335,  1339
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
  "simple_type", "optional_initializer", "object_declaration", "$@1",
  "object_type", "parameter_list_or_empty", "parameter_list", "parameter",
  "forward_declaration", "block_list", "block", "initialization_block",
  "termination_block", "animation_block", "animation_parameter",
  "check_animation_parameter", "on_block", "keystroke", "if_block",
  "statement_block", "statement_block_creator", "end_of_statement_block",
  "statement_list", "statement", "if_statement", "for_statement",
  "print_statement", "exit_statement", "assign_statement_or_empty",
  "assign_statement", "variable", "expression", "primary_expression",
  "math_operator", "empty", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-172)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -172,    27,    59,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,   -11,   -21,   -51,  -172,   -50,  -172,    13,
    -172,   -48,  -172,   -23,   -12,    -4,    -4,   367,   -39,  -172,
    -172,  -172,  -172,  -172,     1,    96,    96,  -172,  -172,    96,
       2,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,    -4,     4,
      92,  -172,  -172,    96,    96,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,    96,   -29,  -172,  -172,  -172,
    -172,   221,  -172,    11,   345,   244,   -16,  -172,  -172,    92,
     -15,    23,   126,  -172,  -172,    96,     5,  -172,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,  -172,    17,    26,    37,  -172,  -172,   -38,  -172,
       7,    45,  -172,  -172,  -172,   267,  -172,  -172,  -172,  -172,
      -6,    -6,    40,    40,    40,    40,    58,    58,    49,   276,
     153,    96,  -172,   -16,    60,    68,    70,    77,  -172,  -172,
    -172,  -172,    79,    80,    85,    94,  -172,    91,    89,  -172,
     345,  -172,    96,  -172,    96,    96,  -172,  -172,  -172,  -172,
      96,    96,    96,  -172,  -172,  -172,    61,   162,    71,   189,
     198,   345,   345,   345,   -32,  -172,    -4,  -172,  -172,  -172,
    -172,  -172,  -172,   101,  -172,   -26,   102,  -172,    -4,  -172,
      96,  -172,  -172,   298,  -172,    71,  -172,   109,    -4,  -172
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
     126,     0,   126,     4,     1,     9,    10,    11,    17,    18,
      19,    20,    21,     0,     0,     0,     7,     0,     8,     2,
      29,     0,     3,   126,    14,     0,     0,     0,     0,    28,
      30,    31,    32,    33,     0,     0,     0,     5,    13,     0,
       0,    67,    34,    35,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,     0,     0,
       0,   112,   113,     0,     0,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,     0,    88,   111,   114,   115,
     110,     0,    92,     0,    12,     0,   126,   126,    39,     0,
       0,     0,     0,   106,   107,     0,     0,     6,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    16,     0,     0,    22,    25,    23,     0,    70,
       0,     0,    37,    27,   109,     0,    90,   103,   104,   105,
     101,   102,    97,    98,    95,    96,    99,   100,    94,    93,
       0,     0,    15,     0,     0,     0,     0,     0,    68,    69,
      71,    72,     0,     0,     0,     0,    38,     0,    89,   108,
      26,    24,     0,    67,     0,     0,    66,    74,    75,    73,
       0,     0,     0,    86,    87,   126,     0,     0,   126,     0,
       0,    83,    84,    85,     0,    91,    67,    68,    81,    82,
      79,    80,    68,    76,    65,     0,     0,    36,    67,    68,
       0,    77,    64,     0,    67,   126,    68,     0,     0,    78
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,   -59,  -172,
    -172,     8,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,   -46,   -22,   -40,  -164,   -25,   -30,  -172,  -172,
    -172,  -172,   -37,  -171,   -97,   -31,  -172,  -172,     0
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    14,    15,    37,    16,    40,    17,   124,
     125,   126,    18,    19,    29,    30,    31,    32,   101,   131,
      33,    68,   203,   204,   205,   176,   128,   159,   160,   161,
     162,   163,   197,   164,    90,    91,    92,    93,   129
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       3,    97,    20,    42,    43,    94,   154,   155,    95,   156,
     157,   100,   154,   155,   158,   156,   157,   198,   154,   155,
     202,   156,   157,    38,   105,    25,    26,     4,   106,    27,
      35,   165,    21,   206,    22,    36,    23,    24,   207,    34,
     130,    39,   102,   103,   198,   212,    98,    41,    69,    86,
      70,    96,   217,    99,   104,    86,    28,   108,   109,   110,
     121,    86,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   123,   132,   133,   135,   151,   152,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   165,   136,   153,   166,   167,   127,   165,     8,     9,
      10,    11,    12,   108,   109,   110,   111,   112,   165,   172,
      71,    72,   108,   109,   110,   111,   112,   173,   165,   174,
     170,   108,   109,   110,   111,   112,   175,   113,   114,   115,
     116,   117,   118,   188,   177,   178,   113,   114,   115,   116,
     179,   187,   185,   189,   190,    73,   186,   208,   195,   191,
     192,   193,   180,   181,   182,   183,   184,   210,    86,   218,
     194,   171,   211,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,   215,   209,   134,     0,   216,   213,
       0,     0,    85,    86,    87,    88,    89,     0,   199,   108,
     109,   110,   111,   112,     0,     0,   219,     0,     0,     0,
       0,     0,     0,   169,   113,   114,   115,   116,   117,   118,
     119,   120,   196,     0,     0,   199,   108,   109,   110,   111,
     112,     0,     0,     0,     0,   108,   109,   110,   111,   112,
       0,   113,   114,   115,   116,   117,   118,   119,   120,   200,
     113,   114,   115,   116,   117,   118,   119,   120,   201,     0,
       0,     0,   108,   109,   110,   111,   112,     0,     0,     0,
       0,   108,   109,   110,   111,   112,     0,   113,   114,   115,
     116,   117,   118,   119,   120,   107,   113,   114,   115,   116,
     117,   118,   119,   120,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   122,   113,
     114,   115,   116,   117,   118,   119,   120,   108,   109,   110,
     111,   112,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   168,   113,   114,   115,   116,   117,   118,   119,   120,
     108,   109,   110,   111,   112,     0,     0,     0,     0,   108,
     109,   110,   111,   112,     0,   113,   114,   115,   116,   117,
     118,   119,   120,   214,   113,   114,   115,   116,   117,   118,
     119,   108,   109,   110,   111,   112,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,   108,   109,
     110,   111,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,   114,   115,   116,   117,   118,   119,
     120
};

static const yytype_int16 yycheck[] =
{
       0,    41,     2,    25,    26,    36,    44,    45,    39,    47,
      48,    70,    44,    45,    52,    47,    48,   188,    44,    45,
      52,    47,    48,    23,    53,    12,    13,     0,    57,    16,
      53,   128,    43,   197,    55,    58,    87,    87,   202,    87,
      99,    53,    73,    74,   215,   209,    68,    51,    87,    87,
      49,    49,   216,    49,    85,    87,    43,    63,    64,    65,
      49,    87,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    87,    87,    50,   105,    58,    50,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   188,    87,    56,    87,    50,    96,   194,     6,     7,
       8,     9,    10,    63,    64,    65,    66,    67,   205,    49,
      14,    15,    63,    64,    65,    66,    67,    49,   215,    49,
     151,    63,    64,    65,    66,    67,    49,    78,    79,    80,
      81,    82,    83,   173,    55,    55,    78,    79,    80,    81,
      55,   172,    51,   174,   175,    49,    57,    46,    87,   180,
     181,   182,    58,    59,    60,    61,    62,    55,    87,    50,
     185,   153,   208,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,   214,   205,    50,    -1,   215,   210,
      -1,    -1,    86,    87,    88,    89,    90,    -1,   188,    63,
      64,    65,    66,    67,    -1,    -1,   218,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    78,    79,    80,    81,    82,    83,
      84,    85,    50,    -1,    -1,   215,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,
      -1,    78,    79,    80,    81,    82,    83,    84,    85,    50,
      78,    79,    80,    81,    82,    83,    84,    85,    50,    -1,
      -1,    -1,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    -1,    78,    79,    80,
      81,    82,    83,    84,    85,    54,    78,    79,    80,    81,
      82,    83,    84,    85,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    78,
      79,    80,    81,    82,    83,    84,    85,    63,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    78,    79,    80,    81,    82,    83,    84,    85,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    67,    -1,    78,    79,    80,    81,    82,
      83,    84,    85,    55,    78,    79,    80,    81,    82,    83,
      84,    63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,
      82,    83,    84,    85,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    79,    80,    81,    82,    83,    84,
      85
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    95,    96,   132,     0,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    97,    98,   100,   102,   106,   107,
     132,    43,    55,    87,    87,    12,    13,    16,    43,   108,
     109,   110,   111,   114,    87,    53,    58,    99,   132,    53,
     101,    51,   117,   117,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,   115,    87,
      49,    14,    15,    49,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    86,    87,    88,    89,    90,
     128,   129,   130,   131,   129,   129,    49,   118,   117,    49,
     102,   112,   129,   129,   129,    53,    57,    54,    63,    64,
      65,    66,    67,    78,    79,    80,    81,    82,    83,    84,
      85,    49,    54,    87,   103,   104,   105,   132,   120,   132,
     102,   113,    87,    50,    50,   129,    87,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,    58,    50,    56,    44,    45,    47,    48,    52,   121,
     122,   123,   124,   125,   127,   128,    87,    50,    54,    50,
     129,   105,    49,    49,    49,    49,   119,    55,    55,    55,
      58,    59,    60,    61,    62,    51,    57,   129,   118,   129,
     129,   129,   129,   129,   120,    87,    50,   126,   127,   132,
      50,    50,    52,   116,   117,   118,   119,   119,    46,   121,
      55,   116,   119,   129,    55,   118,   126,   119,    50,   117
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    96,    96,    97,    97,    97,    97,    98,
      98,    98,    99,    99,   101,   100,   100,   102,   102,   102,
     102,   102,   103,   103,   104,   104,   105,   106,   107,   107,
     108,   108,   108,   108,   109,   110,   111,   112,   113,   114,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   116,   116,   117,   118,   119,   120,
     120,   121,   121,   121,   121,   121,   122,   122,   123,   124,
     125,   126,   126,   127,   127,   127,   127,   127,   128,   128,
     128,   128,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   130,
     130,   130,   130,   130,   130,   130,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   132
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     3,     1,     3,     5,     1,     1,     1,
       1,     1,     2,     1,     0,     6,     5,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     3,     6,     2,     1,
       1,     1,     1,     1,     2,     2,     9,     2,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     5,     0,     0,     2,
       1,     1,     1,     2,     2,     2,     5,     7,    13,     4,
       4,     1,     1,     3,     3,     3,     2,     2,     1,     4,
       3,     6,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     4,     3,
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
  case 5: /* declaration: simple_type "identifier" optional_initializer  */
#line 201 "gpl.y"
    {
        std::string var_name = *(yyvsp[-1].union_string);
        delete (yyvsp[-1].union_string);

        Symbol *new_symbol = nullptr;

        // Create a default symbol based on the declared type
        if ((yyvsp[-2].simple_type) == T_INT) {
            new_symbol = new Symbol(var_name, 0);
        } else if ((yyvsp[-2].simple_type) == T_DOUBLE) {
            new_symbol = new Symbol(var_name, 0.0);
        } else if ((yyvsp[-2].simple_type) == T_STRING) {
            new_symbol = new Symbol(var_name, "");
        } else if ((yyvsp[-2].simple_type) == ANIMATION_BLOCK) {
            new_symbol = new Symbol(var_name, nullptr); // Default animation_block value
        }

        // Attempt to insert the symbol into the symbol table
        if (!Symbol_table::instance()->insert(new_symbol)) {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, var_name);
            delete new_symbol;
        } else if ((yyvsp[0].union_expression)) {
            Gpl_type initializer_type = (yyvsp[0].union_expression)->get_type();

            // Handle animation_block assignments
            if (initializer_type == ANIMATION_BLOCK && (yyvsp[-2].simple_type) != ANIMATION_BLOCK) {
                if ((yyvsp[-2].simple_type) == T_INT) {
                    Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,
                                gpl_type_to_string(initializer_type),
                                var_name,
                                "int");
                } else if ((yyvsp[-2].simple_type) == T_DOUBLE) {
                    Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,
                                gpl_type_to_string(initializer_type),
                                var_name,
                                "double");
                } else if ((yyvsp[-2].simple_type) == T_STRING) {
                    Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,
                                gpl_type_to_string(initializer_type),
                                var_name,
                                "string");
                }

            }
            // Handle other type mismatches
            else if ((yyvsp[-2].simple_type) == T_INT && initializer_type != INT) {
                // Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,
                //              gpl_type_to_string(initializer_type),
                //              var_name,
                //              "int");
            } else if ((yyvsp[-2].simple_type) == T_DOUBLE && initializer_type != DOUBLE && initializer_type != INT) {
                // Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,
                //              gpl_type_to_string(initializer_type),
                //              var_name,
                //              "double");
            } else if ((yyvsp[-2].simple_type) == T_STRING && initializer_type != STRING) {
                // Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE,
                //              gpl_type_to_string(initializer_type),
                //              var_name,
                //              "string");
            } else {
                // Valid initialization: set the symbol's value
                if ((yyvsp[-2].simple_type) == T_INT) {
                    new_symbol->set_value((yyvsp[0].union_expression)->eval_int());
                } else if ((yyvsp[-2].simple_type) == T_DOUBLE) {
                    new_symbol->set_value((yyvsp[0].union_expression)->eval_double());
                } else if ((yyvsp[-2].simple_type) == T_STRING) {
                    new_symbol->set_value((yyvsp[0].union_expression)->eval_string());
                }
            }

            delete (yyvsp[0].union_expression); // Clean up
        }
    }
#line 2031 "y.tab.c"
    break;

  case 6: /* declaration: simple_type "identifier" "[" expression "]"  */
#line 276 "gpl.y"
    {
        std::string array_name = *(yyvsp[-3].union_string);
        Gpl_type expr_type = (yyvsp[-1].union_expression)->get_type();

        // Check if the size expression is valid
        if (expr_type != INT) {
            Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER, gpl_type_to_string(expr_type), array_name);
            delete (yyvsp[-3].union_string);
            delete (yyvsp[-1].union_expression);
        } else {
            int array_size = (yyvsp[-1].union_expression)->eval_int();
            delete (yyvsp[-3].union_string);
            delete (yyvsp[-1].union_expression);

            if (array_size < 1) {
                Error::error(Error::INVALID_ARRAY_SIZE, array_name, std::to_string(array_size));
            } else {
                Symbol *new_symbol = ((yyvsp[-4].simple_type) == T_INT) ? new Symbol(array_name, INT_ARRAY, array_size)
                                  : ((yyvsp[-4].simple_type) == T_DOUBLE) ? new Symbol(array_name, DOUBLE_ARRAY, array_size)
                                  : new Symbol(array_name, STRING_ARRAY, array_size);

                // Insert the array symbol into the symbol table
                if (!sym_table->insert(new_symbol)) {
                    Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, array_name);
                    delete new_symbol;
                }
            }
        }
    }
#line 2065 "y.tab.c"
    break;

  case 9: /* simple_type: "int"  */
#line 316 "gpl.y"
          { (yyval.simple_type) = T_INT; }
#line 2071 "y.tab.c"
    break;

  case 10: /* simple_type: "double"  */
#line 317 "gpl.y"
               { (yyval.simple_type) = T_DOUBLE; }
#line 2077 "y.tab.c"
    break;

  case 11: /* simple_type: "string"  */
#line 318 "gpl.y"
               { (yyval.simple_type) = T_STRING; }
#line 2083 "y.tab.c"
    break;

  case 12: /* optional_initializer: "=" expression  */
#line 324 "gpl.y"
    {
        (yyval.union_expression) = (yyvsp[0].union_expression);
    }
#line 2091 "y.tab.c"
    break;

  case 13: /* optional_initializer: empty  */
#line 328 "gpl.y"
    {
        (yyval.union_expression) = nullptr;
    }
#line 2099 "y.tab.c"
    break;

  case 14: /* $@1: %empty  */
#line 334 "gpl.y"
    {
        // Always create the object, even if it won't be inserted into the symbol table
        Symbol *symbol = new Symbol(*(yyvsp[0].union_string), (yyvsp[-1].gpl_type));

        // Check if the variable is already declared
        if (Symbol_table::instance()->lookup(*(yyvsp[0].union_string))) {
            // Emit error for previously declared variable
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *(yyvsp[0].union_string));

            // Allow parameter parsing for the created object, but it won't be added to the symbol table
            cur_object_under_construction = symbol->get_game_object_value();
            cur_object_under_construction_name = symbol->get_name();
        } else {
            // Attempt to insert the symbol into the symbol table
            if (!sym_table->insert(symbol)) {
                // Fallback error handling (shouldn't reach here)
                Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *(yyvsp[0].union_string));
                delete symbol;
            } else {
                // Prepare for parameter parsing
                cur_object_under_construction = symbol->get_game_object_value();
                cur_object_under_construction_name = symbol->get_name();
            }
        }
    }
#line 2129 "y.tab.c"
    break;

  case 15: /* object_declaration: object_type "identifier" $@1 "(" parameter_list_or_empty ")"  */
#line 360 "gpl.y"
    {
        // Reset the global construction variables after parameter parsing
        cur_object_under_construction = nullptr;
        delete (yyvsp[-4].union_string); // Free memory allocated for T_ID
    }
#line 2139 "y.tab.c"
    break;

  case 16: /* object_declaration: object_type "identifier" "[" expression "]"  */
#line 366 "gpl.y"
    {
        // Check if the variable is already declared
        if (Symbol_table::instance()->lookup(*(yyvsp[-3].union_string))) {
            // Emit error for previously declared variable
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *(yyvsp[-3].union_string));

            delete (yyvsp[-1].union_expression);

            // Skip further processing
            cur_object_under_construction = nullptr;
        } else {
            // Check the type of the size expression
            Gpl_type expr_type = (yyvsp[-1].union_expression)->get_type();

            if (expr_type != INT) {
                // Report an error for non-integer array size
                Error::error(Error::ARRAY_SIZE_MUST_BE_AN_INTEGER,
                             gpl_type_to_string(expr_type),
                             *(yyvsp[-3].union_string));

                // Free memory for T_ID and the expression
                delete (yyvsp[-3].union_string);
                delete (yyvsp[-1].union_expression);

                // Skip further processing
                cur_object_under_construction = nullptr;
            } else {
                // Evaluate the size expression
                int size = (yyvsp[-1].union_expression)->eval_int();
                delete (yyvsp[-1].union_expression); // Free memory allocated for the expression

                if (size <= 0) {
                    // Report an error for invalid array size
                    Error::error(Error::INVALID_ARRAY_SIZE, *(yyvsp[-3].union_string), std::to_string(size));
                } else {
                    // Map object type to array type
                    Gpl_type array_type;
                    if ((yyvsp[-4].gpl_type) == CIRCLE)
                        array_type = CIRCLE_ARRAY;
                    else if ((yyvsp[-4].gpl_type) == RECTANGLE)
                        array_type = RECTANGLE_ARRAY;
                    else if ((yyvsp[-4].gpl_type) == TRIANGLE)
                        array_type = TRIANGLE_ARRAY;
                    else if ((yyvsp[-4].gpl_type) == TEXTBOX)
                        array_type = TEXTBOX_ARRAY;
                    else if ((yyvsp[-4].gpl_type) == PIXMAP)
                        array_type = PIXMAP_ARRAY;
                    else {
                        Error::error(Error::ASSIGNMENT_TYPE_ERROR, *(yyvsp[-3].union_string));
                    }

                    // Create the array symbol
                    Symbol *symbol = new Symbol(*(yyvsp[-3].union_string), array_type, size);

                    if (!sym_table->insert(symbol)) {
                        Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *(yyvsp[-3].union_string));
                        delete symbol;
                    }
                }
                delete (yyvsp[-3].union_string); // Free memory allocated for T_ID
            }
        }
    }
#line 2207 "y.tab.c"
    break;

  case 17: /* object_type: "triangle"  */
#line 433 "gpl.y"
               { (yyval.gpl_type) = TRIANGLE; }
#line 2213 "y.tab.c"
    break;

  case 18: /* object_type: "pixmap"  */
#line 434 "gpl.y"
               { (yyval.gpl_type) = PIXMAP; }
#line 2219 "y.tab.c"
    break;

  case 19: /* object_type: "circle"  */
#line 435 "gpl.y"
               { (yyval.gpl_type) = CIRCLE; }
#line 2225 "y.tab.c"
    break;

  case 20: /* object_type: "rectangle"  */
#line 436 "gpl.y"
                  { (yyval.gpl_type) = RECTANGLE; }
#line 2231 "y.tab.c"
    break;

  case 21: /* object_type: "textbox"  */
#line 437 "gpl.y"
                { (yyval.gpl_type) = TEXTBOX; }
#line 2237 "y.tab.c"
    break;

  case 26: /* parameter: "identifier" "=" expression  */
#line 455 "gpl.y"
    {
        std::string parameter = *(yyvsp[-2].union_string);
        delete (yyvsp[-2].union_string); // Free memory allocated for T_ID

        Expression *value_expression = (yyvsp[0].union_expression);
        Gpl_type value_expression_type = value_expression->get_type();

        // Ensure `cur_object_under_construction` is valid
        if (!cur_object_under_construction) {
            delete value_expression;
            return 0;
        }

        // Get the type of the parameter in the game object
        Status status;
        Gpl_type parameter_type;
        status = cur_object_under_construction->get_member_variable_type(parameter, parameter_type);

        if (status == OK)
        {
            // Handle assignment of an ANIMATION_BLOCK
            if (parameter_type == ANIMATION_BLOCK)
            {
                if (value_expression_type != ANIMATION_BLOCK) {
                    // The provided value is not an animation block
                    Error::error(Error::INVALID_RIGHT_OPERAND_TYPE,
                                 parameter,
                                 gpl_type_to_string(value_expression_type));
                } else {
                    // Verify type compatibility between object and animation block
                    Animation_block *block = value_expression->eval_animation_block();
                    Symbol *parameter_symbol = block->get_parameter_symbol();
                    if (parameter_symbol->get_type() != cur_object_under_construction->get_type()) {
                        // Type mismatch
                        Error::error(Error::TYPE_MISMATCH_BETWEEN_ANIMATION_BLOCK_AND_OBJECT,
                                     cur_object_under_construction_name,
                                     block->name());
                    } else {
                        // Valid assignment
                        cur_object_under_construction->set_member_variable(parameter, block);
                    }
                }
            }
            // Handle implicit conversion for DOUBLE <- INT
            else if (parameter_type == DOUBLE && value_expression_type == INT)
            {
                double converted_value = value_expression->eval_int() * 1.0;
                cur_object_under_construction->set_member_variable(parameter, converted_value);
            }
            // Handle implicit conversion for STRING <- INT or STRING <- DOUBLE
            else if (parameter_type == STRING &&
                     (value_expression_type == INT || value_expression_type == DOUBLE))
            {
                std::string converted_value = value_expression->eval_string();
                cur_object_under_construction->set_member_variable(parameter, converted_value);
            }
            // Handle mismatched types
            else if (parameter_type != value_expression_type)
            {
                Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE,
                             cur_object_under_construction_name,
                             parameter,
                             gpl_type_to_string(parameter_type));
            }
            else
            {
                // Set the parameter value based on its type
                if (parameter_type == INT)
                    cur_object_under_construction->set_member_variable(parameter, value_expression->eval_int());
                else if (parameter_type == DOUBLE)
                    cur_object_under_construction->set_member_variable(parameter, value_expression->eval_double());
                else if (parameter_type == STRING)
                    cur_object_under_construction->set_member_variable(parameter, value_expression->eval_string());
            }
        }
        else
        {
            // Handle unknown parameters
            std::string base_type_name = gpl_type_to_string(cur_object_under_construction->get_type());
            Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER,
                         base_type_name,
                         parameter);
        }

        delete value_expression; // Free memory allocated for the expression
    }
#line 2328 "y.tab.c"
    break;

  case 27: /* forward_declaration: "forward" "animation" "identifier" "(" animation_parameter ")"  */
#line 546 "gpl.y"
    {
        // Create a new Animation_block
        Symbol *animation_symbol = new Symbol(*(yyvsp[-3].union_string), ANIMATION_BLOCK);
        if (!sym_table->insert(animation_symbol))
        {
            Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, *(yyvsp[-3].union_string));
        }

        // Retrieve the Animation_block and initialize it with the parameter
        Animation_block *animation_block = animation_symbol->get_animation_block_value();
        assert(animation_block != nullptr); // Ensure animation_block is valid
        animation_block->initialize((yyvsp[-1].symbol), *(yyvsp[-3].union_string)); // Initialize with parameter symbol and name

        delete (yyvsp[-3].union_string); // Clean up
    }
#line 2348 "y.tab.c"
    break;

  case 35: /* termination_block: "termination" statement_block  */
#line 585 "gpl.y"
  {
      // COMPLETE ME
  }
#line 2356 "y.tab.c"
    break;

  case 37: /* animation_parameter: object_type "identifier"  */
#line 598 "gpl.y"
    {
        // Create a new Game_object parameter
        Symbol *parameter_symbol = new Symbol(*(yyvsp[0].union_string), (yyvsp[-1].gpl_type));
        if (!sym_table->insert(parameter_symbol))
        {
            Error::error(Error::ANIMATION_PARAMETER_NAME_NOT_UNIQUE, *(yyvsp[0].union_string));
        }
        else
        {
            // Mark the object as a parameter (never animate or draw)
            parameter_symbol->get_game_object_value()->never_animate();
            parameter_symbol->get_game_object_value()->never_draw();
        }

        (yyval.symbol) = parameter_symbol; // Pass the Symbol pointer up the tree
        delete (yyvsp[0].union_string); // Clean up
    }
#line 2378 "y.tab.c"
    break;

  case 39: /* on_block: "on" keystroke statement_block  */
#line 625 "gpl.y"
  {
      // COMPLETE ME
  }
#line 2386 "y.tab.c"
    break;

  case 40: /* keystroke: "space"  */
#line 633 "gpl.y"
    {
      (yyval.keystroke) = Window::SPACE;
    }
#line 2394 "y.tab.c"
    break;

  case 41: /* keystroke: "leftarrow"  */
#line 637 "gpl.y"
    {
      (yyval.keystroke) = Window::LEFTARROW;
    }
#line 2402 "y.tab.c"
    break;

  case 42: /* keystroke: "rightarrow"  */
#line 641 "gpl.y"
    {
      (yyval.keystroke) = Window::RIGHTARROW;
    }
#line 2410 "y.tab.c"
    break;

  case 43: /* keystroke: "uparrow"  */
#line 645 "gpl.y"
    {
      (yyval.keystroke) = Window::UPARROW;
    }
#line 2418 "y.tab.c"
    break;

  case 44: /* keystroke: "downarrow"  */
#line 649 "gpl.y"
    {
      (yyval.keystroke) = Window::DOWNARROW;
    }
#line 2426 "y.tab.c"
    break;

  case 45: /* keystroke: "leftmouse_down"  */
#line 653 "gpl.y"
    {
      (yyval.keystroke) = Window::LEFTMOUSE_DOWN;
    }
#line 2434 "y.tab.c"
    break;

  case 46: /* keystroke: "middlemouse_down"  */
#line 657 "gpl.y"
    {
      (yyval.keystroke) = Window::MIDDLEMOUSE_DOWN;
    }
#line 2442 "y.tab.c"
    break;

  case 47: /* keystroke: "rightmouse_down"  */
#line 661 "gpl.y"
    {
      (yyval.keystroke) = Window::RIGHTMOUSE_DOWN;
    }
#line 2450 "y.tab.c"
    break;

  case 48: /* keystroke: "leftmouse_up"  */
#line 665 "gpl.y"
    {
      (yyval.keystroke) = Window::LEFTMOUSE_UP;
    }
#line 2458 "y.tab.c"
    break;

  case 49: /* keystroke: "middlemouse_up"  */
#line 669 "gpl.y"
    {
      (yyval.keystroke) = Window::MIDDLEMOUSE_UP;
    }
#line 2466 "y.tab.c"
    break;

  case 50: /* keystroke: "rightmouse_up"  */
#line 673 "gpl.y"
    {
      (yyval.keystroke) = Window::RIGHTMOUSE_UP;
    }
#line 2474 "y.tab.c"
    break;

  case 51: /* keystroke: "mouse_move"  */
#line 677 "gpl.y"
    {
      (yyval.keystroke) = Window::MOUSE_MOVE;
    }
#line 2482 "y.tab.c"
    break;

  case 52: /* keystroke: "mouse_drag"  */
#line 681 "gpl.y"
    {
      (yyval.keystroke) = Window::MOUSE_DRAG;
    }
#line 2490 "y.tab.c"
    break;

  case 53: /* keystroke: "f1"  */
#line 685 "gpl.y"
    {
      (yyval.keystroke) = Window::F1;
    }
#line 2498 "y.tab.c"
    break;

  case 54: /* keystroke: "akey"  */
#line 689 "gpl.y"
    {
      (yyval.keystroke) = Window::AKEY;
    }
#line 2506 "y.tab.c"
    break;

  case 55: /* keystroke: "skey"  */
#line 693 "gpl.y"
    {
      (yyval.keystroke) = Window::SKEY;
    }
#line 2514 "y.tab.c"
    break;

  case 56: /* keystroke: "dkey"  */
#line 697 "gpl.y"
    {
      (yyval.keystroke) = Window::DKEY;
    }
#line 2522 "y.tab.c"
    break;

  case 57: /* keystroke: "fkey"  */
#line 701 "gpl.y"
    {
      (yyval.keystroke) = Window::FKEY;
    }
#line 2530 "y.tab.c"
    break;

  case 58: /* keystroke: "hkey"  */
#line 705 "gpl.y"
    {
      (yyval.keystroke) = Window::HKEY;
    }
#line 2538 "y.tab.c"
    break;

  case 59: /* keystroke: "jkey"  */
#line 709 "gpl.y"
    {
      (yyval.keystroke) = Window::JKEY;
    }
#line 2546 "y.tab.c"
    break;

  case 60: /* keystroke: "kkey"  */
#line 713 "gpl.y"
    {
      (yyval.keystroke) = Window::KKEY;
    }
#line 2554 "y.tab.c"
    break;

  case 61: /* keystroke: "lkey"  */
#line 717 "gpl.y"
    {
      (yyval.keystroke) = Window::LKEY;
    }
#line 2562 "y.tab.c"
    break;

  case 62: /* keystroke: "wkey"  */
#line 721 "gpl.y"
    {
      (yyval.keystroke) = Window::WKEY;
    }
#line 2570 "y.tab.c"
    break;

  case 63: /* keystroke: "zkey"  */
#line 725 "gpl.y"
    {
      (yyval.keystroke) = Window::ZKEY;
    }
#line 2578 "y.tab.c"
    break;

  case 64: /* if_block: statement_block_creator statement end_of_statement_block  */
#line 733 "gpl.y"
  {
      (yyval.statement_block) = (yyvsp[-2].statement_block);
  }
#line 2586 "y.tab.c"
    break;

  case 65: /* if_block: statement_block  */
#line 737 "gpl.y"
  {
      (yyval.statement_block) = (yyvsp[0].statement_block);
  }
#line 2594 "y.tab.c"
    break;

  case 66: /* statement_block: "{" statement_block_creator statement_list "}" end_of_statement_block  */
#line 745 "gpl.y"
  {
      (yyval.statement_block) = (yyvsp[-3].statement_block);
  }
#line 2602 "y.tab.c"
    break;

  case 67: /* statement_block_creator: %empty  */
#line 752 "gpl.y"
  {
      Statement_block *new_block = new Statement_block();
      statement_block_stack.push(new_block);
      (yyval.statement_block) = new_block;
  }
#line 2612 "y.tab.c"
    break;

  case 68: /* end_of_statement_block: %empty  */
#line 761 "gpl.y"
  {
      assert(!statement_block_stack.empty());
      statement_block_stack.pop();
  }
#line 2621 "y.tab.c"
    break;

  case 76: /* if_statement: "if" "(" expression ")" if_block  */
#line 785 "gpl.y"
  {
      Expression *expr = (yyvsp[-2].union_expression);
      if (expr->get_type() != INT)
      {
        Error::error(Error::INVALID_TYPE_FOR_IF_STMT_EXPRESSION);
        expr = new Expression(0);
      }
      statement_block_stack.top()->insert(new If_statement(expr,(yyvsp[0].statement_block)));
  }
#line 2635 "y.tab.c"
    break;

  case 77: /* if_statement: "if" "(" expression ")" if_block "else" if_block  */
#line 795 "gpl.y"
  {
      // COMPLETE ME
  }
#line 2643 "y.tab.c"
    break;

  case 78: /* for_statement: "for" "(" statement_block_creator assign_statement_or_empty end_of_statement_block ";" expression ";" statement_block_creator assign_statement_or_empty end_of_statement_block ")" statement_block  */
#line 807 "gpl.y"
  {
      // COMPLETE ME
  }
#line 2651 "y.tab.c"
    break;

  case 79: /* print_statement: "print" "(" expression ")"  */
#line 815 "gpl.y"
  {
      Expression *expr = (yyvsp[-1].union_expression);
      if (expr->get_type() != INT
        && expr->get_type() != DOUBLE
        && expr->get_type() != STRING
       )
      {
        Error::error(Error::INVALID_TYPE_FOR_PRINT_STMT_EXPRESSION);
        // for error handling
        expr = new Expression(0);
      }
      statement_block_stack.top()->insert(new Print_statement(expr, (yyvsp[-3].union_int))); // $1 has line_number
  }
#line 2669 "y.tab.c"
    break;

  case 80: /* exit_statement: "exit" "(" expression ")"  */
#line 833 "gpl.y"
  {
      // COMPLETE ME
  }
#line 2677 "y.tab.c"
    break;

  case 83: /* assign_statement: variable "=" expression  */
#line 847 "gpl.y"
  {
      Variable *lhs = (yyvsp[-2].union_variable);
      Expression *rhs = (yyvsp[0].union_expression);
      Gpl_type lhs_type = lhs->get_type();
      Gpl_type rhs_type = rhs->get_type();

      // game_object is illegal on lhs of assignment
      if (lhs_type & GAME_OBJECT)
      {
        Error::error(Error::INVALID_LHS_OF_ASSIGNMENT,
              lhs->get_name(),
              gpl_type_to_string(lhs_type)
              );
      }

      // if variable is an INT, expression must be INT
      // if variable is a DOUBLE, expression must be INT or DOUBLE
      // if variable is a STRING, expression must be STRING,INT, or DOUBLE
      // if variable is a ANIMATION_BLOCK, expression ANIMATION_BLOCK
      else if ((lhs_type == INT && rhs_type != INT)
          ||(lhs_type==DOUBLE&&(rhs_type != INT && rhs_type!=DOUBLE))
          ||(lhs_type == STRING && rhs_type == ANIMATION_BLOCK)
          ||(lhs_type==ANIMATION_BLOCK&& rhs_type != ANIMATION_BLOCK)
          )
      {
        Error::error(Error::ASSIGNMENT_TYPE_ERROR,
                     gpl_type_to_string(lhs_type),
                     gpl_type_to_string(rhs_type)
                    );
      }
        else if (lhs_type==ANIMATION_BLOCK)
        {
          // since lhs is an ANIMATION_BLOCK, it SHOULD take one of these forms
          // circle.animation_block =
          // circles[index].animation_block =

          // this is ok
          //   my_rect.animation_block = bounce;
          // this is NOT ok
          //   bounce = move;
          // check to make sure it is not this illegal form
          if (lhs->is_non_member_animation_block())
          {
            Error::error(Error::CANNOT_ASSIGN_TO_NON_MEMBER_ANIMATION_BLOCK,
                         lhs->get_name()
                        );
          }
          else
          {
  
            // get the type of the Game_object on the LHS
            Gpl_type lhs_base_object_type = lhs->get_base_game_object_type();
  
            Gpl_type rhs_param_type = rhs->eval_animation_block()->get_parameter_symbol()->get_type();
  
            // Animation_block *block = rhs->eval_animation_block();
            // Symbol *sym = block->get_parameter_symbol();
  
            if (lhs_base_object_type != rhs_param_type)
            {
              Error::error(Error::ANIMATION_BLOCK_ASSIGNMENT_PARAMETER_TYPE_ERROR,
                           gpl_type_to_string(lhs_base_object_type),
                           gpl_type_to_string(rhs_param_type)
                          );
  
            }
            else statement_block_stack.top()->insert(new Assign_statement(ASSIGN, lhs, rhs));
            }
          }
      else // the types are ok
      {
        statement_block_stack.top()->insert(new Assign_statement(ASSIGN, lhs, rhs));
      }
  }
#line 2756 "y.tab.c"
    break;

  case 84: /* assign_statement: variable "+=" expression  */
#line 922 "gpl.y"
  {
      Gpl_type lhs_type = (yyvsp[-2].union_variable)->get_type();
      Gpl_type rhs_type = (yyvsp[0].union_expression)->get_type();

      // game_object & statement_block are illegal on lhs of +=
      if ((lhs_type & GAME_OBJECT) || (lhs_type == ANIMATION_BLOCK))
      {
        Error::error(Error::INVALID_LHS_OF_PLUS_ASSIGNMENT,
                  (yyvsp[-2].union_variable)->get_name(),
                  gpl_type_to_string(lhs_type)
              );
      }

      // if variable is an INT, expression must be INT
      // if variable is a DOUBLE, expression must be INT or DOUBLE
      // if variable is a STRING, expression must be STRING,INT, or DOUBLE
      else if ((lhs_type == INT && rhs_type != INT)
          ||(lhs_type==DOUBLE&&(rhs_type != INT && rhs_type!=DOUBLE))
          ||(lhs_type == STRING && rhs_type == ANIMATION_BLOCK)
          )
      {
        Error::error(Error::PLUS_ASSIGNMENT_TYPE_ERROR,
              gpl_type_to_string(lhs_type),
              gpl_type_to_string(rhs_type)
              );
      }
      else // the types are ok
      {
        statement_block_stack.top()->insert(new Assign_statement(PLUS_ASSIGN, (yyvsp[-2].union_variable), (yyvsp[0].union_expression)));
      }
  }
#line 2792 "y.tab.c"
    break;

  case 85: /* assign_statement: variable "-=" expression  */
#line 954 "gpl.y"
  {
      Gpl_type lhs_type = (yyvsp[-2].union_variable)->get_type();
      Gpl_type rhs_type = (yyvsp[0].union_expression)->get_type();

      // game_object & statement_block & string are illegal on lhs of +=
      if (lhs_type != INT && lhs_type != DOUBLE)
      {
        Error::error(Error::INVALID_LHS_OF_MINUS_ASSIGNMENT,
                  (yyvsp[-2].union_variable)->get_name(),
                  gpl_type_to_string(lhs_type)
                 );
      }

      // if variable is an INT, expression must be INT
      // if variable is a DOUBLE, expression must be INT or DOUBLE
      else if ((lhs_type == INT && rhs_type != INT)
          ||(lhs_type==DOUBLE&&(rhs_type != INT && rhs_type!=DOUBLE))
          )
      {
        Error::error(Error::MINUS_ASSIGNMENT_TYPE_ERROR,
              gpl_type_to_string(lhs_type),
              gpl_type_to_string(rhs_type)
              );
      }
      else // the types are ok
      {
        statement_block_stack.top()->insert(new Assign_statement(MINUS_ASSIGN, (yyvsp[-2].union_variable), (yyvsp[0].union_expression)));
      }
  }
#line 2826 "y.tab.c"
    break;

  case 86: /* assign_statement: variable "++"  */
#line 984 "gpl.y"
  {
      Gpl_type lhs_type = (yyvsp[-1].union_variable)->get_type();
      if (lhs_type != INT)
      {
        Error::error(Error::INVALID_LHS_OF_PLUS_PLUS,
                  (yyvsp[-1].union_variable)->get_name(),
                  gpl_type_to_string(lhs_type)
                 );
      }
      else // the types are ok
      {
        statement_block_stack.top()->insert(new Assign_statement(PLUS_PLUS, (yyvsp[-1].union_variable)));
      }
  }
#line 2845 "y.tab.c"
    break;

  case 87: /* assign_statement: variable "--"  */
#line 999 "gpl.y"
  {
      Gpl_type lhs_type = (yyvsp[-1].union_variable)->get_type();
      if (lhs_type != INT)
      {
        Error::error(Error::INVALID_LHS_OF_MINUS_MINUS,
                  (yyvsp[-1].union_variable)->get_name(),
                  gpl_type_to_string(lhs_type)
                 );
      }
      else // the types are ok
      {
        statement_block_stack.top()->insert(new Assign_statement(MINUS_MINUS, (yyvsp[-1].union_variable)));
      }
  }
#line 2864 "y.tab.c"
    break;

  case 88: /* variable: "identifier"  */
#line 1018 "gpl.y"
    {
        Symbol *sym = Symbol_table::instance()->lookup(*(yyvsp[0].union_string));

        if (!sym) {
            Error::error(Error::UNDECLARED_VARIABLE, *(yyvsp[0].union_string));
            (yyval.union_variable) = nullptr;
        } else if (sym->is_array()) {
            Error::error(Error::VARIABLE_IS_AN_ARRAY, *(yyvsp[0].union_string));
            (yyval.union_variable) = nullptr;
        } else {
            (yyval.union_variable) = new Variable(sym);
        }

        delete (yyvsp[0].union_string);
    }
#line 2884 "y.tab.c"
    break;

  case 89: /* variable: "identifier" "[" expression "]"  */
#line 1034 "gpl.y"
    {
        Symbol *sym = Symbol_table::instance()->lookup(*(yyvsp[-3].union_string));

        if (!sym) {
            Error::error(Error::UNDECLARED_VARIABLE, *(yyvsp[-3].union_string) + "[]");
            (yyval.union_variable) = nullptr;
        } else if (!sym->is_array()) {
            Error::error(Error::VARIABLE_NOT_AN_ARRAY, *(yyvsp[-3].union_string));
            (yyval.union_variable) = nullptr;
        } else {
            Gpl_type index_type = (yyvsp[-1].union_expression)->get_type();

            if (index_type != INT) {
                Error::error(
                    Error::ARRAY_INDEX_MUST_BE_AN_INTEGER,
                    *(yyvsp[-3].union_string),
                    "A " + gpl_type_to_string(index_type) + " expression"
                );
                (yyval.union_variable) = nullptr;
            } else {
                (yyval.union_variable) = new Variable(sym, (yyvsp[-1].union_expression));
            }
        }

        delete (yyvsp[-3].union_string);
    }
#line 2915 "y.tab.c"
    break;

  case 90: /* variable: "identifier" "." "identifier"  */
#line 1061 "gpl.y"
    {
        Symbol *sym = Symbol_table::instance()->lookup(*(yyvsp[-2].union_string));

        if (!sym) {
            // Variable not found
            Error::error(Error::UNDECLARED_VARIABLE, *(yyvsp[-2].union_string));
            (yyval.union_variable) = nullptr;
        } else if (!sym->is_game_object()) {
            // Variable is not a game object
            Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *(yyvsp[-2].union_string));
            (yyval.union_variable) = nullptr;
        } else {
            // Check if the member variable exists
            Game_object *game_object = sym->get_game_object_value();
            assert(game_object != nullptr);

            Gpl_type member_type;
            if (game_object->get_member_variable_type(*(yyvsp[0].union_string), member_type) != OK) {
                // Member variable does not exist
                Error::error(Error::UNDECLARED_MEMBER, *(yyvsp[-2].union_string), *(yyvsp[0].union_string));
                (yyval.union_variable) = nullptr;
            } else {
                // Member exists, create the variable
                (yyval.union_variable) = new Variable(sym, *(yyvsp[0].union_string));
            }
        }

        delete (yyvsp[-2].union_string);
        delete (yyvsp[0].union_string);
    }
#line 2950 "y.tab.c"
    break;

  case 91: /* variable: "identifier" "[" expression "]" "." "identifier"  */
#line 1092 "gpl.y"
    {
        Symbol *sym = Symbol_table::instance()->lookup(*(yyvsp[-5].union_string));

        if (!sym) {
            Error::error(Error::UNDECLARED_VARIABLE, *(yyvsp[-5].union_string) + "[]");
            (yyval.union_variable) = nullptr;
        } else {
            if (!sym->is_array()) {
                Error::error(Error::VARIABLE_NOT_AN_ARRAY, *(yyvsp[-5].union_string));
                (yyval.union_variable) = nullptr;
            } else {
                int index = (yyvsp[-3].union_expression)->eval_int();
                if (!sym->is_game_object()) {
                    Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *(yyvsp[-5].union_string));
                    (yyval.union_variable) = nullptr;
                } else {
                    (yyval.union_variable) = new Variable(sym, (yyvsp[-3].union_expression), *(yyvsp[0].union_string)); // Member variable like `rects[i].x`
                }
            }
        }

        delete (yyvsp[-5].union_string);
        delete (yyvsp[0].union_string);
    }
#line 2979 "y.tab.c"
    break;

  case 92: /* expression: primary_expression  */
#line 1121 "gpl.y"
    { 
        (yyval.union_expression) = ((yyvsp[0].union_expression) == nullptr) ? new Expression(0) : (yyvsp[0].union_expression);
    }
#line 2987 "y.tab.c"
    break;

  case 93: /* expression: expression "||" expression  */
#line 1125 "gpl.y"
    {
        bool lhs_valid = ((yyvsp[-2].union_expression) != nullptr && (yyvsp[-2].union_expression)->get_type() != STRING);
        bool rhs_valid = ((yyvsp[0].union_expression) != nullptr && (yyvsp[0].union_expression)->get_type() != STRING);

        if (!lhs_valid) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "||", gpl_type_to_string((yyvsp[-2].union_expression)->get_type()));
        }
        if (!rhs_valid) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "||", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
        }

        (yyval.union_expression) = (!lhs_valid || !rhs_valid) ? new Expression(0) : new Expression(OR, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
    }
#line 3005 "y.tab.c"
    break;

  case 94: /* expression: expression "&&" expression  */
#line 1139 "gpl.y"
    {
        bool lhs_valid = ((yyvsp[-2].union_expression) != nullptr && (yyvsp[-2].union_expression)->get_type() != STRING);
        bool rhs_valid = ((yyvsp[0].union_expression) != nullptr && (yyvsp[0].union_expression)->get_type() != STRING);

        if (!lhs_valid) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "&&", gpl_type_to_string((yyvsp[-2].union_expression)->get_type()));
        }
        if (!rhs_valid) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "&&", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
        }

        (yyval.union_expression) = (!lhs_valid || !rhs_valid) ? new Expression(0) : new Expression(AND, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
    }
#line 3023 "y.tab.c"
    break;

  case 95: /* expression: expression "<=" expression  */
#line 1153 "gpl.y"
    {
        (yyval.union_expression) = ((yyvsp[-2].union_expression) == nullptr || (yyvsp[0].union_expression) == nullptr) 
            ? new Expression(0) 
            : new Expression(LESS_EQUAL, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
    }
#line 3033 "y.tab.c"
    break;

  case 96: /* expression: expression ">=" expression  */
#line 1159 "gpl.y"
    {
        (yyval.union_expression) = ((yyvsp[-2].union_expression) == nullptr || (yyvsp[0].union_expression) == nullptr) 
            ? new Expression(0) 
            : new Expression(GREATER_EQUAL, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
    }
#line 3043 "y.tab.c"
    break;

  case 97: /* expression: expression "<" expression  */
#line 1165 "gpl.y"
    {
        (yyval.union_expression) = ((yyvsp[-2].union_expression) == nullptr || (yyvsp[0].union_expression) == nullptr) 
            ? new Expression(0) 
            : new Expression(LESS_THAN, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
    }
#line 3053 "y.tab.c"
    break;

  case 98: /* expression: expression ">" expression  */
#line 1171 "gpl.y"
    {
        (yyval.union_expression) = ((yyvsp[-2].union_expression) == nullptr || (yyvsp[0].union_expression) == nullptr) 
            ? new Expression(0) 
            : new Expression(GREATER_THAN, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
    }
#line 3063 "y.tab.c"
    break;

  case 99: /* expression: expression "==" expression  */
#line 1177 "gpl.y"
    {
        (yyval.union_expression) = ((yyvsp[-2].union_expression) == nullptr || (yyvsp[0].union_expression) == nullptr) 
            ? new Expression(0) 
            : new Expression(EQUAL, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
    }
#line 3073 "y.tab.c"
    break;

  case 100: /* expression: expression "!=" expression  */
#line 1183 "gpl.y"
    {
        (yyval.union_expression) = ((yyvsp[-2].union_expression) == nullptr || (yyvsp[0].union_expression) == nullptr) 
            ? new Expression(0) 
            : new Expression(NOT_EQUAL, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
    }
#line 3083 "y.tab.c"
    break;

  case 101: /* expression: expression "+" expression  */
#line 1189 "gpl.y"
    {
        if ((yyvsp[-2].union_expression) == nullptr || (yyvsp[0].union_expression) == nullptr) {
            (yyval.union_expression) = new Expression(0);
        } else if ((yyvsp[-2].union_expression)->get_type() == STRING || (yyvsp[0].union_expression)->get_type() == STRING) {
            auto result = new string((yyvsp[-2].union_expression)->eval_string() + (yyvsp[0].union_expression)->eval_string());
            (yyval.union_expression) = new Expression(result);
        } else {
            (yyval.union_expression) = new Expression(PLUS, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
        }
    }
#line 3098 "y.tab.c"
    break;

  case 102: /* expression: expression "-" expression  */
#line 1200 "gpl.y"
    {
        bool lhs_valid = ((yyvsp[-2].union_expression) != nullptr && (yyvsp[-2].union_expression)->get_type() != STRING);
        bool rhs_valid = ((yyvsp[0].union_expression) != nullptr && (yyvsp[0].union_expression)->get_type() != STRING);

        if (!lhs_valid) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "-", gpl_type_to_string((yyvsp[-2].union_expression)->get_type()));
        }
        if (!rhs_valid) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
        }

        (yyval.union_expression) = (!lhs_valid || !rhs_valid) ? new Expression(0) : new Expression(MINUS, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
    }
#line 3116 "y.tab.c"
    break;

  case 103: /* expression: expression "*" expression  */
#line 1214 "gpl.y"
    {
        bool lhs_valid = ((yyvsp[-2].union_expression) != nullptr && (yyvsp[-2].union_expression)->get_type() != STRING);
        bool rhs_valid = ((yyvsp[0].union_expression) != nullptr && (yyvsp[0].union_expression)->get_type() != STRING);

        if (!lhs_valid) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "*", gpl_type_to_string((yyvsp[-2].union_expression)->get_type()));
        }
        if (!rhs_valid) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "*", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
        }

        (yyval.union_expression) = (!lhs_valid || !rhs_valid) ? new Expression(0) : new Expression(MULTIPLY, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
    }
#line 3134 "y.tab.c"
    break;

  case 104: /* expression: expression "/" expression  */
#line 1228 "gpl.y"
    {
        bool lhs_valid = ((yyvsp[-2].union_expression) != nullptr && (yyvsp[-2].union_expression)->get_type() != STRING);
        bool rhs_valid = ((yyvsp[0].union_expression) != nullptr && (yyvsp[0].union_expression)->get_type() != STRING);

        if (!lhs_valid) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "/", gpl_type_to_string((yyvsp[-2].union_expression)->get_type()));
        }
        if (!rhs_valid) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "/", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
        }

        (yyval.union_expression) = (!lhs_valid || !rhs_valid) ? new Expression(0) : new Expression(DIVIDE, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
    }
#line 3152 "y.tab.c"
    break;

  case 105: /* expression: expression "%" expression  */
#line 1242 "gpl.y"
    {
        bool lhs_valid = ((yyvsp[-2].union_expression) != nullptr && (yyvsp[-2].union_expression)->get_type() == INT);
        bool rhs_valid = ((yyvsp[0].union_expression) != nullptr && (yyvsp[0].union_expression)->get_type() == INT);

        if (!lhs_valid) {
            Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "%", gpl_type_to_string((yyvsp[-2].union_expression)->get_type()));
        }
        if (!rhs_valid) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "%", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
        }

        (yyval.union_expression) = (!lhs_valid || !rhs_valid) ? new Expression(0) : new Expression(MOD, (yyvsp[-2].union_expression), (yyvsp[0].union_expression));
    }
#line 3170 "y.tab.c"
    break;

  case 106: /* expression: "-" expression  */
#line 1256 "gpl.y"
    {
        if ((yyvsp[0].union_expression) == nullptr) {
            (yyval.union_expression) = new Expression(0);
        } else if ((yyvsp[0].union_expression)->get_type() == STRING) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
            (yyval.union_expression) = new Expression(0);
        } else {
            (yyval.union_expression) = new Expression(UNARY_MINUS, (yyvsp[0].union_expression));
        }
    }
#line 3185 "y.tab.c"
    break;

  case 107: /* expression: "!" expression  */
#line 1267 "gpl.y"
    {
        if ((yyvsp[0].union_expression) == nullptr) {
            (yyval.union_expression) = new Expression(0);
        } else if ((yyvsp[0].union_expression)->get_type() == STRING) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "!", gpl_type_to_string((yyvsp[0].union_expression)->get_type()));
            (yyval.union_expression) = new Expression(0);
        } else {
            (yyval.union_expression) = new Expression(NOT, (yyvsp[0].union_expression));
        }
    }
#line 3200 "y.tab.c"
    break;

  case 108: /* expression: math_operator "(" expression ")"  */
#line 1278 "gpl.y"
    {
        if ((yyvsp[-1].union_expression) == nullptr) {
            (yyval.union_expression) = new Expression(0);
        } else if ((yyvsp[-1].union_expression)->get_type() == STRING) {
            Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, 
                         operator_to_string(static_cast<Operator_type>((yyvsp[-3].math_operator_type))), 
                         gpl_type_to_string((yyvsp[-1].union_expression)->get_type()));
            (yyval.union_expression) = new Expression(0);
        } else {
            (yyval.union_expression) = new Expression(static_cast<Operator_type>((yyvsp[-3].math_operator_type)), (yyvsp[-1].union_expression));
        }
    }
#line 3217 "y.tab.c"
    break;

  case 109: /* primary_expression: "(" expression ")"  */
#line 1295 "gpl.y"
    { 
        (yyval.union_expression) = ((yyvsp[-1].union_expression) == nullptr) ? new Expression(0) : (yyvsp[-1].union_expression);
    }
#line 3225 "y.tab.c"
    break;

  case 110: /* primary_expression: variable  */
#line 1299 "gpl.y"
    { 
        (yyval.union_expression) = ((yyvsp[0].union_variable) == nullptr) ? new Expression(0) : new Expression((yyvsp[0].union_variable));
    }
#line 3233 "y.tab.c"
    break;

  case 111: /* primary_expression: "int constant"  */
#line 1303 "gpl.y"
    { 
        (yyval.union_expression) = new Expression((yyvsp[0].union_int)); 
    }
#line 3241 "y.tab.c"
    break;

  case 112: /* primary_expression: "true"  */
#line 1307 "gpl.y"
    { 
        (yyval.union_expression) = new Expression(1); 
    }
#line 3249 "y.tab.c"
    break;

  case 113: /* primary_expression: "false"  */
#line 1311 "gpl.y"
    { 
        (yyval.union_expression) = new Expression(0); 
    }
#line 3257 "y.tab.c"
    break;

  case 114: /* primary_expression: "double constant"  */
#line 1315 "gpl.y"
    { 
        (yyval.union_expression) = new Expression((yyvsp[0].union_double)); 
    }
#line 3265 "y.tab.c"
    break;

  case 115: /* primary_expression: "string constant"  */
#line 1319 "gpl.y"
    { 
        (yyval.union_expression) = new Expression((yyvsp[0].union_string)); 
    }
#line 3273 "y.tab.c"
    break;

  case 116: /* math_operator: "sin"  */
#line 1326 "gpl.y"
          { (yyval.math_operator_type) = SIN; }
#line 3279 "y.tab.c"
    break;

  case 117: /* math_operator: "cos"  */
#line 1327 "gpl.y"
            { (yyval.math_operator_type) = COS; }
#line 3285 "y.tab.c"
    break;

  case 118: /* math_operator: "tan"  */
#line 1328 "gpl.y"
            { (yyval.math_operator_type) = TAN; }
#line 3291 "y.tab.c"
    break;

  case 119: /* math_operator: "asin"  */
#line 1329 "gpl.y"
             { (yyval.math_operator_type) = ASIN; }
#line 3297 "y.tab.c"
    break;

  case 120: /* math_operator: "acos"  */
#line 1330 "gpl.y"
             { (yyval.math_operator_type) = ACOS; }
#line 3303 "y.tab.c"
    break;

  case 121: /* math_operator: "atan"  */
#line 1331 "gpl.y"
             { (yyval.math_operator_type) = ATAN; }
#line 3309 "y.tab.c"
    break;

  case 122: /* math_operator: "sqrt"  */
#line 1332 "gpl.y"
             { (yyval.math_operator_type) = SQRT; }
#line 3315 "y.tab.c"
    break;

  case 123: /* math_operator: "floor"  */
#line 1333 "gpl.y"
              { (yyval.math_operator_type) = FLOOR; }
#line 3321 "y.tab.c"
    break;

  case 124: /* math_operator: "abs"  */
#line 1334 "gpl.y"
            { (yyval.math_operator_type) = ABS; }
#line 3327 "y.tab.c"
    break;

  case 125: /* math_operator: "random"  */
#line 1335 "gpl.y"
               { (yyval.math_operator_type) = RANDOM; }
#line 3333 "y.tab.c"
    break;


#line 3337 "y.tab.c"

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

