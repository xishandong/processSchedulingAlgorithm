#pragma once
#ifndef PCB_H
#define PCB_H
#include<iostream>
#include<random>
using namespace std;

//����pcb
struct pcb
{
	int ID = 0;					//���̱�ʶ��
	int prio = 0;				//����������
	int round = 0;				//��תʱ��Ƭ��
	int alltime = 0;			//��������ʱ��Ƭ��
	int needtime = 0;			//������ɻ���Ҫʱ��
	int rtime = 0;				//�����Ѿ�ִ��ʱ��
	char status = 0;			//���̱�ʶ�� W:����̬��R������̬��F�����̬
	pcb* next = NULL;			//��ָ��
};

//�������ж��У��������У���ɶ���
pcb* Rqueue = new pcb();
pcb* Wqueue = new pcb();
pcb* Fqueue = new pcb();
pcb* p1 = Rqueue;
pcb* p2 = Wqueue;
pcb* p3 = Fqueue;

//��ʾ��Ϣ
void display_infor1()
{
	cout << "\n������\t״̬\t������\t��ʱ��\t������ʱ��" << endl;
}
void display_infor2(pcb* p)
{
	cout << "|" << p->ID << "\t" << "|" << p->status << "\t" << "|" << p->prio
		<< "\t" << "|" << p->alltime << "\t" << "|" << p->rtime << endl;
}

//�����ǰ����״��
void print()
{
	pcb* pr = Rqueue;
	pcb* pw = Wqueue;
	pcb* pf = Fqueue;
	cout << endl << "------------------------------------------------------" << endl;
	int time = 0;//�������㵱ǰcpuʱ��
	pcb* pf1 = Fqueue;
	pcb* pw1 = Wqueue;
	pcb* pr1 = Rqueue;
	//�����ǽ����������г��������е�ʱ�����һ��
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
	cout << "\n��ǰCPUʱ��Ϊ��" << time << endl;
	display_infor1();
	//���ж���
	if (pr->next != NULL)
	{
		pr = pr->next;
		display_infor2(pr);
	}
	//��������
	if (pw->next != NULL)
	{
		//display_infor1();
		while (pw->next != NULL)
		{
			display_infor2(pw->next);
			pw = pw->next;
		}
	}
	//��ɶ���
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
