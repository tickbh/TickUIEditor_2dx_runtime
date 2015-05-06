#include "WidgetRichText.h"
#include "src/UIBase.h"

void WidgetRichText::setContent(std::string content) {
	this->content = content;
	parseText();
}

bool WidgetRichText::parseText() {
	this->removeAllChildren();
	const char* info = content.c_str();
	int pre = 0;
	for (int i = 0, len = content.length(); i < len; i++)
	{
		
	}
	LabelTTF* label = LabelTTF::create("rewqrewqreqwrewq", "Helvetica", curConfig.fontSize, this->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
	label->setColor(curConfig.color);
	this->addChild(label);
	setCenterPos(this, label);
	return true;
}

void WidgetRichText::setColor(Color3B color) {
	curConfig.color = color;
	parseText();
}

void WidgetRichText::setFontSize(float fontSize) {
	curConfig.fontSize = fontSize;
	parseText();
}
