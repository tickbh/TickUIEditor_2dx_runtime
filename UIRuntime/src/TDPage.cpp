#include "TDPage.h"
#include "TDUI.h"
#include "LuaUIManager.h"

TDPage::TDPage(){
    m_pLeftPanel=NULL;
    m_pRightPanel=NULL;
    m_pPageTxt=NULL; 
    m_pBarContainer=NULL;
}

bool TDPage::init(){
    if(!TDScrollPanel::init()){
        return false;
    }
    nCurPage=0; 
    return true;
}


void TDPage::clearItems(){
    TDScrollPanel::clearItems();
    gotoPage(1);
}



TDPage* TDPage::create(xml_node<> * pItem){
	TDPage*  ret = UIBase::create<TDPage>();
    ret->initWidthConf(pItem);
    return ret;
}


void TDPage::initWidthConf(xml_node<> * pItem){
    
    if(!pItem){
        return ;
    }
    
    string scrollDir;
    readAttrString(pItem, "itemName", itemName);
    readAttrString(pItem, "scrollDir", scrollDir);
    
    if(scrollDir=="V"){
        setDirection(TScrollV);
    }else{
        setDirection(TScrollH);
    }
    
    m_nRowNum =readAttrInt(pItem, "row");
    m_nColNum=readAttrInt(pItem, "col");
	m_nRowDistance = readAttrFloat(pItem, "rowDis");
	m_nColDistance = readAttrFloat(pItem, "colDis");
    nMaxNum=readAttrInt(pItem, "maxNum");
    hasPageBar=(bool)readAttrInt(pItem, "hasPageBar");

    for(int i=0;i<nMaxNum;i++){ 
        TDPanel* item=TDUI::instance()->createUI(itemName);
        addChildItem(item); 
        TDPanel* panel=dynamic_cast<TDPanel*>(item);
        if(panel && panel->confPath.size()!=0){
            panel->loadConf(panel->confPath.c_str());
        }
        item->setTag(i+1);
        m_nItemWidth=item->getContentSize().width;
        m_nItemHeight=item->getContentSize().height;
    }

    layout();

	//if(hasPageBar) {
	//	m_pBarContainer = LuaUIManager::instance()->createPageBar(this, getTotalPage());
	//}
    this->gotoPage(1);
}

void TDPage::layout(){
    for(ssize_t i=0;i<gTouchItems->count();i++){
        TDPanel* item=(TDPanel*)gTouchItems->getObjectAtIndex(i);
        item->setVisible(false);
        m_nItemWidth=item->getContentSize().width;
        m_nItemHeight=item->getContentSize().height; 
        int index= i%(m_nColNum*m_nRowNum);
        int curPage=i/(m_nColNum*m_nRowNum);
        int curRow=index/m_nColNum;
        int curCol=index%m_nColNum;
        item->setPositionX(  getPageWidth()* curPage+curCol*(m_nItemWidth+ m_nColDistance)-1);
        item->setPositionY(-curRow*(m_nItemHeight+ m_nRowDistance)-1); 
    } 
	int onePageNum = m_nColNum  * m_nRowNum;
    m_pContainer->setContentSize(Size(getPageWidth()-m_nColDistance+2,getPageHeight()-m_nRowDistance));
    if(m_pBarContainer) {
		m_pBarContainer->setContentSize(Size(getPageWidth() - m_nColDistance + 2, 10));
	}
    checkVisible();
}



void TDPage::gotoPage(int curPage ){
    
    if(nCurPage==curPage){
        return;
    }
   
    if(curPage<1){
        curPage=1; 
    }
    
    if(curPage>getTotalPage()){
        curPage=getTotalPage(); 
    }
    
    if(curPage<=1){
        if(m_pLeftPanel){
            m_pLeftPanel->setVisible(false);
        }
       
    }else{
        if(m_pLeftPanel){
            m_pLeftPanel->setVisible(true);
        }
    }
    
    
    if(curPage>=getTotalPage()){
        if(m_pRightPanel){
            m_pRightPanel->setVisible(false);
        }
    }else{
        
        if(m_pRightPanel){
            m_pRightPanel->setVisible(true);
        }
    }
    
    int start=nCurPage;
    if(nCurPage>curPage){
        start=curPage;
    }
    
    
    for(int i=0;i<(int)gTouchItems->count();i++){
        TDPanel* item=(TDPanel*)gTouchItems->getObjectAtIndex(i);
        item->setVisible(true);
      
    }
    
    
    
    nCurPage=curPage;
    
    m_pContainer->stopAllActions();
    m_pContainer->runAction(
                            Sequence::create(
                                               EaseExponentialOut::create(MoveTo::create(0.7f,
                                                                                             Vec2( -(getPageWidth())*(nCurPage-1)  ,
                                                                                                 0)
                                                                                             )
                                                                            ),
																			CallFunc::create(CC_CALLBACK_0(TDPage::onPageEnd, this)),
                                               NULL
                                               )
                            );
    
    
    if(m_pPageTxt){
        string temp=parseString(nCurPage);
        temp.append("/");
        temp.append(parseString(getTotalPage()));
        m_pPageTxt->setString(temp);
    }
    
    if(m_pBarContainer){
		LuaUIManager::instance()->pageChanged(m_pBarContainer, nCurPage);
		LuaUIManager::instance()->changePageNum(this, m_pBarContainer, getTotalPage());
    }
    
}



void TDPage::onPageEnd(){
    checkVisible();
   
}

void TDPage::onTouchMoved(Touch *pTouch, Event *pEvent){
    TDScrollPanel::onTouchMoved(pTouch, pEvent);
    
    
}

TDPanel* TDPage::ensureItemByIdx( int idx )
{
	TDPanel* item = (TDPanel*)m_pContainer->getChildByTag(idx);
	if(item != NULL) {
		return item;
	}
	for(int i=nMaxNum;i<idx;i++){ 
		TDPanel* item=TDUI::instance()->createUI(itemName);
		addChildItem(item); 
		TDPanel* panel=dynamic_cast<TDPanel*>(item);
		if(panel && panel->confPath.size()!=0){
			panel->loadConf(panel->confPath.c_str());
		}
		item->setTag(i+1);
		m_nItemWidth=item->getContentSize().width;
		m_nItemHeight=item->getContentSize().height;
	}
	nMaxNum = idx > nMaxNum ? idx : nMaxNum;
	layout();
	return getItemByIdx(idx);

}


TDPanel* TDPage::getItemByIdx(int idx){
    return (TDPanel*)m_pContainer->getChildByTag(idx);
}

void TDPage::onTouchEnded(Touch *pTouch, Event *pEvent){
     
    Point curPos (m_pContainer->getPosition().x,m_pContainer->getPosition().y);
    
    
    Point touchEndPos= pTouch->getLocation();
    
	float distance = (touchEndPos.x - touchStartPos.x);
    
    
    if(distance>8){
        gotoPage(nCurPage-1);
    }else if(distance<-8){
        gotoPage(nCurPage+1);
        
    }else{
        gotoPage(nCurPage);
        TDPanel::onTouchEnded(pTouch, pEvent);
    }
    
    
}


float TDPage::getPageWidth(){
    return  m_nColNum*m_nItemWidth+(m_nColNum )*m_nColDistance;
}

float TDPage::getPageHeight(){
    return  m_nRowNum*m_nItemHeight+(m_nRowNum )*m_nRowDistance;
}

int TDPage::getTotalPage(){
    int aPage=m_nColNum*m_nRowNum;
    return gTouchItems->count() /aPage;
}

void TDPage::setBarContainer( TDPanel* m_pBarContainer )
{
	this->m_pBarContainer = m_pBarContainer;
	if(this->m_pBarContainer) {
		LuaUIManager::instance()->pageChanged(m_pBarContainer, nCurPage);
		LuaUIManager::instance()->changePageNum(this, m_pBarContainer, getTotalPage());
	}
}

TDPanel* TDPage::getBarContainer()
{
	return this->m_pBarContainer;
}
