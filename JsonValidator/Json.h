#pragma once

#include "Boost.h"

namespace qi = boost::spirit::qi;

template<typename Iterator>
struct JsonGrammar : qi::grammar<Iterator, qi::space_type> {
  typedef qi::rule<Iterator, qi::space_type> rule;

  rule json, element, member, ident, number, doubleValue, arr, value, stringValue, troof;

  JsonGrammar() : JsonGrammar::base_type(json) {

      json = qi::lit("{")
          >> *member
          >> "}";

      member = 
          ident >> ":" >> "{" >> *member >> "}" >> -qi::lit(",") |
          ident >> ":" >> doubleValue >> -qi::lit(",") |
          ident >> ":" >> stringValue >> -qi::lit(",") |
          ident >> ":" >> number >> -qi::lit(",") |
          ident >> ":" >> arr >> -qi::lit(",") |
          ident >> ":" >> troof >> -qi::lit(",")
          ;

      arr = qi::lit("[") >> *(doubleValue >> -qi::lit(",")) >> "]" |
            qi::lit("[") >> *(stringValue >> -qi::lit(",")) >> "]" |
            qi::lit("[") >> *(number >> -qi::lit(",")) >> "]" |
            qi::lit("[") >> *(troof >> -qi::lit(",")) >> "]"
            ;

      ident = qi::lit("\"") >> qi::lexeme[qi::alpha >> *(qi::alnum | '_')] >> qi::lit("\"");
      number = qi::lexeme[qi::int_];
      doubleValue = qi::lexeme[qi::double_];
      troof = qi::lexeme[qi::bool_];

      stringValue = qi::lit("\"") >> qi::lexeme[*(qi::alnum |
                                                  qi::char_(' ') |
                                                  qi::char_('/') |
                                                  qi::char_(':') |
                                                  qi::char_('.'))]
                                  >> qi::lit("\"");
  }
};
