#pragma once
#ifndef _SETTINGS_INCLUDED_
#define _SETTINGS_INCLUDED_

#include <string>

struct ProgramSettings
{
	int loopTimer;
	bool enableAutorun,
		enableMessage,
		makeAction;
	std::string procName, message;
};

#endif
