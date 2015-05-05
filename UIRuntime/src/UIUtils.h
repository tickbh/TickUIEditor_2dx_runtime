#ifndef _UI_UTILS_H_
#define _UI_UTILS_H_

#include "cocos2d.h"
#include <vector>
#include <string>

USING_NS_CC;
using namespace std;

class UIUtils
{
public:
    static UIUtils* getInstance();
    ~UIUtils(void);
    vector<string> getFiles(const char* zipFile, const char* floder);

    SpriteFrame* spriteFrameByName(const char* cacheName);
	void removeUnuseFrames();
private:
	std::set<std::string> frames;
    UIUtils(void);
};


#endif
