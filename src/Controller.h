/*
 * Controller.h
 *
 *  Created on: 01.06.2011
 *      Author: faebser
 */
#include "Point.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

class Controller {
public:
	Controller();
	virtual ~Controller();
	void setup();
	void update();
	void draw();
	void drawDebug();
	void addPoint(int id, ofPoint pos);
	void removePoint(int id);
	bool pointExists(int id);
	void getBlobs(vector <ofxCvBlob> inputBlobs);
private:
	static const int updateLimit = 60;
	static const float farDistance = 60;
	vector <Point> points;
	vector <ofxCvBlob> blobs;

};



#endif /* CONTROLLER_H_ */
