#ifndef _WIDGET_RICH_TEXT_H_
#define _WIDGET_RICH_TEXT_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;

class RichConfig {
public:
	Color4B color;
	int fontSize;
	float outlineSize;
	Color4B outlineColor;
	RichConfig(Color4B color = Color4B::BLACK, int fontSize = 12, float outlineSize = 0.0, Color4B outlineColor = Color4B::BLACK)
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
	static WidgetRichText* create(std::string content, RichConfig config = defaultConfig) {
		WidgetRichText* widget = new WidgetRichText(content, defaultConfig);
		if (widget) {
			widget->autorelease();
		}
		return widget;
	}
	WidgetRichText(std::string content, RichConfig config = defaultConfig)
	:content(content)
	, orignConfig(config)
	, curConfig(config)
	{
		parseText();
	}

	void setContent(std::string content);
	std::string getContent() { return this->content; }
	bool parseText();

private:
	std::string content;
	RichConfig orignConfig;
	RichConfig curConfig;
};

#endif