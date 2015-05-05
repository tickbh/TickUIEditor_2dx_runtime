#ifndef _UI_TD_BUTTON_H_
#define _UI_TD_BUTTON_H_

 
#include "TDScale9.h"
#include "TDBase.h"

using namespace rapidxml;

class TDButton:public TDPanel{
    
public:
    TDButton();
    ~TDButton();
    
    static TDButton* create(xml_node<> * pItem);
    virtual  void initWidthConf(xml_node<> * pItem);
    
    virtual void selected(); 
    virtual void unselected();
    virtual void onEnter();

    
    virtual void setVisible(bool visible);
 
    void setTarget(Ref*   ,SEL_MenuHandler);
    void setEnable(bool value);
    DEV_PROPERTY_READONLY(bool, m_bEnable, Enable)
    
    void setLabel(const char*);
    const char* getLabel();
    string linkPanel;
protected:
    
    const char* m_pLabel;
    
    
    Ref*       m_pListener;
    SEL_MenuHandler    m_pfnSelector;
    
    Node* m_pNormal;
    Node* m_pDown;
    Node* m_pDisable;
    
    Sprite* m_pNormalLabel;
    Sprite* m_pDownLabel;
    Sprite* m_pDisableLabel;
    
    void clear();
   
};

#endif
