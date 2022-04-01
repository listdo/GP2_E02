#include <iostream>
#include <string>
#include "Json.h"

namespace qi = boost::spirit::qi;

using namespace std;

string testCode1(
  "{\n"
  "  \"Image\": {\n"
  "    \"Width\": 800,\n"
  "    \"Height\": 600,\n"
  "    \"Title\": \"View from 15th Floor\",\n"
  "    \"Opacity\": 0.5,\n"
  "    \"Thumbnail\": {\n"
  "      \"Url\": \"http://www.example.com/image/481989943\",\n"
  "      \"Height\": 125,\n"
  "      \"Width\": 100\n"
  "    },\n"
  "    \"Location\": {\n"
  "      \"Latitude\": 37.7668,\n"
  "      \"Longitude\": -122.3959\n"
  "    },\n"
  "    \"Animated\": false,\n"
  "    \"IDs\": [116, 943, 234, 38793]\n"
  "  }\n"
  "}"
);

string testCode2(
  "{\n"
  // TODO: implement additional tests
  "}"
);

void testJson(string description, string code) {
  cout << "--- " << description << " ---" << endl;

  auto iter = code.begin();
  auto end = code.end();
  JsonGrammar<decltype(iter)> grammar;

  cout << "parsing ..." << endl;
  bool success = qi::phrase_parse(iter, end, grammar, qi::space) && iter == end;
  cout << (success ? "SUCCESS" : "FAILURE") << endl;

  cout << "------------------------------------------------" << endl << endl;
}

int main() {
  testJson("JSON Validator Test 1", testCode1);
//  testJson("TODO: Implement additional tests", testCode2);
}
