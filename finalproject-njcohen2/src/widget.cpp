#include "widget.h"

Widget::Widget(std::string settings_filename) {
	settings_filename_ = settings_filename;
}

Widget::~Widget() {

}

void Widget::SetWidgetTheme(const ofxDatGuiTheme* theme) {
	for (ofxDatGuiComponent *component : gui_components_) {
		component->setTheme(theme);
	}

	FormatComponents();
}

int Widget::GetPosX() {
	return posx_;
}

int Widget::GetPosY() {
	return posy_;
}

int Widget::GetWidth() {
	return width_;
}

std::string Widget::GetSettingsFile() {
	return settings_filename_;
}

std::vector<ofxDatGuiComponent*> Widget::GetComponents() {
	return gui_components_;
}