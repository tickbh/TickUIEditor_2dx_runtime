#ifndef _UI_TD_MASKPANEL_H_
#define _UI_TD_MASKPANEL_H_


#include "TDBase.h"


class TMaskContainer :public TDPanel{
public:
    CREATE_FUNC(TMaskContainer);
    
    virtual bool init();
    
    //virtual void visit();
    
    virtual void  afterDraw();
    
    virtual void  beforeDraw();
      
     
    
};


class TDPanel;

class TMaskPanel:public TDPanel{
    
public:
    
    TMaskPanel();
    
    virtual bool init();
    
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    
    DEV_PROPERTY_READONLY(float ,m_nRealContainerHeight,RealContainerHeight);
    
	DEV_PROPERTY_READONLY(float, m_nRealContainerWidth, RealContainerWidth);
     
    
    DEV_PROPERTY_READONLY(TMaskContainer*  ,m_pContainer, Container);
    
    void calculateRealHeight();
    
    void calculateRealWidth();
    
    virtual  void initWidthConf(xml_node<> * pItem);
    
    
    void moveToPos(const Point& pos,bool check=false);
    void moveToBottom();
    void moveToTop();
    
    void checkVisible();
    int renderStartTag;
};




enum TScrollDirection{
    
    TScrollV,
    TScrollH,
    
};

class TDScrollPanel:public TMaskPanel{
public:
    CREATE_FUNC(TDScrollPanel);
    
    virtual bool init();
     
    
    static TDScrollPanel* create(xml_node<> * pItem);
    virtual  void initWidthConf(xml_node<> * pItem);
    
    virtual void addChild(Node * child);
    TDPanel* getItemByTag(int tag);
    
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    
    
    DEV_PROPERTY(bool, m_bIsScroll, IsScroll);
    
    
    void onMoveEnd();
    
    DEV_PROPERTY(TScrollDirection , m_nDirection, Direction);

    void moveToBottom();
    void moveToPos(const Point& pos,bool check=false);
    void moveToTop();
protected: 
    bool isCheckBottom;

};


#endif
