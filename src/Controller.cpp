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
	for(unsigned int i = 0;i < points.size(); i++) {
		points[i].update();
	}
}

void Controller::getBlobs(vector <ofxCvBlob> inputBlobs) {
	blobs = inputBlobs;
	if(blobs.size() > points.size()) {
		cout << "blobs size: " << blobs.size() << endl;
		cout << "points size: " << points.size() << endl;
		for(int i = blobs.size() - points.size(); i >= 0; i--) {
			addPoint(blobs.size()-i, blobs[blobs.size()-i].centroid);
		}
	}

	for(unsigned int it = 0; it > blobs.size(); it++) {
		points[it].newTarget(blobs[it].centroid.x, blobs[it].centroid.y);
	}
}

void Controller::draw() {
	for(unsigned int i = 0;i < points.size(); i++){
		points[i].draw();
	}
}

void Controller::setup() {
	//udp.setup();

}

void Controller::addPoint(int id , ofPoint pos) {
	Point tempPoint(pos.x, pos.y,10,id );
	tempPoint.newTarget( pos.x, pos.y );
	points.push_back(tempPoint);
}

void Controller::removePoint(int id) {
	points.erase(points.begin()+id);
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
