#ifndef  _STUSCORE_H
#define _STUSCORE_H

#define   N   3
struct  student       //ѧ����Ϣ�ṹ��
{
	char name[32];
	int  age;
	float  math;
	float  ch;
	float  sum;
	float  ave;
};

void  calculate(struct student  *d,int n);
void  input(struct student  *d,int n);
void  output(struct student  *d,int n);

#endif
