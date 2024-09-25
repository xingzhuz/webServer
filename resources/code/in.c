#include <stdio.h>
#include "stuscore.h"
void  input(struct student  *d,int n)
{
	char *name[N]={"first","second","three"};
	int age[N]={23,34,52};
	float ch[N]={34.1,36.3,45.3};
	float math[N]={67.0,68.1,78.3};

	int i,m;
	printf("please input base number:");
	scanf("%d",&m);

	for(i=0;i<n;i++)
	{
		strcpy(d[i].name,name[i]);
		d[i].age = age[i]+m;
		d[i].ch = ch[i]+m;
		d[i].math = math[i]+m;
	}
}

