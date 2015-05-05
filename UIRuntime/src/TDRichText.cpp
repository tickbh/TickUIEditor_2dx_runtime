#include "TDRichText.h"


#define DEFAULT_WIDTH 100
#define DEFAULT_HEIGHT 21 
#define DEFAULT_FONT_SIZE 12

TDRichText::TDRichText()
:m_pLabel(NULL)
{

}

TDRichText::~TDRichText()
{
}

TDRichText* TDRichText::create( xml_node<> * pItem )
{
	TDRichText* ret=new TDRichText;
	if(ret == NULL) {
		return NULL;
	}
	ret->autorelease();
	ret->initWidthConf(pItem);
	return ret;
}

bool TDRichText::init()
{
	return TDPanel::init();
}

TDRichText* TDRichText::create( const char* utf8_str, const Size& preferred_size, const char* font_alias /*= DFONT_DEFAULT_FONTALIAS*/ )
{
	TDRichText* label = new TDRichText;
	if (label && label->initWidthFormat(utf8_str, preferred_size, font_alias))
	{
		label->autorelease();
		return label;
	}
	CC_SAFE_DELETE(label);
	return NULL;
}

void TDRichText::initWidthConf( xml_node<> * pItem )
{
	float width,height;
	int fontSize;
	width = readAttrFloat(pItem, "width");
	height = readAttrFloat(pItem, "height");
	fontSize= readAttrInt(pItem, "fontSize");

	float nowWidth=DEFAULT_WIDTH;
	float nowHeight = DEFAULT_HEIGHT;
	int nowFontSize=DEFAULT_FONT_SIZE;

	string strVA="",strHA="" ,color;
	readAttrString(pItem, "textAlign", strHA);
	readAttrString(pItem, "verticalAlign", strVA);
	readAttrString(pItem, "color", color);

	if(strHA.size()!=0){
	}else{
	}
	    
	if(strVA.size()!=0){
	}else{
	}

	if(width!=0){
		nowWidth=width;
	}

	if(height!=0){
		nowHeight=height;
	}
	if(fontSize!=0){
		nowFontSize=fontSize;
	}
	string text;
	readAttrString(pItem, "text", text);

	string font;
	readAttrString(pItem, "font", font);
	if(font.empty()) {
		font = "font";
	}

	Size size(nowWidth, nowHeight);
	initWidthFormat(text.c_str(), size, font.c_str());
	setFontSize(fontSize);
	if(color.size()!=0){
		//replaceStr(color, "#", "");
		//unsigned int temp = HexToDec(color.c_str());
		unsigned int temp = parseColor(color);
		//m_pLabel->setDefaultColor(temp);
	}

	m_pLabel->setAnchorPoint(Vec2(0.5f,0.5f));
	m_pLabel->setPositionX(nowWidth/2);
	m_pLabel->setPositionY(nowHeight/2); 
	//m_pLabel->setDefaultAlignment(hAlign);

	setContentSize(size);
}

bool TDRichText::initWidthFormat( const char* utf8_str, const Size& preferred_size, const char* font_alias /*= DFONT_DEFAULT_FONTALIAS*/ )
{
	if(utf8_str==NULL){
		utf8_str="";
	}
	//m_pLabel = CCHTMLLabel::createWithString(utf8_str, preferred_size, font_alias);
	//m_pLabel =  CCHTMLLabel::create();
	//m_pLabel->setPreferredSize(RSize(preferred_size.width, preferred_size.height));
	//m_pLabel->setDefaultFontAlias(font_alias);
	setString(utf8_str);
	if (m_pLabel)
	{
		this->addChild(m_pLabel);
		return true;
	}
	return false;
}

void TDRichText::setString( const char* cstr )
{
	string draw = cstr;
	std::string current = m_pLabel->getContent();
	if(current.compare(draw)) {
		m_pLabel->setContent(draw.c_str());
	}
}

void TDRichText::setString( const string& str )
{
	setString(str.c_str());
}

void TDRichText::setString( int value )
{
	string cvalue = CCString::createWithFormat("%d", value)->getCString();
	setString(cvalue.c_str());
}

int TDRichText::getNum()
{
	std::string str = m_pLabel->getContent();
	return atoi(str.c_str());
}

std::string TDRichText::getString()
{
	return m_pLabel->getContent();
}

void TDRichText::setColor( const Color3B& color )
{
	int iColor = (color.r << 16) + (color.g << 8) + color.b;
	//m_pLabel->setDefaultColor(iColor);
}

WidgetRichText* TDRichText::getRichLabel()
{
	return m_pLabel;
}

void TDRichText::setFontSize( int size )
{
	//string defaultFontAlias = getRichLabel()->getDefaultFontAlias();
	//static const char* number = "0123456789";
	//int pos = defaultFontAlias.find_first_of(number);
	//if(pos != string::npos) {
	//	defaultFontAlias = CCString::createWithFormat("%s%d", defaultFontAlias.substr(0, pos).c_str(), size)->getCString();
	//} else {
	//	defaultFontAlias = CCString::createWithFormat("%s%d", defaultFontAlias.c_str(), size)->getCString();
	//}
	//getRichLabel()->setDefaultFontAlias(defaultFontAlias.c_str());
}

