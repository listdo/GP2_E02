#pragma once

#include "Boost.h"

namespace qi = boost::spirit::qi;

template<typename Iterator>
struct SimpleCalcGrammar : qi::grammar<Iterator, qi::space_type> {
  typedef qi::rule<Iterator, qi::space_type> rule;
  rule expr, term, fact;

  SimpleCalcGrammar() : SimpleCalcGrammar::base_type(expr) {
//    expr = ...
  }
};

template<typename Iterator>
struct AdvancedCalcGrammar : qi::grammar<Iterator, double(), qi::space_type> {
  typedef qi::rule<Iterator, double(), qi::space_type> rule;
  rule expr, term, fact;

  AdvancedCalcGrammar() : AdvancedCalcGrammar::base_type(expr) {
//    expr = ...
  }
};
