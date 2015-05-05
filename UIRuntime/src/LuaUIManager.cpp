#include "LuaUIManager.h"

extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};
#include "tolua_fix.h"

#include "TDWin.h"
#include "TDUI.h"
#include "rapidxml/rapidxml_print.hpp"
#include "CCLuaEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

static LuaUIManager* s_pSharedCCBManager = NULL;
LuaUIManager* LuaUIManager::instance()
{
    if (!s_pSharedCCBManager)
    {
        s_pSharedCCBManager = new LuaUIManager();
    }

    return s_pSharedCCBManager;
}

LuaUIManager::LuaUIManager()
{

}

LuaUIManager::~LuaUIManager()
{
    removeAllLuaObject();
}

TDPanel* LuaUIManager::createWindow( const char* mxmlPath, cocos2d::Node* parent /*= NULL*/)
{
	TDPanel* panel = UIBase::create<TDPanel>();
    panel->loadConf(mxmlPath, parent);
    return panel; 
}

void LuaUIManager::createWindow( TDPanel* panel, const char* mxmlPath, cocos2d::Node* parent /*= NULL*/ )
{
    //string path = string("normal/src/") + mxmlPath;
    panel->loadConf(mxmlPath, parent);
	if(panel->getPositionX() > 0) {
		parent = NULL;
	}
	cocos2d::log("mxml is %s, x = %d, y = %d", mxmlPath, panel->getPosition().x, panel->getPosition().y);
}

TDPanel* LuaUIManager::getPanelItem(const char* name)
{
	lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
    lua_getglobal(L, "get_panel_by_lua");
    lua_pushstring(L, name);
    //pLuaEngine->pushCCObject(dynamic_cast<CCcocos2d::Node*>(panel), "CCcocos2d::Node");
    lua_call(L, 1, 1);
    cocos2d::Node* node = ((cocos2d::Node*)  tolua_tousertype(L,-1,0));
    lua_pop(L, 1);
	return dynamic_cast<TDPanel*>(node);
}




bool LuaUIManager::onAssignEvent( cocos2d::Ref* pSender, const char* event, cocos2d::Ref* target)
{
    if(strlen(event) == 0) {
        return false;
    }
    // 取得该发送者所对应的 selectorName 和脚本处理函数
    unsigned int uID = pSender->_ID;
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
    lua_getglobal(L, "on_dispatch_event");
    lua_pushnumber(L, uID);
    // 压入第一个参数：pSender
    pLuaEngine->pushObject(target, "CCObject");
    lua_pushstring(pLuaEngine->getLuaState(), event);
	bool controled = pLuaEngine->executeFunction(3) != 0;
	return controled;
}

bool LuaUIManager::selected( unsigned int id )
{
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
    lua_getglobal(L, "selected_panel");
    lua_pushnumber(L, id);
	bool controled = pLuaEngine->executeFunction(1) != 0;
    return controled;
}

bool LuaUIManager::unselected( unsigned int id )
{
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
    lua_getglobal(L, "un_selected_panel");
    lua_pushnumber(L, id);
	bool controled = pLuaEngine->executeFunction(1) != 0;
    return controled;
}

void LuaUIManager::onCreateComplete(unsigned int id)
{
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
    lua_getglobal(L, "on_create_complete");
    lua_pushnumber(L, id);
    pLuaEngine->executeFunction(1);
}

void LuaUIManager::everyLoad(unsigned int id)
{
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
    lua_getglobal(L, "every_load");
    lua_pushnumber(L, id);
    pLuaEngine->executeFunction(1);
}


void LuaUIManager::onUpdateGame(unsigned int id)
{
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
    lua_getglobal(L, "on_update_game");
    lua_pushnumber(L, id);
    pLuaEngine->executeFunction(1);
}

void LuaUIManager::onPanelClicked( cocos2d::Ref * pSender, unsigned int uId, const char* func )
{
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
    lua_getglobal(L, "on_panel_clicked");
    lua_pushinteger(L, uId);
    lua_pushstring(L, func);
    pLuaEngine->pushObject(pSender, "CCObject");
    pLuaEngine->executeFunction(3);
}

void LuaUIManager::removeAllLuaObject()
{
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
    lua_getglobal(L, "destruct_all");
    pLuaEngine->executeFunction(1);
}

TDPanel* LuaUIManager::createPageBar( TDPage* page)
{
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
	lua_getglobal(L, "create_page_bar");
	pLuaEngine->pushObject(page, "TDPage");
	lua_call(L, 1, 1);
	TDPanel* panel = ((TDPanel*)  tolua_tousertype(L,-1,0));
	lua_pop(L, 1);
	return panel;
}

void LuaUIManager::pageChanged( TDPanel* barContainer, int currenTDPage )
{
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
	lua_getglobal(L, "page_changed");
	pLuaEngine->pushObject(barContainer, "TDPanel");
	lua_pushinteger(L, currenTDPage);
	pLuaEngine->executeFunction(2);
}

void LuaUIManager::changePageNum( TDPage* page, TDPanel* barContainer, int currenTDPageNum )
{
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
	lua_getglobal(L, "page_changed");
	pLuaEngine->pushObject(page, "TDPage");
	pLuaEngine->pushObject(barContainer, "TDPanel");
	lua_pushinteger(L, currenTDPageNum);
	pLuaEngine->executeFunction(2);
}

void LuaUIManager::updateLuaEvent()
{
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
	lua_getglobal(L, "update_lua_event");
	pLuaEngine->executeFunction(0);
}

void LuaUIManager::lockThread()
{
	_mutex.lock();
}

void LuaUIManager::unlockThread()
{
	_mutex.unlock();
}

void LuaUIManager::onUpdateAll()
{
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
	lua_getglobal(L, "on_update_all");
	pLuaEngine->executeFunction(0);
}

void LuaUIManager::removeObjectId( unsigned int id )
{
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
	lua_getglobal(L, "call_remove_object");
	lua_pushinteger(L, id);
	pLuaEngine->executeFunction(1);
}


void LuaUIManager::initWidthConfByLua(TDPanel* item, xml_node<> * pItem)
{
	auto iter = _confList.find(item->tName);
	if (iter == _confList.end()) {
		return;
	}
	std::string text;
	rapidxml::print(std::back_inserter(text), *pItem, 0);
	cocos2d::LuaStack* pLuaEngine = LuaEngine::getInstance()->getLuaStack();
	lua_State* L = pLuaEngine->getLuaState();
	lua_getglobal(L, "init_width_conf");
	lua_pushinteger(L, item->getObjectId());
	lua_pushstring(L, text.c_str());
	pLuaEngine->executeFunction(2);
}

void LuaUIManager::registerParseConf(std::string name)
{
	_confList.insert(name);
}



