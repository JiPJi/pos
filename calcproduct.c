#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stock.h"
#include <time.h>

// Do compile with storemanagement.c

extern struct Product stock[50];
extern struct Product *ptr_stock;
extern int balance;

void printallproduct(struct Product*); // print all product
void chooseproduct(struct Product*, struct Product*); // user can choose product in this func
int printshopcart(struct Product*); // Print element of shopping cart & total
int checkadult(); // check user is qualified
int checkfresh(char[9]); // check Today is before than Expriry Date
void payByCard(int); // Get card number and add money to balance
void payByCash(int); // Return change and add moeny to balance


// print all product
void printallproduct(struct Product *ptr)
{
	for(int i = 0; i < 50; ++i)
	{
		printf("%s: ", ptr[i].pName);
		printf("This product made from %s\n", ptr[i].pMaker);
		printf("price: %d ", ptr[i].product_price);
		printf("Expiry Date: %s", ptr[i].exDate);
		printf("Now available %dea \n", ptr[i].stock_count);
		printf("\n");
	}
}

// user can choose product in this func
void chooseproduct(struct Product *ptr, struct Product *ptr_cart)
{
	struct Product shoppingCart[20] = {0, '0', '0', '0', false, 0, 0};
	ptr_cart = shoppingCart;

	// Get entered name of the product
	printf("Please enter product name you want");
	fgets(ptr_cart->pName, strlen(ptr_cart->pName), stdin);
	// Remove null character
	ptr_cart->pName[strlen(ptr_cart->pName)-1] = '\0';
	
	//find that item
	for(int i = 0; i < 20; ++i)
	{ // i for ptr_shop and j for ptr
		for(int j = 0; j < 50; ++j){
			// if find the item
			if(!strcmp(ptr->pName, ptr_cart->pName))
			{	// get info of the item
				strncpy(ptr[j].exDate, ptr_cart[i].exDate,8);
				ptr_cart[i].for_adult = ptr[j].for_adult;
				ptr_cart[i].product_price = ptr[j].product_price;
				printf("How many %s do you want?: ", ptr[i].pName);
				scanf("%d", &ptr_cart[i].stock_count);
			}
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
			printf("%s ", ptr[i].pName);
			printf("%dea, %d won\n", ptr[i].stock_count, ptr[i].product_price * ptr[i].stock_count);
			total += ptr[i].product_price * ptr[i].stock_count;
		}
	}
	return total;
}

//Get card number and add money to balance
void payByCard(int total)
{
	char cardNumber[20] = { 0, };
	

	printf("You choosed pay by card.\n");
	printf("Please enter the card number.\n");

	fgets(cardNumber, sizeof(cardNumber), stdin);

	balance += total;

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
		scanf("%d", bill50);
		printf("How many 10,000 papers do you have?: ");
		scanf("%d", bill10);
		printf("How many 1,000 papers do you have?: ");
		scanf("%d", bill1);

		change = (50000 * bill50) + (10000 * bill10) + (1000 * bill1) - total;
	
		if(change > 0){
			printf("Here's the change: %d\n", change);
		}
		else if(change == 0)
		{
			printf("You paid exactly.\n");
		}else
		{
			printf("You have to pay more.\n");
		}
	}
}

// check user is qualified
int checkadult()
{
	int bYear;

	printf("Please enter your birth year(yyyymmdd)");
	scanf("%d", &bYear);
	//printf("Please enter your birth date(mm)
	bYear = bYear / 100;
	
	// 하드코딩 바꾸
	if(bYear - 20250200 > 0){
		return 1;
	}else return 0;
}

// check Today is before than expiry date
int checkfresh(char ex[9])
{
	time_t now = time(NULL);
	struct tm tm = *localtime(&now);

	int eDate = atoi(ex);
	int comNow	= tm.tm_year + 1900 + tm.tm_mon + 1 + tm.tm_mday; 
	
	if(eDate < comNow)
	{
		printf("Can't buy this; Expiry date has passed.\n");
		return 0;
	}else 
		return 1;

}
