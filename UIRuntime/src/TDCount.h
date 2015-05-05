#ifndef _UI_TD_COUNT_H_
#define _UI_TD_COUNT_H_


#include "TDBase.h"

class TDRichText;


class TDCounterPanel:public TDPanel{
    
public:
    TDCounterPanel();
    
    Node* pCom;
    
    virtual bool init(); 
    
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    
    DEV_PROPERTY(int, m_nMaxNum, MaxNum);
    
    virtual bool procTuiEvent(const string&,TDPanel*);
protected: 
    void hide(); 
     
    
}; 

class TDCount:public TDPanel{
public:
    TDCount();
    ~TDCount();
    
    virtual bool init();
    
    CREATE_FUNC(TDCount);
    
    static TDCount*  create(xml_node<> * pItem);
    
    virtual  void  initWidthConf(xml_node<> * pItem);
      
    void onShow();
    
    void onHide();
    
    bool getIsOpen();
    
    int getNum();
    
    virtual void selected();
    
    virtual void unselected();
    
    DEV_PROPERTY_READONLY(int, m_nMaxNum, MaxNum);
    
    void setMaxNum(int num);
    
    void setNum(int num);
    
    void setTarget(Ref *rec, SEL_MenuHandler selector);
    
    void setCompleteTarget(Ref *rec, SEL_MenuHandler selector);
    void setCloseTarget(Ref *rec, SEL_MenuHandler selector);
    
    void inputEnd();
    void inputClose();
public:
    
    Ref*       m_pListener;
    SEL_MenuHandler    m_pfnSelector;
    
    Ref*       m_pClListener;
    SEL_MenuHandler    m_pClfnSelector;
    
    Ref*       m_pCListener;
    SEL_MenuHandler    m_pCfnSelector;
    
    int m_nNum;
    Node* m_pCountPanel;
	TDRichText* m_pLabel;
};



#endif
