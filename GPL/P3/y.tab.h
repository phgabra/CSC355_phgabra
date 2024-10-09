/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
#line 23 "gpl.y"

  int              union_int;
  double           union_double;
  std::string      *union_string;  // MUST be a pointer to a string ARG!

#line 259 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
