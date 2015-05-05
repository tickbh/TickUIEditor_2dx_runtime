#ifndef _UI_TD_CHECKBOX_H_
#define _UI_TD_CHECKBOX_H_

#include "TDMaskPanel.h"
#include "TDScale9.h"

class TDCheckBox :public TDPanel{
public:
    TDCheckBox();
    ~TDCheckBox(); 
    
    
    virtual void selected();
    virtual void unselected();
    static TDCheckBox* create(xml_node<> * pItem);
    virtual  void initWidthConf(xml_node<> * pItem);
    
    bool isSelected();
    void setSelected(bool value);
protected:
    bool m_bSelected;

    TDScale9* m_pBg;
    Sprite* m_pIcon;
};
#endif
