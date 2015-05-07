#ifndef _UI_TD_TAB_H_
#define _UI_TD_TAB_H_

#include "TDPanel.h"
#include "TDButton.h" 

using namespace rapidxml;

class TDTab:public TDPanel{
    
public: 
    
    ~TDTab();
    TDTab();
    
    static TDTab* create(xml_node<> * pItem);
    virtual  void initWidthConf(xml_node<> * pItem); 
    virtual void onCreateComplete();
    
    TDPanel* getCurPanel();
    TDButton* getCurTButton();
    void setTabChangeTarget(Ref*  m_pListener,SEL_MenuHandler    m_pfnSelector);
    void changeTab(int tag);
    void changeIdx(int idx);
    TDButton* getBtnByTag(int tag);
protected:
    
    TDPanel* m_pCurPanel;
    TDButton* m_pCurBtn;
    Ref*       m_pListener;
    SEL_MenuHandler    m_pfnSelector;
    vector<TDButton*> gBtns;
    vector<TDPanel*>  gPanels;
    void onBtnClick(Ref*);
    void selectBtn(TDButton* btn);
    void clear();
};

#endif
