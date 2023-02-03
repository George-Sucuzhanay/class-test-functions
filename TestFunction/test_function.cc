// Some functions to test rvalues.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Use unnamed namespace for stand-alone functions if possible.
namespace {

void TestFunction1() {
  string str = "fine" ;
  cout << str << endl;
  string &rstr = str; // what do you call this: call by reference??
  cout << rstr << endl;
  str += 'o';
  cout << str << endl;  // why is that rstr retain the changes to str ... perhaps since rstr references the object that this address str points to
  cout << rstr << endl;
  cout << "True/false: " << (&rstr == &str) << endl;
}


void TestFunction3() {
  string str = "fine" ;
  string &&b1 = "hello" ; // b1 is a r-value reference but what exactly does this mean???
  string &&b2 = str + 'a';  // isn'tline 27 and 28 doing the same thing but the output in the terminal allows for this to run properly
  string b4 = str + "b";
  string &&b3 = str.substr(0,3);

  cout << b1 << endl;
  cout << b2 << endl;
  cout << b3 << endl;
  cout << b4 << " look here" << endl;
}

void TestFunction4() {
  vector<int> a_vector = {1, 2, 3, 4, 5};
  for (auto &x : a_vector) ++x;   // this is modifying the elements in the vector individually
  for (auto x : a_vector) cout << x << ", ";
  cout << endl;
}

string RandomItem(const vector<string> &arr) {
  cout << "Version 1" << endl;
  const size_t n = std::rand() % arr.size(); 
  return arr[n];
}

const string &RandomItem2(const vector<string> &arr) {  // why does this func need to return a const string and not simply a string
  cout << "Version 1 -- const reference" << endl;
  const size_t n = std::rand() % arr.size(); 
  return arr[n];
}

string RandomItem(vector<string> &&arr) {    // since we are explicily passing in a vector when this func is called we don't use const and its a r-value reference
  cout << "Version 2" << endl;
  const size_t n = std::rand() % arr.size(); 
  return arr[n];
} 

void TestRandomItems() {
  const vector<string> v = {"hello", "world", "hi", "why"};
  cout << RandomItem(v) << endl;  
  cout << RandomItem({"hello", "world", "hi", "why"}) << endl; 

  auto &result = RandomItem2(v);  // why is the and operator necessary here?? overloading???
  cout << "Result is " << result << endl; 
}

const string &TestLValueReference(const vector<string> &v, size_t element) {
  if (element >= v.size()) abort();
  return v[element];
}

void CompleteTestLValueReference() {
  vector<string> temp{"aa", "bb", "cc"};
  const string &x = TestLValueReference(temp, 1);
  cout << x << endl;
  temp[1] = "jj";
  cout << x << endl;
}

}  // namespace

int main() {
 TestFunction1();
 TestFunction3();
 TestFunction4();
 TestRandomItems();
 CompleteTestLValueReference();
 return 0;
}
