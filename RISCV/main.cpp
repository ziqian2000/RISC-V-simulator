
/**
 *
 * 如何展示这份代码：
 *		解释五级流水
 *		调用show_pipeline()展示每一次流水中各阶段的占用情况（main）
 *		使用pipeline类的成员函数show_buffer展示流水中的内容（main）
 *		解释分支预测并展示代码（pipeline2，pipeline3）
 *
 */

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

unsigned branch_address[0x20005 >> 2][2]; // the two addresses some branch may take, 0 for not taken, 1 for taken
unsigned branch_vis_time[0x20005 >> 2]; // the time some branch is visited
unsigned branch_history[0x20005 >> 2]; // the history of some branch, 0 for not taken, 1 for taken
unsigned branch_taken[0x20005 >> 2][1 << 2][2]; // the times some branch is taken or not
unsigned branch_tot_vis, branch_cor_vis; // the number of times branches are visited (correctly)

std::map<unsigned, unsigned> hash_table; // hash_table in branch_predictor
unsigned timer;

/* show the state of all pipelines */
int show_id;
void show_pipeline(int id, pipeline *ppl1, pipeline *ppl2, pipeline *ppl3, pipeline *ppl4, pipeline *ppl5)
{
	printf("%d : ", id);
	printf("%d %d %d %d %d\n", !ppl1->empty, !ppl2->empty, !ppl3->empty, !ppl4->empty, !ppl5->empty);
}

int main()
{
	//freopen("sample/expr.data", "r", stdin);
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

		//if (!ppl3->empty)ppl3->show_buffer();

	}
}