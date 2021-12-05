#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool chkwin(vector<vector<bool>> a){
  for(int i = 0; i < 5; i++){
    bool f1 = true;
    bool f2 = true;
    for(int j = 0; j < 5; j++){
      f1 = f1 & a[i][j];
      f2 = f2 & a[j][i];
    }
    if(f1 || f2) return true;
  }
  return false;
}

pair<int,int> mark(int q, vector<vector<int>>& b){
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      if(b[i][j] == q) return pair<int,int>(i,j);
    }
  }
  return pair<int,int>(-1,-1);
}

int score(int q, vector<vector<bool>> a, vector<vector<int>> b){
  int o = 0;
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      if(!a[i][j]) o += b[i][j];
    }
  }
  return q * o;
}


pair<int,int> bingo (vector<vector<int>> b, vector<int> c){
  vector<vector<bool>> a;
  for(int i = 0; i < 5; i++){
    vector<bool> a1;
    for(int j = 0; j < 5; j++){
      a1.push_back(false);
    }
    a.push_back(a1);
  }

  for(int q = 0; q < c.size(); q++){
    pair<int,int> x = mark(c[q], b);
    if(x.first == -1) continue;
    a[x.first][x.second] = true;
    if(chkwin(a)) return pair<int,int>(q,score(c[q],a,b));
  }

  return pair<int,int>(1000,-1);
}

int main(){
  string l;
  ifstream f("input");
  getline(f,l);
  for(int i = 0; i < l.size(); i++) if(l[i] == ',') l[i] = ' ';
  stringstream s(l);
  vector<int> calls;
  int x;
  while(s >> x){
    calls.push_back(x);
  }

  vector<vector<vector<int>>> boards;

  while(getline(f,l)){
    vector<vector<int>> board;
    for(int i = 0; i < 5; i++){
      getline(f,l);
      stringstream ss(l);
      vector<int> row;
      int xx;
      while(ss >> xx){
        row.push_back(xx);
      }
      board.push_back(row);
    }
    boards.push_back(board);
  }

  int g = 100;
  int g2 = 1;
  int o;
  int o2;

  for(auto board : boards){
    pair<int,int> q = bingo(board, calls);
    if(g > q.first){
      g = q.first;
      o = q.second;
    }
    if(g2 < q.first){
      g2 = q.first;
      o2 = q.second;
    }
  }

  cout << o << endl;
  cout << o2 << endl;

  return 0;
}
