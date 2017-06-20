//  @luiscript 2017
//  generative tool x

#include "ofApp.h"

float displacement = 0;
float times = 0;
float lineWidth = 0.0;
Boolean mask = false;
ofColor meshColor(0,0, 0, 30);


void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetWindowPosition(0, 0);
    ofSetWindowShape(1920, 1080);
    
    syphonServer.setName("luiscriptGenerative");
    
    image.load("outline.png");
    image.resize(480, 270);
    
    maskImage.load("mask.png");
    
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableIndices();
    resetMesh(meshColor);
    
    setupGui();
    
    ofSetWindowTitle("@luiscript. 2017");
}


void ofApp::update(){
    int numVerts = mesh.getNumVertices();
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);
        
        float time = ofGetElapsedTimef();
        float timeScale = times;
        float displacementScale = displacement;
        ofVec3f timeOffsets = offsets[i];
        
        vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
        vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * displacementScale;
        vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * displacementScale;
        mesh.setVertex(i, vert);
    }
    for(int i=0; i<components.size(); i++) components[i]->update();
    
}


void ofApp::draw(){
    ofBackground(255);
    
    ofPushMatrix();
    ofSetLineWidth(lineWidth);
    ofSetColor(0,0,0);
    ofTranslate(-93, -52);
    ofScale(1.1, 1.1);
    mesh.draw();
    ofPopMatrix();
    
    
    if(mask){
        maskImage.draw(0,0);
    }
    
    syphonServer.publishScreen();
    
    for(int i=0; i<components.size(); i++) components[i]->draw();
    
}

void ofApp::resetMesh(ofColor col){
    //technique based on this example
    //http://openframeworks.cc/ofBook/chapters/generativemesh.html#generativemeshusinganimagetodrivethecreationofamesh
    mesh.clear();
    float intensityThreshold = 5.0;
    int w = image.getWidth();
    int h = image.getHeight();
    for (int x=0; x<w; ++x) {
        for (int y=0; y<h; ++y) {
            ofColor c = image.getColor(x, y);
            
            float intensity = c.getLightness();
            if (intensity >= intensityThreshold) {
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, -100, 100);
                ofVec3f pos(x*4, y*4, z);
                mesh.addVertex(pos);
                mesh.addColor(col);
                
                offsets.push_back(ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
            }
        }
    }
    
    float connectionDistance = 30;
    int numVerts = mesh.getNumVertices();
    for (int a=0; a<numVerts; ++a) {
        ofVec3f verta = mesh.getVertex(a);
        for (int b=a+1; b<numVerts; ++b) {
            ofVec3f vertb = mesh.getVertex(b);
            float distance = verta.distance(vertb);
            if (distance <= connectionDistance) {
                
                mesh.addIndex(a);
                mesh.addIndex(b);
            }
            
        }
    }
}

void ofApp::setupGui(){
    
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    
    gui->addHeader(":: luiscript generative tool 2017 ::");
    gui->addFRM();
    gui->addBreak();
    
    gui->addColorPicker("Color", ofColor::fromHex(0x000000));
    gui->addButton("Reset mesh");
    gui->addToggle("Mask");
    gui->addSlider("Displacement", 0, 20, 0);
    gui->addSlider("Times", 0, 20, 0);
    gui->addSlider("Line width", 0, 10, 0);
    
    vector<string> options = {"LINES", "LINE_LOOP", "TRIANGLE", "TRIANGLE_FAN"};
    gui->addDropdown("draw mode", options);
    
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onToggleEvent(this, &ofApp::onToggleEvent);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    gui->onDropdownEvent(this, &ofApp::onDropdownEvent);
    gui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
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

void ofApp::exit(){
    
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e){
    resetMesh(meshColor);
}

void ofApp::onToggleEvent(ofxDatGuiToggleEvent e){
    if (e.target->getLabel() == "Mask") {
        mask = !mask;
    }
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e){
    
    if(e.target->getLabel() == "Displacement"){
        displacement = e.value;
    }
    
    if(e.target->getLabel() == "Times"){
        times = e.value;
    }
    
    if (e.target->getLabel() == "Line width") {
        lineWidth = e.value;
    }
    
}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e){
    if(e.child == 0){
        mesh.setMode(OF_PRIMITIVE_LINES);
    }
    if(e.child == 1){
        mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    }
    if(e.child == 2){
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    }
    if(e.child == 3){
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    }
}

void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e){
    meshColor = ofColor(e.color.r, e.color.g, e.color.b, 30);
    resetMesh(meshColor);
}


