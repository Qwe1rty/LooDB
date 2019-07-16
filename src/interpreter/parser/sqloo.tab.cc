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
#line 29 "sqloo.yy" // lalr1.cc:413

  #include "Parser.h"

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
      case 26: // INT
        value.move< int > (that.value);
        break;

      case 27: // STRING
      case 37: // restrictions
      case 38: // restriction
      case 42: // col
      case 47: // text
        value.move< std::string > (that.value);
        break;

      case 36: // column
        value.move< std::tuple<std::string, EntryType, std::string> > (that.value);
        break;

      case 46: // entry
        value.move< std::unique_ptr<Entry> > (that.value);
        break;

      case 43: // whereExpr
      case 44: // whereTerm
      case 45: // whereFactor
        value.move< std::unique_ptr<SQLSelect::WhereTree> > (that.value);
        break;

      case 30: // statement
      case 31: // create
      case 32: // drop
      case 33: // insert
      case 34: // select
        value.move< std::unique_ptr<SQLStatement> > (that.value);
        break;

      case 41: // cols
        value.move< std::vector<std::string> > (that.value);
        break;

      case 35: // columns
        value.move< std::vector<std::tuple<std::string, EntryType, std::string>> > (that.value);
        break;

      case 39: // row
      case 40: // entries
        value.move< std::vector<std::unique_ptr<Entry>> > (that.value);
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
      case 26: // INT
        value.copy< int > (that.value);
        break;

      case 27: // STRING
      case 37: // restrictions
      case 38: // restriction
      case 42: // col
      case 47: // text
        value.copy< std::string > (that.value);
        break;

      case 36: // column
        value.copy< std::tuple<std::string, EntryType, std::string> > (that.value);
        break;

      case 46: // entry
        value.copy< std::unique_ptr<Entry> > (that.value);
        break;

      case 43: // whereExpr
      case 44: // whereTerm
      case 45: // whereFactor
        value.copy< std::unique_ptr<SQLSelect::WhereTree> > (that.value);
        break;

      case 30: // statement
      case 31: // create
      case 32: // drop
      case 33: // insert
      case 34: // select
        value.copy< std::unique_ptr<SQLStatement> > (that.value);
        break;

      case 41: // cols
        value.copy< std::vector<std::string> > (that.value);
        break;

      case 35: // columns
        value.copy< std::vector<std::tuple<std::string, EntryType, std::string>> > (that.value);
        break;

      case 39: // row
      case 40: // entries
        value.copy< std::vector<std::unique_ptr<Entry>> > (that.value);
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
    YYUSE (yytype);
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
      case 26: // INT
        yylhs.value.build< int > ();
        break;

      case 27: // STRING
      case 37: // restrictions
      case 38: // restriction
      case 42: // col
      case 47: // text
        yylhs.value.build< std::string > ();
        break;

      case 36: // column
        yylhs.value.build< std::tuple<std::string, EntryType, std::string> > ();
        break;

      case 46: // entry
        yylhs.value.build< std::unique_ptr<Entry> > ();
        break;

      case 43: // whereExpr
      case 44: // whereTerm
      case 45: // whereFactor
        yylhs.value.build< std::unique_ptr<SQLSelect::WhereTree> > ();
        break;

      case 30: // statement
      case 31: // create
      case 32: // drop
      case 33: // insert
      case 34: // select
        yylhs.value.build< std::unique_ptr<SQLStatement> > ();
        break;

      case 41: // cols
        yylhs.value.build< std::vector<std::string> > ();
        break;

      case 35: // columns
        yylhs.value.build< std::vector<std::tuple<std::string, EntryType, std::string>> > ();
        break;

      case 39: // row
      case 40: // entries
        yylhs.value.build< std::vector<std::unique_ptr<Entry>> > ();
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
#line 74 "sqloo.yy" // lalr1.cc:859
    {
    p.result = std::move(yystack_[0].value.as< std::unique_ptr<SQLStatement> > ());
    YYACCEPT;
  }
#line 595 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 3:
#line 81 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLStatement> > () = std::move(yystack_[0].value.as< std::unique_ptr<SQLStatement> > ());
  }
#line 603 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 4:
#line 84 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLStatement> > () = std::move(yystack_[0].value.as< std::unique_ptr<SQLStatement> > ());
  }
#line 611 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 5:
#line 87 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLStatement> > () = std::move(yystack_[0].value.as< std::unique_ptr<SQLStatement> > ());
  }
#line 619 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 90 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLStatement> > () = std::move(yystack_[0].value.as< std::unique_ptr<SQLStatement> > ()); 
  }
#line 627 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 96 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLStatement> > () = std::make_unique<SQLCreate>(std::move(yystack_[4].value.as< std::string > ()), std::move(yystack_[2].value.as< std::vector<std::tuple<std::string, EntryType, std::string>> > ()));
  }
#line 635 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 102 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLStatement> > () = std::make_unique<SQLDrop>(std::move(yystack_[1].value.as< std::string > ()));
  }
#line 643 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 108 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLStatement> > () = std::make_unique<SQLInsert>(std::move(yystack_[3].value.as< std::string > ()), std::move(yystack_[1].value.as< std::vector<std::unique_ptr<Entry>> > ()));
  }
#line 651 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 114 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLStatement> > () = std::make_unique<SQLSelect>(std::move(yystack_[1].value.as< std::string > ()), std::move(yystack_[3].value.as< std::vector<std::string> > ()), false, nullptr);
  }
#line 659 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 117 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLStatement> > () = std::make_unique<SQLSelect>(std::move(yystack_[3].value.as< std::string > ()), std::move(yystack_[5].value.as< std::vector<std::string> > ()), true, std::move(yystack_[1].value.as< std::unique_ptr<SQLSelect::WhereTree> > ()));
  }
#line 667 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 123 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::vector<std::tuple<std::string, EntryType, std::string>> > ().emplace_back(std::move(yystack_[0].value.as< std::tuple<std::string, EntryType, std::string> > ()));
  }
#line 675 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 126 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::vector<std::tuple<std::string, EntryType, std::string>> > ().emplace_back(std::move(yystack_[0].value.as< std::tuple<std::string, EntryType, std::string> > ()));
  }
#line 683 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 132 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::tuple<std::string, EntryType, std::string> > () = std::make_tuple(std::move(yystack_[2].value.as< std::string > ()), EntryType::INTEGER, std::move(yystack_[0].value.as< std::string > ()));
  }
#line 691 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 135 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::tuple<std::string, EntryType, std::string> > () = std::make_tuple(std::move(yystack_[2].value.as< std::string > ()), EntryType::TEXT, std::move(yystack_[0].value.as< std::string > ()));
  }
#line 699 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 141 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::string > () = "";
  }
#line 707 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 144 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::string > () = std::move(yystack_[0].value.as< std::string > ());
  }
#line 715 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 147 "sqloo.yy" // lalr1.cc:859
    {
    if (yystack_[1].value.as< std::string > () != yystack_[0].value.as< std::string > ()) {
      yylhs.value.as< std::string > () = yystack_[1].value.as< std::string > () + ", " + yystack_[0].value.as< std::string > ();
    } else {
      std::cerr << "Parse error: duplicate restriction" << std::endl;
      YYERROR;
    }
  }
#line 728 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 158 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::string > () = "primary key";
  }
#line 736 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 161 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::string > () = "not null";
  }
#line 744 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 167 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::vector<std::unique_ptr<Entry>> > () = std::move(yystack_[1].value.as< std::vector<std::unique_ptr<Entry>> > ());
  }
#line 752 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 173 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::vector<std::unique_ptr<Entry>> > ().emplace_back(std::move(yystack_[0].value.as< std::unique_ptr<Entry> > ()));
  }
#line 760 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 176 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::vector<std::unique_ptr<Entry>> > ().emplace_back(std::move(yystack_[0].value.as< std::unique_ptr<Entry> > ()));
  }
#line 768 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 182 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::vector<std::string> > ().emplace_back("*");
  }
#line 776 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 25:
#line 185 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::vector<std::string> > ().emplace_back(std::move(yystack_[0].value.as< std::string > ()));
  }
#line 784 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 188 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::vector<std::string> > ().emplace_back(std::move(yystack_[0].value.as< std::string > ()));
  }
#line 792 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 194 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::string > () = std::move(yystack_[0].value.as< std::string > ());
  }
#line 800 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 200 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLSelect::WhereTree> > () = std::move(yystack_[0].value.as< std::unique_ptr<SQLSelect::WhereTree> > ());
  }
#line 808 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 203 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLSelect::WhereTree> > () = std::make_unique<SQLSelect::WhereTree>("OR", std::move(yystack_[2].value.as< std::unique_ptr<SQLSelect::WhereTree> > ()), std::move(yystack_[0].value.as< std::unique_ptr<SQLSelect::WhereTree> > ()));
  }
#line 816 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 209 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLSelect::WhereTree> > () = std::move(yystack_[0].value.as< std::unique_ptr<SQLSelect::WhereTree> > ());
  }
#line 824 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 212 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLSelect::WhereTree> > () = std::make_unique<SQLSelect::WhereTree>("AND", std::move(yystack_[2].value.as< std::unique_ptr<SQLSelect::WhereTree> > ()), std::move(yystack_[0].value.as< std::unique_ptr<SQLSelect::WhereTree> > ()));
  }
#line 832 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 218 "sqloo.yy" // lalr1.cc:859
    {
    // std::cout << $1 << "=" << $3->getType() << std::endl;
    yylhs.value.as< std::unique_ptr<SQLSelect::WhereTree> > () = std::make_unique<SQLSelect::WhereTree>(std::move(yystack_[2].value.as< std::string > ()), std::move(yystack_[0].value.as< std::unique_ptr<Entry> > ()));
  }
#line 841 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 33:
#line 222 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<SQLSelect::WhereTree> > () = std::move(yystack_[1].value.as< std::unique_ptr<SQLSelect::WhereTree> > ());
  }
#line 849 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 34:
#line 228 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<Entry> > () = std::make_unique<NullEntry>();
  }
#line 857 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 35:
#line 231 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<Entry> > () = std::make_unique<IntEntry>(std::move(yystack_[0].value.as< int > ()));
  }
#line 865 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 234 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::unique_ptr<Entry> > () = std::make_unique<StringEntry>(std::move(yystack_[0].value.as< std::string > ()));
  }
#line 873 "sqloo.tab.cc" // lalr1.cc:859
    break;

  case 37:
#line 240 "sqloo.yy" // lalr1.cc:859
    {
    yylhs.value.as< std::string > () = std::move(yystack_[1].value.as< std::string > ());
  }
#line 881 "sqloo.tab.cc" // lalr1.cc:859
    break;


#line 885 "sqloo.tab.cc" // lalr1.cc:859
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


  const signed char parser::yypact_ninf_ = -48;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
      -3,    -7,    10,   -14,    -6,    12,   -48,   -48,   -48,   -48,
     -48,   -20,     5,     8,   -48,   -48,     7,   -48,   -48,    31,
      34,    19,    11,    14,    15,   -48,    35,   -48,     1,    17,
      13,   -48,    -1,    40,   -48,    -5,    18,    18,    15,    41,
      20,   -48,   -48,    22,   -48,   -48,   -48,    -5,    36,    -2,
      24,   -48,   -48,   -48,   -48,    18,   -48,   -48,   -48,    39,
      -1,   -48,     2,    -1,   -48,    -5,    -5,   -48,   -48,   -48,
     -48,   -48,    24,   -48
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     2,     3,     4,     5,
       6,     0,     0,     0,    24,    27,     0,    26,     1,     0,
       0,     0,     0,     0,     0,     8,     0,    25,     0,     0,
       0,    13,     0,     0,    10,     0,    16,    16,     0,     0,
       0,    34,    35,     0,    23,    36,     9,     0,     0,     0,
      28,    30,    19,    20,    14,    17,    15,    12,     7,     0,
       0,    21,     0,     0,    11,     0,     0,    18,    37,    22,
      33,    32,    29,    31
  };

  const signed char
  parser::yypgoto_[] =
  {
     -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,    16,    21,
      -4,   -48,   -48,   -48,    27,     3,   -13,   -11,   -47,   -48
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     5,     6,     7,     8,     9,    10,    30,    31,    54,
      55,    33,    43,    16,    17,    49,    50,    51,    44,    45
  };

  const unsigned char
  parser::yytable_[] =
  {
      47,    64,    14,    11,    34,    13,    40,    19,    70,     1,
      41,    22,    18,    69,     2,     3,    71,    38,     4,    39,
      12,    15,    48,    65,    35,    42,    60,    65,    61,    23,
      36,    37,    20,    52,    53,    21,    24,    25,    15,    26,
      32,    28,    29,    46,    58,    63,    68,    59,    66,    27,
      62,    67,    72,     0,    57,    73,     0,     0,    56
  };

  const signed char
  parser::yycheck_[] =
  {
       5,     3,     8,    10,     3,    19,     7,    27,     6,    12,
      11,     4,     0,    60,    17,    18,    63,     4,    21,     6,
      10,    27,    27,    25,    23,    26,     4,    25,     6,    22,
      13,    14,    27,    15,    16,    27,     5,     3,    27,    20,
       5,    27,    27,     3,     3,     9,     7,    27,    24,    22,
      47,    55,    65,    -1,    38,    66,    -1,    -1,    37
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    12,    17,    18,    21,    29,    30,    31,    32,    33,
      34,    10,    10,    19,     8,    27,    41,    42,     0,    27,
      27,    27,     4,    22,     5,     3,    20,    42,    27,    27,
      35,    36,     5,    39,     3,    23,    13,    14,     4,     6,
       7,    11,    26,    40,    46,    47,     3,     5,    27,    43,
      44,    45,    15,    16,    37,    38,    37,    36,     3,    27,
       4,     6,    43,     9,     3,    25,    24,    38,     7,    46,
       6,    46,    44,    45
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    28,    29,    30,    30,    30,    30,    31,    32,    33,
      34,    34,    35,    35,    36,    36,    37,    37,    37,    38,
      38,    39,    40,    40,    41,    41,    41,    42,    43,    43,
      44,    44,    45,    45,    46,    46,    46,    47
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     7,     4,     6,
       5,     7,     3,     1,     3,     3,     0,     1,     2,     1,
       1,     3,     3,     1,     1,     3,     1,     1,     1,     3,
       1,     3,     3,     3,     1,     1,     1,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"EOF\"", "error", "$undefined", "\";\"", "\",\"", "\"(\"", "\")\"",
  "\"'\"", "\"*\"", "\"=\"", "\"table\"", "\"null\"", "\"create\"",
  "\"integer\"", "\"text\"", "\"primary key\"", "\"not null\"", "\"drop\"",
  "\"insert\"", "\"into\"", "\"values\"", "\"select\"", "\"from\"",
  "\"where\"", "\"and\"", "\"or\"", "INT", "STRING", "$accept", "sqloo",
  "statement", "create", "drop", "insert", "select", "columns", "column",
  "restrictions", "restriction", "row", "entries", "cols", "col",
  "whereExpr", "whereTerm", "whereFactor", "entry", "text", YY_NULLPTR
  };


  const unsigned char
  parser::yyrline_[] =
  {
       0,    74,    74,    81,    84,    87,    90,    96,   102,   108,
     114,   117,   123,   126,   132,   135,   141,   144,   147,   158,
     161,   167,   173,   176,   182,   185,   188,   194,   200,   203,
     209,   212,   218,   222,   228,   231,   234,   240
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
#line 1202 "sqloo.tab.cc" // lalr1.cc:1167
#line 244 "sqloo.yy" // lalr1.cc:1168


void yy::parser::error (const std::string& m) {
  std::cerr << "Parse error: " << m << std::endl;
}
