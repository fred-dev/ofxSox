//
//  ofxSox.cpp
//  AudioWeatherSoundEditor
//
//  Created by Fred Rodrigues on 10/01/2023.
//

#include <ofxSox.h>

void ofxSox::setup(){
    ofFile sox;
    sox.open("sox");
    soxPath = add_single_quotes(sox.getAbsolutePath());
    ofLogVerbose("ofxSox::setup") << "SOX path is: " + soxPath << endl;
}

ofJson ofxSox::getStatResults(string inputFile){
    ofLogVerbose("ofxSox::getStatResults") << "For: " + add_single_quotes(inputFile) << endl;

    return stat_output_to_json(processCommand(add_single_quotes(inputFile) + " -n stat"));
}

ofJson ofxSox::getStatsResults(string inputFile){
    ofLogVerbose("ofxSox::getStatsResults") << "For: " + add_single_quotes(inputFile) << endl;

    return stats_output_to_json(processCommand(add_single_quotes(inputFile) + " -n stats"));
}

ofJson ofxSox::getAllAudioStats(string inputFile){
    ofJson statJson;
    
    statJson["stat"] = getStatResults(inputFile);
    statJson["stats"] = getStatsResults(inputFile);
    
    ofLogVerbose("ofxSox::getAllAudioStats")   <<"Complete stat output is: " + ofToString(statJson) << endl;
    return statJson;
}

void ofxSox::normalise(string inputFile, float normaliseMax, string outputFile){
    ofLogVerbose("ofxSox::normalise") << "For: " + add_single_quotes(inputFile) << endl;

    processCommand(add_single_quotes(inputFile)  + " " + add_single_quotes(outputFile)  + " norm " + ofToString(normaliseMax));
}

void ofxSox::convertToWav(string inputFile, int bitRate, int sampleRate, string outputFile){
    ofLogVerbose("ofxSox::convertToWav") << "Bit rate: " + ofToString(bitRate)+ " Sample rate: " + ofToString(sampleRate) << endl;

    processCommand(add_single_quotes(inputFile) + " −b "+ ofToString(bitRate) + " rate " + ofToString(sampleRate) +"k");
}

void ofxSox::convertToMP3(string inputFile, int bitrate, int sampleRate, string outputFile){
    ofLogVerbose("ofxSox::convertToMP3") << "Bit rate: " + ofToString(bitrate) + " Sample rate: " + ofToString(sampleRate) << endl;
    
    processCommand(add_single_quotes(inputFile) + " −b "+ ofToString(bitrate) + " rate " + ofToString(sampleRate) +"k");

}

void ofxSox::lowPass(string inputFile, float cuttoff, string outputFile){
    ofLogVerbose("ofxSox::lowPass") << "Cuttoff: " + ofToString(cuttoff) << endl;

    processCommand(add_single_quotes(inputFile)  + " " + add_single_quotes(outputFile)  + " sinc " + ofToString(-cuttoff)+"k");
}

void ofxSox::highPass(string inputFile, float cuttoff, string outputFile){
    ofLogVerbose("ofxSox::highPass") << "Cuttoff: " + ofToString(cuttoff) << endl;

    processCommand(add_single_quotes(inputFile)  + " " + add_single_quotes(outputFile)  + " sinc " + ofToString(cuttoff)+"k");
}
void ofxSox::trim(string inputFile, string outputFile, float inPoint, float outPoint){
    processCommand(inputFile + " " + outputFile + " trim " + ofToString(inPoint) + " " + ofToString(outPoint));
}

void ofxSox::customCommand(string command){
    processCommand(command);
}

string ofxSox::processCommand(string command){
    string output;
    output = ofSystem(soxPath + " " + command + " 2>&1|cat");
    ofLogVerbose("ofxSox::processCommand") << "Output: " + output << endl;
    return output;
}

ofJson ofxSox::stat_output_to_json(const std::string& output){
    // Regular expression to match a key-value pair in the stat output
    std::regex kv_regex("(.+):\\s*(.+)");
    
    // Create the ofJson object
    ofJson json;
    
    // Split the text into lines
    std::stringstream ss(output);
    std::string line;
    while (std::getline(ss, line)) {
        // Try to match a key-value pair in the current line
        std::smatch kv_match;
        if (std::regex_match(line, kv_match, kv_regex)) {
            std::regex space_re(R"(\s+)");
            std::string key = kv_match[1].str();
            std::string value_str = kv_match[2].str();
            // Using the regular expression to remove extra whitespaces.
            key = std::regex_replace(key, space_re, "_");
            float value = ofToFloat(value_str);
            json[key] = ofJson::parse(value_str);
        }
    }
    
    return json;
    
}

ofJson ofxSox::stats_output_to_json(const std::string& output){
    // Regular expression to match a key-value pair in the stat output
    std::regex kv_regex("(.+)\\s+.*");
    
    // Create the ofJson object
    ofJson json;
    
    // Split the text into lines
    std::stringstream ss(output);
    std::string line;
    while (std::getline(ss, line)) {
        // Try to match a key-value pair in the current line
        std::smatch kv_match;
        if (std::regex_match(line, kv_match, kv_regex)) {
            std::regex space_re(R"(\s+)");
            std::string key = kv_match[1].str();
            std::string value_str = kv_match[2].str();
            // Using the regular expression to remove extra whitespaces.
            key = std::regex_replace(key, space_re, "_");
            // Convert the value to a float
            float value = ofToFloat(value_str);
            // Add the key-value pair to the ofJson object
            json[key.substr(0, key.size() - 1)] = value;
        }
    }
    
    return json;
    
}

string ofxSox::add_single_quotes(string input) {
    
    return "'" + input + "'";;
}
