#include "trump.hpp"
#include <random>
#include <math.h>
#include <time.h>
#include <random>

// create an array of asteroid objects 


Trump::Trump(int lives_in, int x_in, int y_in, int height_in, int width_in) {
	lives = lives_in;
	x = x_in;
	y = y_in;
	height = height_in;
	width = width_in;
}

Trump::Trump() {
	lives = 3;
	x = 0;
	y = 0;
	height = 20;
	width = 15;
}

int Trump::getLives() const {
	return lives;
}

int Trump::getX() const {
	return x;
}

int Trump::getY() const {
	return y;
}

int Trump::getHeight() const {
	return height;
}

int Trump::getWidth() const {
	return width;
}

void Trump::setLives(int lives_in) {
	lives = lives_in;
}

void Trump::setX(int x_in) {
	x = x_in;
}

void Trump::setY(int y_in) {
	y = y_in;
}

void Trump::setWidth(int width_in) {
	width = width_in;
}

void Trump::setHeight(int height_in) {
	height = height_in;
}



Window::Window(int width_in, int height_in, int position1_in, int position2_in) {
	width = width_in;
	height = height_in;
	position1 = position1_in;
	position2 = position2_in;

}

Window::Window() {
	width = 0;
	height = 0;
	position1 = 0;
	position2 = 0;

}

int Window::getHeight() const {
	return height;
}

int Window::getWidth() const {
	return width;
}

int Window::getPosition1() const {
	return position1;
}

int Window::getPosition2() const {
	return position2;
}

void Window::setPosition1(int position1_in) {
	position1 = position1_in;
}

void Window::setPosition2(int position2_in) {
	position2 = position2_in;
}

void Window::setWidth(int width_in) {
	width = width_in;
}

void Window::setHeight(int height_in) {
	height = height_in;
}

Score::Score() {
	score = 0;
	end = false;
}

bool Score::getEnd() const {
	return end;
}

void Score::setEnd(bool end_in) {
	end = end_in;
}

int Score::getScore() const {
	return score;
}

void Score::setScore(int score_in) {
	score = score_in;
}


