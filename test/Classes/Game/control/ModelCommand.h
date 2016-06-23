#ifndef _MODELCOMMAND_H_
#define _MODELCOMMAND_H_

#include "mvc/SimpleCommand.h"
/**
* Model layer (proxy) registered
*/

class ModelCommand:public SimpleCommand
{
public:
	ModelCommand(){};
	~ModelCommand(){};

	virtual void execute(int32 command, char* data);

private:


};


#endif