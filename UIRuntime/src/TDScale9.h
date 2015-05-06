#ifndef _UI_TD_SCALE9_H_
#define _UI_TD_SCALE9_H_

#include "TDBase.h"

class TDScale9 : public TDPanel
{
public:

    TDScale9();
    virtual ~TDScale9();
	virtual bool init();

	virtual void  initWidthConf(xml_node<> * pItem);

	static TDScale9* createWithSpriteFrameName(const std::string& spriteFrameName);
	static TDScale9* create(const std::string& file);

	void setPreferredSize(const Size& size);
	virtual void onEnter();

private:
	ui::Scale9Sprite* _scale9Sprite;
};
 

#endif // __TScale9_H__
