#include "TDBar.h"
#include "TDUI.h"

TDBar::TDBar(){ 
    m_nPer=100;
    m_pItem=NULL;
}
bool TDBar::init(){
    if(!TDPanel::init()){
        return false;
    }
    return true;
}


TDBar::~TDBar(){
   
}



void TDBar::setSource(const char* path){
    if(!UIUtils::getInstance()->spriteFrameByName(path)) {
        return;
    }

    if(m_pItem==NULL){
		m_pItem=Sprite::createWithSpriteFrameName(path );
        addChild(m_pItem);
    }else{
		m_pItem->setSpriteFrame(UIUtils::getInstance()->spriteFrameByName(path));
    }
    
    float width=m_pItem->getContentSize().width;
	float height = m_pItem->getContentSize().height;
    
    m_pItem->setPositionX(width/2);
    m_pItem->setPositionY(-height/2);
    
    
    setContentSize(Size(width, height));
}


TDBar* TDBar::create(xml_node<> * pItem){
    
	TDBar*  ret = UIBase::create<TDBar>();
    ret->initWidthConf(pItem);
    return ret;
}

void TDBar::initWidthConf(xml_node<> * pItem){
    string path;
    readAttrString(pItem, "source", path);
    
    float per= readAttrFloat(pItem, "per");
    setPer(per);

    m_pItem=Sprite::createWithSpriteFrame(UIUtils::getInstance()->spriteFrameByName(path.c_str()));
    if(m_pItem) {
		Size currentSize=readContainSize(pItem,getParent());
		if(currentSize.equals(Size::ZERO)) {
			currentSize = m_pItem->getContentSize();
		}
		m_pItem->setScaleX(currentSize.width * 1.0f / m_pItem->getContentSize().width);
		m_pItem->setScaleY(currentSize.height * 1.0f / m_pItem->getContentSize().height);
		m_pItem->setPosition(Vec2(currentSize.width / 2, -currentSize.height / 2));
		addChild(m_pItem);
		setContentSize(currentSize);
    }
}


 
void TDBar::setNum(long lCur,long lMax){
    if(!getParent()){
        return;
    }
   
    
    setPer(lCur*1.0f/lMax);
}

void TDBar::setPer(float num){
    if(num<0){
        m_nPer=0;
    }
    
    if(num>1){
        m_nPer=100;
    }
    m_nPer=num*100;
}
void TDBar::beforeDraw(Renderer *renderer, const Mat4& parentTransform, bool parentTransformUpdated){
    glEnable(GL_SCISSOR_TEST);
    
    if(this->getParent()){
        Size size=Director::getInstance()->getWinSize();
        
        Point worldPos= convertToWorldSpace(Vec2(0 ,-getContentSize().height));
        
        if(worldPos.x<-getContentSize().width||
           worldPos.y<-getContentSize().height||
           worldPos.x>size.width||
           worldPos.y>size.height
           ){
            return;
        }
		
		Director::getInstance()->getOpenGLView()->setScissorInPoints(
                                                          worldPos.x,
                                                          worldPos.y,
                                                          getContentSize().width*(m_nPer/100.0f)*getScaleX(),
                                                          getContentSize().height
                                                          );
        
        
    }
    
}


void TDBar::afterDraw(Renderer *renderer, const Mat4& parentTransform, bool parentTransformUpdated)
{
    
    glDisable(GL_SCISSOR_TEST);
    
}

void TDBar::visit(Renderer *renderer, const Mat4& parentTransform, bool parentTransformUpdated)
{
	// quick return if not visible
	if (!isVisible())
    {
		return;
    }

	Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	
    //	glPushMatrix();
	
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
        //this->transformAncestors();
    }
    
	this->transform(parentTransform);
    this->beforeDraw(renderer, parentTransform, parentTransformUpdated);
    
	if (!_children.empty())
    {

		unsigned int i=0;
		for (; i < (unsigned int)_children.size(); i++)
        {
			Node *child = _children.at(i);
			if (child->getLocalZOrder() < 0)
            {
				child->visit(renderer, parentTransform, parentTransformUpdated);
			}
            else
            {
				break;
            }
		}
		
		// this draw
		this->draw(renderer, parentTransform, parentTransformUpdated);
		
		// draw children zOrder >= 0
		for (; i < (unsigned int)_children.size(); i++)
        {
			Node *child = _children.at(i);
			child->visit(renderer, parentTransform, parentTransformUpdated);
		}
	}
    else
    {
		this->draw(renderer, parentTransform, parentTransformUpdated);
    }
    
	this->afterDraw(renderer, parentTransform, parentTransformUpdated);
	if ( m_pGrid && m_pGrid->isActive())
    {
		m_pGrid->afterDraw(this);
    }
    
	Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
}



/***************************************************
 * TEditBar
 **************************************************/
 

TDEditBar::TDEditBar(){
    controller=NULL;
    m_pMoveListener=NULL;
    m_pMovefnSelector=NULL;
}
TDEditBar* TDEditBar::create(xml_node<> * pItem){
    
    TDEditBar*  ret=TDEditBar::create();
    ret->initWidthConf(pItem);
    return ret;
}

void TDEditBar::setChangeTarget(Ref*  obj ,SEL_MenuHandler selector){
    m_pMoveListener=obj;
    m_pMovefnSelector=selector;
} 
void TDEditBar::valueChanged(Ref *sender, Control::EventType controlEvent)
{
    if(m_pMoveListener&& m_pMovefnSelector)
        (m_pMoveListener->*m_pMovefnSelector)(this);
    
}

void TDEditBar::initWidthConf(xml_node<> * pItem){
    TDPanel::initWidthConf(pItem);
    string path,progress,thumb;
    readAttrString(pItem, "flag", thumb);
    readAttrString(pItem, "source", progress);
    readAttrString(pItem, "bg", path);
    controller=ControlSlider::create(Sprite::createWithSpriteFrameName(path.c_str()),
                                       Sprite::createWithSpriteFrameName(progress.c_str()),
                                       Sprite::createWithSpriteFrameName(thumb.c_str())
                                       );
    addChild(controller);
    //controller->setTouchPriority(-128);
    controller->setPositionX(getContentSize().width/2);
    controller->setPositionY(-getContentSize().height/2);
    
    controller->addTargetWithActionForControlEvents(this,
                                                    cccontrol_selector(TDEditBar::valueChanged),
													Control::EventType::VALUE_CHANGED);
    controller->setMaximumValue(100.0f);
    controller->setMinimumValue(0.0f);
    
    setPer(0.5);
}


void TDEditBar::setPer(float num){
    if(controller)
    controller->setValue(num*100);
}


float TDEditBar::getPer(){
    if(controller)
    return controller->getValue()/100.0f;
    
    return 0;
}
