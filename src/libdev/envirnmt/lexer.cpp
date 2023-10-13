#define YY_DEFAULT_ACTION ECHO;
/* A lexical scanner generated by pclex */

#define YY_END_TOK 0
#define YY_NEW_FILE -1
#define YY_DO_DEFAULT -2
#ifndef BUFSIZ
#include <cstdio>
#include <algorithm>
#endif
// #define F_BUFSIZ BUFSIZ
#define F_BUFSIZ 4096
#define YY_BUF_SIZE (F_BUFSIZ * 2)
#define YY_BUF_MAX (YY_BUF_SIZE - 1)
#ifndef YY_MAX_LINE
#define YY_MAX_LINE F_BUFSIZ
#endif
#define YY_BUF_LIM (YY_BUF_MAX - YY_MAX_LINE)
#define ECHO (void)fwrite((unsigned char*)yytext, yyleng, 1, yyout)
#define YY_INPUT(buf, result, max_size)                                                                                \
    if ((result = fread((unsigned char*)buf, sizeof(unsigned char), max_size, yyin)) < 0)                              \
        YY_FATAL_ERROR("L0048: fread() in PCLEX scanner failed");
#define YY_NULL 0
#define YY_OUTPUT(c) fputc(c, yyout);
#define YY_FATAL_ERROR(msg)                                                                                            \
    {                                                                                                                  \
        fputs(msg, stderr);                                                                                            \
        putc('\n', stderr);                                                                                            \
        exit(1);                                                                                                       \
    }
#define YY_FIRST_CHAR yy_ch_buf[yy_b_buf_p]
#define yywrap() 1
#define BEGIN yy_start = 1 +
#define YY_SET_BOL(array, pos) array[pos - 1] = '\n';
#define YY_DECL int yylex()
#define yyless(n)                                                                                                      \
    {                                                                                                                  \
        YY_DO_BEFORE_SCAN;                                                                                             \
        yy_c_buf_p = yy_b_buf_p + (n)-1;                                                                               \
        YY_DO_BEFORE_ACTION;                                                                                           \
    }
#define YY_BREAK break;
#define YY_INIT                                                                                                        \
    {                                                                                                                  \
        yyleng = yy_c_buf_p = yy_e_buf_p = 0;                                                                          \
        yy_hold_char = yy_ch_buf[yy_c_buf_p] = '\n';                                                                   \
        yytext = &yy_ch_buf[yy_c_buf_p];                                                                               \
        yy_saw_eof = 0;                                                                                                \
    }
#define YY_LENG (yy_c_buf_p - yy_b_buf_p + 1)
#define YY_DO_BEFORE_SCAN yytext[yyleng] = yy_hold_char;
#define YY_DO_BEFORE_ACTION                                                                                            \
    yytext = &yy_ch_buf[yy_b_buf_p];                                                                                   \
    yyleng = YY_LENG;                                                                                                  \
    yy_hold_char = yytext[yyleng];                                                                                     \
    yytext[yyleng] = '\0';
#define REJECT                                                                                                         \
    {                                                                                                                  \
        YY_DO_BEFORE_SCAN;                                                                                             \
        yy_c_buf_p = yy_full_match;                                                                                    \
        ++yy_lp;                                                                                                       \
        goto find_rule;                                                                                                \
    }

static int input();
static void unput(unsigned char);

// # line 1 "d:\libdev\envirnmt\source\lexer.l"
#define INITIAL 0
// # line 2 "d:\libdev\envirnmt\source\lexer.l"
/*
 * L E X . L
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

#include "base/base.hpp"
#include "base/diag.hpp"

#include <stdlib.h>
#include <cstring> /* strcpy(), getc(),  putc()  */
#include "stdlib/string.hpp"

class RenColour;

#include "envirnmt/elevclut.hpp"
// #include "envirnmt/internal/yytab.h"
// ADDED
#define FLOAT_CONSTANT 257
#define INTEGER_CONSTANT 258
#define STRING 259
#define UNKNOWN_KEYWORD 260
#define ColourKW 261
#define TableKW 262
#define OrbitKW 263
#define SatelliteKW 264
#define MeshKW 265
#define FileKW 266
#define BeginKW 267
#define RadiusKW 268
#define SetKW 269
#define ElevationKW 270
#define MaxKW 271
#define MinKW 272
#define HeadingKW 273
#define PeriodKW 274
#define StartKW 275
#define DirectionalKW 276
#define TimeKW 277
#define AmbientKW 278
#define GraduatedKW 279
#define SkyKW 280
#define UniformKW 281
#define ControllerKW 282
#define FogKW 283
#define VisibilityKW 284
#define StarsKW 285
#define NumberKW 286
#define ZenithKW 287
#define MultKW 288
#define StaticKW 289
#define DynamicKW 290
#define BackgroundKW 291
#define DayKW 292
#define NightKW 293
#define ThresholdKW 294
#define PhaseKW 295
#define NvgKW 296
#define FilterKW 297
#define LightKW 298
#define ConfigKW 299
#define SkylineKW 300
union YYSTYPE
{
    int intVal;
    float floatVal;
    string* pString;
    RenColour* pColour;
    EnvElevationColourTable* pClut;
    EnvElevationColourTable::Entry* pClutEntry;
};
// YYSTYPE yylval, yyval;
extern YYSTYPE yylval;
#define YYERRCODE 256
// END ADDED

extern unsigned char* yytext; /* current token's text, internal pcyacc variable */
extern FILE* yyin; /* pointer to input file, defined in main.c */

int yylineno = -1; /* current line number */

static int keyword();

// Don't ask why, but yytext is unsigned and strcmp requires signed.
inline const char* yytextChar()
{
    // return _STATIC_CAST(char*, yytext);
    return _REINTERPRET_CAST(char*, yytext);
}

// To allow istream's to be used, and therefore SysMetaFile's, you have to redefine this macro.
// See Abraxas PCLEX manual appendix C or Lex & Yacc (O' Reilly & Assoiciates) pages 156 - 157.

// Prototype for function that fills the buffer with chars from a stream.
int globalLexIstreamBufferInput(unsigned char* pBuffer, int bufferSize);

#undef YY_INPUT
#define YY_INPUT(pBuffer, result, bufferSize) (result = globalLexIstreamBufferInput(pBuffer, bufferSize))
#define COMMENT 2
// # line 48 "d:\libdev\envirnmt\source\lexer.l"
#define YY_JAM 32
#define YY_JAM_BASE 1696
static signed char a[39] = { 0,  14, 15, 6,  14, 15, 7,  15, 14, 15, 14, 15, 14, 15, 14, 15, 3,  14, 15, 1,
                             14, 15, 11, 15, 12, 15, 13, 15, 6,  2,  3,  5,  9,  4,  1,  11, 10, 8,  4 };

static signed char l[34] = { 0,  -2, -2, -2, -2, 1,  3,  6,  8,  10, 12, 14, 16, 19, 22, 24, 26,
                             28, 29, 29, 30, 30, 31, 32, 33, 33, 34, 35, 36, 37, 37, 38, 39, 39 };

static short int b[38]
    = { 0,    0,   114, 1,   2,    1696, 4,   1696, 26, 79,   101, 16,   191, 184,  0,   1696, 12,  5,    1,
        1696, 259, 271, 281, 1696, 6,    291, 284,  0,  1696, 5,   1696, 359, 1696, 416, 672,  928, 1184, 1440 };

static short int d[38] = { 0,  33, 33, 34, 34, 32, 32, 32, 35, 32, 32, 32, 32, 32,     36, 32, 32, 32, 35,
                           32, 32, 32, 32, 32, 37, 32, 32, 36, 32, 37, 32, 32, -32767, 32, 32, 32, 32, 32 };

static short int n[1953]
    = { 0,  32, 32, 32, 32, 32, 32, 32, 32, 6,  7,  15, 15, 17, 17, 30, 30, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 6,  32, 8,  19, 17, 17, 32, 32, 32, 32, 32, 16, 16, 9,  10, 11, 12, 12, 12, 12,
        12, 12, 12, 12, 12, 12, 23, 28, 19, 32, 32, 24, 32, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
        13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 32, 32, 32, 32, 13, 32, 13, 13, 13, 13,

        13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 6,  7,  20, 32,
        21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 32, 32, 32, 32, 32, 32, 32, 32, 32, 6,  32, 8,  22, 22, 22, 22,
        22, 22, 22, 22, 22, 22, 9,  10, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 32, 32, 32, 32, 32, 32, 32,
        13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,

        13, 13, 13, 13, 32, 32, 32, 32, 13, 32, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
        13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 25, 32, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 26, 26, 26, 26,
        26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 32, 32, 32, 32,
        26, 32, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

        26, 26, 26, 26, 26, 26, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 25, 32, 21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 26, 26, 26, 26,
        26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 32, 32, 32, 32,
        26, 32, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

        26, 26, 26, 26, 26, 26, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
        5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
        5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
        5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,

        5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
        5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
        5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
        5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,

        5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
        5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,
        5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,

        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,

        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,

        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
        18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
        18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,

        18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
        18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
        18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
        18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,

        18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
        18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
        18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
        18, 18, 18, 18, 18, 18, 27, 27, 27, 27, 27, 27, 27, 27, 27, 32, 27, 27, 27, 27, 27, 27,

        27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 32,
        27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
        27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
        27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,

        27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
        27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
        27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
        27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,

        27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
        27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
        29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
        29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,

        29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
        29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
        29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
        29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,

        29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
        29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
        29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
        29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 32, 32, 32, 32,

        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,

        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,

        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32 };

static short int c[1953]
    = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  4,  6,  17, 29, 24, 0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  1,  0,  1,  18, 6,  17, 0,  0,  0,  0,  0,  3,  4,  1,  1,  1,  1,  1,  1,  1,
        1,  1,  1,  1,  1,  1,  11, 16, 8,  0,  0,  11, 0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  1,  0,  1,  1,  1,  1,

        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  9,  0,
        9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  2,  10, 10, 10, 10,
        10, 10, 10, 10, 10, 10, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  0,  0,  0,  0,  0,  0,  0,
        2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,

        2,  2,  2,  2,  0,  0,  0,  0,  2,  0,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
        2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  12, 0,  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13,
        13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 0,  0,  0,  0,
        13, 0,  13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,

        13, 13, 13, 13, 13, 13, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 0,  21, 21, 21, 21, 21, 21, 21, 21,
        21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26,
        26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 0,  0,  0,  0,
        26, 0,  26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,

        26, 26, 26, 26, 26, 26, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
        33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
        33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
        33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,

        33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
        33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
        33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
        33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,

        33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
        33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33,
        33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34,
        34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,

        34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
        34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
        34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
        34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,

        34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
        34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
        34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
        34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,

        34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
        34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
        35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
        35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,

        35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
        35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
        35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
        35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,

        35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
        35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
        35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,
        35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 0,  36, 36, 36, 36, 36, 36,

        36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 0,
        36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
        36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
        36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,

        36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
        36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
        36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
        36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,

        36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
        36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
        37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
        37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,

        37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
        37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
        37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
        37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,

        37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
        37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
        37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37,
        37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 32, 32, 32, 32,

        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,

        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,

        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
        32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32 };

FILE *yyin = stdin, *yyout = stdout;
static int yy_start, yy_b_buf_p, yy_c_buf_p, yy_e_buf_p;
static int yy_saw_eof = 1, yy_init = 1;
static unsigned char yy_ch_buf[YY_BUF_SIZE + 1];
static int yy_st_buf[YY_BUF_SIZE];
static unsigned char yy_hold_char;
unsigned char* yytext;
int yyleng;

static int input()
{
    int c;

    YY_DO_BEFORE_SCAN
    if (yy_c_buf_p == yy_e_buf_p)
    {
        int yy_n_chars;

        if (yy_saw_eof)
        {
            if (yywrap())
                return (EOF);

            YY_INIT;
        }

        yy_b_buf_p = 0;
        YY_INPUT(yy_ch_buf, yy_n_chars, YY_MAX_LINE);

        if (yy_n_chars == YY_NULL)
        {
            yy_saw_eof = 1;

            if (yywrap())
                return (EOF);

            YY_INIT;
            return (input());
        }

        yy_c_buf_p = -1;
        yy_e_buf_p = yy_n_chars - 1;
    }

    c = yy_ch_buf[++yy_c_buf_p];

    YY_DO_BEFORE_ACTION;

    return (c);
}

static void unput(unsigned char c)
{
    YY_DO_BEFORE_SCAN;

    if (yy_c_buf_p == 0)
    {
        register int i;
        register int yy_buf_pos = YY_BUF_MAX;

        for (i = yy_e_buf_p; i >= yy_c_buf_p; --i)
        {
            yy_ch_buf[yy_buf_pos] = yy_ch_buf[i];
            yy_st_buf[yy_buf_pos] = yy_st_buf[i];
            --yy_buf_pos;
        }

        yy_c_buf_p = YY_BUF_MAX - yy_e_buf_p;
        yy_e_buf_p = YY_BUF_MAX;
    }

    if (yy_c_buf_p <= 0)
        YY_FATAL_ERROR("L0027: PCLEX scanner push-back overflow");

    if (yy_c_buf_p >= yy_b_buf_p && yy_ch_buf[yy_c_buf_p] == '\n')
        yy_ch_buf[yy_c_buf_p - 1] = '\n';

    yy_ch_buf[yy_c_buf_p--] = c;

    YY_DO_BEFORE_ACTION;
}

YY_DECL
{
    register int yy_curst;
    register unsigned char yy_sym;
    int yy_n_chars, yy_lp, yy_iii, yy_buf_pos, yy_act, yy_full_match;

    if (yy_init)
    {
        YY_INIT;
        yy_start = 1;
        yy_init = 0;
    }
    goto get_next_token;

do_action:
    yy_full_match = yy_c_buf_p;

    for (;;)
    {
        YY_DO_BEFORE_ACTION

        switch (yy_act)
        {
            /*  An alternative to the keyword fn.  Why doesn't this work??
    begin       { return BeginKW; }
    colour      { return ColourKW; }
    elevation   { return ElevationKW; }
    file        { return FileKW; }
    heading     { return HeadingKW; }
    max         { return MaxKW; }
    mesh        { return MeshKW; }
    min         { return MinKW; }
    orbit       { return OrbitKW; }
    period      { return PeriodKW; }
    radius      { return RadiusKW; }
    satellite   { return SatelliteKW; }
    set         { return SetKW; }
    start       { return StartKW; }
    table       { return TableKW; }
    time        { return TimeKW; }
    */
            case 1:
                // # line 69 "d:\libdev\envirnmt\source\lexer.l"
                return keyword();
                YY_BREAK
            case 2:
                // # line 71 "d:\libdev\envirnmt\source\lexer.l"
                {
                    // The regex string is quoted.  Drop the first and last chars.
                    yylval.pString = new string(yytextChar() + 1, strlen(yytextChar()) - 2);
                    const string& str = *(yylval.pString);
                    IAIN_STREAM("Lexed string \"" << str << "\"" << std::endl);
                    return STRING;
                }
                YY_BREAK
            case 3:
                // # line 79 "d:\libdev\envirnmt\source\lexer.l"
                {
                    yylval.intVal = atoi(yytextChar());
                    IAIN_STREAM("Lexed int=" << yylval.intVal << std::endl);
                    return INTEGER_CONSTANT;
                }
                YY_BREAK
            case 4:
                // # line 85 "d:\libdev\envirnmt\source\lexer.l"
                {
                    yylval.floatVal = atof(yytextChar());
                    IAIN_STREAM("Lexed float=" << yylval.floatVal << std::endl);
                    return FLOAT_CONSTANT;
                }
                YY_BREAK
            case 5:
                // # line 91 "d:\libdev\envirnmt\source\lexer.l"
                {
                    yylval.floatVal = atof(yytextChar());
                    IAIN_STREAM("Lexed float=" << yylval.floatVal << std::endl);
                    return FLOAT_CONSTANT;
                }
                YY_BREAK
            case 6:
                // # line 97 "d:\libdev\envirnmt\source\lexer.l"
                ;
                YY_BREAK
            case 7:
                // # line 98 "d:\libdev\envirnmt\source\lexer.l"
                ++yylineno;
                YY_BREAK
            case 8:
                YY_DO_BEFORE_SCAN; /* undo effects of setting up yytext */
                yy_c_buf_p -= 1;
                YY_DO_BEFORE_ACTION; /* set up yytext again */
                // # line 100 "d:\libdev\envirnmt\source\lexer.l"
                ; /* C++ style comment */
                YY_BREAK
            case 9:
                // # line 101 "d:\libdev\envirnmt\source\lexer.l"
                BEGIN(COMMENT); /* begin exclusive start state for C comments */
                YY_BREAK
            case 10:
                // # line 102 "d:\libdev\envirnmt\source\lexer.l"
                BEGIN(0); /* end   exclusive start state for C comments */
                YY_BREAK
            case 11:
                // # line 103 "d:\libdev\envirnmt\source\lexer.l"
                ; /* breaks comments into lines    */
                YY_BREAK
            case 12:
                // # line 104 "d:\libdev\envirnmt\source\lexer.l"
                ++yylineno; /* so they won't overflow buffer */
                YY_BREAK
            case 13:
                // # line 105 "d:\libdev\envirnmt\source\lexer.l"
                ; /* so they won't overflow buffer */
                YY_BREAK
            case 14:
                // # line 107 "d:\libdev\envirnmt\source\lexer.l"
                {
                    IAIN_STREAM("Lexed '" << yytext[0] << "'" << std::endl);
                    return yytext[0];
                }
                YY_BREAK
            case 15:
                // # line 112 "d:\libdev\envirnmt\source\lexer.l"
                YY_DEFAULT_ACTION;
                YY_BREAK

            case YY_NEW_FILE:
                break;
            case YY_END_TOK:
                return (YY_END_TOK);
            default:
                YY_FATAL_ERROR("L0028: fatal PCLEX scanner internal error");
        }

    get_next_token:
        YY_DO_BEFORE_SCAN

        yy_curst = yy_start;

        if (yy_ch_buf[yy_c_buf_p] == '\n')
            ++yy_curst;

        yy_b_buf_p = yy_c_buf_p + 1;

        do
        {
            if (yy_c_buf_p == yy_e_buf_p)
            {
                if (yy_e_buf_p >= YY_BUF_LIM)
                {
                    yy_n_chars = yy_e_buf_p - yy_b_buf_p;

                    if (yy_n_chars >= 0)
                    {
                        for (yy_iii = 0; yy_iii <= yy_n_chars; ++yy_iii)
                        {
                            yy_buf_pos = yy_b_buf_p + yy_iii;
                            yy_ch_buf[yy_iii] = yy_ch_buf[yy_buf_pos];
                            yy_st_buf[yy_iii] = yy_st_buf[yy_buf_pos];
                        }
                    }

                    yy_b_buf_p = 0;
                    yy_e_buf_p = yy_n_chars;

                    if (yy_e_buf_p >= YY_BUF_LIM)
                        YY_FATAL_ERROR("L0029: PCLEX input buffer overflowed");

                    yy_c_buf_p = yy_e_buf_p;
                }
                else if (yy_saw_eof)
                {
                saweof:
                    if (yy_b_buf_p <= yy_e_buf_p)
                        break;
                    if (yywrap())
                        yy_act = YY_END_TOK;
                    else
                    {
                        YY_INIT;
                        yy_act = YY_NEW_FILE;
                    }
                    goto do_action;
                }

                YY_INPUT((yy_ch_buf + yy_c_buf_p + 1), yy_n_chars, YY_MAX_LINE);

                if (yy_n_chars == YY_NULL)
                {
                    if (yy_saw_eof)
                        YY_FATAL_ERROR("L0030: PCLEX scanner saw EOF twice - shouldn't happen");
                    yy_saw_eof = 1;
                    goto saweof;
                }

                yy_e_buf_p += yy_n_chars;
            }

            ++yy_c_buf_p;
            yy_sym = yy_ch_buf[yy_c_buf_p];
            if (yy_sym == '\000')
                yy_sym = '\001';

            while (c[b[yy_curst] + yy_sym] != yy_curst)
                yy_curst = d[yy_curst];

            yy_curst = n[b[yy_curst] + yy_sym];
            yy_st_buf[yy_c_buf_p] = yy_curst;
        } while (b[yy_curst] != YY_JAM_BASE);

        if (yy_c_buf_p >= yy_b_buf_p)
        {
            yy_curst = yy_st_buf[yy_c_buf_p];
            yy_lp = l[yy_curst];

        find_rule:
            for (;;)
            {
                if (yy_lp && yy_lp < l[yy_curst + 1])
                {
                    yy_act = a[yy_lp];
                    goto do_action;
                }

                if (--yy_c_buf_p < yy_b_buf_p)
                    break;

                yy_curst = yy_st_buf[yy_c_buf_p];
                yy_lp = l[yy_curst];
            }
        }
        ++yy_c_buf_p;

        yy_act = YY_DO_DEFAULT;
    }
}
// # line 112 "d:\libdev\envirnmt\source\lexer.l"

// keyword screener
// The contents of this table *must* be in alphabetical order for the
// binary search to work.
static const struct
{
    const char* name;
    int yylex;
} keywords[] = { { "ambient", AmbientKW },
                 { "background", BackgroundKW },
                 { "begin", BeginKW },
                 { "colour", ColourKW },
                 { "config", ConfigKW },
                 { "controller", ControllerKW },
                 { "day", DayKW },
                 { "dir", DirectionalKW },
                 { "directional", DirectionalKW },
                 { "dynamic", DynamicKW },
                 { "elevation", ElevationKW },
                 { "file", FileKW },
                 { "filter", FilterKW },
                 { "fog", FogKW },
                 { "heading", HeadingKW },
                 { "light", LightKW },
                 { "max", MaxKW },
                 { "mesh", MeshKW },
                 { "min", MinKW },
                 { "multiplier", MultKW },
                 { "night", NightKW },
                 { "number", NumberKW },
                 { "nvg", NvgKW },
                 { "orbit", OrbitKW },
                 { "period", PeriodKW },
                 { "phase", PhaseKW },
                 { "radius", RadiusKW },
                 { "satellite", SatelliteKW },
                 { "set", SetKW },
                 { "sky", SkyKW },
                 { "skyline", SkylineKW },
                 { "stars", StarsKW },
                 { "start", StartKW },
                 { "static", StaticKW },
                 { "table", TableKW },
                 { "threshold", ThresholdKW },
                 { "time", TimeKW },
                 { "uniform", UniformKW },
                 { "visibility", VisibilityKW },
                 { "zenith", ZenithKW } };

#define DIM(a) (sizeof(a) / sizeof((a)[0]))

static int keyword()
{
    register int mid;
    int cc, hi, lo;

    lo = 0;
    hi = DIM(keywords) - 1;

    while (lo <= hi)
    {
        mid = (lo + hi) / 2;

        const char* crufty = yytextChar();

        if ((cc = strcmp(crufty, keywords[mid].name)) == 0)
        {
            IAIN_STREAM("Lexed keyord \"" << crufty << "\"" << std::endl);
            return keywords[mid].yylex;
        }

        if (cc < 0)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    IAIN_STREAM("Lexed unknown keyord" << std::endl);
    return UNKNOWN_KEYWORD;
}

// This needs to be called to ensure initialisation. Otherwise only works for
// 1st file.
void yydoinit()
{
    yy_init = 1;
}

std::istream* pGlobalLexIstream = nullptr;

// This function reads characters from an istream into the buffer passed.
int globalLexIstreamBufferInput(unsigned char* pBuffer, int bufferSize)
{
    PRE(pBuffer);
    PRE(bufferSize > 0);
    PRE(pGlobalLexIstream);

    // pGlobalLexIstream->read(pBuffer, bufferSize);
    pGlobalLexIstream->read(_REINTERPRET_CAST(char*, pBuffer), bufferSize);

    // \r\n line endings seem to cause some troubles, replace them.
    std::replace(pBuffer, pBuffer + bufferSize, '\r', '\n');

    int result = 0;

    // Check to see if the first character was eof.
    // if(pGlobalLexIstream->rdstate() & std::ios::eofbit)
    //{
    //  result = YY_NULL;
    //}
    // Check to see whether only part of the buffer was filled.
    if (pGlobalLexIstream->rdstate() & std::ios::failbit || pGlobalLexIstream->rdstate() & std::ios::eofbit)
    {
        result = pGlobalLexIstream->gcount();
    }
    else
        result = bufferSize;

    return result;
}

/* End LEX.L ******************************************************/
