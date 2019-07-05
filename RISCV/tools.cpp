#include "tools.h"

unsigned tools::hex2dec(char v)
{
	if ('0' <= v && v <= '9') return v - '0';
	else if ('a' <= v && v <= 'z') return v - 'a' + 10;
	else return v - 'A' + 10;
}

unsigned tools::gen_con01(unsigned v, int high, int low)
{
	if (!v) return 0;
	else return ((1 << (high - low + 1)) - 1) << low;
}

unsigned tools::get(unsigned ins, int high, int low)
{
	return ins << (31 - high) >> (32 - (high - low + 1));
}