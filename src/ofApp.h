#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCvHaarFinder.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    int camWidth, camHeight;
    
    ofVideoGrabber vidGrabber;
    
    ofxCvHaarFinder finder;
    
    ofxCvColorImage rgb, hsb;
    ofxCvGrayscaleImage hue, sat, bri, filter1, filter2, finalImage;
    
    ofxCvContourFinder contours;
    
    int findHue, findSat;
    
    
    
    //fish stuff
    
    int x = 20;
    int y = 50;
    int imgsource=3;
    int numImgs=4;
    int changeTime=5;
    int xInc=1;
    int yInc=1;
    
    int w = 1100;
    int z =600;
    int wInc=-1;
    int zInc=-1;
    
    int c = 100;
    int d =400;
    int cInc=1;
    int dInc=-1;
    
    
    int e = 800;
    int f =20;
    int eInc=-1;
    int fInc=1;
    
    
    int a = 500;
    int b = 300;
    int aInc=1;
    int bInc=1;
    
    ofImage RDOimgs[4];
    
    ofImage RUOimgs[4];
    
    ofImage LDOimgs[4];
    
    ofImage LUOimgs[4];
    
    ofImage orange[4];
    

    
    ofImage RDWimgs[4];
    
    ofImage RUWimgs[4];
    
    ofImage LDWimgs[4];
    
    ofImage LUWimgs[4];
    
    ofImage white[4];
    
    
    
    ofImage RDBimgs[4];
    
    ofImage RUBimgs[4];
    
    ofImage LDBimgs[4];
    
    ofImage LUBimgs[4];
    
    ofImage black[4];
    
    
    ofImage RDMimgs[4];
    
    ofImage RUMimgs[4];
    
    ofImage LDMimgs[4];
    
    ofImage LUMimgs[4];
    
    ofImage mix[4];
    
    
    
    ofImage lily[1];
    ofImage backgrounds[3];
    
    ofSoundPlayer  sound;
    

    

};
