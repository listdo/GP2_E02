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
  "    \"Title\": \"View from 15th Floor\",\n" //View from 15th Floor
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

// Snippet from https://json-generator.com/
string testCode2(
	"{"
	"	\"id\": \"62518d699e210f14fcb1e3c8\",         "
	"	\"age\": 29,                                  "
	"	\"eyeColor\": \"brown\",                      "
	"	\"name\": \"Byers Davenport\",                "
	"	\"gender\": \"male\",                         "
	"	\"latitude\": 58.49273,                       "
	"	\"longitude\": 32.859783,                     "
	"	\"tags\": [                                   "
	"	  \"cupidatat\",                              "
	"	  \"ex\"                                      "
	"	],                                            "
	"	\"friends\": [                                "
	"		\"Payne Fields\" ,             		  	  "
	"		\"Barlow Patel\" ,             		      "
	"		\"Helen Harmon\"                		  "
	"	],                                            "
	"	\"fruite\": \"strawberry\"					  "
	"}                                                "
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
  testJson("Additional tests", testCode2);
}
