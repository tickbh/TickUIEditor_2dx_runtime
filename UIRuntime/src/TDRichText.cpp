#include "TDRichText.h"

const char* defaultText = "Text Label";

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
	string color;
	readAttrString(pItem, "Color", color);
	int fontSize = readAttrFontSize(pItem, 18);
	string text;
	readAttrString(pItem, "Text", text);
#ifdef ENABLE_DEFAULT_UI
	if (text.empty())
		text = defaultText;
#endif

	string font;
	readAttrString(pItem, "font", font);

	Size size = this->getContentSize();
	initWidthFormat(text.c_str(), size, font.c_str());
	if (color.size() != 0) {
		unsigned int temp = parseColor(color);
		m_pLabel->setColor(parseRgb(temp));
	}
	m_pLabel->setFontSize(fontSize);
	m_pLabel->setContentSize(size);
	setCenterPos(this, m_pLabel);
	TDPanel::initWidthConf(pItem);
}

bool TDRichText::initWidthFormat( const char* utf8_str, const Size& preferred_size, const char* font_alias /*= DFONT_DEFAULT_FONTALIAS*/ )
{
	if(utf8_str==NULL){
		utf8_str="";
	}
	m_pLabel = WidgetRichText::create(utf8_str, preferred_size);
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
	if (m_pLabel)
		m_pLabel->setColor(color);
}

WidgetRichText* TDRichText::getRichLabel()
{
	return m_pLabel;
}

void TDRichText::setFontSize( int size )
{
	if (m_pLabel)
		m_pLabel->setFontSize(size);
}

