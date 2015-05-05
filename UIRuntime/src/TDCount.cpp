
#include "TDCount.h"
#include "TDBase.h"
#include "TDRichText.h"
#include "TDUI.h"

/***************************************************
 * TCounterPanel
 **************************************************/


bool TDCounterPanel::procTuiEvent(const string& event,TDPanel* node){ 
    if(event=="num"){
        TDCount* com=(TDCount*)(pCom);
        int num=com->getNum();
        
        if(node->getTag()==11)
        {
            num=num/10;
            
        }else if(node->getTag()==10)
        {
            num=num*10;
        }else {
            num=num*10+node->getTag();
        }
        
        if(num>com->getMaxNum()){
            num=com->getMaxNum();
        }
        com->setNum(num);
        getRichText("txtNum")->setString(num);
    }else if(event=="ok"){
        hide();
        TDCount* com=(TDCount*)(pCom);
        com->inputEnd();
    }else{
        hide();
        TDCount* com=(TDCount*)(pCom);
        com->inputClose();
    }
    return true;
}

TDCounterPanel::TDCounterPanel(){
    pCom=NULL;
}

void TDCounterPanel::hide(){
    if(this->getParent())
    {
        this->getParent()->removeChild(this, true);
    }
}

bool TDCounterPanel::onTouchBegan(Touch *pTouch, Event *pEvent){
    
    Point worldPos=convertToWorldSpace(Point::ZERO);
    
    Point touchLocation = pTouch->getLocation();
    
    
    
    if(touchLocation.y> worldPos.y 
       || touchLocation.y<worldPos.y-getContentSize().height ){
        hide();
        return false;
    }
    
    if(touchLocation.x> worldPos.x +  getContentSize().width
       || touchLocation.x<worldPos.x){
        hide();
        return false;
    }
    
    TDPanel::onTouchBegan(pTouch, pEvent);
    return true;
}


bool TDCounterPanel::init(){ 
    if (!TDPanel::init()) {
        return false;
    }
    
    loadConf("tcom/TDCountPanel.mxml");
     
    return true;
} 
 


 

/***************************************************
 * TCount
 **************************************************/
TDCount::TDCount(){
    m_nMaxNum=10;
    m_pListener=NULL;
    m_pfnSelector=NULL;
    m_pCListener=NULL;
    m_pCfnSelector=NULL;
    m_pClListener=NULL;
    m_pClfnSelector=NULL;

}


void TDCount::onShow(){
    
    
    if(m_pCountPanel && m_pCountPanel->getParent()==NULL){
        Director::getInstance()->getRunningScene()->addChild(m_pCountPanel,100);
    }
	Size winSize = Director::getInstance()->getWinSize();
    
    Point containerPos=  getPosInScreen(Point::ZERO, this);
    
    int dir=1;
    
    if(containerPos.x+getContentSize().width/2>winSize.width/2){
        dir=-1;
    }
    m_pCountPanel->setPositionY(containerPos.y);
    
    
    if(dir==1){
        
        m_pCountPanel->setPositionX(containerPos.x+getContentSize().width+m_pCountPanel->getContentSize().width +20);
    }else{ 
        m_pCountPanel->setPositionX(containerPos.x-m_pCountPanel->getContentSize().width -20);
    }
    
    if(m_pCountPanel->getPositionX()<0){
        m_pCountPanel->setPositionX(0);
    }
    
    
    if(m_pCountPanel->getPositionX()+m_pCountPanel->getContentSize().width>winSize.width){
        m_pCountPanel->setPositionX(winSize.width-m_pCountPanel->getContentSize().width);
    }
    
    
    if(containerPos.y>winSize.height){
        m_pCountPanel->setPositionY(winSize.height-10);
    }
    
    if(containerPos.y-m_pCountPanel->getContentSize().height<0){
        m_pCountPanel->setPositionY(m_pCountPanel->getContentSize().height+10);
    }
   ((TDCounterPanel*)m_pCountPanel)->setMaxNum(m_nMaxNum);
    
    ((TDCounterPanel*)m_pCountPanel)->getRichText("txtNum")->setString(getNum());
}

void TDCount::onHide(){
    if(m_pCountPanel && m_pCountPanel->getParent()){
        m_pCountPanel->getParent()->removeChild(m_pCountPanel, true);
    }
}


int TDCount::getNum(){
    return m_nNum;
}


bool TDCount::getIsOpen(){
    return m_pCountPanel->isVisible();
}


void TDCount::unselected(){
    onHide();
}

void TDCount::selected(){
    onShow();
    
}
void TDCount::setCloseTarget(Ref *rec, SEL_MenuHandler selector){
    m_pClListener=rec;
    m_pClfnSelector=selector;
}


void  TDCount::setCompleteTarget(Ref *rec, SEL_MenuHandler selector){
    m_pCListener=rec;
    m_pCfnSelector=selector;
}

void TDCount::setTarget(Ref *rec, SEL_MenuHandler selector){
    m_pListener=rec;
    m_pfnSelector=selector;
}


void TDCount::inputEnd(){
    
    if(m_pCListener && m_pCfnSelector){
        (m_pCListener->*m_pCfnSelector)(this);
    }
}

void TDCount::inputClose(){
    
    if(m_pClListener && m_pClfnSelector){
        (m_pClListener->*m_pClfnSelector)(this);
    }
}

void TDCount::setMaxNum(int num){
    m_nMaxNum=num;
    m_nNum=0;
    m_pLabel->setString("0");
}



void TDCount::setNum(int num){
    
    m_nNum=num;
    m_pLabel->setString(parseString(m_nNum).c_str());
    
    if(m_pListener && m_pfnSelector){
        (m_pListener->*m_pfnSelector)(this);
    }


}



TDCount::~TDCount(){
    m_pCountPanel->release();
}

bool TDCount::init(){
    if(!TDPanel::init()){
        return false;
    }
    m_nNum=0;
	TDCounterPanel* temp = UIBase::create<TDCounterPanel>();
    temp->retain();
     
    ((TDCounterPanel*)temp)->pCom=this;
    m_pCountPanel=temp;

	//TODO
    //m_pLabel=createLabel(100,20);

    //addChild(m_pLabel);
    
    onHide();
    return true;
}

 

TDCount* TDCount::create(xml_node<> * pItem){
    TDCount*  ret=TDCount::create();
    ret->initWidthConf(pItem);
    return ret;
}

 
void TDCount::initWidthConf(xml_node<> * pItem){
    
    float width=readAttrFloat(pItem, "width");
	float height = readAttrFloat(pItem, "height");
    
    if(width==0 || height==0){
        width=getContentSize().width;
        height=getContentSize().height;
    }
    
    m_pLabel->setPosition(Vec2(width/2,-height/2));
    
    setContentSize(Size(width, height));
    
    string color;
    readAttrString(pItem, "color", color);
    
    
    int fontSize;
    fontSize= readAttrInt(pItem, "fontSize");
    
    
    
    if(fontSize!=0){
        m_pLabel->setFontSize(fontSize);
    }
    
    if(color.size()!=0){
        replaceStr(color, "#", "");
        int temp=HexToDec(color.c_str());
        m_pLabel->setColor(parseRgb(temp));
    }
    
}