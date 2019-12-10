#include <stdio.h>
#if defined(_WIN32)
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#else
#include <unistd.h>
#endif

typedef struct data_s {
    char *msg;
    int id;
} data_t;

#if defined(_WIN32)
DWORD WINAPI print_msg(LPVOID lpParam);
#else
void print_msg(data_t *data);
#endif


int main(void)
{
#if defined(_WIN32)

    DWORD dwThreadId;
    HANDLE hThread;

    data_t parentData = { .msg = "parent", .id = 0 };
    data_t childData = { .msg = "child", .id = 0 };

    print_msg(&parentData);

    hThread = CreateThread(
        NULL,
        0,
        print_msg,
        &childData,
        0,
        &dwThreadId);

    if (hThread != NULL) {
        WaitForSingleObject(hThread, INFINITE);
    }
#else
    pid_t pid;

    puts("=Before fork=");
    if((pid=fork()) == 0) {
        // If pid == 0, it's parent process
        print_msg("parent", pid);
    } else {
        print_msg("child", pid);
    }
#endif
    return 0;
}


#if defined(_WIN32)
DWORD WINAPI print_msg(LPVOID lpParam)
{
    TCHAR msgBuf[256];

    data_t *data;
    HANDLE hStdout;

    size_t cchStringSize;
    DWORD dwChars;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    data = (data_t *)lpParam;

    StringCchPrintf(msgBuf, sizeof(msgBuf), TEXT("%s: %d\n"),
        data->msg, data->id);
    (void)StringCchLength(msgBuf, sizeof(msgBuf), &cchStringSize);
    WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

    return 0;
}
#else
void print_msg(data_t *data)
{
    printf("%s: %d\n", data->msg, data->id);
}
#endif

