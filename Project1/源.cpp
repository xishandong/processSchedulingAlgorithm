#include"priority.h"
#include"rr.h"

int main()
{
	int select;
	cout << "��������Ҫѡ��Ľ��̵��ȷ�����";
	cout << "1.���ȼ������㷨 2.ʱ��Ƭ��ת�㷨" << endl;
	cin >> select;
	if (select == 1)
		run_priority_infor();
	else if (select == 2)
		run_rr_infor();
	return 0;
}
