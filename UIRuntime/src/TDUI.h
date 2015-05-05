#ifndef _UI_TD_UI_H_
#define _UI_TD_UI_H_

#include "TDBase.h"

#define T_BUTTON_NAME   "Button"
#define T_SCALE9_NAME   "Scale9"
#define T_IMAGE_NAME    "Sprite"
#define T_PAGE_NAME     "Page"
#define T_PANEL_NAME    "Panel"
#define T_BAR_NAME      "ProgressBar"
#define T_WIN_NAME      "tdui:TDWin"
#define T_INPUT_NAME   "Input"
#define T_RICH_TEXT_NAME  "Text"

class TDUIExpand{
public: 
    virtual TDPanel* createUI(xml_node<> *);
    virtual TDPanel* createUI(const string&);
};

                  
class   TDUI
{
public:
    TDUI(void);
    virtual ~TDUI(void);
    
    void init();
    static TDUI* instance(void);
    
    
    void setExpand(TDUIExpand* exp);
    
    TDPanel* createUI(xml_node<> *);
    TDPanel* createUI(const string&);
	TDPanel* createBaseUI(const string& itemName);
    
    xml_document<>* getDoc(const string&);
    void addDoc(const string& ,xml_document<>*,unsigned char * data);
protected:
    map<string, xml_document<> * > docs;
    vector<unsigned char *> datas;
    TDUIExpand* m_pExpand;
};



#endif
