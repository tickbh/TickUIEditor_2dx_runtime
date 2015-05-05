#include "TDTab.h"
#include "TDUI.h"

TDTab* TDTab::create(xml_node<> * pItem){
    
	TDTab*  ret = UIBase::create<TDTab>();
    ret->initWidthConf(pItem);
    return ret;
}

TDTab::~TDTab(){
    for(unsigned int i=0;i<gPanels.size();i++){
        gPanels[i]->release();
    }
    
}


TDTab::TDTab(){
    m_pListener=NULL;
    m_pfnSelector=NULL;
    m_pCurPanel=NULL;
    m_pCurBtn=NULL;
}

void TDTab::initWidthConf(xml_node<> * pItem){
   
    if(!pItem) return;
    Size size=readContainSize(pItem,getParent());
    if(size.width ==-1) size.width=getContentSize().width;
    if(size.height==-1) size.height=getContentSize().height;
    setContentSize(size);
    
    parseConf(pItem->first_node());
    
    
    onCreateComplete();
}


void TDTab::onCreateComplete(){
    
    TDPanel * node = 0;
    Point pos;
	for (auto child : getChildren()) {
		node = (TDPanel*)child;
		if (node->tName == T_BUTTON_NAME){
			gBtns.push_back((TDButton*)node);
			((TDButton*)node)->setTarget(this, menu_selector(TDTab::onBtnClick));
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

TDPanel* TDTab::getCurPanel(){
    
    return m_pCurPanel;
    
}
TDButton* TDTab::getCurTButton(){
    
    return m_pCurBtn;
}

void TDTab::onBtnClick(Ref* obj){
    selectBtn((TDButton*)obj);
}
void TDTab::clear(){ 
    for(unsigned int i=0;i<gPanels.size();i++){
        
        gPanels[i]->setOpacity(255);
        if(gPanels[i]->getParent()){
            gPanels[i]->getParent()->removeChild(gPanels[i], true);
        }
    }
    
    for(unsigned int i=0;i<gBtns.size();i++){
 
        gBtns[i]->setEnable(true);
    }
}


TDButton* TDTab::getBtnByTag(int tag){ 
    for(unsigned int i=0;i<gBtns.size();i++){
        
        vector<string>ret;
        splitStr(ret, gBtns[i]->linkPanel, ",");
        for(unsigned int j=0;j<ret.size();j++){
            TDPanel* item=getUI(ret[j].c_str());
            if(tag==item->getTag()){
                return (gBtns[i]);
                
            }
            
        } 
        
    }
    return NULL;
}
void TDTab::changeTab(int tag){
    
    TDButton* btn=getBtnByTag(tag);
    
    if(!btn){
        return;
    }
    selectBtn(btn);
}
void TDTab::changeIdx(int idx){
    TDButton* btn=gBtns[idx];
    
    if(!btn){
        return;
    }
    selectBtn(btn);
}

void TDTab::selectBtn(TDButton* btn){
    if(btn->linkPanel.size()==0){
        return;
    }
    clear();
    btn->setEnable(false);
    m_pCurBtn=btn;
    
    vector<string>ret;
    splitStr(ret, btn->linkPanel, ","); 
    for(unsigned int i=0;i<ret.size();i++){ 
 
        TDPanel* item=getUI(ret[i].c_str());
        if(item){
            m_pCurPanel=(TDPanel*)item;
        }
        if(item && item->getParent()==NULL){
            addChild(item,-1);
        }
        
    }
    
    
    if(m_pListener&& m_pfnSelector)
        (m_pListener->*m_pfnSelector)(btn);

    //if(m_uListener && func.size() > 0) {
    //    FlashBuilderManager::sharedManager()->onPanelClicked(this, m_uListener, func.c_str());
    //}
}

void TDTab::setTabChangeTarget(Ref*  listener,SEL_MenuHandler    selector){
    
     m_pListener=listener;
     m_pfnSelector=selector;
}



