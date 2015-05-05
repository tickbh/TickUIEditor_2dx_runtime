#include "UIBase.h"

int parseInt(const char* str){
	if(str==NULL){
		return 0;
	}

	return atoi(str);
}


double parseDouble(const char* str){
	if(str==NULL){
		return 0;
	}

	return atof(str);
}
float parseNumber(const char* str){
	if(str==NULL){
		return 0;
	}

	return (float)atof(str);
}

int HexToDec(const char *s)
{
	const char *p = s;

	//空串返回0。
	if(*p == '\0')
		return 0;

	int dec = 0;

	if (strlen(s) == 6) {
		dec = 0xff;
	}
	//忽略开头的'0'字符
	while(*p == '0')
		p++;

	char c;

	//循环直到字符串结束。
	while(c = *p++)
	{
		//dec乘16
		dec <<= 4;

		//数字字符。
		if(c >= '0' && c <= '9')
		{
			dec += c - '0';
			continue;
		}

		//小写abcdef。
		if(c >= 'a' && c <= 'f')
		{
			dec += c - 'a' + 10;
			continue;
		}

		//大写ABCDEF。
		if(c >= 'A' && c <= 'F')
		{
			dec += c - 'A' + 10;
			continue;
		}

		//没有从任何一个if语句中结束，说明遇到了非法字符。
		return -1;
	}


	//正常结束循环，返回10进制整数值。
	return dec;
}


int to_hex_value(unsigned short c)
{
	if (c >= '0' && c <= '9')
	{
		return c - '0';
	}
	else if (c >= 'A' && c <= 'F')
	{
		return c - 'A' + 10;
	}
	else if (c >= 'a' && c <= 'f')
	{
		return c - 'a' + 10;
	}

	return -1;
}


unsigned int parseColor(string & color_str)
{
	unsigned int color = 0;
	if (!color_str.empty())
	{
		if (color_str[0] == '#'
			&& (color_str.size() == 7 || color_str.size() == 9)) // RGB || ARGB
		{
			if (color_str.size() == 7)
			{
				color = 0xff;
			}

			for (size_t i = color_str.size() - 1; i > 1; i -= 2)
			{
				color = (color << 4) + to_hex_value(color_str[i - 1]);
				color = (color << 4) + to_hex_value(color_str[i]);
			}
		}
	}

	return color;
}



void replaceStr(string& str ,const char* find ,const char* replace){
	string searchString( find);
	string replaceString( replace );

	if(find==replace){
		return ;
	}

	string::size_type pos = 0;
	while ( (pos = str.find(searchString, pos)) != string::npos ) {
		str.replace( pos, searchString.size(), replaceString );
		pos++;
	}
}



void splitStr(vector<string> &gRet, string cStr ,const char* cSplit ){
	gRet.clear();
	int comma_n = 0;
	do
	{
		string tmp_s = "";
		comma_n = cStr.find( cSplit );
		if( -1 == comma_n )
		{
			tmp_s = cStr.substr( 0, cStr.length() );
			gRet.push_back( tmp_s );
			break;
		}
		tmp_s = cStr.substr( 0, comma_n );
		cStr.erase( 0, comma_n+1 );
		gRet.push_back( tmp_s );
	} 
	while(true);
}


int readAttrInt(xml_node<> * pItem,const char* cAttr){
    
	if(!cAttr)
		return 0;
    
	xml_attribute<> * pNode = pItem->first_attribute(cAttr);
	if(!pNode)
		return 0;
    
	char * v = pNode->value();
	if(v)
		return atoi(v);
	else
		return 0;
}
void readAttrString(xml_node<> * pItem,const char* cAttr, string & ret){
    ret = "";
	if(!cAttr)
		return;
    
    
	xml_attribute<> * pNode = pItem->first_attribute(cAttr);
    
    
	if(!pNode)
		return;
    
    
	char * v = pNode->value();
	if(v)
		ret.append(v);
}

Size readContainSize(xml_node<> * pItem,Node* parent){
    Size ret;
    string strWidth="";
    readAttrString(pItem, "Width",strWidth);
    
    string strHeight="";
    readAttrString(pItem, "Height",strHeight);
    float width=0,height=0;
    
	Size parentSize = getParentSize(parent);
    if(strWidth.size()!=0)
    {
        if(strWidth.find("%")!=string::npos){
            replaceStr(strWidth, "%", "");
            
			float per = parseNumber(strWidth.c_str());
            width= (parentSize.width*per)/100;
        }else{
			width = parseNumber(strWidth.c_str());
        }
    }else{
        width=-1;
    }
    
    if(strHeight.size()!=0)
    {
        if(strHeight.find("%")!=string::npos){
            replaceStr(strHeight, "%", "");
			float per = parseNumber(strHeight.c_str());
            height= (parentSize.height*per)/100;
        }else{
			height = parseNumber(strHeight.c_str());
        }
    }else{
        height=-1;
    }
    
    ret.width=width;
    ret.height=height;
    return ret;
}

cocos2d::Size getParentSize( Node* parent )
{
	Size parentSize = parent != NULL ? parent->getContentSize() : Director::getInstance()->getWinSize();
	return parentSize;
}


float readAttrFloat(xml_node<> * pItem,const char* cAttr){
    if(!cAttr)
        return 0.0f;
    
	xml_attribute<> * pNode = pItem->first_attribute(cAttr);
	if(!pNode)
		return 0.0f;
    
	char * v = pNode->value();
	if(v)
		return (float)atof(v);
	else
		return 0.0f;
}

Color3B parseRgb(int hex) 
{
	Color3B color;
	color.r=( 0xff <<16 & hex ) >> 16;
	color.g=( 0xff <<8 & hex ) >> 8;
	color.b=0xff & hex;
	return color;
}

int parseH(const Color3B& color){
	return color.r<< 16 | color.g << 8 | color.b;
}



//target上的点相对于屏幕里面的点
Point getPosInScreen(Point point,Node* pTarget){
	return pTarget->convertToWorldSpace(point);
}

//屏幕上的点相对于target里面的点
Point  getPosInTarget(Point point,Node* pTarget){
	return pTarget->convertToNodeSpace(point);
}

std::string parseString( float i )
{
	ostringstream oss;
	oss<<i;
	return oss.str();
}

std::string parseString( int i )
{
	ostringstream oss;
	oss<<i;
	return oss.str();
}

long getTimer()
{
	//struct cc_timeval now;
	//CCTime::gettimeofdayCocos2d(&now, NULL);
	//long a=now.tv_sec%100000;
	//return (a * 1000 + now.tv_usec / 1000);
	return 0;
}

