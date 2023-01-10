//
//  ofxSox.h
//  AudioWeatherSoundEditor
//
//  Created by Fred Rodrigues on 10/01/2023.
//

#ifndef ofxSox_h
#define ofxSox_h

#pragma once

#include "ofMain.h"
#include <regex>


class ofxSox {
public:
    string soxPath;
    
    void setup();
    ofJson getStatResults(string inputFile);
    ofJson getStatsResults(string inputFile);
    void normalise(string inputFile, float normaliseMax, string outputFile);
    void convertToWav(string inputFile, int bitRate, int sampleRate, string outputFile);
    void convertToMP3(string inputFile, int bitrate, int sampleRate, string outputFile);
    void lowPass(string inputFile, float cuttoff, string outputFile);
    void highPass(string inputFile, float cuttoff, string outputFile);
    
    void customCommand(string command);
    string processCommand(string command);
    
    ofJson stat_output_to_json(const std::string& output);
    ofJson stats_output_to_json(const std::string& output);
    string add_single_quotes(string input);

};
#endif /* ofxSox_h */
