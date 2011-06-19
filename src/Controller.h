/*
 * Controller.h
 *
 *  Created on: 01.06.2011
 *      Author: faebser
 */
#include "Point.h"
//#include "UdpController.h"


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

class Controller {
public:
	Controller();
	virtual ~Controller();
	void setup();
	void update();
	void draw();
	void addPoint(int id);
	void removePoint(int id);
	bool pointExists(int id);
private:
	vector <Point> points;
	//UdpController udp;
};

#endif /* CONTROLLER_H_ */
