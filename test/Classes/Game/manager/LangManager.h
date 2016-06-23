#ifndef _LangManager_H_
#define _LangManager_H_

#include "Message.h"
#include "../utils/ValuesUtil.h"

class LangManager
{
public:
	LangManager(){};

	static string getText( string msg )
	{
		////ԭʼ�ı���#LC1#�ı�#R
		////�滻�ı���<font color='#ff0000'> �ı� </font>
		//if(!langMap)return "";
		//if(langMap.hasOwnProperty(code)){
		//	var text:String = langMap[code];
		//	text = text.replace(/#L(?!C)/ig, "#LC1#");//Ĭ����ɫC1#
		//	text = text.replace(/\\n/ig, "\n");//ת�廻�з�
		//	var regArr:Array = text.match(/C\d+#/ig);//ƥ��C1# C2#��
		//	if(regArr!=null){
		//		for each(var reg:String in regArr){
		//			if(!langMap.hasOwnProperty(reg)){//û��������ɫ��Ĭ����#ff0000
		//				langMap[reg] = "#ff0000";
		//			}
		//			text = text.replace(reg, langMap[reg]+"'>");
		//		}
		//	}
		//	text = text.replace(/#L/ig, "<font color='");
		//	text = text.replace(/#R/ig, "</font>");

		//	if(text!=""){
		//		if(arg.length>0 && arg[0] is Array){
		//			arg = arg[0];
		//		}
		//		return StringUtil.substitute(text, arg);
		//	}
		//}
		//return StringUtil.substitute("Error: {0}",  code);

		return ValuesUtil::Instance()->getString( msg );
	}

	static string getText( string msg, int arg1 )
	{
		char txt[128];
		sprintf( txt, ValuesUtil::Instance()->getString( msg ).c_str(), arg1 );
		return txt;
	}
	static string getText( string msg, int arg1, int arg2 )
	{
		char txt[128];
		sprintf( txt, ValuesUtil::Instance()->getString( msg ).c_str(), arg1, arg2 );
		return txt;
	}

	static string getText( string msg, const char* arg1 )
	{
		char txt[128];
		sprintf( txt, ValuesUtil::Instance()->getString( msg ).c_str(), arg1 );
		return txt;
	}

	static ccColor3B getColor( string msg )
	{
		return ValuesUtil::Instance()->getColor(msg);
	}
public:
	static void msgShow( string msg, ccColor3B color = ccc3(0, 255, 0), int delay = 3 )
	{
		color = ValuesUtil::Instance()->getColor(msg);
		msg = ValuesUtil::Instance()->getString( msg );
		Message::Instance()->show( msg, color, delay );
	}

	static void msgStr( string msg, ccColor3B color = ccc3(0, 255, 0), int delay = 3 )
	{
		Message::Instance()->show( msg, color, delay );
	}

	static void msgShow( string msg, string arg1, ccColor3B color = ccc3(0, 255, 0), int delay = 3 )
	{
		color = ValuesUtil::Instance()->getColor(msg);
		msg = getText( msg, arg1.c_str() );
		Message::Instance()->show( msg, color, delay );
	}

	static void msgShow( string msg, string arg1, int arg2, ccColor3B color = ccc3(0, 255, 0), int delay = 3 )
	{
		color = ValuesUtil::Instance()->getColor(msg);
		char txt[128];
		sprintf( txt, ValuesUtil::Instance()->getString( msg ).c_str(), arg1.c_str(), arg2 );
		Message::Instance()->show( string(txt), color, delay );
	}
};

#endif