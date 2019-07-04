#pragma once
#include "pipeline.h"
#include "memory.h"
extern unsigned x[], pc, locked[];
class pipeline5 : public pipeline
{
public:
	void execute()
	{
		switch (opcode)
		{
		case 0b0110111: // LUI
			x[rd] = imm;
			break;
		case 0b0010111: // AUIPC
			x[rd] = imm;
			break;
		case 0b1101111: // JAL
			rd ? x[rd] = rs1 : 0;
			break;
		case 0b1100111: // JALR
			rd ? x[rd] = rs1 : 0;
			break;
		case 0b1100011: // ...
			switch (func3)
			{
			case 0b000: // BEQ
				break;
			case 0b001: // BNE
				break;
			case 0b100: // BLT
				break;
			case 0b101: // BGE
				break;
			case 0b110: // BLTU
				break;
			case 0b111: // BGEU
				break;
			}
			break;
		case 0b0000011: // ...
			switch (func3)
			{
			case 0b000: // LB
				x[rd] = int(char(imm));
				break;
			case 0b001: // LH
				x[rd] = int(short(imm));
				break;
			case 0b010: // LW
				x[rd] = imm;
				break;
			case 0b100: // LBU
				x[rd] = imm;
				break;
			case 0b101: // LHU
				x[rd] = imm;
				break;
			}
			break;
		case 0b0100011: // ...
			switch (func3)
			{
			case 0b000: // SB
				break;
			case 0b001: // SH
				break;
			case 0b010: // SW
				break;
			}
			break;
		case 0b0010011: // ...
			switch (func3)
			{
			case 0b000: // ADDI
				x[rd] = rs1;
				break;
			case 0b010: // SLTI
				x[rd] = rs1;
				break;
			case 0b011: // SLTIU
				x[rd] = rs1;
				break;
			case 0b100: // XORI
				x[rd] = rs1;
				break;
			case 0b110: // ORI
				x[rd] = rs1;
				break;
			case 0b111: // ANDI
				x[rd] = rs1;
				break;
			case 0b001: // SLLI
				x[rd] = rs1;
				break;
			case 0b101: // ...
				switch (func7)
				{
				case 0b0000000: // SRLI
					x[rd] = rs1;
					break;
				case 0b0100000: // SRAI
					x[rd] = rs1;
					break;
				}
				break;
			}
			break;
		case 0b0110011: // ...
			switch (func3)
			{
			case 0b000: // ...
				switch (func7)
				{
				case 0b0000000: // ADD
					x[rd] = rs1;
					break;
				case 0b0100000: // SUB
					x[rd] = rs1;
					break;
				}
				break;
			case 0b001: // SLL
				x[rd] = rs1;
				break;
			case 0b010: // SLT
				x[rd] = rs1;
				break;
			case 0b011: // SLTU
				x[rd] = rs1;
				break;
			case 0b100: // XOR
				x[rd] = rs1;
				break;
			case 0b101: // ...
				switch (func7)
				{
				case 0b0000000: // SRL
					x[rd] = rs1;
					break;
				case 0b0100000: // SRA
					x[rd] = rs1;
					break;
				}
				break;
			case 0b110: // OR
				x[rd] = rs1;
				break;
			case 0b111: // AND
				x[rd] = rs1;
				break;
			}
			break;
		}
	}

	void unlock_register()
	{
		switch (type)
		{
		case R:	case I:	case U:	case J:
			locked[rd]--;
			break;
		default: // no rd
			break;
		}
	}

	void run(pipeline *next_ppl)
	{
		if (!is_empty(next_ppl) || is_empty(this)) return;
		execute();
		unlock_register(); // hazard : unlock the rd register
		pass(next_ppl);
	}
};