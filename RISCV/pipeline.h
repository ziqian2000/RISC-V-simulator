#pragma once
enum TYPE { R, I, S, B, U, J };
class pipeline
{
public:

	/*buffer*/
	unsigned ins, rs1, rs2, rd, imm, func3, func7, opcode; 
	bool empty;
	TYPE type;

	pipeline() { empty = true; }
	~pipeline() {}

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
};