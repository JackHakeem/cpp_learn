#include "TextFieldTTF.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
//#include "CCTextEmojiArray.h"
#include "manager/LangManager.h"


std::string EMOJIARRAY[800]={
    "\xe2\x98\x80"      ,
    "\xe2\x98\x81"      ,
    "\xe2\x98\x94"      ,
    "\xe2\x9b\x84"      ,
    "\xe2\x9a\xa1"     ,
    "\xf0\x9f\x8c\x80" ,
    "\xf0\x9f\x8c\x81" ,
    "\xf0\x9f\x8c\x82" ,
    "\xf0\x9f\x8c\x83" ,
    "\xf0\x9f\x8c\x84" ,
    "\xf0\x9f\x8c\x85" ,
    "\xf0\x9f\x8c\x86" ,
    "\xf0\x9f\x8c\x87" ,
    "\xf0\x9f\x8c\x88" ,
    "\xe2\x9d\x84"     ,
    "\xe2\x9b\x85"     ,
    "\xf0\x9f\x8c\x89" ,
    "\xf0\x9f\x8c\x8a" ,
    "\xf0\x9f\x8c\x8b" ,
    "\xf0\x9f\x8c\x8c" ,
    "\xf0\x9f\x8c\x8f" ,
    "\xf0\x9f\x8c\x91" ,
    "\xf0\x9f\x8c\x94" ,
    "\xf0\x9f\x8c\x93" ,
    "\xf0\x9f\x8c\x99" ,
    "\xf0\x9f\x8c\x95" ,
    "\xf0\x9f\x8c\x9b" ,
    "\xf0\x9f\x8c\x9f" ,
    "\xf0\x9f\x8c\xa0" ,
    "\xf0\x9f\x95\x90" ,
    "\xf0\x9f\x95\x91" ,
    "\xf0\x9f\x95\x92" ,
    "\xf0\x9f\x95\x93" ,
    "\xf0\x9f\x95\x94" ,
    "\xf0\x9f\x95\x95" ,
    "\xf0\x9f\x95\x96" ,
    "\xf0\x9f\x95\x97" ,
    "\xf0\x9f\x95\x98" ,
    "\xf0\x9f\x95\x99" ,
    "\xf0\x9f\x95\x9a" ,
    "\xf0\x9f\x95\x9b" ,
    "\xe2\x8c\x9a"      ,
    "\xe2\x8c\x9b"      ,
    "\xe2\x8f\xb0" ,
    "\xe2\x8f\xb3" ,
    "\xe2\x99\x88" ,
    "\xe2\x99\x89" ,
    "\xe2\x99\x8a" ,
    "\xe2\x99\x8b" ,
    "\xe2\x99\x8c" ,
    "\xe2\x99\x8d" ,
    "\xe2\x99\x8e" ,
    "\xe2\x99\x8f" ,
    "\xe2\x99\x90" ,
    "\xe2\x99\x91" ,
    "\xe2\x99\x92" ,
    "\xe2\x99\x93" ,
    "\xe2\x9b\x8e" ,
    "\xf0\x9f\x8d\x80" ,
    "\xf0\x9f\x8c\xb7" ,
    "\xf0\x9f\x8c\xb1" ,
    "\xf0\x9f\x8d\x81" ,
    "\xf0\x9f\x8c\xb8" ,
    "\xf0\x9f\x8c\xb9" ,
    "\xf0\x9f\x8d\x82" ,
    "\xf0\x9f\x8d\x83" ,
    "\xf0\x9f\x8c\xba" ,
    "\xf0\x9f\x8c\xbb" ,
    "\xf0\x9f\x8c\xb4" ,
    "\xf0\x9f\x8c\xb5" ,
    "\xf0\x9f\x8c\xbe" ,
    "\xf0\x9f\x8c\xbd" ,
    "\xf0\x9f\x8d\x84" ,
    "\xf0\x9f\x8c\xb0" ,
    "\xf0\x9f\x8c\xbc" ,
    "\xf0\x9f\x8c\xbf" ,
    "\xf0\x9f\x8d\x92" ,
    "\xf0\x9f\x8d\x8c" ,
    "\xf0\x9f\x8d\x8e" ,
    "\xf0\x9f\x8d\x8a" ,
    "\xf0\x9f\x8d\x93" ,
    "\xf0\x9f\x8d\x89" ,
    "\xf0\x9f\x8d\x85" ,
    "\xf0\x9f\x8d\x86" ,
    "\xf0\x9f\x8d\x88" ,
    "\xf0\x9f\x8d\x8d" ,
    "\xf0\x9f\x8d\x87" ,
    "\xf0\x9f\x8d\x91" ,
    "\xf0\x9f\x8d\x8f" ,
    "\xf0\x9f\x91\x80" ,
    "\xf0\x9f\x91\x82" ,
    "\xf0\x9f\x91\x83" ,
    "\xf0\x9f\x91\x84" ,
    "\xf0\x9f\x91\x85" ,
    "\xf0\x9f\x92\x84" ,
    "\xf0\x9f\x92\x85" ,
    "\xf0\x9f\x92\x86" ,
    "\xf0\x9f\x92\x87" ,
    "\xf0\x9f\x92\x88" ,
    "\xf0\x9f\x91\xa4" ,
    "\xf0\x9f\x91\xa6" ,
    "\xf0\x9f\x91\xa7" ,
    "\xf0\x9f\x91\xa8" ,
    "\xf0\x9f\x91\xa9" ,
    "\xf0\x9f\x91\xaa" ,
    "\xf0\x9f\x91\xab" ,
    "\xf0\x9f\x91\xae" ,
    "\xf0\x9f\x91\xaf" ,
    "\xf0\x9f\x91\xb0" ,
    "\xf0\x9f\x91\xb1" ,
    "\xf0\x9f\x91\xb2" ,
    "\xf0\x9f\x91\xb3" ,
    "\xf0\x9f\x91\xb4" ,
    "\xf0\x9f\x91\xb5" ,
    "\xf0\x9f\x91\xb6" ,
    "\xf0\x9f\x91\xb7" ,
    "\xf0\x9f\x91\xb8" ,
    "\xf0\x9f\x91\xb9" ,
    "\xf0\x9f\x91\xba" ,
    "\xf0\x9f\x91\xbb" ,
    "\xf0\x9f\x91\xbc" ,
    "\xf0\x9f\x91\xbd" ,
    "\xf0\x9f\x91\xbe" ,
    "\xf0\x9f\x91\xbf" ,
    "\xf0\x9f\x92\x80" ,
    "\xf0\x9f\x92\x81" ,
    "\xf0\x9f\x92\x82" ,
    "\xf0\x9f\x92\x83" ,
    "\xf0\x9f\x90\x8c" ,
    "\xf0\x9f\x90\x8d" ,
    "\xf0\x9f\x90\x8e" ,
    "\xf0\x9f\x90\x94" ,
    "\xf0\x9f\x90\x97" ,
    "\xf0\x9f\x90\xab" ,
    "\xf0\x9f\x90\x98" ,
    "\xf0\x9f\x90\xa8" ,
    "\xf0\x9f\x90\x92" ,
    "\xf0\x9f\x90\x91" ,
    "\xf0\x9f\x90\x99" ,
    "\xf0\x9f\x90\x9a" ,
    "\xf0\x9f\x90\x9b" ,
    "\xf0\x9f\x90\x9c" ,
    "\xf0\x9f\x90\x9d" ,
    "\xf0\x9f\x90\x9e" ,
    "\xf0\x9f\x90\xa0" ,
    "\xf0\x9f\x90\xa1" ,
    "\xf0\x9f\x90\xa2" ,
    "\xf0\x9f\x90\xa4" ,
    "\xf0\x9f\x90\xa5" ,
    "\xf0\x9f\x90\xa6" ,
    "\xf0\x9f\x90\xa3" ,
    "\xf0\x9f\x90\xa7" ,
    "\xf0\x9f\x90\xa9" ,
    "\xf0\x9f\x90\x9f" ,
    "\xf0\x9f\x90\xac" ,
    "\xf0\x9f\x90\xad" ,
    "\xf0\x9f\x90\xaf" ,
    "\xf0\x9f\x90\xb1" ,
    "\xf0\x9f\x90\xb3" ,
    "\xf0\x9f\x90\xb4" ,
    "\xf0\x9f\x90\xb5" ,
    "\xf0\x9f\x90\xb6" ,
    "\xf0\x9f\x90\xb7" ,
    "\xf0\x9f\x90\xbb" ,
    "\xf0\x9f\x90\xb9" ,
    "\xf0\x9f\x90\xba" ,
    "\xf0\x9f\x90\xae" ,
    "\xf0\x9f\x90\xb0" ,
    "\xf0\x9f\x90\xb8" ,
    "\xf0\x9f\x90\xbe" ,
    "\xf0\x9f\x90\xb2" ,
    "\xf0\x9f\x90\xbc" ,
    "\xf0\x9f\x90\xbd" ,
    "\xf0\x9f\x98\xa0" ,
    "\xf0\x9f\x98\xa9" ,
    "\xf0\x9f\x98\xb2" ,
    "\xf0\x9f\x98\x9e" ,
    "\xf0\x9f\x98\xb5" ,
    "\xf0\x9f\x98\xb0" ,
    "\xf0\x9f\x98\x92" ,
    "\xf0\x9f\x98\x8d" ,
    "\xf0\x9f\x98\xa4" ,
    "\xf0\x9f\x98\x9c" ,
    "\xf0\x9f\x98\x9d" ,
    "\xf0\x9f\x98\x8b" ,
    "\xf0\x9f\x98\x98" ,
    "\xf0\x9f\x98\x9a" ,
    "\xf0\x9f\x98\xb7" ,
    "\xf0\x9f\x98\xb3" ,
    "\xf0\x9f\x98\x83" ,
    "\xf0\x9f\x98\x85" ,
    "\xf0\x9f\x98\x86" ,
    "\xf0\x9f\x98\x81" ,
    "\xf0\x9f\x98\x82" ,
    "\xf0\x9f\x98\x8a" ,
    "\xe2\x98\xba" ,
    "\xf0\x9f\x98\x84" ,
    "\xf0\x9f\x98\xa2" ,
    "\xf0\x9f\x98\xad" ,
    "\xf0\x9f\x98\xa8" ,
    "\xf0\x9f\x98\xa3" ,
    "\xf0\x9f\x98\xa1" ,
    "\xf0\x9f\x98\x8c" ,
    "\xf0\x9f\x98\x96" ,
    "\xf0\x9f\x98\x94" ,
    "\xf0\x9f\x98\xb1" ,
    "\xf0\x9f\x98\xaa" ,
    "\xf0\x9f\x98\x8f" ,
    "\xf0\x9f\x98\x93" ,
    "\xf0\x9f\x98\xa5" ,
    "\xf0\x9f\x98\xab" ,
    "\xf0\x9f\x98\x89" ,
    "\xf0\x9f\x98\xba" ,
    "\xf0\x9f\x98\xb8" ,
    "\xf0\x9f\x98\xb9" ,
    "\xf0\x9f\x98\xbd" ,
    "\xf0\x9f\x98\xbb" ,
    "\xf0\x9f\x98\xbf" ,
    "\xf0\x9f\x98\xbe" ,
    "\xf0\x9f\x98\xbc" ,
    "\xf0\x9f\x99\x80" ,
    "\xf0\x9f\x99\x85" ,
    "\xf0\x9f\x99\x86" ,
    "\xf0\x9f\x99\x87" ,
    "\xf0\x9f\x99\x88" ,
    "\xf0\x9f\x99\x8a" ,
    "\xf0\x9f\x99\x89" ,
    "\xf0\x9f\x99\x8b" ,
    "\xf0\x9f\x99\x8c" ,
    "\xf0\x9f\x99\x8d" ,
    "\xf0\x9f\x99\x8e" ,
    "\xf0\x9f\x99\x8f" ,
    "\xf0\x9f\x8f\xa0" ,
    "\xf0\x9f\x8f\xa1" ,
    "\xf0\x9f\x8f\xa2" ,
    "\xf0\x9f\x8f\xa3" ,
    "\xf0\x9f\x8f\xa5" ,
    "\xf0\x9f\x8f\xa6" ,
    "\xf0\x9f\x8f\xa7" ,
    "\xf0\x9f\x8f\xa8" ,
    "\xf0\x9f\x8f\xa9" ,
    "\xf0\x9f\x8f\xaa" ,
    "\xf0\x9f\x8f\xab" ,
    "\xe2\x9b\xaa" ,
    "\xe2\x9b\xb2" ,
    "\xf0\x9f\x8f\xac" ,
    "\xf0\x9f\x8f\xaf" ,
    "\xf0\x9f\x8f\xb0" ,
    "\xf0\x9f\x8f\xad" ,
    "\xe2\x9a\x93" ,
    "\xf0\x9f\x8f\xae" ,
    "\xf0\x9f\x97\xbb" ,
    "\xf0\x9f\x97\xbc" ,
    "\xf0\x9f\x97\xbd" ,
    "\xf0\x9f\x97\xbe" ,
    "\xf0\x9f\x97\xbf" ,
    "\xf0\x9f\x91\x9e" ,
    "\xf0\x9f\x91\x9f" ,
    "\xf0\x9f\x91\xa0" ,
    "\xf0\x9f\x91\xa1" ,
    "\xf0\x9f\x91\xa2" ,
    "\xf0\x9f\x91\xa3" ,
    "\xf0\x9f\x91\x93" ,
    "\xf0\x9f\x91\x95" ,
    "\xf0\x9f\x91\x96" ,
    "\xf0\x9f\x91\x91" ,
    "\xf0\x9f\x91\x94" ,
    "\xf0\x9f\x91\x92" ,
    "\xf0\x9f\x91\x97" ,
    "\xf0\x9f\x91\x98" ,
    "\xf0\x9f\x91\x99" ,
    "\xf0\x9f\x91\x9a" ,
    "\xf0\x9f\x91\x9b" ,
    "\xf0\x9f\x91\x9c" ,
    "\xf0\x9f\x91\x9d" ,
    "\xf0\x9f\x92\xb0" ,
    "\xf0\x9f\x92\xb1" ,
    "\xf0\x9f\x92\xb9" ,
    "\xf0\x9f\x92\xb2" ,
    "\xf0\x9f\x92\xb3" ,
    "\xf0\x9f\x92\xb4" ,
    "\xf0\x9f\x92\xb5" ,
    "\xf0\x9f\x92\xb8" ,
    "\xf0\x9f\x87\xa8\xf0\x9f\x87\xb3" ,
    "\xf0\x9f\x87\xa9\xf0\x9f\x87\xaa" ,
    "\xf0\x9f\x87\xaa\xf0\x9f\x87\xb8" ,
    "\xf0\x9f\x87\xab\xf0\x9f\x87\xb7" ,
    "\xf0\x9f\x87\xac\xf0\x9f\x87\xa7" ,
    "\xf0\x9f\x87\xae\xf0\x9f\x87\xb9" ,
    "\xf0\x9f\x87\xaf\xf0\x9f\x87\xb5" ,
    "\xf0\x9f\x87\xb0\xf0\x9f\x87\xb7" ,
    "\xf0\x9f\x87\xb7\xf0\x9f\x87\xba" ,
    "\xf0\x9f\x87\xba\xf0\x9f\x87\xb8" ,
    "\xf0\x9f\x94\xa5" ,
    "\xf0\x9f\x94\xa6" ,
    "\xf0\x9f\x94\xa7" ,
    "\xf0\x9f\x94\xa8" ,
    "\xf0\x9f\x94\xa9" ,
    "\xf0\x9f\x94\xaa" ,
    "\xf0\x9f\x94\xab" ,
    "\xf0\x9f\x94\xae" ,
    "\xf0\x9f\x94\xaf" ,
    "\xf0\x9f\x94\xb0" ,
    "\xf0\x9f\x94\xb1" ,
    "\xf0\x9f\x92\x89" ,
    "\xf0\x9f\x92\x8a" ,
    "\xf0\x9f\x85\xb0" ,
    "\xf0\x9f\x85\xb1" ,
    "\xf0\x9f\x86\x8e" ,
    "\xf0\x9f\x85\xbe" ,
    "\xf0\x9f\x8e\x80" ,
    "\xf0\x9f\x8e\x81" ,
    "\xf0\x9f\x8e\x82" ,
    "\xf0\x9f\x8e\x84" ,
    "\xf0\x9f\x8e\x85" ,
    "\xf0\x9f\x8e\x8c" ,
    "\xf0\x9f\x8e\x86" ,
    "\xf0\x9f\x8e\x88" ,
    "\xf0\x9f\x8e\x89" ,
    "\xf0\x9f\x8e\x8d" ,
    "\xf0\x9f\x8e\x8e" ,
    "\xf0\x9f\x8e\x93" ,
    "\xf0\x9f\x8e\x92" ,
    "\xf0\x9f\x8e\x8f" ,
    "\xf0\x9f\x8e\x87" ,
    "\xf0\x9f\x8e\x90" ,
    "\xf0\x9f\x8e\x83" ,
    "\xf0\x9f\x8e\x8a" ,
    "\xf0\x9f\x8e\x8b" ,
    "\xf0\x9f\x8e\x91" ,
    "\xf0\x9f\x93\x9f" ,
    "\xe2\x98\x8e" ,
    "\xf0\x9f\x93\x9e" ,
    "\xf0\x9f\x93\xb1" ,
    "\xf0\x9f\x93\xb2" ,
    "\xf0\x9f\x93\x9d" ,
    "\xf0\x9f\x93\xa0" ,
    "\xe2\x9c\x89" ,
    "\xf0\x9f\x93\xa8" ,
    "\xf0\x9f\x93\xa9" ,
    "\xf0\x9f\x93\xaa" ,
    "\xf0\x9f\x93\xab" ,
    "\xf0\x9f\x93\xae" ,
    "\xf0\x9f\x93\xb0" ,
    "\xf0\x9f\x93\xa2" ,
    "\xf0\x9f\x93\xa3" ,
    "\xf0\x9f\x93\xa1" ,
    "\xf0\x9f\x93\xa4" ,
    "\xf0\x9f\x93\xa5" ,
    "\xf0\x9f\x93\xa6" ,
    "\xf0\x9f\x93\xa7" ,
    "\xf0\x9f\x94\xa0" ,
    "\xf0\x9f\x94\xa1" ,
    "\xf0\x9f\x94\xa2" ,
    "\xf0\x9f\x94\xa3" ,
    "\xf0\x9f\x94\xa4" ,
    "\xe2\x9c\x92" ,
    "\xf0\x9f\x92\xba" ,
    "\xf0\x9f\x92\xbb" ,
    "\xe2\x9c\x8f" ,
    "\xf0\x9f\x93\x8e" ,
    "\xf0\x9f\x92\xbc" ,
    "\xf0\x9f\x92\xbd" ,
    "\xf0\x9f\x92\xbe" ,
    "\xf0\x9f\x92\xbf" ,
    "\xf0\x9f\x93\x80" ,
    "\xe2\x9c\x82" ,
    "\xf0\x9f\x93\x8d" ,
    "\xf0\x9f\x93\x83" ,
    "\xf0\x9f\x93\x84" ,
    "\xf0\x9f\x93\x85" ,
    "\xf0\x9f\x93\x81" ,
    "\xf0\x9f\x93\x82" ,
    "\xf0\x9f\x93\x93" ,
    "\xf0\x9f\x93\x96" ,
    "\xf0\x9f\x93\x94" ,
    "\xf0\x9f\x93\x95" ,
    "\xf0\x9f\x93\x97" ,
    "\xf0\x9f\x93\x98" ,
    "\xf0\x9f\x93\x99" ,
    "\xf0\x9f\x93\x9a" ,
    "\xf0\x9f\x93\x9b" ,
    "\xf0\x9f\x93\x9c" ,
    "\xf0\x9f\x93\x8b" ,
    "\xf0\x9f\x93\x86" ,
    "\xf0\x9f\x93\x8a" ,
    "\xf0\x9f\x93\x88" ,
    "\xf0\x9f\x93\x89" ,
    "\xf0\x9f\x93\x87" ,
    "\xf0\x9f\x93\x8c" ,
    "\xf0\x9f\x93\x92" ,
    "\xf0\x9f\x93\x8f" ,
    "\xf0\x9f\x93\x90" ,
    "\xf0\x9f\x93\x91" ,
    "\xf0\x9f\x8e\xbd" ,
    "\xe2\x9a\xbe" ,
    "\xe2\x9b\xb3" ,
    "\xf0\x9f\x8e\xbe" ,
    "\xe2\x9a\xbd" ,
    "\xf0\x9f\x8e\xbf" ,
    "\xf0\x9f\x8f\x80" ,
    "\xf0\x9f\x8f\x81" ,
    "\xf0\x9f\x8f\x82" ,
    "\xf0\x9f\x8f\x83" ,
    "\xf0\x9f\x8f\x84" ,
    "\xf0\x9f\x8f\x86" ,
    "\xf0\x9f\x8f\x88" ,
    "\xf0\x9f\x8f\x8a" ,
    "\xf0\x9f\x9a\x83" ,
    "\xf0\x9f\x9a\x87" ,
    "\xe2\x93\x82" ,
    "\xf0\x9f\x9a\x84" ,
    "\xf0\x9f\x9a\x85" ,
    "\xf0\x9f\x9a\x97" ,
    "\xf0\x9f\x9a\x99" ,
    "\xf0\x9f\x9a\x8c" ,
    "\xf0\x9f\x9a\x8f" ,
    "\xf0\x9f\x9a\xa2" ,
    "\xe2\x9c\x88" ,
    "\xe2\x9b\xb5" ,
    "\xf0\x9f\x9a\x89" ,
    "\xf0\x9f\x9a\x80" ,
    "\xf0\x9f\x9a\xa4" ,
    "\xf0\x9f\x9a\x95" ,
    "\xf0\x9f\x9a\x9a" ,
    "\xf0\x9f\x9a\x92" ,
    "\xf0\x9f\x9a\x91" ,
    "\xf0\x9f\x9a\x93" ,
    "\xe2\x9b\xbd" ,
    "\xf0\x9f\x85\xbf" ,
    "\xf0\x9f\x9a\xa5" ,
    "\xf0\x9f\x9a\xa7" ,
    "\xf0\x9f\x9a\xa8" ,
    "\xe2\x99\xa8" ,
    "\xe2\x9b\xba" ,
    "\xf0\x9f\x8e\xa0" ,
    "\xf0\x9f\x8e\xa1" ,
    "\xf0\x9f\x8e\xa2" ,
    "\xf0\x9f\x8e\xa3" ,
    "\xf0\x9f\x8e\xa4" ,
    "\xf0\x9f\x8e\xa5" ,
    "\xf0\x9f\x8e\xa6" ,
    "\xf0\x9f\x8e\xa7" ,
    "\xf0\x9f\x8e\xa8" ,
    "\xf0\x9f\x8e\xa9" ,
    "\xf0\x9f\x8e\xaa" ,
    "\xf0\x9f\x8e\xab" ,
    "\xf0\x9f\x8e\xac" ,
    "\xf0\x9f\x8e\xad" ,
    "\xf0\x9f\x8e\xae" ,
    "\xf0\x9f\x80\x84" ,
    "\xf0\x9f\x8e\xaf" ,
    "\xf0\x9f\x8e\xb0" ,
    "\xf0\x9f\x8e\xb1" ,
    "\xf0\x9f\x8e\xb2" ,
    "\xf0\x9f\x8e\xb3" ,
    "\xf0\x9f\x8e\xb4" ,
    "\xf0\x9f\x83\x8f" ,
    "\xf0\x9f\x8e\xb5" ,
    "\xf0\x9f\x8e\xb6" ,
    "\xf0\x9f\x8e\xb7" ,
    "\xf0\x9f\x8e\xb8" ,
    "\xf0\x9f\x8e\xb9" ,
    "\xf0\x9f\x8e\xba" ,
    "\xf0\x9f\x8e\xbb" ,
    "\xf0\x9f\x8e\xbc" ,
    "\xe3\x80\xbd" ,
    "\xf0\x9f\x93\xb7" ,
    "\xf0\x9f\x93\xb9" ,
    "\xf0\x9f\x93\xba" ,
    "\xf0\x9f\x93\xbb" ,
    "\xf0\x9f\x93\xbc" ,
    "\xf0\x9f\x92\x8b" ,
    "\xf0\x9f\x92\x8c" ,
    "\xf0\x9f\x92\x8d" ,
    "\xf0\x9f\x92\x8e" ,
    "\xf0\x9f\x92\x8f" ,
    "\xf0\x9f\x92\x90" ,
    "\xf0\x9f\x92\x91" ,
    "\xf0\x9f\x92\x92" ,
    "\xf0\x9f\x94\x9e" ,
    "\xc2\xa9" ,
    "\xc2\xae" ,
    "\xe2\x84\xa2" ,
    "\xe2\x84\xb9" ,
    "#\xe2\x83\xa3" ,
    "1\xe2\x83\xa3" ,
    "2\xe2\x83\xa3" ,
    "3\xe2\x83\xa3" ,
    "4\xe2\x83\xa3" ,
    "5\xe2\x83\xa3" ,
    "6\xe2\x83\xa3" ,
    "7\xe2\x83\xa3" ,
    "8\xe2\x83\xa3" ,
    "9\xe2\x83\xa3" ,
    "0\xe2\x83\xa3" ,
    "\xf0\x9f\x94\x9f" ,
    "\xf0\x9f\x93\xb6" ,
    "\xf0\x9f\x93\xb3" ,
    "\xf0\x9f\x93\xb4" ,
    "\xf0\x9f\x8d\x94" ,
    "\xf0\x9f\x8d\x99" ,
    "\xf0\x9f\x8d\xb0" ,
    "\xf0\x9f\x8d\x9c" ,
    "\xf0\x9f\x8d\x9e" ,
    "\xf0\x9f\x8d\xb3" ,
    "\xf0\x9f\x8d\xa6" ,
    "\xf0\x9f\x8d\x9f" ,
    "\xf0\x9f\x8d\xa1" ,
    "\xf0\x9f\x8d\x98" ,
    "\xf0\x9f\x8d\x9a" ,
    "\xf0\x9f\x8d\x9d" ,
    "\xf0\x9f\x8d\x9b" ,
    "\xf0\x9f\x8d\xa2" ,
    "\xf0\x9f\x8d\xa3" ,
    "\xf0\x9f\x8d\xb1" ,
    "\xf0\x9f\x8d\xb2" ,
    "\xf0\x9f\x8d\xa7" ,
    "\xf0\x9f\x8d\x96" ,
    "\xf0\x9f\x8d\xa5" ,
    "\xf0\x9f\x8d\xa0" ,
    "\xf0\x9f\x8d\x95" ,
    "\xf0\x9f\x8d\x97" ,
    "\xf0\x9f\x8d\xa8" ,
    "\xf0\x9f\x8d\xa9" ,
    "\xf0\x9f\x8d\xaa" ,
    "\xf0\x9f\x8d\xab" ,
    "\xf0\x9f\x8d\xac" ,
    "\xf0\x9f\x8d\xad" ,
    "\xf0\x9f\x8d\xae" ,
    "\xf0\x9f\x8d\xaf" ,
    "\xf0\x9f\x8d\xa4" ,
    "\xf0\x9f\x8d\xb4" ,
    "\xe2\x98\x95" ,
    "\xf0\x9f\x8d\xb8" ,
    "\xf0\x9f\x8d\xba" ,
    "\xf0\x9f\x8d\xb5" ,
    "\xf0\x9f\x8d\xb6" ,
    "\xf0\x9f\x8d\xb7" ,
    "\xf0\x9f\x8d\xbb" ,
    "\xf0\x9f\x8d\xb9" ,
    "\xe2\x86\x97" ,
    "\xe2\x86\x98" ,
    "\xe2\x86\x96" ,
    "\xe2\x86\x99" ,
    "\xe2\xa4\xb4" ,
    "\xe2\xa4\xb5" ,
    "\xe2\x86\x94" ,
    "\xe2\x86\x95" ,
    "\xe2\xac\x86" ,
    "\xe2\xac\x87" ,
    "\xe2\x9e\xa1" ,
    "\xe2\xac\x85" ,
    "\xe2\x96\xb6" ,
    "\xe2\x97\x80" ,
    "\xe2\x8f\xa9" ,
    "\xe2\x8f\xaa" ,
    "\xe2\x8f\xab" ,
    "\xe2\x8f\xac" ,
    "\xf0\x9f\x94\xba" ,
    "\xf0\x9f\x94\xbb" ,
    "\xf0\x9f\x94\xbc" ,
    "\xf0\x9f\x94\xbd" ,
    "\xe2\xad\x95" ,
    "\xe2\x9d\x8c" ,
    "\xe2\x9d\x8e" ,
    "\xe2\x9d\x97" ,
    "\xe2\x81\x89" ,
    "\xe2\x80\xbc" ,
    "\xe2\x9d\x93" ,
    "\xe2\x9d\x94" ,
    "\xe2\x9d\x95" ,
    "\xe3\x80\xb0" ,
    "\xe2\x9e\xb0" ,
    "\xe2\x9e\xbf" ,
    "\xe2\x9d\xa4" ,
    "\xf0\x9f\x92\x93" ,
    "\xf0\x9f\x92\x94" ,
    "\xf0\x9f\x92\x95" ,
    "\xf0\x9f\x92\x96" ,
    "\xf0\x9f\x92\x97" ,
    "\xf0\x9f\x92\x98" ,
    "\xf0\x9f\x92\x99" ,
    "\xf0\x9f\x92\x9a" ,
    "\xf0\x9f\x92\x9b" ,
    "\xf0\x9f\x92\x9c" ,
    "\xf0\x9f\x92\x9d" ,
    "\xf0\x9f\x92\x9e" ,
    "\xf0\x9f\x92\x9f" ,
    "\xe2\x99\xa5" ,
    "\xe2\x99\xa0" ,
    "\xe2\x99\xa6" ,
    "\xe2\x99\xa3" ,
    "\xf0\x9f\x9a\xac" ,
    "\xf0\x9f\x9a\xad" ,
    "\xe2\x99\xbf" ,
    "\xf0\x9f\x9a\xa9" ,
    "\xe2\x9a\xa0" ,
    "\xe2\x9b\x94" ,
    "\xe2\x99\xbb" ,
    "\xf0\x9f\x9a\xb2" ,
    "\xf0\x9f\x9a\xb6" ,
    "\xf0\x9f\x9a\xb9" ,
    "\xf0\x9f\x9a\xba" ,
    "\xf0\x9f\x9b\x80" ,
    "\xf0\x9f\x9a\xbb" ,
    "\xf0\x9f\x9a\xbd" ,
    "\xf0\x9f\x9a\xbe" ,
    "\xf0\x9f\x9a\xbc" ,
    "\xf0\x9f\x9a\xaa" ,
    "\xf0\x9f\x9a\xab" ,
    "\xe2\x9c\x94" ,
    "\xf0\x9f\x86\x91" ,
    "\xf0\x9f\x86\x92" ,
    "\xf0\x9f\x86\x93" ,
    "\xf0\x9f\x86\x94" ,
    "\xf0\x9f\x86\x95" ,
    "\xf0\x9f\x86\x96" ,
    "\xf0\x9f\x86\x97" ,
    "\xf0\x9f\x86\x98" ,
    "\xf0\x9f\x86\x99" ,
    "\xf0\x9f\x86\x9a" ,
    "\xf0\x9f\x88\x81" ,
    "\xf0\x9f\x88\x82" ,
    "\xf0\x9f\x88\xb2" ,
    "\xf0\x9f\x88\xb3" ,
    "\xf0\x9f\x88\xb4" ,
    "\xf0\x9f\x88\xb5" ,
    "\xf0\x9f\x88\xb6" ,
    "\xf0\x9f\x88\x9a" ,
    "\xf0\x9f\x88\xb7" ,
    "\xf0\x9f\x88\xb8" ,
    "\xf0\x9f\x88\xb9" ,
    "\xf0\x9f\x88\xaf" ,
    "\xf0\x9f\x88\xba" ,
    "\xe3\x8a\x99" ,
    "\xe3\x8a\x97" ,
    "\xf0\x9f\x89\x90" ,
    "\xf0\x9f\x89\x91" ,
    "\xe2\x9e\x95" ,
    "\xe2\x9e\x96" ,
    "\xe2\x9c\x96" ,
    "\xe2\x9e\x97" ,
    "\xf0\x9f\x92\xa0" ,
    "\xf0\x9f\x92\xa1" ,
    "\xf0\x9f\x92\xa2" ,
    "\xf0\x9f\x92\xa3" ,
    "\xf0\x9f\x92\xa4" ,
    "\xf0\x9f\x92\xa5" ,
    "\xf0\x9f\x92\xa6" ,
    "\xf0\x9f\x92\xa7" ,
    "\xf0\x9f\x92\xa8" ,
    "\xf0\x9f\x92\xa9" ,
    "\xf0\x9f\x92\xaa" ,
    "\xf0\x9f\x92\xab" ,
    "\xf0\x9f\x92\xac" ,
    "\xe2\x9c\xa8" ,
    "\xe2\x9c\xb4" ,
    "\xe2\x9c\xb3" ,
    "\xe2\x9a\xaa" ,
    "\xe2\x9a\xab" ,
    "\xf0\x9f\x94\xb4" ,
    "\xf0\x9f\x94\xb5" ,
    "\xf0\x9f\x94\xb2" ,
    "\xf0\x9f\x94\xb3" ,
    "\xe2\xad\x90" ,
    "\xe2\xac\x9c" ,
    "\xe2\xac\x9b" ,
    "\xe2\x96\xab" ,
    "\xe2\x96\xaa" ,
    "\xe2\x97\xbd" ,
    "\xe2\x97\xbe" ,
    "\xe2\x97\xbb" ,
    "\xe2\x97\xbc" ,
    "\xf0\x9f\x94\xb6" ,
    "\xf0\x9f\x94\xb7" ,
    "\xf0\x9f\x94\xb8" ,
    "\xf0\x9f\x94\xb9" ,
    "\xe2\x9d\x87" ,
    "\xf0\x9f\x92\xae" ,
    "\xf0\x9f\x92\xaf" ,
    "\xe2\x86\xa9" ,
    "\xe2\x86\xaa" ,
    "\xf0\x9f\x94\x83" ,
    "\xf0\x9f\x94\x8a" ,
    "\xf0\x9f\x94\x8b" ,
    "\xf0\x9f\x94\x8c" ,
    "\xf0\x9f\x94\x8d" ,
    "\xf0\x9f\x94\x8e" ,
    "\xf0\x9f\x94\x92" ,
    "\xf0\x9f\x94\x93" ,
    "\xf0\x9f\x94\x8f" ,
    "\xf0\x9f\x94\x90" ,
    "\xf0\x9f\x94\x91" ,
    "\xf0\x9f\x94\x94" ,
    "\xe2\x98\x91" ,
    "\xf0\x9f\x94\x98" ,
    "\xf0\x9f\x94\x96" ,
    "\xf0\x9f\x94\x97" ,
    "\xf0\x9f\x94\x99" ,
    "\xf0\x9f\x94\x9a" ,
    "\xf0\x9f\x94\x9b" ,
    "\xf0\x9f\x94\x9c" ,
    "\xf0\x9f\x94\x9d" ,
    "\xe2\x80\x83" ,
    "\xe2\x80\x82" ,
    "\xe2\x80\x85" ,
    "\xe2\x9c\x85" ,
    "\xe2\x9c\x8a" ,
    "\xe2\x9c\x8b" ,
    "\xe2\x9c\x8c" ,
    "\xf0\x9f\x91\x8a" ,
    "\xf0\x9f\x91\x8d" ,
    "\xe2\x98\x9d" ,
    "\xf0\x9f\x91\x86" ,
    "\xf0\x9f\x91\x87" ,
    "\xf0\x9f\x91\x88" ,
    "\xf0\x9f\x91\x89" ,
    "\xf0\x9f\x91\x8b" ,
    "\xf0\x9f\x91\x8f" ,
    "\xf0\x9f\x91\x8c" ,
    "\xf0\x9f\x91\x8e" ,
    "\xf0\x9f\x91\x90"
};



static int _calcCharCount(const char * pszText)
{
    int n = 0;
    char ch = 0;
    while ((ch = *pszText))
    {
        CC_BREAK_IF(! ch);
        
        if (0x80 != (0xC0 & ch))
        {
            ++n;
        }
        ++pszText;
    }
    return n;
}

KKTextFieldTTF * KKTextFieldTTF::textFieldWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
{
    KKTextFieldTTF *pRet = new KKTextFieldTTF();
    if(pRet && pRet->initWithPlaceHolder("", dimensions, alignment, fontName, fontSize))
    {
		pRet->m_isNumber = false;
		pRet->m_numberCount = 0;
		pRet->m_banjiaoCountMax = 0;
		pRet->m_banjiaoCount = 0;
        pRet->autorelease();
        if (placeholder)
        {
            pRet->setPlaceHolder(placeholder);
        }
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool KKTextFieldTTF::initWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
{
    setEmojiRefuse(false);
    if (placeholder)
    {

        CC_SAFE_DELETE(m_pPlaceHolder);
        m_pPlaceHolder = new std::string(placeholder);
    }
    return CCLabelTTF::initWithString(m_pPlaceHolder->c_str(), dimensions, alignment, fontName, fontSize);
}


void KKTextFieldTTF::setString(const char *text)
{
    CC_SAFE_DELETE(m_pInputText);
    
    m_banjiaoCount = 0;
    
    int addtextcount = 0;
	int scount = 0;
    int len = strlen(text);
    bool bchange = false;
	for (int i = 0; i < strlen(text);)
	{
        
		int zengfu = 0;
		if (text[addtextcount] & 0x80)
		{//中文
			addtextcount += 3;
			zengfu = 3;
			i+=3;
			scount++;
		}
		else
		{//半角
			addtextcount++;
			zengfu = 1;
			i++;
			scount++;
		}
        
		if (m_banjiaoCount + scount >= m_banjiaoCountMax)
		{
			len = addtextcount-zengfu;
            bchange = true;
            
		}
	}
    
    m_banjiaoCount = scount;
    
    char tmpstr[51];
    if (bchange)
    {
        strncpy(tmpstr, text, len);
        tmpstr[len] = '\0';
    }
    
    
    
    if (bchange)
    {
        m_pInputText = new std::string(tmpstr);
    }
    else if (text)
    {
        m_pInputText = new std::string(text);
    }
    else
    {
        m_pInputText = new std::string;
    }
    
    // if there is no input text, display placeholder instead
    if (! m_pInputText->length())
    {
        CCLabelTTF::setString(m_pPlaceHolder->c_str());
    }
    else
    {
        CCLabelTTF::setString(m_pInputText->c_str());
    }
    m_nCharCount = _calcCharCount(m_pInputText->c_str());
}


void KKTextFieldTTF::insertText(const char * text, int len)
{
	if (m_banjiaoCount > m_banjiaoCountMax)
		return;
	
	
	int addtextcount = 0;
	int scount = 0;
	for (int i = 0; i < strlen(text);)
	{	

		int zengfu = 0;
		if (text[addtextcount] & 0x80)
		{//中文
			addtextcount += 3;
			zengfu = 3;
			i+=3;
			scount++;
		}
		else 
		{//半角
			addtextcount++;
			zengfu = 1;
			i++;
			scount++;
		}

		if (m_banjiaoCount + scount >= m_banjiaoCountMax)
		{
			len = addtextcount-zengfu;
		}

	}


    //kevin0824
	if (m_isNumber)//1，只取第一个字符作为数字 2,只允许一共有9个数字
	{
		int length = strlen(text);
		if (length > 1)
		{
			int itext = 0;itext = 0;
		}
		if (m_pInputText->size() > m_numberCount)
			return;
		int sub;
		for (int i = 0; i < 1; i++)
		{
			sub = (int)text[i]-48;
			if (sub < 0 || sub > 9)
			{
				return;
			}
		}
	}



    if (getEmojiRefuse())
    {
        bool isEmoji = false;
        for (int i = 0; i < 700; i++)
        {
            if (strcmp(EMOJIARRAY[i].c_str(), text)==0)
            {
                isEmoji = true;
                break;
            }
        }
        
        if (isEmoji)
		{
			LangManager::msgShow("COM637");
            return;
		}
    }

    
    //
    std::string sInsert(text, len);
    
    // insert \n means input end
    int nPos = sInsert.find('\n');
    if ((int)sInsert.npos != nPos)
    {
        len = nPos;
        sInsert.erase(nPos);
    }
    
    if (len > 0)
    {
        if (m_pDelegate && m_pDelegate->onTextFieldInsertText(this, sInsert.c_str(), len))
        {
            // delegate doesn't want insert text
            return;
        }
        
        m_nCharCount += _calcCharCount(sInsert.c_str());
        std::string sText(*m_pInputText);
        sText.append(sInsert);
        setString(sText.c_str());

		for (int valueIndex = 0; valueIndex < sInsert.size();)
		{
			if (sInsert[valueIndex] & 0x80)
			{//中文
				valueIndex += 3;
				m_banjiaoCount++;
			}
			else 
			{//半角
				valueIndex++;
				m_banjiaoCount++;
			}
		}
    }

    if ((int)sInsert.npos == nPos) {
        return;
    }
    
    // '\n' has inserted,  let delegate process first
    if (m_pDelegate && m_pDelegate->onTextFieldInsertText(this, "\n", 1))
    {
        return;
    }
    
    // if delegate hasn't process, detach with ime as default
    detachWithIME();
}

void KKTextFieldTTF::deleteBackward()
{
    int nStrLen = m_pInputText->length();
    if (! nStrLen)
    {
        // there is no string
        return;
    }

    // get the delete byte number
    int nDeleteLen = 1;    // default, erase 1 byte

    while(0x80 == (0xC0 & m_pInputText->at(nStrLen - nDeleteLen)))
    {
        ++nDeleteLen;
    }

	m_banjiaoCount --;
	if (m_banjiaoCount < 0)
		m_banjiaoCount = 0;

    if (m_pDelegate && m_pDelegate->onTextFieldDeleteBackward(this, m_pInputText->c_str() + nStrLen - nDeleteLen, nDeleteLen))
    {
        // delegate don't wan't delete backward
        return;
    }

    // if delete all text, show space holder string
    if (nStrLen <= nDeleteLen)
    {
        CC_SAFE_DELETE(m_pInputText);
        m_pInputText = new std::string;
        m_nCharCount = 0;
        CCLabelTTF::setString(m_pPlaceHolder->c_str());
        return;
    }

    // set new input text
    std::string sText(m_pInputText->c_str(), nStrLen - nDeleteLen);
    setString(sText.c_str());
}

//CC_PROPERTY(bool, _emojiRefuse, EmojiRefuse);
void KKTextFieldTTF::setEmojiRefuse(bool value)
{
    _emojiRefuse = value;
}

bool KKTextFieldTTF::getEmojiRefuse()
{
    return _emojiRefuse;
}

///////////////////////////////////////////////////////////////////////

static CCRect getRect(CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}

//////////////////////////////////////////////////////////////////////////
// implement KeyboardNotificationLayer
//////////////////////////////////////////////////////////////////////////

KeyboardNotificationLayer::KeyboardNotificationLayer()
: m_pTrackNode(0),m_pUpMoveNode(0)
{
    setIsTouchEnabled(true);
	m_UpMoveDis = 0.0f;
    m_pri = -1500;
	setEmptyStr(false);
	setIsCanBeTouched(true);
    setEmojiRefuse(false);
	m_frame = CCSizeMake(POSX(600), POSX(60));
	m_isNumber = false;
	m_numberCount = 0;
	m_banjiaoCountMax = 50;
}

void KeyboardNotificationLayer::setUp(CCNode * pUpMoveNode, float UpMoveDis)
{
	m_pUpMoveNode = pUpMoveNode;
	m_UpMoveDis = UpMoveDis;
}

void KeyboardNotificationLayer::registerWithTouchDispatcher()
{
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, m_pri, false);
}

void KeyboardNotificationLayer::keyboardWillHide(CCIMEKeyboardNotificationInfo& info)
{
	if (getEmptyStr())
		setString("");
    if (m_pUpMoveNode)
	{
		//oldPos = m_pUpMoveNode->getPosition();
		m_pUpMoveNode->runAction(CCMoveTo::actionWithDuration(0.2f, ccp(0, 0)));
	}
/*
	CCNode* p = this->getChildByTag(1000);
	if (p)
	{
		p->removeFromParentAndCleanup(true);
	}
 */


}


void KeyboardNotificationLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    CCLOG("TextInputTest:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
        info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);

    if (! m_pTrackNode)
    {
        return;
    }

    CCRect rectTracked = getRect(m_pTrackNode);
    CCLOG("TextInputTest:trackingNodeAt(origin:%f,%f, size:%f,%f)",
        rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);

    // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
    if (! CCRect::CCRectIntersectsRect(rectTracked, info.end))
    {
        return;
    }

    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    float adjustVert = CCRect::CCRectGetMaxY(info.end) - CCRect::CCRectGetMinY(rectTracked);
    CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);

    // move all the children node of KeyboardNotificationLayer
    CCArray * children = getChildren();
    CCNode * node = 0;
    int count = children->count();
    CCPoint pos;
    for (int i = 0; i < count; ++i)
    {
        node = (CCNode*)children->objectAtIndex(i);
        pos = node->getPosition();
        pos.y += adjustVert;
       // node->setPosition(pos);kevinchange
    }


}

// CCLayer function

bool KeyboardNotificationLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!getIsCanBeTouched()) // LH20120815
	{
		return false;
	}
    CCLOG("++++++++++++++++++++++++++++++++++++++++++++");
    m_beginPos = pTouch->locationInView(pTouch->view());	
    m_beginPos = CCDirector::sharedDirector()->convertToGL(m_beginPos);
	//
	CCRect rect;
    CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);

    rect = getRect(m_pTrackNode);
    CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
        rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

    this->onClickTrackNode(CCRect::CCRectContainsPoint(rect, point));
    CCLOG("----------------------------------");


    return true;
}

void KeyboardNotificationLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	return;

    if (! m_pTrackNode)
    {
        return;
    }
    
    CCPoint endPos = pTouch->locationInView(pTouch->view());	
    endPos = CCDirector::sharedDirector()->convertToGL(endPos);

    float delta = 5.0f;
    if (::abs(endPos.x - m_beginPos.x) > delta
        || ::abs(endPos.y - m_beginPos.y) > delta)
    {
        // not click
        m_beginPos.x = m_beginPos.y = -1;
        return;
    }

    // decide the trackNode is clicked.
    CCRect rect;
    CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);

    rect = getRect(m_pTrackNode);
    CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
        rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

    this->onClickTrackNode(CCRect::CCRectContainsPoint(rect, point));
    CCLOG("----------------------------------");
}

//CC_PROPERTY(bool, emptyStr, EmptyStr);
void KeyboardNotificationLayer::setEmptyStr(bool value)
{
	emptyStr = value;
}

bool KeyboardNotificationLayer::getEmptyStr()
{
	return emptyStr;
}

//////////////////////////////////////////////////////////////////////////
// implement TextFieldTTF
//////////////////////////////////////////////////////////////////////////
TextFieldTTF::TextFieldTTF()
{
	m_s = "";
}

void TextFieldTTF::setFieldSize(CCSize size)
{
	if (this->getChildByTag(1000))
	{
		this->getChildByTag(1000)->setContentSize(size);
	}
	this->setContentSize(size);
}

std::string TextFieldTTF::subtitle()
{
    return "TextFieldTTF with default behavior test";
}

void TextFieldTTF::onClickTrackNode(bool bClicked)
{
    KKTextFieldTTF * pTextField = (KKTextFieldTTF*)m_pTrackNode;
    if (bClicked)
    {
        // TextFieldTTFTest be clicked
        CCLOG("TextFieldTTF:KKTextFieldTTF attachWithIME");
        pTextField->attachWithIME();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if (m_pUpMoveNode)
        {
            oldPos = m_pUpMoveNode->getPosition();
            m_pUpMoveNode->runAction(CCMoveTo::actionWithDuration(0.2f, ccp(m_pUpMoveNode->getPosition().x, m_UpMoveDis)));
        }
#endif
    }
    else
    {
        // TextFieldTTFTest not be clicked
        CCLOG("TextFieldTTF:KKTextFieldTTF detachWithIME");
   //     pTextField->detachWithIME();
    }
}



void KeyboardNotificationLayer::setString(std::string s)
{
	if (m_pTrackNode)
		((KKTextFieldTTF*)m_pTrackNode)->setString(s.c_str());

	m_s = s;
}

void KeyboardNotificationLayer::setEmojiRefuse(bool value)
{
    m_bEmojiRefuse = value;
}

void TextFieldTTF::onEnter()
{
    KeyboardNotificationLayer::onEnter();

    // add KKTextFieldTTF
    CCSize s = CCDirector::sharedDirector()->getWinSize();
	/*
    KKTextFieldTTF * pTextField = KKTextFieldTTF::textFieldWithPlaceHolder(ValuesUtil::Instance()->getString("INPUT001").c_str(),//"<input player name>"
        "Arial", 20);
    addChild(pTextField);
	*/

    
    if (this->getChildByTag(1000))
        return;
    
    KKTextFieldTTF *pTextField = KKTextFieldTTF::textFieldWithPlaceHolder(ValuesUtil::Instance()->getString("INPUT001").c_str(),
		m_frame,
		CCTextAlignmentLeft,
		"Arial",
		POSX(20));
	if(pTextField)
	{
		pTextField->m_isNumber = m_isNumber;
		pTextField->m_numberCount = m_numberCount;
		pTextField->m_banjiaoCountMax = m_banjiaoCountMax;
		if (m_s.size() > 0)
			pTextField->setString(m_s.c_str());
	//	pTextField->setContentSize(CCSizeMake((380), (40)));
		//pTextField->setAnchorPoint(CCPointZero);
		//pTextField->setPosition(ccp(226, 376));
		//pTextField->attachWithIME();

		this->addChild(pTextField, 0, 1000);
        
        pTextField->setEmojiRefuse(m_bEmojiRefuse);
		//pTextField->setColor(ccc3(22,22,222));
	}



#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)	
	// on android, KKTextFieldTTF cannot auto adjust its position when soft-keyboard pop up
	// so we had to set a higher position to make it visable
	//pTextField->setPosition(ccp(s.width / 2, s.height/2 + 50));
#else
//	pTextField->setPosition(ccp(s.width / 2, s.height / 2));
#endif

    m_pTrackNode = pTextField;
}