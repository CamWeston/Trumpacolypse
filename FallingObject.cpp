//
//  FallingObject.cpp
//  CS 120
//
//  Created by Michelle Niland on 11/17/16.
//  Copyright © 2016 Michelle Niland. All rights reserved.
//

#include "FallingObject.hpp"
#include <iostream>
using namespace std;

// every falling object has an update speed
FallingObject::FallingObject() {
	speed = 0;
	xPosition = 0;
	yPosition = 0;
	bottom = false;
}

FallingObject::FallingObject(int x, int y, int r, double s) {
	speed = s;
	xPosition = x;
	yPosition = y;
	radius = r;
	bottom = false;

}

int FallingObject::getXPos() const{
	return xPosition;
}

int FallingObject::getYPos() const{
	return yPosition;
}

int FallingObject::getRadius() const
{
	return radius;
}

double FallingObject::getSpeed() const{
	return speed;
}

bool FallingObject::getBottom() const {
	return bottom;
}

bool FallingObject::getHit() const
{
	return hit;
}

void FallingObject::setXPos(int x){
	xPosition = x;
}

void FallingObject::setYPos(int y){
	yPosition = y;

}

void FallingObject::setRadius(int r){
	radius = r;
}

void FallingObject::setSpeed(double s){
	speed = s;
}

void FallingObject::setBottom(bool b) {
	bottom = b;
}

void FallingObject::setHit(bool h){
	hit = h;
}

void FallingObject::testIfBottom(int bottomY) {
	if (yPosition <= bottomY) {
		bottom = true;
	}
}

int FallingObject::StartingX()
{
	return rand() % 500 +1;
}

void FallingObject::fall(){
	cout << "Asteroid Fall" << endl;


}

bool FallingObject::checkInteraction(Trump t){
	//calculate 4 corners
	int tx1 = t.getX();
	int ty1 = t.getY();
	int tx2 = tx1 + t.getWidth();
	int ty2 = ty1;
	int tx3 = tx2;
	int ty3 = ty2 + t.getHeight();
	int tx4 = tx1;
	int ty4 = ty1 + t.getHeight();

	//check intersecton of falling object and trump 
	if ((xPosition > tx1 & xPosition < tx2) & (yPosition > ty1 & yPosition < ty4)) {
		
		hit = true;
		
	}
	else {
		
		hit = false;
	}
	setHit(hit);
	return hit;
}

PowerUp::PowerUp() : FallingObject(StartingX(),500,10, 5) {
}

int PowerUp::getHeight() const {
	return height;
}

int PowerUp::getWidth() const {
	return width;
}

void PowerUp::setWidth(int width_in) {
	width = width_in;
}

void PowerUp::setHeight(int height_in) {
	height = height_in;
}
void PowerUp::effect(Trump &t) {
	t.setLives(t.getLives() + 1);
}
Asteroid::Asteroid() : FallingObject(StartingX(),500,10,10) {
}


void Asteroid::effect(Trump &t){
	t.setLives(t.getLives()-1);
}
