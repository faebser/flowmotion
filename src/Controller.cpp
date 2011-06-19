/*
 * Controller.cpp
 *
 *  Created on: 01.06.2011
 *      Author: faebser
 */

#include "Controller.h"

Controller::Controller() {
	// TODO Auto-generated constructor stub
}

void Controller::update() {
	//udp.update();

	for(unsigned int i = 0;i < points.size(); i++) {
		points[i].update();
	}
}

void Controller::draw() {
	for(unsigned int i = 0;i < points.size(); i++){
		points[i].draw();
	}
}

void Controller::setup() {
	//udp.setup();
	for(int i = 0;i < 50; i++) {
		Point tempPoint(ofRandom(0,(float) ofGetWindowWidth()),ofRandom(0,(float) ofGetWindowHeight()),10,i );
		tempPoint.newTarget( ofRandom(0,(float) ofGetWindowWidth()), ofRandom(0,(float) ofGetWindowHeight()) );
		points.push_back(tempPoint);
	}
}

void Controller::addPoint(int id) {

}

void Controller::removePoint(int id) {

}

bool Controller::pointExists(int id) {
	for(unsigned int i = 0;i < points.size(); i++){
			if(points[i].getId() == id) return true;
		}
	return false;
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}
