#pragma once
#ifndef _PROCESS_HANDLING_INCLUDED_
#define _PROCESS_HANDLING_INCLUDED_

#include <Windows.h>
#include <tlhelp32.h>

DWORD PidByName(const char* AProcessName);

BOOL KillProcess(IN DWORD dwProcessId);

bool IsProcessRun(LPTSTR processName);

#endif
