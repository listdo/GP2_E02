#include <iostream>
#include <string>
#include "Calculator.h"

namespace qi = boost::spirit::qi;

using namespace std;

void testSimpleCalc() {
  cout << "--- Simple Calculator Test ---" << endl;

  string input("(4 / 2 + 5) * 0.5 - 1.4"); // 2.1
  auto iter = input.begin();
  auto end = input.end();
  SimpleCalcGrammar<decltype(iter)> grammar;

  cout << "parsing ... ";
  bool success = qi::phrase_parse(iter, end, grammar, qi::space) /*&& iter == end */;
  cout << (success ? "SUCCESS" : "FAILURE") << endl;

  cout << "------------------------------------------------" << endl << endl;
}

void testAdvancedCalc() {
  cout << "--- Advanced Calculator Test ---" << endl;

  string input("(4 / 2 + 5) * 0.5 - 1.4"); // 2.1
  double output = 0.0;
  auto iter = input.begin();
  auto end = input.end();
  AdvancedCalcGrammar<decltype(iter)> grammar;

  cout << "parsing ... ";
  bool success = qi::phrase_parse(iter, end, grammar, qi::space, output) && iter == end;
  cout << (success ? "SUCCESS" : "FAILURE") << endl;
  cout << "output: " << output << endl;

  cout << "------------------------------------------------" << endl << endl;
}

int main() {
  testSimpleCalc();
  testAdvancedCalc();
}
