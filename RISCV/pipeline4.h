#pragma once
#include "pipeline.h"
#include "memory.h"
extern unsigned pc;
class pipeline4 : public pipeline
{
public:
	void execute()
	{
		if (ins == 0x00c68223)
		{
			printf("%d\n", ((unsigned)x[10]) & 255u);
			//for (;;);
			exit(0);
		}
		switch (opcode)
		{
		case 0b0110111: // LUI
			break;
		case 0b0010111: // AUIPC
			imm += pc;
			break;
		case 0b1101111: // JAL
			rs1 = pc + 4;
			pc += imm;
			break;
		case 0b1100111: // JALR
			rs1 = pc + 4;
			pc = imm;
			break;
		case 0b1100011: // ...
			switch (func3)
			{
			case 0b000: // BEQ
				rs1 ? pc += imm : 0;
				break;
			case 0b001: // BNE
				rs1 ? pc += imm : 0;
				break;
			case 0b100: // BLT
				rs1 ? pc += imm : 0;
				break;
			case 0b101: // BGE
				rs1 ? pc += imm : 0;
				break;
			case 0b110: // BLTU
				rs1 ? pc += imm : 0;
				break;
			case 0b111: // BGEU
				rs1 ? pc += imm : 0;
				break;
			}
			break;
		case 0b0000011: // ...

			switch (func3)
			{
			case 0b000: // LB
				imm = memory::read_mem_pos(imm, 8 / 8);
				break;
			case 0b001: // LH
				imm = memory::read_mem_pos(imm, 16 / 8);
				break;
			case 0b010: // LW
				imm = memory::read_mem_pos(imm, 32 / 8);
				break;
			case 0b100: // LBU
				imm = memory::read_mem_pos(imm, 8 / 8);
				break;
			case 0b101: // LHU
				imm = memory::read_mem_pos(imm, 16 / 8);
				break;
			}
			break;
		case 0b0100011: // ...

			switch (func3)
			{
			case 0b000: // SB
				memory::write_mem_pos(imm, 8 / 8, rs2);
				break;
			case 0b001: // SH
				memory::write_mem_pos(imm, 16 / 8, rs2);
				break;
			case 0b010: // SW
				memory::write_mem_pos(imm, 32 / 8, rs2);
				break;
			}
			break;
		case 0b0010011: // ...
			switch (func3)
			{
			case 0b000: // ADDI
				break;
			case 0b010: // SLTI
				break;
			case 0b011: // SLTIU
				break;
			case 0b100: // XORI
				break;
			case 0b110: // ORI
				break;
			case 0b111: // ANDI
				break;
			case 0b001: // SLLI
				break;
			case 0b101: // ...
				switch (func7)
				{
				case 0b0000000: // SRLI
					break;
				case 0b0100000: // SRAI
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
					break;
				case 0b0100000: // SUB
					break;
				}
				break;
			case 0b001: // SLL
				break;
			case 0b010: // SLT
				break;
			case 0b011: // SLTU
				break;
			case 0b100: // XOR
				break;
			case 0b101: // ...
				switch (func7)
				{
				case 0b0000000: // SRL
					break;
				case 0b0100000: // SRA
					break;
				}
				break;
			case 0b110: // OR
				break;
			case 0b111: // AND
				break;
			}
			break;
		}
	}

	void run(pipeline *next_ppl)
	{
		if (!is_empty(next_ppl) || is_empty(this)) return;
		execute();
		pass(next_ppl);
	}
};