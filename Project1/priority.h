#ifndef PRIORITY_H
#define PRIORITY_H
#include"pcb.h"

//链接pcb
void linkpcb(pcb* program)
{
	pcb* first, * second;
	if (program->status == 'R')
	{
		p1->next = program;
		p1 = program;
	}
	if (program->status == 'W')
	{
		if (Wqueue->next == NULL || (program->prio) <= (p2->prio))
		{
			p2->next = program;
			p2 = program;
		}
		else //比较进程优先级,插入适当的位置中
		{
			first = Wqueue;
			second = first->next;
			int flag = 0;
			while (second != NULL)
			{
				if ((program->prio) > (second->prio))
				{
					//若插入进程比当前进程优先数大,插入到当前进程前面
					program->next = second;
					first->next = program;
					flag = 1;
					break;
				}
				else //若插入进程优先数最低,则插入到队尾
				{
					first = first->next;
					second = first->next;
					if (second == NULL && flag == 0)//说明到了最后优先级还是小，要插到表尾
					{
						program->next = second;
						first->next = program;
						flag = 1;
					}
				}

			}

		}
	}
	if (program->status == 'F')
	{
		p3->next = program;
		p3 = program;
	}
}

//进程的初始化
void input()
{
	pcb* p;
	int num, round1;
	cout << "***************************最高优先级优先调度算法******************************\n" << endl;
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
		linkpcb(p);
	}
}

//进程运行
void run()
{
	pcb* program = Wqueue->next;
	Wqueue->next = program->next;//将当前程序从就绪队列中删除
	if (Wqueue != NULL)
		p2 = Wqueue;
	program->status = 'R';//修改程序的状态为运行态
	program->next = NULL;
	linkpcb(program);//将程序重新排入队列中
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
	program->prio = program->prio- 3;//没进行一次，优先级减三

	Rqueue->next = program->next;//将改进程从运行队列中删除
	p1 = Rqueue;
	if (program->needtime == 0)
	{
		program->status = 'F';
		cout << "\n进程" << program->ID << "已经完成！" << endl;
		linkpcb(program);
	}
	else
	{
		program->status = 'W';
		linkpcb(program);
	}
}

//显示程序运作过程
void run_priority_infor()
{
	pcb* head = Wqueue;
	input();	//输入进程
	cout << "\n初始状态如下所示" << endl;
	print();
	while (head->next != NULL)
		run();
	print();
	cout << "\n进程已经全部结束！" << endl;
}


#endif // !PRIORITY_H
