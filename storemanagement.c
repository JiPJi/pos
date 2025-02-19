#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stock.h"

/*
struct Product{
	int pID;
	char pName[30]; // product's name
	char pMaker[30]; // where the product is maked
	char exDate[9]; // Expirement date
	bool for_adult; // Is IdCard needed when buy this  
	int product_price; // price
	int stock_count; // stock count
};
*/

int balance = 1234000;
struct Product stock[50] = { 0, '\0', '\0', '\0', false, 0, 0};
struct Product *ptr_stock = stock;

void workerMenu();
int registerProduct(struct Product*, int); 
void receiving(struct Product*, int); // adding product 
void searchMenu(struct Product*); // search product  
void searchByName(struct Product*);
void searchByID(struct Product*);
void countStock(struct Product*); // print how many product do they have

void workerMenu()
{

	int menu = 1; //Option Menu
	int i = 0;

	while(menu != 0){
		// Print Option
		printf("\nOption \n\n");
		printf("1. Register product \n");
		printf("2. Receiving \n");
		printf("3. Search\n");
		printf("4. Show all product\n\n");

		printf("Go to: ");
		scanf("%d", &menu);

		switch(menu)
		{	
			// Register product
			case 1:
				i = registerProduct(ptr_stock, i);
				break;
			
			// Product Receiving
			case 2:
				receiving(ptr_stock, balance);
				break;
			
			// Search
			case 3:
				searchMenu(ptr_stock);
				break;
		
			// Show all product 
			case 4:
				countStock(ptr_stock);
				break;
		}
		printf("\n Press 1 to go back to worker menu \n");
		printf("(0 to quit from worker menu): ");
		scanf("%d", &menu);
	}
}


int registerProduct(struct Product *ptr, int i) 
{
	int is_continue = 1;
	printf("%d\n", i);

	if(ptr->pID == 0)
	{
		printf("First Addition\n\n");
	}

	while(is_continue != 0)
	{	
		// Remove blank characters
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		
		
		ptr[i].pID = i + 1;

		printf("Name: "); fgets(ptr[i].pName, 
			30, stdin);
		ptr[i].pName[strlen(ptr[i].pName)-1] = '\0';


		printf("Maker: "); fgets(ptr[i].pMaker, 
			30, stdin);
		ptr[i].pMaker[strlen(ptr[i].pMaker)-1] = '\0';
		

		printf("Expirement Date: "); fgets(ptr[i].exDate, 
			9, stdin);
		ptr[i].exDate[strlen(ptr[i].exDate)-1] = '\0';

		printf("Is this product only for over 18 years old?\n");
		printf("Press 1 to Yes, Press 0 to No: ");
		scanf("%d", &ptr[i].for_adult);
	
		printf("Price: ");
		scanf("%d", &ptr[i].product_price);
		
		ptr[i].stock_count += 10;
		balance -= ((ptr[i].product_price * 0.3) * 10);

		printf("Press '0' to quit(1 to continue): ");
		scanf("%d", &is_continue);
	
		++i;	
	}
	//수정할 물품 번호 받아서 번호로 찾아가서 수정?? 
	return i;
}

void receiving(struct Product *ptr, int balance)
{
	char target[30] = {"/0", }; // target item's id

	int addition = 0; // add it to stock_count
	int is_continue = 1; //continue to 1 stop to 0


	while(is_continue != 0){
		//get target item's id
		printf("Which product do you want to add?");
		fgets(target, strlen(target), stdin);
	
		// add stock & pay
		for(int i = 0; i < 50; ++i)
		{
			if(!strcmp(ptr->pName, target))
			{
				printf("Current stock: ");
				scanf("%d", &addition);
				ptr->stock_count += addition;

				//pay
				balance = balance - ((ptr->product_price * 0.3) * addition);
				printf("Current balance: %d", balance);	
				break;
			}
		}
		
		printf("Press '0' to quit(1 to continue)\n");
		scanf("%d", &is_continue);
	}

}

void searchMenu(struct Product* ptr) {
	int smenu = 0; // search menu

	printf("1. Search by name \n");
	printf("2. Search by product ID. \n\n");
	
	printf("Press number(0 to quit): ");
	scanf("%d", &smenu);
	
	while (smenu != 0) {
		switch (smenu)
		{
			case 1:
				searchByName(ptr);
				break;
			case 2:
				searchByID(ptr);
				break;
			default:
				break;
		}
	}

}

// Search product by name
void searchByName(struct Product* ptr) {
	char sName[30] = {"/0"};

	printf("Product name : ");
	fgets(sName, strlen(sName), stdin);

	for (int i = 0; i < 50; ++i) {
		if (!strcmp(sName, ptr[i].pName)) {
			printf("%s", ptr[i].pName);
			printf("This product made from %s", ptr[i].pMaker);
			printf("price: %d \n", ptr[i].product_price);
			printf("Expiry Date: %s", ptr[i].exDate);
			printf("Now available %d ea", ptr[i].stock_count);
			break;
		}
	}
}

// Search product by product ID
void searchByID(struct Product* ptr) {
	int sID = 0;

	printf("Product ID : ");
	scanf("%d", &sID);

	for (int i = 0; i < 50; ++i) {
		if (sID == ptr[i].pID) {
			printf("%s", ptr[i].pName);
			printf("This product made from %s", ptr[i].pMaker);
			printf("price: %d \n", ptr[i].product_price);
			printf("Expiry Date: %s", ptr[i].exDate);
			printf("Now available %d ea", ptr[i].stock_count);
			break;
		}
	}
}

// Print stock
void countStock(struct Product *ptr)
{
	for (int i = 0; i < 50; ++i) {
		if(ptr[i].pName[0] != '\0'){
			printf("%s : ", ptr[i].pName);
			for (int j = 0; j < ptr[i].stock_count; ++j) {
				printf("*");
			}
			printf(" (%dea)\n", ptr[i].stock_count);
		}
	}
}

