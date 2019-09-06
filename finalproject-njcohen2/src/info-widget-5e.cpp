#include "info-widget-5e.h"

InfoWidget5E::InfoWidget5E(std::string character_name,
	std::string settings_filename) : Widget(settings_filename) {
	character_name_ = character_name;
	ParseWidgetSizeSettings();
	LoadCharacterInfo();
	InitializeComponents();
	FormatComponents();
}

InfoWidget5E::~InfoWidget5E() {
	for (ofxDatGuiComponent *component : gui_components_) {
		delete component;
	}

	gui_components_.clear();
}

void InfoWidget5E::ParseWidgetSizeSettings() {
	std::string value_prefix = "info:";

	xml_reader_.loadFile("standard_info_settings.xml");
	posx_ = xml_reader_.getValue(value_prefix + "posx", 10);
	posy_ = xml_reader_.getValue(value_prefix + "posy", 400);
	width_ = xml_reader_.getValue(value_prefix + "widget_w", 600);
	if_label_ratio_ = xml_reader_.getValue(value_prefix + "stat_label_ratio", 0.4);
}

void InfoWidget5E::InitializeComponents() {
	info_panel_top_label_ = new ofxDatGuiLabel("Info");
	name_inputfield_ = new ofxDatGuiTextInput("Name", "");
	class_inputfield_ = new ofxDatGuiTextInput("Class/Level", "");
	race_inputfield_ = new ofxDatGuiTextInput("Race", "");
	background_inputfield_ = new ofxDatGuiTextInput("Background", "");
	faction_inputfield_ = new ofxDatGuiTextInput("Faction", "");
	alignment_inputfield_ = new ofxDatGuiTextInput("Alignment", "");
	exp_inputfield_ = new ofxDatGuiTextInput("EXP", "");
	dci_num_inputfield_ = new ofxDatGuiTextInput("DCI #", "");

	name_inputfield_->onTextInputEvent(this, &InfoWidget5E::SaveTextInputEvent);
	class_inputfield_->onTextInputEvent(this, &InfoWidget5E::SaveTextInputEvent);
	race_inputfield_->onTextInputEvent(this, &InfoWidget5E::SaveTextInputEvent);
	background_inputfield_->onTextInputEvent(this, &InfoWidget5E::SaveTextInputEvent);
	faction_inputfield_->onTextInputEvent(this, &InfoWidget5E::SaveTextInputEvent);
	alignment_inputfield_->onTextInputEvent(this, &InfoWidget5E::SaveTextInputEvent);
	exp_inputfield_->onTextInputEvent(this, &InfoWidget5E::SaveTextInputEvent);
	dci_num_inputfield_->onTextInputEvent(this, &InfoWidget5E::SaveTextInputEvent);

	gui_components_.push_back(info_panel_top_label_);
	gui_components_.push_back(name_inputfield_);
	gui_components_.push_back(class_inputfield_);
	gui_components_.push_back(race_inputfield_);
	gui_components_.push_back(background_inputfield_);
	gui_components_.push_back(faction_inputfield_);
	gui_components_.push_back(alignment_inputfield_);
	gui_components_.push_back(exp_inputfield_);
	gui_components_.push_back(dci_num_inputfield_);
}

void InfoWidget5E::LoadCharacterInfo() {
	std::string value_prefix = "character:";

	xml_reader_.loadFile(character_name_ + kCharacterDataFileAppend_);
	name_ = xml_reader_.getValue(value_prefix + "name", "INSERT NAME");
	class_ = xml_reader_.getValue(value_prefix + "class_level", "Level 1 Rogue");
	race_ = xml_reader_.getValue(value_prefix + "race", "Human");
	background_ = xml_reader_.getValue(value_prefix + "background", "Orphan");
	faction_ = xml_reader_.getValue(value_prefix + "faction", "The Cool One");
	alignment_ = xml_reader_.getValue(value_prefix + "alignment", "True Neutral");
	exp_ = xml_reader_.getValue(value_prefix + "exp", "0/25");
	dci_ = xml_reader_.getValue(value_prefix + "dci_num", "N/A");
}

void InfoWidget5E::FormatComponents() {
	info_panel_top_label_->setPosition(posx_, posy_);
	info_panel_top_label_->setWidth(width_);
	
	name_inputfield_->setPosition(posx_, posy_ + kStandardComponentHeight_);
	name_inputfield_->setWidth(width_, (int)(width_ * if_label_ratio_));

	class_inputfield_->setPosition(posx_, name_inputfield_->getY() + kStandardComponentHeight_);
	class_inputfield_->setWidth(width_, (int)(width_ * if_label_ratio_));

	// -------
	race_inputfield_->setPosition(posx_, 
		class_inputfield_->getY() + kStandardComponentHeight_);
	race_inputfield_->setWidth(width_ / 2, (int)(width_ / 2 * if_label_ratio_));

	background_inputfield_->setPosition(posx_ + race_inputfield_->getWidth(), 
		class_inputfield_->getY() + kStandardComponentHeight_);
	background_inputfield_->setWidth(width_ / 2, (int)(width_ / 2* if_label_ratio_));
	// -------
	faction_inputfield_->setPosition(posx_,
		race_inputfield_->getY() + kStandardComponentHeight_);
	faction_inputfield_->setWidth(width_ / 2, (int)(width_ / 2 * if_label_ratio_));

	alignment_inputfield_->setPosition(faction_inputfield_->getX() + faction_inputfield_->getWidth(),
		background_inputfield_->getY() + kStandardComponentHeight_);
	alignment_inputfield_->setWidth(width_ / 2, (int)(width_ / 2 * if_label_ratio_));
	// ------ 
	exp_inputfield_->setPosition(posx_,
		faction_inputfield_->getY() + kStandardComponentHeight_);
	exp_inputfield_->setWidth(width_ / 2, (int)(width_ / 2 * if_label_ratio_));

	dci_num_inputfield_->setPosition(exp_inputfield_->getX() + exp_inputfield_->getWidth(),
		alignment_inputfield_->getY() + kStandardComponentHeight_);
	dci_num_inputfield_->setWidth(width_ / 2, (int)(width_ / 2 * if_label_ratio_));

	std::string display_name(AlgorithmUtils::VecToString(AlgorithmUtils::Split(name_, '_')));

	name_inputfield_->setText(display_name);
	class_inputfield_->setText(class_);
	race_inputfield_->setText(race_);
	background_inputfield_->setText(background_);
	faction_inputfield_->setText(faction_);
	alignment_inputfield_->setText(alignment_);
	exp_inputfield_->setText(exp_);
	dci_num_inputfield_->setText(dci_);

	info_panel_top_label_->setLabelAlignment(ofxDatGuiAlignment::CENTER);
}

void InfoWidget5E::SaveTextInputEvent(ofxDatGuiTextInputEvent e) {
	name_ = AlgorithmUtils::VecToString(AlgorithmUtils::Split(name_inputfield_->getText(), ' '), "_");
	class_ = class_inputfield_->getText();
	race_ = race_inputfield_->getText();
	background_ = background_inputfield_->getText();
	faction_ = faction_inputfield_->getText();
	alignment_ = alignment_inputfield_->getText();
	exp_ = exp_inputfield_->getText();
	dci_ = dci_num_inputfield_->getText();

	SaveCharacterData();
}

void InfoWidget5E::SaveCharacterData() {
	std::string value_prefix = "character:";

	xml_reader_.loadFile(character_name_ + kCharacterDataFileAppend_); name_ = xml_reader_.getValue(value_prefix + "name", "INSERT NAME");
	xml_reader_.setValue(value_prefix + "class_level", class_);
	xml_reader_.setValue(value_prefix + "race", race_);
	xml_reader_.setValue(value_prefix + "background", background_);
	xml_reader_.setValue(value_prefix + "faction", faction_);
	xml_reader_.setValue(value_prefix + "alignment", alignment_);
	xml_reader_.setValue(value_prefix + "exp", exp_);
	xml_reader_.setValue(value_prefix + "dci_num", dci_);

	xml_reader_.saveFile();
}

void InfoWidget5E::ChangeCharacter(std::string character_name) {
	character_name_ = character_name;
	LoadCharacterInfo();
	FormatComponents();
}