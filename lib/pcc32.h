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

/* �������� */
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

/* ����̨�ߴ綨�� */
#define MIN_CONSOLE_WIDTH   14
#define MIN_CONSOLE_HEIGHT  1

/* ��ɫ���� */
enum
{
  BLACK           =  0,   // ��ɫ
  BLUE            =  1,   // ��ɫ
  GREEN           =  2,   // ��ɫ
  CYAN            =  3,   // ��ɫ
  RED             =  4,   // ��ɫ
  MAGENTA         =  5,   // ��ɫ
  BROWN           =  6,   // ��ɫ
  LIGHT_GRAY      =  7,   // ǳ��
  DARK_GRAY       =  8,   // ���
  LIGHT_BLUE      =  9,   // ����
  LIGHT_GREEN     = 10,   // ����
  LIGHT_CYAN      = 11,   // ǳ��
  LIGHT_RED       = 12,   // ����
  LIGHT_MAGENTA   = 13,   // ����
  YELLOW          = 14,   // ��ɫ
  WHITE           = 15    // ��ɫ
};

#ifdef __cplusplus
extern "C"
{
#endif

  /* ��ʽ��ʱ���ַ��� */
  char *pccTimeStr(time_t t, char *fmt);
  /* ��ӡ��־���ļ� */
  int pccLog(char *fmt, ...);
  /* ��ʱ,�Ժ���� */
  void pccSleep(uint32 d);
  /* ������� */
  int pccClear(void);
  /* ��ͣ,�ȴ��û����� */
  int pccPause(void);
  /* �����򵥵�������(����,����) */
  int pccBeep(uint16 freq, uint16 len);

  /* �����ı���ɫ,0~15 */
  int pccSetTextColor(uint8 c);
  /* ��ȡ�ı���ɫ,0~15 */
  int pccGetTextColor(void);
  /* �����ı�������ɫ,0~15 */
  int pccSetBackColor(uint8 c);
  /* ��ȡ�ı�������ɫ,0~15 */
  int pccGetBackColor(void);
  /* �����ı����䱳����ɫ,0~15 */
  int pccSetColors(uint8 f, uint8 b);
  /* ����/ȡ��ǰ/������ɫ�Ľ������� */
  int pccSwapColors(int b);
  /* �趨/ȡ�����ֵ��»��� */
  int pccSetUnderLine(int b);

  /* ��ȡ����̨�ı��е���󳤶�[Ĭ��Ϊ80] */
  int pccGetColsNum(void);
  /* ��ȡ����̨�ı��е�������� */
  int pccGetRowsNum(void);

  /* ��ȡ���ĺ�����[����] */
  int pccGetCursorCol(void);
  /* ��ȡ����������[����] */
  int pccGetCursorRow(void);
  /* ��Ļ��궨λ,xΪ��(��),yΪ��(��) */
  int pccGotoPos(uint8 col, uint8 row);

  /* ���ù��Ŀɼ��� */
  int pccShowCursor(int b);
  /* ���ù���(���)�ߴ�,1-100 */
  int pccSetCursorSize(uint8 s);

  /* ��ȡ����̨�ı����ַ��� */
  int pccGetTitle(char *title, uint8 len);
  /* ���ÿ���̨�ı����ַ��� */
  int pccSetTitle(char *title);

  /* ����һ��û�й������Ŀ���̨���ڳߴ� */
  int pccFixSize(uint16 cols, uint16 rows);
  /* �������̨�������Ϣ(����������) */
  int pccShowInfo(void);

  /* ��ȡ����̨�ļ����� */
  int pccGetKey(void);
  /* �жϿ���̨�Ƿ��м����� */
  int pccHasKey(void);

#ifdef __cplusplus
}
#endif

/* �ɰ�API�����Դ��� */
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
