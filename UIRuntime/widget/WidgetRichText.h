#ifndef _WIDGET_RICH_TEXT_H_
#define _WIDGET_RICH_TEXT_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class RichConfig {
public:
	Color3B color;
	int fontSize;
	float outlineSize;
	Color3B outlineColor;
	RichConfig(Color3B color = Color3B::BLACK, int fontSize = 12, float outlineSize = 0.0, Color3B outlineColor = Color3B::BLACK)
	:color(color)
	,fontSize(fontSize)
	,outlineSize(outlineSize)
	,outlineColor(outlineColor){

	}

	RichConfig& operator= (RichConfig& other) {
		this->color = other.color;
		this->fontSize = other.fontSize;
		this->outlineSize = other.outlineSize;
		this->outlineColor = other.outlineColor;
	}
};

static const RichConfig defaultConfig;

class WidgetRichText : public Node {
public:
	static WidgetRichText* create(std::string content, Size size, RichConfig config = defaultConfig) {
		WidgetRichText* widget = new WidgetRichText(content, size, defaultConfig);
		if (widget) {
			widget->autorelease();
		}
		return widget;
	}
	WidgetRichText(std::string content, Size size, RichConfig config = defaultConfig)
	:content(content)
	, orignConfig(config)
	, curConfig(config)
	{
		this->setContentSize(size);
		parseText();
	}

	void setContent(std::string content);
	std::string getContent() { return this->content; }
	void setColor(Color3B color);
	void setFontSize(float fontSize);
	bool parseText();

private:
	std::string content;
	RichConfig orignConfig;
	RichConfig curConfig;
};

#endif