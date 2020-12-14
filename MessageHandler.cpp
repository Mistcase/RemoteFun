#include "MessageHandler.h"

MessageHandler::MessageHandler(ProgramSettings* settings)
{
	this->settings = settings;

	this->commands.emplace("test", &MessageHandler::Test);
	this->commands.emplace("autorun", &MessageHandler::SetAutorun);
	this->commands.emplace("looptime", &MessageHandler::SetLooptime);
	this->commands.emplace("message", &MessageHandler::SetMessage);
	this->commands.emplace("enablemessage", &MessageHandler::EnableMessage);
	this->commands.emplace("setprocessname", &MessageHandler::SetProcessName);
	this->commands.emplace("exit", &MessageHandler::Exit);
}

int MessageHandler::process(std::string message)
{
	try
	{
		int index = 0;
		bool commandDefined = false;
		std::string command(""), params("");

		while (index != message.size())
		{
			if (message.at(index) == '=')
			{
				commandDefined = true;
				index++;
			}

			if (!commandDefined)
			{
				command += tolower(message[index]);
			}
			else
			{
				params += message[index];
			}
			index++;
		}

		(this->*commands.at(command))(params);
	}
	catch (const std::exception&)
	{
		printf("Exception\n");
		return -1;
	}

	return 0;
}

void MessageHandler::Test(std::string str)
{
	printf("Test\n");
}

void MessageHandler::SetAutorun(std::string str)
{
	settings->enableAutorun = atoi(str.c_str());
}

void MessageHandler::SetLooptime(std::string str)
{
	settings->loopTimer = atoi(str.c_str());
}

void MessageHandler::SetMessage(std::string str)
{
	settings->message = str;
}

void MessageHandler::EnableMessage(std::string str)
{
	settings->enableMessage = atoi(str.c_str());
}

void MessageHandler::SetProcessName(std::string str)
{
	settings->procName = str;
}

void MessageHandler::Exit(std::string str)
{
	if (settings->enableAutorun)
	{
		EnableAutorun("C:\\Windows\\NoPlay");
	}
	else
	{
		//DisableAutorun
	}
	exit(0);
}
