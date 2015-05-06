#ifndef _UI_BASE_H_
#define _UI_BASE_H_

#include "UIBase.h"

class TDTip;
class TDPanel;

struct TuiEvent{
public:
    virtual bool procTuiEvent(const string& event, TDPanel* target) = 0;
};

class TDButton;
class TDPage;
class TDScale9;
class TDTab;
class TDImage;
class TDScrollPanel;
class TDCount;
class TDBar;
class TDInput;
class TDCheckBox;
class TDRadio;
class TDAccordion;
class TDRichText;

class TDPanel : public Node, public TuiEvent, public BaseEvent
{
public:
    TDPanel();
	virtual ~TDPanel();

    virtual bool init();

	void initConf(xml_node<> * pRoot, Node* parent = NULL);
    void loadConf(const string&, Node* parent = NULL);
    void parseConf(xml_node<> * pItem);
    TDPanel* getUI(const string& );
	virtual void initSizeConf(xml_node<> * pItem);
    virtual void initWidthConf(xml_node<> * pItem);
    virtual bool procTuiEvent(const string&,TDPanel*);

	virtual void selected();
	virtual void unselected();
	virtual void onPreSelect();
    
    virtual void onCreateComplete();
    virtual void everyLoad();
    virtual void onEnter();
    virtual void onExit();

	void setLeft(float n);
	void setRight(float n);
	void setTop(float n);
	void setBottom(float n);
	void setHorizontalCenter(float n);
	void setVerticalCenter(float n);

	virtual void setX(float x);
	virtual void setY(float y);

	virtual void updateGame(float dt = 0.0f);
	virtual void update(float fDelta = 0.0f);

	unsigned int getObjectId();
	unsigned int getLuaRefId();
    
	Node* getItemByPos(float nX, float nY);
	void addItem(TDPanel*);
	void addChildItem(TDPanel*);
	void removeItem(TDPanel*);
	void registerItem();

	void loadProp(xml_node<> * pItem);
	virtual void updateDisplayedOpacity(GLubyte parentOpacity);

    virtual  void clearItems();
    __Array* getItems(){return  gTouchItems;}
    Node* getSelectedItem(){return  m_pSelectedItem;}
    int getSelectedIndex();
    void setSelecetIndex(int idex);
    void setSelecetItem(Node* node);
    void clearSelect();
    
    DEV_PROPERTY(bool, m_bTouchEnable, TouchEnable);
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *touch, Event *pEvent);
    virtual void registerWithTouchDispatcher();
	virtual void unregisterWithTouchDispatcher();
    
	virtual void setTarget(Ref *rec, SEL_MenuHandler selector);
    virtual void setListner(unsigned int id, string func);
    
    TDInput* getInput(const char*);
    TDScrollPanel* getScrollPanel(const char*);
    TDButton* getButton( const char*);
    TDImage* getImage(const char*);
    TDPage* getPage(const char*);
    TDScale9* getScale9(const char*);
    TDTab* getTab(const char*);
    TDPanel* getPanel(const char*);
    TDBar* getBar(const char*);
    
    TDCheckBox* getCheckBox(const char*);
    TDAccordion* getAccordion(const char*);

	TDRichText* getRichText(const char* name);
    
    bool hasLoadConf;
    bool hasInitMask;
	virtual void onSelectItem(Ref*);
	virtual void onUnSelectItem(Node*);
    
	static void setStaticTarget(Ref *rec, SEL_MenuHandler selector);
	map<string,TDPanel*> gUIs;
public:
	string confPath;
	string tTag;
	string tName;
	string tPath;
	string tEvent;
	
protected:
	GridBase *m_pGrid;                ///< a grid

    static  Ref*     m_pStaticListener;
    static  SEL_MenuHandler  m_pStaticfnSelector;

    Ref*       m_pListener;
    SEL_MenuHandler    m_pfnSelector;
    unsigned int m_uListener;
    string func;
    Node* m_pSelectedItem;
    Point touchStartPos; 
    Point touchMovePos;
	__Array* gTouchItems;
	EventListener* _touchListener;
    
};

#endif
