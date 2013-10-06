//game.cpp
#include <cstdlib>
#include <cstdio>
using namespace std;
#include "Game.h"
#include "shapes.h"

//restarts the game
void Game::Restart() {
	for (int i = 0; i < 7; i++)
		numTimes[i] = 0;
	numTimes[currPc] = 1;
	ClearGrid(false);
	pos = COLS / 2;		
	row = ROWS;
	linesCleared = 0;
	killed = false;
	paused = false;
}

//Handles the moving/rotating
void Game::Move(int dir, int rotate) {
	if (dir < 0 && pos > 1 && !CheckCollision(false,true,false,orientation))
		pos--;
	else if (dir > 0 && pos < COLS - bricks[currPc][orientation].w && !CheckCollision(false,false,false,orientation)) 
		pos++; 
	else if (!CheckCollision(false,true,true,0) && !CheckCollision(false,false,true,1)) {
		if (rotate < 0) {
			orientation--;
			if (orientation == -1)
				orientation = 3;
		} else if (rotate > 0) {
			orientation++;
			if (orientation == 4)
				orientation = 0;
		}
	}
}

//Sets killed to true if there is a block underneath the 
//starting position
void Game::CheckDeath() {
	if (grid[ROWS-1][COLS/2] != -1) {
		killed = true;
	} 
}

//Clears the grid or flags a row to be cleared
void Game::ClearGrid(bool clearRow) {	
	if (!clearRow) {
		for (int r=0; r<ROWS; r++) {
			for (int c=0; c<COLS; c++) {
				grid[r][c] = -1;
			}
		}
	} else {
		for (int r=0; r<ROWS; r++) {
			bool flag = true;
			for (int c = 0; c < COLS-1; c++) {
				if (grid[r][c] == -1) {
					flag = false;
				} 
			} if (flag) {
				clearedRow = r;
				isRowCleared = true;
				flashOn = true;
			} 
		}
	} 
}

//Removes the flagged row from the grid and
//calls the update function to move the blocks
void Game::ClearRow() {
	linesCleared++;
	for (int c = 0; c < COLS - 1; c++) {
			grid[clearedRow][c]=-1;
	} Update(clearedRow);
}


//Game - Constructor - DONE
Game::Game() {
	currPc = rand()%7;
	Restart();
	numTimes[currPc] = 1;
	nextPc = rand()%7;
	timer = 300;
}

//resets timer, puts piece on grid, checks
//grid for a removal, and sets next piece info
void Game::SwitchBlock() {
	timer = 300;
	BlockToGrid();
	ClearGrid(true);
	CheckDeath();
	currPc = nextPc;
	numTimes[currPc] += 1;
	row = ROWS;
	pos = COLS/2;
	orientation = 0;
	nextPc = rand() % 7;
}

//puts the current piece to the grid
void Game::BlockToGrid() {
	BrickPose piece = bricks[currPc][orientation];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (piece.grid[i][j] == 'X') {
				grid[row-i-1][pos+j-1] = currPc;
			}
		}
	}
	
}

//Detects collisions due to rotation and something below
bool Game::CheckCollision(bool down, bool left, bool rotate, int orient) {
	BrickPose piece = bricks[currPc][orient];
	int rotateOffset = 0;
	if (rotate)
		rotateOffset = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (piece.grid[i][j] == 'X') { 
				if (down) {
					if (piece.h - row == 0)
						return true;
					else if (grid[row-i-2][pos+j-1] != -1) //works if block is underneath
						return true;
				} else if (left) {
					if (grid[row-i-1][pos+j-2+rotateOffset] != -1 || row-piece.h < 0 || pos+piece.w < 0)
						return true;
				} else if (!left) {
					if (grid[row-i-1][pos+j-rotateOffset] != -1 || pos+piece.w > COLS)
						return true;
				}
			}
		}
	} return false;
}

// Update - Moves the blocks down after a line clear.
void Game::Update(int rowCleared) {
	for (int r=rowCleared; r<ROWS-2; r++) {
		for (int c=0; c<COLS; c++) {
			grid[r][c] = grid[r+1][c];
			ClearGrid(true);
		}
	}
}