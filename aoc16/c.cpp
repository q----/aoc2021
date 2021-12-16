#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <numeric>
#include <climits>

using namespace std;

vector<long long int> parse(string b, bool fix, int& v);

long long int pl(string& b, int& i){
  bool fl = true;
  long long int x = 0;
  while(fl){
    x = 16*x + bitset<4>(b.substr(i+1,4)).to_ulong();
    if(b[i] == '0') fl = false;
    i += 5;
  }
  return x;
}

long long int po(string& b, int& i, int& v, int op){
  bool l = bitset<1>(b.substr(i,1)).to_ulong();
  i++;
  vector<long long int> vals;
  if(l){
    long long int ga = bitset<11>(b.substr(i,11)).to_ulong();
    i += 11;
    long long int t = 0;
    while(t < ga){
      v += bitset<3>(b.substr(i,3)).to_ulong();
      i += 3;
      int q = bitset<3>(b.substr(i,3)).to_ulong();
      i += 3;
      if(q == 4){
        vals.push_back(pl(b,i));
      } else {
        vals.push_back(po(b,i,v,q));
      }
      t++;
    }
  } else {
    long long int len = bitset<15>(b.substr(i,15)).to_ulong();
    i += 15;
    vals = parse(b.substr(i,len), false, v);
    i += len;
  }
  long long int out;
  switch(op){
    case 0:
      out =  accumulate(vals.begin(),vals.end(),0ll,[](long long int x, long long int y){return x + y;});
      break;
    case 1:
      out =  accumulate(vals.begin(),vals.end(),1ll,[](long long int x,long long int y){return x * y;});
      break;
    case 2:
      out =  accumulate(vals.begin(),vals.end(),LLONG_MAX,[](long long int x,long long int y){return (x<y)?x:y;});
      break;
    case 3:
      out =  accumulate(vals.begin(),vals.end(),0ll,[](long long int x,long long int y){return (x>y)?x:y;});
      break;
    case 5:
      out =  (vals[0] > vals[1])?1:0;
      break;
    case 6:
      out =  (vals[0] < vals[1])?1:0;
      break;
    case 7:
      out =  (vals[0] == vals[1])?1:0;
      break;
  }
  return out;
}

vector<long long int> parse(string b, bool fix, int& v){
  vector<long long int> o;
  for(int i = 0; i < b.size();){
    v += bitset<3>(b.substr(i,3)).to_ulong();
    i += 3;
    int t = bitset<3>(b.substr(i,3)).to_ulong();
    i += 3;
    if(t==4){
      o.push_back(pl(b,i));
    } else {
      o.push_back(po(b,i,v,t));
      if(fix) break;
    }
  }
  return o;
}

int main(){
  string l;
  ifstream f("input");
  string b = "";
  getline(f,l);

  for(int i = 0; i < l.size(); i++){
    b += bitset<4>(stoi(l.substr(i,1), nullptr, 16)).to_string();
  }

  int v = 0;
  vector<long long int> ah = parse(b,true,v);
  cout << v << endl;
  cout << ah[0] << endl;

  return 0;
}
