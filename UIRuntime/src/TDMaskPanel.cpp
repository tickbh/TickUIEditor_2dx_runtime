#include "TDMaskPanel.h"


/***************************************************
 * TMaskContainer
 **************************************************/
 
bool TMaskContainer::init(){ 
    return true;
}



void TMaskContainer::beforeDraw()
{
    glEnable(GL_SCISSOR_TEST);
    if(this->getParent()){
        
        Point worldPos=this->getParent()->convertToWorldSpace(Vec2(0,0-getContentSize().height));
		Director::getInstance()->getOpenGLView()->setScissorInPoints(
                                                          worldPos.x,
                                                          worldPos.y,
                                                          getContentSize().width,
                                                          getContentSize().height
                                                          );
    }
    
    
} 


void TMaskContainer::afterDraw()
{
    
    glDisable(GL_SCISSOR_TEST);
    
}
//
//void TMaskContainer::visit()
//{
//	// quick return if not visible
//	if (!isVisible())
//    {
//		return;
//    }
//    
//	kmGLPushMatrix();
//	
//    //	glPushMatrix();
//	
//    if (m_pGrid && m_pGrid->isActive())
//    {
//        m_pGrid->beforeDraw();
//        this->transformAncestors();
//    }
//    
//	this->transform();
//    this->beforeDraw();
//    
//	if(m_pChildren)
//    {
//		ccArray *arrayData = m_pChildren->data;
//		unsigned int i=0;
//		
//		// draw children zOrder < 0
//		for( ; i < arrayData->num; i++ )
//        {
//			CCNode *child =  (CCNode*)arrayData->arr[i];
//			if ( child->getZOrder() < 0 )
//            {
//				child->visit();
//			}
//            else
//            {
//				break;
//            }
//		}
//		
//		// this draw
//		this->draw();
//		
//		// draw children zOrder >= 0
//		for( ; i < arrayData->num; i++ )
//        {
//			CCNode* child = (CCNode*)arrayData->arr[i];
//			child->visit();
//		}
//        
//	}
//    else
//    {
//		this->draw();
//    }
//    
//    this->afterDraw();
//	if ( m_pGrid && m_pGrid->isActive())
//    {
//		m_pGrid->afterDraw(this);
//    }
//    
//	kmGLPopMatrix();
//    
//}





/***************************************************
 * TMaskPanel
 **************************************************/

TMaskPanel::TMaskPanel(){
    m_pContainer=NULL;
}

bool TMaskPanel::init(){
    if(!TDPanel::init()){
        return false;
    }
    
    m_pContainer=TMaskContainer::create();
    m_pContainer->setTag(1);
    Node::addChild(m_pContainer,1);
    
    return true;
}


void TMaskPanel::checkVisible(){
    
    int visibleNum=0;
    Point curPos  = m_pContainer->getPosition();
    float startX=   -curPos.x;
	float startY = -curPos.y;
    
    renderStartTag=0;
    for(ssize_t i=0;i<gTouchItems->count();i++){
        TDPanel* item=(TDPanel*)gTouchItems->getObjectAtIndex(i);
        
        if(item->getPositionX()+item->getContentSize().width<startX ||
           item->getPositionY()+item->getContentSize().height<startY ||
           item->getPositionX()-item->getContentSize().width>startX+m_pContainer->getContentSize().width ||
           item->getPositionY()-item->getContentSize().height>startY+m_pContainer->getContentSize().height )
        {
            item->setVisible(false);
        }else{
            
            visibleNum++;
            item->setVisible(true);
            
            if(renderStartTag==0){
                renderStartTag=item->getTag();
            }
        }
        
    }
    
    if(renderStartTag==0){
        renderStartTag=1;
    }
    
}

bool TMaskPanel::onTouchBegan(Touch *pTouch, Event *pEvent){
    
    Node* parent=this;
    while(parent){
        if(!parent->isVisible() || !parent->isRunning()){
            
            return false;
        }
        parent=parent->getParent();
    }
    
    TDPanel::onTouchBegan(pTouch, pEvent);
    
    Point worldPos=convertToWorldSpace(Point::ZERO);
    
    Point touchLocation = pTouch->getLocation();
    
    if(touchLocation.y> worldPos.y
       || touchLocation.y<worldPos.y-m_pContainer->getContentSize().height){
        return false;
    }
    
    if(touchLocation.x> worldPos.x+  m_pContainer->getContentSize().width
       || touchLocation.x<worldPos.x){
        return false;
    }
    
    return true;
}


void  TMaskPanel::calculateRealHeight(){
    
    float height=-m_pContainer->getContentSize().height;
    
	for (auto child : m_pContainer->getChildren())
	{
		float realHeight = (child->getPositionY() - child->getContentSize().height);
		if (realHeight < height){
			height = realHeight;
		}
	}
    m_nRealContainerHeight=-height;
    
}


void  TMaskPanel::calculateRealWidth(){
    
    float width=m_pContainer->getContentSize().width;
    
	for (auto child : m_pContainer->getChildren())
	{
		if (!child->isRunning() || !child->isVisible()){
			continue;
		}
		float realHeight = child->getPositionX() + child->getContentSize().width;

		if (realHeight > width){
			width = realHeight;
		}
	}
    m_nRealContainerWidth=width;
}


void TMaskPanel::initWidthConf(rapidxml::xml_node<> * pItem){
	TDPanel::initWidthConf(pItem);
    if(!pItem) return;
    onCreateComplete();
}


void TMaskPanel::moveToPos(const Point& pos,bool check){
    
    Point targetPos=m_pContainer->getPosition();
    targetPos.y=-pos.y;
    
    if(check){
        
        if(m_nRealContainerHeight-targetPos.y>getContentSize().height){  
            targetPos.y=-getContentSize().height+m_nRealContainerHeight;
        }
    }
    
    
    m_pContainer->setPosition(targetPos);
}

void TMaskPanel::moveToBottom(){
    Point pos=m_pContainer->getPosition();
    pos.y=-getContentSize().height+m_nRealContainerHeight+5;
    m_pContainer->setPosition(pos);
    
}
void TMaskPanel::moveToTop(){
    
    m_pContainer->setPosition(Point::ZERO);
}

/***************************************************
 * TScrollPanel
 **************************************************/

bool TDScrollPanel::init(){
    
    if(!TMaskPanel::init()){
        return false;
    }
     
    m_bIsScroll=true;
    m_nDirection=TScrollV;
    renderStartTag=0;
    isCheckBottom=false;
    return true;
}

void TDScrollPanel::moveToTop(){
    TMaskPanel::moveToTop();
    checkVisible();
    
}
void TDScrollPanel::moveToBottom(){
    TMaskPanel::moveToBottom();
    checkVisible();
    
}
 

void TDScrollPanel::moveToPos(const Point& pos,bool check){
    TMaskPanel::moveToPos(pos,check);
    checkVisible();
}

TDScrollPanel* TDScrollPanel::create(xml_node<> * pItem){
    TDScrollPanel*  ret=TDScrollPanel::create();
    ret->initWidthConf(pItem);
    return ret;
}

void TDScrollPanel::addChild(Node * child){
    m_pContainer->addChild(child);
}


TDPanel* TDScrollPanel::getItemByTag(int tag){
    return (TDPanel*)m_pContainer->getChildByTag(tag);
}
 


void TDScrollPanel::initWidthConf(rapidxml::xml_node<> * pItem){
	TDPanel::initWidthConf(pItem);
    if(!pItem) return;
    if(m_nDirection==TScrollH){
        calculateRealWidth();
    }else{
       calculateRealHeight(); 
    }
    onCreateComplete();
}


void TDScrollPanel::onTouchMoved(Touch *pTouch, Event *pEvent)
{
    
    TDPanel::onTouchMoved(pTouch, pEvent);
    if(m_bIsScroll){
        
        Point touchLocation = pTouch->getLocation();
        Point preLocation  =pTouch->getPreviousLocation();
        Point curPos  = m_pContainer->getPosition();
        Point nextPos ;
        if(m_nDirection==TScrollH){
            
            float nMoveX= touchLocation.x - preLocation.x;
            nextPos = Vec2(curPos.x+ nMoveX, curPos.y);
        }else{
            
            float nMoveY = touchLocation.y - preLocation.y;
			nextPos = Vec2(curPos.x, (curPos.y + nMoveY));
        }
         
        m_pContainer->setPosition(nextPos);
        checkVisible();
        
    }
    
    
}



void TDScrollPanel::onMoveEnd(){
    checkVisible();
}


void TDScrollPanel::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    TDPanel::onTouchEnded(pTouch, pEvent);
    Point curPos (m_pContainer->getPosition().x,m_pContainer->getPosition().y);
     
    if(m_nDirection==TScrollH){
        
        float minX=m_pContainer->getContentSize().width-getRealContainerWidth() ;
        if (curPos.x <minX){
            curPos.x=minX;
        }
        if (curPos.x >0){
            curPos.x=0;
        }
    }else{ 
        float maxY=getRealContainerHeight()-m_pContainer->getContentSize().height;
        if (curPos.y >maxY ){
            curPos.y=maxY;
        } 
        if (curPos.y < 0){
            curPos.y=0;
        }
    }
    
    m_pContainer->stopAllActions();
    Point nowPos=m_pContainer->getPosition();
    m_pContainer->setPosition(curPos);
    checkVisible();
    m_pContainer->setPosition(nowPos);
    m_pContainer->runAction(
                            Sequence::create(
                                               EaseExponentialOut::create(MoveTo::create(0.3f, curPos)  ),
											   CallFunc::create(CC_CALLBACK_0(TDScrollPanel::onMoveEnd, this)),
                                               NULL
                                               )
                            );
}