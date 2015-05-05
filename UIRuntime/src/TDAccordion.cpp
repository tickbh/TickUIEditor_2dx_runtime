#include "TDAccordion.h"
#include "TDUI.h"

TDAccordion* TDAccordion::create(xml_node<> * pItem){
    
	TDAccordion*  ret = UIBase::create<TDAccordion>();
    ret->initWidthConf(pItem);
    return ret;
}

TDAccordion::~TDAccordion(){
    for(unsigned int i=0;i<gPanels.size();i++){
        gPanels[i]->release();
    }
    
}


TDAccordion::TDAccordion(){
    m_pListener=NULL;
    m_pfnSelector=NULL;
    
    m_pCurPanel=NULL;
    m_pCurBtn=NULL;
}

void TDAccordion::initWidthConf(xml_node<> * pItem){
	TDPanel::initWidthConf(pItem);

    if(!pItem) return;
    onCreateComplete();
}


void TDAccordion::onCreateComplete(){
    TDPanel * node = 0;
    Point pos;
	for (auto child : getChildren()) {
		node = (TDPanel*)child;
		if (node->tName == T_BUTTON_NAME){
			gBtns.push_back((TDButton*)node);
			((TDButton*)node)->setTarget(this, menu_selector(TDAccordion::onBtnClick));
		}
		else{
			node->retain();
			gPanels.push_back((TDPanel*)node);
		}
	}
    
    if(gBtns.size()!=0){
        selectBtn(gBtns[0]);
    }
}

TDPanel* TDAccordion::getCurPanel(){
    
    return  m_pCurPanel;
    
}
TDButton* TDAccordion::getCurTButton(){
   
    return  m_pCurBtn;
}

void TDAccordion::onBtnClick(Ref* obj){
    selectBtn((TDButton*)obj);
}
void TDAccordion::clear(){
    for(unsigned int i=0;i<gPanels.size();i++){
        if(gPanels[i]->getParent()){
            gPanels[i]->getParent()->removeChild(gPanels[i], true);
        }
    }
    
    for(unsigned int i=0;i<gBtns.size();i++){
        gBtns[i]->setEnable(true);
    }
}


TDButton* TDAccordion::getBtnByTag(int tag){
    for(unsigned int i=0;i<gBtns.size();i++){
         
        TDPanel* item=getUI(gBtns[i]->linkPanel);
        if(item && tag==item->getTag()){
            return (gBtns[i]);
        }
    }
    return NULL;
}
void TDAccordion::changeTab(int tag){
    
    TDButton* btn=getBtnByTag(tag);
    
    if(!btn){
        return;
    }
    selectBtn(btn);
}
void TDAccordion::changeIdx(int idx){
    TDButton* btn=gBtns[idx];
    
    if(!btn){
        return;
    }
    selectBtn(btn);
}

void TDAccordion::selectBtn(TDButton* btn){
    if(btn->linkPanel.size()==0){
        return;
    }
    clear();
    btn->setEnable(false);
    
    m_pCurBtn=btn;
    
   
    TDPanel* item=getUI( btn->linkPanel);
    if(item){
        m_pCurPanel=(TDPanel*)item;
    }
   if(item && item->getParent()==NULL){
        addChild(item,-1);
    } 
    layout();
    
    if(m_pListener&& m_pfnSelector)
        (m_pListener->*m_pfnSelector)(btn);

	//if(m_uListener && func.size() > 0) {
	//	FlashBuilderManager::sharedManager()->onPanelClicked(this, m_uListener, func.c_str());
	//}
}

void TDAccordion::layout(){
    float curHeight=0;
    for(unsigned int i=0;i<gBtns.size();i++){
        if(gBtns[i]){ 
            gBtns[i]->stopAllActions(); 
            Point curPos=gBtns[i]->getPosition();
            curPos.y=-curHeight; 
            gBtns[i]->runAction(  CCEaseExponentialOut::create(CCMoveTo::create(0.2f, curPos))); 
            curHeight+=gBtns[i]->getContentSize().height;
                                
            if(getCurTButton()==gBtns[i]){ 
                TDPanel* panel=getUI( gBtns[i]->linkPanel);
                if(panel){
                    panel->setPositionY(-curHeight);
                    curHeight+=panel->getContentSize().height;
                }
            }
        }
    }
}

void TDAccordion::seTAccordionChangeTarget(Ref*  listener,SEL_MenuHandler    selector){
    
    m_pListener=listener;
    m_pfnSelector=selector;
}

