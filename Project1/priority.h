#ifndef PRIORITY_H
#define PRIORITY_H
#include"pcb.h"

//����pcb
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
		else //�ȽϽ������ȼ�,�����ʵ���λ����
		{
			first = Wqueue;
			second = first->next;
			int flag = 0;
			while (second != NULL)
			{
				if ((program->prio) > (second->prio))
				{
					//��������̱ȵ�ǰ������������,���뵽��ǰ����ǰ��
					program->next = second;
					first->next = program;
					flag = 1;
					break;
				}
				else //������������������,����뵽��β
				{
					first = first->next;
					second = first->next;
					if (second == NULL && flag == 0)//˵������������ȼ�����С��Ҫ�嵽��β
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

//���̵ĳ�ʼ��
void input()
{
	pcb* p;
	int num, round1;
	cout << "***************************������ȼ����ȵ����㷨******************************\n" << endl;
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
		linkpcb(p);
	}
}

//��������
void run()
{
	pcb* program = Wqueue->next;
	Wqueue->next = program->next;//����ǰ����Ӿ���������ɾ��
	if (Wqueue != NULL)
		p2 = Wqueue;
	program->status = 'R';//�޸ĳ����״̬Ϊ����̬
	program->next = NULL;
	linkpcb(program);//�������������������
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
	program->prio = program->prio- 3;//û����һ�Σ����ȼ�����

	Rqueue->next = program->next;//���Ľ��̴����ж�����ɾ��
	p1 = Rqueue;
	if (program->needtime == 0)
	{
		program->status = 'F';
		cout << "\n����" << program->ID << "�Ѿ���ɣ�" << endl;
		linkpcb(program);
	}
	else
	{
		program->status = 'W';
		linkpcb(program);
	}
}

//��ʾ������������
void run_priority_infor()
{
	pcb* head = Wqueue;
	input();	//�������
	cout << "\n��ʼ״̬������ʾ" << endl;
	print();
	while (head->next != NULL)
		run();
	print();
	cout << "\n�����Ѿ�ȫ��������" << endl;
}


#endif // !PRIORITY_H
