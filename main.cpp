#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <iostream>
#include <timeapi.h>
#include "raylib.h"

const int screenWidth = 608;
const int screenHeight = 608;

int** initCell;
int** cCell;


void initializeCells() {

    initCell = new int*[16];
    for (int i = 0; i < 16; i++) {
        initCell[i] = new int[16];
        for (int j = 0; j < 16; j++) {
            initCell[i][j] = 0;
        }
    }

    initCell[3][3] = 1;
    initCell[4][4] = 1;
    initCell[4][5] = 1;
    initCell[3][5] = 1;
    initCell[2][5] = 1;

    cCell = new int*[16];
    for (int i = 0; i < 16; i++) {
        cCell[i] = new int[16];
        for (int j = 0; j < 16; j++) {
            cCell[i][j] = initCell[i][j];
        }
    }
    
}

void FreeCells(){
    for(int i = 0; i < 16; i++){
        delete[] initCell[i];
        delete[] cCell[i];
    }
    delete[] initCell;
    delete[] cCell;
}

// {
//     {0,1,0,1,0,0,1,1}
//     {1,0,0,0,0,0,0,0}
//     {0,1,1,0,1,0,1,0}
//     {0,0,1,1,0,0,1,1}
// }

//check every neighbour and add the value of each neigherbour into an array
//  and iterate thorugh that array(fuck dat bitch) to get a count and then procede to 
// change the value of the inital cell to 0 || 1

int neighbourLogic(int curX, int curY, int** cState){
    int count = 0;
    for(int i = -1; i < 1; i++){
        for(int j = -1; j < 1; j++){
            if(i == 0 && j == 0) continue;

            int nX = curX + i;
            int nY = curY + i;

            if(nX >= 0 && nX <= 16 && nY >= 0 && nY <=16){
                if(cState[nX][nY] == 1){
                    count++;
                }
            }
        }
    }
    return count;
}

int** statusCheck(int** currState){

    
    int **nState = new int*[16];
    for(int i = 0; i<16;i++){
        nState[i] = new int[16];
    }

    for(int i = 0; i < 16; i++){
        for(int j=0; j < 16; j++){
            int nCount = neighbourLogic(i, j, nState);
            if(nCount == 2 || 3){
                nState[i][j] = 1;
            }
            if(nCount >=3){
                nState[i][j] = 0;
            }
            if(nCount <=1){
                nState[i][j] = 0;
            }
            
        }
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            nState[i][j] = currState[i][j];

        }
    }
    return nState;

   
    
}

void DrawCells(){
    int** nState = statusCheck(cCell);
    int xDis = 0;
    int yDis = 0;
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            if(nState[i][j] == 0){
                DrawRectangle(xDis, yDis, 38, 38, WHITE);
            }
            if(nState[i][j] == 1){
                DrawRectangle(xDis, yDis, 38, 38, BLACK);
            }
            yDis = yDis + 38;  // Move to the next row
        }
        xDis = xDis + 38;  // After finishing a row, move to the next column
        yDis = 0;  // Reset vertical position for the next row
    }
    for(int i=0; i < 16; i++){
        delete[] nState[i];

    } delete[] nState;
}





//[16][16]
//
int main(){
    InitWindow(screenWidth,screenHeight,"Game Of life");
    SetTargetFPS(60);

    initializeCells();
    while(!WindowShouldClose()){

        BeginDrawing();
            ClearBackground(WHITE);
            DrawCells();
        EndDrawing();
    }
    
    FreeCells();
    CloseWindow();
}


