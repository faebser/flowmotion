/*
 * Point.h
 *
 *  Created on: 01.06.2011
 *      Author: faebser
 */

#include "ofMain.h"
#include "ofVec3f.h"

#ifndef POINT_H_
#define POINT_H_

class Point {
public:
	Point(int x, int y, int size, int id);
	virtual ~Point();
	void setup();
	void update();
	void draw();
	int getId();
	void newTarget(float x, float y);
private:
	ofVec2f position,target, addedPoint, addedPointTarget;
	int id;
	float speed,size, addedPointSpeed, addedPointSize, maxDistance;
	void calculateAddedPoint();
};

#endif /* POINT_H_ */
