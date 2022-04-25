#include<iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include<ctime>
#define N 100
using namespace std;

typedef struct node
{
	char data;//节点数据
	struct node* fir, * sib, * dad;//指向第一个子节点、下一个兄弟节点的指针、父节点
	int childnum;//孩子数
	int depth;//深度
	int totaltime;//计算总时间
	int caltime;//计算时间
	int savetime;//保存时间
	bool flag;//判断要不要保存
}tr;
int k = 0, k1 = 0, t0 = 0, t1 = 0,at=0;
int time0[N], time1[N];
int root = 1;//子树根节点

int createnode(tr* t)//随机生成节点数量
{
	int p;
	p = rand() % 9 + 1;
	if (p >= 1 && p < 4)//0个孩子
		t->childnum = 0;
	if (p >= 4 && p < 8)//1个孩子
		t->childnum = 1;
	if (p >= 8 && p < 9)//2个孩子
		t->childnum = 2;
	if (p >= 9 && p < 10)//3个孩子
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
		if (t->childnum == 0)//叶子节点
		{
			while (t->data == 'A' && t->childnum == 0)
				t->childnum = createnode(t);
			if (t->data != 'A')
			{
				t->fir = NULL;
			}
		}
		if (t->childnum == 1)//孩子数为1
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
		if (t->childnum == 2)//孩子数为2
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
		if (t->childnum == 3)//孩子数为3
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

void showtr(tr* t)//打印多叉树
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

int leaf(tr* t, int root)//计算叶子节点个数
{
	if (!t)
		return 0;
	else if (!t->fir)//叶子节点
		return 1 + leaf(t->sib,root);// 二叉链的结构特性导致需要把兄弟节点返回的个数加一
	else if (root == 1)//根节点情况
	{
		root++;
		return leaf(t->fir,root);
	}
	else //非叶子节点/根节点
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
		cout <<"计算时间是："<<totaltime<< endl;
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

void getpath(tr* t)//打印根到叶子节点的所有路径并计算时间(dfs)
{
	char path[N];
	path[0] = t->data;
	allpath(t, path, 1, t->caltime, t->totaltime);
	 cout << "总时间：";
	 for (int i = 0; i < leaf(t,root); i++)
	 {
		 t0 += time0[i];
	 }
	 cout <<t0<< endl;
	 
}

void newallpath(tr* t, char* path, int n, int caltime, int savetime, int totaltime, bool flag, int childnum,int snum)
{	
	if (t->childnum==0)//已经是叶子节点
	{
		for (int i = 0; i < n; ++i)
		{
			cout << path[i] << " ";
		}
		cout << "计算时间是：" << totaltime <<",保存了"<<snum<<"个节点"<< endl;
		time1[k1] = totaltime;
		k1++;
	}
	
	if (t->childnum>0)//判断有无子节点
	{//就算只有一个子节点，子节点下面的孙子节点可能还有多个子节点
		path[n] = t->fir->data;
		if ((leaf(t,root) - 1) * caltime > savetime)//判断以t为根节点的子树下有几个叶子节点
		{
			t->flag = 1;
			snum++;
			cout <<"该子树叶子节点为："<<leaf(t,root)<< ",保存节点"<<t->data << endl;
			totaltime += savetime;
		}
		totaltime += caltime;
		newallpath(t->fir, path, n + 1, caltime, savetime, totaltime, t->flag, t->fir->childnum,snum);//继续遍历子节点
	}
	//1、走到叶子节点了，遍历叶子节点的兄弟； 2、非叶子节点，其子树已遍历完，准备遍历兄弟节点的子树
	if (t->sib)//判断有无兄弟
	{
		path[n - 1] = t->sib->data;		
		if (t->childnum==0)//情况1
		{
			/*if (t->sib->childnum == 0)//t兄弟节点是叶子节点
			{
				totaltime = (n - snum) * caltime;
			}
			else//t兄弟节点不是叶子节点
			{
				totaltime = (n - snum) * caltime;
			}*///都一样
			totaltime = (n - snum) * caltime;
		}
		else//情况2
		{
			if (t->flag)//t是保存了的节点、t不是叶子节点
			{//不存在t不保存t子节点保存的情况，如果t已经保存那么父节点也会保存
				snum -= 1;//准备遍历t兄弟，保存了的节点数减1（减去t）
				totaltime = (n - snum) * caltime;
				if (!t->sib->fir && n == 2)//被保存了根节点下的叶子节点
					totaltime = caltime;
			}
			else//t没被保存
			{
				totaltime = (n - snum) * caltime;
			}
		}
		newallpath(t->sib, path, n, caltime, savetime, totaltime, t->flag, t->sib->childnum,snum);//指向兄弟节点，遍历他的子节点
	}
	
}

void newgetpath(tr* t)//提高效率后打印根到叶子节点的所有路径和时间(dfs)
{
	char path[N];
	path[0] = t->data;
	
	newallpath(t, path, 1, t->caltime, t->savetime, t->totaltime,t->flag, t->childnum, 0);
	cout << "总时间：";
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
	double eff =0;//提高效率
	double alleff=0;//总效率
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
		cout << endl << "每个节点的计算时间：" << tree->caltime << endl;
		cout << "每个节点的保存时间：" << tree->savetime << endl;
		createnode(tree);
		/*cout <<endl<< "输入每个节点的计算时间：";
		cin >> tree->caltime;
		cout << "输入每个节点的保存时间：";
		cin >> tree->savetime;*/
		tree->totaltime = tree->caltime;
		cout << "从根节点到叶子节点的所有路径:" << endl;
		getpath(tree);
		cout << endl;
		cout << "优化后从根节点到叶子节点的所有路径:" << endl;
		newgetpath(tree);
		eff = 100 * (t0 - t1) / t0;
		cout << "节省时间："<<t0-t1<<",提高效率："<< eff<<"%"<<endl<<endl;
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
	cout << "提高的总效率为：" << alleff / 20 << "%";
}
