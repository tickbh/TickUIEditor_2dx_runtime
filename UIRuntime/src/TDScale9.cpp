
#include "TDScale9.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteFrameCache.h"
#include "base/CCVector.h"
#include "base/CCDirector.h"

    
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
	readAttrString(pItem, "source", path);

	_scale9Sprite->initWithSpriteFrame(UIUtils::getInstance()->spriteFrameByName(path.c_str()));
	_scale9Sprite->setAnchorPoint(Vec2(0, 0));
	Size size=readContainSize(pItem,getParent());
	if(size.width ==-1){
		size.width=0;
	}
	if(size.height==-1){
		size.height=0;
	} 
	this->setPreferredSize(size);
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
