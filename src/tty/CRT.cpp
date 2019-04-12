#include "CRT.h"
#include "IOPort.h"

unsigned short* CRT::m_VideoMemory = (unsigned short *)(0xB8000 + 0xC0000000);
int CRT::m_CursorX = 0;		/*源代码这里有个Bug，应该为int而不是unsigned int*/
int CRT::m_CursorY = 0;
int CRT::m2_CursorX= 40;
int CRT::m2_CursorY= 0;
char* CRT::m_Position = 0;
char* CRT::m_BeginChar = 0;
char* CRT::m2_Position = 0;
char* CRT::m2_BeginChar = 0;

unsigned int CRT::ROWS = 14;



void CRT::CRTStart(TTy* pTTy)
{
	int ntty=pTTy->ntty;	//获取当前tty的编号
	if(ntty==0){
		char ch;
		if ( 0 == CRT::m_BeginChar)
		{
			m_BeginChar = pTTy->t_outq.CurrentChar();
		}
		if ( 0 == m_Position )
		{
			m_Position = m_BeginChar;
		}

		while ( (ch = pTTy->t_outq.GetChar()) != TTy::GET_ERROR )
		{
			switch (ch)
			{
			case '\n':
				NextLine(ntty);
				CRT::m_BeginChar = pTTy->t_outq.CurrentChar();
				m_Position = CRT::m_BeginChar;
				break;

			case 0x15:
				//del_line();
				break;

			case '\b':
				if ( m_Position != CRT::m_BeginChar )
				{
					BackSpace(ntty);
					m_Position--;
				}
				break;

			case '\t':
				Tab(ntty);
				m_Position++;
				break;

			default:	/* 在屏幕上回显普通字符 */
				WriteChar(ch,ntty);
				m_Position++;
				break;
			}
		}
	}
	else{
		char ch;
		if ( 0 == CRT::m2_BeginChar)
		{
			m2_BeginChar = pTTy->t_outq.CurrentChar();
		}
		if ( 0 == m2_Position )
		{
			m2_Position = m2_BeginChar;
		}

		while ( (ch = pTTy->t_outq.GetChar()) != TTy::GET_ERROR )
		{
			switch (ch)
			{
			case '\n':
				NextLine(ntty);
				CRT::m2_BeginChar = pTTy->t_outq.CurrentChar();
				m2_Position = CRT::m2_BeginChar;
				break;

			case 0x15:
				//del_line();
				break;

			case '\b':
				if ( m2_Position != CRT::m2_BeginChar )
				{
					BackSpace(ntty);
					m2_Position--;
				}
				break;

			case '\t':
				Tab(ntty);
				m2_Position++;
				break;

			default:	/* 在屏幕上回显普通字符 */
				WriteChar(ch,ntty);
				m2_Position++;
				break;
			}
		}
	}
}

void CRT::MoveCursor(unsigned int col, unsigned int row)
{
	if ( (col < 0 || col >= CRT::COLUMNS) || (row < 0 || row >= CRT::ROWS) )
	{
		return;
	}

	/* 计算光标偏移量 */
	unsigned short cursorPosition = row * CRT::COLUMNS + col;

	/* 选择 r14和r15寄存器，分别为光标位置的高8位和低8位 */
	IOPort::OutByte(CRT::VIDEO_ADDR_PORT, 14);
	IOPort::OutByte(CRT::VIDEO_DATA_PORT, cursorPosition >> 8);
	IOPort::OutByte(CRT::VIDEO_ADDR_PORT, 15);
	IOPort::OutByte(CRT::VIDEO_DATA_PORT, cursorPosition & 0xFF);
}

void CRT::NextLine(int ntty)
{
	if(ntty==0){
		m_CursorX = 0;
		m_CursorY += 1;
		/* 超出最大行数 */
		if ( m_CursorY >= CRT::ROWS )
		{
			m_CursorY = 0;
			ClearScreen(ntty);
		}
		MoveCursor(m_CursorX, m_CursorY);
	}
	else{
		m2_CursorX = 40;
		m2_CursorY += 1;
		/* 超出最大行数 */
		if ( m2_CursorY >= CRT::ROWS )
		{
			m2_CursorY = 0;
			ClearScreen(ntty);
		}
		MoveCursor(m2_CursorX, m2_CursorY);
	}

}

void CRT::BackSpace(int ntty)
{
	/* 移动光标，如果要回到上一行的话 */
	if(ntty==0){
		m_CursorX--;
		if ( m_CursorX < 0 )
		{
			m_CursorX = CRT::SCREN_COLUMNS - 1;
			m_CursorY--;
			if ( m_CursorY < 0 )
			{
				m_CursorY = 0;
			}
		}
		MoveCursor(m_CursorX, m_CursorY);

		/* 在光标所在位置填上空格 */
		m_VideoMemory[m_CursorY * COLUMNS + m_CursorX] = ' ' | CRT::COLOR;
	}
	else{
		m2_CursorX--;
		if ( m2_CursorX < 40 )
		{
			m2_CursorX = CRT::COLUMNS - 1;
			m2_CursorY--;
			if ( m2_CursorY < 0 )
			{
				m2_CursorY = 0;
			}
		}
		MoveCursor(m2_CursorX, m2_CursorY);

		/* 在光标所在位置填上空格 */
		m_VideoMemory[m2_CursorY * COLUMNS + m2_CursorX] = ' ' | CRT::COLOR;
	}

}

void CRT::Tab(int ntty)
{
	if(ntty==0){
		m_CursorX &= 0xFFFFFFF8;	/* 向左对齐到前一个Tab边界 */
		m_CursorX += 8;
		// const int TabWidth = 10;
		// m_CursorX -= m_CursorX % TabWidth;
		// m_CursorX += TabWidth;
		if ( m_CursorX >= CRT::SCREN_COLUMNS )
			NextLine(ntty);
		else
			MoveCursor(m_CursorX, m_CursorY);
	}
	else{
		m2_CursorX &= 0xFFFFFFF8;	/* 向左对齐到前一个Tab边界 */
		m2_CursorX += 8;
		// const int TabWidth = 10;
		// m_CursorX -= m_CursorX % TabWidth;
		// m_CursorX += TabWidth;
		if ( m2_CursorX >= CRT::SCREN_COLUMNS )
			NextLine(ntty);
		else
			MoveCursor(m2_CursorX, m2_CursorY);
	}
}

void CRT::WriteChar(char ch,int ntty)
{
	if(ntty==0){
		m_VideoMemory[m_CursorY * CRT::COLUMNS + m_CursorX] = (unsigned char) ch | CRT::COLOR;
		m_CursorX++;

		if ( m_CursorX >= CRT::SCREN_COLUMNS)
		{
			NextLine(ntty);
		}
		MoveCursor(m_CursorX, m_CursorY);
	}
	else{
		m_VideoMemory[m2_CursorY * CRT::COLUMNS + m2_CursorX] = (unsigned char) ch | CRT::COLOR;
		m2_CursorX++;

		if ( m2_CursorX >= CRT::COLUMNS)
		{
			NextLine(ntty);
		}
		MoveCursor(m2_CursorX, m2_CursorY);
	}
}

void CRT::ClearScreen(int ntty)
{
	unsigned int i;

/*	for ( i = 0; i < COLUMNS * ROWS; i++ )
	{
		m_VideoMemory[i] = (unsigned short)' ' | CRT::COLOR;
	}*/
	unsigned int j;
	if(ntty==0){
		for(i=0;i<ROWS;i++){
			int cn=i*CRT::COLUMNS;
			for(j=0;j<CRT::SCREN_COLUMNS;j++){
				m_VideoMemory[j+cn] = (unsigned short)' ' | CRT::COLOR;
			}
		}
	}
	else{
		for(i=0;i<ROWS;i++){
			int cn=i*CRT::COLUMNS+40;
			for(j=0;j<CRT::SCREN_COLUMNS;j++){
				m_VideoMemory[j+cn] = (unsigned short)' ' | CRT::COLOR;
			}
		}
	}
}

void CRT::FreshCursor(int ntty){
	if(ntty==0){
		m_VideoMemory[m2_CursorY * CRT::COLUMNS + m2_CursorX] = (unsigned char) ' ' | CRT::COLOR;
		MoveCursor(m_CursorX, m_CursorY);
	}
	else{
		m_VideoMemory[m_CursorY * CRT::COLUMNS + m_CursorX] = (unsigned char) ' ' | CRT::COLOR;
		MoveCursor(m2_CursorX, m2_CursorY);
	}
}

