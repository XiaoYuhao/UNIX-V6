#ifndef CRT_H
#define CRT_H

#include "TTy.h"


class CRT
{
	/* Const Member */
public:
	/* 显示控制寄存器I/O端口地址 */
	static const unsigned short VIDEO_ADDR_PORT = 0x3d4;	/* 显示控制索引寄存器端口号 */
	static const unsigned short VIDEO_DATA_PORT = 0x3d5;	/* 显示控制数据寄存器端口号 */
	
	/* 屏幕大小为80 * 25 */
	static const unsigned int COLUMNS = 80;
	static unsigned int ROWS;
	static const unsigned int SCREN_COLUMNS=39;
	static const unsigned short COLOR = 0x0F00;		/* char in white color */

	/* Functions */
public:
	/* 将输出缓存队列中的内容输出到屏幕上 */
	static void CRTStart(TTy* pTTy);

	/* 改变光标位置 */
	static void MoveCursor(unsigned int x, unsigned int y);

	/* 换行处理子程序 */
	static void NextLine(int ntty);

	/* 退格处理子程序 */
	static void BackSpace(int ntty);
	
	/* Tab处理子程序 */
	static void Tab(int ntty);

	/* 显示单个字符 */
	static void WriteChar(char ch,int ntty);

	/* 清除屏幕 */
	static void ClearScreen(int ntty);

	/* Members */
public:
	static unsigned short* m_VideoMemory;
	static int m_CursorX;
	static int m_CursorY;
	static int m2_CursorX;	/* tty2终端的XY坐标信息 */
	static int m2_CursorY;

	/* 指向输出缓存队列中当前要输出的字符 */
	static char* m_Position;
	static char* m2_Position;
	/* 指向输出缓存队列中未确认的输出字符的开始处，即可以通过Backspace键删除的内容，
	 * 最后一个回车之前的内容为已确认内容，不可被Backspace键删除。
	 */
	static char* m_BeginChar;
	static char* m2_BeginChar;
};

#endif
