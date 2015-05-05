#ifndef _UI_TD_SCENE_H_
#define _UI_TD_SCENE_H_

#include "TDBase.h"

USING_NS_CC;

class TDScene : public Scene
{
public:
	CREATE_FUNC(TDScene);
    virtual ~TDScene();
    TDScene();
	unsigned int getObjectId() { return this->_ID;  }
	unsigned int getLuaRefId()  { return this->_luaID; }
     
protected: 
    
	int m_nWinID;
     
};

#endif
