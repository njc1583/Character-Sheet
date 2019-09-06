#include "stats-widget.h"

const std::string kWidgetName_ = "stats";

StatsWidget::StatsWidget(std::string character_name,
	std::string settings_filename) : Widget(settings_filename) {
	character_name_ = character_name;
	LoadCharacterStats();
	ParseWidgetSizeSettings();
	InitializeComponents();
	FormatComponents();
}

StatsWidget::~StatsWidget() {
	for (ofxDatGuiComponent *component : gui_components_) {
		delete component;
	}

	gui_components_.clear();
}

void StatsWidget::ParseWidgetSizeSettings() {
	xml_reader_.loadFile(settings_filename_);

	posx_ = xml_reader_.getValue(kWidgetName_ + ":posx", 10);
	posy_ = xml_reader_.getValue(kWidgetName_ + ":posy", 10);
	width_ = xml_reader_.getValue(kWidgetName_ + ":widget_w", 0);

	num_stats_ = xml_reader_.getValue(kWidgetName_ + ":num_stats", 6);
	
	std::string has_mod_str = xml_reader_.getValue(kWidgetName_ + ":has_mod", "false");
	std::string has_form_str = xml_reader_.getValue(kWidgetName_ + ":has_formula", "false");
	has_mod_display_ = AlgorithmUtils::SToBool(has_mod_str);
	has_formula_option_ = AlgorithmUtils::SToBool(has_form_str);

	stat_label_ratio_ = xml_reader_.getValue(kWidgetName_ + ":stat_label_ratio", 0.6);

	if (has_mod_display_) {
		mod_label_ratio_ = xml_reader_.getValue(kWidgetName_ + ":mod_label_ratio", 0.6);
	} else {
		mod_label_ratio_ = 0;
	}

	if (has_formula_option_) {
		formula_label_ratio_ = xml_reader_.getValue(kWidgetName_ + ":formula_label_ratio", 0.6);
		name_label_ratio_ = xml_reader_.getValue(kWidgetName_ + ":name_label_ratio", 0.9);
	} else {
		formula_label_ratio_ = 0;
		name_label_ratio_ = 1.0;
	}

	std::string stat_name_whole = xml_reader_.getValue(kWidgetName_ + ":stat_names", "CON STR INT WIS DEX CHA");
	stat_names_ = AlgorithmUtils::Split(stat_name_whole, ' ');

	single_stat_w_ = width_ / num_stats_;
}

void StatsWidget::LoadCharacterStats() {
	xml_reader_.loadFile(settings_filename_);
	character_xml_reader_.loadFile(character_name_ + "_char_info.xml");

	std::string stat_vals_str = character_xml_reader_.getValue("character:stats", 
		"10 10 10 10 10 10");
	stat_vals_ = AlgorithmUtils::Split(stat_vals_str, ' ');

	if (has_mod_display_) {
		std::string mod_vals_str = character_xml_reader_.getValue("character:mods", 
			"0 0 0 0 0 0");
		mod_vals_ = AlgorithmUtils::Split(mod_vals_str, ' ');
	}

	if (has_formula_option_) {
		std::string stat_rolls_str = character_xml_reader_.getValue("character:stat_rolls", 
			"d20 d20 d20 d20 d20 d20");
		stat_rolls_ = AlgorithmUtils::Split(stat_rolls_str, ' ');
	}
}

void StatsWidget::InitializeComponents() {
	name_label_ = new ofxDatGuiLabel("Stats");

	if (has_formula_option_) {
		formula_button_ = new ofxDatGuiButton("Roll!");
		formula_button_->onButtonEvent(this, &StatsWidget::RollStats);
	}

	gui_components_.push_back(name_label_);
	gui_components_.push_back(formula_button_);

	for (int i = 0; i < num_stats_; i++) {
		InitializeSingleStatPanel(i);
	}
}

void StatsWidget::FormatComponents() {
	name_label_->setWidth((int)(name_label_ratio_ * width_));
	name_label_->setPosition(posx_, posy_);

	if (has_formula_option_) {
		formula_button_->setWidth(width_ - name_label_->getWidth());
		formula_button_->setPosition(posx_ + name_label_->getWidth(), posy_);
	}

	for (int idx = 0; idx < num_stats_; idx++) {
		int num_vertical_components = 1; // The "STATS" label is assumed to be there always

		stat_val_inputfields_[idx]->setWidth(single_stat_w_, (int)(stat_label_ratio_ * single_stat_w_));
		stat_val_inputfields_[idx]->setPosition(posx_ + single_stat_w_ * idx,
			posy_ + num_vertical_components * kStandardComponentHeight_);
		stat_val_inputfields_[idx]->onTextInputEvent(this, &StatsWidget::SaveInputEvent);
		stat_val_inputfields_[idx]->setText(stat_vals_[idx]);

		if (has_mod_display_) {
			num_vertical_components++;

			mod_val_inputfields_[idx]->setWidth(single_stat_w_, (int)(mod_label_ratio_ * single_stat_w_));
			mod_val_inputfields_[idx]->setPosition(posx_ + single_stat_w_ * idx,
				posy_ + num_vertical_components * kStandardComponentHeight_);
			mod_val_inputfields_[idx]->setText(mod_vals_[idx]);
		}

		if (has_formula_option_) {
			num_vertical_components++;

			stat_roll_inputfields_[idx]->setWidth(single_stat_w_, (int)(mod_label_ratio_ * single_stat_w_));
			stat_roll_inputfields_[idx]->setPosition(posx_ + single_stat_w_ * idx,
				posy_ + num_vertical_components * kStandardComponentHeight_);

			num_vertical_components++;

			stat_result_labels_[idx]->setWidth(single_stat_w_);
			stat_result_labels_[idx]->setPosition(posx_ + single_stat_w_ * idx,
				posy_ + num_vertical_components * kStandardComponentHeight_);
			stat_result_labels_[idx]->setLabelAlignment(ofxDatGuiAlignment::RIGHT);
		}
	}
}

void StatsWidget::InitializeSingleStatPanel(int idx) {
	ofxDatGuiTextInput *stat_inputfield = new ofxDatGuiTextInput(stat_names_[idx], stat_vals_[idx]);
	
	stat_val_inputfields_.push_back(stat_inputfield);
	gui_components_.push_back(stat_inputfield);

	if (has_mod_display_) {		
		ofxDatGuiTextInput *mod_inputfield = new ofxDatGuiTextInput("Mod", mod_vals_[idx]);
		
		mod_inputfield->onTextInputEvent(this, &StatsWidget::SaveInputEvent);

		mod_val_inputfields_.push_back(mod_inputfield);
		gui_components_.push_back(mod_inputfield);
	}

	if (has_formula_option_) {
		ofxDatGuiTextInput *formula_inputfield = new ofxDatGuiTextInput("Formula", stat_rolls_[idx]);
		ofxDatGuiLabel *formula_result = new ofxDatGuiLabel("");
		
		formula_inputfield->onTextInputEvent(this, &StatsWidget::SaveInputEvent);

		gui_components_.push_back(formula_inputfield);
		gui_components_.push_back(formula_result);

		stat_roll_inputfields_.push_back(formula_inputfield);
		stat_result_labels_.push_back(formula_result);
	}
}

void StatsWidget::SaveInputEvent(ofxDatGuiTextInputEvent e) {
	for (int i = 0; i < num_stats_; i++) {
		stat_vals_[i] = stat_val_inputfields_[i]->getText();

		if (has_mod_display_) {
			mod_vals_[i] = mod_val_inputfields_[i]->getText();
		}

		if (has_formula_option_) {
			stat_rolls_[i] = stat_roll_inputfields_[i]->getText();
		}
	}

	SaveCharacterData();
	ParseWidgetSizeSettings();
}

void StatsWidget::RollStats(ofxDatGuiButtonEvent e) {
	for (int i = 0; i < num_stats_; i++) {
		std::string complete_formula(stat_roll_inputfields_[i]->getText());

		if (has_formula_option_) {
			complete_formula += "+" + mod_val_inputfields_[i]->getText();
		}

		stat_result_labels_[i]->setLabel("");
		stat_result_labels_[i]->setLabel(calculator_.Evaluate(complete_formula));
	}
}

void StatsWidget::SaveCharacterData() {
	character_xml_reader_.loadFile(character_name_ + "_char_info.xml");
	character_xml_reader_.setValue("character:stats",
		AlgorithmUtils::VecToString(stat_vals_));

	if (has_mod_display_) {
		character_xml_reader_.setValue("character:mods",
			AlgorithmUtils::VecToString(mod_vals_));
	}

	if (has_formula_option_) {
		character_xml_reader_.setValue("character:stat_rolls",
			AlgorithmUtils::VecToString(stat_rolls_));
	}

	character_xml_reader_.save(character_name_ + "_char_info.xml");
}

void StatsWidget::ChangeCharacter(std::string character_name) {
	character_name_ = character_name;
	LoadCharacterStats();
	FormatComponents();
}