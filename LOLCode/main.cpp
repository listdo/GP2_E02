#include <iostream>
#include <string>
#include "LOLCode.h"

namespace qi = boost::spirit::qi;

using namespace std;

string testCode1(
  "HAI\n"
  "CAN HAS STDIO?\n"
  "VISIBLE \"HAI WORLD!\"\n"
  "KTHXBYE"
);

string testCode2(
  "HAI\n"
  "BTW was up?\n"
  "OBTW bla bla\n"
  "bla bla TLDR\n"
  "OBTW i can nestd?\n"
  "OBTW yes, i can TLDR\n"
  "TLDR\n"
  "KTHXBYE"
);

string testCode3(
  "HAI\n"
  "BTW i'm a comment\n"
  "I   HAS  A    answer             BTW declare variable\n"
  "answer R 21.0                    BTW assign value\n"
  "VISIBLE answer                   BTW print value\n"
  "answer R SUM OF 21.6 AN 20.4     BTW add two values and assign result\n"
  "VISIBLE answer\n"
  "VISIBLE SUM OF 1 AN SUM OF 0.3 0.037\n"
  "I HAS A truth\n"
  "truth R BOTH OF WIN WIN\n"
  "VISIBLE truth\n"
  "BOTH OF WIN AN FAIL\n"
  "VISIBLE IT\n"
  "VISIBLE \"iz coffeh tiem!\"\n"
  "KTHXBYE"
);

string testCode4(
  "HAI\n"
  // TODO: implement additional tests
  "KTHXBYE"
);

void testLOLCode(string description, string code) {
  cout << "--- " << description << " ---" << endl;

  auto iter = code.begin();
  auto end = code.end();
  Skipper<decltype(iter)> skipper;
  LOLCodeGrammar<decltype(iter)> grammar;

  cout << "parsing ..." << endl;
  bool success = qi::phrase_parse(iter, end, grammar, skipper) && iter == end;
  cout << (success ? "SUCCESS" : "FAILURE") << endl;

  cout << "------------------------------------------------" << endl << endl;
}

int main() {
  testLOLCode("LOLCODE Test 1 (Hello World)", testCode1);
  testLOLCode("LOLCODE Test 2 (Comments)", testCode2);
  testLOLCode("LOLCODE Test 3 (Simple LOLCODE Program)", testCode3);
//  testLOLCode("TODO: Implement additional tests", testCode4);
}