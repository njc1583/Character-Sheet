#pragma once
#include "widget.h"

class InfoWidget5E : public Widget {
private:	
	std::string character_name_;

	double if_label_ratio_;

	ofxDatGuiLabel *info_panel_top_label_;
	ofxDatGuiTextInput *name_inputfield_;
	ofxDatGuiTextInput *class_inputfield_;
	ofxDatGuiTextInput *race_inputfield_;
	ofxDatGuiTextInput *background_inputfield_;
	ofxDatGuiTextInput *faction_inputfield_;
	ofxDatGuiTextInput *alignment_inputfield_;
	ofxDatGuiTextInput *exp_inputfield_;
	ofxDatGuiTextInput *dci_num_inputfield_;

	std::string name_;
	std::string class_;
	std::string race_;
	std::string background_;
	std::string faction_;
	std::string alignment_;
	std::string exp_;
	std::string dci_;

	const std::string kCharacterDataFileAppend_ = "_char_info.xml";

	void LoadCharacterInfo();
	void SaveTextInputEvent(ofxDatGuiTextInputEvent e);

public:
	InfoWidget5E(std::string character_name, std::string settings_filename);
	~InfoWidget5E();

	virtual void ParseWidgetSizeSettings();
	virtual void InitializeComponents();
	virtual void FormatComponents();
	void SaveCharacterData();
	void ChangeCharacter(std::string character_name);
};