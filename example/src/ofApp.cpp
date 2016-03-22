#include "ofMain.h"
#include "ofxShuffleText.h"

class ofApp : public ofBaseApp {
public:
    const string OF_TEXT = "OPENFRAMEWORKS IS AN OPEN SOURCE C++ TOOLKIT FOR CREATIVE CODING.";
    ofTrueTypeFont font;
    ofxShuffleText text[3];
    
    void setup() {
        ofBackground(0);
        ofSetFrameRate(30);
        
        font.load("verdana.ttf", 12);
        text[0].setup(font, OF_TEXT, false, 1.f);
        text[1].setup(font, OF_TEXT, true, 1.f);
    }

    void update() {
        text[0].update();
        text[1].update();
    }

    void draw() {
        ofSetColor(255);
        text[0].draw(40, 60);
        text[1].draw(40, 90);
    }
    
    void keyPressed(int key) {
        if (key == ' ') {
            !text[0].isRunning() ? text[0].start() : text[0].stop();
            !text[1].isRunning() ? text[1].start() : text[1].stop();
        }
    }
};

int main() {
    ofSetupOpenGL(1000, 200, OF_WINDOW);
    ofRunApp(new ofApp());
}