#pragma once
#ifndef PCB_H
#define PCB_H
#include<iostream>
#include<random>
using namespace std;

//定义pcb
struct pcb
{
	int ID = 0;					//进程标识符
	int prio = 0;				//进程优先数
	int round = 0;				//轮转时间片数
	int alltime = 0;			//进程所需时间片数
	int needtime = 0;			//进程完成还需要时间
	int rtime = 0;				//进程已经执行时间
	char status = 0;			//进程标识符 W:就绪态，R：运行态，F：完成态
	pcb* next = NULL;			//链指针
};

//创建运行队列，就绪队列，完成队列
pcb* Rqueue = new pcb();
pcb* Wqueue = new pcb();
pcb* Fqueue = new pcb();
pcb* p1 = Rqueue;
pcb* p2 = Wqueue;
pcb* p3 = Fqueue;

//显示信息
void display_infor1()
{
	cout << "\n进程名\t状态\t优先数\t总时间\t已运行时间" << endl;
}
void display_infor2(pcb* p)
{
	cout << "|" << p->ID << "\t" << "|" << p->status << "\t" << "|" << p->prio
		<< "\t" << "|" << p->alltime << "\t" << "|" << p->rtime << endl;
}

//输出当前队列状况
void print()
{
	pcb* pr = Rqueue;
	pcb* pw = Wqueue;
	pcb* pf = Fqueue;
	cout << endl << "------------------------------------------------------" << endl;
	int time = 0;//用来计算当前cpu时间
	pcb* pf1 = Fqueue;
	pcb* pw1 = Wqueue;
	pcb* pr1 = Rqueue;
	//下面是将三个队列中程序已运行的时间加在一起
	while (pf1->next != NULL)
	{
		time += pf1->next->rtime;
		pf1 = pf1->next;
	}
	while (pw1->next != NULL)
	{
		time += pw1->next->rtime;
		pw1 = pw1->next;
	}
	while (pr1->next != NULL)
	{
		time += pr1->next->rtime;
		pr1 = pr1->next;
	}
	cout << "\n当前CPU时间为：" << time << endl;
	display_infor1();
	//运行队列
	if (pr->next != NULL)
	{
		pr = pr->next;
		display_infor2(pr);
	}
	//就绪队列
	if (pw->next != NULL)
	{
		//display_infor1();
		while (pw->next != NULL)
		{
			display_infor2(pw->next);
			pw = pw->next;
		}
	}
	//完成队列
	if (pf->next != NULL)
	{
		while (pf->next != NULL)
		{
			display_infor2(pf->next);
			pf = pf->next;
		}
	}
}


#endif // !PCB_H
