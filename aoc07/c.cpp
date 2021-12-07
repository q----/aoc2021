#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <regex>
#include <numeric>

using namespace std;

int main(){
  string l;
  ifstream f("input");

  getline(f,l);

  vector<int> c;
  regex rgx (",");
  regex_token_iterator<string::iterator> it(l.begin(), l.end(), rgx, -1);
  regex_token_iterator<string::iterator> end;
  for(; it != end; ++it) c.push_back(stoi(*it));

  sort(c.begin(), c.end());
  int median = c[c.size()/2];

  cout << accumulate(c.begin(),c.end(),0,[median](int x, int y){return x + abs(y-median);}) << endl;

  int mean = accumulate(c.begin(),c.end(),0)/c.size();

  cout << accumulate(c.begin(),c.end(),0,[mean](int x, int y){return x + [](int t){return t*(t+1)/2;}(abs(y-mean));}) << endl;

  return 0;
}
