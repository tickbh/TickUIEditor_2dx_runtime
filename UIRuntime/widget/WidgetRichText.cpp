#include "WidgetRichText.h"

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
	LabelTTF* label =  LabelTTF::create(content, "", defaultConfig.fontSize);
	this->addChild(label);
	return true;
}
