
#include "TDScale9.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteFrameCache.h"
#include "base/CCVector.h"
#include "base/CCDirector.h"

static const char* defaultImage = "Images/ImageFile.png";

TDScale9::TDScale9()
{
	_scale9Sprite = ui::Scale9Sprite::create();
	this->addChild(_scale9Sprite);
}
    
TDScale9::~TDScale9()
{

}

bool TDScale9::init()
{
	return TDPanel::init();
}



void TDScale9::initWidthConf( xml_node<> * pItem )
{
	string path;
	readAttrString(pItem, "Image", path);
	SpriteFrame* frame = UIUtils::getInstance()->spriteFrameByName(path.c_str());
#ifdef ENABLE_DEFAULT_PNG
	if (frame == nullptr) {
		frame = UIUtils::getInstance()->spriteFrameByName(defaultImage);
	}
#endif
	if (frame == nullptr)
		return;
	_scale9Sprite->initWithSpriteFrame(frame);
	_scale9Sprite->setAnchorPoint(Vec2(0, 0));
	Size size = this->getContentSize();
	if(size.width == 0){
		size.width = _scale9Sprite->getContentSize().width;
	}
	if(size.height == 0){
		size.height = _scale9Sprite->getContentSize().height;
	} 
	this->setContentSize(size);
	TDPanel::initWidthConf(pItem);
}

TDScale9* TDScale9::createWithSpriteFrameName( const std::string& spriteFrameName )
{
	TDScale9* pReturn = new (std::nothrow) TDScale9();
	if ( pReturn && pReturn->_scale9Sprite->initWithSpriteFrame(UIUtils::getInstance()->spriteFrameByName(spriteFrameName.c_str())))
	{
		 pReturn->_scale9Sprite->setAnchorPoint(Vec2(0, 0));
		pReturn->setContentSize(pReturn->_scale9Sprite->getContentSize());
		pReturn->autorelease();
		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	log("Could not allocate TDScale9()");
	return NULL;
}

void TDScale9::setPreferredSize( const Size& size )
{
	this->setContentSize(size);
	this->_scale9Sprite->setPreferredSize(size);
}

TDScale9* TDScale9::create( const std::string& file )
{
	TDScale9* pReturn = new (std::nothrow) TDScale9();
	if ( pReturn && pReturn->_scale9Sprite->initWithFile(file) )
	{
		pReturn->_scale9Sprite->setAnchorPoint(Vec2(0, 0));
		pReturn->setContentSize(pReturn->_scale9Sprite->getContentSize());
		pReturn->autorelease();
		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	return NULL;
}

void TDScale9::onEnter()
{
	CCNode::onEnter();
	cocos2d::log("TDScale9::onEnter");
}
