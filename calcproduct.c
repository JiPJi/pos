#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"
#include <time.h>
//#pragma warning(disable:4996)

extern struct Product stock[50];
extern struct Product *ptr_stock;
extern int balance;

struct Product shoppingCart[20] = { 0, '0', '0', 0, 0, 0, 0 };
struct Product *ptr_cart = shoppingCart;

void printallproduct(struct Product*); // print all product
void chooseproduct(int); // user can choose product in this func
int printshopcart(struct Product*); // Print element of shopping cart & total
int checkadult(); // check user is qualified
int checkfresh(int); // check Today is before than Expriry Date
void payByCard(int); // Get card number and add money to balance
void payByCash(int); // Return change and add moeny to balance
int calculate();


// print all product
void printallproduct(struct Product *ptr)
{
	printf("These are what we have... \n\n");

	for(int i = 0; i < 20; ++i)
	{
		if (ptr[i].pID != 0) {
			printf("ID : %d\n", ptr[i].pID);
			printf("%s: \n", ptr[i].pName);
			printf("This product made from %s\n", ptr[i].pMaker);
			printf("price: %d ,", ptr[i].product_price);
			printf("Expiry Date: %d ,", ptr[i].exDate);
			printf("Now available %dea \n", ptr[i].stock_count);
			printf("Only For adult : %d\n", ptr[i].for_adult);
			printf("\n");
		}
	}
}

// user can choose product in this func
void chooseproduct(int stuffs)
{
	// Empty buffer
	removeemptyspace();

	int i = 0;
	int j;
	int menu = 1;

	for (i = 0; i < stuffs; ++i) {
		j = 0;

		printf("Please enter product ID you want: ");
		scanf("%d", &ptr_cart[i].pID);
		
		/*
		// Get entered name of the product
		printf("Please enter product name you want: ");
		fgets(ptr_cart[i].pName, 30, stdin);
		
		// Remove null character
		ptr_cart[i].pName[strlen(ptr_cart[i].pName) - 1] = '\0';
		*/

		while (j < 50) {
			//find that item
			//if (!strcmp(ptr_stock[j].pName, ptr_cart[i].pName))
			if(ptr_cart[i].pID == ptr_stock[j].pID)
			{	
				strcpy(ptr_cart[i].pName, ptr_stock[j].pName);
				// Get entered numbers of user needed.
				printf("How many %s do you want?: ", ptr_cart[i].pName);
				scanf("%d", &ptr_cart[i].stock_count);
				// Empty buffer
				getchar();				
				
				// get info of the item
				strcpy(ptr_cart[i].pMaker, ptr_stock[j].pMaker);
				ptr_cart[i].exDate = ptr_stock[j].exDate;
				ptr_cart[i].for_adult = ptr_stock[j].for_adult;
				ptr_cart[i].product_price = ptr_stock[j].product_price;

				break;
			}
			else ++j;
		}
	}
}

// Print element of shopping cart & total

int printshopcart(struct Product *ptr)
{
	int total = 0;

	for(int i = 0; i < 20; ++i)
	{
		if(ptr[i].pID == 0)
		{
			break;
		}
		else
		{
			printf("\n%s : ", ptr[i].pName);
			printf("%dea, %d won\n", ptr[i].stock_count, ptr[i].product_price * ptr[i].stock_count);
			total += ptr[i].product_price * ptr[i].stock_count;
		}
	}
	return total;
}

//Get card number and add money to balance
void payByCard(int total)
{
	removeemptyspace();

	char cardNumber[20] = { 0, };
	

	printf("You choosed pay by card.\n");
	printf("Please enter the card number.\n");

	fgets(cardNumber, sizeof(cardNumber), stdin);

	balance += total;
	printf("You paid %d won.\n", total);

	//return balance;
}	

// Return change and add money to balance
void payByCash(int total)
{
	int change = 0;

	int bill50 = 0; // 50,000
	int bill10 = 0; // 10,000
	int bill1 = 0; // 1,000
	
	while(1){
		printf("How many 50,000 papers do you have?: ");
		scanf("%d", &bill50);
		printf("How many 10,000 papers do you have?: ");
		scanf("%d", &bill10);
		printf("How many 1,000 papers do you have?: ");
		scanf("%d", &bill1);

		change = (50000 * bill50) + (10000 * bill10) + (1000 * bill1) - total;
	
		if(change > 0){
			printf("Here's the change: %d\n", change);
			break;
		}
		else if(change == 0)
		{
			printf("You paid exactly.\n");
			break;
		}else
		{
			printf("You have to pay more.\n");
		}
	}
}


int calculate()
{
	removeemptyspace();

	int total = 0;
	int i = 0;
	int stuffs = 0;

	printf("How many stuffs do you want to buy?: ");
	scanf("%d", &stuffs);

	// shopping
	printallproduct(ptr_stock);
	chooseproduct(stuffs);
	printf("\n Using print function\n");
	printallproduct(ptr_cart);



	// Check is adult & expiry date
	while (i < stuffs && ptr_cart[i].pID != 0) {
	
		// Check expiry date
		if (checkfresh(ptr_cart[i].exDate) == 0)
		{
			for (int j = 0; j < 20; ++j)
			{
				if (ptr_cart[j].pID != 0) {
					ptr_cart[j] = ptr_cart[j + 1];
				}
				else {
					break;
				}
			}
		}
		if ((ptr_cart[i].for_adult) != 0)
		{
			if (checkadult() == 0)
			{
				for (int j = 0; j < 20; ++j)
				{
					if (ptr_cart[j].pID != 0) {
						ptr_cart[j] = ptr_cart[j + 1];
					}
					else break;
				}
			}
		}
		++i;
	}

	// Calculate total price
	total = printshopcart(ptr_cart);
	//calcMenu(total);
	return total;
}

// check user is qualified
int checkadult()
{
	int bYear;

	printf("Please enter your birth year(yyyymmdd)");
	scanf("%d", &bYear);


	//printf("Please enter your birth date(mm)
	bYear = bYear / 100;
	
	if(bYear - 20250200 < 18){
		return 1;
	}else return 0;
}

// check Today is before than expiry date
int checkfresh(int ex)
{
	printf("Check fresh! \n");

	time_t now = time(NULL);
	struct tm tm = *localtime(&now);
	
	int comNow = (((tm.tm_year + 1900) * 10000) + ((tm.tm_mon + 1) * 100) + tm.tm_mday);
	
	if(ex < comNow)
	{
		printf("Can't buy this ; Expiry date has passed.\n");
		return 0;
	}
	else {
		return 1;
	}
}
