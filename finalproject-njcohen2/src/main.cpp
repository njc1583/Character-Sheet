#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	settings.resizable = false; // For now, all window resizing is verboten
	settings.setSize(620, 505);
	ofCreateWindow(settings); 

	ofRunApp(new ofApp());
}