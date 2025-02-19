#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "stock.h"

extern int balance;
extern struct Product stock[50];
extern struct Product *ptr_stock;

void calcEarnings(time_t); //(22) end time - start time
void calcMenu(int);
void calc();

int main()
{
	// Try login
	system("./LOGIN");


	time_t startTime = time(NULL);
	struct tm sTm = *localtime(&startTime);

	int menu = 1;

	while(menu != 0){
		// Start Work
		printf("\nOptions \n\n");
		printf("1. Calculate \n");
		printf("2. Management \n\n");
		printf("Go to: ");

		scanf("%d", &menu);
		printf("\n");

		switch (menu) {
			case 1:
				calc();
				break;
			case 2:
				workerMenu();
				break;
		}
		printf("\nPress 0 to finish work : ");
		scanf("%d", &menu);
	}

	calcEarnings(startTime);

	return 0;
}

void calcMenu(int total)
{
	int menu = 0;
	int pMenu = 0;

	printf("Options\n\n");
	printf("1. Print all product\n");
	printf("2. Start shopping\n");
	scanf("%d", &menu);

	switch(menu)
	{
		case 1:
			printallproduct(ptr_stock);
			break;
		case 2:
			calc();
			printf("Pay options \n\n");
			printf("1. Pay by card. \n");
			printf("2. Pay by cash. \n");
			scanf("%d", &pMenu);

			switch(pMenu)
			{
				case 1:
					payByCard(total);
					break;
				case 2:
					payByCash(total);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void calc()
{	
	int total = 0;
	struct Product *ptr_cart = NULL;
	
	// shopping
	chooseproduct(ptr_stock, ptr_cart);

	// Check is adult & expiry date
	for(int i = 0; i < sizeof(ptr_cart); ++i)
	{
		if((ptr_cart->for_adult) != 0)
		{
			if(checkadult() == 0)
			{
				for(int j = 0; j < sizeof(ptr_cart) - 1; ++j)
				{
					ptr_cart[j] = ptr_cart[j + 1];
				}
			}
		} 
		// Check expiry date
		if(checkfresh(ptr_cart[i].exDate) != 0)
		{
			for(int j = 0; j < sizeof(ptr_cart) - 1; ++j)
			{
				ptr_cart[j] = ptr_cart[j + 1];
			}

		}
	}
	
	// Calculate total price
	total = printshopcart(ptr_stock);
	calcMenu(total);

}

void calcEarnings(time_t startTime)
{
	struct tm sTm = *localtime(&startTime);

	time_t endTime = time(NULL);
	struct tm eTm = *localtime(&endTime);
	
	// calculating time for today's work
	int workMin = ((sTm.tm_hour - eTm.tm_hour) * 60) + (sTm.tm_min - eTm.tm_min);

	// print current time, how many times he/she worked
	// and earnings for today
	printf("Now: %d-%d-%d %d-%d-%d\n", eTm.tm_year, eTm.tm_mon, eTm.tm_mday, 
			eTm.tm_hour, eTm.tm_min, eTm.tm_sec);	
	printf("Work is ended!\n");
	printf("Today's work: %d min.\n", -(workMin));
	printf("Today's earning: %d won.\n", -(workMin) * 9200);

}
