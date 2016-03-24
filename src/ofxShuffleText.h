//
//  ofxShuffleText.h
//
//  Created by Kenta Watashima on 3/22/16.
//
//

#pragma once
#include "ofMain.h"

#define OFX_SHUFFLE_TEXT_NUMBERS 0x0001
#define OFX_SHUFFLE_TEXT_UPPER_LETTERS 0x0002
#define OFX_SHUFFLE_TEXT_LOWER_LETTERS 0x0004
#define OFX_SHUFFLE_TEXT_SYMBOLS 0x0008

class ofxShuffleText {

public:
    ofxShuffleText()
        : _text("")
        , _originalText("")
        , _speed(2.f)
        , _delay(0)
        , _startTime(0)
        , _bReady(false)
        , _bRunning(false)
        , _bFill(false)
        , _index(0)
        , _shuffleLength(4)
        , _randomChars(NUMBERS + UPPER_LETTERS + LOWER_LETTERS + SYMBOLS) {}
    
    virtual ~ofxShuffleText() {}
    
    void setup(const ofTrueTypeFont &font, string text) {
        _font = font;
        _originalText = text;
    }
    
    void update() {
        if (!_bRunning) {
            return;
        }
        
        if (_delay != 0) {
            if (_startTime == 0) {
                _startTime = ofGetElapsedTimeMillis();
            }
            if (ofGetElapsedTimeMillis() - _startTime >= _delay) {
                _bReady = true;
            }
            if (!_bReady) {
                return;
            }
        } else {
            _bReady = true;
        }
        
        if (_index <= _originalText.length() * _speed) {
            _text = "";
            if (_bFill) {
                _text = _originalText.substr(0, (int) (_index / _speed));
                _text += generateRandomText(_originalText.length() - (int) (_index / _speed));
            } else {
                for (int i = 0; i < (int) (_index / _speed); i++) {
                    _text += _originalText[i];
                }
                _text += generateRandomText(MIN(_shuffleLength, _originalText.length() - _text.length()));
            }
            _index++;
        } else {
            _text = _originalText;
            _bRunning = false;
        }
    }
    
    void draw(float x, float y) {
        if (!_font.isLoaded()) return;
        _font.drawString(_text, x, y);
    }
    
    void start(float speed, float delay, bool bFill, int shuffleLength = 4) {
        _text = "";
        _speed = speed;
        _delay = delay;
        _startTime = 0;
        _index = 0;
        _shuffleLength = shuffleLength;
        _bReady = false;
        _bRunning = true;
        _bFill = bFill;
    }
    
    void stop() {
        if (_bRunning) _bRunning = false;
    }
    
    void setRandomChars(int flag) {
        _randomChars = "";
        if (flag & OFX_SHUFFLE_TEXT_NUMBERS) _randomChars += NUMBERS;
        if (flag & OFX_SHUFFLE_TEXT_UPPER_LETTERS) _randomChars += UPPER_LETTERS;
        if (flag & OFX_SHUFFLE_TEXT_LOWER_LETTERS) _randomChars += LOWER_LETTERS;
        if (flag & OFX_SHUFFLE_TEXT_SYMBOLS) _randomChars += SYMBOLS;
    }
    
    void setFont(ofTrueTypeFont &font) {
        _font = font;
    }
    
    void setSpeed(float speed) {
        _speed = speed;
    }
    
    void setText(string text) {
        _originalText = text;
    }
    
    void setFill(bool bFill) {
        _bFill = bFill;
    }
    
    void setShuffleLength(int shuffleLength) {
        _shuffleLength = shuffleLength;
    }
    
    bool isReady() {
        return _bReady;
    }
    
    bool isRunning() {
        return _bRunning;
    }

private:
    const string NUMBERS = "0123456789";
    const string UPPER_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const string LOWER_LETTERS = "abcdefghijklmnopqrstuvwxyz";
    const string SYMBOLS = "!#@$%^&*_+-\\";
    ofTrueTypeFont _font;
    string _text;
    string _originalText;
    float _speed;
    float _delay;
    int _startTime;
    int _index;
    int _shuffleLength;
    bool _bReady;
    bool _bRunning;
    bool _bFill;
    string _randomChars;
    
    string generateRandomText(int length) {
        string text = "";
        int r = 0;
        for (int i = 0; i < length; i++) {
            r = floor(ofRandom(_randomChars.length()));
            text += _randomChars[r];
        }
        return text;
    }

};
