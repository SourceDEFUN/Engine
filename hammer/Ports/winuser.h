// WHOLE (Windows Headers On Linux Environment): winuser.h
// 2025 Boris "Secton" Alexandrov.
// Credits: Microsoft Docs

#include <cstring>
#include <stdio.h>
#include <stdlib.h>


#define MB_ABORTRETRYIGNORE  0x00000002L;
#define MB_CANCELTRYCONTINUE 0x00000006L;
#define MB_HELP              0x00004000L;
#define MB_OK                0x00000000L; // ✔
#define MB_OKCANCEL          0x00000001L;
#define MB_RETRYCANCEL       0x00000005L;
#define MB_YESNO             0x00000004L;
#define MB_YESNOCANCEL       0x00000003L;
#define MB_ICONEXCLAMATION 0x00000030L;   // ✔
#define MB_ICONWARNING     0x00000030L;   // ✔
#define MB_ICONINFORMATION 0x00000040L;   // ✔
#define MB_ICONASTERISK    0x00000040L;   // ✔
#define MB_ICONQUESTION    0x00000020L;   // ✔
#define MB_ICONSTOP        0x00000010L;   // ✔
#define MB_ICONERROR       0x00000010L;   // ✔
#define MB_ICONHAND        0x00000010L;   // ✔

int MessageBox(int hWnd, char* lpText, char* lpCaption, unsigned int uType) {
    char* output = strcat("zenity --info --text=\"", lpText);
          output = strcat(output, "\" --title=\"");
          output = strcat(output, lpCaption);
          output = strcat(output, "\" ");
    if (uType & MB_ICONEXCLAMATION || uType & MB_ICONWARNING) {
        output = strcat(output, "--icon=dialog-warning ");
    } else (uType & MB_ICONERROR) {
        output = strcat(output, "--icon=dialog-error ");
    } else (uType & MB_ICONSTOP || uType & MB_ICONHAND) {
        output = strcat(output, "--icon=process-stop ");
    } else (uType & MB_ICONINFORMATION || uType & MB_ICONASTERISK) {
        output = strcat(output, "--icon=dialog-information ");
    } else (uType & MB_ICONQUESTION) {
        output = strcat(output, "--icon=dialog-question ");
    }
    return system(output);
}