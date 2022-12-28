#include "autocomplete.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void testAC01() {
  cout << "Starting AC test01" << endl;
  cout << "* Testing basic autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("small.txt");
  auto v = ac.complete("hel");
  assert(v.size() == 2);
  assert(v[0].first == "help");
  assert(v[0].second == 20);
  assert(v[1].first == "hello");
  assert(v[1].second == 10);
  cout << "Ending tesAC01" << endl;
}

void testAC02() {
  cout << "Starting AC test02" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Sea");
  assert(v.size() == 47);
  string test = "Seattle, Washington, United States";
  assert(v[0].first == "Seattle, Washington, United States");
  assert(v[0].second == 608660);
  assert(v[46].first == "Seabeck, Washington, United States");
  assert(v[46].second == 1105);
  cout << "Ending tesAC02" << endl;
}

void testAC03() {
  cout << "Starting AC test03" << endl;
  cout << "* Testing cities Non-Existant Prefix" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Ali-Kassim-Ibrahim");
  assert(v.empty());
  cout << "Ending testAC03" << endl;
}

void testAC04() {
  cout << "Starting AC test04" << endl;
  cout << "* Testing with Specific Prefix same as City Name" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Seattle, Washington, United States");
  assert(v.size() == 1);
  string test = "Seattle, Washington, United States";
  assert(v[0].first == "Seattle, Washington, United States");
  assert(v[0].second == 608660);
  cout << "Ending tesAC04" << endl;
}

void testAC05() {
  cout << "Starting AC test05" << endl;
  cout << "* Testing numbers as a prefix" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("999999");
  assert(v.empty());
  cout << "Ending tesAC05" << endl;
}

void testAC06() {
  cout << "Starting AC test06" << endl;
  cout << "* Testing cities autocomplete with numbers" << endl;
  Autocomplete ac;
  ac.readFile("numbers.txt");
  auto v = ac.complete("9");
  assert(v.size() == 5);
  string test = "989898";
  assert(v[0].first == "989898");
  assert(v[0].second == 30);
  assert(v[4].first == "99978");
  assert(v[4].second == 6);
  cout << "Ending tesAC06" << endl;
}

void testAC07() {
  cout << "Starting AC test07" << endl;
  cout << "* Testing cities autocomplete with Special characters" << endl;
  Autocomplete ac;
  ac.readFile("numbers.txt");
  auto v = ac.complete("@");
  assert(v.size() == 3);
  string test = "@3423";
  assert(v[0].first == "@33");
  assert(v[0].second == 20);
  assert(v[2].first == "@3423");
  assert(v[2].second == 2);
  cout << "Ending tesAC07" << endl;
}

void testAC08() {
  cout << "Starting AC test08" << endl;
  cout << "* Testing with no prefix" << endl;
  Autocomplete ac;
  ac.readFile("small.txt");
  auto v = ac.complete("");
  assert(v.size() == 10);
  string test = "help";
  assert(v[0].first == "like");
  assert(v[0].second == 30);
  assert(v[9].first == "lerp");
  assert(v[9].second == 2);
  cout << "Ending tesAC08" << endl;
}

// // Calling all test functions
void testACAll() {
  testAC01();
  testAC02();
  testAC03();
  testAC04();
  testAC05();
  testAC06();
  testAC07();
  testAC08();
  // TODO(student) Add more tests
}