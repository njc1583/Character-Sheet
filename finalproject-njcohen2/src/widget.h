#ifndef WIDGE_SUPCLASS_H
#define WIDGE_SUPCLASS_H

#include "ofxDatGui.h"
#include "ofxXmlSettings.h"
#include "algorithm-utils.h"
#include "dungeon-dice-master-themes.h"
#include <string>
#include <vector>

class Widget {
protected:
	ofxXmlSettings xml_reader_;
	std::vector<ofxDatGuiComponent*> gui_components_;

	int posx_;
	int posy_;
	int width_;
	const int kStandardComponentHeight_ = 26;
	std::string settings_filename_;

	virtual void ParseWidgetSizeSettings() = 0;
	virtual void InitializeComponents() = 0;
	virtual void FormatComponents() = 0;

public:
	Widget(std::string settings_filename);
	virtual ~Widget();

	std::vector<ofxDatGuiComponent*> GetComponents();
	std::string GetSettingsFile();
	int GetPosX();
	int GetPosY();
	int GetWidth();
	void SetWidgetTheme(const ofxDatGuiTheme* theme);
};

#endif