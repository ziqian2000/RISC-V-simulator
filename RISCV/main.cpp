#pragma warning(disable:4996)
#include "stdc++.h"
#include "memory.h"
#include "pipeline1.h"
#include "pipeline2.h"
#include "pipeline3.h"
#include "pipeline4.h"
#include "pipeline5.h"

unsigned mem[0x20005]; // memory
unsigned x[32], pc; // user-visible registers

unsigned locked[32], pc_lock; // deal with hazard

unsigned branch_address[0x20005 >> 2][2]; // the two addresses some branch may take, 0 for not taken, 1 for taken
unsigned branch_vis_time[0x20005 >> 2]; // the time some branch is visited
unsigned branch_history[0x20005 >> 2]; // the history of some branch, 0 for not taken, 1 for taken
unsigned branch_taken[0x20005 >> 2][1 << 2][2]; // the times some branch is taken or not
unsigned branch_tot_vis, branch_cor_vis; // the number of times branches are visited (correctly)

int main()
{
	freopen("sample/basicopt1.data", "r", stdin);
	memory::init_mem();
	pipeline1 *ppl1 = new pipeline1();
	pipeline2 *ppl2 = new pipeline2();
	pipeline3 *ppl3 = new pipeline3();
	pipeline4 *ppl4 = new pipeline4();
	pipeline5 *ppl5 = new pipeline5();
	while (true)
	{
		ppl5->run(nullptr);
		ppl4->run(ppl5);
		ppl3->run(ppl4, ppl2);
		ppl2->run(ppl3);
		ppl1->run(ppl2);
	}
}