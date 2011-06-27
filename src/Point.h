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
	ofVec2f getPosition();
	void drawDebug();
	int getId();
	int gotUpdates();
	float x, y;
	void newTarget(float x, float y);
	void moveToCenter();
	bool getMoveToCenter();
	void breakFree();
	void setAddedPointSize(float size);
private:
	ofVec2f position, target,
			addedPoint, addedPointTarget,
			lastPos;
	int id, notUpdated;
	bool gotUpdate, moveToCenterCheck;
	float speed,size, addedPointSpeed, addedPointSize, addedPointInitalSize, maxDistance, addedPointDistanceToTarget;
	void calculateAddedPoint();
};

#endif /* POINT_H_ */
