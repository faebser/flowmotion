/*
 * Point.cpp
 *
 *  Created on: 01.06.2011
 *      Author: faebser
 */

/*
 *  kinect.init(true, false);
        kinect.setVerbose(true);
        if(!kinect.open()) {
                cout << "FUCK YOU! CONNECT A KINECT FIRST!" << endl;
                ofExit();
        }

        kinect.setCameraTiltAngle(conf.rotation);

        kinectCal=&kinect.getCalibration();
        kinectCal->setClippingInCentimeters(conf.minDistance, conf.maxDistance);
 */

#include "Point.h"

Point::Point(int x, int y, int size, int id) {
	this->id = id;
	this->position.x = x;
	this->position.y = y;
	this->size = size;
	maxDistance = 50;
	addedPoint.x = this->position.x + ofRandom(-maxDistance, maxDistance);
	addedPoint.y = this->position.y + ofRandom(-maxDistance, maxDistance);
	speed = 0.01;
	addedPointSpeed = 0.1;
	addedPointInitalSize = 2;
	addedPointSize = addedPointInitalSize;
	target.x = 0;
	target.y = 0;

	this->x = position.x;
	this->y = position.y;

	gotUpdate = false;
	notUpdated = 0;

	addedPointTarget.x = this->position.x + ofRandom(-maxDistance, maxDistance);
	addedPointTarget.y = this->position.y + ofRandom(-maxDistance, maxDistance);
	addedPointDistanceToTarget = maxDistance/10;

	moveToCenterCheck = false;

}

int Point::getId() {
	return id;
}

ofVec2f Point::getPosition() {
	return position;
}

void Point::draw() {
	ofSetColor(255,0,0);
	ofFill();
	ofCircle(addedPoint.x, addedPoint.y, addedPointSize);
}

void Point::drawDebug() {
	ofSetColor(255,255,255);
	ofFill();
	ofCircle(position.x, position.y, size);
}

int Point::gotUpdates() {
	return notUpdated;
}

void Point::setup() {

}

void Point::calculateAddedPoint() { // TODO new target add
	//cout << "unterschied ist ->" << addedPointDistanceToTarget*-1 << endl;
	if(ofDist(addedPoint.x, addedPoint.y, addedPointTarget.x, addedPointTarget.y) <= addedPointDistanceToTarget && moveToCenterCheck == false) {
		addedPointTarget.x = this->position.x + ofRandom(-maxDistance, maxDistance);
		addedPointTarget.y = this->position.y + ofRandom(-maxDistance, maxDistance);
		addedPoint += (addedPointTarget - addedPoint) * addedPointSpeed;
	} else {
		addedPointTarget += (position - lastPos);
		addedPoint += (addedPointTarget - addedPoint) * addedPointSpeed;
	}

	if(moveToCenterCheck) {
		addedPointSize++;
		addedPointTarget = position;
		addedPoint += (addedPointTarget - addedPoint) * addedPointSpeed;
	}

	if(moveToCenterCheck == false && addedPointSize > addedPointInitalSize) { // goes here if the point is moving back from the center
		addedPointSize--;
	}
}

void Point::moveToCenter() {
	addedPointTarget = position;
	moveToCenterCheck = true;
}

bool Point::getMoveToCenter() {
	return moveToCenterCheck;
}

void Point::breakFree() {
	addedPointTarget.x = this->position.x + ofRandom(-maxDistance, maxDistance);
	addedPointTarget.y = this->position.y + ofRandom(-maxDistance, maxDistance);
	moveToCenterCheck = false;
}

void Point::setAddedPointSize(float size) {
	addedPointSize = size;
}

void Point::newTarget(float x, float y) {
	target.x = x;
	target.y = y;
	gotUpdate = true;
}

void Point::update() {
	lastPos = position;
	position += (target - position) * speed;
	calculateAddedPoint();

	x = position.x;
	y = position.y;

	if(gotUpdate) {
		gotUpdate = false;
	} else {
		gotUpdate = false;
		notUpdated++;
	}
}

Point::~Point() {
	// TODO Auto-generated destructor stub
}
