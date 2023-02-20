#include"priority.h"
#include"rr.h"

int main()
{
	int select;
	cout << "请输入想要选择的进程调度方法：";
	cout << "1.优先级调度算法 2.时间片轮转算法" << endl;
	cin >> select;
	if (select == 1)
		run_priority_infor();
	else if (select == 2)
		run_rr_infor();
	return 0;
}
