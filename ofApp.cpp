#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->size = 10;
	for (auto x = size * 0.5; x < ofGetWidth() + size * 0.5; x += size) {

		for (auto y = size * 0.5; y < ofGetHeight() + size * 0.5; y += size) {

			this->location_list.push_back(glm::vec2(x, y));
			this->noise_seed_list.push_back(ofRandom(1000));
			this->noise_step_list.push_back(ofRandom(1000));
			this->param_list.push_back(0);
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::update() {

	glm::vec2 noise_location = glm::vec2(ofMap(ofNoise(11, ofGetFrameNum() * 0.005), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(3, ofGetFrameNum() * 0.005), 0, 1, 0, ofGetHeight()));

	int index = 0;
	for (auto& location : location_list) {

		if (glm::distance(location, noise_location) < 80) {

			this->param_list[index] += this->param_list[index] < 100 ? 5 : 0;
		}
		else {

			this->param_list[index] -= this->param_list[index] > 0 ? 1 : 0;
		}

		this->noise_step_list[index] += this->param_list[index] > 0 ? ofMap(this->param_list[index], 0, 100, 0.01, 0.05) : 0;

		index++;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	ofColor color;
	int index = 0;
	for (auto& location : location_list) {

		color.setHsb(ofMap(ofNoise(this->noise_seed_list[index], this->noise_step_list[index]), 0, 1, 0, 255), 180, 255);

		ofSetColor(color, ofMap(this->param_list[index], 0, 100, 0, 255));
		ofDrawRectangle(location, this->size, this->size);

		index++;
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}