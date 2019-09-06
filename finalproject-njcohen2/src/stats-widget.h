#ifndef STATS_WIDGE_H
#define STATS_WIDGE_H

#include "widget.h"
#include "dnd-calculator.h"

class StatsWidget : public Widget {
private:
	ofxXmlSettings character_xml_reader_;

	DNDCalculator calculator_;

	std::vector<ofxDatGuiTextInput*> stat_val_inputfields_;
	std::vector<ofxDatGuiTextInput*> mod_val_inputfields_;
	std::vector<ofxDatGuiTextInput*> stat_roll_inputfields_;
	std::vector<ofxDatGuiLabel*> stat_result_labels_;

	std::vector<std::string> stat_names_;
	std::vector<std::string> stat_vals_;
	std::vector<std::string> mod_vals_;
	std::vector<std::string> stat_rolls_;

	std::string character_name_;

	ofxDatGuiLabel *name_label_;
	ofxDatGuiButton *formula_button_;

	// Parsed 
	int num_stats_;
	double name_label_ratio_;
	double stat_label_ratio_;
	double mod_label_ratio_;
	double formula_label_ratio_;
	bool has_mod_display_;
	bool has_formula_option_;
	// Calculated 
	int single_stat_w_; 

	void LoadCharacterStats();
	void InitializeSingleStatPanel(int idx);
	void SaveInputEvent(ofxDatGuiTextInputEvent e);
	void RollStats(ofxDatGuiButtonEvent e);

public:
	StatsWidget(std::string character_name, std::string settings_filename);
	~StatsWidget();

	virtual void ParseWidgetSizeSettings();
	virtual void InitializeComponents();
	virtual void FormatComponents();
	void SaveCharacterData();
	void ChangeCharacter(std::string character_name);
};

#endif