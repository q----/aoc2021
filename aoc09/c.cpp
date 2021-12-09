#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int ctoi(char a){
  return (int) a - '0';
}

void basin(vector<string>& map, int i, int j, set<pair<int,int>>& b){
  if(i < 0 || j < 0 || i >= map.size() || j >= map[i].size()) return;
  if(map[i][j] == '9') return;
  if(!b.insert(pair<int,int>(i,j)).second) return;
  basin(map, i+1, j, b);
  basin(map, i-1, j, b);
  basin(map, i, j-1, b);
  basin(map, i, j+1, b);
  return;
}

int main(){
  string l;
  ifstream f("input");
  vector<string> map;

  while(getline(f,l)) map.push_back(l);

  int risk = 0;
  vector<int> sizes;

  for(int i = 0; i < map.size(); i++){
    for(int j = 0; j < map[i].size(); j++){
      if(i > 0) if(ctoi(map[i-1][j]) <= ctoi(map[i][j])) continue;
      if(j > 0) if(ctoi(map[i][j-1]) <= ctoi(map[i][j])) continue;
      if(i < map.size()-1) if(ctoi(map[i+1][j]) <= ctoi(map[i][j])) continue;
      if(j < map[i].size() -1) if(ctoi(map[i][j+1]) <= ctoi(map[i][j])) continue;
      risk += ctoi(map[i][j]) + 1;
      set<pair<int,int>> a;
      basin(map,i,j,a);
      sizes.push_back(a.size());
    }
  }

  cout << risk << endl;

  int e = 1;
  sort(sizes.begin(), sizes.end());
  for(int i = sizes.size()-1; i > sizes.size()-4; --i) e *= sizes[i];
  cout << e << endl;

  return 0;
}
