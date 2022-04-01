#pragma once

#include <map>
#include <string>
#include "Boost.h"

namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;

using namespace std;

template<typename Iterator>
struct Skipper : qi::grammar<Iterator> {
  qi::rule<Iterator> skip;
  Skipper() : Skipper::base_type(skip) {
//    skip = ...
  }
};

template<typename Iterator>
struct LOLCodeGrammar : qi::grammar<Iterator, Skipper<Iterator>> {
  qi::rule<Iterator, Skipper<Iterator>> program;

  LOLCodeGrammar() : LOLCodeGrammar::base_type(program) {
//    program = ...
  }
};
