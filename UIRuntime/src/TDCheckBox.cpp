#include "TDCheckBox.h"

TDCheckBox::TDCheckBox(){
    m_bSelected=false;
}

TDCheckBox::~TDCheckBox(){
    
}


bool TDCheckBox::isSelected(){
    return m_bSelected;
}


void TDCheckBox::selected(){
    if(m_bSelected){
        
        setSelected(false);
    }else{
        
        setSelected(true);
    }
}

void TDCheckBox::unselected(){
    
}
void TDCheckBox::setSelected(bool value){
    m_bSelected=value;
    m_pIcon->setVisible(m_bSelected);
}

TDCheckBox* TDCheckBox::create(xml_node<> * pItem){
	TDCheckBox*  ret = UIBase::create<TDCheckBox>();
    ret->initWidthConf(pItem);
    return ret;
}


void TDCheckBox::initWidthConf(xml_node<> * pItem){
    if(!pItem) return;
    Size size=readContainSize(pItem,getParent());
    if(size.width ==-1) size.width=getContentSize().width;
    if(size.height==-1) size.height=getContentSize().height;
    setContentSize(size);
    
    
    
    string path;
    readAttrString(pItem, "source", path);
    m_pBg=TDScale9::createWithSpriteFrameName(path.c_str());
    addChild(m_pBg);
    m_pBg->setPreferredSize(size); 
    
    
    readAttrString(pItem, "icon", path);
    m_pIcon=Sprite::createWithSpriteFrameName(path.c_str());
    addChild(m_pIcon);
    m_pIcon->setPositionX(getContentSize().width/2 );
    m_pIcon->setPositionY(-getContentSize().height/2 );
    
    m_bSelected=true;
}
