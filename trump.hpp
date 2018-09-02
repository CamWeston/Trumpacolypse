#ifndef trump_hpp
#define trump_hpp
#include <string>
#include <random>
#include <time.h>
using namespace std;

class Trump {
public:
	Trump();

	Trump(int lives_in, int x_in, int y_in, int height_in, int width_in);

	int getWidth() const;

	int getHeight() const;

	int getLives() const;

	int getX() const;

	int getY() const;

	void setX(int x_in);

	void setY(int y_in);

	void setWidth(int width_in);

	void setHeight(int height_in);

	void setLives(int lives_in);
private:
	int height;
	int width;
	int y;
	int x;
	int lives;

};

class Window { //created in init function edit sizes here
public:
	Window();

	Window(int width_in, int height_in,int position1_in, int position2_in);

	int getWidth() const;

	int getHeight() const;

	int getPosition1() const;

	int getPosition2() const;

	void setWidth(int width_in);

	void setHeight(int height_in);

	void setPosition1(int position1_in);

	void setPosition2(int position2_in);

private:
	int width;
	int height;
	int position1;
	int position2;
};

class Score {
public:
	Score();

	bool getEnd() const;

	void setEnd(bool end_in);

	int getScore() const;

	void setScore(int score_in);

private:
	int score;

	bool end;
};



#endif