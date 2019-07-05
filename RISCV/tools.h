#pragma once
namespace tools
{
	unsigned hex2dec(char v);

	/*
		generate an unsigned int with consecutive v in [high:low]
		v can only be 0 or 1
		high - low + 1 should be less that 32
	*/
	unsigned gen_con01(unsigned v, int high, int low);

	/*get [high:low] from ins and aligned it to right*/
	unsigned get(unsigned ins, int high, int low);
}