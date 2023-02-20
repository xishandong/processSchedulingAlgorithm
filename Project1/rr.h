#ifndef RR_H
#define RR_H
#include"pcb.h"

//���̵�����
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

//������װ���������β��
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
//������װ���������ͷ��
void link2head(pcb* program)
{
	pcb* first, * second;
	first = Wqueue;
	second = first->next;
	program->next = second;
	first->next = program;
}

//���̵ĳ�ʼ��
void input_rr()
{
	pcb* p;
	int num, round1;
	cout << "***************************ʱ��Ƭ��ת�����㷨******************************\n" << endl;
	cout << "�����뼴�����еĽ�������Ŀ��";
	cin >> num;
	cout << "������ʱ��Ƭ��С��";
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


//��������
void run_rr()
{
	pcb* program = Wqueue->next;
	Wqueue->next = program->next;//����ǰ����Ӿ���������ɾ��
	if (Wqueue != NULL)
		p2 = Wqueue;
	program->status = 'R';//�޸ĳ����״̬Ϊ����̬
	program->next = NULL;
	linkpcb_rr(program);//�������������������
	print();
	//�ж�ʣ��ʱ����ʱ��Ƭ��С�Ĺ�ϵ
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
	Rqueue->next = program->next;//���Ľ��̴����ж�����ɾ��
	p1 = Rqueue;
	if (program->needtime == 0)
	{
		program->status = 'F';
		cout << "\n����" << program->ID << "�Ѿ���ɣ�" << endl;
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

//չʾ�㷨��������
void run_rr_infor()
{
	pcb* head = Wqueue;
	input_rr();	//�������
	cout << "\n��ʼ״̬������ʾ" << endl;
	print();
	while (head->next != NULL)
		run_rr();
	print();
	cout << "\n�����Ѿ�ȫ��������" << endl;
}

#endif // !RR_H

