#include "TDWin.h"
#include "TDScale9.h"

/***************************************************
 * TWin
 **************************************************/

TDWin::TDWin()
{
    m_nWinID = 0;  
    
}

TDWin::~TDWin(){
}

bool TDWin::init(void){
    
    if(!TDPanel::init()){
        return false;
    } 
  
    return true;
}

bool TDWin::onTouchBegan(Touch *pTouch, Event *pEvent){
    
    Point clickPos= pTouch->getLocation();
    Point pos= getPosInTarget(clickPos, this);
    
    if(pos.x<0 || pos.x>getContentSize().width
       ||pos.y<0 || pos.y>getContentSize().height  ){
        return false;
    }
	TDPanel::onTouchBegan(pTouch, pEvent);
    return true;
}

void TDWin::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	TDPanel::onTouchMoved(pTouch, pEvent);
}


void TDWin::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	TDPanel::onTouchEnded(pTouch, pEvent);
}
 

bool TDWin::procTuiEvent(const string& event,TDPanel* target){
	cocos2d::log("event no deal with %s", event.c_str());
    return TDPanel::procTuiEvent(event, target);
}

void TDWin::onEnter()
{
	TDPanel::onEnter();
	registerWithTouchDispatcher();
}


