#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>

using namespace std;

bool operator<(const string& lhs, const string& rhs){
  for(char a : lhs) if(!count(rhs.begin(),rhs.end(),a)) return false;
  return true;
}

int main(){
  string l;
  ifstream f("input");
  int o = 0;
  int total = 0;

  while(getline(f,l)){
    stringstream s(l);

    string t;
    vector<string> x;

    while(t != "|"){
      s >> t;
      sort(t.begin(), t.end());
      x.push_back(t);
    }

    map<string,int> c;
    string one;
    string four;
    string nine;
    for(string f : x){
      if(f.size() == 2){
        c[f] = 1;
        one = f;
      }
      if(f.size() == 3) c[f] = 7;
      if(f.size() == 4){
        c[f] = 4;
        four = f;
      }
      if(f.size() == 7) c[f] = 8;
    }
    for(string f : x){
      if(f.size() != 6) continue;
      if(one < f){
        if(four < f){
          c[f] = 9;
          nine = f;
        } else {
          c[f] = 0;
        }
      } else {
        c[f] = 6;
      }
    }
    for(string f : x){
      if(f.size() != 5) continue;
      if(one < f){
        c[f] = 3;
      }else{
        if(f < nine){
          c[f] = 5;
        } else {
          c[f] = 2;
        }
      }
    }

    int add = 0;
    
    while(s >> t){
      if(t.size() == 2 || t.size() == 3 || t.size() == 4 || t.size() == 7) o++;
      sort(t.begin(),t.end());
      add = 10 * add + c[t];
    }
    total += add;
  }

  cout << o << endl;
  cout << total << endl;
  return 0;
}
