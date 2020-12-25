#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

enum class State{kEmpty, kObstacle, kPath, kClosed, kStart , kFinish};
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};


vector<State> ParseString(string line){
    istringstream sline(line);
    int n;
    char c; 
    vector<State> res;
    while(sline >> n >> c && c== ','){
        if(n==0){
            res.push_back(State::kEmpty);
        }
        else res.push_back(State::kObstacle);
    }
    return res;
}


string cellString(State cell){
      switch(cell) {
    case State::kObstacle: return "⛰   ";
    case State::kPath: return "🚗   ";
    case State::kStart: return "🚦  ";
    case State::kFinish: return "🏁  ";
    default: return "0   "; 
    }
}

 //vector<vector<State>> Search(<vector<vector<State>> board , int init[2] , int goal[2]){

bool Compare(vector<int> node1 , vector<int> node2){
    int f1 = node1[2] + node1[3];
    int f2 = node2[2] + node2[3];
    return f1>f2;
}


void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}

int hueristic(int x1, int y1 , int x2, int y2){
    return abs(x2-x1) + abs(y2-y1);
}

void AddToOpen(int x , int y, int g, int h , vector<vector<int>> & openNodes, vector<vector<State>> &board){
    vector<int> open = {x,y,g,h};
    openNodes.push_back(open);
    board[x][y] = State::kClosed;
}



 bool CheckValidCell(int x , int y, vector<vector<State>> &grid){
     if(x<0 || y< 0 || x>= grid.size() || y>= grid.size() || grid[x][y] != State::kEmpty) return false;
    return true;

 }


void ExpandNeighbors(vector<int> &current, vector<vector<int>> &open , vector<vector<State>> &grid, int goal[2]){
    int x=  current[0];
    int y = current[1];
    int g = current[2];

    for(int i=0 ; i<4 ; i++){
        int nextX = x + delta[i][0];
        int nextY = y + delta[i][1];

        if(CheckValidCell(nextX, nextY,grid)){
            int h = hueristic(nextX, nextY , goal[0], goal[1]);
            AddToOpen(nextX, nextY, g+1 , h , open, grid);

        }
    }

}




void PrintBoard(vector<vector<State>> board){
     for(vector<State> v : board){
        for(State num : v){
            cout<< cellString(num);
        }
        cout<< "\n";

    }
}

vector<vector<State>> ReadBoardFile(string path){
    ifstream myfile (path);
    vector<vector<State>> res;
    if(myfile){
        string line;
        while(getline(myfile,line)){
            vector<State> row = ParseString(line);
            res.push_back(row);
        }
    }
    return res;
}



vector<vector<State>> Search(vector<vector<State>> &grid, int init[2] , int goal[2] ){

    vector<vector<int>> open;

    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = hueristic(x,y,goal[0], goal[1]);

    AddToOpen(x,y,g,h,open,grid);

    while (open.size() > 0) {
    // Get the next node
    CellSort(&open);
    auto current = open.back();
    open.pop_back();
    x = current[0];
    y = current[1];
    grid[x][y] = State::kPath;

        if(x == goal[0] && y == goal[1]){
            grid[init[0]][init[1]] = State::kStart;
            grid[goal[0]][goal[1]] = State::kFinish;
            return grid;
        }
        ExpandNeighbors(current, open, grid, goal);

    }

    printf("No path Found");
    return vector<vector<State>> {};
}


int main(){
    std::vector<std::string> brothers {"David", "Harshit", "Pulkit"};

    vector<vector<int>> board = {{0, 1, 0, 0, 0, 0},
 {0, 1, 0, 0, 0, 0},
 {0, 1, 0, 0, 0, 0},
 {0, 1, 0, 0, 0, 0},
 {0, 0, 0, 0, 1, 0}}
;
    for(std::string const & brother : brothers){
        std::cout<< "Hello" << brother << "\n";
    };


    vector<vector<State>> board2 = ReadBoardFile("1.board");
    
    PrintBoard(board2);
    int start[2] ={0,0};
    int goal[2]= {4,5};

      auto solution = Search( board2, start,  goal);
  PrintBoard(solution);



   
}
