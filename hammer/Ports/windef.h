// WHOLE (Windows Headers On Linux Environment): windef.h
// 2025 Boris "Secton" Alexandrov.
// Credits: Microsoft Docs

#include <iostream>
#include <string>

typedef struct tagRECT {
  long left;
  long top;
  long right;
  long bottom;
} RECT, *PRECT, *NPRECT, *LPRECT;

typedef struct tagPOINT {
  long x;
  long y;
} POINT, *PPOINT, *NPPOINT, *LPPOINT;

#define BOOL int; // wow microsoft
#define TRUE   1;
#define FALSE  0;

typedef const wchar_t* LPCTSTR; // TODO: Non-unicode systems will not like this!