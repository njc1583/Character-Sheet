#include "calculator-widget.h"

const std::string kWidgetName_ = "calculator";

CalculatorWidget::CalculatorWidget(std::string settings_filename) : Widget(settings_filename) {
	ParseWidgetSizeSettings();
	InitializeComponents();
	FormatComponents();
}

CalculatorWidget::~CalculatorWidget() {
	for (ofxDatGuiComponent *component : gui_components_) {
		delete component;
	}

	gui_components_.clear();
}

void CalculatorWidget::ParseWidgetSizeSettings() {
	xml_reader_.loadFile(settings_filename_);

	posx_ = xml_reader_.getValue(kWidgetName_ + ":posx", 10);
	posy_ = xml_reader_.getValue(kWidgetName_ + ":posy", 10);
	width_ = xml_reader_.getValue(kWidgetName_ + ":widget_w", 0);

	button_w_ = xml_reader_.getValue(kWidgetName_ + ":button_w", 0);
	label_w_ = xml_reader_.getValue(kWidgetName_ + ":label_w", 0);
	input_field_w_ = xml_reader_.getValue(kWidgetName_ + ":input_field_w", 0);
	if_label_w_ = xml_reader_.getValue(kWidgetName_ + ":if_label_w", 0);
}

void CalculatorWidget::FormatComponents() {
	calculator_inputfield_->setPosition(posx_, posy_);

	calculator_outputfield_->setPosition(posx_, posy_ + kStandardComponentHeight_);

	calculator_inputfield_->setWidth(input_field_w_, if_label_w_);
	calculator_outputfield_->setWidth(label_w_);

	for (int i = 0; i < calculator_buttons_.size(); i++) {
		calculator_buttons_[i]->setWidth(button_w_);
		calculator_buttons_[i]->setLabelAlignment(ofxDatGuiAlignment::CENTER);
		calculator_buttons_[i]->setPosition(
			posx_ + button_w_ * (i % 4),
			posx_ + 2 * kStandardComponentHeight_ + kStandardComponentHeight_ * (i / 4)
		);
	}
}

void CalculatorWidget::InitializeComponents() {
	SetUpLabels();
	SetUpButtons();
}

void CalculatorWidget::SetUpLabels() {
	calculator_inputfield_ = new ofxDatGuiTextInput("Calculator", "");
	calculator_inputfield_->setLabelAlignment(ofxDatGuiAlignment::CENTER);
	calculator_outputfield_ = new ofxDatGuiLabel("");

	

	gui_components_.push_back(calculator_inputfield_);
	gui_components_.push_back(calculator_outputfield_);

	calculator_inputfield_->onTextInputEvent(this, &CalculatorWidget::onCalculatorTextInputEvent);
}

void CalculatorWidget::SetUpButtons() {
	// std::vector<ofxDatGuiButton*> calculator_buttons_;

	zero_button_ = new ofxDatGuiButton("0");
	one_button_ = new ofxDatGuiButton("1");
	two_button_ = new ofxDatGuiButton("2");
	three_button_ = new ofxDatGuiButton("3");
	four_button_ = new ofxDatGuiButton("4");
	five_button_ = new ofxDatGuiButton("5");
	six_button_ = new ofxDatGuiButton("6");
	seven_button_ = new ofxDatGuiButton("7");
	eight_button_ = new ofxDatGuiButton("8");
	nine_button_ = new ofxDatGuiButton("9");
	d_button_ = new ofxDatGuiButton("D");
	h_button_ = new ofxDatGuiButton("H");
	l_button_ = new ofxDatGuiButton("L");
	plus_button_ = new ofxDatGuiButton("+");
	minus_button_ = new ofxDatGuiButton("-");
	mult_button_ = new ofxDatGuiButton("x");
	divides_button_ = new ofxDatGuiButton("/");
	equals_button_ = new ofxDatGuiButton("=");
	calc_clear_button_ = new ofxDatGuiButton("C");

	// Order is from left-to-right, top-to-bottom
	calculator_buttons_.push_back(d_button_);
	calculator_buttons_.push_back(h_button_);
	calculator_buttons_.push_back(l_button_);
	calculator_buttons_.push_back(divides_button_);
	// Next line of buttons
	calculator_buttons_.push_back(seven_button_);
	calculator_buttons_.push_back(eight_button_);
	calculator_buttons_.push_back(nine_button_);
	calculator_buttons_.push_back(mult_button_);
	// Next line of buttons
	calculator_buttons_.push_back(four_button_);
	calculator_buttons_.push_back(five_button_);
	calculator_buttons_.push_back(six_button_);
	calculator_buttons_.push_back(plus_button_);
	// Next line of buttons
	calculator_buttons_.push_back(one_button_);
	calculator_buttons_.push_back(two_button_);
	calculator_buttons_.push_back(three_button_);
	calculator_buttons_.push_back(minus_button_);
	// Next line of buttons
	calculator_buttons_.push_back(zero_button_);
	calculator_buttons_.push_back(equals_button_);
	calculator_buttons_.push_back(calc_clear_button_);

	zero_button_->onButtonEvent(this, &CalculatorWidget::onCalculatorButtonEvent);

	for (int i = 0; i < calculator_buttons_.size(); i++) {
		calculator_buttons_[i]->onButtonEvent(this, &CalculatorWidget::onCalculatorButtonEvent);
		
		gui_components_.push_back(calculator_buttons_[i]);
	}
}

void CalculatorWidget::onCalculatorTextInputEvent(ofxDatGuiTextInputEvent textinput_e) {
	calculator_outputfield_->setLabel(calculator_.Evaluate(textinput_e.target->getText()));
}

void CalculatorWidget::onCalculatorButtonEvent(ofxDatGuiButtonEvent button_e) {
	if (button_e.target == calc_clear_button_) {
		calculator_inputfield_->setText("");
		calculator_outputfield_->setLabel("");
	} else if (button_e.target == equals_button_) {
		calculator_outputfield_->setLabel(calculator_.Evaluate(
			calculator_inputfield_->getText()));
	} else {
		calculator_inputfield_->setText(
			calculator_inputfield_->getText() + button_e.target->getLabel());
	}
}