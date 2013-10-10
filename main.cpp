// main.cpp
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <GL/glut.h>
#include "Game.h"
#include "shapes.h"
#include <iostream>
#include <vector>

using namespace std;

const int BLOCKSIZE = 30;
const int VPWIDTH = COLS * BLOCKSIZE;
const int VPHEIGHT = ROWS * BLOCKSIZE - BLOCKSIZE;

//Function to draw bitmap text
void BitmapText(char *str, int wcx, int wcy) {
	void *font = GLUT_BITMAP_HELVETICA_12;
	glRasterPos2i(wcx, wcy);
	for (int i=0; str[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
	}
}

//Function of switch cases handling color variables
void SetColor(int x) {
	switch (x) {
		case 1:		glColor3f(1.0, 1.0, 0.0); break; //Yellow
		case 2:		glColor3f(0.0, 1.0, 1.0); break; //Cyan
		case 3:		glColor3ub(153, 50, 504); break;
		case 4: 	glColor3f(0.0, 0.0, 1.0); break;
		case 5:		glColor3f(1.0, 0.5, 0.0); break;
		case 6:		glColor3f(0.0, 1.0, 0.0); break;
		case 7:		glColor3f(1.0, 0.0, 0.0); break;
		case 8:		glColor3f(0.5, 0.0, 0.5); break;
		default:	glColor3f(0.5, 0.5, 0.5); break;
	}
}

// Structure to maintain the state of a game
Game game;		

//timer - Callback for timers - Handles the movement down
//and what happens when dead and when a row is cleared
void timer(int id)
{
	if (!game.paused) {
		if (game.killed || game.isRowCleared) {	// mode for when the user has been killed
			game.flashOn = !game.flashOn;
			if (id < 5) {
				glutTimerFunc(100, timer, id+1);
			}
			else {
				if (game.isRowCleared){ 
					game.isRowCleared = false;
					game.ClearRow();
				} else if (game.killed)
					game.Restart();
				glutTimerFunc(game.timer, timer, 0);
			}
			glutPostRedisplay();
		} else  {	// normal operation is when game
			if (game.killed) {
				glutTimerFunc(100, timer, 1);
			} else if (id == 0) {	
				glutTimerFunc(game.timer, timer, 0);
				if (game.CheckCollision(true, false, false, game.orientation)) {
					game.SwitchBlock();
				}
				else if (!game.CheckCollision(true, false, false, game.orientation)) {
					game.row -= 1;
				}
				else if (game.isRowCleared) {
					glutTimerFunc(100,timer,1);
				}
				glutPostRedisplay();
			}
		}
	}
}

//sets a linewidth, clears color, etc
void init() {
	glLineWidth(2.0);
	glClearColor(255,255,255,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//Draws a white rectangle ove the grid of blocks
void pause() {
	glViewport(180, 0, VPWIDTH, VPHEIGHT);
	init();
	gluOrtho2D(-1, COLS-1, 0, ROWS);
	glColor3ub(255,255,255);
	glRectd(0,0,COLS-1,ROWS);
	glutSwapBuffers();
}

//Pauses, speeds up, and exits
void keyboard(unsigned char key, int x, int y) {
	if (key == 'p') {
		game.paused = !game.paused;
		pause();
		if (!game.paused) {
			glutTimerFunc(game.timer, timer, 0);
			glutSwapBuffers();
		}
	} else if (key == ' ') {
		game.timer = 50;
	} else if (key == 'x') {
		exit(0);
	}
}

// Moves left, right Rotates up, down, F1 makes next piece I
void special(int key, int x, int y)
{
	if (!game.paused && !game.killed) {
		if (key == GLUT_KEY_LEFT) {
			game.Move(-1,0);
		} else if (key == GLUT_KEY_RIGHT) {
			game.Move(+1,0);
		} else if (key == GLUT_KEY_DOWN) {
			game.Move(0,-1);
		} else if (key == GLUT_KEY_UP) {
			game.Move(0,1);
		} else if (key == GLUT_KEY_F1) {
			game.nextPc = 1;
		} glutPostRedisplay();
	}
}

//Draws the outline for each individual brick in
//the grid, the next piece, and the current piece
void drawOutline(int x1, int y1) {
	glColor3ub(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2d(x1, y1);
		glVertex2d(x1, y1+1); 
		glVertex2d(x1+1, y1+1); 
		glVertex2d(x1+1, y1);
	glEnd();
}

//Draws the shapes be it active, next piece, or info
void displayTetriminos(BrickPose tetrimino, int x, int y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			if (tetrimino.grid[i][j] == 'X') {
				SetColor(tetrimino.color);
				glRectd(x+j, y-i, x-1+j, y-1-i);
				drawOutline(x-1+j, y-1-i);
			}
	}
}

//Draws the shapes that the player is not
//controlling
void displayGrid() {
	for (int r=0; r<ROWS; r++) {
		for (int c=0; c<COLS; c++) {
			if (game.grid[r][c] > -1) { 
				SetColor(bricks[game.grid[r][c]][0].color);
				glRectd(c,r,c+1,r+1);
				drawOutline(c,r);
			}
		}
	}
}

//Handles drawing the animation between
//black and white when a row is cleared
void displayAnimation() {
	if (game.isRowCleared) {
		if (game.flashOn == true) {
			glColor3d(0.0, 0.0, 0.0);
		} else {
			glColor3d(1.0, 1.0, 1.0);
		} for (int c = 0; c < COLS; c++) {
			if (game.grid[game.clearedRow][c] > -1)
				glRectd(c,game.clearedRow,c+1,game.clearedRow+1);
		}
	} 
}

void display(void){
	init();
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(180, 0, VPWIDTH, VPHEIGHT);
	gluOrtho2D(-1, COLS-1, 0, ROWS);
	
	//Draws boudary between game grid and score info
	glColor3ub(0,0,0);
	glBegin(GL_LINES);
		glVertex2d(0, 0);
		glVertex2d(0, ROWS);
	glEnd();
	
	displayGrid();
	displayAnimation();

	//draws current shape
	BrickPose currTetr = bricks[game.currPc][game.orientation];
	displayTetriminos(currTetr, game.pos, game.row);
	
	//Draws to next piece viewport
	glViewport(0,350,VPWIDTH-60,VPHEIGHT-60);
	init();
	gluOrtho2D(-1, COLS-3, 0, ROWS-3);

	BrickPose nextTetr = bricks[game.nextPc][0];
	displayTetriminos(nextTetr, 0, (ROWS-8)/2);

	//draws to the piece info
	glViewport(0,25,125,350);
	init();
	gluOrtho2D(-1,COLS,0,ROWS+10);
	//draws each piece
	for (int i = 0; i < 7; i++) {
		BrickPose p = bricks[i][0];
		if (i == 1) 
			displayTetriminos(p, 0,  ROWS+10 - i*4 +1);
		else
			displayTetriminos(p, 0,  ROWS+10 - i*4);
	}

	//Writes "x " and the number of times a shape has appeared
	glViewport(20,25, 125, 350);
	init();
	gluOrtho2D(-1, COLS, 0, ROWS + 10);
	char m[100];
	glColor3f(0,0,0);
	for (int i = 0; i < 7; i++) {
		sprintf(m, "x %d", game.numTimes[i]);
		BitmapText(m,0, ROWS+10 - i*4 - 2);
	}

	//Writes scores on bottom left viewport
	init();
	glViewport(0, 0, VPWIDTH, 25);
	gluOrtho2D(0, 100, 0, 500);

	char msg[100];
	sprintf(msg, "Lines cleared: %d", game.linesCleared);
	glColor3f(0, 0, 0);
	BitmapText(msg, 1, 50);

	glutSwapBuffers();
}

void main(int argc, char *argv[]) {
	srand(time(NULL));
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(VPWIDTH + 180, VPHEIGHT-60);

	glutCreateWindow("Tetris");

	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(game.timer, timer, 0);

	glutMainLoop();
}
