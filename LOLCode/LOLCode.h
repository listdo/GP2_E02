#pragma once

#include <map>
#include <string>
#include "Boost.h"

namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;

using namespace std;

typedef double NUMBAR;
typedef bool TROOF;

typedef typename boost::variant<TROOF, NUMBAR> vartype;

map<string, vartype> variables;

struct new_variable {
	void operator()(string const & var) const {
		variables[var] = 0.0;
	}
};

struct values_visitor : public boost::static_visitor<string> {
	string operator()(TROOF value) const {
		return value ? "WIN" : "FAIL";
	}
	string operator()(NUMBAR value) const {
		return to_string(value);
	}
};

struct print_variable {
	void operator()(string const & var) const {
		cout << boost::apply_visitor(values_visitor(), variables[var]) << endl;
	}
};

struct print_value {
	void operator()(vartype const & value) const {
		cout << boost::apply_visitor(values_visitor(), value) << endl;
	}
};

template<typename Iterator>
struct Skipper : qi::grammar<Iterator> {
  qi::rule<Iterator> skip;
  Skipper() : Skipper::base_type(skip) {
	  skip = qi::space
		  | "BTW" >> *(qi::char_ - qi::eol - qi::eoi)
		  | "OBTW" >> *(skip | qi::char_ - "TLDR" - qi::eoi) >> "TLDR";
  }
};

void set_variable(string const & var, vartype const & val) {
	cout << var << " " << val << endl;
	variables[var] = val;
}

template<typename Iterator>
struct LOLCodeGrammar : qi::grammar<Iterator, Skipper<Iterator>> {
  qi::rule<Iterator, Skipper<Iterator>> program, include, stat, visible, vardecl;
  qi::rule<Iterator, string(), Skipper<Iterator>> ident, string_literal;
  qi::rule<Iterator, Skipper<Iterator>, qi::locals<string>> assignment;
  qi::rule<Iterator, NUMBAR, Skipper<Iterator>> mathexpr, sum, mul, div;
  qi::rule<Iterator, TROOF, Skipper<Iterator>> boolexpr, both, either, won, not;

  LOLCodeGrammar() : LOLCodeGrammar::base_type(program) {
	  program = qi::lit("HAI")
		  >> -include
		  >> *stat
		  >> "KTHXBYE";

	  include = qi::lit("CAN")
		  >> "HAS"
		  >> ident
		  >> "?";

	  vardecl = qi::lit("I")
		  >> "HAS"
		  >> "A"
		  >> ident [new_variable()];

	  assignment = ident[qi::_a = qi::_1]
		  >> "R"                 // v-------- NEEDED: phoenix::bind needed to call set_variable
		  >> mathexpr[phoenix::bind(&set_variable, qi::_a, qi::_1)] |
			 boolexpr[phoenix::bind(&set_variable, qi::_a, qi::_1)];
	  
	  stat = visible | mathexpr | boolexpr | vardecl | assignment; // mathexpr -> expr == mathexpr | boolexpr	 
	  
	  mathexpr = div | mul | sum | qi::double_; // ^------^------ ADDED: vardecl | assignment
	  
	  boolexpr = both | either | won | not |
				 qi::bool_;
		  
	  both = qi::lit("BOTH")
		  >> "OF"
		  >> boolexpr[qi::_val = qi::_1]
		  >> qi::lit("AN")
		  >> boolexpr[qi::_val = (qi::_val && qi::_1)];

	  either = qi::lit("EITHER")
		  >> "OF"
		  >> boolexpr[qi::_val = qi::_1]
		  >> qi::lit("AN")
		  >> boolexpr[qi::_val = (qi::_val || qi::_1)];

	  won = qi::lit("WON")
		  >> "OF"
		  >> boolexpr[qi::_val = qi::_1]
		  >> qi::lit("AN")
		  >> boolexpr[qi::_val = (qi::_val && !qi::_1) || (!qi::_val && qi::_1)];

	  not = qi::lit("NOT")
		  >> boolexpr[qi::_val = !qi::_1];
	  
	  mul = qi::lit("MUL")
		  >> "OF"
		  >> mathexpr[qi::_val = qi::_1]
		  >> -qi::lit("AN")
		  >> mathexpr[qi::_val *= qi::_1];

	  div = qi::lit("DIV")
		  >> "OF"
		  >> mathexpr[qi::_val = qi::_1]
		  >> -qi::lit("AN")
		  >> mathexpr[qi::_val /= qi::_1];

	  sum = qi::lit("SUM")
		  >> "OF"
		  >> mathexpr [qi::_val = qi::_1]
		  >> -qi::lit("AN")
		  >> mathexpr [qi::_val += qi::_1];
	  
	  visible = qi::lit("VISIBLE") // think about VISIBLE ..... ! (newline y/n?)
		  >> (  string_literal     [cout << qi::_1 << endl]
			  // v----- switched order of mathexpr and ident
			  | boolexpr		   [print_value()]
			  | mathexpr           [print_value()] // <------- IMPORTANT: order of alternatives
			  | ident              [print_variable()] // <---- IMPORTANT: order of alternatives
			  );

	  ident = qi::lexeme[qi::alpha >> *(qi::alnum | '_')];
	  string_literal = qi::lexeme['"' >> *(qi::char_ - '"') >> '"'];
  }
};
