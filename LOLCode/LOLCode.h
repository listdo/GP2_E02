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
  qi::rule<Iterator, NUMBAR, Skipper<Iterator>> mathexpr, sum;

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
	  assignment = ident  [qi::_a = qi::_1]
		  >> "R"                 // v-------- NEEDED: phoenix::bind needed to call set_variable
		  >> mathexpr     [phoenix::bind(&set_variable, qi::_a, qi::_1)];
	  stat = visible | mathexpr | vardecl | assignment; // mathexpr -> expr == mathexpr | boolexpr
	  mathexpr = sum | qi::double_; // ^------^------ ADDED: vardecl | assignment
	  sum = qi::lit("SUM")
		  >> "OF"
		  >> mathexpr [qi::_val = qi::_1]
		  >> -qi::lit("AN")
		  >> mathexpr [qi::_val += qi::_1];
	  visible = qi::lit("VISIBLE") // think about VISIBLE ..... ! (newline y/n?)
		  >> (  string_literal     [cout << qi::_1 << endl]
			  // v----- switched order of mathexpr and ident
			  | mathexpr           [print_value()] // <------- IMPORTANT: order of alternatives
			  | ident              [print_variable()] // <---- IMPORTANT: order of alternatives
			  );
	  ident = qi::lexeme[qi::alpha >> *(qi::alnum | '_')];
	  string_literal = qi::lexeme['"' >> *(qi::char_ - '"') >> '"'];
  }
};
