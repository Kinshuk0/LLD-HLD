#include <bits/stdc++.h>
using namespace std;
//entitites Board, Cell, Player
// game will be the manger class
// Gamestatus
// Cental controller class in TicTacToeSystem manages all the games
// There will be a score card entity to main the leaderboard

//define the class for each of the entitites
// when there is logic and manipulation always use the class
enum GameStatus{
  IN_PROGRESS,
  WINNER_X,
  WINNER_O,
  DRAW
};
enum Symbol{
    X,
    O,
    EMPTY
};

class Player{
    private:
    string name;
    Symbol symbol;
    public:
    Player(string name,Symbol symbol){
        this->name = name;
        this->symbol = symbol;
    }
    string getName(){
        return name;
    }
    Symbol getSymbol(){
        return symbol;
    }
    string getChar(Symbol symbol){
        switch (symbol) {
            case X:
                return "X";
            case O:
                return "O";
            case EMPTY:
                return "EMPTY";
            default:
                return "ERROR";
        }
    }
};

class Cell{
    // this is the current value
    private:
    Symbol symbol;
    public:
    Cell(){
        this->symbol = Symbol::EMPTY;
    }
    void setSymbol(Symbol symbol){
        this->symbol = symbol;
    }
    Symbol getSymbol(){
        return symbol;
    }
    string getChar(Symbol symbol){
        switch (symbol) {
            case X:
                return "X";
            case O:
                return "O";
            case EMPTY:
                return "EMPTY";
            default:
                return "ERROR";
        }
    }
};

class Board{
    private:
    int size;
    vector<vector<Cell>> board;
    int movesCount;
    public:
    Board(int size){
        this->size = size;
        movesCount = 0;
        // this will pick the default value of the cell
        board.resize(size,vector<Cell>(size));
    }
    // no destructor required for the vector it cleans it self
    // ~Board(){
    //     for(int i=0;i<size;i++){
    //         for(int j=0;j<size;j++){
    //             delete board[i][j];
    //         }
    //     }
    // }
    void placeSymbol(int row,int col,Symbol symbol){
        if(board[row][col].getSymbol()!=EMPTY){
            cout << "Already occupied\n";
            return;
        }
        movesCount++;
        board[row][col].setSymbol(symbol);
    }
    bool isCellEmpty(int row,int col){
        return board[row][col].getSymbol() == Symbol::EMPTY;
    }
    bool isFull(){
        return movesCount==(size*size);
    }
    // we will see for the getwinner function later
    void printBoard(){
        cout << "-------------" << endl;
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                string cellValue = board[i][j].getChar(board[i][j].getSymbol());
                cout << cellValue << " ";
            }
            cout << endl;
        }
        cout << "--------------" << endl;
    }
};
class WinningStrategy{
    Board board;
    int size;
    WinningStrategy(int size,Board board):
    size(size),board(board){};

};
class Game{
  private:
  Board board;
  int size;
  vector<Player> players;
  Player currentPlayer;
  GameStatus status;
  public:
  Game(Player p1, Player p2, int size)
      : board(size), currentPlayer(p1)
  {
      this->size = size;
      players.push_back(p1);
      players.push_back(p2);
      status = GameStatus::IN_PROGRESS;
  }
  void makeMove(int row,int col){
      board.placeSymbol(row,col,currentPlayer.getSymbol());
      if(currentPlayer.getSymbol() == players[0].getSymbol()){
          currentPlayer = players[1];
      }
      else{
          currentPlayer = players[0];
      }
      status=GameStatus::IN_PROGRESS;
  }
  void printBoard(){
      board.printBoard();
  }
  void getWinner(){

  }
};

int main(){
    string s;cin>>s;
    cout << s <<endl ;
    return 0;
}
