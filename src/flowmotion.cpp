#include "flowmotion.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofEnableBlendMode(OF_BLENDMODE_SCREEN);
	ofBackground(0,0,0,10);
	//ofSetBackgroundAuto(false);

	//ofBackground(0,0,0);
	debugOutput = true;
	controller.setup();
	kinect.init(false,false);
	//kinect.init(true);  // shows infrared instead of RGB video image
	//kinect.init(false, false);  // disable infrared/rgb video iamge (faster fps)
	kinect.setVerbose(true);
	kinect.open();

	// start with the live kinect source
	kinectSource = &kinect;

	colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);

	nearThreshold = 255;
	farThreshold  = 125;
	bThreshWithOpenCV = true;

	ofSetFrameRate(60);

	bRecord = false;
	bPlayback = false;

	// zero the tilt on startup
	angle = 0;
	kinect.setCameraTiltAngle(angle);

	// start from the front
	pointCloudRotationY = 180;
	bDrawPointCloud = false;
}

//--------------------------------------------------------------
void testApp::update(){

	kinectSource->update();

	// there is a new frame and we are connected
	if(kinectSource->isFrameNew()) {

		// record ?
		if(bRecord && kinectRecorder.isOpened()) {
			kinectRecorder.newFrame(kinect.getRawDepthPixels(), kinect.getPixels());
		}

		// load grayscale depth image from the kinect source
		grayImage.setFromPixels(kinectSource->getDepthPixels(), kinect.width, kinect.height);

		// we do two thresholds - one for the far plane and one for the near plane
		// we then do a cvAnd to get the pixels which are a union of the two thresholds
		grayThreshNear = grayImage;
		grayThreshFar = grayImage;
		grayThreshNear.threshold(nearThreshold, true);
		grayThreshFar.threshold(farThreshold);
		cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);

		// update the cv images
		grayImage.flagImageChanged();

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
	}

	controller.getBlobs(contourFinder.blobs);
	controller.update();

}

//--------------------------------------------------------------
void testApp::draw(){

	if(debugOutput) {
		ofSetColor(200);
		grayImage.draw(0, 0, ofGetWidth(), ofGetHeight());
		contourFinder.draw(0, 0, ofGetWidth(), ofGetHeight());
		controller.drawDebug();
	}
	controller.draw();
	/*//TRAIL
	float trail = 16.0;
	//float trail = 16.0;﻿
	glAccum(GL_MULT, trail/32);
	glAccum(GL_ACCUM, 1 - (trail/32));
	glAccum(GL_RETURN, 1);*/
	//ofDisableBlendMode();
}

void testApp::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
	kinectPlayer.close();
	kinectRecorder.close();


}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	switch (key) {

	case '>':
	case '.':
		farThreshold ++;
		if (farThreshold > 255) farThreshold = 255;
		break;

	case '<':
	case ',':
		farThreshold --;
		if (farThreshold < 0) farThreshold = 0;
		break;

	case '+':
	case '=':
		nearThreshold ++;
		if (nearThreshold > 255) nearThreshold = 255;
		break;

	case '-':
		nearThreshold --;
		if (nearThreshold < 0) nearThreshold = 0;
		break;
	case 'd':
		debugOutput = !debugOutput;
		break;
	case OF_KEY_UP:
		angle++;
		if(angle>30) angle=30;
		kinect.setCameraTiltAngle(angle);
		break;

	case OF_KEY_DOWN:
		angle--;
		if(angle<-30) angle=-30;
		kinect.setCameraTiltAngle(angle);
		break;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

// Super Fast Blur v1.1
// by Mario Klingemann <http://incubator.quasimondo.com>
// converted to C++ by Mehmet Akten, <http://www.memo.tv>
//
// Tip: Multiple invovations of this filter with a small
// radius will approximate a gaussian blur quite well.
//

/*void testApp::superFastBlur(unsigned char *pix, int w, int h, int radius) {

	if (radius<1) return;
	int wm=w-1;
	int hm=h-1;
	int wh=w*h;
	int div=radius+radius+1;
	unsigned char *r=new unsigned char[wh];
	unsigned char *g=new unsigned char[wh];
	unsigned char *b=new unsigned char[wh];
	int rsum,gsum,bsum,x,y,i,p,p1,p2,yp,yi,yw;
	int *vMIN = new int[MAX(w,h)];
	int *vMAX = new int[MAX(w,h)];

	unsigned char *dv=new unsigned char[256*div];
	for (i=0;i<256*div;i++) dv[i]=(i/div);

	yw=yi=0;

	for (y=0;y<h;y++){
		rsum=gsum=bsum=0;
		for(i=-radius;i<=radius;i++){
			p = (yi + MIN(wm, MAX(i,0))) * 3;
			rsum += pix[p];
			gsum += pix[p+1];
			bsum += pix[p+2];
		}
		for (x=0;x<w;x++){

			r[yi]=dv[rsum];
			g[yi]=dv[gsum];
			b[yi]=dv[bsum];

			if(y==0){
				vMIN[x]=MIN(x+radius+1,wm);
				vMAX[x]=MAX(x-radius,0);
			}
			p1 = (yw+vMIN[x])*3;
			p2 = (yw+vMAX[x])*3;

			rsum += pix[p1]		- pix[p2];
			gsum += pix[p1+1]	- pix[p2+1];
			bsum += pix[p1+2]	- pix[p2+2];

			yi++;
		}
		yw+=w;
	}

	for (x=0;x<w;x++){
		rsum=gsum=bsum=0;
		yp=-radius*w;
		for(i=-radius;i<=radius;i++){
			yi=MAX(0,yp)+x;
			rsum+=r[yi];
			gsum+=g[yi];
			bsum+=b[yi];
			yp+=w;
		}
		yi=x;
		for (y=0;y<h;y++){
			pix[yi*3]		= dv[rsum];
			pix[yi*3 + 1]	= dv[gsum];
			pix[yi*3 + 2]	= dv[bsum];
			if(x==0){
				vMIN[y]=MIN(y+radius+1,hm)*w;
				vMAX[y]=MAX(y-radius,0)*w;
			}
			p1=x+vMIN[y];
			p2=x+vMAX[y];

			rsum+=r[p1]-r[p2];
			gsum+=g[p1]-g[p2];
			bsum+=b[p1]-b[p2];

			yi+=w;
		}
	}

	delete r;
	delete g;
	delete b;

	delete vMIN;
	delete vMAX;
	delete dv;
}*/

