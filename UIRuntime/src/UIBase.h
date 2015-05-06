#ifndef _TD_UI_BASE_H_
#define _TD_UI_BASE_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "UIUtils.h"
#include <string>
#include "rapidxml/rapidxml.hpp"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace rapidxml;
using namespace std;

#define DEV_PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void){return varName;}\
public: virtual void set##funName(varType var){varName=var; }\


#define DEV_PROPERTY_VALUE(varType, varName, funName,value)\
protected: varType varName;\
public: virtual varType get##funName(void){return varName;}\
public: virtual void set##funName(varType var=value){varName=var; }\

#define DEV_PROPERTY_READONLY(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void){return varName; }\

#define DEV_PROPERTY_READONLY_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual const varType& get##funName(void){return varName; }\


struct EventStruct
{
	int		nID;
	long	lParam;
	long	rParam;
	EventStruct():nID(0), lParam(0), rParam(0) {}
	EventStruct(const EventStruct & evtStru)
	{
		this->nID = evtStru.nID;
		this->lParam = evtStru.lParam;
		this->rParam = evtStru.rParam;
	}
};

struct BaseEvent
{
	virtual void procEvent(EventStruct * pEvt = NULL) {}
};

class UIBase {
public:
	template<typename T> static T* create() {
		T *pRet = new T();
		if (pRet && pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}

};

int parseInt(const char* str);

float parseNumber(const char* str); 
double parseDouble(const char* str);

void replaceStr(string& str ,const char* find ,const char* replace);
void splitStr(vector<string> &gRet, string cStr ,const char* cSplit );

int HexToDec(const char *s);
int to_hex_value(unsigned short c);
unsigned int parseColor(string & color_str);

bool existAttr(xml_node<> * pItem, const char* cAttr);
bool readAttrBool(xml_node<> * pItem, const char* cAttr);
int readAttrInt(xml_node<> * pItem,const char* cAttr);
float readAttrFloat(xml_node<> * pItem,const char* cAttr);
void readAttrString(xml_node<> * pItem,const char* cAttr, string & ret);
Size readContainSize(xml_node<> * pItem, Node* parent);
Size getParentSize(Node* parent);
Color3B parseRgb(int hex);
int parseH(const Color3B& color);
void setCenterPos(Node* parent, Node* current);
Rect getPanelRect(Node* pNode);
Point getPosInScreen(Point point, Node* pTarget);

//屏幕上的点相对于target里面的点
Point  getPosInTarget(Point point, Node* pTarget);

string  parseString(float i); 
string parseString(int i); 
long getTimer();

#endif

