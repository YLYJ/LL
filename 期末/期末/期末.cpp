// 期末.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// test.cpp : Defines the entry point for the console application.



#include "pch.h"
#include <stdlib.h>
#include<stdio.h>
#include <time.h>
#include <string.h>
#include <crtdbg.h>		// 判断内存泄漏

// 玩家链表节点结构体类型

typedef struct M {
	float Hp;
	float	Phisic;
	char	Name[16];
	struct	M *next1;
}Monster;

typedef struct S {
	float hp;
	float Magic;
	char name[16];
	struct S*next2;
}Sprite;
// 玩家链表头节点结构体类型

typedef struct {
	int num1;
	Monster* next1;
}EnemyLinklist1;
typedef struct {
	int num2;
	Sprite* next2;
}EnemyLinklist2;

// 向链表中添加一个节点，此处直接插到链表头部

void AddNewEnemy1(EnemyLinklist1 *head,  Monster* newEnemy)
{
	newEnemy->next1 = head->next1;
	head->next1= newEnemy;
	head->num1++;
}
void AddNewEnemy2(EnemyLinklist2 *head, Sprite* newEnemy)
{
	newEnemy->next2 = head->next2;
	head->next2 = newEnemy;
	head->num2++;
}
// 从链表中删除一个节点，需要注意链表不能断开
void Damage (EnemyLinklist1 *head)                     //对敌人攻击，伤害值为0.4
{
	Monster* p = head->next1;
	while (p != NULL)
	{
		p->Hp -= 0.4;
		p = p->next1;
	}
}
void Damage(EnemyLinklist2 *head)
{
	Sprite* p = head->next2;
	while (p != NULL)
	{
		p->hp -= 0.4;
		p = p->next2;
	}
}
void RemoveEnemy1(EnemyLinklist1 *head, Monster *enemy)

{
	Monster *p = head->next1;
	if (p == enemy)	// 第一个节点是待删除节点
	{
		head->next1 = p->next1;
		free(p);
		head->num1--;
		return;
	}

	while (p->next1 != enemy && p->next1 != NULL)
		p = p->next1;
	if (p->next1 == enemy)	// 删除节点，防止断链
	{
		Monster *tmp = p->next1->next1;
		free(p->next1);
		p->next1 = tmp;
		head->num1--;
	}
}

void RemoveEnemy2(EnemyLinklist2*head, Sprite *enemy)

{
	Sprite*p = head->next2;
	if (p == enemy)	// 第一个节点是待删除节点
	{
		head->next2 = p->next2;
		free(p);
		head->num2--;
		return;
	}

	while (p->next2 != enemy && p->next2 != NULL)
		p = p->next2;
	if (p->next2 == enemy)	// 删除节点，防止断链
	{
		Sprite *tmp = p->next2->next2;
		free(p->next2);
		p->next2 = tmp;
		head->num2--;
	}
}

// 利用递归函数实现，依据玩家的hp对链表中的节点升序排序

// 返回值为排序之后的头节点指针

Monster* SortByHP1(Monster *first)

{
	// 链表中没有节点或者只有一个，则直接返回
	if (first == NULL || first->next1 == NULL)
		return first;
	Monster *minPre = first;	// 保存链表中最小元素的前面一个元素指针
	Monster*p = first->next1;
	// 将minPre设置为最小的元素前面一个元素的指针
	while (p->next1 != NULL)//当链表不是只有两个节点
	{
		if (p->next1->Hp < minPre->next1->Hp)//第二个节点的生命小于第一个节点的生命
			minPre = p;
		p = p->next1;
	}
	if (minPre->next1->Hp < first->Hp)	// 比较最小节点和首节点大小
		// 将最小节点插入到首节点前面
	{
		p = minPre->next1;
		minPre->next1 = p->next1;
		p->next1 = first;
		first = p;
	}
	first->next1 = SortByHP1(first->next1);// 递归，将后续的节点中最小的节点设为首节点，并重新挂接到链表中
	return first;
}
Sprite* SortByHP2(Sprite *first)

{
	// 链表中没有节点或者只有一个，则直接返回
	if (first == NULL || first->next2 == NULL)
		return first;
	Sprite *minPre = first;	// 保存链表中最小元素的前面一个元素指针
	Sprite *p = first->next2;
	// 将minPre设置为最小的元素前面一个元素的指针
	while (p->next2 != NULL)//不是只有两个节点
	{
		if (p->next2->hp < minPre->next2->hp)
			minPre = p;
		p = p->next2;//让第三个节点成为第二个节点用来再次比较
	}
	if (minPre->next2->hp < first->hp)	// 比较最小节点和首节点大小
		// 将最小节点插入到首节点前面
	{
		p = minPre->next2;
		minPre->next2= p->next2;
		p->next2 = first;
		first = p;
	}
	first->next2 = SortByHP2(first->next2);// 递归，将后续的节点中最小的节点设为首节点，并重新挂接到链表中
	return first;
}
Monster * Reverse1(Monster * p)                    //递归函数倒序排列链表
{
	if (p == NULL || p->next1 == NULL) {
		return p;
	}
	Monster * newHead = Reverse1(p->next1);
	p->next1->next1 = p;
	p->next1 = NULL;
	return newHead;
}
Sprite * Reverse2(Sprite * p)                    //递归函数倒序排列链表
{
	if (p == NULL || p->next2 == NULL) {
		return p;
	}
	Sprite * newHead = Reverse2(p->next2);
	p->next2->next2 = p;
	p->next2 = NULL;
	return newHead;
}


// 遍历所有节点

// 遍历所有节点，打印链表中的玩家信息

void Print1(EnemyLinklist1 *head)
{
	Monster* p = head->next1;
	while (p != NULL)
	{
		printf("%s,%.2f,%.2f\t", p->Name, p->Hp, p->Phisic);
		p = p->next1;
	}
	printf("\n");
}
void Print2(EnemyLinklist2 *head)
{
	Sprite* p = head->next2;
	while (p != NULL)
	{
		printf("%s,%.2f,%.2f\t", p->name, p->hp, p->Magic);
		p = p->next2;
	}
	printf("\n");
}
// 释放所有临时占用内存

void Destroy1(EnemyLinklist1 *head)
{
	Monster* p1 = head->next1;
	Monster* q1 = p1->next1;
	while (q1 != NULL)
	{
		q1 = p1->next1;
		free(p1);
		p1 = q1;
	}
	free(head);
}
void Destroy2(EnemyLinklist2 *head)
{
	Sprite* p2 = head->next2;
	Sprite* q2 = p2->next2;
	while (q2 != NULL)
	{
		q2 = p2->next2;
		free(p2);
		p2 = q2;
	}
	free(head);
}

int main()
{
	srand(time(NULL));		// 随机种子
	// 动态生成玩家链表头
	EnemyLinklist1 *head1 = (EnemyLinklist1*)malloc(sizeof(EnemyLinklist1));
	head1->next1 = NULL;
	head1->num1 = 0;
	int nCand1 = rand() % 10;	// 随机待查找和删除的玩家序号
	char *find1 = NULL;		// 待查找玩家姓名
	

	for (int i = 0; i < 10; i++)	// 随机生成10个玩家，并添加到链表中
	{
		Monster *p1 = (Monster*)malloc(sizeof(Monster));
		if (nCand1 == i)
		   p1->Hp = (rand() % 101) / 100.0f-1.00;	// 随机血量，选定的敌人使其生命值为负
		else 
			p1->Hp = (rand() % 101) / 100.0f+0.8;
		p1->Phisic = (rand() % 101) / 100.0f;	// 随机物理攻击值
		p1->Name[0] = 'A' + rand() % 26;	// 随机的名字，为了简便只使用3个字母
		p1->Name[1] = 'A' + rand() % 26;
		p1->Name[2] = 'A' + rand() % 26;
		p1->Name[3] = 'A' + rand() % 26;
		p1->Name[4] = '\0';
		AddNewEnemy1(head1, p1);			// 将新生成的玩家加入列表
		if (nCand1== i)
			find1 = p1->Name;
	}
	EnemyLinklist2 *head2 = (EnemyLinklist2*)malloc(sizeof(EnemyLinklist2));
	head2->next2 = NULL;
	head2->num2 = 0;
	int nCand2 = rand() % 10;	// 随机待查找和删除的玩家序号
	char *find2 = NULL;		// 待查找玩家姓名
	for (int j= 0; j < 10; j++)	// 随机生成20个玩家，并添加到链表中
	{
		Sprite *p2 = (Sprite*)malloc(sizeof(Sprite));
		if (nCand1 == j)
			p2->hp = (rand() % 101) / 100.0f - 1.00;	// 随机血量
		else
			p2->hp = (rand() % 101) / 100.0f + 0.8;
		
		p2->Magic = rand() % 101;	// 随机法力值
		p2->name[0] = 'A' + rand() % 26;	// 随机的名字，为了简便只使用3个字母
		p2->name[1] = 'A' + rand() % 26;
		p2->name[2] = 'A' + rand() % 26;
		p2->name[3] = '\0';
		AddNewEnemy2(head2, p2);			// 将新生成的玩家加入列表
		if (nCand2 == j)
			find2 = p2->name;
	}
	Monster *p1 = head1->next1;  // 搜索这个敌人
	Sprite*p2 = head2->next2; // 搜索这个敌人
	FILE *fp = fopen("note.txt", "w");      //读写文件，并保存为外部文件
	while (p1 != NULL)
	{
		fprintf(fp, "Name：%s   HP:%.2f   Phisic:%.2f    Name：%s   HP:%.2f   Magic:%.2f\t\n", p1->Name, p1->Hp, p1->Phisic, p2->name, p2->hp, p2->Magic);
		p1 = p1->next1;
		p2 = p2->next2;
	}

	fclose(fp);

	printf("\n");
	Print1(head1);						// 打印生成的玩家链表
	printf("Damage to enemy is 0.4\n ");
	Damage(head1);
	Print1(head1);
	printf("After reversing\n");           //倒序
	head1->next1 =Reverse1(head1->next1);
	Print1(head1);
	printf("Sort the list by hp\n");	// 排序
	head1->next1 = SortByHP1(head1->next1);
	Print1(head1);
    p1 = head1->next1;  // 搜索这个敌人
	printf("The first one's hp is smaller than 0,remove it\n");
	RemoveEnemy1(head1, p1);
	Print1(head1);
	printf("\n\n");
	
	Print2(head2);
	printf("Damage to enemy is 0.4\n ");
	Sprite *P = (Sprite*)malloc(sizeof(Sprite));
	Damage(head2);
	Print2(head2);
	printf("After reversing\n");     //倒序，
	head2->next2 = Reverse2(head2->next2);
	Print2(head2);
	printf("Sort the list by hp\n");	// 排序，生命值为负数的为第一个
	head2->next2 = SortByHP2(head2->next2);
	Print2(head2);
    p2 = head2->next2; // 搜索这个敌人
	printf("The first one's hp is smaller than 0,remove it\n");
	RemoveEnemy2(head2, p2);    //删除生命值为负的敌人
	Print2(head2);
	FILE *fp1 = fopen("note.txt", "r");      //读取文件
	system("note.txt");

	// 该语句可以在程序调试运行后的output窗口中输出内存泄漏信息

	// 读者尝试将后面的Destroy函数调用语句删除，就会导致内存泄漏

	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	Destroy1(head1);						// 善后，将所有临时创建内存删除
	Destroy2(head2);
	getchar();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
