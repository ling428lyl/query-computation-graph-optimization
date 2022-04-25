#include<iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include<ctime>
#define N 100
using namespace std;

typedef struct node
{
	char data;//�ڵ�����
	struct node* fir, * sib, * dad;//ָ���һ���ӽڵ㡢��һ���ֵܽڵ��ָ�롢���ڵ�
	int childnum;//������
	int depth;//���
	int totaltime;//������ʱ��
	int caltime;//����ʱ��
	int savetime;//����ʱ��
	bool flag;//�ж�Ҫ��Ҫ����
}tr;
int k = 0, k1 = 0, t0 = 0, t1 = 0,at=0;
int time0[N], time1[N];
int root = 1;//�������ڵ�

int createnode(tr* t)//������ɽڵ�����
{
	int p;
	p = rand() % 9 + 1;
	if (p >= 1 && p < 4)//0������
		t->childnum = 0;
	if (p >= 4 && p < 8)//1������
		t->childnum = 1;
	if (p >= 8 && p < 9)//2������
		t->childnum = 2;
	if (p >= 9 && p < 10)//3������
		t->childnum = 3;
	return t->childnum;
}

void inittree(tr* t, int depth,int childnum)
{
	if (depth == 4)
	{
		t->childnum = 0;
		t->fir = NULL;
	}
	if (depth <4)
	{
		if (t->childnum == 0)//Ҷ�ӽڵ�
		{
			while (t->data == 'A' && t->childnum == 0)
				t->childnum = createnode(t);
			if (t->data != 'A')
			{
				t->fir = NULL;
			}
		}
		if (t->childnum == 1)//������Ϊ1
		{
			tr* child = new node();
			child->data = t->data + 1;
			child->dad = t;
			child->depth=t->depth +1;
			child->childnum = createnode(child);
			t->fir = child;
			child->sib = NULL;
			inittree(child, child->depth,child->childnum);
		}
		if (t->childnum == 2)//������Ϊ2
		{
			tr* child1 = new node();
			child1->data = t->data + 1;
			child1->dad = t;
			child1->depth=t->depth +1;
			child1->childnum = createnode(child1);
			t->fir= child1;
			inittree(child1, child1->depth,child1->childnum);		
			tr* child2 = new node();
			child2->data = child1->data + 1;
			child2->dad = t;
			child2->depth = t->depth + 1;
			child2->sib = NULL;
			child2->childnum = createnode(child2);
			child1->sib = child2;
			inittree(child2, child2->depth, child2->childnum);
			
		}
		if (t->childnum == 3)//������Ϊ3
		{
			tr* child1 = new node();
			child1->data = t->data + 1;
			child1->dad = t;
			child1->data = t->data + 1;
			child1->depth = t->depth + 1;
			child1->childnum = createnode(child1);
			t->fir = child1;
			inittree(child1, child1->depth, child1->childnum);			
			tr* child2 = new node();
			child2->data = child1->data + 1;
			child2->dad = t;
			child2->depth = t->depth + 1;
			child2->childnum = createnode(child2);
			child1->sib = child2;
			inittree(child2, child2->depth, child2->childnum);		
			tr* child3 = new node();
			child3->data = child2->data + 1;
			child3->dad = t;
			child3->depth = t->depth + 1;
			child3->childnum = createnode(child3);
			child2->sib = child3;
			inittree(child3, child3->depth, child3->childnum);
		}
	}
}

void showtr(tr* t)//��ӡ�����
{
	if (t)
	{
		cout << t->data;
		if (t->fir)
		{
			cout << "(";
			tr* p = t->fir;
			showtr(p);
			p = p->sib;
			while (p)
			{
				cout << ",";
				showtr(p);
				p = p->sib;
			}
			cout << ")";
		}
	}
}

int leaf(tr* t, int root)//����Ҷ�ӽڵ����
{
	if (!t)
		return 0;
	else if (!t->fir)//Ҷ�ӽڵ�
		return 1 + leaf(t->sib,root);// �������Ľṹ���Ե�����Ҫ���ֵܽڵ㷵�صĸ�����һ
	else if (root == 1)//���ڵ����
	{
		root++;
		return leaf(t->fir,root);
	}
	else //��Ҷ�ӽڵ�/���ڵ�
		return leaf(t->fir,root) + leaf(t->sib,root);
}

void allpath(tr* t, char* path, int n,int caltime,int totaltime)
{
	if (!t->fir)
	{	
		for (int i = 0; i < n; ++i)
		{
			cout << path[i] << " ";
		}
		cout <<"����ʱ���ǣ�"<<totaltime<< endl;
		time0[k] = totaltime;
		k++;
	}
	if (t->fir)
	{
		path[n] = t->fir->data;
		allpath(t->fir, path, n + 1,caltime,totaltime+caltime);
	}
	if (t->sib)
	{
		path[n - 1] = t->sib->data;
		allpath(t->sib, path, n,caltime,totaltime);
	}
}

void getpath(tr* t)//��ӡ����Ҷ�ӽڵ������·��������ʱ��(dfs)
{
	char path[N];
	path[0] = t->data;
	allpath(t, path, 1, t->caltime, t->totaltime);
	 cout << "��ʱ�䣺";
	 for (int i = 0; i < leaf(t,root); i++)
	 {
		 t0 += time0[i];
	 }
	 cout <<t0<< endl;
	 
}

void newallpath(tr* t, char* path, int n, int caltime, int savetime, int totaltime, bool flag, int childnum,int snum)
{	
	if (t->childnum==0)//�Ѿ���Ҷ�ӽڵ�
	{
		for (int i = 0; i < n; ++i)
		{
			cout << path[i] << " ";
		}
		cout << "����ʱ���ǣ�" << totaltime <<",������"<<snum<<"���ڵ�"<< endl;
		time1[k1] = totaltime;
		k1++;
	}
	
	if (t->childnum>0)//�ж������ӽڵ�
	{//����ֻ��һ���ӽڵ㣬�ӽڵ���������ӽڵ���ܻ��ж���ӽڵ�
		path[n] = t->fir->data;
		if ((leaf(t,root) - 1) * caltime > savetime)//�ж���tΪ���ڵ���������м���Ҷ�ӽڵ�
		{
			t->flag = 1;
			snum++;
			cout <<"������Ҷ�ӽڵ�Ϊ��"<<leaf(t,root)<< ",����ڵ�"<<t->data << endl;
			totaltime += savetime;
		}
		totaltime += caltime;
		newallpath(t->fir, path, n + 1, caltime, savetime, totaltime, t->flag, t->fir->childnum,snum);//���������ӽڵ�
	}
	//1���ߵ�Ҷ�ӽڵ��ˣ�����Ҷ�ӽڵ���ֵܣ� 2����Ҷ�ӽڵ㣬�������ѱ����꣬׼�������ֵܽڵ������
	if (t->sib)//�ж������ֵ�
	{
		path[n - 1] = t->sib->data;		
		if (t->childnum==0)//���1
		{
			/*if (t->sib->childnum == 0)//t�ֵܽڵ���Ҷ�ӽڵ�
			{
				totaltime = (n - snum) * caltime;
			}
			else//t�ֵܽڵ㲻��Ҷ�ӽڵ�
			{
				totaltime = (n - snum) * caltime;
			}*///��һ��
			totaltime = (n - snum) * caltime;
		}
		else//���2
		{
			if (t->flag)//t�Ǳ����˵Ľڵ㡢t����Ҷ�ӽڵ�
			{//������t������t�ӽڵ㱣�����������t�Ѿ�������ô���ڵ�Ҳ�ᱣ��
				snum -= 1;//׼������t�ֵܣ������˵Ľڵ�����1����ȥt��
				totaltime = (n - snum) * caltime;
				if (!t->sib->fir && n == 2)//�������˸��ڵ��µ�Ҷ�ӽڵ�
					totaltime = caltime;
			}
			else//tû������
			{
				totaltime = (n - snum) * caltime;
			}
		}
		newallpath(t->sib, path, n, caltime, savetime, totaltime, t->flag, t->sib->childnum,snum);//ָ���ֵܽڵ㣬���������ӽڵ�
	}
	
}

void newgetpath(tr* t)//���Ч�ʺ��ӡ����Ҷ�ӽڵ������·����ʱ��(dfs)
{
	char path[N];
	path[0] = t->data;
	
	newallpath(t, path, 1, t->caltime, t->savetime, t->totaltime,t->flag, t->childnum, 0);
	cout << "��ʱ�䣺";
	for (int i = 0; i < leaf(t,root); i++)
	{
		t1 += time1[i];
	}
	cout<<t1<<endl;
}


int main()
{	
	srand((unsigned)time(NULL));
	int p=0;
	double eff =0;//���Ч��
	double alleff=0;//��Ч��
	while (p < 20)
	{
		tr* tree = new node();
		tree->data = 'A';
		tree->depth = 0;
		tree->caltime = rand()%4+1;
		tree->savetime = rand() % (3* tree->caltime) + (2 * tree->caltime);
		tree->flag = 0;
		while (tree->childnum == 0)
			createnode(tree);
		inittree(tree, tree->depth, tree->childnum);
		showtr(tree);
		cout << endl << "ÿ���ڵ�ļ���ʱ�䣺" << tree->caltime << endl;
		cout << "ÿ���ڵ�ı���ʱ�䣺" << tree->savetime << endl;
		createnode(tree);
		/*cout <<endl<< "����ÿ���ڵ�ļ���ʱ�䣺";
		cin >> tree->caltime;
		cout << "����ÿ���ڵ�ı���ʱ�䣺";
		cin >> tree->savetime;*/
		tree->totaltime = tree->caltime;
		cout << "�Ӹ��ڵ㵽Ҷ�ӽڵ������·��:" << endl;
		getpath(tree);
		cout << endl;
		cout << "�Ż���Ӹ��ڵ㵽Ҷ�ӽڵ������·��:" << endl;
		newgetpath(tree);
		eff = 100 * (t0 - t1) / t0;
		cout << "��ʡʱ�䣺"<<t0-t1<<",���Ч�ʣ�"<< eff<<"%"<<endl<<endl;
		alleff += eff;
		k = 0; k1 = 0; t0 = 0; t1 = 0; eff = 0;
		for (int i = 0; i < leaf(tree,root); i++)
		{
			time0[i] = 0;
			time1[i] = 0;
		}
		delete tree;
		p++;
		system("pause");
	}
	cout << "��ߵ���Ч��Ϊ��" << alleff / 20 << "%";
}