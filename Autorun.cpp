#include "Autorun.h"

bool EnableAutorun(const char* programName)
{
    // Ключ который будем создавать
    char szPath[] = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
    //\\Software\\Microsoft\\Windows\\CurrentVersion\\Run
    HKEY hKey;
    //\\Software\\Microsoft\\Windows\\CurrentVersion\\Run
    // Создаем ключ в ветке HKEY_CURRENT_USER
    if (RegCreateKeyExA(HKEY_CURRENT_USER, szPath, 0, NULL, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS)
    {
        return false;
    }

    // Пишем тестовую строку в созданный ключ
    if (RegSetValueExA(hKey, "No Play", 0, REG_SZ, (BYTE*)programName, strlen(programName)) != ERROR_SUCCESS) {
        return false;
    }

    // Закрываем описатель ключа
    if (RegCloseKey(hKey) != ERROR_SUCCESS) 
    {
        return false;
    };

    return true;
}
