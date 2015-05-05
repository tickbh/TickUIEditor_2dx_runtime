#include "TDImage.h" 

static const char* defaultImage = "Images/Sprite.png";

TDImage::TDImage(){
    m_pItem=NULL;
}

TDImage* TDImage::create(xml_node<> * pItem){
	TDImage*  ret = UIBase::create<TDImage>();
    ret->initWidthConf(pItem);
    return ret;
}

void TDImage::setSource(const char* path, float customWidth, float customHeight){
	SpriteFrame* frame = UIUtils::getInstance()->spriteFrameByName(path);
#ifdef ENABLE_DEFAULT_PNG
	if (frame == nullptr) {
		frame = UIUtils::getInstance()->spriteFrameByName(defaultImage);
	}
#endif
	if (!frame) {
		if(m_pItem != NULL) {
			m_pItem->setVisible(false);
		}
        return;
    }
    if(m_pItem==NULL){
		m_pItem = Sprite::createWithSpriteFrame(frame);
        m_pItem->setCascadeOpacityEnabled(true);
        addChild(m_pItem);
    }else{
		m_pItem->setSpriteFrame(frame);
		m_pItem->setVisible(true);
    }
	m_pItem->setAnchorPoint(Vec2(0.5f, 0.5f));
	float width=m_pItem->getContentSize().width;
	if(customWidth > 0) {
		m_pItem->setScaleX(customWidth * 1.0f / width);
		width = customWidth;
	}
	m_pItem->setPositionX(width/2);
	float height = m_pItem->getContentSize().height;
	if(customHeight > 0) {
		m_pItem->setScaleY(customHeight * 1.0f / height);
		height = customHeight;
	}
	m_pItem->setPositionY(-height/2);
    setContentSize(Size(width, height));
}

void TDImage::initWidthConf(xml_node<> * pItem){
    string path;
    readAttrString(pItem, "Image", path);
	Size size=readContainSize(pItem, getParent());
    setSource(path.c_str(), size.width, size.height);
    
}