#pragma once
#include "mvc/SimpleCommand.h"

class MailProxyCommand : public SimpleCommand
{
public:
	MailProxyCommand();
	virtual void execute(int32 command, char* data);

public:
	enum
	{
		INIT_MAIL_COUNT,
		UPDATE_MAIL_LIST,
		UPDATE_MAIL_CONTENT,
	};

protected:
private:
};