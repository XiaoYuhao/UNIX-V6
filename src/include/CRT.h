#ifndef CRT_H
#define CRT_H

#include "TTy.h"


class CRT
{
	/* Const Member */
public:
	/* ��ʾ���ƼĴ���I/O�˿ڵ�ַ */
	static const unsigned short VIDEO_ADDR_PORT = 0x3d4;	/* ��ʾ���������Ĵ����˿ں� */
	static const unsigned short VIDEO_DATA_PORT = 0x3d5;	/* ��ʾ�������ݼĴ����˿ں� */
	
	/* ��Ļ��СΪ80 * 25 */
	static const unsigned int COLUMNS = 80;
	static unsigned int ROWS;
	static const unsigned int SCREN_COLUMNS=39;
	static const unsigned short COLOR = 0x0F00;		/* char in white color */

	/* Functions */
public:
	/* �������������е������������Ļ�� */
	static void CRTStart(TTy* pTTy);

	/* �ı���λ�� */
	static void MoveCursor(unsigned int x, unsigned int y);

	/* ���д����ӳ��� */
	static void NextLine(int ntty);

	/* �˸����ӳ��� */
	static void BackSpace(int ntty);
	
	/* Tab�����ӳ��� */
	static void Tab(int ntty);

	/* ��ʾ�����ַ� */
	static void WriteChar(char ch,int ntty);

	/* �����Ļ */
	static void ClearScreen(int ntty);

	/* Members */
public:
	static unsigned short* m_VideoMemory;
	static int m_CursorX;
	static int m_CursorY;
	static int m2_CursorX;	/* tty2�ն˵�XY������Ϣ */
	static int m2_CursorY;

	/* ָ�������������е�ǰҪ������ַ� */
	static char* m_Position;
	static char* m2_Position;
	/* ָ��������������δȷ�ϵ�����ַ��Ŀ�ʼ����������ͨ��Backspace��ɾ�������ݣ�
	 * ���һ���س�֮ǰ������Ϊ��ȷ�����ݣ����ɱ�Backspace��ɾ����
	 */
	static char* m_BeginChar;
	static char* m2_BeginChar;
};

#endif
