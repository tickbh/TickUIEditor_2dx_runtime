#ifndef _UI_TD_INPUT_H_
#define _UI_TD_INPUT_H_

#include "UIBase.h"
#include "TDPanel.h"

class TDInput :public TDPanel, public ui::EditBoxDelegate {
public:  
    TDInput();
    virtual bool init();
     
    static TDInput* create(xml_node<> * pItem);   
    virtual  void initWidthConf(xml_node<> * pItem);
    
	virtual void editBoxEditingDidBegin(ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(ui::EditBox* editBox);
	virtual void editBoxTextChanged(ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(ui::EditBox* editBox);
    const char* getString();
    void setString(const char*);
protected: 
	ui::EditBox* m_pEditor;
};


#endif
