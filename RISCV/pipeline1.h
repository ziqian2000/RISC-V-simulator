#pragma once
#include "memory.h"
#include "pipeline.h"
class pipeline1 : public pipeline
{
public:
	void run(pipeline *next_ppl)
	{
		if (!is_empty(next_ppl)) return;
		ins = memory::read_mem32();
		pass(next_ppl);
	}
};