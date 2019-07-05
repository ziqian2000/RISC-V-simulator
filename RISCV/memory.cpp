#include "stdc++.h"
#include "tools.h"
#include "memory.h"

extern unsigned mem[];
extern unsigned pc;

char memory::getc()
{
	char c = getchar();
	while (c == ' ' || c == '\n')
		c = getchar();
	return c;
}

void memory::init_mem()
{
	unsigned pos = 0;
	while (true)
	{
		char c = getc();
		if (c == EOF)
		{
			break;
		}
		else if (c == '@')
		{
			unsigned v = 0;
			for (int i = 1; i <= 8; i++)
				v = v << 4 | tools::hex2dec(getc());
			pos = v;
		}
		else
		{
			unsigned v = tools::hex2dec(c) << 4 | tools::hex2dec(getc());
			mem[pos++] = v;
		}
	}
}

unsigned memory::read_mem(int len)
{
	unsigned v = 0;
	for (int i = len - 1; ~i; i--)
		v = v << 8 | mem[pc + i];
	pc += len;
	return v;
}

unsigned memory::read_mem32()
{
	return memory::read_mem(4);
}

unsigned memory::read_mem_pos(int pos, int len)
{
	unsigned v = 0;
	for (int i = len - 1; ~i; i--)
		v = v << 8 | mem[pos + i];
	return v;
}

unsigned memory::read_mem32_pos(int pos)
{
	return memory::read_mem_pos(pos, 4);
}

void memory::write_mem_pos(int pos, int len, int v)
{
	for (int i = 0; i < len; i++)
	{
		mem[pos + i] = v & ((1 << 8) - 1);
		v >>= 8;
	}
}