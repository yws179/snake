/********************************************************
* Author:  RedOC                                        *
* Email:   redoc@foxmail.com                            *
* Notes:   Some functions about Win32 Console Control.  *
* License: Copyleft. Enjoy it Just for fun.             *
* Date:    2008-12-17 00:28:39                          *
********************************************************/

#include "pcc32.h"
//~ ccflag = -c
//~ ccobj = libpcc32.a

char *pccTimeStr(time_t t, char *fmt)
{
  static char tm[64] = {0};
  if(!t)
    t = time(0);
  if(!fmt)
    fmt = "%Y-%m-%d %H:%M:%S";
  strftime(tm, 64, fmt, localtime(&t));
  return tm;
}

int pccLog(char *fmt, ...)
{
  static char buf[1024];
  sprintf(buf, "pcc.%s.log", pccTimeStr(0, "%Y-%m-%d"));
  FILE *fp = fopen(buf, "at");
  if(!fp)
    return 0;
  memset(buf, 0, 1024);
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, 1000, fmt, args);
  va_end (args);
  int len = fprintf(fp, "%s\t%s\n", pccTimeStr(0, 0), buf);
  fclose(fp);
  return len;
}

void pccSleep(uint32 d)
{
  Sleep(d);
}

int pccClear(void)
{
  return system("cls");
}

int pccPause(void)
{
  return system("pause > nul");
}

int pccBeep(uint16 freq, uint16 len)
{
  return Beep(freq, len);
}

int pccSetTextColor(uint8 c)
{
  HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbInfo;
  GetConsoleScreenBufferInfo(hd, &csbInfo);
  return SetConsoleTextAttribute(hd, c | (csbInfo.wAttributes&~0x0F));
}

int pccGetTextColor(void)
{
  CONSOLE_SCREEN_BUFFER_INFO csbInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);
  return (csbInfo.wAttributes & 0x0F);
}

int pccSetBackColor(uint8 c)
{
  HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbInfo;
  GetConsoleScreenBufferInfo(hd, &csbInfo);
  return SetConsoleTextAttribute(hd, (c << 4) | (csbInfo.wAttributes&~0xF0));
}

int pccGetBackColor(void)
{
  CONSOLE_SCREEN_BUFFER_INFO csbInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);
  return ((csbInfo.wAttributes & 0xF0) >> 4);
}

int pccSetColors(uint8 f, uint8 b)
{
  HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbInfo;
  GetConsoleScreenBufferInfo(hd, &csbInfo);
  return SetConsoleTextAttribute(hd, f | (b << 4) | (csbInfo.wAttributes&~0xFF));
}

int pccSwapColors(int b)
{
  HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbInfo;
  GetConsoleScreenBufferInfo(hd, &csbInfo);
  if (!!b)
    return SetConsoleTextAttribute(hd, csbInfo.wAttributes | 0x4000);
  else
    return SetConsoleTextAttribute(hd, csbInfo.wAttributes & ~0x4000);
}

int pccSetUnderLine(int b)
{
  HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbInfo;
  GetConsoleScreenBufferInfo(hd, &csbInfo);
  if (!!b)
    return SetConsoleTextAttribute(hd, csbInfo.wAttributes | 0x8000);
  else
    return SetConsoleTextAttribute(hd, csbInfo.wAttributes & ~0x8000);
}

int pccGetColsNum(void)
{
  CONSOLE_SCREEN_BUFFER_INFO csbInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);
  return csbInfo.dwSize.X;
}

int pccGetRowsNum(void)
{
  CONSOLE_SCREEN_BUFFER_INFO csbInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);
  return csbInfo.dwSize.Y;
}

int pccGetCursorCol(void)
{
  CONSOLE_SCREEN_BUFFER_INFO csbInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);
  return csbInfo.dwCursorPosition.X;
}

int pccGetCursorRow(void)
{
  CONSOLE_SCREEN_BUFFER_INFO csbInfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);
  return csbInfo.dwCursorPosition.Y;
}

int pccGotoPos(uint8 col, uint8 row)
{
  COORD cd;
  cd.X = col;
  cd.Y = row;
  return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}

int pccShowCursor(int b)
{
  HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO ccInfo;
  GetConsoleCursorInfo(hd, &ccInfo);
  ccInfo.bVisible = !!b;
  return SetConsoleCursorInfo(hd, &ccInfo);
}

int pccSetCursorSize(uint8 s)
{
  HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO ccInfo;
  GetConsoleCursorInfo(hd, &ccInfo);
  ccInfo.dwSize = s;
  return SetConsoleCursorInfo(hd, &ccInfo);
}

int pccGetTitle(char *title, uint8 len)
{
  return GetConsoleTitle(title, len);
}

int pccSetTitle(char *title)
{
  return SetConsoleTitle(title);
}

int pccFixSize(uint16 cols, uint16 rows)
{
  int ret = 0;
  int fixX = 0, fixY = 0;
  COORD cd;
  SMALL_RECT srctWindow;
  CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
  HANDLE hWin = GetStdHandle(STD_OUTPUT_HANDLE);

  if (!hWin)
    return 0;

  fixX = (cols < MIN_CONSOLE_WIDTH) ? MIN_CONSOLE_WIDTH : cols;
  fixY = (rows < MIN_CONSOLE_HEIGHT) ? MIN_CONSOLE_HEIGHT : rows;

  cd.X = 512;
  cd.Y = 512;
  ret = SetConsoleScreenBufferSize(hWin, cd);
  if (!ret)
    return ret;

  GetConsoleScreenBufferInfo(hWin, &csbiInfo);
  cd = csbiInfo.dwMaximumWindowSize;
  fixX = (fixX > cd.X) ? cd.X : fixX;
  fixY = (fixY > cd.Y) ? cd.Y : fixY;

  srctWindow.Left = 0;
  srctWindow.Right = fixX - 1;
  srctWindow.Top = 0;
  srctWindow.Bottom = fixY - 1;
  ret = SetConsoleWindowInfo(hWin, 1, &srctWindow);
  if (!ret)
    return ret;

  cd.X = fixX;
  cd.Y = fixY;
  ret = SetConsoleScreenBufferSize(hWin, cd);
  if (!ret)
    return ret;

  Sleep(100);
  return ret;
}

int pccShowInfo(void)
{
  int ret;
  HANDLE hWin = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

  ret = GetConsoleScreenBufferInfo(hWin, &csbiInfo);
  if (ret)
  {
    pccLog("Buffer Size: [X]%d - [Y]%d\n", csbiInfo.dwSize.X, csbiInfo.dwSize.Y);
    pccLog("Cursor Pos : [X]%d - [Y]%d\n", csbiInfo.dwCursorPosition.X, csbiInfo.dwCursorPosition.Y);
    pccLog("Attributes : %d\n", csbiInfo.wAttributes);
    pccLog("Current Win: [L]%d - [R]%d - [T]%d - [B]%d\n", \
           csbiInfo.srWindow.Left, csbiInfo.srWindow.Right, csbiInfo.srWindow.Top, csbiInfo.srWindow.Bottom);
    pccLog("Maximum Win: [X]%d - [Y]%d\n", csbiInfo.dwMaximumWindowSize.X, csbiInfo.dwMaximumWindowSize.Y);
  }
  return ret;
}

int pccGetKey(void)
{
  uint16 rk = 0;
  uint8 k = getch();
  if (k == JK_FUNC_KEY)
  {
    k = getch();
    rk = 0xFF00 | k;
    return rk;
  }
  if (k == JK_CTRL_KEY)
  {
    k = getch();
    rk = 0xE000 | k;
    return rk;
  }
  rk = 0x0000 | k;
  return rk;
}

int pccHasKey(void)
{
  return (kbhit());
}

//End of pcc32.c
