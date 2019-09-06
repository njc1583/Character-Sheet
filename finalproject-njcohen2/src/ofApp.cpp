#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ParseCharacterFiles();

	ofxXmlSettings xml_reader;
	xml_reader.loadFile(character_files_[0].getFileName());
	curr_character_ = xml_reader.getValue("character:name", "rasputin");

	// ---- External Widgets ----
	calculator_widget_ = new CalculatorWidget("calculator_settings.xml");
	external_component_groups_.push_back(calculator_widget_->GetComponents());

	stats_widget_ = new StatsWidget(curr_character_, "standard_stats_settings.xml");
	external_component_groups_.push_back(stats_widget_->GetComponents());

	info_widget_ = new InfoWidget5E(curr_character_, "standard_stats_settings.xml");
	external_component_groups_.push_back(info_widget_->GetComponents());

	external_widgets_.push_back(calculator_widget_);
	external_widgets_.push_back(stats_widget_);
	external_widgets_.push_back(info_widget_);

	// ---- Internal Widgets -----
	ParseXMLData();
	InitializeInternalComponents();
	FormatInternalComponents();
	SetWidgetsTheme(new DDMThemeDragon());
	ofSetBackgroundColor(ofColor(220, 180, 152));
}

//--------------------------------------------------------------
void ofApp::update(){
	for (std::vector<ofxDatGuiComponent*> group : external_component_groups_) {
		for (ofxDatGuiComponent *component : group) {
			component->update();
		}
	}

	for (std::vector<ofxDatGuiComponent*> group : internal_component_groups_) {
		for (ofxDatGuiComponent *component : group) {
			component->update();
		}
	}

	attacks_formulae_scrollview_->update();
	char_select_scrollview_->update();
	theme_scrollview_->update();
	theme_indicator_->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (std::vector<ofxDatGuiComponent*> group : external_component_groups_) {
		for (ofxDatGuiComponent *component : group) {
			component->draw();
		}
	}

	for (std::vector<ofxDatGuiComponent*> group : internal_component_groups_) {
		for (ofxDatGuiComponent *component : group) {
			component->draw();
		}
	}
	
	attacks_formulae_scrollview_->draw();
	char_select_scrollview_->draw();
	theme_scrollview_->draw();
	theme_indicator_->draw();
}

void ofApp::SaveCharacterData() {
	SaveAttackFormulaeData();
}

void ofApp::InitializeInternalComponents() {
	InitializeFormulaeScrollView();
	InitializeCharacterSelection();
	IntializeThemeSelection();
}

void ofApp::FormatInternalComponents() {
	FormatFormulaeScrollView();
	FormatCharacterSelection();
	FormatThemeSelection();
}

void ofApp::ParseXMLData() {
	ParseFormulaeScrollViewData();
	ParseCharacterSelectionData();
	ParseThemeSelectData();
}

void ofApp::ParseCharacterFiles() {
	character_names_.clear();
	ofDirectory data_dir = ofDirectory(".");
	ofxXmlSettings xml_reader;

	for (ofFile file : data_dir.getFiles()) {
		std::string file_name = file.getFileName();

		if (std::regex_match(file_name, kCharFilenameRegex_)) {
			character_files_.push_back(file);

			xml_reader.loadFile(file_name);
			std::string char_name = xml_reader.getValue("character:name", "Sample_Character");
			std::string presentable_name(
				AlgorithmUtils::VecToString(
				AlgorithmUtils::Split(char_name, '_')));
			character_names_.push_back(presentable_name);
		}
	}

	if (character_files_.empty()) {
		ofxXmlSettings xml_writer;
		xml_writer.setValue("character:name", "sample_character");
		xml_writer.saveFile("sample_character_char_info.xml");
		ofFile new_file("sample_character_char_info.xml");
		character_files_.push_back(new_file);
		character_names_.push_back("sample character");
	}
}

void ofApp::SetWidgetsTheme(ofxDatGuiTheme *theme) {
	for (std::vector<ofxDatGuiComponent*> group : internal_component_groups_) {
		for (ofxDatGuiComponent *component : group) {
			component->setTheme(theme);
		}
	}

	for (Widget *widget : external_widgets_) {
		widget->SetWidgetTheme(theme);
	}

	attacks_formulae_scrollview_->setTheme(theme);
	char_select_scrollview_->setTheme(theme);
	theme_scrollview_->setTheme(theme);
	theme_indicator_->setTheme(theme);

	FormatInternalComponents();
}

void ofApp::ParseFormulaeScrollViewData() {
	ofxXmlSettings xml_reader;

	xml_reader.loadFile(kAttackFormFilePath_);
	std::string tag_prefix = "attacks_formulae:";

	attack_form_posx_ = xml_reader.getValue(tag_prefix + "posx", 100);
	attack_form_posy_ = xml_reader.getValue(tag_prefix + "posy", 10);
	attack_form_widget_w_ = xml_reader.getValue(tag_prefix + "widget_w", 102);
	attack_form_scroll_numvisible_ = xml_reader.getValue(tag_prefix + "num_visible", 4);
	attack_form_if_labelratio_ = xml_reader.getValue(tag_prefix + "iflabel_ratio", 0.4);

	xml_reader.loadFile(curr_character_ + kCharacterDataFileAppend_);

	tag_prefix = "character:";
	std::string form_names_str(xml_reader.getValue(tag_prefix + "formulae_names", "A Sword"));
	std::string form_vals_str(xml_reader.getValue(tag_prefix + "formulae_vals", "2d8"));
	formulae_names_ = AlgorithmUtils::Split(form_names_str, kMultiWordSplitDelim_);
	formulae_vals_ = AlgorithmUtils::Split(form_vals_str, kMultiWordSplitDelim_);
}

void ofApp::ParseCharacterSelectionData() {
	ofxXmlSettings xml_reader;

	xml_reader.loadFile("character_selection_settings.xml");
	std::string tag_prefix = "char_select:";

	char_select_posx_ = xml_reader.getValue(tag_prefix + "posx", 10);
	char_select_posy_ = xml_reader.getValue(tag_prefix + "posy", 500);
	char_select_w_ = xml_reader.getValue(tag_prefix + "widget_w", 300);
	char_select_scroll_numvisible_ = xml_reader.getValue(tag_prefix + "num_vis", 3);
}

void ofApp::ParseThemeSelectData() {
	ofxXmlSettings xml_reader;

	std::string tag_prefix("theme_select:");

	xml_reader.loadFile("theme_select_settings.xml");
	theme_select_posx_ = xml_reader.getValue(tag_prefix + "posx", 190);
	theme_select_posy_ = xml_reader.getValue(tag_prefix + "posy", 10);
	theme_select_w_ = xml_reader.getValue(tag_prefix + "width", 100);

	if (theme_choices_.empty()) {
		theme_names_.push_back("Dragon");
		theme_choices_["Dragon"] = std::pair<ofColor, ofxDatGuiTheme*>
			(ofColor(220, 180, 152), new DDMThemeDragon());
		theme_names_.push_back("Aquatic");
		theme_choices_["Aquatic"] = std::pair<ofColor, ofxDatGuiTheme*>
			(ofColor(139, 189, 197), new DDMThemeAquatic());
		theme_names_.push_back("Royalty");
		theme_choices_["Royalty"] = std::pair<ofColor, ofxDatGuiTheme*>
			(ofColor(227, 150, 214), new DDMThemeRoyalty());
		theme_names_.push_back("Forest");
		theme_choices_["Forest"] = std::pair<ofColor, ofxDatGuiTheme*>
			(ofColor(161, 198, 163), new DDMThemeForest());
		theme_names_.push_back("Illini");
		theme_choices_["Illini"] = std::pair<ofColor, ofxDatGuiTheme*>
			(ofColor(216, 216, 216), new DDMThemeIllini());
		theme_names_.push_back("Nature");
		theme_choices_["Nature"] = std::pair<ofColor, ofxDatGuiTheme*>
			(ofColor(226, 223, 188), new DDMThemeNature());
	}
}

void ofApp::IntializeThemeSelection() {
	theme_indicator_ = new ofxDatGuiLabel("Themes");
	theme_scrollview_ = new ofxDatGuiScrollView("Theme choices", 6);
	theme_scrollview_->onScrollViewEvent(this, &ofApp::SelectTheme);
}

void ofApp::FormatThemeSelection() {
	theme_indicator_->setPosition(theme_select_posx_, theme_select_posy_);
	theme_indicator_->setWidth(theme_select_w_);

	theme_scrollview_->setPosition(theme_select_posx_, theme_indicator_->getY() + kStandardComponentHeight_);
	theme_scrollview_->setWidth(theme_select_w_);

	if (theme_scrollview_->getNumItems() == 0) {
		for (std::string theme_name : theme_names_) {
			theme_scrollview_->add(theme_name);
		}
	}
}

void ofApp::SelectTheme(ofxDatGuiScrollViewEvent e) {
	ofBackground(theme_choices_[e.target->getLabel()].first);
	SetWidgetsTheme(theme_choices_[e.target->getLabel()].second);
}

void ofApp::InitializeFormulaeScrollView() {
	attacks_formulae_scrollview_ = new ofxDatGuiScrollView("Attacks", attack_form_scroll_numvisible_);
	formula_name_input_ = new ofxDatGuiTextInput("Name");
	formula_val_input_ = new ofxDatGuiTextInput("Formula");
	formula_roll_button_ = new ofxDatGuiButton("ROLL");
	formula_save_button_ = new ofxDatGuiButton("SAVE");
	formula_delete_button_ = new ofxDatGuiButton("DELETE");
	formula_result_label_ = new ofxDatGuiLabel("Result");

	attacks_formulae_scrollview_->onScrollViewEvent(this, &ofApp::SelectFormula);
	formula_roll_button_->onButtonEvent(this, &ofApp::ModifyFormulae);
	formula_save_button_->onButtonEvent(this, &ofApp::ModifyFormulae);
	formula_delete_button_->onButtonEvent(this, &ofApp::ModifyFormulae);

	attackform_gui_components_.push_back(formula_name_input_);
	attackform_gui_components_.push_back(formula_val_input_);
	attackform_gui_components_.push_back(formula_roll_button_);
	attackform_gui_components_.push_back(formula_save_button_);
	attackform_gui_components_.push_back(formula_delete_button_);
	attackform_gui_components_.push_back(formula_result_label_);
	internal_component_groups_.push_back(attackform_gui_components_);
}

void ofApp::InitializeCharacterSelection() {
	char_select_scrollview_ = new ofxDatGuiScrollView("character selection", 
		char_select_scroll_numvisible_);
	character_name_input_ = new ofxDatGuiTextInput("Character:", "");
	character_new_button_ = new ofxDatGuiButton("New Character");
	character_delete_button_ = new ofxDatGuiButton("Delete");

	character_new_button_->onButtonEvent(this, &ofApp::ModifyCharacterData);
	character_delete_button_->onButtonEvent(this, &ofApp::ModifyCharacterData);
	char_select_scrollview_->onScrollViewEvent(this, &ofApp::SelectCharacter);

	character_select_gui_components_.push_back(character_name_input_);
	character_select_gui_components_.push_back(character_new_button_);
	character_select_gui_components_.push_back(character_delete_button_);
	internal_component_groups_.push_back(character_select_gui_components_);
}

void ofApp::FormatFormulaeScrollView() {
	attacks_formulae_scrollview_->clear();

	attacks_formulae_scrollview_->setWidth(attack_form_widget_w_);
	formula_name_input_->setWidth(attack_form_widget_w_, 
		(int)(attack_form_if_labelratio_ * attack_form_widget_w_));
	formula_val_input_->setWidth(attack_form_widget_w_,
		(int)(attack_form_if_labelratio_ * attack_form_widget_w_));
	formula_roll_button_->setWidth(attack_form_widget_w_ / 6);
	formula_save_button_->setWidth(attack_form_widget_w_ / 6);
	formula_delete_button_->setWidth(attack_form_widget_w_ / 6);
	formula_result_label_->setWidth(attack_form_widget_w_ / 2);

	attacks_formulae_scrollview_->setPosition(attack_form_posx_, attack_form_posy_);
	formula_name_input_->setPosition(attack_form_posx_, 
		attack_form_posy_ + attacks_formulae_scrollview_->getHeight());
	formula_val_input_->setPosition(attack_form_posx_,
		formula_name_input_->getY() + kStandardComponentHeight_);
	formula_roll_button_->setPosition(attack_form_posx_,
		formula_val_input_->getY() + kStandardComponentHeight_);
	formula_save_button_->setPosition(formula_roll_button_->getX() + formula_roll_button_->getWidth(),
		formula_roll_button_->getY());
	formula_delete_button_->setPosition(formula_save_button_->getX() + formula_save_button_->getWidth(),
		formula_roll_button_->getY());
	formula_result_label_->setPosition(formula_delete_button_->getX() + formula_delete_button_->getWidth(),
		formula_roll_button_->getY());

	for (int i = 0; i < formulae_names_.size(); i++) {
		std::string formula_display(formulae_names_[i] + ": " + formulae_vals_[i]);
		attacks_formulae_scrollview_->add(formula_display);
	}
}

void ofApp::FormatCharacterSelection() {
	char_select_scrollview_->clear();
	char_select_scrollview_->setPosition(char_select_posx_, char_select_posy_);
	char_select_scrollview_->setWidth(char_select_w_);

	character_name_input_->setPosition(char_select_posx_, char_select_posy_ + char_select_scrollview_->getHeight());
	character_name_input_->setWidth(char_select_w_, (int)(char_select_iflabel_ratio_ * char_select_w_));

	character_new_button_->setPosition(char_select_posx_, character_name_input_->getY() + kStandardComponentHeight_);
	character_new_button_->setWidth(char_select_w_ / 2);

	character_delete_button_->setPosition(char_select_posx_ + character_new_button_->getWidth(), 
		character_new_button_->getY());
	character_delete_button_->setWidth(char_select_w_ / 2);

	for (std::string name : character_names_) {
		char_select_scrollview_->add(name);
	}
}

void ofApp::SelectFormula(ofxDatGuiScrollViewEvent e) {
	int idx = e.target->getIndex();
	formula_name_input_->setText(formulae_names_[idx]);
	formula_val_input_->setText(formulae_vals_[idx]);
}

void ofApp::ModifyFormulae(ofxDatGuiButtonEvent e) {
	if (formula_name_input_->getText().empty()) {
		return;
	}

	if (e.target == formula_roll_button_) {
		formula_result_label_->setLabel(
			calculator_.Evaluate(formula_val_input_->getText()));
	} else if (e.target == formula_save_button_) {
		for (int idx = 0; idx < attacks_formulae_scrollview_->getNumItems(); idx++) {
			std::string input_name = formula_name_input_->getText();
			std::string input_val = formula_val_input_->getText();
			std::string saved_name = formulae_names_[idx];

			std::transform(input_name.begin(), input_name.end(), input_name.begin(), toupper);
			std::transform(saved_name.begin(), saved_name.end(), saved_name.begin(), toupper);

			if (input_name == saved_name) {
				formulae_vals_[idx] = input_val;
				SaveAttackFormulaeData();
				FormatFormulaeScrollView();
				return;
			}
		}

		formulae_names_.push_back(formula_name_input_->getText());
		formulae_vals_.push_back(formula_val_input_->getText());
		SaveAttackFormulaeData();
		FormatFormulaeScrollView();
	} else { // Delete button
		for (int idx = 0; idx < attacks_formulae_scrollview_->getNumItems(); idx++) {
			std::string input_name =formula_name_input_->getText();
			std::string input_val = formula_val_input_->getText();
			std::string saved_name = formulae_names_[idx];

			std::transform(input_name.begin(), input_name.end(), input_name.begin(), toupper);
			std::transform(saved_name.begin(), saved_name.end(), saved_name.begin(), toupper);

			if (input_name == saved_name) {
				formulae_names_.erase(formulae_names_.begin() + idx);
				formulae_vals_.erase(formulae_vals_.begin() + idx);
				FormatFormulaeScrollView();
				break;
			}
		}

		formula_name_input_->setText("");
		formula_val_input_->setText("");
		SaveAttackFormulaeData();
	}
}

void ofApp::ModifyCharacterData(ofxDatGuiButtonEvent e) {
	std::regex invalid_name_regex("\s+");

	std::string char_name(character_name_input_->getText());
	std::transform(char_name.begin(), char_name.end(), char_name.begin(), tolower);

	if (char_name.empty() || std::regex_match(char_name, invalid_name_regex)) {
		return;
	}

	char_name = AlgorithmUtils::VecToString(AlgorithmUtils::Split(char_name, ' '), "_");
	ofFile selected_char_file(char_name + kCharacterDataFileAppend_);

	if (e.target == character_new_button_) {
		if (ofFile::doesFileExist(selected_char_file)) {
			return;
		} else {
			std::cout << selected_char_file.getFileName() << std::endl;
			std::cout << char_name << std::endl;

			ofxXmlSettings xml_writer;
			xml_writer.setValue("character:name", char_name);
			xml_writer.saveFile(selected_char_file.getFileName());

			curr_character_ = char_name;

			info_widget_->ChangeCharacter(curr_character_);
			stats_widget_->ChangeCharacter(curr_character_);
			ParseCharacterFiles();
			ParseCharacterSelectionData();
			FormatCharacterSelection();
		}
	} else {
		if (!ofFile::doesFileExist(selected_char_file)) {
			return;
		} else {
			std::cout << selected_char_file.getFileName() << std::endl;
			std::cout << char_name << std::endl;

			selected_char_file.remove();
			ParseCharacterFiles();
		
			ofxXmlSettings xml_reader;
			xml_reader.loadFile(character_files_[0].getFileName());
			curr_character_ = xml_reader.getValue("character:name", "rasputin");

			info_widget_->ChangeCharacter(curr_character_);
			stats_widget_->ChangeCharacter(curr_character_);
			ParseCharacterSelectionData();
			FormatCharacterSelection();
		}
	}
}

void ofApp::SelectCharacter(ofxDatGuiScrollViewEvent e) {
	std::string char_name = e.target->getLabel();
	char_name = AlgorithmUtils::VecToString(AlgorithmUtils::Split(char_name, ' '), "_");
	curr_character_ = char_name;

	info_widget_->ChangeCharacter(curr_character_);
	stats_widget_->ChangeCharacter(curr_character_);
	ParseFormulaeScrollViewData();
	FormatFormulaeScrollView();
}

void ofApp::SaveAttackFormulaeData() {
	ofxXmlSettings xml_writer_;
	xml_writer_.loadFile(curr_character_ + kCharacterDataFileAppend_);

	std::string all_formulae_names = AlgorithmUtils::VecToString(formulae_names_, 
		std::string(1, kMultiWordSplitDelim_));
	std::string all_formulae_vals = AlgorithmUtils::VecToString(formulae_vals_,
		std::string(1, kMultiWordSplitDelim_));

	xml_writer_.setValue("character:formulae_names", all_formulae_names);
	xml_writer_.setValue("character:formulae_vals", all_formulae_vals);
	xml_writer_.saveFile();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}