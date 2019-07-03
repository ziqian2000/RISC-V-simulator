#pragma once
#include "tools.h"
#include "pipeline.h"

extern unsigned x[];

class pipeline2 : public pipeline
{
public:
	void get_type()
	{
		opcode = tools::get(ins, 6, 0);
		func3 = tools::get(ins, 14, 12); // may be not available in some cases but never mind
		switch (opcode)
		{
		case 55: // 0110111
			type = U;
			break;
		case 23: // 0010111
			type = U;
			break;
		case 111: // 1101111
			type = J;
			break;
		case 103: // 1100111
			type = I;
			break;
		case 99: // 1100011
			type = B;
			break;
		case 3: // 0000011
			type = I;
			break;
		case 35: // 0100011
			type = S;
			break;
		case 19: // 0010011
			type = I;
			break;
		case 51: // 0110011
			type = R;
			break;
		default:
			break;
		}
	}

	/* opcode has been decoded */
	void decode_all() 
	{
		switch (type)
		{
		case R:
			func7 = tools::get(ins, 31, 25);
			rs2 = tools::get(ins, 24, 20);
			rs1 = tools::get(ins, 19, 15);
			func3 = tools::get(ins, 14, 12);
			rd = tools::get(ins, 11, 7);
			break;
		case I:
			imm = tools::get(ins, 31, 20);
			rs1 = tools::get(ins, 19, 15);
			func3 = tools::get(ins, 14, 12);
			rd = tools::get(ins, 11, 7);
			break;
		case S:
			imm = tools::get(ins, 31, 25) << 5 | tools::get(ins, 11 ,7);
			rs2 = tools::get(ins, 24, 20);
			rs1 = tools::get(ins, 19, 15);
			func3 = tools::get(ins, 14, 12);
			break;
		case B:
			imm = tools::get(ins, 31, 31) << 12 | tools::get(ins, 30, 25) << 5 | tools::get(ins, 11, 8) << 1 | tools::get(ins, 7, 7) << 11;
			rs2 = tools::get(ins, 24, 20);
			rs1 = tools::get(ins, 19, 15);
			func3 = tools::get(ins, 14, 12);
			break;
		case U:
			imm = tools::get(ins, 31, 12) << 12;
			rd = tools::get(ins, 11, 7);
			break;
		case J:
			imm = tools::get(ins, 31, 31) << 20 | tools::get(ins, 30, 21) << 1 | tools::get(ins, 20, 20) << 11 | tools::get(ins, 19, 12) << 12;
			rd = tools::get(ins, 11, 7);
			break;
		default:
			throw "error in decode";
			break;
		}
	}

	void sign_extend()
	{
		switch (type)
		{
		case R: // no imm
			break;
		case I: case S: case B:
			imm |= tools::gen_con01(tools::get(ins, 31, 31), 31, 12);
			break;
		case U: // nothing to do
			break;
		case J:
			imm |= tools::gen_con01(tools::get(ins, 31, 31), 31, 20);
			break;
		default:
			throw "error in sign extend";
			break;
		}
	}

	void register_fetch()
	{
		switch (type)
		{
		case R: case S: case B:
			rs2 = x[rs2];
			rs1 = x[rs1];
			break;
		case I:
			rs1 = x[rs1];
			break;
		case U: case J:
			break;
		default:
			throw "error in regiter fetch";
			break;
		}
	}

	void run(pipeline *next_ppl)
	{
		if (!is_empty(next_ppl) || is_empty(this)) return;
		get_type();
		decode_all();
		sign_extend();
		register_fetch();
		pass(next_ppl);
	}
};