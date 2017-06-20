#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxSyphon.h"

class ofApp : public ofBaseApp{
    
public:
    ofMesh mesh;
    vector<ofVec3f> offsets;
    
    ofxSyphonServer syphonServer;
    
    ofImage image;
    ofImage maskImage;
    
    ofxDatGui* gui;
    vector<ofxDatGuiComponent*> components;
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void resetMesh(ofColor col);
    void setupGui();
    
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
    
    
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onToggleEvent(ofxDatGuiToggleEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
    
    
};
