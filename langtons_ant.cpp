#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;


int main(){
  int definer;
  int Rows, Cols;
  int rows, cols;
  int TotalAnts;
  cin>>definer >> TotalAnts;
  cin >> Rows >> Cols;
  vector <char> ant_dir;

  vector <int> Row(Cols,0);
  vector <vector<int>> Matrix;
  vector <int> ant_rowStorage, ant_colStorage;
  set <pair <int,int>> ant_set;
  map <char, char> White_dir{
    {'N', 'E'},{'S', 'W'},{'W', 'N'},{'E', 'S'}
  };
  map <char, char> Black_dir{
    {'N', 'W'},{'S', 'E'},{'W', 'S'},{'E', 'N'}
  };
  for (int i=0; i < TotalAnts; i++){
      cin >> rows >> cols;
    if (rows<0|| rows>=Rows || cols<0|| cols>=Cols) {
      continue;
    }
    if (ant_set.count({rows,cols})) {
      continue;
    }
    ant_set.insert({rows,cols});
      ant_rowStorage.push_back(rows);
      ant_colStorage.push_back(cols);
      ant_dir.push_back('N');
  }
  for (int i=0; i < Rows; i++){
      Matrix.push_back(Row);
  }
  for (const vector<int> &items: Matrix){
      for( const int numbers: items){
        cout << numbers;
  }
    cout << endl;
  }


for (int j =0; j<definer; j++) {
    cout << endl;
    for (int i=0; i < ant_rowStorage.size(); i++){
      rows = ant_rowStorage[i];
      cols = ant_colStorage[i];
      char direction = ant_dir[i];

  if (rows == (Rows)){
      rows = 0;
  }
  else if( rows == -1){
      rows = Rows-1;
  }
  if (cols == (Cols)){
      cols = 0;
  }
  else if (cols ==-1){
      cols = Cols-1;
  }
  if (Matrix[rows][cols] == 1){
    Matrix[rows][cols] = 0;
    if (direction == 'N'){
      // turn to w, move to 1 less column
      cols-=1;
      direction=Black_dir[direction];
    }
    else if (direction == 'W'){
      // turn to S, move down
      rows+=1;
      direction=Black_dir[direction];
    }
    else if (direction == 'S'){
      cols+=1;
      direction=Black_dir[direction];
    }
    else if (direction == 'E'){
      // turn to n, row-1
      rows-=1;
      direction=Black_dir[direction];
    }
  }
  else if (Matrix[rows][cols] == 0){
    Matrix[rows][cols] = 1;
    if (direction == 'N'){
      // turn to w, move to 1 less column
      cols+=1;
      direction=White_dir[direction];
    }
    else if (direction == 'W'){
      // turn to S, move down
      rows-=1;
      direction = White_dir[direction];
    }
    else if (direction == 'S'){
      cols-=1;
      direction =White_dir[direction];
    }
    else if (direction == 'E'){
      // turn to n, row-1
      rows+=1 ;
      direction = White_dir[direction];
    }
  }

    ant_rowStorage[i] = rows;
    ant_colStorage[i] = cols;
    ant_dir[i] = direction;
  }

  for (const vector <int> & items: Matrix){
    for(const int numbers: items){
      cout << numbers;
    }
    cout << endl;
  }
}
  return 0;
}

