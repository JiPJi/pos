#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "stock.h"
//#pragma warning(disable:4996)

extern int balance;
extern struct Product stock[50];
extern struct Product *ptr_stock;
extern struct Product shoppingCart[20];
extern struct Product* ptr_cart;

void calcEarnings(time_t); //(22) end time - start time
void calcMenu(int);
//void calculate();
int checkadult(); // check user is qualified
int checkfresh(int); // check Today is before than Expriry Date

int main()
{
	// Try login
	system("./LOGIN");


	time_t startTime = time(NULL);
	struct tm sTm = *localtime(&startTime);

	int menu = 1;
	int total = 0;

	while(menu != 0){
		// Start Work
		printf("\nOptions \n\n");
		printf("1. Calculate \n");
		printf("2. Management \n");
		printf("0. Finish work. \n\n");
		printf("Go to: ");

		scanf("%d", &menu);
		printf("\n");

		if (menu != 0) {
			switch (menu) {
				case 1:
					total = calculate();
					calcMenu(total);
					break;
				case 2:
					workerMenu();
					break;
			}
			printf("\nPress any key to continue.\n");
			printf("(0 to quit): ");

			scanf("%d", &menu);
		}
	}
	calcEarnings(startTime);

	return 0;
}

void calcMenu(int total)
{
	int pMenu = 1;

	while (pMenu != 0) {
		printf("Pay options \n\n");
		printf("1. Pay by card. \n");
		printf("2. Pay by cash. \n");
		scanf("%d", &pMenu);

		switch (pMenu)
		{
			case 1:
				payByCard(total);
				return;
			case 2:
				payByCash(total);
				return;
			default:
				printf("Invalid value.");
		}
	}
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
	printf("Now: %d-%d-%d %d-%d-%d\n", eTm.tm_year + 1900, eTm.tm_mon + 1, eTm.tm_mday, 
			eTm.tm_hour, eTm.tm_min, eTm.tm_sec);	
	printf("Work is ended!\n");
	printf("Today's work: %d min.\n", -(workMin));
	printf("Today's earning: %d won.\n", -(workMin) * 9200);

}
