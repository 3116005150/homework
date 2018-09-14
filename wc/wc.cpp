#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "io.h"
//#include <iostream>

int charcalculate = 0;
int wordcalculate = 0;
//int zhushiline = 0;
int linecalculate = 0;
//int emptyline = 0;

void calculate(char * file)
{
	FILE * fp;
	char a;
	//char befo_a;
	charcalculate = 0;
	wordcalculate = 0;
	linecalculate = 0;
	//zhushiline = 0;
	//int zhushi=0;

	if ((fp = fopen(file, "r")) == NULL)
	{
		printf("read file failed！\n");
		exit(-1);
	}
	while (!feof(fp))
	{
		//befo_a = a;
		a = fgetc(fp);
		//if (a == '/' && a == befo_a) { zhushi = 1; ++zhushiline; }
		if (a != ' '&&a != '\n'&&a != '\t'&&a != ','&&a != '.'&&a != '!'&&a != ';'&&a != '=') {
			charcalculate++;
		}
		if (a == ' ' || a == '\n' || a == '\t' || a == ',' || a == '.' || a == '!' || a == '=' || a == ';' || a == EOF)
			wordcalculate++;
		if (a == '\n' || a == '\t' || a == EOF) {
			linecalculate++;
			//zhushi = 0;
		}
		
	}
	fclose(fp);
}

int main(int argc, char* argv[])
{
	FILE *fp;
	//int flag = 0;//判断是否为扩展功能
	long      Handle;//操作句柄
	struct    _finddata_t   FileInfo;

	//calculate(argv[flag+2]);
	while (1)
	{
		if (argc == 1) {//非命令行启动
			argc = 4; 
			for (int i = 1; i < 4; ++i) {
				argv[i] = (char*)(malloc(sizeof(char[15])));//
			}//
		}else if (!strcmp(argv[1], "-s")) {
			if ((Handle = _findfirst(argv[3], &FileInfo)) == -1L)//用赋值语句返回值判断赋值是否成功
				printf("无适配文件\n");
			else
			{
				//flag = 1;
				do {
					calculate(FileInfo.name);
					//printf("%ld \n", Handle);
					if (!strcmp(argv[2], "-c"))
						printf("文件:%s字符数:%d\n", FileInfo.name, charcalculate);
					else if (!strcmp(argv[2], "-w"))
						printf("文件:%s词数:%d\n", FileInfo.name, wordcalculate);
					else if (!strcmp(argv[2], "-l"))
						printf("文件:%s行数:%d\n", FileInfo.name, linecalculate);
					else if (!strcmp(argv[2], "exit"))
					{
						printf("Exit!\n");
						break;
					}
				} while (_findnext(Handle, &FileInfo) == 0);
				_findclose(Handle);
			}
		}
		else {
			if ((fp = fopen(argv[2], "r")) == NULL)
			{
				printf("无此文件\n\n\n");
			}
			else {
				calculate(argv[2]);
				if (!strcmp(argv[1], "-c"))
					printf("文件:%s字符数:%d\n", argv[2], charcalculate);
				else if (!strcmp(argv[1], "-w"))
					printf("文件:%s词数:%d\n", argv[2], wordcalculate);
				else if (!strcmp(argv[1], "-l"))
					printf("文件:%s行数:%d\n", argv[2], linecalculate);
				else
					printf("无此命令\n");
			}
		} 

		printf("\n");
		printf("1:基础功能 2:拓展功能 其他:退出\n");
		int swi;
		scanf("%d", &swi);
		printf("\n");
		switch (swi) {
		case 1:
			scanf("%s %s", argv[1], argv[2]); break;
		case 2:
			scanf("%s %s %s", argv[1], argv[2], argv[3]); break; 
		default:
			return 0;
		}
	}
	return 0;

}