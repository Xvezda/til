#include <stdio.h>

#if defined(_WIN32)
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#define PID_TYPE DWORD
#define PID_FMT "%ld"
#else
#include <unistd.h>
#define PID_TYPE pid_t
#define PID_FMT "%d"
#endif


typedef struct data_s {
    char *msg;
    PID_TYPE id;
} data_t;

#if defined(_WIN32)
DWORD WINAPI print_msg(LPVOID lpParam);
#else
void print_msg(data_t *data);
#endif


int main(void)
{
    data_t data;

    puts("=Before fork=");
#if defined(_WIN32)

    DWORD dwThreadId;
    HANDLE hThread;

    data.msg = "parent";
    data.id = GetCurrentProcessId();

    print_msg(&data);

    data.msg = "child";
    data.id = 0;

    hThread = CreateThread(
        NULL,
        0,
        print_msg,
        &data,
        0,
        &dwThreadId);

    if (hThread != NULL) {
        WaitForSingleObject(hThread, INFINITE);
    }
#else
    PID_TYPE pid;

    if((pid=fork()) == 0) {
        // If pid == 0, it's parent process
        data.msg = "parent";
    } else {
        data.msg = "child";
    }
    data.id = pid;
    print_msg(&data);
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

    StringCchPrintf(msgBuf, sizeof(msgBuf), TEXT("%s: " PID_FMT "\n"),
        data->msg, data->id);
    (void)StringCchLength(msgBuf, sizeof(msgBuf), &cchStringSize);
    WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

    return 0;
}
#else
void print_msg(data_t *data)
{
    printf("%s: " PID_FMT "\n", data->msg, data->id);
}
#endif

