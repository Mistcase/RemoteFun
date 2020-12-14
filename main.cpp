#include "init.h"
#include "process.h"
#include "autorun.h"
#include "net.h"
#include "messagehandler.h"

using cat_network::TcpClient;

constexpr size_t MESSAGE_BUFFFER_SIZE = 512;

int main()
{
    start:
    ProgramSettings settings = Initialize();
    ShowWindow(GetConsoleWindow(), SW_SHOW);

    TcpClient client;
    Address serverAddress;

    int desc = FindServer(&client, &serverAddress);
    if (desc == -1)
    {
        exit(-1);
    }
    std::cout << "Server found!\n";

    MessageHandler handler(&settings);
    while (true)
    {
        if (client.readable(desc))
        {
            //Если есть сообщение, обрабоать его
            char buffer[MESSAGE_BUFFFER_SIZE];
            ZeroMemory(buffer, MESSAGE_BUFFFER_SIZE);
            size_t rsize = 0;

            client.read(buffer, &rsize, desc, 0);
            handler.process(buffer);

            if (rsize > 100000 || rsize < 0)
            {
                goto start;
            }
        }

        HANDLE handle = 0;
        Sleep(settings.loopTimer);
        if (settings.makeAction)
        {
            if (IsProcessRun((LPTSTR)settings.procName.c_str()))
            {
                KillProcess(PidByName(settings.procName.c_str()));
                MessageBoxA(NULL, settings.message.c_str(), "Error", MB_ICONERROR | MB_OK);
            }
        }
    }

    return 0;
}
