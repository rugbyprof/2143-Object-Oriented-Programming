#include <iostream>
#include "helper.hpp"
#include "colors.h"
#include <unistd.h> 

using namespace std;

#define LIZARD u8"\U0001F438"

class GOL {
  int **board;
  int **next;
  int width;
  int height;


  void Clear(int **&array){
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        array[i][j] = 0;
      }
    }
  }

  void init() {
    board = allocate(width,height);
    next = allocate(width,height);
    
    Clear(board);
    Clear(next);
    // board[0][1] = 1;
    // board[1][1] = 1;
    // board[1][0] = 1;
  }

public:
  GOL() {
    width = 30;
    height = 20;
    init();
  }

  GOL(int w, int h) {
    width = w;
    height = h;
    init();
  }

  void rando() {    
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if(rand()%5==0){
          board[i][j] = 1;
        }else{
          board[i][j] = 0;
        }
      }
    }
  }

  void Print() {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (board[i][j] == 1) {
          //cout<<ON_CYAN<<<<LIZARD;
          cout<<ON_IYELLOW<<" ";
          //cout << "▆";
          //cout << '0';
        } else {
          cout<<ON_CYAN<<" ";
        }
      }
      cout << endl<<OFF;
    }
    cout << endl<<OFF;
  }

  bool OnWorld(int row, int col){
    return row >= 0 && col >= 0 && row < height && col < width;
  }

  int CountNeighbors(int row, int col){
    int sum = 0;
    if(OnWorld(row-1,col) && board[row - 1][col] == 1){
      sum++;
    }

    if(OnWorld(row-1,col-1) && board[row - 1][col-1] == 1){
      sum++;
    }

    if(OnWorld(row,col-1) && board[row][col-1] == 1){
      sum++;
    }

    if(OnWorld(row+1,col-1) && board[row+1][col-1] == 1){
      sum++;
    }

    if(OnWorld(row+1,col) && board[row + 1][col] == 1){
      sum++;
    }

    if(OnWorld(row+1,col+1) && board[row + 1][col + 1] == 1){
      sum++;
    }
       
    
    if(OnWorld(row,col+1) && board[row][col + 1] == 1){
      sum++;
    }

    if(OnWorld(row-1,col+1) && board[row - 1][col+1] == 1){
      sum++;
    }
       
    
    return sum;
  }

  /**
Any live cell with two or three live neighbours survives.
Any dead cell with three live neighbours becomes a live cell.
All other live cells die in the next generation. Similarly, all other dead cells stay dead.
  */
  void ApplyRules(){
    int n;
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
         n = CountNeighbors(i, j);

        if(board[i][j] && (n ==2 || n == 3)){
          next[i][j] = board[i][j];
        }else if(!board[i][j] && n == 3){
          next[i][j] = 1;
        }else{
          next[i][j] = 0;
        }
      }
    }
  }

  void Swap(){
      int **temp;
      temp = board;
      board = next;
      next = temp;
  }

  void Run(int generations){
    
    for (int g = 0; g < generations; g++) {
      ApplyRules();
      Swap();
      Clear(next);
      Print();
      usleep(500000);
      system("clear");
      }
  }
};