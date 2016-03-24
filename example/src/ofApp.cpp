#include "ofMain.h"
#include "ofxShuffleText.h"

class ofApp : public ofBaseApp {
public:
    const string OF_TEXT = "OPENFRAMEWORKS IS AN OPEN SOURCE C++ TOOLKIT FOR CREATIVE CODING.";
    ofTrueTypeFont font;
    ofxShuffleText text[3];
    
    void setup() {
        ofBackground(0);
        ofSetFrameRate(60);
        
        font.load("verdana.ttf", 12);
        text[0].setup(font, OF_TEXT);
        text[1].setup(font, OF_TEXT);
        
        text[0].setRandomChars(OFX_SHUFFLE_TEXT_NUMBERS
                               | OFX_SHUFFLE_TEXT_UPPER_LETTERS
                               | OFX_SHUFFLE_TEXT_LOWER_LETTERS
                               | OFX_SHUFFLE_TEXT_SYMBOLS);
        
        text[1].setRandomChars(OFX_SHUFFLE_TEXT_UPPER_LETTERS
                               | OFX_SHUFFLE_TEXT_LOWER_LETTERS); // only letters
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
            !text[0].isRunning() ? text[0].start(1.f, 0, false) : text[0].stop();
            !text[1].isRunning() ? text[1].start(1.f, 0, true) : text[1].stop();
        }
    }
};

int main() {
    ofSetupOpenGL(1000, 200, OF_WINDOW);
    ofRunApp(new ofApp());
}