#ifndef _UI_TD_TIP_H_
#define _UI_TD_TIP_H_

#include "TDScale9.h"
#include "TDMaskPanel.h"

class TDTip;

class TDTipOper:public TDPanel{
public:
    
    
};


class TDTip:public TDPanel
{
public:
    TDTip();
    virtual bool init();
    
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
      
    void hide();
    
    virtual bool procTuiEvent(const string&,TDPanel*);
    
    void setOperPanel(TDTipOper* panel);
protected:
    
    TDTipOper* m_pOperPanel;
     
    Point m_tStartPos;
    
    void clear();
    
    int curInfoHeight;
    
    
};
#endif
