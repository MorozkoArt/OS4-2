#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct list
{
	int id;
	int time;
	struct list* next;
};

void add(struct list* head, int a, int t) {
	while ((head->next) != NULL) {
		head = head->next;
	}
	struct list* temp = (struct list*)malloc(sizeof(list*));
	head->next = temp;
	temp->id = a;
	temp->time = t;
	temp->next = NULL;
}

void sort(list* head, int c) {
	list* hi = head;
	list* hj = head;
	for (int i = 0; i < c - 1; i++)
	{
		for (int j = (c - 1); j > i; j--)
		{
			hj = head;
			int k = 0;
			while (k != j) {
				hj = hj->next;
				k++;
			}
			if (hi->time > hj->time)
			{
				int tid = hi->id;
				int ttime = hi->time;
				hi->id = hj->id;
				hi->time = hj->time;
				hj->id = tid;
				hj->time = ttime;
			}
		}
		hi = hi->next;
	}
}

int count(list* head) {
	int c = 0;
	while (head) {
		c++;
		head = head->next;
	}
	return(c);
}

int sum(list* head) {
	int s = 0;
	while (head) {
		s += head->time;
		head = head->next;
	}
	return(s);
}
int minsort(int a[], int n, int lasti) {
	int min = 9999999;
	int id = -1;
	int zero = 0;
	for (int i = 0; i < n; ++i) {
		if ((a[i] < min) && (a[i] > 0) && (i != lasti)) {
			min = a[i];
			id = i;
		}
		else {
			if (a[i] == 0) {
				zero++;
			}
		}
	}
	if (zero == n - 1) {
		for (int i = 0; i < n; ++i) {
			if (a[i] != 0) {
				id = i;
			}
		}
	}
	return(id);
}

int uchettime(int a[], int n, int lasti, int b[], int ids[]) {
	int min = 9999999;
	int id = -1;
	int zero = 0;
	for (int i = 0; i < n; ++i) {
		if ((a[i] <= min) && (a[i] > 0) && (i != lasti) && (b[i] == 1)) {
			if (a[i] == min) {
				if (id >= ids[i]) {
					id = ids[i];
				}
			}
			min = a[i];
			id = i;
		}
		else {
			if (a[i] == 0) {
				zero++;
			}
		}
	}
	if (zero == n - 1) {
		for (int i = 0; i < n; ++i) {
			if (a[i] != 0) {
				id = i;
			}
		}
	}
	return(id);
}



int main() {
	setlocale(LC_ALL, "Rus");
	int n, i, t, i1, i2, kv;
	struct list* head = NULL;
	printf("������� ����� �������: \n");
	scanf("%d", &kv);
	printf("������� ���������� ���������: \n");
	scanf("%d", &n);
	printf("������� %d ���������: \n", n);
	for (i = 0; i < n; ++i) {
		if (i == 0) {
			struct list* temp = (struct list*)malloc(sizeof(list*));
			temp->id = i;
			scanf("%d", &temp->time);
			temp->next = head;
			head = temp;
		}
		else {
			scanf("%d", &t);
			add(head, i, t);
		}
	}
	system("cls");
	printf("ID ��������� ���������: ");
	struct list* p = head;
	while (p != NULL) {
		printf("%5d ", p->id + 1);
		p = p->next;
	}
	printf("\n������� ���������:      ");
	p = head;
	while (p != NULL) {
		printf("%5d ", p->time);
		p = p->next;
	}
	printf("\n------------------------------------------------------------------------------------------------\n");
	int c = count(head);
	i1 = sum(head);
	i2 = count(head);
	char** fcfs = (char**)malloc(i1 * sizeof(char*));
	for (int i = 0; i < i1; i++) {
		fcfs[i] = (char*)malloc(i2 * sizeof(char));
	}
	for (int i = 0; i < c; ++i) {
		for (int j = 0; j < i1; ++j) {
			fcfs[i][j] = '0';
		}
	}
	list* f = head;
	int* lis = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		lis[i] = f->time;
		f = f->next;
	}
	f = head;
	int* ids = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		ids[i] = f->id;
		f = f->next;
	}
	int* av = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		av[i] = 0;
	}
	int* lastp = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		av[i] = 0;
	}
	int* ti = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		ti[i] = 0;
	}
	int summa = 0;
	i = 0;
	int nows = 0;
	for (i = 0; i < c; ++i) {
		for (int j = 0; j < i1; ++j) {
			fcfs[i][j] = '�';
		}
	}
	while (summa < i1) {
		if ((av[i] < lis[i]) && (nows < kv)) {
			fcfs[ids[i]][summa] = '�';
			nows++;
			summa++;
			av[i]++;
			lastp[i] = summa;
			ti[ids[i]] = summa;
		}
		else {
			nows = 0;
			if (i < c)
				i++;
			if (i == c) {
				i = 0;
			}
		}
	}
	for (i = 0; i < c; ++i) {
		for (int j = 0; j < i1; ++j) {
			if (j >= lastp[i]) {
				fcfs[ids[i]][j] = ' ';
			}
		}
	}
	printf("\n�������� FCFS: \n");
	printf("\n      ");
	for (int i = 0; i < i1; ++i) {
		printf("%5d ", (i + 1));
	}
	printf("\n");
	printf("\n");
	for (int i = 0; i < i2; ++i) {
		printf("%5d ", (i + 1));
		for (int j = 0; j < i1; ++j) {
			printf("%5c ", fcfs[i][j]);
		}
		printf("\n");
	}
	printf("\n�����, ������ ��� ���������� ���� ��������� = %d\n", summa);
	printf("\n\n����� ���������� |");
	for (int i = 0; i < c; ++i) {
		printf("%5d ", i + 1);
	}
	int summai = 0;
	int summao = 0;
	printf("\n����� ���������� |");
	for (int i = 0; i < c; ++i) {
		printf("%5d ", ti[i]);
		summai += ti[i];
	}
	printf("    ����� = %d", summai);
	printf("\n����� ��������   |");
	for (int i = 0; i < c; ++i) {
		printf("%5d ", (lastp[i] - lis[i]));
		summao += (lastp[i] - lis[i]);
	}
	printf("    ����� = %d\n", summao);
	float sr;
	sr = (float)summai / (float)c;
	printf("������� ����� ����������: %6.2f\n", sr);
	sr = (float)summao / (float)c;
	printf("������� ����� ��������:   %6.2f\n", sr);
	printf("\n------------------------------------------------------------------------------------------------\n");
	sort(head, c);
	printf("\n�������� SJF: \n");
	f = head;
	for (int i = 0; i < c; ++i) {
		lis[i] = f->time;
		ids[i] = f->id;
		f = f->next;
	}
	int* copylis = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		copylis[i] = lis[i];
	}
	char** sjf = (char**)malloc(i1 * sizeof(char*));
	for (int i = 0; i < n; i++) {
		sjf[i] = (char*)malloc(i2 * sizeof(char));
	}
	summa = 0;
	for (int i = 0; i < c; ++i) {
		ti[i] = 0;
		av[i] = 0;
	}
	nows = 0;
	int lasti = -1;
	for (i = 0; i < c; ++i) {
		for (int j = 0; j < i1; ++j) {
			sjf[i][j] = '�';
		}
	}
	i = 0;
	while ((summa < i1) && (minsort(copylis, c, lasti) != -1)) {
		if ((av[ids[i]] < lis[i]) && (nows < kv)) {
			sjf[ids[i]][summa] = '�';
			nows++;
			summa++;
			av[ids[i]]++;
			lastp[ids[i]] = summa;
			ti[ids[i]] = summa;
			copylis[i]--;
		}
		else {
			nows = 0;
			lasti = i;
			i = minsort(copylis, c, lasti);
		}
	}
	for (i = 0; i < c; ++i) {
		for (int j = 0; j < i1; ++j) {
			if (j >= lastp[ids[i]]) {
				sjf[ids[i]][j] = ' ';
			}
		}
	}
	printf("\n      ");
	for (int i = 0; i < i1; ++i) {
		printf("%5d ", (i + 1));
	}
	printf("\n");
	for (int i = 0; i < i2; ++i) {
		printf("%5d ", (i + 1));
		for (int j = 0; j < i1; ++j) {
			printf("%5c ", sjf[i][j]);
		}
		printf("\n");
	}
	printf("\n�����, ������ ��� ���������� ���� ��������� = %d\n", summa);
	printf("\n\n����� ���������� |");
	for (int i = 0; i < c; ++i) {
		printf("%5d ", i + 1);
	}
	summai = 0;
	summao = 0;
	printf("\n����� ���������� |");
	for (int i = 0; i < c; ++i) {
		printf("%5d ", ti[i]);
		summai += ti[i];
	}
	printf("    ����� = %d", summai);
	printf("\n����� ��������   |");
	for (int i = 0; i < c; ++i) {
		int j;
		for (j = 0; j < c; ++j) {
			if (ids[j] == i) {
				break;
			}
		}
		printf("%5d ", (lastp[i] - lis[j]));
		summao += (lastp[i] - lis[j]);
	}
	printf("    ����� = %d\n", summao);
	sr = (float)summai / (float)c;
	printf("������� ����� ����������: %6.2f\n", sr);
	sr = (float)summao / (float)c;
	printf("������� ����� ��������:   %6.2f\n", sr);
	printf("\n------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < c; ++i) {
		copylis[i] = lis[i];
	}
	int* time = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		int j;
		for (j = 0; j < c; ++j) {
			if (ids[j] == i) {
				break;
			}
		}
		printf("\n������� ����� ���������� ��� %d �������� (�������� = %d): ", (ids[j] + 1), lis[j]);
		scanf("%d", &time[j]);
	}
	printf("\n\n\n�������� SJF (���� ������� �����������): \n");
	int* status = (int*)malloc(c * sizeof(int));
	for (int i = 0; i < c; ++i) {
		status[i] = 0;
	}
	summa = 0;
	for (int i = 0; i < c; ++i) {
		ti[i] = 0;
		av[i] = 0;
	}
	lasti = -1;
	int min = 999;
	for (i = 0; i < n; ++i) {
		if (time[i] < min) {
			min = time[i];
		}
	}
	i1 = i1 + min;
	char** sjfv = (char**)malloc(i1 * sizeof(char*));
	for (int i = 0; i < n; i++) {
		sjfv[i] = (char*)malloc(i2 * sizeof(char));
	}
	for (i = 0; i < c; ++i) {
		for (int j = 0; j < i1; ++j) {
			sjfv[i][j] = '�';
		}
	}
	while (summa < i1) {
		for (i = 0; i < c; ++i) {
			if (time[i] == summa) {
				status[i] = 1;
			}
		}
		i = uchettime(copylis, c, lasti, status, ids);
		if (av[ids[i]] < lis[i]) {
			sjfv[ids[i]][summa] = '�';
			summa++;
			av[ids[i]]++;
			lastp[ids[i]] = summa;
			ti[ids[i]] = summa;
			copylis[i]--;
		}
		else {
			lasti = i;
			i = uchettime(copylis, c, lasti, status, ids);
		}
		if (uchettime(copylis, c, lasti, status, ids) == -1)
			break;
	}
	for (i = 0; i < c; ++i) {
		for (int j = 0; j < i1; ++j) {
			if ((j >= lastp[ids[i]]) || (j < time[i])) {
				sjfv[ids[i]][j] = ' ';
			}
		}
	}
	printf("\n      ");
	for (int i = 0; i < i1; ++i) {
		printf("%5d ", i);
	}
	printf("\n");
	for (int i = 0; i < i2; ++i) {
		printf("%5d ", (i + 1));
		for (int j = 0; j < i1; ++j) {
			printf("%5c ", sjfv[i][j]);
		}
		printf("\n");
	}
	printf("\n�����, ������ ��� ���������� ���� ��������� = %d\n", summa);
	printf("\n\n����� ���������� |");
	for (int i = 0; i < c; ++i) {
		printf("%5d ", i + 1);
	}
	summai = 0;
	summao = 0;
	printf("\n����� ���������� |");
	for (int i = 0; i < c; ++i) {
		int j;
		for (j = 0; j < c; ++j) {
			if (ids[j] == i) {
				break;
			}
		}
		printf("%5d ", ti[i] - time[j]);
		summai += ti[i] - time[j];
	}
	printf("    ����� = %d", summai);
	printf("\n����� ��������   |");
	for (int i = 0; i < c; ++i) {
		int j;
		for (j = 0; j < c; ++j) {
			if (ids[j] == i) {
				break;
			}
		}
		printf("%5d ", (lastp[i] - lis[j] - time[j]));
		summao += (lastp[i] - lis[j] - time[j]);
	}
	printf("    ����� = %d\n", summao);
	sr = (float)summai / (float)c;
	printf("������� ����� ����������: %6.2f\n", sr);
	sr = (float)summao / (float)c;
	printf("������� ����� ��������:   %6.2f\n", sr);

}