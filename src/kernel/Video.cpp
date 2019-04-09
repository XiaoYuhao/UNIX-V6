#include "Video.h"

unsigned short* Diagnose::m_VideoMemory = (unsigned short *)(0xB8000 + 0xC0000000);
unsigned int Diagnose::m_Row = 10;
unsigned int Diagnose::m_Column = 0;

unsigned int Diagnose::ROWS = 10;

bool Diagnose::trace_on = true;

Diagnose::Diagnose()
{
	//ȫ������static��Ա����������û��ʲô��Ҫ�ڹ��캯���г�ʼ���ġ�
}


Diagnose::~Diagnose()
{
	//this is an empty dtor
}

void Diagnose::TraceOn()
{
	Diagnose::trace_on = 1;
}

void Diagnose::TraceOff()
{
	Diagnose::trace_on = 0;
}

/*
	�ܹ������ʽ������ַ�����Ŀǰֻ��ʶ��һЩ%d %x  %s ��%n;
	û�м������ܣ�% �� ֵƥ��Ҫ�Լ�ע�⡣
*/

void Diagnose::Write(const char* fmt, ...)
{
	if ( false == Diagnose::trace_on )
	{
		return;
	}
	//ʹva_arg�д�Ų���fmt�� ����һ�������� ���ڵ��ڴ��ַ
	//fmt�����ݱ������ַ������׵�ַ(�ⲻ������Ҫ��)����&fmt + 1������һ�������ĵ�ַ
	//�ο�UNIX v6�еĺ���prf.c/printf(fmt, x1,x2,x3,x4,x5,x6,x7,x8,x9,xa,xb,xc)
	unsigned int * va_arg = (unsigned int *)&fmt + 1;
	const char * ch = fmt;
	
	while(1)
	{
		while(*ch != '%' && *ch != '\n')
		{
			if(*ch == '\0')
				return;
			if(*ch == '\n')
				break;
			/*ע�⣺ '\n'��һ����һ�ַ���������'\\'�� ��n'�����ַ�����ӣ� 
			Ʃ�����ַ���"\nHello World!!"������Ƚ� if(*ch == '\\' && *(ch+1) == '\n' ) �Ļ���
			�����ĺݲҵģ�*/
			WriteChar(*ch++);
		}
		
		ch++;	//skip the '%' or '\n'   

		if(*ch == 'd' || *ch == 'x')
		{//%d �� %x ��ʽ���������ȻҪ��Ӱ˽��ƺͶ�����Ҳ�����ף����ô�����
			int value = (int)(*va_arg);
			va_arg++;
			if(*ch == 'x')
				Write("0x");   //as prefix for HEX value
			PrintInt(value, *ch == 'd' ? 10 : 16);
			ch++;	//skip the 'd' or 'x'
		}
		
		else if(*ch == 's')
		{//%s ��ʽ�����
			ch++;	//skip the 's'
			char *str = (char *)(*va_arg);
			va_arg++;
			while(char tmp = *str++)
			{
				WriteChar(tmp);
			}
		}
		else /* if(*(ch-1) == '\n') */
		{
			Diagnose::NextLine();
		}
	}
}

/*
	�ο�UNIX v6�еĺ���prf.c/printn(n,b)
	�˺����Ĺ����ǽ�һ��ֵvalue��base���Ƶķ�ʽ��ʾ������
*/
void Diagnose::PrintInt(unsigned int value, int base)
{
	//��Ϊ����0��9 �� A~F��ASCII��֮�䲻�������ģ����Բ��ܼ�ͨ��
	//ASCII(i) = i + '0'ֱ�Ӽ���õ����������Digits�ַ����顣
	static char Digits[] = "0123456789ABCDEF";
	int i;
	
	if((i = value / base) != 0)
		PrintInt(i ,base);
	WriteChar(Digits[value % base]);
}

void Diagnose::NextLine()
{
	m_Row += 1;
	m_Column = 0;
}


void Diagnose::WriteChar(const char ch)
{
	if(Diagnose::m_Column >= Diagnose::COLUMNS)
	{
		NextLine();
	}
	//�����ǲ�������
		Diagnose::m_VideoMemory[39] = (unsigned char) '|' | Diagnose::COLOR;
		Diagnose::m_VideoMemory[119] = (unsigned char) '|' | Diagnose::COLOR;
		Diagnose::m_VideoMemory[199] = (unsigned char) '|' | Diagnose::COLOR;
		Diagnose::m_VideoMemory[279] = (unsigned char) '|' | Diagnose::COLOR;
		Diagnose::m_VideoMemory[359] = (unsigned char) '|' | Diagnose::COLOR;
		Diagnose::m_VideoMemory[439] = (unsigned char) '|' | Diagnose::COLOR;
		Diagnose::m_VideoMemory[519] = (unsigned char) '|' | Diagnose::COLOR;
		Diagnose::m_VideoMemory[599] = (unsigned char) '|' | Diagnose::COLOR;
		Diagnose::m_VideoMemory[679] = (unsigned char) '|' | Diagnose::COLOR;
		Diagnose::m_VideoMemory[759] = (unsigned char) '|' | Diagnose::COLOR;
		Diagnose::m_VideoMemory[839] = (unsigned char) '|' | Diagnose::COLOR;
		Diagnose::m_VideoMemory[919] = (unsigned char) '|' | Diagnose::COLOR;
		Diagnose::m_VideoMemory[999] = (unsigned char) '|' | Diagnose::COLOR;
		Diagnose::m_VideoMemory[1079] = (unsigned char) '|' | Diagnose::COLOR;
//		Diagnose::m_VideoMemory[1159] = (unsigned char) '|' | Diagnose::COLOR;
		for(int i=1120;i<1199;i++){
			Diagnose::m_VideoMemory[i] = (unsigned char) '_' | Diagnose::COLOR;
		}
		Diagnose::m_VideoMemory[1159] = (unsigned char) '|' | Diagnose::COLOR;
//		Diagnose::m_VideoMemory[1159] = (unsigned char) '|' | Diagnose::COLOR;
//		Diagnose::m_VideoMemory[1239] = (unsigned char) '|' | Diagnose::COLOR;
//		Diagnose::m_VideoMemory[1319] = (unsigned char) '|' | Diagnose::COLOR;
//		Diagnose::m_VideoMemory[1399] = (unsigned char) '|' | Diagnose::COLOR;
//		Diagnose::m_VideoMemory[1479] = (unsigned char) '|' | Diagnose::COLOR;
//		Diagnose::m_VideoMemory[1559] = (unsigned char) '|' | Diagnose::COLOR;
//		Diagnose::m_VideoMemory[1639] = (unsigned char) '|' | Diagnose::COLOR;
//		Diagnose::m_VideoMemory[1719] = (unsigned char) '|' | Diagnose::COLOR;
//		Diagnose::m_VideoMemory[1799] = (unsigned char) '|' | Diagnose::COLOR;
//		Diagnose::m_VideoMemory[1879] = (unsigned char) '|' | Diagnose::COLOR;

	if(Diagnose::m_Row >= Diagnose::SCREEN_ROWS)
	{
		Diagnose::ClearScreen();
	}

	Diagnose::m_VideoMemory[Diagnose::m_Row * Diagnose::COLUMNS + Diagnose::m_Column] = (unsigned char) ch | Diagnose::COLOR;
	Diagnose::m_Column++;
}

void Diagnose::ClearScreen()
{
	unsigned int i;

	Diagnose::m_Row = Diagnose::SCREEN_ROWS - Diagnose::ROWS;
	Diagnose::m_Column = 0;

	for(i = 0; i < (Diagnose::COLUMNS * ROWS); i++)
	{
		Diagnose::m_VideoMemory[i + m_Row * Diagnose::COLUMNS] = (unsigned char) ' ' | Diagnose::COLOR;
	}

/*	unsigned int j,cn;
	for(i=0;i<ROWS;i++){
		cn=m_Row*Diagnose::SCREEN_COLUMNS+i*80;
		for(j=0;j<COLUMNS;j++){
			Diagnose::m_VideoMemory[j + cn] = (unsigned char) ' ' | Diagnose::COLOR;
		}
	}*/
}
