#include "UIUtils.h"

UIUtils::UIUtils(void)
{
}


UIUtils::~UIUtils(void)
{
}

static UIUtils* uiUtilsInstance = NULL;

UIUtils* UIUtils::getInstance()
{
    if(uiUtilsInstance == NULL) {
        uiUtilsInstance = new UIUtils();
    }
    return uiUtilsInstance;
}

SpriteFrame* UIUtils::spriteFrameByName( const char* cacheName )
{
    if(cacheName == NULL || strlen(cacheName) == 0) {
        return NULL;
    }
	SpriteFrame *frame = CCSpriteFrameCache::getInstance()->getSpriteFrameByName(cacheName);
    if(frame == NULL) {
        do 
        {
            string fullpath = CCFileUtils::getInstance()->fullPathForFilename(cacheName);
            if(fullpath.size() == 0) break;
            Sprite* sprite = Sprite::create(fullpath.c_str());
            if(sprite == NULL) break;
            frame = SpriteFrame::createWithTexture(sprite->getTexture(), sprite->getTextureRect());
            CCSpriteFrameCache::getInstance()->addSpriteFrame(frame, cacheName);
        } while (0);
    }
	frames.insert(cacheName);
    return frame;
}

void UIUtils::removeUnuseFrames()
{
	std::set<std::string>::iterator it = frames.begin();
	for( ; it != frames.end(); ) {
		SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName((*it).c_str());
		if(spriteFrame == NULL) {
			frames.erase(it++);
		} else if (spriteFrame && spriteFrame->getReferenceCount() == 1) {
			SpriteFrameCache::getInstance()->removeSpriteFrameByName((*it).c_str());
			frames.erase(it++);
        } else {
			++it;
		}
	}
}


