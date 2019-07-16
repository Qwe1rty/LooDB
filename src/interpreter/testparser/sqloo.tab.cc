// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "sqloo.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "sqloo.tab.hh"

// User implementation prologue.

#line 51 "sqloo.tab.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 17 "sqloo.yy" // lalr1.cc:413

# include "Parser.h"

#line 57 "sqloo.tab.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 124 "sqloo.tab.cc" // lalr1.cc:479

  /// Build a parser object.
  parser::parser (Parser& p_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      p (p_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
      switch (that.type_get ())
    {
      case 15: // INT
        value.move< int > (that.value);
        break;

      case 16: // STRING
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 15: // INT
        value.copy< int > (that.value);
        break;

      case 16: // STRING
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    switch (yytype)
    {
            case 15: // INT

#line 41 "sqloo.yy" // lalr1.cc:636
        { yyo << yysym.value.template as< int > (); }
#line 267 "sqloo.tab.cc" // lalr1.cc:636
        break;

      case 16: // STRING

#line 41 "sqloo.yy" // lalr1.cc:636
        { yyo << yysym.value.template as< std::string > (); }
#line 274 "sqloo.tab.cc" // lalr1.cc:636
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (p));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 15: // INT
        yylhs.value.build< int > ();
        break;

      case 16: // STRING
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 48 "sqloo.yy" // lalr1.cc:859
    {}
#line 494 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 3:
#line 51 "sqloo.yy" // lalr1.cc:859
    {}
#line 500 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 4:
#line 52 "sqloo.yy" // lalr1.cc:859
    {}
#line 506 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 5:
#line 55 "sqloo.yy" // lalr1.cc:859
    {}
#line 512 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 56 "sqloo.yy" // lalr1.cc:859
    {}
#line 518 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 57 "sqloo.yy" // lalr1.cc:859
    {}
#line 524 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 60 "sqloo.yy" // lalr1.cc:859
    {
    std::cout << "creating table " << yystack_[1].value.as< std::string > () << std::endl;
  }
#line 532 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 65 "sqloo.yy" // lalr1.cc:859
    {
    std::cout << "dropping table " << yystack_[1].value.as< std::string > () << std::endl;
  }
#line 540 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 70 "sqloo.yy" // lalr1.cc:859
    {
    std::cout << "inserting " << std::endl;
  }
#line 548 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 75 "sqloo.yy" // lalr1.cc:859
    {}
#line 554 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 76 "sqloo.yy" // lalr1.cc:859
    {}
#line 560 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 79 "sqloo.yy" // lalr1.cc:859
    {}
#line 566 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 82 "sqloo.yy" // lalr1.cc:859
    {}
#line 572 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 83 "sqloo.yy" // lalr1.cc:859
    {}
#line 578 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 86 "sqloo.yy" // lalr1.cc:859
    {}
#line 584 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 87 "sqloo.yy" // lalr1.cc:859
    {}
#line 590 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 88 "sqloo.yy" // lalr1.cc:859
    {}
#line 596 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 91 "sqloo.yy" // lalr1.cc:859
    {
    std::cout << "StringEntry: " << yystack_[1].value.as< std::string > () << std::endl;
  }
#line 604 "sqloo.tab.cc" // lalr1.cc:859
    break;


#line 608 "sqloo.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -14;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      -6,   -11,    -2,     1,    13,    -6,   -14,   -14,   -14,   -14,
      -1,     0,     3,   -14,   -14,    11,    14,     7,   -14,   -14,
      16,    -7,     2,   -14,     6,   -14,   -14,     5,   -14,   -14,
     -14,    16,    17,    -7,   -14,   -14,   -14,   -14
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     2,     4,     5,     6,     7,
       0,     0,     0,     1,     3,     0,     0,     0,     8,     9,
       0,     0,     0,    12,     0,    16,    17,     0,    15,    18,
      10,     0,     0,     0,    13,    11,    19,    14
  };

  const signed char
  parser::yypgoto_[] =
  {
     -14,   -14,   -14,    18,   -14,   -14,   -14,   -14,   -13,   -14,
      -8,   -14
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,     8,     9,    22,    23,    27,
      28,    29
  };

  const unsigned char
  parser::yytable_[] =
  {
      24,    10,     1,     2,     3,    30,    31,    25,    26,    33,
      11,    34,    12,    13,    18,    15,    16,    19,    35,    17,
      20,    21,    32,    14,    36,    37
  };

  const unsigned char
  parser::yycheck_[] =
  {
       7,    12,     8,     9,    10,     3,     4,    14,    15,     4,
      12,     6,    11,     0,     3,    16,    16,     3,    31,    16,
      13,     5,    16,     5,     7,    33
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     8,     9,    10,    18,    19,    20,    21,    22,    23,
      12,    12,    11,     0,    20,    16,    16,    16,     3,     3,
      13,     5,    24,    25,     7,    14,    15,    26,    27,    28,
       3,     4,    16,     4,     6,    25,     7,    27
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    17,    18,    19,    19,    20,    20,    20,    21,    22,
      23,    24,    24,    25,    26,    26,    27,    27,    27,    28
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     1,     1,     1,     4,     4,
       6,     3,     1,     3,     3,     1,     1,     1,     1,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"EOF\"", "error", "$undefined", "\";\"", "\",\"", "\"(\"", "\")\"",
  "\"'\"", "\"create\"", "\"drop\"", "\"insert\"", "\"into\"", "\"table\"",
  "\"values\"", "\"null\"", "INT", "STRING", "$accept", "sqloo",
  "statements", "statement", "create", "drop", "insert", "rows", "row",
  "values", "value", "text", YY_NULLPTR
  };


  const unsigned char
  parser::yyrline_[] =
  {
       0,    48,    48,    51,    52,    55,    56,    57,    60,    65,
      70,    75,    76,    79,    82,    83,    86,    87,    88,    91
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 898 "sqloo.tab.cc" // lalr1.cc:1167
#line 95 "sqloo.yy" // lalr1.cc:1168


void yy::parser::error (const std::string& m) {
  std::cerr << "Parse error: " << m << std::endl;
}
