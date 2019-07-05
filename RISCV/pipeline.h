#pragma once
enum TYPE { R, I, S, B, U, J };
class pipeline
{
public:

	/* n-bit dynamic branch predictor */
	const unsigned STEP = 2;
	const unsigned MASK = (1 << STEP) - 1;
	const unsigned LEN = 2 * 2; // dynamic 2, automaton ranges from 1 to LEN

	/* buffer with meaningless name */
	unsigned ins, rs1, rs2, rd, imm, func3, func7, opcode; 
	bool empty;
	TYPE type;

	pipeline() { empty = true; }
	~pipeline() {}

	/* because the constant variables STEP and MASK, the default operator "=" is deleted */
	pipeline &operator = (const pipeline &that)
	{
		ins = that.ins;
		rs1 = that.rs1;
		rs2 = that.rs2;
		rd = that.rd;
		imm = that.imm;
		func3 = that.func3;
		func7 = that.func7;
		opcode = that.opcode;
		empty = that.empty;
		type = that.type;
		return *this;
	}

	bool is_empty(pipeline *ppl) {return ppl != nullptr ? ppl->empty : true; }

	/* assuming that next_ppl is empty */
	void pass(pipeline *next_ppl)
	{
		if(next_ppl != nullptr)
		{
			*next_ppl = *this;
			next_ppl->empty = false;
		}
		empty = true;
	}

	void show_buffer()
	{
		printf("ins = %2X\trs1 = %2X\trs2 = %2X\trd = %2X\timm = %2X\tfunc3 = %2X\tfunc7 = %2X\topcode = %2X\tempty = %d\ttype = %d\n",
			ins, rs1, rs2, rd, imm, func3, func7, opcode, empty, type);
	}

};