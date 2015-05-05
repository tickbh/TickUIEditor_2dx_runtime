#include "TDButton.h"
#include "TDScale9.h"
#include "TDUI.h"

static const char* disableImg = "Images/Button_Disable.png";
static const char* normalImg = "Images/Button_Normal.png";
static const char* selectImg = "Images/Button_Select.png";

TDButton::TDButton()
: m_pNormalBg(nullptr)
, m_pSelectBg(nullptr)
, m_pDisableBg(nullptr)
, m_pNormalLabel(nullptr)
, m_pSelectLabel(nullptr)
, m_pDisableLabel(nullptr)
, m_pNormalText(nullptr)
, m_pSelectText(nullptr)
, m_pDisableText(nullptr)
, m_pListener(nullptr)
, m_pfnSelector(nullptr)
{
    m_bEnable=true;
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
            m_pDisableBg->setVisible(true);
			if (getPreDisableNode())
				getPreDisableNode()->setVisible(true);
        }
    }
}

void TDButton::clear(){
    if(m_pNormalBg)
       m_pNormalBg->setVisible(false); 
    if(m_pSelectBg)
        m_pSelectBg->setVisible(false);
    if(m_pDisableBg)
        m_pDisableBg->setVisible(false);
    
    if(m_pNormalLabel)
        m_pNormalLabel->setVisible(false);
    if(m_pSelectLabel)
        m_pSelectLabel->setVisible(false);
    
    if(m_pDisableLabel)
        m_pDisableLabel->setVisible(false);
}
void TDButton::selected(){
    if(!m_bEnable)
        return;
    clear();
    if(m_pSelectBg)
		m_pSelectBg->setVisible(true);
	if (getPreSelectNode())
		getPreSelectNode()->setVisible(true);
    if (m_pListener && m_pfnSelector)
        (m_pListener->*m_pfnSelector)(this);
}

void TDButton::unselected(){
    if(!m_bEnable){
        return;
    }
    clear();
    if(m_pNormalBg) m_pNormalBg->setVisible(true);
	if (getPreNormalNode())
		getPreNormalNode()->setVisible(true);
    
}
TDButton* TDButton::create(xml_node<> * pItem){
	TDButton*  ret = UIBase::create<TDButton>();
    ret->initWidthConf(pItem);
    return ret;
}

void TDButton::setLabel(const char* path){
    if(UIUtils::getInstance()->spriteFrameByName(path)){
        if(m_pNormalLabel==nullptr){
            m_pNormalLabel=Sprite::createWithSpriteFrameName(path);
            addChild(m_pNormalLabel);
        }else{
             m_pNormalLabel->setSpriteFrame( UIUtils::getInstance()->spriteFrameByName(path)); 
        }
        
		m_pNormalLabel->setPosition(Vec2(getContentSize().width / 2, -getContentSize().height / 2));
        
        
        if(m_pSelectLabel==nullptr){
            m_pSelectLabel=Sprite::createWithSpriteFrameName(path);
            addChild(m_pSelectLabel);
        }else{
			m_pSelectLabel->setSpriteFrame(UIUtils::getInstance()->spriteFrameByName(path));
        }
		m_pSelectLabel->setPosition(Vec2(getContentSize().width / 2, -getContentSize().height / 2));
    }
    
}

void TDButton::initWidthConf(xml_node<> * pItem){
	TDPanel::initWidthConf(pItem);
    string normalBg, selectBg,disableBg;
    string normalLabel, selectLabel,disableLabel;
	string normalText, selectText, disableText;
	bool isScale9 = true;
	int fontSize = readAttrInt(pItem, "FontSize");
	if (fontSize == 0) {
		fontSize = 18;
	}
	if (existAttr(pItem, "IsScale9")) {
		isScale9 = readAttrBool(pItem, "IsScale9");
	}
	
    readAttrString(pItem, "normalLabel", normalLabel);
    readAttrString(pItem, "selectLabel", selectLabel);
    readAttrString(pItem, "disableLabel", disableLabel);
     
    readAttrString(pItem, "normalBg", normalBg);
    readAttrString(pItem, "selectBg", selectBg);
    readAttrString(pItem, "disableBg", disableBg);

	readAttrString(pItem, "mormalText", normalText);
	readAttrString(pItem, "selectText", selectText);
	readAttrString(pItem, "disableText", disableText);
    
    readAttrString(pItem, "linkPanel", linkPanel);
   
    
    if(disableBg.size()==0){
        disableBg=selectBg;
    }
    
    if(disableLabel.size()==0){
        disableLabel=selectLabel;
    }
   

	float anchor = 0.5f;
    if(UIUtils::getInstance()->spriteFrameByName(normalLabel.c_str())){ 
        m_pNormalLabel=Sprite::createWithSpriteFrameName(normalLabel.c_str());
		m_pNormalLabel->setAnchorPoint(Vec2(anchor, anchor));
    }
    
    if(UIUtils::getInstance()->spriteFrameByName(selectLabel.c_str())){
        m_pSelectLabel=Sprite::createWithSpriteFrameName(selectLabel.c_str());
		m_pSelectLabel->setAnchorPoint(Vec2(anchor, anchor));
    }
    if(UIUtils::getInstance()->spriteFrameByName(disableLabel.c_str())){
        m_pDisableLabel=Sprite::createWithSpriteFrameName(disableLabel.c_str());
		m_pDisableLabel->setAnchorPoint(Vec2(anchor, anchor));
    }
	Size contentSize = this->getContentSize();
    anchor = 0;
    if(!isScale9){
        m_pNormalBg=Sprite::createWithSpriteFrame(UIUtils::getInstance()->spriteFrameByName(normalBg.c_str()));
        m_pSelectBg=Sprite::createWithSpriteFrame(UIUtils::getInstance()->spriteFrameByName(selectBg.c_str()));
        m_pDisableBg=Sprite::createWithSpriteFrame(UIUtils::getInstance()->spriteFrameByName(disableBg.c_str()));
        m_pNormalBg->setAnchorPoint(Vec2(anchor, anchor));
		m_pSelectBg->setAnchorPoint(Vec2(anchor, anchor));
		m_pDisableBg->setAnchorPoint(Vec2(anchor, anchor));
        if (m_pNormalBg && contentSize.equals(Size::ZERO)) { 
            setContentSize(m_pNormalBg->getContentSize());
        }
    }else{
        m_pNormalBg=TDScale9::create(normalBg.c_str());
        m_pSelectBg=TDScale9::create(selectBg.c_str());
        m_pDisableBg=TDScale9::create(disableBg.c_str());
		m_pNormalBg->setAnchorPoint(Vec2(anchor, anchor));
		m_pSelectBg->setAnchorPoint(Vec2(anchor, anchor));
		m_pDisableBg->setAnchorPoint(Vec2(anchor, anchor));
		float nowWidth = 0;
		float nowHeight = 0;
        if(m_pNormalBg) {
            nowWidth=m_pNormalBg->getContentSize().width;
            nowHeight=m_pNormalBg->getContentSize().height;
			if (contentSize.width != 0)  nowWidth = contentSize.width;
			if (contentSize.height != 0)  nowHeight = contentSize.height;
            ((TDScale9*)m_pNormalBg)->setPreferredSize(Size(nowWidth, nowHeight));
            setContentSize(m_pNormalBg->getContentSize());
        }

        if(m_pSelectBg) {
            nowWidth=m_pSelectBg->getContentSize().width;
            nowHeight=m_pSelectBg->getContentSize().height;
			if (contentSize.width != 0)  nowWidth = contentSize.width;
			if (contentSize.height != 0)  nowHeight = contentSize.height;
            ((TDScale9*)m_pSelectBg)->setPreferredSize(Size(nowWidth, nowHeight));
        }
        
        if(m_pDisableBg) {
            nowWidth=m_pDisableBg->getContentSize().width;
            nowHeight=m_pDisableBg->getContentSize().height;
			if (contentSize.width != 0)  nowWidth = contentSize.width;
			if (contentSize.height != 0)  nowHeight = contentSize.height;
            ((TDScale9*)m_pDisableBg)->setPreferredSize(Size(nowWidth, nowHeight));
        }
    }

	contentSize = this->getContentSize();
	m_pDisableText = LabelTTF::create(disableText, "", fontSize, contentSize, TextHAlignment::CENTER, TextVAlignment::CENTER);
	m_pNormalText = LabelTTF::create(normalText, "", fontSize, contentSize, TextHAlignment::CENTER, TextVAlignment::CENTER);
	m_pSelectText = LabelTTF::create(selectText, "", fontSize, contentSize, TextHAlignment::CENTER, TextVAlignment::CENTER);

	if(m_pNormalBg) {
		addChild(m_pNormalBg);
	}
	if(m_pSelectBg) {
		addChild(m_pSelectBg);
	}
	if(m_pDisableBg) {
		addChild(m_pDisableBg);
	}

	if (m_pDisableText) {
		addChild(m_pDisableText);
		m_pDisableText->setPosition(Vec2(getContentSize().width / 2,
			getContentSize().height / 2));
	}
	if (m_pNormalText) {
		addChild(m_pNormalText);
		m_pNormalText->setPosition(Vec2(getContentSize().width / 2,
			getContentSize().height / 2));
	}
	if (m_pSelectText) {
		addChild(m_pSelectText);
		m_pSelectText->setPosition(Vec2(getContentSize().width / 2,
			getContentSize().height / 2));
	}
    
    if(m_pNormalLabel) {
       addChild(m_pNormalLabel);
        m_pNormalLabel->setPosition(Vec2((getContentSize().width - m_pNormalLabel->getContentSize().width) /2,
			(getContentSize().height - m_pNormalLabel->getContentSize().height) /2));
		m_pNormalLabel->setPosition(Vec2(getContentSize().width /2,
			getContentSize().height / 2));
    }
    if(m_pSelectLabel){
        addChild(m_pSelectLabel);
		m_pSelectLabel->setPosition(Vec2((getContentSize().width - m_pSelectLabel->getContentSize().width) /2,
			(getContentSize().height - m_pSelectLabel->getContentSize().height) /2));
		m_pSelectLabel->setPosition(Vec2(getContentSize().width /2,
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

void TDButton::setTarget(Ref* obj, SEL_MenuHandler selector){
    m_pListener=obj;
    m_pfnSelector=selector;
}


