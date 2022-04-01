#pragma once

#include "Boost.h"

namespace qi = boost::spirit::qi;

template<typename Iterator>
struct JsonGrammar : qi::grammar<Iterator, qi::space_type> {
  typedef qi::rule<Iterator, qi::space_type> rule;

  rule json;

  JsonGrammar() : JsonGrammar::base_type(json) {
//    json = ...
  }
};
