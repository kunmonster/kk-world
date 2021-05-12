#include<stdio.h>
#include<string.h>
#include<iostream>
char left[3][7] ,right[3][7],result[3][7];
int status[12];
bool isbalance()
{
	int i, j, leftw, rightw;
	for (i = 0; i<3; i++)
	{
		leftw = rightw = 0;
		for (j = 0; (j<6) && (left[i][j] != 0); j++)
		{
			leftw += status[left[i][j] - 'A'];
			rightw += status[right[i][j] - 'A'];
		}
		if(leftw == rightw && result[i][0] != 'e')
			return false;
		if(leftw> rightw && result[i][0] != 'u')
			return false;
		if(leftw< rightw && result[i][0] !='d' )
			return false;
	}
	return true;
}
int main()
{
	int num, i;
	scanf("%d", &num);
	while (num-->0)
	{
		for (i = 0; i < 3; i++)
			scanf("%s %s %s", left[i], right[i], result[i]);
	}
	for (i = 0; i < 0; i++)
		status[i] = 0;
	for (i = 0; i < 12; i++)
	{
		//假设第i枚重的
		status[i] = 1;
		for (i = 0; i < 12; i++)
		if (isbalance())break;
		//假设第i枚是轻的
		status[i] = 0;
		for (i = 0; i < 12; i++)
		if (isbalance())break;
		//假设第i枚是真币
		status[i] = 0;
	}
	printf("%c is the counterfeit coin and it is %s\n", i + 'A', status[i]>0 ? "heavy" : "light");
  system("pause");
  return 0;
}