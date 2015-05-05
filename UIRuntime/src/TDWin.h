#ifndef _UI_TD_WIN_H_
#define _UI_TD_WIN_H_

#include "TDBase.h"

USING_NS_CC;

class TDWin : public  TDPanel
{
public:
    virtual ~TDWin();
    TDWin();
    
	virtual bool init(void);
     
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    
    virtual void onShow(); 

	virtual void onEnter();
    
    virtual void onClose();
    
    virtual void onRefresh(){}

    
	int getWinID() { return m_nWinID; }
    
	void setWinID(int nID) { m_nWinID = nID; }
    
    
    virtual bool procTuiEvent(const string&,TDPanel*);
     
protected: 
    
	int m_nWinID;
     
};

#endif
