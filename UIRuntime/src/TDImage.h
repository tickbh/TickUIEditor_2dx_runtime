#ifndef _UI_TD_IMAGE_H_
#define _UI_TD_IMAGE_H_

#include "TDBase.h"

using namespace rapidxml;

class TDImage:public TDPanel{
public:
    TDImage();
    
    static TDImage*  create(xml_node<> * pItem);
    
    virtual  void  initWidthConf(xml_node<> * pItem);
   
	void setSource(const char* path, float customWidth = 0, float customHeight = 0);
protected:
    Sprite* m_pItem;
};
#endif
