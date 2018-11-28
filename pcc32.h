/********************************************************
* Author:  RedOC                                        *
* Email:   redoc@foxmail.com                            *
* Notes:   Some functions about Win32 Console Control.  *
* License: Copyleft. Enjoy it Just for fun.             *
* Date:    2008-12-17 00:28:39                          *
********************************************************/

#ifndef PCC32_H_INCLUDED
#define PCC32_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#ifndef REDOC_COMMEN_TYPE
#define REDOC_COMMEN_TYPE

typedef char int8;
typedef short int16;
typedef long int32;
typedef long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef unsigned long long uint64;

#endif // REDOC_COMMEN_TYPE

/* 按键定义 */
#define JK_FUNC_KEY  0x00
#define JK_CTRL_KEY  0xE0

#define JK_ESC       0x001B
#define JK_ENTER     0x000D
#define JK_SPACE     0x0020
#define JK_BKSPACE   0x0008
#define JK_TAB       0x0009

#define JK_CTRL_Z    0x001A
#define JK_CTRL_X    0x0018
#define JK_CTRL_C    0x0003
#define JK_CTRL_A    0x0001
#define JK_CTRL_S    0x0013
#define JK_CTRL_D    0x0004

#define JK_LEFT      0xE04B
#define JK_RIGHT     0xE04D
#define JK_UP        0xE048
#define JK_DOWN      0xE050
#define JK_INSERT    0xE052
#define JK_HOME      0xE047
#define JK_PGUP      0xE049
#define JK_DELETE    0xE053
#define JK_END       0xE04F
#define JK_PGDW      0xE051

#define JK_F1        0xFF3B
#define JK_F2        0xFF3C
#define JK_F3        0xFF3D
#define JK_F4        0xFF3E
#define JK_F5        0xFF3F
#define JK_F6        0xFF40
#define JK_F7        0xFF41
#define JK_F8        0xFF42
#define JK_F9        0xFF43
#define JK_F10       0xFF44
#define JK_F11       0xE085
#define JK_F12       0xE086

/* 控制台尺寸定义 */
#define MIN_CONSOLE_WIDTH   14
#define MIN_CONSOLE_HEIGHT  1

/* 颜色定义 */
enum
{
  BLACK           =  0,   // 黑色
  BLUE            =  1,   // 蓝色
  GREEN           =  2,   // 绿色
  CYAN            =  3,   // 青色
  RED             =  4,   // 红色
  MAGENTA         =  5,   // 紫色
  BROWN           =  6,   // 褐色
  LIGHT_GRAY      =  7,   // 浅灰
  DARK_GRAY       =  8,   // 深灰
  LIGHT_BLUE      =  9,   // 亮蓝
  LIGHT_GREEN     = 10,   // 亮绿
  LIGHT_CYAN      = 11,   // 浅蓝
  LIGHT_RED       = 12,   // 亮红
  LIGHT_MAGENTA   = 13,   // 亮紫
  YELLOW          = 14,   // 黄色
  WHITE           = 15    // 白色
};

#ifdef __cplusplus
extern "C"
{
#endif

  /* 格式化时间字符串 */
  char *pccTimeStr(time_t t, char *fmt);
  /* 打印日志到文件 */
  int pccLog(char *fmt, ...);
  /* 延时,以毫秒计 */
  void pccSleep(uint32 d);
  /* 清除文字 */
  int pccClear(void);
  /* 暂停,等待用户按键 */
  int pccPause(void);
  /* 发出简单的响铃声(阻塞,慎用) */
  int pccBeep(uint16 freq, uint16 len);

  /* 设置文本颜色,0~15 */
  int pccSetTextColor(uint8 c);
  /* 获取文本颜色,0~15 */
  int pccGetTextColor(void);
  /* 设置文本背景颜色,0~15 */
  int pccSetBackColor(uint8 c);
  /* 获取文本背景颜色,0~15 */
  int pccGetBackColor(void);
  /* 设置文本及其背景颜色,0~15 */
  int pccSetColors(uint8 f, uint8 b);
  /* 设置/取消前/背景颜色的交换解析 */
  int pccSwapColors(int b);
  /* 设定/取消文字的下划线 */
  int pccSetUnderLine(int b);

  /* 获取控制台文本行的最大长度[默认为80] */
  int pccGetColsNum(void);
  /* 获取控制台文本行的最大行数 */
  int pccGetRowsNum(void);

  /* 获取光标的横坐标[列数] */
  int pccGetCursorCol(void);
  /* 获取光标的纵坐标[行数] */
  int pccGetCursorRow(void);
  /* 屏幕光标定位,x为列(横),y为行(纵) */
  int pccGotoPos(uint8 col, uint8 row);

  /* 设置光标的可见性 */
  int pccShowCursor(int b);
  /* 设置光标的(厚度)尺寸,1-100 */
  int pccSetCursorSize(uint8 s);

  /* 获取控制台的标题字符串 */
  int pccGetTitle(char *title, uint8 len);
  /* 设置控制台的标题字符串 */
  int pccSetTitle(char *title);

  /* 设置一个没有滚动条的控制台窗口尺寸 */
  int pccFixSize(uint16 cols, uint16 rows);
  /* 输出控制台的相关信息(仅作调试用) */
  int pccShowInfo(void);

  /* 获取控制台的键输入 */
  int pccGetKey(void);
  /* 判断控制台是否有键按下 */
  int pccHasKey(void);

#ifdef __cplusplus
}
#endif

/* 旧版API兼容性处理 */
#define delayMS           pccSleep
#define clearText         pccClear
#define pauseHere         pccPause
#define simpleRing        pccBeep
#define setTextColor      pccSetTextColor
#define getTextColor      pccGetTextColor
#define setBackColor      pccSetBackColor
#define getBackColor      pccGetBackColor
#define setColors         pccSetColors
#define setSwapColors     pccSwapColors
#define setUnderLine      pccSetUnderLine
#define getLineWidth      pccGetColsNum
#define getLineNum        pccGetRowsNum
#define getCursorX        pccGetCursorCol
#define getCursorY        pccGetCursorRow
#define gotoTextPos       pccGotoPos
#define setCursorVisible  pccShowCursor
#define setCursorSize     pccSetCursorSize
#define getConsoleTitle   pccGetTitle
#define setConsoleTitle   pccSetTitle
#define fixConsoleSize    pccFixSize
#define showConsoleInfo   pccShowInfo
#define jkGetKey          pccGetKey
#define jkHasKey          pccHasKey
#define PCCOLOR           uint32

#endif // PCC32_H_INCLUDED
