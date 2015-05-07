#ifndef _WIDGET_RICH_TEXT_H_
#define _WIDGET_RICH_TEXT_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/UIRichText.h"
#include "src/UIBase.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RichConfig {
public:
	Color3B color;
	int fontSize;
	float outlineSize;
	Color3B outlineColor;
	int tags;
	RichConfig(Color3B color = Color3B::BLACK, int fontSize = 12, float outlineSize = 0.0, Color3B outlineColor = Color3B::BLACK)
	:color(color)
	,fontSize(fontSize)
	,outlineSize(outlineSize)
	,outlineColor(outlineColor)
	,tags(0){

	}

	RichConfig& operator= (RichConfig& other) {
		this->color = other.color;
		this->fontSize = other.fontSize;
		this->outlineSize = other.outlineSize;
		this->outlineColor = other.outlineColor;
		return *this;
	}
};

static const RichConfig defaultConfig;

class WidgetRichText : public ui::RichText {
public:
	static WidgetRichText* create(std::string content, Size size, RichConfig config = defaultConfig) {
		WidgetRichText* widget = new WidgetRichText(content, size, defaultConfig);
		if (widget && widget->init()) {
			widget->autorelease();
			return widget;
		}
		delete widget;
		return nullptr;
	}
	WidgetRichText(std::string content, Size size, RichConfig config = defaultConfig)
	: RichText()
	, content(content)
	, orignConfig(config)
	, curConfig(config)
	, _isDataDirty(true)
	{
		this->setContentSize(size);
	}

	void setContent(std::string content);
	std::string getContent() { return this->content; }
	void setColor(Color3B color);
	void setFontSize(float fontSize);
	bool parseText();
	
private:
	virtual void adaptRenderers() override;
	bool parseConfig(std::string value, RichConfig originConfig, RichConfig& curConfig);
	ui::RichElementText* generateRichText(std::string value, RichConfig& config);
	std::string content;
	RichConfig orignConfig;
	RichConfig curConfig;
	bool _isDataDirty;
};

#endif