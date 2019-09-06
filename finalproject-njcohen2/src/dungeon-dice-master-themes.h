#pragma once

#include "ofxDatGuiTheme.h"

class DDMThemeDragon : public ofxDatGuiTheme {
public:
	DDMThemeDragon() {
		stripe.visible = true;
		color.label = hex(0xFFFFFF);
		color.textInput.text = hex(0xFFFFFF);

		color.background = hex(0xB12A19);
		color.guiBackground = hex(0x95321e);
		color.inputAreaBackground = hex(0xFF381F);
		
		color.textInput.highlight = hex(0xFF4081);
		color.textInput.backgroundOnActive = hex(0xF50057);
		color.backgroundOnMouseOver = hex(0xFF80AB);
		color.backgroundOnMouseDown = hex(0xF50057);

		color.icons = hex(0xFFFFFF);
		color.pad2d.line = hex(0xFFFFFF);
		color.pad2d.ball = hex(0xFFFFFF);
		init();
	}
};

class DDMThemeAquatic : public ofxDatGuiTheme {
public:
	DDMThemeAquatic() {
		stripe.visible = true;
		color.label = hex(0xFFFFFF);
		color.textInput.text = hex(0xFFFFFF);

		color.background = hex(0x1b2571);
		color.guiBackground = hex(0x0F1440);
		color.inputAreaBackground = hex(0x134f89);

		color.textInput.highlight = hex(0x197a9e);
		color.textInput.backgroundOnActive = hex(0x197a9e);
		color.backgroundOnMouseOver = hex(0x197a9e);
		color.backgroundOnMouseDown = hex(0x145b76);

		color.icons = hex(0xFFFFFF);
		color.pad2d.line = hex(0xFFFFFF);
		color.pad2d.ball = hex(0xFFFFFF);
		init();
	}
};

class DDMThemeRoyalty : public ofxDatGuiTheme {
public:
	DDMThemeRoyalty() {
		stripe.visible = true;
		color.label = hex(0xFFFFFF);
		color.textInput.text = hex(0xFFFFFF);

		color.background = hex(0x4729c0);
		color.guiBackground = hex(0x9032b8);
		color.inputAreaBackground = hex(0xf4c1976);

		color.textInput.highlight = hex(0x3b1758);
		color.textInput.backgroundOnActive = hex(0x320954);
		color.backgroundOnMouseOver = hex(0x2d0d46);
		color.backgroundOnMouseDown = hex(0x1e0930);

		color.icons = hex(0xFFFFFF);
		color.pad2d.line = hex(0xFFFFFF);
		color.pad2d.ball = hex(0xFFFFFF);
		init();
	}
};

class DDMThemeForest : public ofxDatGuiTheme {
public:
	DDMThemeForest() {
		stripe.visible = true;
		color.label = hex(0xFFFFFF);
		color.textInput.text = hex(0xFFFFFF);

		color.background = hex(0x2c5e2f);
		color.guiBackground = hex(0x319538);
		color.inputAreaBackground = hex(0x1a9822);

		color.textInput.highlight = hex(0x16811c);
		color.textInput.backgroundOnActive = hex(0x125717);
		color.backgroundOnMouseOver = hex(0x1a481d);
		color.backgroundOnMouseDown = hex(0x123414);

		color.icons = hex(0xFFFFFF);
		color.pad2d.line = hex(0xFFFFFF);
		color.pad2d.ball = hex(0xFFFFFF);
		init();
	}
};

class DDMThemeIllini : public ofxDatGuiTheme {
public:
	DDMThemeIllini() {
		stripe.visible = true;
		color.label = hex(0xFFFFFF);
		color.textInput.text = hex(0xFFFFFF);

		color.background = hex(0xc16d29);
		color.guiBackground = hex(0x965521);
		color.inputAreaBackground = hex(0x7d4b22);

		color.textInput.highlight = hex(0x3843de6);
		color.textInput.backgroundOnActive = hex(0x262eaa);
		color.backgroundOnMouseOver = hex(0x181d68);
		color.backgroundOnMouseDown = hex(0x0f134d);

		color.icons = hex(0xFFFFFF);
		color.pad2d.line = hex(0xFFFFFF);
		color.pad2d.ball = hex(0xFFFFFF);
		init();
	}
};

class DDMThemeNature : public ofxDatGuiTheme {
public:
	DDMThemeNature() {
		stripe.visible = true;
		color.label = hex(0xFFFFFF);
		color.textInput.text = hex(0xFFFFFF);

		color.background = hex(0x264185);
		color.guiBackground = hex(0x147f35);
		color.inputAreaBackground = hex(0x6b6e1e);

		color.textInput.highlight = hex(0x494b14);
		color.textInput.backgroundOnActive = hex(0x386a31);
		color.backgroundOnMouseOver = hex(0x1842ab);
		color.backgroundOnMouseDown = hex(0x0d255f);

		color.icons = hex(0xFFFFFF);
		color.pad2d.line = hex(0xFFFFFF);
		color.pad2d.ball = hex(0xFFFFFF);
		init();
	}
};