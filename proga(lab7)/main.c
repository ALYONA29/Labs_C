#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "List.h"
#include "Source.h"
#include "Checker.h"

void add_account(struct List* list);

int main(void)
{
	struct List* list = (struct List*)calloc(1, sizeof(struct List));
	int switch_menu;
	unsigned long long int account_number;
	char* passport_series;
	int sum;
	char* surname;
	struct Node* account;
	while(1)
	{
		switch_menu = 0;
		printf("\nMenu\n");
		printf("1) Add account\n");
		printf("2) Add deposit\n");
		printf("3) Search\n");
		printf("4) Sort deposit\n");
		printf("5) Balance\n");
		printf("6) Put money\n");
		printf("7) Get money\n");
		printf("8) Transfer money\n");
		printf("9) Account statement\n");
		printf("10) Calculate interest rate\n");
		printf("11) Remove account\n");
		printf("12) Remove deposit\n");
		printf("13) Print all accounts\n");
		printf("14) Exit\n");
		switch_menu = check("", -1, 15);
		switch (switch_menu)
		{
			case 1:
				add_account(list);
				break;
			case 2:
				account_number = long_checker("Please, enter account: ");
				struct Node* account = find_account(list->head, account_number);
				if (account != NULL)
				{
					char* deposit_category = deposit_checker();
					int Balance = check("Please, enter deposit summ: ", -1, 10000);
					add_deposit(account, account->passport_series, deposit_category, Balance);
				}
				else
				{
					printf("Invalid account\n");
				}
				break;
			case 3:
				surname = string_checker("Please, enter surname in latin: ", "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM");
				find_surname(list->head, surname);
				free(surname);
				break;
			case 4:
				account_number = long_checker("Please, enter account: ");
				account = find_account(list->head, account_number);
				sort(account);
				break;
			case 5:
				account_number = long_checker("Please, enter account: ");
				get_balance(list, account_number);
				break;
			case 6:
				account_number = long_checker("Please, enter account: ");
				sum = check("Please, enter deposit summ: ", -1, 10000);
				put_money(list, account_number, sum);
				break;
			case 7:
				account_number = long_checker("Please, enter account: ");
				sum = check("Please, enter deposit summ: ", -1, 10000);
				get_money(list, account_number, sum);
				break;
			case 8:
				account_number = long_checker("Please, enter account from we take: ");
				unsigned long long int to = long_checker("Please, enter account to we add: ");
				sum = check("Please, enter deposit summ: ", -1, 10000);
				transfer(list, account_number, to, sum);
				break;
			case 9:
				account_number = long_checker("Please, enter account: ");
				show_history(account_number);
				break;
			case 10:
				sum = check("Please, enter deposit summ: ", -1, 10000);
				char* from_date = get_time("Please, enter deposit openning date(##.##.####): ");
				char* to_date = get_time("Please, enter deposit closing date(##.##.####): ");
				printf("Result: %lf\n", sum + get_percent(sum, from_date, to_date));
				free(from_date);
				free(to_date);
				break;
            case 11:
			case 12:
				account_number = long_checker("Please, enter account(you will lose all your money in deposit): ");
				account = find_account(list->head, account_number);
				if (account != NULL)
				{
					passport_series = string_checker("Please, enter passport series(you will lose all your money in deposit): ", "QWERTYUIOPLKJHGFDSAZXCVBNM1234567890");
					if (strcmp(account->passport_series,passport_series) != 0)
					{
						printf("Invalid passport series\n");
						break;
					}
					if (switch_menu == 4)
					{
						show_dep(account);
						int index = check("Please, enter index: ", 0, account->dep_size + 1);
						index--;
						pop(list, passport_series, index);
					}
					else
					{
						while (pop(list, passport_series, 0));
					}
					free(passport_series);
				}
				else
				{
					printf("Invalid account\n");
				}
				break;
			case 13:
				print(list->head);
                break;
			case 14:
				free_list(list);
				free(list);
				return 0;
			default:
				break;
		}
	}
}

void add_account(struct List* list)
{
	char* name = string_checker("Please, enter name in latin: ", "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM");
	char* surname = string_checker("Please, enter surname in latin: ", "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM");
	char* issuing_authority = string_checker("Please, enter issuing authority: ", "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM");
	char* passport_series = string_checker("Please, enter passport series: ", "QWERTYUIOPLKJHGFDSAZXCVBNM1234567890");
	char* time_in = get_time("Please, enter date of issue passport(##.##.####): ");
	char* time_expired = get_time("Please, enter passport validity(##.##.####): ");
	char* deposit_category = deposit_checker();
	int Balance = check("Please, enter deposit summ: ", -1, 10000);
	push_back(deposit_category, name, surname, issuing_authority, time_in, time_expired, passport_series, Balance, list);
}
