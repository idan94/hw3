/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.ypp" /* yacc.c:339  */

   #include "hw3_output.hpp"
   #include <stack>
   #include <iostream>
   #include <map>
   #include <string>
   #include <vector>
   #include <assert.h>
   #include "utils.hpp"
   #include <set>
   #include <algorithm>
   #include <functional>
   using namespace std;
   extern int yylineno;

   string relop(Expression a, Expression b);
   string log_eq(Expression a, Expression b);
   string binop(Expression a, Expression b);
   void check_bool_exp(Expression exp);

   map<string,pair<string, int>>* make_table(map<string,pair<string, int>>* parent);
   void pop_tables();
   void pop_offsets();
   void push_tables(map<string,pair<string, int>>* table);
   void push_offsets(int offset);
   map<string,pair<string, int>> &top_tables();
   int &top_offsets();
   void insert(string name, string type,int offset);

   const string TYPE_INT    = "INT";
   const string TYPE_BOOL   = "BOOL";
   const string TYPE_BYTE   = "BYTE";
   const string TYPE_STRING = "STRING";
   const string TYPE_VOID = "VOID";
  
   int yylex();
   void yyerror(const char*);

   stack<map<string,pair<string, int>>>* tables = NULL;
   stack<int>* offsets = NULL;

   map<string,pair<string, int>>* t = NULL;

   string vectorToString(const std::vector<string>& argTypes) {
      string res;
      res = "(";
      for(int i = 0; i < argTypes.size(); ++i) {
         res.append(argTypes[i]);
         if (i + 1 < argTypes.size())
            res.append(",");
      }
      res.append(")");
      return res;
   }
   // Gets a string and 
   vector<string> split_str(string str, string delimiter){
      if(str[0] == '('){
         str.erase(0,1);
      }
      if(str[str.length()-1] == ')'){
         str.erase(str.length()-1,1);
      }
      vector<string> tokens;
      size_t position = 0;
      while ((position = str.find(delimiter)) != string::npos) {
         tokens.push_back(str.substr(0, position));
         str.erase(0,position + delimiter.length());
      }
      if(tokens.size()!=0 || !str.empty()){
         tokens.push_back(str);
      }
      return tokens;
   }

   string get_id_type(const string name, const stack<map<string, pair<string, int>>> &tables){
      stack<map<string, pair<string, int>>> *tabels_clone = new stack<map<string, pair<string, int>>>(tables);
      while (!tabels_clone->empty()) {
         auto table = tabels_clone->top();
         tabels_clone->pop();
         auto it= table.find(name);
         if (it != table.end()) {
               // if reached here, that means the key already is in some table
               string id_type = it->second.first;
               delete tabels_clone;
               return id_type;
         }
      }
      delete tabels_clone;
      output::errorUndef(yylineno, name);
      exit(0);
   }

   bool name_exists_in_table(const string name,const stack<map<string, pair<string, int>>> &tables, bool is_fun=false){
      /*
      * this function will get a pointer to a string representing a name and a stack of tables
      * the function will return true if the name is already in the tables and false otherwise
      */
      stack<map<string, pair<string, int>>> *tabels_clone = new stack<map<string, pair<string, int>>>(tables);
      while (!tabels_clone->empty()) {
         auto table = tabels_clone->top();
         tabels_clone->pop();
         // in c++11 table.contains doesnt exist yet, so to find if the key
         // exists in the table, we search an iterator, and if we got to the end
         // of the table, that means the value is not there
         auto it= table.find(name);
         if (it != table.end()) {
               // if reached here, that means the key already is in some table
               if(is_fun){
                  string id_type = it->second.first;
                  if(id_type.find("->") == string::npos){
                     return false;
                  }
               }
               // if reached here, that means the key already is in some table
               delete tabels_clone;
               return true;
         }
      }
      delete tabels_clone;
      return false;
   } 
   void print_map_inc_offset(map<string, pair<string, int>> scope_map){
      for (auto element : scope_map){
         output::printID(element.first, element.second.second, element.second.first);
      }
   }


   template<class input_class, class output_class>
   void print_stack_of_maps(stack<map<input_class, output_class>> s) {
      stack<map<input_class, output_class>> *clone = new stack<map<input_class, output_class>>(s);
      while (!clone->empty()) {
         map<input_class, output_class> m = clone->top();
         clone->pop();
         print_map_inc_offset(m);
      }
      delete (clone);
   }

#line 206 "parser.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.hpp".  */
#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VOID = 258,
    INT = 259,
    BYTE = 260,
    B = 261,
    BOOL = 262,
    TRUE = 263,
    FALSE = 264,
    RETURN = 265,
    IF = 266,
    WHILE = 267,
    BREAK = 268,
    CONTINUE = 269,
    SC = 270,
    COMMA = 271,
    LBRACE = 272,
    RBRACE = 273,
    ASSIGN = 274,
    OR = 275,
    AND = 276,
    EQUALITY_RELOP = 277,
    RELATIONAL_RELOP = 278,
    ADD_BINOP = 279,
    MUL_BINOP = 280,
    NOT = 281,
    LPAREN = 282,
    RPAREN = 283,
    ELSE = 284,
    ID = 285,
    NUM = 286,
    STRING = 287
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 290 "parser.tab.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   212

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  108

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   173,   173,   186,   197,   198,   200,   202,   228,   229,
     233,   238,   243,   248,   252,   257,   262,   263,   267,   270,
     273,   276,   280,   282,   290,   298,   304,   305,   306,   307,
     308,   310,   315,   322,   341,   357,   360,   365,   369,   373,
     378,   379,   382,   385,   388,   391,   395,   399,   404,   408,
     412,   413,   416,   417,   420
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VOID", "INT", "BYTE", "B", "BOOL",
  "TRUE", "FALSE", "RETURN", "IF", "WHILE", "BREAK", "CONTINUE", "SC",
  "COMMA", "LBRACE", "RBRACE", "ASSIGN", "OR", "AND", "EQUALITY_RELOP",
  "RELATIONAL_RELOP", "ADD_BINOP", "MUL_BINOP", "NOT", "LPAREN", "RPAREN",
  "ELSE", "ID", "NUM", "STRING", "$accept", "Program", "Marker1", "Funcs",
  "FuncDecl", "FuncDeclPart1", "FuncDeclPart2", "RetType", "Formals",
  "FormalsList", "FormalsDecl", "Statements", "Statement", "Marker2",
  "Marker3", "Call", "ExpList", "Type", "Exp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287
};
# endif

#define YYPACT_NINF -81

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-81)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -81,     9,    44,   -81,   -81,   -81,   -81,   -81,   -81,    44,
       6,    -8,   -81,   -81,    26,   -81,     1,   106,    18,    23,
      38,    54,   -81,     5,    80,   -81,    57,    28,    50,   -81,
     -81,   -81,   121,   121,    32,    67,   -81,   -81,    -9,   121,
     121,   -81,   -81,    26,   121,   114,   -81,   -81,   -81,   -12,
      48,   -81,    61,    52,   -81,   161,   -81,   -81,   121,   121,
     121,   121,   121,   121,   170,   179,    95,   134,   -81,    55,
     155,   -81,   -81,   121,   -81,    50,   -81,   -81,   187,    94,
      43,   103,    70,   -81,   -81,   -81,   -81,   -81,   -81,   121,
     145,   -81,    26,    26,   -81,   -81,   -81,   -81,    72,    74,
     -81,   -81,    26,    26,   -81,   -81,   -81,   -81
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     4,     1,    10,    37,    38,    39,     2,     4,
       0,     0,     9,     5,     0,     6,     0,     0,     0,     0,
       0,     0,    31,     0,     0,    16,     0,     0,    11,    48,
      49,    27,     0,     0,    43,    45,    47,    44,     0,     0,
       0,    29,    30,     0,     0,     0,    32,    17,    26,     0,
       0,    12,    13,     0,    50,     0,    46,    28,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,     0,
      35,     8,    23,     0,     7,     0,    15,    40,    52,    51,
      53,    54,    41,    42,    31,    31,    22,    25,    33,     0,
       0,    14,     0,     0,    36,    24,    32,    32,    18,    20,
      31,    31,     0,     0,    32,    32,    19,    21
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -81,   -81,   -81,    77,   -81,   -81,   -81,   -81,   -81,    21,
     -81,    68,   -22,   -80,   -79,   -14,    15,    -1,     2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     8,     9,    10,    15,    11,    50,    51,
      52,    24,    25,    43,    71,    37,    69,    27,    70
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      26,    12,    47,    72,    92,    93,    57,    73,    12,     3,
      26,    58,    59,    60,    61,    62,    63,    98,    99,    38,
     102,   103,    16,    14,    44,   106,   107,    53,    28,    26,
       5,     6,    45,     7,    54,    55,    17,    18,    19,    20,
      21,    64,    65,    22,    47,    39,    67,     4,     5,     6,
      40,     7,    26,    41,     5,     6,    23,     7,    49,    45,
      78,    79,    80,    81,    82,    83,    61,    62,    63,    42,
      96,    97,    48,    56,    53,    90,    74,    75,    26,    26,
     104,   105,    76,    88,     5,     6,    13,     7,    26,    26,
      17,    18,    19,    20,    21,    63,    91,    22,    46,     5,
       6,   100,     7,   101,    94,    17,    18,    19,    20,    21,
      23,    66,    22,    86,    29,    30,    60,    61,    62,    63,
       0,    31,    29,    30,     0,    23,    -1,    62,    63,    29,
      30,     0,    32,    33,     0,     0,    34,    35,    36,     0,
      32,    33,    68,     0,    34,    35,    36,    32,    33,    87,
       0,    34,    35,    36,    58,    59,    60,    61,    62,    63,
      95,     0,     0,     0,     0,    58,    59,    60,    61,    62,
      63,    89,     0,     0,     0,    58,    59,    60,    61,    62,
      63,    58,    59,    60,    61,    62,    63,     0,     0,    77,
      58,    59,    60,    61,    62,    63,     0,     0,    84,    58,
      59,    60,    61,    62,    63,     0,     0,    85,    59,    60,
      61,    62,    63
};

static const yytype_int8 yycheck[] =
{
      14,     2,    24,    15,    84,    85,    15,    19,     9,     0,
      24,    20,    21,    22,    23,    24,    25,    96,    97,    17,
     100,   101,    30,    17,    19,   104,   105,    28,    27,    43,
       4,     5,    27,     7,    32,    33,    10,    11,    12,    13,
      14,    39,    40,    17,    66,    27,    44,     3,     4,     5,
      27,     7,    66,    15,     4,     5,    30,     7,    30,    27,
      58,    59,    60,    61,    62,    63,    23,    24,    25,    15,
      92,    93,    15,     6,    75,    73,    28,    16,    92,    93,
     102,   103,    30,    28,     4,     5,     9,     7,   102,   103,
      10,    11,    12,    13,    14,    25,    75,    17,    18,     4,
       5,    29,     7,    29,    89,    10,    11,    12,    13,    14,
      30,    43,    17,    18,     8,     9,    22,    23,    24,    25,
      -1,    15,     8,     9,    -1,    30,    23,    24,    25,     8,
       9,    -1,    26,    27,    -1,    -1,    30,    31,    32,    -1,
      26,    27,    28,    -1,    30,    31,    32,    26,    27,    15,
      -1,    30,    31,    32,    20,    21,    22,    23,    24,    25,
      15,    -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,
      25,    16,    -1,    -1,    -1,    20,    21,    22,    23,    24,
      25,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    21,    22,
      23,    24,    25
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    34,    35,     0,     3,     4,     5,     7,    36,    37,
      38,    40,    50,    36,    17,    39,    30,    10,    11,    12,
      13,    14,    17,    30,    44,    45,    48,    50,    27,     8,
       9,    15,    26,    27,    30,    31,    32,    48,    51,    27,
      27,    15,    15,    46,    19,    27,    18,    45,    15,    30,
      41,    42,    43,    50,    51,    51,     6,    15,    20,    21,
      22,    23,    24,    25,    51,    51,    44,    51,    28,    49,
      51,    47,    15,    19,    28,    16,    30,    28,    51,    51,
      51,    51,    51,    51,    28,    28,    18,    15,    28,    16,
      51,    42,    46,    46,    49,    15,    45,    45,    47,    47,
      29,    29,    46,    46,    45,    45,    47,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    36,    36,    37,    38,    39,    40,
      40,    41,    41,    42,    42,    43,    44,    44,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    46,    47,    48,    48,    49,    49,    50,    50,    50,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     0,     2,     2,     5,     4,     1,
       1,     0,     1,     1,     3,     2,     1,     2,     7,    11,
       7,    11,     4,     3,     5,     4,     2,     2,     3,     2,
       2,     0,     0,     4,     3,     1,     3,     1,     1,     1,
       3,     3,     3,     1,     1,     1,     2,     1,     1,     1,
       2,     3,     3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 2:
#line 173 "parser.ypp" /* yacc.c:1646  */
    {

   //TODO: check main
   if(!name_exists_in_table("main",*tables,true)){
      output::errorMainMissing();
      exit(0);
   }
   output::endScope();
   print_map_inc_offset(tables->top());
   pop_tables();
   pop_offsets();
}
#line 1467 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 186 "parser.ypp" /* yacc.c:1646  */
    {
      t = make_table(NULL);
      push_tables(t);
      push_offsets(0);
      vector<string> args_to_print;
      args_to_print.push_back(TYPE_STRING);
      insert("print", output::makeFunctionType(TYPE_VOID, args_to_print),0);
      args_to_print.clear();
      args_to_print.push_back(TYPE_INT);
      insert("printi", output::makeFunctionType(TYPE_VOID, args_to_print),0);
}
#line 1483 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 197 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1489 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 198 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1495 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 200 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1501 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 202 "parser.ypp" /* yacc.c:1646  */
    {
   //TODO: check if function and var may have the same name.
      if(name_exists_in_table((yyvsp[-3])->id_name,*tables)){
         output::errorDef(yylineno,(yyvsp[-3])->id_name);
         exit(0);
      }
      auto function_args = split_str((yyvsp[-1])->type, ",");
      insert((yyvsp[-3])->id_name,output::makeFunctionType((yyvsp[-4])->type, function_args),0);

      t = make_table(&top_tables());
      push_tables(t);
      push_offsets(top_offsets());

      auto id_names = split_str((yyvsp[-1])->id_name,",");
      auto types = split_str((yyvsp[-1])->type,",");

      assert(id_names.size() == types.size());
      auto it_names = id_names.begin();
      auto it_types = types.begin();
      int offset = 0;
      while (it_names != id_names.end() || it_types != types.end()) {
         insert(*it_names, *it_types, --offset);
         it_names++;
         it_types++;
      } 
}
#line 1532 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 228 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1538 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 229 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval) = new Expression();
                  (yyval)->type = (yyvsp[0])->type;
}
#line 1547 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 233 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval) = new Expression();
                  (yyval)->type = "void";
}
#line 1556 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 238 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval) = new Expression();
                  (yyval)->type = "";
                  (yyval)->id_name = "";
}
#line 1566 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 243 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->type = (yyvsp[0])->type;
                  (yyval)->id_name = (yyvsp[0])->id_name;
}
#line 1575 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 248 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->type = (yyvsp[0])->type;
                  (yyval)->id_name = (yyvsp[0])->id_name;
}
#line 1584 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 252 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->type= ((yyvsp[-2])->type).append(",").append((yyvsp[0])->type);
                  (yyval)->id_name= ((yyvsp[-2])->id_name).append(",").append((yyvsp[0])->id_name);
               }
#line 1593 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 257 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->type = (yyvsp[-1])->type;
                  (yyval)->id_name = (yyvsp[0])->id_name;
}
#line 1602 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 262 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1608 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 263 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1614 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 267 "parser.ypp" /* yacc.c:1646  */
    {
                  check_bool_exp(*(yyvsp[-4]));
               }
#line 1622 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 270 "parser.ypp" /* yacc.c:1646  */
    {
                  check_bool_exp(*(yyvsp[-8]));
               }
#line 1630 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 273 "parser.ypp" /* yacc.c:1646  */
    {
                  check_bool_exp(*(yyvsp[-4]));
               }
#line 1638 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 276 "parser.ypp" /* yacc.c:1646  */
    {
                  check_bool_exp(*(yyvsp[-8]));
               }
#line 1646 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 280 "parser.ypp" /* yacc.c:1646  */
    {
               }
#line 1653 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 282 "parser.ypp" /* yacc.c:1646  */
    {
                  if(name_exists_in_table((yyvsp[-1])->id_name,*tables)){
                     output::errorDef(yylineno,(yyvsp[-1])->id_name);
                     exit(0);
                  }
                  insert((yyvsp[-1])->id_name,(yyvsp[-2])->type, top_offsets());
                  top_offsets() += 1;
               }
#line 1666 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 290 "parser.ypp" /* yacc.c:1646  */
    {
                  if(name_exists_in_table((yyvsp[-3])->id_name,*tables)){
                     output::errorDef(yylineno,(yyvsp[-3])->id_name);
                     exit(0);
                  }
                  insert((yyvsp[-3])->id_name,(yyvsp[-4])->type, top_offsets());
                  top_offsets() += 1;
               }
#line 1679 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 298 "parser.ypp" /* yacc.c:1646  */
    {
                  if(!name_exists_in_table((yyvsp[-2])->id_name,*tables)){
                     output::errorUndef(yylineno,(yyvsp[-2])->id_name);
                     exit(0);
                  }
               }
#line 1690 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 304 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1696 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 305 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1702 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 306 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1708 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 307 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1714 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 308 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1720 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 310 "parser.ypp" /* yacc.c:1646  */
    {
      t = make_table(&top_tables());
      push_tables(t);
      push_offsets(top_offsets());
}
#line 1730 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 315 "parser.ypp" /* yacc.c:1646  */
    {
      output::endScope();
      print_map_inc_offset(tables->top());
      pop_tables();
      pop_offsets();
}
#line 1741 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 322 "parser.ypp" /* yacc.c:1646  */
    {
                     // Check if the function name exists
                     if(!name_exists_in_table((yyvsp[-3])->id_name, *tables, true)) {
                        output::errorUndefFunc(yylineno, (yyvsp[-3])->id_name);
                        exit(0);
                     }

                     // Check if given args matching the function args
                     string fun_sign = get_id_type((yyvsp[-3])->id_name ,*tables);
                     string ret_type = fun_sign.substr(fun_sign.find("->")+2, fun_sign.size()-1);
                     vector<string> function_args = split_str(fun_sign.substr(0,fun_sign.find("->")),",");
                     vector<string> given_args = split_str((yyvsp[-1])->type,",");
                     if(function_args != given_args){
                        output::errorPrototypeMismatch(yylineno,(yyvsp[-3])->id_name,function_args);
                        exit(0);
                     }
                     /* Rule #5 hw's PDF */
                     (yyval)->type = fun_sign.substr(fun_sign.find("->")+2, fun_sign.size()-1);
                  }
#line 1765 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 341 "parser.ypp" /* yacc.c:1646  */
    {
                  // Check if the function name exists
                  if(!name_exists_in_table((yyvsp[-2])->id_name, *tables, true)) {
                     output::errorUndefFunc(yylineno, (yyvsp[-2])->id_name);
                     exit(0);
                  }
                  string fun_sign = get_id_type((yyvsp[-2])->id_name ,*tables);
                  vector<string> function_args = split_str(fun_sign.substr(0,fun_sign.find("->")),",");
                  if(!function_args.empty()){
                     output::errorPrototypeMismatch(yylineno,(yyvsp[-2])->id_name,function_args);
                  }

                  /* Rule #5 hw's PDF */
                  (yyval)->type = fun_sign.substr(fun_sign.find("->")+2, fun_sign.size()-1);
               }
#line 1785 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 357 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->type = (yyvsp[0])->type;
}
#line 1793 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 360 "parser.ypp" /* yacc.c:1646  */
    {
                  //TODO: pass the value?
                  (yyval)->type = ((yyvsp[-2])->type).append(",").append((yyvsp[0])->type);
               }
#line 1802 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 365 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval) = new Expression();
                  (yyval)->type = TYPE_INT;
               }
#line 1811 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 369 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval) = new Expression();
                  (yyval)->type = TYPE_BYTE;
               }
#line 1820 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 373 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval) = new Expression();
                  (yyval)->type = TYPE_BOOL;
               }
#line 1829 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 378 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1835 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 379 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->type = binop(*(yyvsp[-2]), *(yyvsp[0]));
               }
#line 1843 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 382 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->type = binop(*(yyvsp[-2]), *(yyvsp[0]));
               }
#line 1851 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 385 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->type = get_id_type((yyvsp[0])->id_name, *tables);
               }
#line 1859 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 388 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->type = (yyvsp[0])->type;
               }
#line 1867 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 391 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->type = TYPE_INT;
                  (yyval)->number = (yyvsp[0])->number;
               }
#line 1876 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 395 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->number = (yyvsp[-1])->number;  
                  (yyval)->type = TYPE_BYTE;
               }
#line 1885 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 399 "parser.ypp" /* yacc.c:1646  */
    {
                  // String is an internal type
                  (yyval)->str=(yyvsp[0])->str;  
                  (yyval)->type= TYPE_STRING;
               }
#line 1895 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 404 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->bool_value=true;
                  (yyval)->type = TYPE_BOOL;
               }
#line 1904 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 408 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->bool_value=false;
                  (yyval)->type = TYPE_BOOL;
               }
#line 1913 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 412 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1919 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 413 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->type = log_eq(*(yyvsp[-2]), *(yyvsp[0]));
               }
#line 1927 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 416 "parser.ypp" /* yacc.c:1646  */
    {}
#line 1933 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 417 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->type = relop(*(yyvsp[-2]), *(yyvsp[0]));
               }
#line 1941 "parser.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 420 "parser.ypp" /* yacc.c:1646  */
    {
                  (yyval)->type = relop(*(yyvsp[-2]), *(yyvsp[0]));
               }
#line 1949 "parser.tab.cpp" /* yacc.c:1646  */
    break;


#line 1953 "parser.tab.cpp" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
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
  return yyresult;
}
#line 425 "parser.ypp" /* yacc.c:1906  */


/* Rule #8 hw's PDF */
string relop(Expression a, Expression b){
   if ((get_id_type(a.id_name,*tables) != TYPE_INT && get_id_type(a.id_name,*tables) != TYPE_BYTE)
   || (get_id_type(b.id_name,*tables) != TYPE_INT && get_id_type(b.id_name,*tables) != TYPE_BYTE)) {
      // Both must be numbers
      output::errorMismatch(yylineno);
      exit(0);
   }
   return TYPE_BOOL;
}


/* Rule #9 hw's PDF */
string log_eq(Expression a, Expression b){
   if (get_id_type(a.id_name,*tables) != TYPE_BOOL || get_id_type(b.id_name,*tables) != TYPE_BOOL) {
      // Both must be boolean
      output::errorMismatch(yylineno);
      exit(0);
   }
   return TYPE_BOOL;
}

/* Rule #10 hw's PDF */
string binop(Expression a, Expression b){
   if ((get_id_type(a.id_name,*tables) != TYPE_INT && (get_id_type(a.id_name,*tables) != TYPE_INT))
   || (get_id_type(b.id_name,*tables) != TYPE_BYTE && get_id_type(b.id_name,*tables) != TYPE_BYTE)) {
		// We allow: int&int, int&byte, byte&int or byte&byte
		output::errorMismatch(yylineno);
		exit(0);
	}
	if (get_id_type(a.id_name,*tables) == TYPE_INT || get_id_type(b.id_name,*tables) == TYPE_INT) {
      // If there is int, we will return int type
		return TYPE_INT;
	} else {
		return TYPE_BYTE;
	}
}

/* Rule #16 hw's PDF */
void check_bool_exp(Expression exp){
   if(exp.type == ""){
      return;
   }
   if(exp.type.compare(TYPE_BOOL)){
      output::errorMismatch(yylineno);
		exit(0);
   }
}




map<string,pair<string, int>>* make_table(map<string,pair<string, int>>* parent){
   // <Name, part<Type, Offset>>
   return new map<string,pair<string, int>>();
}
void pop_tables(){
   tables->pop();
}
void pop_offsets(){
   offsets->pop();
}
void push_tables(map<string,pair<string, int>>* table){
   tables->push(*table);
}
void push_offsets(int offset){
   offsets->push(offset);
}
map<string,pair<string, int>> &top_tables(){
   return tables->top();
}

int &top_offsets(){
   return offsets->top();
}

void insert(string name, string type,int offset){
   (tables->top()).insert({
         name,
         pair<string ,int>(type,offset)
   });
}

void yyerror(const char*){
   output::errorSyn(yylineno); 
}

int main(){
   tables = new stack<map<string,pair<string, int>>>();
   offsets = new stack<int>();
   return yyparse();
}



