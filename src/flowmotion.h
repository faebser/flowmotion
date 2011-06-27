#pragma once
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofMain.h"
#include "Controller.h"
#include "Point.h"


class testApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	//void superFastBlur(unsigned char *pix, int w, int h, int radius);

	bool debugOutput;

	ofxKinect 			kinect;
	ofxKinectRecorder 	kinectRecorder;
	ofxKinectPlayer 	kinectPlayer;

	/// used to switch between the live kinect and the recording player
	ofxBase3DVideo* 	kinectSource;

	ofxCvColorImage		colorImg;

	ofxCvGrayscaleImage grayImage;			// grayscale depth image
	ofxCvGrayscaleImage grayThreshNear;		// the near thresholded image
	ofxCvGrayscaleImage grayThreshFar;		// the far thresholded image

	ofxCvContourFinder 	contourFinder;

	bool				bThreshWithOpenCV;
	bool				bDrawPointCloud;

	int 				nearThreshold;
	int					farThreshold;

	int					angle;

	int 				pointCloudRotationY;

	bool 				bRecord;
	bool 				bPlayback;

private:
	Controller controller;
};
