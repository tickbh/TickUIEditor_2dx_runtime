#ifndef  _UI_ACCORDION_H_
#define  _UI_ACCORDION_H_

#include "TDPanel.h"
#include "TDButton.h"


class TDAccordion :public TDPanel{
    
public:
    
    ~TDAccordion();
    TDAccordion();
    
    static TDAccordion* create(xml_node<> * pItem);
    virtual void initWidthConf(xml_node<> * pItem);
    virtual void onCreateComplete();
    
    TDPanel* getCurPanel();
    TDButton* getCurTButton();
    void seTAccordionChangeTarget(Ref*  m_pListener,SEL_MenuHandler    m_pfnSelector);
    void changeTab(int tag);
    void changeIdx(int idx);
    TDButton* getBtnByTag(int tag);
protected:
    void layout();
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
