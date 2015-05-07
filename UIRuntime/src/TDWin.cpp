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
    //if(event=="closeWin"){
    //    if(this->getParent()){
    //        this->getParent()->removeChild(this, true);
    //    }
    //    return true;
    //} 
    return TDPanel::procTuiEvent(event, target);
}

void TDWin::onShow(){
	Size parentSize = getParentSize(getParent());
	//this->setX(parentSize.width/2-getContentSize().width/2);
	//this->setY(parentSize.height/2-getContentSize().height/2);
	//this->setReversePosition();
}

void TDWin::onClose(){
    
}

void TDWin::onEnter()
{
	TDPanel::onEnter();
	registerWithTouchDispatcher();
}


