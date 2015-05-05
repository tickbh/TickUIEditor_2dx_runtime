#include "TDButton.h"
#include "TDScale9.h"
#include "TDUI.h"


TDButton::TDButton()
:m_pNormal(NULL)
,m_pDown(NULL)
,m_pDisable(NULL)
 
{
    
    m_pNormalLabel=NULL;
    m_pDownLabel=NULL;
    m_pDisableLabel=NULL;
    m_bEnable=true;
    m_pListener=NULL;
    m_pfnSelector=NULL;
    m_pLabel=NULL;
}

TDButton::~TDButton(){
    
    
}

void TDButton::onEnter(){
    TDPanel::onEnter();
 
}


void TDButton::setVisible(bool visible){
    if(isVisible()==visible){
        return;
    }
    
    TDPanel::setVisible(visible); 
    unselected();
     
}


void TDButton::setEnable(bool value){
    if(m_bEnable!=value){
        m_bEnable=value;
        if(m_bEnable){
            unselected();
        }else{
            clear();
            m_pDisable->setVisible(true);
            if(m_pDisableLabel)m_pDisableLabel->setVisible(true);
        }
    }
}

void TDButton::clear(){
    setOpacity(255);
    if(m_pNormal){
        m_pNormal->setOpacity(255);
       m_pNormal->setVisible(false); 
    }
    if(m_pDown){
        m_pDown->setOpacity(255);
        m_pDown->setVisible(false);
    }
    if(m_pDisable){
        m_pDisable->setOpacity(255);
        m_pDisable->setVisible(false);
    }
    
    
    if(m_pNormalLabel)
    {
        m_pNormalLabel->setOpacity(255);
        m_pNormalLabel->setVisible(false);
    }
    if(m_pDownLabel)
    {
        m_pDownLabel->setOpacity(255);
        m_pDownLabel->setVisible(false);
    }
    
    if(m_pDisableLabel)
    {
        m_pDisableLabel->setOpacity(255);
        m_pDisableLabel->setVisible(false);
    }
}
void TDButton::selected(){
    if(!m_bEnable){
        return;
    }
    clear();
    if(m_pDown) m_pDown->setVisible(true);
    if(m_pDownLabel)m_pDownLabel->setVisible(true);
    if (m_pListener && m_pfnSelector)
    {
        (m_pListener->*m_pfnSelector)(this);
    }
}


const char* TDButton::getLabel(){
    if(m_pLabel==NULL){
        return "";
    }
    
    return m_pLabel;
}

void TDButton::unselected(){
    if(!m_bEnable){
        return;
    }
    clear();
    if(m_pNormal) m_pNormal->setVisible(true);
     if(m_pNormalLabel)m_pNormalLabel->setVisible(true);
    
}
TDButton* TDButton::create(xml_node<> * pItem){
	TDButton*  ret = UIBase::create<TDButton>();
    ret->initWidthConf(pItem);
    return ret;
}

void TDButton::setLabel(const char* path){
    
    m_pLabel=path;
    if(UIUtils::getInstance()->spriteFrameByName(path)){
        if(m_pNormalLabel==NULL){
            m_pNormalLabel=Sprite::createWithSpriteFrameName(path);
            addChild(m_pNormalLabel);
        }else{
             m_pNormalLabel->setSpriteFrame( UIUtils::getInstance()->spriteFrameByName(path)); 
        }
        
		m_pNormalLabel->setPosition(Vec2(getContentSize().width / 2, -getContentSize().height / 2));
        
        
        if(m_pDownLabel==NULL){
            m_pDownLabel=Sprite::createWithSpriteFrameName(path);
            addChild(m_pDownLabel);
        }else{
			m_pDownLabel->setSpriteFrame(UIUtils::getInstance()->spriteFrameByName(path));
        }
        
		m_pDownLabel->setPosition(Vec2(getContentSize().width / 2, -getContentSize().height / 2));
    }
    
}

void TDButton::initWidthConf(xml_node<> * pItem){ 
	float width = 0, height = 0;
    string normalPath, downPath,disablePath;
    string normalLabelPath, downLabelPath,disableLabelPath;
    
    readAttrString(pItem, "normalLabel", normalLabelPath);
    readAttrString(pItem, "downLabel", downLabelPath);
    readAttrString(pItem, "disableLabel", disableLabelPath);
    
     
    readAttrString(pItem, "normalImage", normalPath);
    readAttrString(pItem, "downImage", downPath);
    readAttrString(pItem, "disableImage", disablePath);
    
    readAttrString(pItem, "linkPanel", linkPanel);
   
    
    Size size=readContainSize(pItem,getParent());
    if(size.width !=-1){
        width=size.width;
    }
    
    if(size.height!=-1){
        height=size.height;
    }
    
    if(disablePath.size()==0){
        disablePath=downPath;
    }
    
    if(disableLabelPath.size()==0){
        disableLabelPath=downLabelPath;
    }
    
   

	float anchor = 0.5f;
    if(UIUtils::getInstance()->spriteFrameByName(normalLabelPath.c_str())){ 
        m_pNormalLabel=Sprite::createWithSpriteFrameName(normalLabelPath.c_str());
		m_pNormalLabel->setAnchorPoint(Vec2(anchor, anchor));
    }
    
    if(UIUtils::getInstance()->spriteFrameByName(downLabelPath.c_str())){
        m_pDownLabel=Sprite::createWithSpriteFrameName(downLabelPath.c_str());
		m_pDownLabel->setAnchorPoint(Vec2(anchor, anchor));
    }
    if(UIUtils::getInstance()->spriteFrameByName(disableLabelPath.c_str())){
        m_pDisableLabel=Sprite::createWithSpriteFrameName(disableLabelPath.c_str());
		m_pDisableLabel->setAnchorPoint(Vec2(anchor, anchor));
    }
    
    
    anchor = 0;
    if(width==0 && height==0){
        m_pNormal=Sprite::createWithSpriteFrame(UIUtils::getInstance()->spriteFrameByName(normalPath.c_str()));
        m_pDown=Sprite::createWithSpriteFrame(UIUtils::getInstance()->spriteFrameByName(downPath.c_str()));
        m_pDisable=Sprite::createWithSpriteFrame(UIUtils::getInstance()->spriteFrameByName(disablePath.c_str()));
        m_pNormal->setAnchorPoint(Vec2(anchor, anchor));
		m_pDown->setAnchorPoint(Vec2(anchor, anchor));
		m_pDisable->setAnchorPoint(Vec2(anchor, anchor));
        if (m_pNormal) { 
            setContentSize(m_pNormal->getContentSize());
        }
        
    }else{
        m_pNormal=TDScale9::create(normalPath.c_str());
        m_pDown=TDScale9::create(downPath.c_str());
        m_pDisable=TDScale9::create(disablePath.c_str());
		m_pNormal->setAnchorPoint(Vec2(anchor, anchor));
		m_pDown->setAnchorPoint(Vec2(anchor, anchor));
		m_pDisable->setAnchorPoint(Vec2(anchor, anchor));
		float nowWidth = 0;
		float nowHeight = 0;
        if(m_pNormal) {
            nowWidth=m_pNormal->getContentSize().width;
            nowHeight=m_pNormal->getContentSize().height;
            if(width!=0)  nowWidth=width;
            if(height!=0)  nowHeight=height;
            ((TDScale9*)m_pNormal)->setPreferredSize(Size(nowWidth, nowHeight));
            setContentSize(m_pNormal->getContentSize());
        }

        if(m_pDown) {
            nowWidth=m_pDown->getContentSize().width;
            nowHeight=m_pDown->getContentSize().height;
            if(width!=0)  nowWidth=width;
            if(height!=0)  nowHeight=height;
            ((TDScale9*)m_pDown)->setPreferredSize(Size(nowWidth, nowHeight));
        }
        
        if(m_pDisable) {
            nowWidth=m_pDisable->getContentSize().width;
            nowHeight=m_pDisable->getContentSize().height;
            if(width!=0)  nowWidth=width;
            if(height!=0)  nowHeight=height;
            ((TDScale9*)m_pDisable)->setPreferredSize(Size(nowWidth, nowHeight));
        }
        
    }
    
	if(m_pNormal) {
		addChild(m_pNormal);
	}
	if(m_pDown) {
		addChild(m_pDown);
	}
	if(m_pDisable) {
		addChild(m_pDisable);
	}
    
    if(m_pNormalLabel) {
       addChild(m_pNormalLabel);
        m_pNormalLabel->setPosition(Vec2((getContentSize().width - m_pNormalLabel->getContentSize().width) /2,
			(getContentSize().height - m_pNormalLabel->getContentSize().height) /2));
		m_pNormalLabel->setPosition(Vec2(getContentSize().width /2,
			getContentSize().height / 2));
    }
    if(m_pDownLabel){
        addChild(m_pDownLabel);
		m_pDownLabel->setPosition(Vec2((getContentSize().width - m_pDownLabel->getContentSize().width) /2,
			(getContentSize().height - m_pDownLabel->getContentSize().height) /2));
		m_pDownLabel->setPosition(Vec2(getContentSize().width /2,
			getContentSize().height /2));
    }
    if(m_pDisableLabel){
        addChild(m_pDisableLabel);
		m_pDisableLabel->setPosition(Vec2((getContentSize().width - m_pDisableLabel->getContentSize().width) /2,
			(getContentSize().height - m_pDisableLabel->getContentSize().height) /2));
		m_pDisableLabel->setPosition(Vec2(getContentSize().width /2,
			getContentSize().height /2));
    }
    
    
    
    unselected();
}

void TDButton::setTarget(Ref*   obj,SEL_MenuHandler selector){
    
    m_pListener=obj;
    m_pfnSelector=selector;
}


