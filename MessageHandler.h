#pragma once
#ifndef _MESSAGE_HANDLER_INCLUDED_
#define _MESSAGE_HANDLER_INCLUDED_

#include <map>
#include <string>

#include "ProgramSettings.h"
#include "Autorun.h"

class MessageHandler
{
public:
	MessageHandler(ProgramSettings* settings);
	int process(std::string message);

private:
	std::map<std::string, void(MessageHandler::*)(std::string)> commands;

	//Commadns
	void Test(std::string str);
	void SetAutorun(std::string str);
	void SetLooptime(std::string str);
	void SetMessage(std::string str);
	void EnableMessage(std::string str);
	void SetProcessName(std::string str);
	void Exit(std::string str);
	//Commadns

	ProgramSettings* settings;
};


#endif
