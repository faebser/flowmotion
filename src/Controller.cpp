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
	for(unsigned int it = 0; it < blobs.size(); it++) {
		points[it].newTarget(blobs[it].centroid.x, blobs[it].centroid.y);
	}

	for(unsigned int i = 0;i < points.size(); i++) {
		points[i].update();
	}

	for(unsigned int i = 0;i < points.size(); i++) {
		ofVec2f pos = points[i].getPosition();
		bool check = points[i].getMoveToCenter();
		if(check) {
			check = false;
			for(unsigned int inner = 0;inner < points.size(); inner++) {
				if(i != inner) {
					if(ofDist(pos.x, pos.y, points[inner].x, points[inner].y) < farDistance)
					{
						points[i].moveToCenter();
						points[inner].moveToCenter();
						check = true;
					}
				}
				if(check == false) {
					points[i].breakFree();
				}
			}
		} else {
			for(unsigned int inner = 0;inner < points.size(); inner++) {
				if(i != inner) {
					if(ofDist(pos.x, pos.y, points[inner].x, points[inner].y) < farDistance)
					{
						points[i].moveToCenter();
						points[inner].moveToCenter();
					}
				}
			}
		}
	}

	vector<Point>::iterator it;
	for(it = points.begin(); it < points.end(); it++ ) {
		if( (*it).gotUpdates() > updateLimit) {
			points.erase(it);
		}
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
}

void Controller::draw() {
	for(unsigned int i = 0;i < points.size(); i++){
		points[i].draw();
	}
}

void Controller::drawDebug() {
	for(unsigned int i = 0;i < points.size(); i++){
		points[i].drawDebug();
	}
}

void Controller::setup() {
	//udp.setup();

}

void Controller::addPoint(int id , ofPoint pos) {
	Point tempPoint(pos.x, pos.y,10,id );
	//tempPoint.newTarget( pos.x, pos.y );
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
