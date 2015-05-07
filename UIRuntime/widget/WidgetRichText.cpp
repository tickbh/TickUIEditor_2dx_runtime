#include "WidgetRichText.h"
#include "src/UIBase.h"

void WidgetRichText::setContent(std::string content) {
	this->content = content;
	_isDataDirty = true;
}

bool WidgetRichText::parseText() {
	if (!_isDataDirty)
		return true;
	_isDataDirty = false;
	_richElements.clear();
	_formatTextDirty = true;
	const char* info = content.c_str();
	curConfig = orignConfig;
	int pre = 0;
	bool inSerch = false;
	std::string::size_type searchPos;
	for (int i = 0, len = content.length(); i < len; i++)
	{
		if (content[i] != '[' || (i > 0 && content[i - 1] == '\\'))
			continue;
		inSerch = true;
		if (i > pre) {
			ui::RichElementText* re = generateRichText(content.substr(pre, i - pre), curConfig);
			if (re)
				this->pushBackElement(re);
		}
		searchPos = content.find(']', i);
		if (searchPos == std::string::npos) {
			break;
		}
		if (searchPos - i > 1)
			parseConfig(content.substr(i + 1, searchPos - i - 1), orignConfig, curConfig);
		i = pre = searchPos + 1;
		inSerch = false;
	}
	if (!inSerch) {
		ui::RichElementText* re = generateRichText(content.substr(pre, content.length() - pre), curConfig);
		if (re)
			this->pushBackElement(re);
	}
	//LabelTTF* label = LabelTTF::create(content.c_str(), "Helvetica", orignConfig.fontSize, this->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
	//label->setColor(orignConfig.color);
	//this->addChild(label);
	//setCenterPos(this, label);
	return true;
}

void WidgetRichText::setColor(Color3B color) {
	orignConfig.color = color;
	_isDataDirty = true;
}

void WidgetRichText::setFontSize(float fontSize) {
	orignConfig.fontSize = fontSize;
	_isDataDirty = true;
}

ui::RichElementText* WidgetRichText::generateRichText(std::string value, RichConfig& config) {
	ui::RichElementText* re1 = ui::RichElementText::create(config.tags, config.color, 255, value, "Helvetica", config.fontSize);
	config.tags = 0;
	return re1;
}

bool WidgetRichText::parseConfig(std::string value, RichConfig originConfig, RichConfig& curConfig) {
	if (value.empty()) {
		return false;
	}
	if (value == "/c") {
		curConfig.color = originConfig.color;
	} else if (value == "/f") {
		curConfig.fontSize = originConfig.fontSize;
	} else if (value == "cr") {
		curConfig.color = Color3B::RED;
	} else if (value == "cw") {
		curConfig.color = Color3B::WHITE;
	} else if (value == "cy") {
		curConfig.color = Color3B::YELLOW;
	} else if (value == "cg") {
		curConfig.color = Color3B::GREEN;
	} else if (value == "cm") {
		curConfig.color = Color3B::MAGENTA;
	} else if (value == "cb") {
		curConfig.color = Color3B::BLACK;
	} else if (value == "co") {
		curConfig.color = Color3B::ORANGE;
	} else if (value == "cgr") {
		curConfig.color = Color3B::GRAY;
	} else if (value.find("c") == 0) {
		value = value.substr(1);
		bool success = false;
		unsigned int color = parseColor(value, &success);
		if (success)
			curConfig.color = parseRgb(color);
	} else if (value.find("f") == 0) {
		value = value.substr(1);
		int size = atoi(value.c_str());
		if (size != 0)
			curConfig.fontSize = size;
	}
	return true;
}

void WidgetRichText::adaptRenderers() {
	parseText();
	ui::RichText::adaptRenderers();
}
