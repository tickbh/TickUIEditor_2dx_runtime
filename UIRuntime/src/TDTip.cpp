#include "TDTip.h"
#include "TDScale9.h"
#include "TDUI.h"


/***************************************************
 * TTip
 **************************************************/
TDTip::TDTip(){ 
    m_pOperPanel=NULL;
}
bool TDTip::init(){
     
    if(!TDPanel::init()){
        return false;
    } 
    
    return true;
}


void TDTip::setOperPanel(TDTipOper* panel){
    TDPanel* container= (TDPanel* ) getUI("operPanel");
    container->removeAllChildrenWithCleanup(true);
    if(panel==NULL){
        return;
    }
    panel->setTag(1);//为了引导
    this->m_pOperPanel=panel;
    container->addChild(panel);
    
    if(!m_pOperPanel->hasLoadConf){
        m_pOperPanel->loadConf(m_pOperPanel->confPath);
    }
}


void TDTip::clear(){ 
}


bool TDTip::procTuiEvent(const string& event,TDPanel*){
    if(event=="closeTip"){
        hide();
        return true;
    }
    return false;
}
void TDTip::hide(){
    if(this->getParent()){
        this->getParent()->removeChild(this, true);
    }
}
 

bool TDTip::onTouchBegan(Touch *pTouch, Event *pEvent){
    
    Point clickPos= pTouch->getLocation();
    
    Point pos= getPosInTarget(clickPos, this);
    
    if(pos.x<0 || pos.x>getContentSize().width
       ||pos.y>0 || pos.y<-getContentSize().height  ){
         
        hide();
        return false;
    } 
    TDPanel::onTouchBegan(pTouch, pEvent);
  
    
    return true;
}



