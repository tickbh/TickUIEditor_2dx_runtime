#include "TDInput.h"
#include "TDScale9.h"

#define DEFAULT_WIDTH 100
#define DEFAULT_HEIGHT 21 
#define DEFAULT_FONT_SIZE 21

void TDInput::editBoxEditingDidBegin(ui::EditBox* editBox){
    
}
void TDInput::editBoxEditingDidEnd(ui::EditBox* editBox){
    
}
void TDInput::editBoxTextChanged(ui::EditBox* editBox, const std::string& text){
    
}

void TDInput::editBoxReturn(ui::EditBox* editBox) {
    
}

TDInput* TDInput::create(xml_node<> * pItem){
	TDInput*  ret = UIBase::create<TDInput>();
    ret->initWidthConf(pItem);
    return ret;
}

ui::EditBox::InputFlag getInputFlag(int num){
    
    switch (num) { 
	case 0: return ui::EditBox::InputFlag::PASSWORD;  break;
	case 1: return ui::EditBox::InputFlag::SENSITIVE;  break;
	case 2: return ui::EditBox::InputFlag::INITIAL_CAPS_WORD;  break;
	case 3: return ui::EditBox::InputFlag::INITIAL_CAPS_SENTENCE;  break;
	case 4: return ui::EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS;  break;
            
        default:
            break;
    }

	return ui::EditBox::InputFlag::INITIAL_CAPS_WORD;
}


ui::EditBox::InputMode getInputMode(int num){
    
    switch (num) {
	case 0: return ui::EditBox::InputMode::ANY;  break;
	case 1: return ui::EditBox::InputMode::EMAIL_ADDRESS;  break;
	case 2: return ui::EditBox::InputMode::NUMERIC;  break;
	case 3: return ui::EditBox::InputMode::PHONE_NUMBER;  break;
	case 4: return ui::EditBox::InputMode::URL;  break;
	case 5: return ui::EditBox::InputMode::DECIMAL;  break;
	case 6: return ui::EditBox::InputMode::SINGLE_LINE;  break;
            
        default:
            break;
    }
  
	return ui::EditBox::InputMode::ANY;
}


ui::EditBox::KeyboardReturnType getInputReturnType(int num){
    switch (num) {
	case 0: return ui::EditBox::KeyboardReturnType::DEFAULT;  break;
	case 1: return ui::EditBox::KeyboardReturnType::DONE;  break;
	case 2: return ui::EditBox::KeyboardReturnType::SEND;  break;
	case 3: return ui::EditBox::KeyboardReturnType::SEARCH;  break;
	case 4: return ui::EditBox::KeyboardReturnType::GO;  break;
            
        default:
            break;
    }
    
	return ui::EditBox::KeyboardReturnType::DEFAULT;
}


TDInput::TDInput(){
    m_pEditor=NULL;
}

bool TDInput::init(){
    
    if(!TDPanel::init()){
        return false;
    } 
    return true;
}


const char* TDInput::getString(){
    if(m_pEditor){
        return m_pEditor->getText();
    }
    return "";
}

void TDInput::setString(const char* str)
{
    if(str==NULL)
    {
        str="";
    }
    
    if(m_pEditor)
    {
        return m_pEditor->setText(str);
    }
}

void TDInput::initWidthConf(xml_node<> * pItem){
	TDPanel::initWidthConf(pItem);
	float width, height;
	int fontSize, maxNum, returnType, inputMode, inputFlag;
    width= readAttrFloat(pItem, "Width");
	height = readAttrFloat(pItem, "Height");
    fontSize= readAttrInt(pItem, "FontSize");
    maxNum= readAttrInt(pItem, "LimitNum");
    
    float nowWidth=DEFAULT_WIDTH;
	float nowHeight = DEFAULT_HEIGHT;
    int nowFontSize=DEFAULT_FONT_SIZE; 
    
    string color; 
    readAttrString(pItem, "Color", color);
    if(width!=0){
        nowWidth=width;
    }
    
    if(height!=0){
        nowHeight=height;
    }
    if(fontSize!=0){
        nowFontSize=fontSize;
    }
    string text,bg;
    readAttrString(pItem, "Text", text);
    readAttrString(pItem, "EmptyText", bg);
    setContentSize(Size(nowWidth, nowHeight));
    //, ui::Scale9Sprite::createWithSpriteFrame(UIUtils::getInstance()->spriteFrameByName(bg.c_str()))
    m_pEditor=ui::EditBox::create(Size(nowWidth, nowHeight), NULL);
    if(text.size()!=0){
        m_pEditor->setPlaceHolder(text.c_str());
    }
    if(color.size()!=0){
        replaceStr(color, "#", "");
        int temp=HexToDec(color.c_str());
        m_pEditor->setFontColor(parseRgb(temp));
    }
    m_pEditor->setFont("Helvetica", nowFontSize);
  
    //m_pEditor->setTouchPriority(kCCMenuHandlerPriority);  
    m_pEditor->setMaxLength(maxNum);
    //m_pEditor->setInputFlag(getInputFlag(inputFlag));
    //m_pEditor->setInputMode(getInputMode(inputMode));
    //m_pEditor->setReturnType(getInputReturnType(returnType));
 
    addChild(m_pEditor);
   
    m_pEditor->setPositionX(nowWidth/2);
    m_pEditor->setPositionY(-nowHeight/2);
}
