#include "TDPanel.h"
#include "TDScale9.h"
#include "TDButton.h"
#include "TDImage.h"
#include "TDUI.h"
#include "TDRichText.h"
#include "TDInput.h"
#include "TDTab.h"
#include "TDBar.h"
#include "TDCheckBox.h"
#include "TDAccordion.h"
#include "TDPage.h"
#include "rapidxml/rapidxml_print.hpp"
#include "LuaUIManager.h"

void TDPanel::updateDisplayedOpacity(GLubyte parentOpacity)
{
	_displayedOpacity = (GLubyte)(_realOpacity * parentOpacity / 255.0);
	
    if (_cascadeOpacityEnabled)
    {
		for (auto item : _children) {
			if (item && item->isVisible())
			{
				item->setOpacity(_displayedOpacity);
			}
		}
    }
}


void TDPanel::loadProp( xml_node<> * pItem)
{
	readAttrString(pItem, "Tag", this->tTag);
	readAttrString(pItem, "Event", this->tEvent);
	int id = readAttrInt(pItem, "Id");
	if (id != 0) {
		this->setTag(id);
	}
}

void TDPanel::setHorizontalCenter(float n){
	if (_parent){
		setPositionX(_parent->getContentSize().width / 2 - getContentSize().width / 2 + n);
	}
}

void TDPanel::setVerticalCenter(float n){
    if(_parent){
		setPositionY(_parent->getContentSize().height / 2 + getContentSize().height / 2 - n);
    } 
}

void TDPanel::setLeft(float n){
    setPositionX(n);
}

void TDPanel::setRight(float n){
	if (_parent){
		setPositionX(_parent->getContentSize().width - getContentSize().width - n);
    }
}

void TDPanel::setTop(float n){
    //setPositionY(-n);
	if(_parent)
		setPositionY(_parent->getContentSize().height - this->getContentSize().height - n);

}

void TDPanel::setBottom(float n){
	if (_parent){
		setPositionY(-_parent->getContentSize().height + getContentSize().height + n);
		//setPositionY(n);
    }
}

void TDPanel::setX(float x){
    setPositionX(x);
}

void TDPanel::setY(float y){
	if (_parent){
		setPositionY(_parent->getContentSize().height - y);
    } else {
		setPositionY(y);
	}
}


void TDPanel::onSelected(){
#ifdef ENABLE_LUA
	bool control = LuaUIManager::instance()->selected(this->getObjectId());
	if (control) {
		return;
	}
#endif
}

void TDPanel::onPreSelect() {
    
}

void TDPanel::onEndSelect() {

}


unsigned int TDPanel::getObjectId()
{
    return this->_ID;
}

unsigned int TDPanel::getLuaRefId()
{
	return this->_luaID;
}

void TDPanel::updateGame( float dt /*= 0.0*/ )
{
#ifdef ENABLE_LUA
	LuaUIManager::instance()->onUpdateGame(this->getObjectId());
#endif
}

void TDPanel::update( float fDelta /*= 0.0f*/ )
{
#ifdef ENABLE_LUA
	LuaUIManager::instance()->onUpdateGame(this->getObjectId());
#endif
}



/***************************************************
 * TPanel
 **************************************************/

Ref*     TDPanel::m_pStaticListener=NULL;
SEL_MenuHandler  TDPanel::m_pStaticfnSelector=NULL;


void TDPanel::setStaticTarget(Ref *rec, SEL_MenuHandler selector){
    m_pStaticListener=rec;
    m_pStaticfnSelector=selector;
}

void TDPanel::initConf( xml_node<> * pRoot, Node* parent /*= NULL*/ )
{
	Size size=readContainSize(pRoot, parent == NULL ? getParent() : parent);
	if(size.width ==-1){
		size.width=0;
	} 
	if(size.height==-1){ 
		size.height=0;
	}
	setContentSize(size);
}

void TDPanel::loadConf(const string& path, Node* parent /*= NULL*/){
    if(hasLoadConf){
        return;
    }
    
    xml_document<>* doc= TDUI::instance()->getDoc(path);
    if(doc==NULL){ 
		string temp = FileUtils::getInstance()->fullPathForFilename(path.c_str());
		Data ret = FileUtils::getInstance()->getDataFromFile(temp);
		if (ret.isNull())
            return ;
		unsigned char* newData = new unsigned char[ret.getSize() + 1];
		memcpy(newData, ret.getBytes(), ret.getSize());
		newData[ret.getSize()] = '\0';
        doc=new xml_document<>();
        doc->parse<0>((char *)newData);
        TDUI::instance()->addDoc(path, doc,newData);
    }
    
    xml_node<> * pRoot = doc->first_node();
	if(!pRoot)
		return;
    
	initConf(pRoot, parent);
	this->setAnchorPoint(Vec2(0, 0));
	//child node
	xml_node<> * pItem = pRoot->first_node("Child");
	if (pItem) {
		parseConf(pItem->first_node());
	}
    hasLoadConf=true;
    onCreateComplete();

}

void TDPanel::initSizeConf(xml_node<> * pItem) {
	Size size = readContainSize(pItem, getParent());
	if (size.width < 0) size.width = getContentSize().width;
	if (size.height < 0) size.height = getContentSize().height;
	setContentSize(size);
}


void TDPanel::initWidthConf(xml_node<> * pItem){
    if(!pItem) return;

	xml_attribute<> * pNode = pItem->first_attribute("ScaleX");
	if (pNode) {
		setScaleX(readAttrFloat(pItem, "ScaleX"));
	}

	pNode = pItem->first_attribute("ScaleY");
	if (pNode) {
		setScaleY(readAttrFloat(pItem, "ScaleY"));
	}

	pNode = pItem->first_attribute("Scale");
	if (pNode) {
		setScale(readAttrFloat(pItem, "Scale"));
	}

	pNode = pItem->first_attribute("AnchorX");
	if (pNode) {
		setAnchorPoint(Vec2(readAttrFloat(pItem, "AnchorX"), getAnchorPoint().y));
	}

	pNode = pItem->first_attribute("AnchorY");
	if (pNode) {
		setAnchorPoint(Vec2(getAnchorPoint().x, 1 - readAttrFloat(pItem, "AnchorY")));
	}

	pNode = pItem->first_attribute("X");
	if (pNode) {
		setX(readAttrFloat(pItem, "X"));
	}
	pNode = pItem->first_attribute("Y");
	if (pNode) {
		setY(readAttrFloat(pItem, "Y"));
	}

	pNode = pItem->first_attribute("Right");
	if (pNode) {
		setRight(readAttrFloat(pItem, "Right"));
	}

	pNode = pItem->first_attribute("HorizontalCenter");
	if (pNode) {
		setHorizontalCenter(readAttrFloat(pItem, "HorizontalCenter"));
	}

	pNode = pItem->first_attribute("VerticalCenter");
	if (pNode) {
		setVerticalCenter(readAttrFloat(pItem, "VerticalCenter"));
	}

	pNode = pItem->first_attribute("Left");
	if (pNode) {
		setLeft(readAttrFloat(pItem, "Left"));
	}

	pNode = pItem->first_attribute("Top");
	if (pNode) {
		setTop(readAttrFloat(pItem, "Top"));
	}

	pNode = pItem->first_attribute("Bottom");
	if (pNode) {
		setBottom(readAttrFloat(pItem, "Bottom"));
	}
	pNode = pItem->first_attribute("Rotation");
	if (pNode) {
		setRotation(readAttrFloat(pItem, "Rotation"));
	}
	pNode = pItem->first_attribute("RotationY");
	if (pNode) {
		setRotationSkewY(readAttrFloat(pItem, "RotationY"));
	}
	pNode = pItem->first_attribute("RotationX");
	if (pNode) {
		setRotationSkewX(readAttrFloat(pItem, "RotationX"));
	}
    
	xml_node<> * pChild = pItem->first_node();
	if (pChild) {
		parseConf(pChild->first_node());
	}
    
    if(!hasLoadConf){ 
        onCreateComplete();
    }
}

void TDPanel::parseConf(xml_node<> * pItem){
    while (pItem) {
        TDPanel* item=  TDUI::instance()->createUI(pItem);
        if(item){
			if (item->tName == T_BUTTON_NAME || item->tName == T_CHECKBOX_NAME || item->tName == T_PAGE_NAME) {
                addChildItem(item); 
			} else if (item->tEvent.size() != 0) {
                addChildItem(item);
            }else{
                addChild(item);
            }
            string id=item->tTag;
            if(id.size()>0) {
				this->gUIs.insert(pair<string, TDPanel*>(id, item));
			}
			if (item->tName == "Panel" && item->confPath.size() != 0) {
				item->loadConf(item->confPath.c_str());
            }
			item->initSizeConf(pItem);
			item->initWidthConf(pItem);
#ifdef ENABLE_LUA
			LuaUIManager::instance()->initWidthConfByLua(item, pItem);
#endif
        }
        pItem=pItem->next_sibling();
        
    }
}

TDPanel* TDPanel::getUI(const string& key){
	auto iter = gUIs.find(key);
	if (iter == gUIs.end()){
        return nullptr;
    }
	return iter->second;
}

void TDPanel::onExit(){
    Node::onExit();
	_eventDispatcher->removeEventListener(_touchListener);
}

void  TDPanel::onCreateComplete(){
    everyLoad();
#ifdef ENABLE_LUA
    LuaUIManager::instance()->onCreateComplete(getObjectId());
#endif
}

void TDPanel::everyLoad()
{
#ifdef ENABLE_LUA
	LuaUIManager::instance()->everyLoad(getObjectId()); 
#endif
}

bool TDPanel::init(){
	if (!Node::init()) {
		return false;
	}
	setAnchorPoint(Vec2(0.5, 0.5));
	setCascadeOpacityEnabled(true);
    return true;
}

void TDPanel::registerWithTouchDispatcher()
{
	if (_touchListener != nullptr) {
		_eventDispatcher->removeEventListener(_touchListener);
		_touchListener = nullptr;
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(TDPanel::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TDPanel::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TDPanel::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(TDPanel::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_touchListener = listener;
}

void TDPanel::unregisterWithTouchDispatcher()
{
	if (_touchListener != nullptr) {
		_eventDispatcher->removeEventListener(_touchListener);
		_touchListener = nullptr;
	}
}


void TDPanel::onEnter(){
    Node::onEnter();
    if(hasLoadConf) {
        everyLoad();
    }
}


TDPanel::TDPanel(){
    gTouchItems=__Array::create();
	gTouchItems->retain();
    m_pSelectedItem=NULL;
    m_pListener=NULL;
    m_pfnSelector=NULL;
    hasLoadConf=false;
    hasInitMask=false;
    m_bTouchEnable=true;
    m_uListener = 0;
	m_pGrid = NULL;
	_scissorRestored = false;
}

TDPanel::~TDPanel(){
    gUIs.clear();
	gTouchItems->removeAllObjects();
    CC_SAFE_RELEASE_NULL(gTouchItems);
#ifdef ENABLE_LUA
	LuaUIManager::instance()->removeObjectId(this->getObjectId());
#endif
}


void TDPanel::clearItems(){
    clearSelect();
    gTouchItems->removeAllObjects();
}

void TDPanel::addItem(TDPanel* item){
	if (gTouchItems->containsObject(item)) {
		return;
	}
    gTouchItems->addObject(item);
}

void TDPanel::addChildItem(TDPanel* item){
    addItem(item);
    addChild(item);
    
}

int TDPanel::getSelectedIndex(){
    if(m_pSelectedItem==NULL){
        return -1;
    } 
	return gTouchItems->getIndexOfObject(m_pSelectedItem);
}



void TDPanel::clearSelect(){
    if(m_pSelectedItem){
        onUnSelectItem(m_pSelectedItem);
    }
}


void TDPanel::setSelecetItem(Node* node){
    if(!node) return;
    if(m_pSelectedItem){
        onUnSelectItem(m_pSelectedItem);
    }
    
    onSelectItem(node);
   
}

void TDPanel::setSelecetIndex(int index){
    if(m_pSelectedItem){
        onUnSelectItem(m_pSelectedItem);
    }
    
    if(index==-1){
        index=0;
    }
    
    if((ssize_t)index>=gTouchItems->count()){
        return;
    }
	Ref* obj = gTouchItems->getObjectAtIndex(index);
    if(obj){
        onSelectItem((Node*)obj);
    }
}

void TDPanel::setTarget(Ref *rec, SEL_MenuHandler selector)
{
    m_pListener = rec;
    m_pfnSelector = selector;
}

bool TDPanel::onTouchBegan(Touch *pTouch, Event *pEvent){
    if(!m_bTouchEnable){
        return false;
    }
    touchStartPos.setPoint(pTouch->getLocation().x,pTouch->getLocation().y);
    Node* parent=this;
    while(parent){
        if(!parent->isVisible() || !parent->isRunning()){
            return false;
        }
        parent=parent->getParent(); 
    }
    
    if(gTouchItems->count()<=0){
        return false;
    }
    
	Node* item = (Node*)gTouchItems->getObjectAtIndex(0);
    if(item==NULL || item->getParent()==NULL){
        return false;
    }
    
    Point targetPos=getPosInTarget(pTouch->getLocation(),item->getParent());
    Node* node= getItemByPos(targetPos.x,targetPos.y);
    if(node==NULL){
        return false;
    }
	TDPanel* panel = dynamic_cast<TDPanel*>(node);
	if (panel) {
        if(m_pSelectedItem){
            onUnSelectItem(m_pSelectedItem);
        }
		onPreSelectItem(panel);
    }
    return true;
}


void TDPanel::onTouchMoved(Touch *pTouch, Event *pEvent) {
	touchMovePos.setPoint(pTouch->getLocation().x, pTouch->getLocation().y);
	if (m_pSelectedItem) {
		Node* item = (Node*)gTouchItems->getObjectAtIndex(0);
		if (item == NULL) {
			return;
		}
		Point targetPos = getPosInTarget(pTouch->getLocation(), item->getParent());
		Node* node = getItemByPos(targetPos.x, targetPos.y);
		if (node == NULL || node != m_pSelectedItem) {
			onUnSelectItem(m_pSelectedItem);
		}
	}
}

void TDPanel::onTouchCancelled(Touch *touch, Event *pEvent) {
	onUnSelectItem(m_pSelectedItem);
}
void TDPanel::onTouchEnded(Touch *pTouch, Event *pEvent) {
	if (gTouchItems->count() <= 0) {
		return;
	}

	Node* item = (Node*)gTouchItems->getObjectAtIndex(0);
	if (item == NULL || item->getParent() == NULL) {
		return;
	}
	Point touchEndPos = (pTouch->getLocation());

	float distance = (touchEndPos.x - touchStartPos.x)*(touchEndPos.x - touchStartPos.x) + (touchEndPos.y - touchStartPos.y)*(touchEndPos.y - touchStartPos.y);
	if (sqrt(distance) < 20) {
		Point targetPos = getPosInTarget(pTouch->getLocation(), item->getParent());
		TDPanel* node = (TDPanel*)getItemByPos(targetPos.x, targetPos.y);
		if (node != NULL) {
			if (m_pSelectedItem && node != m_pSelectedItem) {
				onUnSelectItem(m_pSelectedItem);
			}
			if (node->tEvent.size() != 0) {
				procTuiEvent(node->tEvent, node);
			}
			if (m_pStaticListener&& m_pStaticfnSelector)
				(m_pStaticListener->*m_pStaticfnSelector)(node);
			onSelectItem(node);
		}
	}
	onEndSelectItem();
}

void TDPanel::removeItem(TDPanel* node){
    gTouchItems->removeObject(node);
}




Node* TDPanel::getItemByPos(float nX, float nY){
    Ref* obj;
    CCARRAY_FOREACH(gTouchItems, obj)
    {
        Node* pNode =  (Node*)(obj);
        if(pNode->isVisible()){
			Rect rect = getPanelRect(pNode);
			if (rect.containsPoint(Vec2(nX, nY))) {
				return pNode;
			}
        }
    }
    return NULL;
}


bool TDPanel::procTuiEvent(const string& event,TDPanel* target){
	bool success = false;
#ifdef ENABLE_LUA
	success = LuaUIManager::instance()->onAssignEvent(this, event.c_str(), target);
	if (success) {
		return success;
	}
#endif
	TDPanel* item = dynamic_cast<TDPanel*>(this->getParent());
	if (item) {
		success = item->procTuiEvent(event, target);
		return success;
	}
    return true;
}


void TDPanel::onPreSelectItem(Node* pNode) {
	m_pSelectedItem = pNode;
	TDPanel* tipContainer = dynamic_cast<TDPanel*>(pNode);
	if (tipContainer) {
		tipContainer->onPreSelect();
	}
}


void TDPanel::onSelectItem(Node* pNode) {
	m_pSelectedItem = pNode;
	if (m_pListener&& m_pfnSelector)
		(m_pListener->*m_pfnSelector)(m_pSelectedItem);

#ifdef ENABLE_LUA
	if (m_uListener && func.size() > 0) {
		LuaUIManager::instance()->onPanelClicked(this, m_uListener, func.c_str());
	}
#endif
	TDPanel* tipContainer = dynamic_cast<TDPanel*>(pNode);
	if (tipContainer) {
		tipContainer->onSelected();
	}
}

void TDPanel::onUnSelectItem(Node* pNode){
	TDPanel* tipContainer = dynamic_cast<TDPanel*>(pNode);
	if (tipContainer) {
		tipContainer->onEndSelect();
	}
    m_pSelectedItem=NULL;
}

void TDPanel::onEndSelectItem() {
	TDPanel* tipContainer = dynamic_cast<TDPanel*>(m_pSelectedItem);
	if (tipContainer) {
		tipContainer->onEndSelect();
	}
}

void TDPanel::setListner(unsigned int id, string func)
{
	m_uListener = id;
	this->func = func;
}


TDScrollPanel* TDPanel::getScrollPanel(const char* name){
	return dynamic_cast<TDScrollPanel*>(this->getUI(name));
}

TDButton* TDPanel::getButton(  const char* name){
	return dynamic_cast<TDButton*>(this->getUI(name));
}

TDImage* TDPanel::getImage(const char* name){
    
	return dynamic_cast<TDImage*>(this->getUI(name));
}
TDPage* TDPanel::getPage(const char* name){
    
	return dynamic_cast<TDPage*>(this->getUI(name));
}
TDScale9* TDPanel::getScale9(const char* name){
    
	return dynamic_cast<TDScale9*>(this->getUI(name));
}
TDTab* TDPanel::getTab(const char* name){
    
	return dynamic_cast<TDTab*>(this->getUI(name));
}
TDPanel* TDPanel::getPanel(const char* name){
    
	return dynamic_cast<TDPanel*>(this->getUI(name));
}

TDCheckBox* TDPanel::getCheckBox(const char* name){
	return dynamic_cast<TDCheckBox*>(this->getUI(name));
}

TDBar* TDPanel::getBar(const char* name){
	return dynamic_cast<TDBar*>(this->getUI(name));
}

TDInput*  TDPanel::getInput(const char* name){
	return dynamic_cast<TDInput*>(this->getUI(name));
}

TDAccordion* TDPanel::getAccordion(const char* name){
	return dynamic_cast<TDAccordion*>(this->getUI(name));
}

TDRichText* TDPanel::getRichText( const char* name )
{
	return dynamic_cast<TDRichText*>(this->getUI(name));
}

void TDPanel::registerItem()
{
	TDPanel* parent = dynamic_cast<TDPanel*>(this->getParent());
	if (parent) {
		parent->addItem(this);
	}
}

void TDPanel::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) {
	if (!isVisible()) {
		return;
	}
	if (isNeedScissor()) {
		_beforeVisitCmdScissor.init(_globalZOrder);
		_beforeVisitCmdScissor.func = CC_CALLBACK_0(TDPanel::beforeDraw, this);
		renderer->addCommand(&_beforeVisitCmdScissor);
	}

	Node::visit(renderer, parentTransform, parentFlags);
	if (isNeedScissor()) {
		_afterVisitCmdScissor.init(_globalZOrder);
		_afterVisitCmdScissor.func = CC_CALLBACK_0(TDPanel::afterDraw, this);
		renderer->addCommand(&_afterVisitCmdScissor);
	}
}

void TDPanel::afterDraw() {
	if (_scissorRestored) {//restore the parent's scissor rect
		auto glview = Director::getInstance()->getOpenGLView();
		glview->setScissorInPoints(_parentScissorRect.origin.x, _parentScissorRect.origin.y, _parentScissorRect.size.width, _parentScissorRect.size.height);
	} else {
		glDisable(GL_SCISSOR_TEST);
	}
}

void TDPanel::beforeDraw() {
	//if (this->getParent()) {
	//	Rect rect = getPanelRect(this);
	//	Size size = Director::getInstance()->getWinSize();
	//	Point worldPos = convertToWorldSpace(Vec2::ZERO);
	//	if (worldPos.x<-getContentSize().width ||
	//		worldPos.y<-getContentSize().height ||
	//		worldPos.x>size.width ||
	//		worldPos.y>size.height
	//		) {
	//		return;
	//	}
	//	Director::getInstance()->getOpenGLView()->setScissorInPoints(
	//		worldPos.x,
	//		worldPos.y,
	//		getContentSize().width * getScaleX(),
	//		getContentSize().height * getScaleY()
	//		);
	//}
	if (!this->getParent()) {
		return;
	}

	Rect frame = getPanelRect(this);
	auto glview = Director::getInstance()->getOpenGLView();

	if (glview->isScissorEnabled()) {
		_scissorRestored = true;
		_parentScissorRect = glview->getScissorRect();
		//set the intersection of _parentScissorRect and frame as the new scissor rect
		if (frame.intersectsRect(_parentScissorRect)) {
			float x = MAX(frame.origin.x, _parentScissorRect.origin.x);
			float y = MAX(frame.origin.y, _parentScissorRect.origin.y);
			float xx = MIN(frame.origin.x + frame.size.width, _parentScissorRect.origin.x + _parentScissorRect.size.width);
			float yy = MIN(frame.origin.y + frame.size.height, _parentScissorRect.origin.y + _parentScissorRect.size.height);
			glview->setScissorInPoints(x, y, xx - x, yy - y);
		}
	} else {
		_scissorRestored = false;
		glEnable(GL_SCISSOR_TEST);
		glview->setScissorInPoints(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
	}
}

bool TDPanel::isNeedScissor() {
	return this->tName == "Panel";
}
