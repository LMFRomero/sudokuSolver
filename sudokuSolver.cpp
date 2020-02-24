#include <bits/stdc++.h>
#include <algorithm>
#include <unistd.h>

using namespace std;

#define SUDOKU_SIZE 9
#define REGION_SIZE 3

int matriz[SUDOKU_SIZE][SUDOKU_SIZE];
int ref_matriz[SUDOKU_SIZE][SUDOKU_SIZE][SUDOKU_SIZE+1];

void readSudoku() {
    char tmp;

    for (int i = 0; i < SUDOKU_SIZE; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            do {
                cin >> tmp; 
            } while(tmp == ' ');

            if (tmp == 'x' or tmp == 'X') continue;
            else matriz[i][j] = static_cast<int> (tmp - '0'); 
        }
    }
    

}


void defineInitialReferences() {
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            
            if (matriz[i][j] > 0) {
                ref_matriz[i][j][matriz[i][j]] = false;
            }

            else {
                for (int k = 1; k <= SUDOKU_SIZE; k++) {
                    ref_matriz[i][j][k] = true;
                }
            }
        }
    }
}


void deleteRef(int possib, int i, int j) {
    ref_matriz[i][j][possib] = false;
}

void scanHorizontally(int i, int j) {
    for(int possibJ=0; possibJ<SUDOKU_SIZE; possibJ++){
        if (matriz[i][possibJ] == 0) continue;
        if (possibJ == j) continue;
        deleteRef(matriz[i][possibJ],i,j);
    }
}

void scanVertically(int i, int j) {
    for(int possibI=0; possibI<SUDOKU_SIZE; possibI++){
        if (matriz[possibI][j] == 0) continue;
        if (possibI == i) continue;
        deleteRef(matriz[possibI][j],i,j);
    }
}

void scanRegion(int i, int j) {
    int startRegionY = (i / REGION_SIZE) * REGION_SIZE;
    int startRegionX = (j / REGION_SIZE) * REGION_SIZE;


    for (int scanI = startRegionY; scanI < startRegionY + REGION_SIZE; scanI++) {
        for (int scanJ = startRegionX; scanJ < startRegionX + REGION_SIZE; scanJ++) {
            if (matriz[scanI][scanJ] == 0) continue;
            if (scanI == i && scanJ == j) continue;

            deleteRef(matriz[scanI][scanJ], i, j);
        }
    }
}

int scanRef (int i, int j) {
    int counterTrue = 0;
    int lastTrue = 0;
    
    for (int k = 1; k <= SUDOKU_SIZE; k++) {
        if (ref_matriz[i][j][k] == true) {
            counterTrue++;
            lastTrue = k;
        }
    }
    return (counterTrue == 1) ? lastTrue : 0;
}

void updateReferences(int i, int j) {
    scanHorizontally(i,j);
    scanVertically(i,j);
    scanRegion(i,j);
}

void printSudoku () {
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }    
}

void solveSudoku() {
    bool isSolved = false;

    while (!isSolved) {
        isSolved = true;

        for (int i = 0; i < SUDOKU_SIZE; i++) {
            for (int j = 0; j < SUDOKU_SIZE; j++) {
                if (matriz[i][j] != 0) continue;

                isSolved = false;
                updateReferences(i,j);
                
                matriz[i][j] = scanRef(i, j);                                      
            }
        }
    }
    cout << endl;  
}



void bootstrapSudoku() { 
    readSudoku();
    defineInitialReferences();
}

int main () {
    bootstrapSudoku();
    solveSudoku();
    printSudoku();
}


