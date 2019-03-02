#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* 未实现自动增长因子 */

typedef struct Array
{
	int *pBase;
	int len;
	int cnt;
}Arr;

/* must be init */
bool Init_Arr(Arr *const parr, int const len);
bool IsEmpty_Arr(Arr const *const parr);
bool IsFull_Arr(Arr const *const parr);

/*	pos | index		: range [1:parr->len]	*
 *	data			: insert data			*/
bool Insert_Arr(Arr *const parr, int const pos, int const data);
bool Append_Arr(Arr *const parr, int const data);
bool Delet_Arr(Arr *const parr,int const index);
void Clear_Arr(Arr *const parr);
int Get_Arr(Arr const *const parr,int const index);
/* moder		: 1	冒泡	2 选择	*/

void Sort_Arr(Arr *const parr, int const moder);
void Inversion_Arr(Arr *const parr);
void Show_Arr(Arr const *const parr);


int main(int argc,char *argv[],char *env)
{
	Arr arr;
	Init_Arr(&arr, 5);
	Append_Arr(&arr, 2);
	Append_Arr(&arr, 8);
	Append_Arr(&arr, 6);
	Append_Arr(&arr, 4);
	Append_Arr(&arr, 1);

	Show_Arr(&arr);

	getchar();
	return 0;
}

bool Init_Arr(Arr *const parr, int const len)
{
	if (NULL == parr)
	{
		return false;
	}
	else
	{	
		parr->pBase = (int *)malloc(sizeof(int)*len);
		if (NULL == parr->pBase)
		{
			return false;
		}
		parr->len = len;
		parr->cnt = 0;
		return true;
	}
}

bool IsEmpty_Arr(Arr const *const parr)
{
	if (parr->cnt == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IsFull_Arr(Arr const *const parr)
{
	if (parr->cnt == parr->len)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Insert_Arr(Arr *const parr, int const pos, int const data)
{
	if (IsFull_Arr(parr))
	{
		printf("is full\n");
		return false;
	}
	else
	{
		for (int i = parr->cnt; i >= pos; i--)
		{
			parr->pBase[i] = parr->pBase[i - 1];
		}
		parr->pBase[pos - 1] = data;
		++parr->cnt;
		return true;
	}
}

bool Append_Arr(Arr *const parr, int const data)
{
	if (IsFull_Arr(parr))
	{
		printf("is full\n");
		return false;
	}
	else
	{
		parr->pBase[parr->cnt++] = data;
		return true;
	}
}

void Show_Arr(Arr const *const parr)
{
	if (IsEmpty_Arr(parr))
	{
		printf("is empty\n");
	}
	else
	{
		for (int i = 0; i < parr->cnt; i++)
		{
			printf("cnt = %02d	data = %03d\n", i, parr->pBase[i]);
		}
		printf("\n");
	}
}

int Get_Arr(Arr const *const parr, int const index)
{
	return parr->pBase[index - 1];
}

bool Delet_Arr(Arr *const parr, int const index)
{
	if (IsEmpty_Arr(parr))
	{
		return false;
	}
	else
	{
		if (index > parr->cnt)
		{
			return false;
		}
		for (int i=index;i<parr->cnt;i++)
		{
			parr->pBase[i-1] = parr->pBase[i];
		}
		--parr->cnt;
		return true;
	}
}

void Clear_Arr(Arr *const parr)
{
	parr->cnt = 0;
	parr->len = 0;
	free(parr->pBase);
	parr->pBase = NULL;
}

void Inversion_Arr(Arr *const parr)
{
	int tmp;
	for (int *pi = parr->pBase+0, *pj = parr->pBase+parr->cnt - 1; pi < pj; pi++, pj--)
	{
		tmp = *pi;
		*pi = *pj;
		*pj = tmp;
	}
}

static swap(int *const pi, int *const pj)
{
	int tmp;
	tmp = *pi;
	*pi = *pj;
	*pj = tmp;
}

void Sort_Arr(Arr *const parr, int const moder)
{
	switch (moder)
	{
	case 1:
		{
			for (int i = 0; i < parr->cnt - 1; i++)
			{
				for (int j = 0; j < parr->cnt - 1 - i; j++)
				{
					if (parr->pBase[j] > parr->pBase[j + 1])
					{
						swap(parr->pBase + j, parr->pBase + j + 1);
					}
				}
			}
		}
		break;
	case 2:
		{
			for (int i = 0; i < parr->cnt - 1; i++)
			{
				int imin = i;
				for (int j = i + 1; j < parr->cnt; j++)
				{
					if (parr->pBase[j] < parr->pBase[imin])
					{
						imin = j;
					}
				}
				if (imin != i)
				{
					swap(parr->pBase + i, parr->pBase + imin);
				}
			}
		}
		break;
	}
}

