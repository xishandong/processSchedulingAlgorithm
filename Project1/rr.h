#ifndef RR_H
#define RR_H
#include"pcb.h"

//进程的链接
void linkpcb_rr(pcb *program)
{
	if (program->status == 'R')
	{
		p1->next = program;
		p1 = program;
	}
	if (program->status == 'F')
	{
		p3->next = program;
		p3 = program;
	}
	if (program->status == 'W')
	{
		p2->next = program;
		p2 = program;
	}
}

//将进程装入就绪队列尾部
void link2end(pcb* program)
{
	pcb* first, * second;
	first = Wqueue;
	second = first->next;
	while (second != NULL)
	{
		first = first->next;
		second = first->next;
	}
	program->next = second;
	first->next = program;
}
//将进程装入就绪队列头部
void link2head(pcb* program)
{
	pcb* first, * second;
	first = Wqueue;
	second = first->next;
	program->next = second;
	first->next = program;
}

//进程的初始化
void input_rr()
{
	pcb* p;
	int num, round1;
	cout << "***************************时间片轮转调度算法******************************\n" << endl;
	cout << "请输入即将运行的进程总数目：";
	cin >> num;
	cout << "请输入时间片大小：";
	cin >> round1;
	for (int i = 1; i <= num; i++)
	{
		p = (pcb*)malloc(sizeof(pcb));
		p->ID = (rand() % (10000 - 100 + 1)) + 100;
		p->alltime = (rand() % (15 - 0 + 1)) + 0;
		p->needtime = p->alltime;
		p->round = round1;
		p->rtime = 0;
		p->prio = (rand() % (100 - 10 + 1)) + 10;
		p->status = 'W';
		p->next = NULL;
		linkpcb_rr(p);
	}
}


//进程运行
void run_rr()
{
	pcb* program = Wqueue->next;
	Wqueue->next = program->next;//将当前程序从就绪队列中删除
	if (Wqueue != NULL)
		p2 = Wqueue;
	program->status = 'R';//修改程序的状态为运行态
	program->next = NULL;
	linkpcb_rr(program);//将程序重新排入队列中
	print();
	//判断剩余时间与时间片大小的关系
	if (program->needtime >= program->round)
	{
		program->rtime = program->rtime + program->round;
		program->needtime = program->needtime - program->round;
	}
	else
	{
		program->rtime = program->rtime + program->needtime;
		program->needtime = 0;
	}
	Rqueue->next = program->next;//将改进程从运行队列中删除
	p1 = Rqueue;
	if (program->needtime == 0)
	{
		program->status = 'F';
		cout << "\n进程" << program->ID << "已经完成！" << endl;
		linkpcb_rr(program);
	}
	else
	{
		program->status = 'W';
		if (p2->next != NULL)
			if (program->prio >= p2->next->prio)
				link2end(program);
			else
				link2head(program);
		else
			link2head(program);
	}
}

//展示算法运作过程
void run_rr_infor()
{
	pcb* head = Wqueue;
	input_rr();	//输入进程
	cout << "\n初始状态如下所示" << endl;
	print();
	while (head->next != NULL)
		run_rr();
	print();
	cout << "\n进程已经全部结束！" << endl;
}

#endif // !RR_H

