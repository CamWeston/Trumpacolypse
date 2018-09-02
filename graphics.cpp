
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "trump.hpp"
#include "FallingObject.hpp"
#include "stopwatch.hpp"
#include "SOIL.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <windows.h>
#include <math.h>
#include "irrKlang.h"

#include <chrono>
#include <thread>

#include <iomanip>
#include <vector>
#include <memory>

using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using namespace irrklang;

GLdouble width, height;

int wd;
bool backgroundSet = false;
Trump t;

Asteroid a;


PowerUp p;

vector<Asteroid> asteroids;
vector<PowerUp> powerups;
vector<int> asteroidsout;
Stopwatch s;
GLuint texture;
GLuint texture2;
GLuint texture3;
GLuint texture4;
GLuint texture5;
int sec = -1;
bool followActive;
bool gamePlay;
bool gameOver;
bool gameStart=false;
bool mouseHover = false;
int curr_time = 0;
int del_time = 0;
int prev_time = 0;
double speed;
int endingScore;
ISoundEngine *SoundEngine = createIrrKlangDevice();

void init() {
	
	gamePlay=true;
	width = 500;
	height = 500;
	int tx = 250;
	t.setX(tx);
	int ty = 50;
	t.setY(ty);
	int th = 70;
	t.setHeight(th);
	int tw = 70;
	t.setWidth(tw);
	asteroids.push_back(a);
	
	p.setWidth(70);
	p.setHeight(40);
	
	powerups.push_back(p);
	
}
void loadTexture(GLuint* texture, char* filename) {
	*texture = SOIL_load_OGL_texture(filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
	);
	if (*texture == NULL) {
		printf("[Texture loader] \"%s\" failed to load!\n", filename);
	}
}

void drawTexturedRect(int x, int y, int w, int h, GLuint texture) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
	glColor3f(255, 255, 255);
	glTexCoord2f(0, 1);
	glVertex2f(x, y);
	glTexCoord2f(0, 0);
	glVertex2f(x, y + h);
	glTexCoord2f(1, 0);
	glVertex2f(x + w, y + h);
	glTexCoord2f(1, 1);
	glVertex2f(x + w, y);
	//glTexCoord2f(0, 0);
	//glVertex2f(x, y);
	glEnd();
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

}
/* Initialize OpenGL Graphics */
void initGL() {
	// Set "clearing" or background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
	
	loadTexture(&texture2, "back.jpg");
	loadTexture(&texture5, "make.png");

}

void highScoresIO() {
	//file io
	//after game is over user's high score will be written to file with name
	//then, they will see a list of names with high scores

	//since gameplay not possible at the moment, score is manually set
	
	string name = "Michelle";
	cout << "Save your score! "<<endl;
	cout << "Enter your name: ";
	getline(cin, name);

	cout << "Name: " << name << endl;

	string filename = "HighScores.txt";

	ofstream outFile;
	outFile.open(filename, ios_base::app);

	if (outFile) { // same as outFile.good()
		cout << "Writing to the file" << endl;
		outFile << "Name: " << name << " Score: " << (endingScore*100) << endl;;
	}
	outFile.close();

	ifstream inFile(filename);
	while (inFile) {
		double num;
		while (!inFile.eof() && !(inFile >> num)) {
			// clear stream
			string word;
			inFile.clear();
			inFile >> word;
		}

	}
	inFile.close();
	cout << "Game Session Complete" << endl;
}



/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void display() {
	if (gameStart == true) {
		// tell OpenGL to use the whole window for drawing
		glViewport(0, 0, width, height);

		// do an orthographic parallel projection with the coordinate
		// system set to first quadrant, limited by screen/window size

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, width, 0.0, height, -1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
		
			
		
		drawTexturedRect(0, 0, 500, 500, texture2);
		

		//asteroids
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glColor4f(0.360f, 0.360f, 0.360f, 0.5f);
		
		for (int i = 0; i < asteroids.size(); i++) {
			glBegin(GL_TRIANGLE_FAN);
			glVertex2i(asteroids[i].getXPos(), asteroids[i].getYPos());
			for (int j = 0; j < 360; ++j) {
				glVertex2f(asteroids[i].getXPos() + cosf(j) * asteroids[i].getRadius(), asteroids[i].getYPos() + sinf(j) * asteroids[i].getRadius());
			}
			glEnd();
		}

		//powerups
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glColor4f(0.0f, 0.0f, 1.0f, 0.5f);

		for (int i = 0; i < powerups.size(); i++) {

			
			drawTexturedRect(powerups[i].getXPos(), powerups[i].getYPos(), powerups[i].getWidth(), powerups[i].getHeight(), texture5);
			
		}

		
		loadTexture(&texture, "trump.png");
		drawTexturedRect(t.getX(), t.getY(), t.getWidth(), t.getHeight(), texture);
		
		

		if (gamePlay == true) {
			string message = "Lives: " + to_string(t.getLives());
			
			glColor3f(0.0f, 1.0f, 0.0f);
			glRasterPos2i(210, 450);
			for (int c = 0; c < message.length(); ++c) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,
					message[c]);
			}

			string message2 = "Score: " + to_string(s.timeElapsed() * 100);
		
			glColor3f(0.0f, 1.0f, 0.0f);
			glRasterPos2i(1, 450);
			for (int c = 0; c < message2.length(); ++c) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,
					message2[c]);
			}
		}
		else if (gamePlay == false&&t.getLives()==0) {
			
			SoundEngine->play2D("dream.wav");
			string message3 = "GAME OVER";
	
			glColor3f(1.0f, 0.0f, 0.0f);
			glRasterPos2i(200, 250);
			for (int c = 0; c < message3.length(); ++c) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,
					message3[c]);

			}

			string message6 = "Final Score: " + to_string(endingScore * 100);
			
			
			glColor3f(0.0f, 1.0f, 0.0f);
			glRasterPos2i(200, 450);
			for (int c = 0; c < message6.length(); ++c) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,
					message6[c]);
			}
		
			//stop all keyboard input
			glutKeyboardFunc(NULL);
			glutSpecialFunc(NULL);
			gameOver = true;

		}
		else if (gamePlay == false && t.getLives() != 0) {
			string message5 = "Game Paused. Press Space to continue.";
			
			glColor3f(0.0f, 0.0f, 1.0f);
			glRasterPos2i(50, 250);
			for (int c = 0; c < message5.length(); ++c) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,
					message5[c]);
			}


		}

		

	}
	else {
		glViewport(0, 0, width, height);

		// do an orthographic parallel projection with the coordinate
		// system set to first quadrant, limited by screen/window size

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, width, 0.0, height, -1.f, 1.f);

		glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

		loadTexture(&texture4, "startScreen.jpg");
		drawTexturedRect(0, 0, 500, 500, texture4);

		loadTexture(&texture3, "TRUMPOCALYPSE.png");
		drawTexturedRect(25, 325, 450, 70, texture3);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		glBegin(GL_QUADS);

		if (mouseHover == true) {
			glColor3f(1.00f, 0.00f, 0.00f);
		}
		else {
			glColor3f(1.00f, 1.00f, 1.00f);
		}
		
		glVertex2i(150, 200);
		glVertex2i(350, 200);
		glVertex2i(350, 150);
		glVertex2i(150, 150);

		glEnd();
		

		string message4 = "Start Game";
		
		glColor3f(1.0f, 0.5f, 0.0f);
		glRasterPos2i(195, 170);
		for (int c = 0; c < message4.length(); ++c) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,
				message4[c]);

		}
	}
	glFlush();  // Render now
	if (gameOver == true) {
		sleep_for(3s);
		glutDestroyWindow(wd);
		highScoresIO();
	}
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
	// escape
	if (key == 27) {
		glutDestroyWindow(wd);
		exit(0);
	}
	// space
	if (key == 32) {
		gamePlay = !gamePlay;
	}

	// l/L makes the rectangle larger
	if (key == 'l' || key == 'L') {
		//r.setSideLengths(r.getHeight() + 10, r.getWidth() + 10);
	}

	if (key == 'q' || key == 'Q') {
		SoundEngine->play2D("daughter.wav");
	}



	// s/S makes the rectangle smaller
	if (key == 's' || key == 'S') {
		//r.setSideLengths(r.getHeight() - 10, r.getWidth() - 10);
	}
	glutPostRedisplay();

	return;
}

void kbdS(int key, int x, int y) {
	switch (key) {

	case GLUT_KEY_LEFT:
		t.setX(t.getX() - 20);
		break;
	case GLUT_KEY_RIGHT:
		t.setX(t.getX() + 20);
		break;

	}
		glutPostRedisplay();
		return;
	}

void idle(void) {
	
	if (gameStart==true){
	if (gamePlay == true) {

		if (t.getLives() > 0) {

			SYSTEMTIME time;
			GetSystemTime(&time);
			LONG time_ms = (time.wSecond * 1000) + time.wMilliseconds;


			prev_time = curr_time;
			curr_time = time_ms;
			del_time = curr_time - prev_time;
		

			for (int i = 0; i < asteroids.size(); i++) {

				asteroids[i].checkInteraction(t);
				if (asteroids[i].getHit() == false) {
					if (del_time > 5) { //changes frequency of updates
						if (asteroids[i].getYPos() < 0) {
							asteroidsout.push_back(i);
						}
						else {
							speed = s.timeElapsed() *.4;
							asteroids[i].setYPos(asteroids[i].getYPos() - speed); // changes speed
						}

					}

				}
				else {

					t.setLives(t.getLives() - 1);
					SoundEngine->play2D("wrong.wav");

					asteroids.erase(asteroids.begin() + i);

					
				}

			}

			for (int i = 0; i < powerups.size(); i++) {

				powerups[i].checkInteraction(t);
				if (powerups[i].getHit() == false) {
					if (del_time > 5) { //changes frequency of updates
					
							speed = s.timeElapsed() *.4;
							powerups[i].setYPos(powerups[i].getYPos() - speed); // changes speed
						}

					}
				else {

					t.setLives(t.getLives() + 1);
					SoundEngine->play2D("fantastic.wav");

					powerups.erase(powerups.begin() + i);


				}

			}
			//add asteroids
			if (sec != s.timeElapsed()) {
				

				sec = s.timeElapsed();
				//add asteroids to the falling vector every second
				if (sec % 1 == 0) {
					int randX = rand() % 500 + 1;
					Asteroid temp;
					temp.setXPos(randX);
					asteroids.push_back(temp);
				}

				//add powerups to their vector ever 4 seconds
				if (sec % 4 == 0) {
					int randX = rand() % 500 + 1;
					PowerUp temp;
					temp.setXPos(randX);
					temp.setWidth(70);
					temp.setHeight(40);
					powerups.push_back(temp);
				}

			}
			
			


				
				

			
			if (asteroidsout.size() > 0) {
				for (int c = 0; c < asteroidsout.size(); c++) {
					int temp = asteroidsout.at(c);
					asteroids.erase(asteroids.begin() + temp);

				}
				asteroidsout.clear();

			}
			glutPostRedisplay();
		}
		else {
			gamePlay = false;
			endingScore = s.timeElapsed();
			s.end();
			glutPostRedisplay();
			
			

		}
		}
	}
}


 //button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
 //state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
	if (gameStart == false){
		if (state == GLUT_UP) {
			if (x <= 350 && x >= 150 && y >=300 && y<=350){ //ys are switched, location of start game button
				gameStart = true;
				s.start();
				
			}
		}

	glutPostRedisplay();
}
}

void hover(int x, int y) {

	if (x <= 350 && x >= 150 && y >= 300 && y <= 350) {
		mouseHover = true;
	}
	else {
		mouseHover = false;
	}
	glutPostRedisplay();

}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

	init();

	glutInit(&argc, argv);          // Initialize GLUT

	glutInitDisplayMode(GLUT_RGBA);

	glutInitWindowSize((int)width, (int)height);
	glutInitWindowPosition(500, 100); // Position the window's initial top-left corner
									  /* create the window and store the handle to it */
	wd = glutCreateWindow("Trumpocalypse" /* title */);

	
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	initGL();                       // Our own OpenGL initialization
									// register keyboard press event processing function
									// works for numbers, letters, spacebar, etc.
	glutKeyboardFunc(kbd);

	// register special event: function keys, arrows, etc.
	glutSpecialFunc(kbdS);
	
	// handles mouse movement
	//glutPassiveMotionFunc(cursor);

	// handles mouse click
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(hover);
	glutIdleFunc(idle);
	glutMainLoop();                 // Enter the event-processing loop
	return 0;
}