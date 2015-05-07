#ifndef _UI_TD_PAGE_H_
#define _UI_TD_PAGE_H_

#include "TDMaskPanel.h"  
#include "TDRichText.h"
#include "TDButton.h"
#include "TDPage.h"

class TDPage:public TDScrollPanel{
    
public:
    TDPage();
    virtual bool init();
    
    void layout();
    
    static TDPage*  create(xml_node<> * pItem); 
    virtual void  initWidthConf(xml_node<> * pItem); 
    
    
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    
    int nCurPage;
    int getTotalPage();
    int nMaxNum;
    
    virtual  void clearItems();
    
    void gotoPage(int );
    
    TDPanel* getItemByIdx(int idx);
	TDPanel* ensureItemByIdx(int idx);
    
    DEV_PROPERTY(TDPanel*, m_pLeftPanel, LeftPanel);
    DEV_PROPERTY(TDPanel*, m_pRightPanel, RightPanel);
    DEV_PROPERTY(TDRichText*, m_pPageTxt,  PageTxt);
protected:
    
    int m_nRowNum;
    int m_nColNum;
    float m_nRowDistance;
	float m_nColDistance;
	float m_nItemWidth;
	float m_nItemHeight;
	bool hasPageBar;
	int nPage;
    void onPageEnd(); 
    float getPageWidth(); 
    float getPageHeight();
	xml_node<> * m_RenderItem;
};



#endif
