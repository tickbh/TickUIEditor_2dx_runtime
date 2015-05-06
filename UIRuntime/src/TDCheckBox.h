#ifndef _UI_TD_CHECKBOX_H_
#define _UI_TD_CHECKBOX_H_

#include "TDMaskPanel.h"
#include "TDScale9.h"

enum class CheckStatus {
	Enable,
	Disable,
};

class TDCheckBox :public TDPanel{
public:
    TDCheckBox();
    ~TDCheckBox(); 
    
    
    virtual void onSelected();
    static TDCheckBox* create(xml_node<> * pItem);
    virtual  void initWidthConf(xml_node<> * pItem);
    
    bool isSelected();
    void setSelected(bool value);

	bool isEnable();
	void setEnable(bool enable);

	void resetStatus();
protected:
	CheckStatus m_eStatus;
    bool m_bSelected;

	Sprite* m_pImgNormalBg;
	Sprite* m_pImgSelectBg;
	Sprite* m_pImgDisableBg;
	Sprite* m_pImgNodeDisable;
	Sprite* m_pImgNodeNormal;


};
#endif
