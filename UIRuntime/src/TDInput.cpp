#include "TDInput.h"
#include "TDScale9.h"

#define DEFAULT_WIDTH 121
#define DEFAULT_HEIGHT 31 
#define DEFAULT_FONT_SIZE 12
const static char* defaultImg = "Images/shurukuang.png";

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
    if(m_pEditor)
        return m_pEditor->getText();
    return "";
}

void TDInput::setString(const char* str)
{
    if(str==NULL)
        str="";
    
    if(m_pEditor)
        m_pEditor->setText(str);
}

void TDInput::initWidthConf(xml_node<> * pItem){
	
	float width, height;
	int fontSize, maxNum, returnType, inputMode, inputFlag;
	string color;
	string text, bg, emptyText;
    width= readAttrFloat(pItem, "Width");
	height = readAttrFloat(pItem, "Height");
    fontSize= readAttrInt(pItem, "FontSize");
	maxNum = readAttrInt(pItem, "LimitNum");
	readAttrString(pItem, "Color", color);
	readAttrString(pItem, "Text", text);
	readAttrString(pItem, "InputBg", bg);
	readAttrString(pItem, "EmptyText", emptyText);
	bool isPassword = readAttrBool(pItem, "IsPassword");
    float nowWidth=DEFAULT_WIDTH;
	float nowHeight = DEFAULT_HEIGHT;
    int nowFontSize=DEFAULT_FONT_SIZE; 
    if(width!=0){
        nowWidth=width;
    }
    if(height!=0){
        nowHeight=height;
    }
    if(fontSize!=0){
        nowFontSize=fontSize;
    }
    setContentSize(Size(nowWidth, nowHeight));
	
	SpriteFrame* frame = UIUtils::getInstance()->spriteFrameByName(bg.c_str());
#ifdef ENABLE_DEFAULT_PNG
	if (!frame)
		frame = UIUtils::getInstance()->spriteFrameByName(defaultImg);
#endif
	if (!frame)
		return;
	
	m_pEditor = EditBox::create(Size(nowWidth, nowHeight), Scale9Sprite::createWithSpriteFrame(frame));
    if(emptyText.size() != 0){
		m_pEditor->setPlaceHolder(emptyText.c_str());
    }
    if(color.size()!=0){
        replaceStr(color, "#", "");
        int temp=HexToDec(color.c_str());
        m_pEditor->setFontColor(parseRgb(temp));
    }
    m_pEditor->setFont("Helvetica", nowFontSize);
    m_pEditor->setMaxLength(maxNum);
	if (isPassword)
		m_pEditor->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    //m_pEditor->setInputMode(getInputMode(inputMode));
    //m_pEditor->setReturnType(getInputReturnType(returnType));
 
    addChild(m_pEditor);
    m_pEditor->setPositionX(nowWidth/2);
    m_pEditor->setPositionY(nowHeight/2);

	TDPanel::initWidthConf(pItem);
}
