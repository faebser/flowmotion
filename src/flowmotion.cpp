#include "flowmotion.h"

//--------------------------------------------------------------
void testApp::setup(){
	debugOutput = true;
	ofBackground(0,0,0);
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
	controller.draw();
	if(debugOutput) {
		grayImage.draw(10, 320, 400, 300);
	}
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
