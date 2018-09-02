//
//  FallingObject.hpp
//  CS 120
//
//  Created by Michelle Niland on 11/17/16.
//  Copyright © 2016 Michelle Niland. All rights reserved.
//

#ifndef FallingObject_hpp
#define FallingObject_hpp

#include "trump.hpp"
#include <string>
#include <math.h>
#include <random>
#include <vector>

using namespace std;


class FallingObject {
public:
	/**
	* Default Constructor
	* Requires: nothing
	* Modifies: 
	* Effects: 
	* Calls: nothing
	*/
	FallingObject();
	/**
	* Non-Default Constructor
	* Requires: nothing
	* Modifies:
	* Effects:
	* Calls: nothing
	*/
	FallingObject(int x, int y, int r, double s);


	/**
	* x Position Getter
	* Requires: nothing
	* Modifies: nothing
	* Effects: gets x position
	* Calls: nothing
	*/
	int getXPos() const;

	/**
	* y Position Getter
	* Requires: nothing
	* Modifies: nothing
	* Effects: gets y position
	* Calls: nothing
	*/
	int getYPos() const;

	int getRadius() const;

	/**
	* Speed Getter
	* Requires: nothing
	* Modifies: nothing
	* Effects: gets speed
	* Calls: nothing
	*/
	double getSpeed() const;

	bool getBottom() const;

	bool getHit() const;

	/**
	* x Position Setter
	* Requires: nothing
	* Modifies: nothing
	* Effects: changes x position
	* Calls: nothing
	*/
	void setXPos(int x);
	/**
	* y Position Setter
	* Requires: nothing
	* Modifies: nothing
	* Effects: changes y position
	* Calls: nothing
	*/
	void setYPos(int y);

	/**
	* radius Setter
	* Requires: nothing
	* Modifies: nothing
	* Effects: changes radius of asteroid
	* Calls: nothing
	*/
	void setRadius(int r);

	/**
	* Speed Setter
	* Requires: nothing
	* Modifies: speed
	* Effects: changes speed
	* Calls: nothing
	*/
	void setSpeed(double s);

	void setBottom(bool b);

	void setHit(bool h);

	// tests to see if the bottom is created takes a the lowest Y coordinate as a parameter. sets bottom to true of Y = Y
	void testIfBottom(int bottomY);

	int StartingX();

	void fall();

	bool checkInteraction(Trump t);
	//pure virtual 
	//makes class abstract
	virtual void effect(Trump &t)=0;

private:
	int xPosition;
	int yPosition;
	int radius;
	double speed;
	bool bottom;
	bool hit =false;


};

class PowerUp : public FallingObject {
public:
	/**
	* Default Constructor
	* Requires: nothing
	* Modifies:
	* Effects:
	* Calls: nothing
	*/
	PowerUp();

	int getWidth() const;

	int getHeight() const;

	void setWidth(int width_in);

	void setHeight(int height_in);

	virtual void effect(Trump &t) override;

private:
	int width;
	int height;
};

class Asteroid : public FallingObject {
public: 
	/**
	* Default Constructor
	* Requires: nothing
	* Modifies:
	* Effects:
	* Calls: nothing
	*/
	Asteroid();


	virtual void effect(Trump &t) override;
private:
};




#endif /* FallingObject_hpp */