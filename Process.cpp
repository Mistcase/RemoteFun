#include "Process.h"

DWORD PidByName(const char* AProcessName)
{
    HANDLE pHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 ProcessEntry;
    DWORD pid;
    ProcessEntry.dwSize = sizeof(ProcessEntry);
    bool Loop = Process32First(pHandle, &ProcessEntry);

    while (Loop)
    {
        if (strstr(ProcessEntry.szExeFile, AProcessName))
        {
            pid = ProcessEntry.th32ProcessID;
            CloseHandle(pHandle);
            return pid;
        }
        Loop = Process32Next(pHandle, &ProcessEntry);
    }
    return 0;
}

BOOL KillProcess(IN DWORD dwProcessId)
{
    HANDLE hProcess;
    DWORD dwError;

    // сначала попробуем получить описатель процесса без 
    // использования дополнительных привилегий
    hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessId);
    if (hProcess == NULL)
    {
        if (GetLastError() != ERROR_ACCESS_DENIED)
            return FALSE;
    }
    // пытаемся завершить процесс
    if (!TerminateProcess(hProcess, (UINT)-1))
    {
        dwError = GetLastError();
        CloseHandle(hProcess);
        return SetLastError(dwError), FALSE;
    }

    CloseHandle(hProcess);
    return TRUE;
}

bool IsProcessRun(LPTSTR processName)
{
    HANDLE hSnap = NULL;
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != NULL)
    {
        if (Process32First(hSnap, &pe32))
        {
            if (lstrcmp(pe32.szExeFile, processName) == 0)
                return TRUE;
            while (Process32Next(hSnap, &pe32))
            {
                if (lstrcmp(pe32.szExeFile, processName) == 0)
                {
                    return TRUE;
                }
            }
        }
    }
    CloseHandle(hSnap);
    return FALSE;
}