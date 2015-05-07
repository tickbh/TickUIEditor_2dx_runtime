#ifndef _UI_TD_TRICHTEXT_H_
#define _UI_TD_TRICHTEXT_H_

#include "TDScale9.h"
#include "TDPanel.h"
#include "widget/WidgetRichText.h"

using namespace rapidxml;

class TDRichText:public TDPanel{
    
public:
    TDRichText();
    ~TDRichText();
    static TDRichText* create(const char* utf8_str, const Size& preferred_size, const char* font_alias = "");

	virtual bool init();
    
    static TDRichText* create(xml_node<> * pItem);
    virtual  void initWidthConf(xml_node<> * pItem);
	virtual  bool initWidthFormat(const char* utf8_str, const Size& preferred_size, const char* font_alias = "");
    
    void setString(const char* cstr);
    void setString(const string& str);
    void setString(int value);
    int getNum();
    std::string getString();
    void setColor(const Color3B& color);
	void setFontSize(int size);


	WidgetRichText* getRichLabel();
private:
    WidgetRichText* m_pLabel;
};




#endif
