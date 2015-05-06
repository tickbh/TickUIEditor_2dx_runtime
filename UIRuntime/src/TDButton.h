#ifndef _UI_TD_BUTTON_H_
#define _UI_TD_BUTTON_H_

 
#include "TDScale9.h"
#include "TDBase.h"

using namespace rapidxml;

class TDButton:public TDPanel{
    
public:
    TDButton();
    virtual ~TDButton();
    
    static TDButton* create(xml_node<> * pItem);
    virtual  void initWidthConf(xml_node<> * pItem);
    
    virtual void onSelected(); 
	virtual void onPreSelect();
	virtual void onEndSelect();

    virtual void onEnter();
    
    virtual void setVisible(bool visible);
 
	void setTarget(Ref* obj, SEL_MenuHandler selector);
    void setEnable(bool value);
    DEV_PROPERTY_READONLY(bool, m_bEnable, Enable)
    
    void setLabel(const char*);
    string linkPanel;
protected:
    
    Ref*       m_pListener;
    SEL_MenuHandler    m_pfnSelector;
    
    Node* m_pNormalBg;
    Node* m_pSelectBg;
    Node* m_pDisableBg;
    
    Sprite* m_pNormalLabel;
    Sprite* m_pSelectLabel;
    Sprite* m_pDisableLabel;

	LabelTTF* m_pNormalText;
	LabelTTF* m_pSelectText;
	LabelTTF* m_pDisableText;
    
    void clear();

private:
	Node* getPreNormalNode() {
		if (m_pNormalLabel) {
			return m_pNormalLabel;
		}
		return m_pNormalText;
	}

	Node* getPreSelectNode() {
		if (m_pSelectLabel) {
			return m_pSelectLabel;
		}
		return m_pSelectText;
	}

	Node* getPreDisableNode() {
		if (m_pDisableLabel) {
			return m_pDisableLabel;
		}
		return m_pDisableText;
	}
   
};

#endif
