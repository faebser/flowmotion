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
	maxDistance = 15;
	addedPoint.x = this->position.x + ofRandom(maxDistance);
	addedPoint.y = this->position.y + ofRandom(maxDistance);
	speed = 0.01;
	addedPointSpeed = 0.02;
	addedPointSize = 2;
	target.x = 0;
	target.y = 0;
}

int Point::getId() {
	return id;
}

void Point::draw() {
	ofSetColor(255,255,255);
	ofFill();
	ofCircle(position.x, position.y, size);
	ofSetColor(255,0,0);
	ofFill();
	ofCircle(addedPoint.x, addedPoint.y, addedPointSize);
}

void Point::setup() {

}

void Point::calculateAddedPoint() {

}

void Point::newTarget(float x, float y) {
	target.x = x;
	target.y = y;
}

void Point::update() {
	position += (target - position) * speed;
	calculateAddedPoint();
}

Point::~Point() {
	// TODO Auto-generated destructor stub
}
