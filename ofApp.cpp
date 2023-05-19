#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	float back_color_value, color_value;

	if (ofGetFrameNum() % 240 < 120) {

		back_color_value = ofMap(ofGetFrameNum() % 240, 0, 120, 239, 39);
		color_value = ofMap(ofGetFrameNum() % 240, 0, 120, 39, 239);
	}
	else {

		back_color_value = ofMap(ofGetFrameNum() % 240, 120, 240, 39, 239);
		color_value = ofMap(ofGetFrameNum() % 240, 120, 240, 239, 39);
	}

	ofBackground(ofColor(back_color_value));
	ofColor color(color_value);

	for (int k = 0; k < 35; k++) {

		ofMesh mesh;
		vector<glm::vec3> right, left, frame;

		auto x = ofRandom(50, ofGetWindowWidth() - 50);
		auto base_y = ofRandom(ofGetWindowHeight());
		auto speed = ofRandom(5, 20);
		float head_size = 9;
		glm::vec3 last_location;
		float last_theta;

		for (int i = 0; i < 25; i++) {

			auto location = glm::vec3(x, (int)(base_y + (ofGetFrameNum() + i) * speed) % 1220 - 200, 0);
			auto next = glm::vec3(x, (int)(base_y + (ofGetFrameNum() + i + 1) * speed) % 1220 - 200, 0);

			auto direction = next - location;
			auto theta = atan2(direction.y, direction.x);

			right.push_back(location + glm::vec3(ofMap(i, 0, 25, 0, head_size) * cos(theta + PI * 0.5), ofMap(i, 0, 25, 0, head_size) * sin(theta + PI * 0.5), 0));
			left.push_back(location + glm::vec3(ofMap(i, 0, 25, 0, head_size) * cos(theta - PI * 0.5), ofMap(i, 0, 25, 0, head_size) * sin(theta - PI * 0.5), 0));

			last_location = location;
			last_theta = theta;
		}

		for (int i = 0; i < right.size(); i++) {

			mesh.addVertex(left[i]);
			mesh.addVertex(right[i]);

			mesh.addColor(ofColor(color, ofMap(i, 0, right.size(), 0, 255)));
			mesh.addColor(ofColor(color, ofMap(i, 0, right.size(), 0, 255)));
		}

		for (int i = 0; i < mesh.getNumVertices() - 2; i += 2) {

			mesh.addIndex(i + 0); mesh.addIndex(i + 1); mesh.addIndex(i + 3);
			mesh.addIndex(i + 0); mesh.addIndex(i + 2); mesh.addIndex(i + 3);
		}

		auto tmp_head_size = ofMap(mesh.getNumVertices() - 2, 0, mesh.getNumVertices() - 2, 0, head_size);
		tmp_head_size = head_size;

		mesh.addVertex(last_location);
		mesh.addColor(color);
		int index = mesh.getNumVertices();
		for (auto theta = last_theta - PI * 0.5; theta <= last_theta + PI * 0.5; theta += PI / 10) {

			mesh.addVertex(last_location + glm::vec3(tmp_head_size * cos(theta), tmp_head_size * sin(theta), 0));
			mesh.addColor(color);
			frame.push_back(last_location + glm::vec3(tmp_head_size * cos(theta), tmp_head_size * sin(theta), 0));
		}

		for (int i = index; i < mesh.getNumVertices() - 1; i++) {

			mesh.addIndex(index); mesh.addIndex(i + 0); mesh.addIndex(i + 1);
		}

		mesh.draw();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}