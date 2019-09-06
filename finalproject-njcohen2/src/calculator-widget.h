#ifndef CALC_WIDGE_H
#define CALC_WIDGE_H

#include "widget.h"
#include "dnd-calculator.h"

class CalculatorWidget : public Widget {
private:
	DNDCalculator calculator_;

	ofxDatGuiTextInput *calculator_inputfield_;
	ofxDatGuiLabel *calculator_outputfield_;

	ofxDatGuiButton *zero_button_;
	ofxDatGuiButton *one_button_;
	ofxDatGuiButton *two_button_;
	ofxDatGuiButton *three_button_;
	ofxDatGuiButton *four_button_;
	ofxDatGuiButton *five_button_;
	ofxDatGuiButton *six_button_;
	ofxDatGuiButton *seven_button_;
	ofxDatGuiButton *eight_button_;
	ofxDatGuiButton *nine_button_;
	ofxDatGuiButton *plus_button_;
	ofxDatGuiButton *minus_button_;
	ofxDatGuiButton *mult_button_;
	ofxDatGuiButton *divides_button_;
	ofxDatGuiButton *d_button_;
	ofxDatGuiButton *h_button_;
	ofxDatGuiButton *l_button_;
	ofxDatGuiButton *equals_button_;
	ofxDatGuiButton *calc_clear_button_;

	std::vector<ofxDatGuiButton*> calculator_buttons_;

	void onCalculatorTextInputEvent(ofxDatGuiTextInputEvent textinput_e);
	void onCalculatorButtonEvent(ofxDatGuiButtonEvent button_e);

	void SetUpLabels();
	void SetUpButtons();

	int button_w_;
	int label_w_;
	int input_field_w_;
	int if_label_w_;
public:
	CalculatorWidget(std::string settings_filename);
	~CalculatorWidget();

	virtual void ParseWidgetSizeSettings();
	virtual void InitializeComponents();
	virtual void FormatComponents();
};

#endif