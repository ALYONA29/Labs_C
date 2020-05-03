#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

typedef struct item
{
	int digit;
	struct item *next;
	struct item *prev;
} Item;

typedef struct mnumber
{
	Item *head;
	Item *tail;
	int n;
} MNumber;

MNumber CreateMNumber(char *initStr);
void AddDigit(MNumber *number, int digit);
void PrintNumber(MNumber number);
MNumber SumMNumber(MNumber n1, MNumber n2);
MNumber DifMNumber(MNumber n1, MNumber n2);
MNumber UmnMNumber(MNumber n1, MNumber n2);
MNumber DelMNumber(MNumber n1, MNumber n2, int *count);

int main()
{
	int count = 0;
	MNumber d = CreateMNumber("2");
	MNumber res = CreateMNumber("");
	MNumber one = CreateMNumber("1");
	printf("2^19936 * (2^19937 - 1)\n");
	printf("Base : ");
	PrintNumber(d);
	printf("\n");
	printf("Power : ");
	MNumber e = CreateMNumber("19937");
	PrintNumber(e);
	printf("\n");
	MNumber ost = CreateMNumber("");
	for(int i = 2; i < 142; i++)
	{
		ost = DelMNumber(e, d, &count);
		if(count == 1)
        {
            break;
        }
		d = SumMNumber(d, one);
	}
    if (count == 1)
	{
		printf("\n2^19937 - 1 isn't prime");
	}
	else
	{
	    printf("\n19937 is prime.");
		printf("\n2^19937 - 1 is prime.");
		printf("\nThat why according to Euclid the number is perfect.");
	}
	getchar();
	return 0;
}

MNumber CreateMNumber(char initStr[])
{
	MNumber number = {NULL, NULL, 0};
	int n;
	for(n = strlen(initStr) - 1; n >= 0; n--)
    {
		AddDigit(&number, initStr[n] - '0');
	}
	return number;
}

void AddDigit(MNumber *number, int digit)
{
	Item *p = (Item*) malloc (sizeof(Item));
	p->digit = digit;
	p->next = p->prev = NULL;
	if(number->head == NULL)
	{
		number->head = number->tail = p;
	}
	else
	{
		number->tail->next = p;
		p->prev = number->tail;
		number->tail = p;
    }
	number->n++;
}

void PrintNumber(MNumber number)
{
	Item *p = number.tail;
    while(p)
	{
		printf("%d", p->digit);
		p = p->prev;
	}
}

MNumber SumMNumber(MNumber n1, MNumber n2)
{
	MNumber sum = CreateMNumber("");
	Item *p1 = n1.head, *p2 = n2.head;
	int digit, pos = 0, s1, s2;
	while (p1 || p2)
	{
		if (p1)
		{
			s1 = p1->digit;
            p1 = p1->next;
		}
		else s1 = 0;
		if (p2)
		{
			s2 = p2->digit;
			p2 = p2->next;
		}
		else s2 = 0;
		digit = (s1 + s2 + pos) % 10;
		pos = (s1 + s2 + pos) / 10;
		AddDigit(&sum, digit);
	}
	if (pos) AddDigit(&sum, pos);
	return sum;
}

MNumber DelMNumber(MNumber n1, MNumber n2, int *count)
{
	MNumber del = CreateMNumber("");
	Item *p1 = n1.tail, *p2 = n2.head;
	unsigned long long int digit, ost = 0, s2 = 0, j = 0, s1 = 0, check = 0;
	double i = 0;
	while(p2)
	{
		if(p2->digit == 0)
		{
			s2 *= pow(10, i);
			p2 = p2->next;
			i++;
		}
		else
		{
			s2 += p2->digit * pow(10, i);
			p2 = p2->next;
			i++;
		}
    }
	while(p1)
	{
		if(check == 1)
		{
			ost = ost % s2;
			ost = ost * 10 + p1->digit;
			p1 = p1->prev;
		}
		else
		{
			while(j <= i)
			{
				if(p1->digit == 0)
				{
					ost *= 10;
					p1 = p1->prev;
					j++;
				}
				else
				{
					ost *= 10;
					ost += p1->digit;
					p1 = p1->prev;
					j++;
				}
				if(p1 == NULL)
				{
					break;
				}
			}
			ost = ost % s2;
			if(p1 == NULL)
			{
				break;
			}
			ost = ost * 10 + p1->digit;
			p1 = p1->prev;
		}
		check = 1;
	}
	ost -= ost / s2 *s2;
	if(count == 0)
    {
        *count = 1;
    }
	while(ost != 0)
	{
		int did = ost % 10;
		AddDigit(&del, did);
		ost /= 10;
	}
	return del;
}
