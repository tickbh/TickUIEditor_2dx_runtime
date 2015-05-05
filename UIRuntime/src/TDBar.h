#ifndef _UI_BAR_H_
#define _UI_BAR_H_

#include "UIBase.h"
#include "TDBase.h"
#include "TDMaskPanel.h"


class TDBar:public TDPanel{
    
public:
    virtual bool init();
    
    TDBar();
    virtual ~TDBar();
    
    void setSource(const char* source, Size contentSize = Size::ZERO);
    
    static TDBar* create(xml_node<> * pItem);
    virtual  void initWidthConf(xml_node<> * pItem);
    
	virtual void visit(Renderer *renderer, const Mat4& parentTransform, bool parentTransformUpdated);
    
	virtual void  afterDraw(Renderer *renderer, const Mat4& parentTransform, bool parentTransformUpdated);
    
	virtual void  beforeDraw(Renderer *renderer, const Mat4& parentTransform, bool parentTransformUpdated);
    void setNum(long lCur,long lMax);
    
    void setPer(float num);
    
protected:
    float m_nPer;
    Sprite* m_pItem;
};

    
#endif
