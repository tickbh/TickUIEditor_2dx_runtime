#ifndef _FLASH_BUILDER_MANGER_H_
#define _FLASH_BUILDER_MANGER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>
#include <map>
#include <mutex>
#include <set>
#include "TDPanel.h"
#include "TDPage.h"

USING_NS_CC_EXT;

using namespace std;

class LuaUIManager
    : public Ref
{
public:
    static LuaUIManager* instance();

    LuaUIManager();
    virtual ~LuaUIManager();

    TDPanel* createWindow(const char* mxmlPath, cocos2d::Node* parent = NULL);
    void createWindow(TDPanel* panel, const char* mxmlPath, cocos2d::Node* parent = NULL);
    TDPanel* getPanelItem( const char* name );

	TDPanel* createPageBar(TDPage* page);
	void pageChanged(TDPanel* barContainer, int currenTDPage);
	void changePageNum(TDPage* page, TDPanel* barContainer, int currenTDPageNum);

    bool onAssignEvent(Ref* pSender, const char* event, Ref* target);
    void removeAllLuaObject();

    void onPanelClicked(Ref * pSender, unsigned int uId, const char* func); 

    bool selected(unsigned int id);
    bool unselected(unsigned int id);
    void onCreateComplete(unsigned int id);
    void everyLoad(unsigned int id);
    void onUpdateGame(unsigned int id);
	void removeObjectId(unsigned int id);
	void initWidthConfByLua(TDPanel* item, xml_node<> * pItem);
	void registerParseConf(std::string name);
	void onUpdateAll();
	void updateLuaEvent();

	void lockThread();
	void unlockThread();

private:
	std::mutex _mutex;
	std::set<std::string> _confList;
};

#endif