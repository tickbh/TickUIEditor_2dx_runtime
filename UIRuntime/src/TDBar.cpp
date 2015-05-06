#include "TDBar.h"
#include "TDUI.h"

static const char* defaultImage = "Images/ProgressFile.png";

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

void TDBar::setSource(const char* path, Size contentSize/* = Size::ZERO*/) {
	SpriteFrame* frame = UIUtils::getInstance()->spriteFrameByName(path);
#ifdef ENABLE_DEFAULT_PNG
	if (frame == nullptr) {
		frame = UIUtils::getInstance()->spriteFrameByName(defaultImage);
	}
#endif
	if (!frame) {
		return;
	}
	if (m_pItem == nullptr) {
		m_pItem = Sprite::createWithSpriteFrame(frame);
		addChild(m_pItem);
	} else {
		m_pItem->setSpriteFrame(frame);
	}
	if (contentSize.equals(Size::ZERO)) {
		contentSize = m_pItem->getContentSize();
	}
	m_pItem->setScaleX(contentSize.width * 1.0f / m_pItem->getContentSize().width);
	m_pItem->setScaleY(contentSize.height * 1.0f / m_pItem->getContentSize().height);
	m_pItem->setPosition(Vec2(contentSize.width / 2, contentSize.height / 2));
	setContentSize(contentSize);
	resetSpriteInfo();
}


TDBar* TDBar::create(xml_node<> * pItem){
    
	TDBar*  ret = UIBase::create<TDBar>();
    ret->initWidthConf(pItem);
    return ret;
}

void TDBar::initWidthConf(xml_node<> * pItem){
    string path;
    readAttrString(pItem, "ImageBar", path);
    float per= readAttrFloat(pItem, "Progress");
    setPer(per);
	Size currentSize = readContainSize(pItem, getParent());
	setSource(path.c_str(), currentSize);
	TDPanel::initWidthConf(pItem);
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
	resetSpriteInfo();
}


void TDBar::resetSpriteInfo() {
	if (!m_pItem)
		return;

	m_pItem->setContentSize(Size(this->getContentSize().width * m_nPer / 100, this->getContentSize().height));

}


void TDBar::beforeDraw(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) {
    glEnable(GL_SCISSOR_TEST);
    if(this->getParent()){
		Rect rect = getPanelRect(this);
		Size size=Director::getInstance()->getWinSize();
		//Point worldPos = convertToWorldSpace(Vec2(rect.origin.x, rect.origin.y));
		Point worldPos = convertToWorldSpace(Vec2(0, -this->getContentSize().height));
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


void TDBar::afterDraw(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    glDisable(GL_SCISSOR_TEST);
    
}

void TDBar::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
	//Node::visit(renderer, parentTransform, parentFlags);
	//return;
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
	this->beforeDraw(renderer, parentTransform, parentFlags);
    
	if (!_children.empty())
    {

		unsigned int i=0;
		for (; i < (unsigned int)_children.size(); i++)
        {
			Node *child = _children.at(i);
			if (child->getLocalZOrder() < 0)
            {
				child->visit(renderer, parentTransform, parentFlags);
			}
            else
            {
				break;
            }
		}
		
		// this draw
		this->draw(renderer, parentTransform, parentFlags);
		
		// draw children zOrder >= 0
		for (; i < (unsigned int)_children.size(); i++)
        {
			Node *child = _children.at(i);
			child->visit(renderer, parentTransform, parentFlags);
		}
	}
    else
    {
		this->draw(renderer, parentTransform, parentFlags);
    }
    
	this->afterDraw(renderer, parentTransform, parentFlags);
	if ( m_pGrid && m_pGrid->isActive())
    {
		m_pGrid->afterDraw(this);
    }
    
	Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
}
