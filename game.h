#ifndef _GAME_H_
#define _GAME_H_

const int ROWS = 21;
const int COLS = 11;

struct Game {
	Game();
	
	void Update(int rowCleared);
	void ClearGrid(bool clearRow);
	void Restart();
	void Move(int dir, int rotate);
	bool CheckCollision(bool down, bool left, bool rotate, int orient);
	void CheckDeath();
	void BlockToGrid();
	void SwitchBlock();
	void ClearRow();

	int grid[ROWS][COLS]; // 0 = empty. Others = colors
	int pos;		// column where user's block is located
	int row;		// row where user's block is located
	bool killed;	// true if the current life has been terminated
	int nextPc;
	int currPc;
	int orientation;

	bool flashOn;	// used during a kill. Temporarily alternates btw T and F
	bool isRowCleared;
	int clearedRow;
	bool paused;	// true if the game is to be paused
	int timer;		// determines how fast game proceeds

	int numTimes[7];

	int linesCleared;
};

#endif