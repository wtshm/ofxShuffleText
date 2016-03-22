//
//  ofxShuffleText.h
//
//  Created by Kenta Watashima on 3/22/16.
//
//

#pragma once
#include "ofMain.h"

class ofxShuffleText {
private:
    const string NUMBERS = "0123456789";
    const string UPPER_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const string LOWER_LETTERS = "abcdefghijklmnopqrstuvwxyz";
    const string SYMBOLS = ",.?/\\(^)![]{}*&^%$#'\"";
    ofTrueTypeFont _font;
    string _text;
    string _originalText;
    float _speed;
    float _delay;
    int _startTime;
    bool _bReady = false, _bRunning = false, _bFill = false;
    int _index;
    int _shuffleLength;
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

public:
    ofxShuffleText() {
    }
    
    ~ofxShuffleText() {
    }
    
    void setup(ofTrueTypeFont &font,
               string text,
               bool bFill = true,
               float speed = 2.f,
               int shuffleLength = 4,
               bool bNumbers = true,
               bool bUpperLetters = true,
               bool bLowerLetters = true,
               bool bSymbols = true) {
        _font = font;
        _originalText = text;
        _bFill = bFill;
        _speed = speed;
        _shuffleLength = shuffleLength;
        _randomChars += bNumbers ? NUMBERS : "";
        _randomChars += bUpperLetters ? UPPER_LETTERS : "";
        _randomChars += bLowerLetters ? LOWER_LETTERS : "";
        _randomChars += bSymbols ? SYMBOLS : "";
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
    
    void start(float delay = 0.f) {
        _text = "";
        _index = 0;
        _startTime = 0;
        _delay = delay;
        _bReady = false;
        _bRunning = true;
    }
    
    void stop() {
        if (_bRunning) _bRunning = false;
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
};
