﻿// 字符串新.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <stdio.h>
#include <string.h>


void main()
{
	printf("请输入字符:\n");
	char str[100], t;      
	int i, j;
	gets_s(str);
	i = 0;                          //定义输入字符串的第一个字母和最后一个字母的地址
	j = strlen(str) - 1;
	
	while (i < j)                  //根据对称性，通过中间值交换字符串首尾字母的值，实现整体翻转，
		                           //但此时不只单词内部的字母，连单词的顺序也颠倒了
	{
	
		t = str[i];
		str[i] = str[j];
		str[j] = t;
		i++;
		j--;
	}
	//将翻转后的字符串按空格划分，空格之间的字母算作一个单位，                  
	int k;                   
	char *p; 
	k = strlen(str);   
	p = str + k;                     //得到字符串中最后一个单位的地址
	while (1)
	{
		if (p == str)
		{
	
			printf("%s\n", p);
			break;
		}
		if (*p == ' ' && *(p + 1) != ' ')     //从最后一个单位开始，每当遇到空格，就输出空格后的单位，这样又实现了单词顺序的翻转，
			                                  //和最初输入时一样的单词顺序
		{
			*p = '\0';

			printf("%s ", p + 1);
		}
		p--;
	}
	

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
