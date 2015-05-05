#include "TDUI.h"

#include "TDImage.h"
#include "TDScale9.h"
#include "TDButton.h"
#include "TDTip.h"
#include "TDTab.h"
#include "TDPage.h"
#include "TDBar.h"
#include "TDCount.h"
#include "TDWin.h"
#include "TDRichText.h"
#include "TDCheckBox.h"
#include "TDAccordion.h"
#include "TDInput.h"
#include "LuaUIManager.h"

TDPanel* TDUIExpand::createUI(xml_node<> *){

    return NULL;
}

TDPanel* TDUIExpand::createUI(const string&){
    
    return NULL;
}

extern const char* cocos2dVersion(void);

TDUI* TDUI::instance(void)
{
	static TDUI s_SharedTUI;
    return &s_SharedTUI;
}

TDPanel* TDUI::createUI(const string& itemName){
    
	TDPanel* ret = createBaseUI(itemName);
	if (!ret && m_pExpand){
        ret=m_pExpand->createUI(itemName);
    }
    //为空，应调用LUA层去创建
    if(ret == NULL) {
        //ret = FlashBuilderManager::instance()->getPanelItem(itemName.c_str());
    }
    return ret;
}


TDPanel* TDUI::createUI(xml_node<> * pItem){
    string itemName=  pItem->name() ;
	string name;
	readAttrString(pItem, "Name", name);
	if (name.size() != 0) {
		itemName = name;
    }
    TDPanel* ret=createUI(itemName);
    
    if(ret){
        ret->tName=itemName;
		ret->loadProp(pItem);
    }
    return ret;
}

void TDUI::setExpand(TDUIExpand* exp){
    m_pExpand=exp;
}

void TDUI::init(){
    
}

TDUI::TDUI(void)
	:m_pExpand(NULL)
{
	init();
}


xml_document<>* TDUI::getDoc(const string& name){
    
   if( docs.find(name)!=docs.end())
   {
       return docs[name];
   }
    
    return NULL;
    
}
void TDUI::addDoc(const string& name,xml_document<>* doc,unsigned char * data){
    if(doc)
    {
        docs[name]=doc;
    }
    
    datas.push_back(data);
}

TDUI::~TDUI(void){
    CC_SAFE_DELETE(m_pExpand);
    
    
    map<string,xml_document<>*>::iterator it=docs.begin();
    
    for( ;it!=docs.end() ;it++){
        CC_SAFE_DELETE(it->second);
    }
    docs.clear();
    
    for(unsigned int i=0;i<datas.size();i++){
        CC_SAFE_DELETE(datas[i]);
    }
    datas.clear();
}

TDPanel* TDUI::createBaseUI(const string& itemName)
{
	TDPanel* ret = NULL;
	if (itemName == T_SCALE9_NAME){
		ret = UIBase::create<TDScale9>();
	}
	else if (itemName == T_BUTTON_NAME){
		ret = UIBase::create<TDButton>();
	}
	else if (itemName == T_IMAGE_NAME){
		ret = UIBase::create<TDImage>();
	}
	//else if (itemName == T_TAB_NAME){
	//	ret = UIBase::create<TDTab>();
	//}
	//else if (itemName == T_SCROLL_NAME){
	//	ret = UIBase::create<TDScrollPanel>();
	//}
	else if (itemName == T_PAGE_NAME){
		ret = UIBase::create<TDPage>();
	}
	else if (itemName == T_PANEL_NAME){
		ret = UIBase::create<TDPanel>();
	}
	else if (itemName == T_BAR_NAME){
		ret = UIBase::create<TDBar>();
	}
	else if (itemName == T_INPUT_NAME){
		ret = UIBase::create<TDInput>();
	}
	else if (itemName == T_RICH_TEXT_NAME) {
		ret = UIBase::create<TDRichText>();
	}
	else if (itemName == T_WIN_NAME) {
		ret = UIBase::create<TDWin>();
	}
	
	return ret;
}

