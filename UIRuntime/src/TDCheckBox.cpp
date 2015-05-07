#include "TDCheckBox.h"

static const char* DisableImgBg = "Images/CheckBox_Disable.png";
static const char* NormalImgBg = "Images/CheckBox_Normal.png";
static const char* SelectImgBg = "Images/CheckBox_Select.png";
static const char* NodeDisableImg = "Images/CheckBoxNode_Disable.png";
static const char* NodeNormalImg = "Images/CheckBoxNode_Normal.png";

TDCheckBox::TDCheckBox(){
    m_bSelected=true;
	m_eStatus = CheckStatus::Enable;
	m_pImgNormalBg = nullptr;
	m_pImgSelectBg = nullptr;
	m_pImgDisableBg = nullptr;
	m_pImgNodeDisable = nullptr;
	m_pImgNodeNormal = nullptr;
}

TDCheckBox::~TDCheckBox(){
    
}


bool TDCheckBox::isSelected(){
    return m_bSelected;
}


void TDCheckBox::onSelected(){
	if (!isEnable())
		return;
	setSelected(!m_bSelected);
}

void TDCheckBox::setSelected(bool value){
    m_bSelected=value;
	resetStatus();
}

TDCheckBox* TDCheckBox::create(xml_node<> * pItem){
	TDCheckBox*  ret = UIBase::create<TDCheckBox>();
    ret->initWidthConf(pItem);
    return ret;
}


void TDCheckBox::initWidthConf(xml_node<> * pItem){
    if(!pItem) return;

	Size conntentSize = this->getContentSize();
	SpriteFrame* frame = nullptr;
    string path;
    readAttrString(pItem, "ImgNormalBg", path);
	frame = UIUtils::getInstance()->spriteFrameByName(path.c_str());
#ifdef ENABLE_DEFAULT_UI
	if (frame == nullptr) {
		frame = UIUtils::getInstance()->spriteFrameByName(NormalImgBg);
	}
#endif
	if (frame) {
		m_pImgNormalBg = Sprite::createWithSpriteFrame(frame);
		m_pImgNormalBg->setAnchorPoint(Vec2::ZERO);
		addChild(m_pImgNormalBg);
	}

	readAttrString(pItem, "ImgSelectBg", path);
	frame = UIUtils::getInstance()->spriteFrameByName(path.c_str());
#ifdef ENABLE_DEFAULT_UI
	if (frame == nullptr) {
		frame = UIUtils::getInstance()->spriteFrameByName(SelectImgBg);
	}
#endif
	if (frame) {
		m_pImgSelectBg = Sprite::createWithSpriteFrame(frame);
		m_pImgSelectBg->setAnchorPoint(Vec2::ZERO);
		addChild(m_pImgSelectBg);
	}

	readAttrString(pItem, "ImgDisableBg", path);
	frame = UIUtils::getInstance()->spriteFrameByName(path.c_str());
#ifdef ENABLE_DEFAULT_UI
	if (frame == nullptr) {
		frame = UIUtils::getInstance()->spriteFrameByName(DisableImgBg);
	}
#endif
	if (frame) {
		m_pImgDisableBg = Sprite::createWithSpriteFrame(frame);
		m_pImgDisableBg->setAnchorPoint(Vec2::ZERO);
		addChild(m_pImgDisableBg);
	}

	readAttrString(pItem, "ImgNodeDisable", path);
	frame = UIUtils::getInstance()->spriteFrameByName(path.c_str());
#ifdef ENABLE_DEFAULT_UI
	if (frame == nullptr) {
		frame = UIUtils::getInstance()->spriteFrameByName(NodeDisableImg);
	}
#endif
	if (frame) {
		m_pImgNodeDisable = Sprite::createWithSpriteFrame(frame);
		setCenterPos(this, m_pImgNodeDisable);
		addChild(m_pImgNodeDisable);
	}

	readAttrString(pItem, "ImgNodeNormal", path);
	frame = UIUtils::getInstance()->spriteFrameByName(path.c_str());
#ifdef ENABLE_DEFAULT_UI
	if (frame == nullptr) {
		frame = UIUtils::getInstance()->spriteFrameByName(NodeNormalImg);
	}
#endif
	if (frame) {
		m_pImgNodeNormal = Sprite::createWithSpriteFrame(frame);
		setCenterPos(this, m_pImgNodeNormal);
		addChild(m_pImgNodeNormal);
	}
	std::string status;
	readAttrString(pItem, "Status", status);
	if (status == "Disable")
		m_eStatus = CheckStatus::Disable;

	if (existAttr(pItem, "IsCheck"))
		m_bSelected = readAttrBool(pItem, "IsCheck");


	TDPanel::initWidthConf(pItem);
}

void TDCheckBox::resetStatus() {
	if (m_pImgNormalBg) {
		m_pImgNormalBg->setVisible(m_eStatus == CheckStatus::Enable && !m_bSelected);
	}
	if (m_pImgSelectBg) {
		m_pImgSelectBg->setVisible(m_eStatus == CheckStatus::Enable && m_bSelected);
	}
	if (m_pImgDisableBg) {
		m_pImgDisableBg->setVisible(m_eStatus == CheckStatus::Disable);
	}
	if (m_pImgNodeDisable) {
		m_pImgNodeDisable->setVisible(m_eStatus == CheckStatus::Disable && m_bSelected);
	}
	if (m_pImgNodeNormal) {
		m_pImgNodeNormal->setVisible(m_eStatus == CheckStatus::Enable && m_bSelected);
	}
}

void TDCheckBox::setEnable(bool enable) {
	m_eStatus = enable ? CheckStatus::Enable : CheckStatus::Disable;
}

bool TDCheckBox::isEnable() {
	return m_eStatus == CheckStatus::Enable;
}
