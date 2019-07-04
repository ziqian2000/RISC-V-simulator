#pragma once
#include "memory.h"
#include "pipeline.h"
extern unsigned pc_lock;
class pipeline1 : public pipeline
{
public:
	bool test_pc_permission()
	{
		if (pc_lock)
			return false;
		else
			return true;
	}
	void run(pipeline *next_ppl)
	{
		if (!is_empty(next_ppl)) return;
		if (!test_pc_permission()) return; // hazard : unable to get pc as it is locked
		ins = memory::read_mem32();
		pass(next_ppl);
	}
};