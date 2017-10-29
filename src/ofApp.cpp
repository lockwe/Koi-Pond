#include "ofApp.h"

bool showStuff = true;

bool showContour = false;

//--------------------------------------------------------------
void ofApp::setup(){
    
    camWidth = 640;
    camHeight = 480;
    
    vidGrabber.setDeviceID(0);
    vidGrabber.initGrabber(camWidth, camHeight);

    
    //alocates memory for each of these value
    
    rgb.allocate(camWidth, camHeight);
    hsb.allocate(camWidth, camHeight);
    hue.allocate(camWidth, camHeight);
    sat.allocate(camWidth, camHeight);
    bri.allocate(camWidth, camHeight);
    filter1.allocate(camWidth, camHeight);
    filter2.allocate(camWidth, camHeight);
    finalImage.allocate(camWidth, camHeight);

    
    

    sound.load("pond_sound.wav");
    sound.setLoop(true);
    sound.play();
    
//fish stuff starts here
    
    //orange fish
    RDOimgs[0].load("RDO1.png");
    RDOimgs[1].load("RDO2.png");
    RDOimgs[2].load("RDO3.png");
    RDOimgs[3].load("RDO4.png");
    
    RUOimgs[0].load("RUO1.png");
    RUOimgs[1].load("RUO2.png");
    RUOimgs[2].load("RUO3.png");
    RUOimgs[3].load("RUO4.png");
    
    LDOimgs[0].load("LDO1.png");
    LDOimgs[1].load("LDO2.png");
    LDOimgs[2].load("LDO3.png");
    LDOimgs[3].load("LDO4.png");
    
    LUOimgs[0].load("LUO1.png");
    LUOimgs[1].load("LUO2.png");
    LUOimgs[2].load("LUO3.png");
    LUOimgs[3].load("LUO4.png");
    
    
    //whitefish
    RDWimgs[0].load("RDW1.png");
    RDWimgs[1].load("RDW2.png");
    RDWimgs[2].load("RDW3.png");
    RDWimgs[3].load("RDW4.png");
    
    RUWimgs[0].load("RUW1.png");
    RUWimgs[1].load("RUW2.png");
    RUWimgs[2].load("RUW3.png");
    RUWimgs[3].load("RUW4.png");
    
    LDWimgs[0].load("LDW1.png");
    LDWimgs[1].load("LDW2.png");
    LDWimgs[2].load("LDW3.png");
    LDWimgs[3].load("LDW4.png");
    
    LUWimgs[0].load("LUW1.png");
    LUWimgs[1].load("LUW2.png");
    LUWimgs[2].load("LUW3.png");
    LUWimgs[3].load("LUW4.png");
    
    //blackfish
    RDBimgs[0].load("RDB1.png");
    RDBimgs[1].load("RDB2.png");
    RDBimgs[2].load("RDB3.png");
    RDBimgs[3].load("RDB4.png");
    
    RUBimgs[0].load("RUB1.png");
    RUBimgs[1].load("RUB2.png");
    RUBimgs[2].load("RUB3.png");
    RUBimgs[3].load("RUB4.png");
    
    LDBimgs[0].load("LDB1.png");
    LDBimgs[1].load("LDB2.png");
    LDBimgs[2].load("LDB3.png");
    LDBimgs[3].load("LDB4.png");
    
    LUBimgs[0].load("LUB1.png");
    LUBimgs[1].load("LUB2.png");
    LUBimgs[2].load("LUB3.png");
    LUBimgs[3].load("LUB4.png");
    
    
    //mixedfish
    RDMimgs[0].load("RDM1.png");
    RDMimgs[1].load("RDM2.png");
    RDMimgs[2].load("RDM3.png");
    RDMimgs[3].load("RDM4.png");
    
    RUMimgs[0].load("RUM1.png");
    RUMimgs[1].load("RUM2.png");
    RUMimgs[2].load("RUM3.png");
    RUMimgs[3].load("RUM4.png");
    
    LDMimgs[0].load("LDM1.png");
    LDMimgs[1].load("LDM2.png");
    LDMimgs[2].load("LDM3.png");
    LDMimgs[3].load("LDM4.png");
    
    LUMimgs[0].load("LUM1.png");
    LUMimgs[1].load("LUM2.png");
    LUMimgs[2].load("LUM3.png");
    LUMimgs[3].load("LUM4.png");
    
    

    lily[0].load("lilypad.png");
    
    backgrounds[0].load("bluebackground.png");
    backgrounds[1].load("lillies.png");
    backgrounds[2].load("KoiPond.png");


}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSoundUpdate();
    
    //video stuff
    
    vidGrabber.update();
    
    
    if(vidGrabber.isFrameNew()){
        
        rgb.setFromPixels(vidGrabber.getPixels());
        rgb.mirror(false, true);
        hsb = rgb;
        hsb.convertRgbToHsv();
        hsb.convertToGrayscalePlanarImages(hue, sat, bri);
        
        int hueRange = 20;
        for (int i =0; i < camWidth * camHeight; ++i){
            filter1.getPixels()[i] = ofInRange(hue.getPixels()[i], findHue - hueRange, findHue + hueRange) ? 255: 0;
        }
                filter1.flagImageChanged();
        
        int satRange = 20;
        for (int i =0; i < camWidth * camHeight; ++i){
            filter2.getPixels()[i] = ofInRange(sat.getPixels()[i], findSat - satRange, findSat + satRange) ? 255: 0;
        }
                filter2.flagImageChanged();
        
        cvAnd(filter1.getCvImage(), filter2.getCvImage(), finalImage.getCvImage());
        finalImage.flagImageChanged();
        
        contours.findContours(finalImage, 50, (camWidth*camHeight)/3, 3, false);

        
    }
    
    
    
    //fish stuff
    
    changeTime=changeTime-1;
    if(changeTime==0){
        ++imgsource;
        imgsource=imgsource%numImgs;
        changeTime=10;
    }
    
    x = x+xInc;
    y = y+yInc;
    
    w = w+wInc;
    z = z+zInc;
    
    c = c+cInc;
    d = d+dInc;
    
    e = e+eInc;
    f = f+fInc;

    
    
    
    
    if (x < 0){
        xInc*=-1;
    }
    
    if(x>1125){
        xInc*=-1;
    }
    if ( y < 0 ){
        yInc*=-1;
    }
    if(y>650){
        yInc*=-1;
    }
    
    //Lilly Hit
    
    if (xInc == 1 && yInc == 1){
        ofPoint p = ofVec2f(x+150, y+150);
        ofPoint p2 = ofVec2f(a+75, b+75);
        if (75>p.distance(p2)){
            xInc*=-1;
            yInc*=-1;
            cout << "hitbottomright" << endl;
        }
    }
    
    if (xInc == -1 && yInc == 1){
        ofPoint p = ofVec2f(x, y+150);
        ofPoint p2 = ofVec2f(a+75, b+75);

        if (75>p.distance(p2)){
            xInc*=-1;
            yInc*=-1;
            cout << "hitbottomleft" << endl;
        }
    }
    
    if (xInc == -1 && yInc == -1){
        ofPoint p = ofVec2f(x, y);
        ofPoint p2 = ofVec2f(a+75, b+75);
        if (75>p.distance(p2)){
                xInc*=-1;
                yInc*=-1;
            cout << "hittopleft" << endl;
        }
    }
    
     if (xInc == 1 && yInc == -1){
     ofPoint p = ofVec2f(x+150, y);
     ofPoint p2 = ofVec2f(a+75, b+75);
         if (75>p.distance(p2)){
             xInc*=-1;
             yInc*=-1;
             cout << "hittopright" << endl;
         }
     }
    
//white fish
    
    if (w < 0){
        wInc*=-1;
    }
    
    if(w>1125){
        wInc*=-1;
    }
    if ( z < 0 ){
        zInc*=-1;
    }
    if(z>650){
        zInc*=-1;
    }
    
    //Lilly Hit
    
    if (wInc == 1 && zInc == 1){
        ofPoint p = ofVec2f(w+200, z+200);
        ofPoint p2 = ofVec2f(a+75, b+75);
        if (75>p.distance(p2)){
            wInc*=-1;
            zInc*=-1;
        }
    }
    
    if (wInc == -1 && zInc == 1){
        ofPoint p = ofVec2f(w, z+200);
        ofPoint p2 = ofVec2f(a+75, b+75);
        if (75>p.distance(p2)){
            wInc*=-1;
            zInc*=-1;
        }
    }
    
    if (wInc == -1 && zInc == -1){
        ofPoint p = ofVec2f(w, z);
        ofPoint p2 = ofVec2f(a+75, b+75);
        if (75>p.distance(p2)){
            wInc*=-1;
            zInc*=-1;
        }
    }
    
    if (wInc == 1 && zInc == -1){
        ofPoint p = ofVec2f(w+200, z);
        ofPoint p2 = ofVec2f(a+75, b+75);
        if (75>p.distance(p2)){
            wInc*=-1;
            zInc*=-1;
        }
    }
    
    
//black fish
    
    if (c < 0){
        cInc*=-1;
    }
    
    if(c>1125){
        cInc*=-1;
    }
    if (d < 0 ){
        dInc*=-1;
    }
    if(d>650){
        dInc*=-1;
    }
    
    //Lilly Hit
    
    if (cInc == 1 && dInc == 1){
        ofPoint p = ofVec2f(c+175, d+175);
        ofPoint p2 = ofVec2f(a+75, b+75);
        if (75>p.distance(p2)){
            cInc*=-1;
            dInc*=-1;
        }
    }
    
    if (cInc == -1 && dInc == 1){
        ofPoint p = ofVec2f(c, d+175);
        ofPoint p2 = ofVec2f(a+75, b+75);
        
        if (75>p.distance(p2)){
            cInc*=-1;
            dInc*=-1;
        }
    }
    
    if (cInc == -1 && dInc == -1){
        ofPoint p = ofVec2f(c, d);
        ofPoint p2 = ofVec2f(a+75, b+75);
        if (75>p.distance(p2)){
            cInc*=-1;
            dInc*=-1;
        }
    }
    
    if (cInc == 1 && dInc == -1){
        ofPoint p = ofVec2f(c+175, d);
        ofPoint p2 = ofVec2f(a+75, b+75);
        if (75>p.distance(p2)){
            cInc*=-1;
            dInc*=-1;
        }
    }
    
    
    
    //mixed fish
    
    if (e < 0){
        eInc*=-1;
    }
    
    if(e>1125){
        eInc*=-1;
    }
    if (f < 0 ){
        fInc*=-1;
    }
    if(f>650){
        fInc*=-1;
    }
    
    //Lilly Hit
    
    if (eInc == 1 && fInc == 1){
        ofPoint p = ofVec2f(e+125, f+125);
        ofPoint p2 = ofVec2f(a+75, b+75);
        if (75>p.distance(p2)){
            eInc*=-1;
            fInc*=-1;
        }
    }
    
    if (eInc == -1 && fInc == 1){
        ofPoint p = ofVec2f(e, f+125);
        ofPoint p2 = ofVec2f(a+75, b+75);
        
        if (75>p.distance(p2)){
            eInc*=-1;
            fInc*=-1;
        }
    }
    
    if (eInc == -1 && fInc == -1){
        ofPoint p = ofVec2f(e, f);
        ofPoint p2 = ofVec2f(a+75, b+75);
        if (75>p.distance(p2)){
            eInc*=-1;
            fInc*=-1;
        }
    }
    
    if (eInc == 1 && fInc == -1){
        ofPoint p = ofVec2f(e+125, f);
        ofPoint p2 = ofVec2f(a+75, b+75);
        if (75>p.distance(p2)){
            eInc*=-1;
            fInc*=-1;
        }
    }
    
        
        
        //ANIMATION
    
    //orange fish
    
    if (xInc == 1 && yInc == 1){
        orange[0] = RDOimgs[0];
        orange[1] = RDOimgs[1];
        orange[2] = RDOimgs[2];
        orange[3] = RDOimgs[3];
    }
    
    if (xInc == -1 && yInc == 1){
        orange[0] = LDOimgs[0];
        orange[1] = LDOimgs[1];
        orange[2] = LDOimgs[2];
        orange[3] = LDOimgs[3];
        }

    
    if (xInc == -1 && yInc == -1){
        orange[0] = LUOimgs[0];
        orange[1] = LUOimgs[1];
        orange[2] = LUOimgs[2];
        orange[3] = LUOimgs[3];
    }
    
    if (xInc == 1 && yInc == -1){
        orange[0] = RUOimgs[0];
        orange[1] = RUOimgs[1];
        orange[2] = RUOimgs[2];
        orange[3] = RUOimgs[3];
    }
    
    
    //white fish
  
    if (wInc == 1 && zInc == 1){
        white[0] = RDWimgs[0];
        white[1] = RDWimgs[1];
        white[2] = RDWimgs[2];
        white[3] = RDWimgs[3];
    }
    
    if (wInc == -1 && zInc == 1){
        white[0] = LDWimgs[0];
        white[1] = LDWimgs[1];
        white[2] = LDWimgs[2];
        white[3] = LDWimgs[3];
    }
    
    
    if (wInc == -1 && zInc == -1){
        white[0] = LUWimgs[0];
        white[1] = LUWimgs[1];
        white[2] = LUWimgs[2];
        white[3] = LUWimgs[3];
    }
    
    if (wInc == 1 && zInc == -1){
        white[0] = RUWimgs[0];
        white[1] = RUWimgs[1];
        white[2] = RUWimgs[2];
        white[3] = RUWimgs[3];
    }
    
    
    //black fish
    
    if (cInc == 1 && dInc == 1){
        black[0] = RDBimgs[0];
        black[1] = RDBimgs[1];
        black[2] = RDBimgs[2];
        black[3] = RDBimgs[3];
    }
    
    if (cInc == -1 && dInc == 1){
        black[0] = LDBimgs[0];
        black[1] = LDBimgs[1];
        black[2] = LDBimgs[2];
        black[3] = LDBimgs[3];
    }
    
    
    if (cInc == -1 && dInc == -1){
        black[0] = LUBimgs[0];
        black[1] = LUBimgs[1];
        black[2] = LUBimgs[2];
        black[3] = LUBimgs[3];
    }
    
    if (cInc == 1 && dInc == -1){
        black[0] = RUBimgs[0];
        black[1] = RUBimgs[1];
        black[2] = RUBimgs[2];
        black[3] = RUBimgs[3];
    }
    
    //mixed fish
    
    if (eInc == 1 && fInc == 1){
        mix[0] = RDMimgs[0];
        mix[1] = RDMimgs[1];
        mix[2] = RDMimgs[2];
        mix[3] = RDMimgs[3];
    }
    
    if (eInc == -1 && fInc == 1){
        mix[0] = LDMimgs[0];
        mix[1] = LDMimgs[1];
        mix[2] = LDMimgs[2];
        mix[3] = LDMimgs[3];
    }
    
    
    if (eInc == -1 && fInc == -1){
        mix[0] = LUMimgs[0];
        mix[1] = LUMimgs[1];
        mix[2] = LUMimgs[2];
        mix[3] = LUMimgs[3];
    }
    
    if (eInc == 1 && fInc == -1){
        mix[0] = RUMimgs[0];
        mix[1] = RUMimgs[1];
        mix[2] = RUMimgs[2];
        mix[3] = RUMimgs[3];
    }
  
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //draws fish and background
    
    backgrounds[0].draw(0,0);
    
    orange[imgsource].draw(x,y,150,150);
    
    white[imgsource].draw(w,z,200,200);
    
    black[imgsource].draw(c,d,175,175);
    
    mix[imgsource].draw(e,f,125,125);
    
    
    
    if (contours.blobs.size() > 0){
        a = contours.blobs[0].boundingRect.getMinX()*2;
        b = contours.blobs[0].boundingRect.getMinY()*1.67;
        lily[0].draw(a,b,150,150);
    }

    backgrounds[1].draw(0,0);
    
    
    //FACE TRACKING
    
    if (showStuff){
        
        ofSetColor(ofColor::white);
        backgrounds[2].draw(0,0);
        rgb.draw(320,210,camWidth,camHeight);
        
        //draws the contour
        ofPushMatrix();
        ofScale(2,1.67,0);
        if (showContour){
            contours.draw(0,0);
        }
        ofPopMatrix();
        
    }
    
    

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if (key == ' '){
        showStuff = !showStuff;
    }
    
    if (key == 'c'){
        showContour = !showContour;
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    //tells you to only pick things inside the camera image
    int mx = (x-320) % camWidth;
    int my = (y-210) % camHeight;
    
    //puts the hue where it is
    findHue = hue.getPixels()[my*camWidth +mx ];
    findSat = sat.getPixels()[my*camWidth+mx];


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
