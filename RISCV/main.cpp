#pragma warning(disable:4996)
#include <map>
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

const unsigned _S = 1 << 13, _M = _S - 1; // 8191 is a prime so we can use bitwise 'and'

unsigned branch_address[_S][2]; // the two addresses some branch may take, 0 for not taken, 1 for taken
unsigned branch_vis_time[_S]; // the time some branch is visited
unsigned branch_history[_S]; // the history of some branch, 0 for not taken, 1 for taken
unsigned branch_taken2[_S][1 << 2]; // the state of the automaton of some branch
/* not used */ unsigned branch_taken[_S][1 << 2][2]; // the times some branch is taken or not

unsigned branch_tot_vis, branch_cor_vis; // the number of times branches are visited (correctly)

/* show the state of all pipelines */
int show_id;
void show_pipeline(int id, pipeline *ppl1, pipeline *ppl2, pipeline *ppl3, pipeline *ppl4, pipeline *ppl5)
{
	printf("%d : ", id);
	printf("%d %d %d %d %d\n", !ppl1->empty, !ppl2->empty, !ppl3->empty, !ppl4->empty, !ppl5->empty);
}

int main()
{
	//freopen("sample/basicopt1.data", "r", stdin);
	//freopen("sample/superloop.data", "r", stdin);

	memory::init_mem();
	pipeline1 *ppl1 = new pipeline1();
	pipeline2 *ppl2 = new pipeline2();
	pipeline3 *ppl3 = new pipeline3();
	pipeline4 *ppl4 = new pipeline4();
	pipeline5 *ppl5 = new pipeline5();
	while (true)
	{
		ppl5->run(nullptr);
		//show_pipeline(++show_id, ppl1, ppl2, ppl3, ppl4, ppl5);
		ppl4->run(ppl5);
		//show_pipeline(++show_id, ppl1, ppl2, ppl3, ppl4, ppl5);
		ppl3->run(ppl4, ppl2);
		//show_pipeline(++show_id, ppl1, ppl2, ppl3, ppl4, ppl5);
		ppl2->run(ppl3);
		//show_pipeline(++show_id, ppl1, ppl2, ppl3, ppl4, ppl5);
		ppl1->run(ppl2);
		//show_pipeline(++show_id, ppl1, ppl2, ppl3, ppl4, ppl5);

		// if (!ppl3->empty)ppl3->show_buffer();

	}
}