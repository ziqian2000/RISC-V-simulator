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

int main()
{
	freopen("sample.data", "r", stdin);

	memory::init_mem();
	pipeline1 *ppl1 = new pipeline1();
	pipeline2 *ppl2 = new pipeline2();
	pipeline3 *ppl3 = new pipeline3();
	pipeline4 *ppl4 = new pipeline4();
	pipeline5 *ppl5 = new pipeline5();
	while (true)
	{
		//printf("0 : %d %d %d %d %d\n", ppl1->empty, ppl2->empty, ppl3->empty, ppl4->empty, ppl5->empty);
		ppl1->run(ppl2);
		//printf("1 : %d %d %d %d %d\n", ppl1->empty, ppl2->empty, ppl3->empty, ppl4->empty, ppl5->empty);
		ppl2->run(ppl3);
		//printf("2 : %d %d %d %d %d\n", ppl1->empty, ppl2->empty, ppl3->empty, ppl4->empty, ppl5->empty);
		ppl3->run(ppl4);
		//printf("3 : %d %d %d %d %d\n", ppl1->empty, ppl2->empty, ppl3->empty, ppl4->empty, ppl5->empty);
		ppl4->run(ppl5);
		//printf("4 : %d %d %d %d %d\n", ppl1->empty, ppl2->empty, ppl3->empty, ppl4->empty, ppl5->empty);
		ppl5->run(nullptr);
		//printf("5 : %d %d %d %d %d\n", ppl1->empty, ppl2->empty, ppl3->empty, ppl4->empty, ppl5->empty);

	}
}