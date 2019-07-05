#pragma once
#include "stdc++.h"
#include "tools.h"

namespace memory
{
	char getc();
	void init_mem();
	unsigned read_mem(int len);
	unsigned read_mem32();
	unsigned read_mem_pos(int pos, int len); // won't change pc
	unsigned read_mem32_pos(int pos); // won't change pc
	void write_mem_pos(int pos, int len, int v);
}