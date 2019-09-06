#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxDatGui.h"
#include "ofxXmlSettings.h"
#include "dnd-calculator.h"
#include <string>
#include <regex>
#include <map>
#include "widget.h"
#include "calculator-widget.h"
#include "stats-widget.h"
#include "info-widget-5e.h"
#include "dungeon-dice-master-themes.h"

class ofApp : public ofBaseApp {

private:
	CalculatorWidget *calculator_widget_;
	StatsWidget *stats_widget_;
	InfoWidget5E *info_widget_;
	// AttacksFormulaeWidget *formulae_widget_;

	DNDCalculator calculator_;

	// Scrollview had to be handled in ofApp class due to bugs 
	// regarding placement inside of other classes
	// ----- Weapon fomulae widget -----
	// CANNOT BE IN ITS OWN VECTOR AND/OR CLASS
	ofxDatGuiScrollView *attacks_formulae_scrollview_;
	ofxDatGuiTextInput *formula_name_input_;
	ofxDatGuiTextInput *formula_val_input_;
	ofxDatGuiButton *formula_roll_button_;
	ofxDatGuiButton *formula_save_button_;
	ofxDatGuiButton *formula_delete_button_;
	ofxDatGuiLabel *formula_result_label_;
	std::vector<ofxDatGuiComponent*> attackform_gui_components_;
	int attack_form_posx_;
	int attack_form_posy_;
	int attack_form_widget_w_;
	int attack_form_scroll_numvisible_;
	double attack_form_if_labelratio_;
	std::vector<std::string> formulae_names_;
	std::vector<std::string> formulae_vals_;
	void ParseFormulaeScrollViewData();
	void InitializeFormulaeScrollView();
	void FormatFormulaeScrollView();
	void SaveAttackFormulaeData();
	void ModifyFormulae(ofxDatGuiButtonEvent e);
	void SelectFormula(ofxDatGuiScrollViewEvent e);
	// ---------------------------------
	// ----- Character selection widget -----
	ofxDatGuiScrollView *char_select_scrollview_;
	ofxDatGuiTextInput *character_name_input_;
	ofxDatGuiButton *character_new_button_;
	ofxDatGuiButton *character_delete_button_;
	std::vector<ofxDatGuiComponent*> character_select_gui_components_;
	int char_select_posx_;
	int char_select_posy_;
	int char_select_w_;
	int char_select_scroll_numvisible_;
	double char_select_iflabel_ratio_ = 0.3;
	std::vector<std::string> character_names_;
	void ParseCharacterSelectionData();
	void InitializeCharacterSelection();
	void FormatCharacterSelection();
	void SelectCharacter(ofxDatGuiScrollViewEvent e);
	void ModifyCharacterData(ofxDatGuiButtonEvent e);
	// --------------------------------------

	std::vector<Widget*> external_widgets_;
	std::vector<std::vector<ofxDatGuiComponent*>> external_component_groups_;
	std::vector<std::vector<ofxDatGuiComponent*>> internal_component_groups_;
	std::vector<ofFile> character_files_;

	const int kStandardComponentHeight_ = 26;
	const std::string kMetadataFilepath_ = "metadata.xml";
	const std::string kAttackFormFilePath_ = "attacks_form_settings.xml";
	const std::string kCharacterDataFileAppend_ = "_char_info.xml";
	const std::regex kCharFilenameRegex_ = std::regex(".+char_info.xml", std::regex::icase);
	const char kMultiWordSplitDelim_ = '#';

	std::string curr_character_;

	// ---------------
	std::map<std::string, std::pair<ofColor, ofxDatGuiTheme*>> theme_choices_;
	std::vector<std::string> theme_names_;
	int theme_select_posx_;
	int theme_select_posy_;
	int theme_select_w_;
	ofxDatGuiLabel *theme_indicator_;
	ofxDatGuiScrollView *theme_scrollview_;
	void ParseThemeSelectData();
	void IntializeThemeSelection();
	void FormatThemeSelection();
	void SelectTheme(ofxDatGuiScrollViewEvent e);
	// ---------------

	void ParseXMLData();
	void ParseCharacterFiles();
	void InitializeInternalComponents();
	void FormatInternalComponents();
	void SaveCharacterData();
	void SetWidgetsTheme(ofxDatGuiTheme *theme);

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};