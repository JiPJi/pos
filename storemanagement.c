#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stock.h"
//#pragma warning(disable:4996)

int balance = 1234000;
struct Product stock[50] = { 0, '\0', '\0', '\0', 0, 0, 0};
struct Product *ptr_stock = stock;

void workerMenu();
int registerProduct(struct Product*, int); 
void receiving(struct Product*, int); // adding product 
void searchMenu(struct Product*); // search product  
void searchByName(struct Product*);
void searchByID(struct Product*);
void countStock(struct Product*); // print how many product do they have
void removeemptyspace();

void workerMenu()
{
	int menu = 1; //Option Menu
	int i = 0;

	while(menu != 0){
		// Print Option
		printf("Option(0 to quit) \n\n");
		printf("1. Register product \n");
		printf("2. Receiving \n");
		printf("3. Search\n");
		printf("4. Show all product\n\n");

		printf("Go to: ");
		scanf("%d", &menu);

		printf("\n");

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
			default:
				break;
		}
		if (menu != 0) {
			printf("\n Press 1 to go back to worker menu \n");
			printf("(0 to quit (or calcualtion): ");
			scanf("%d", &menu);

			printf("\n");
		}
	}
}


int registerProduct(struct Product *ptr, int i) 
{
	int is_continue = 1;

	printf("NOW -> Register product.\n");

	if(ptr->pID == 0)
	{
		printf("\nFirst Addition\n\n");
	}

	while(is_continue != 0)
	{			
		// Empty buffer
		removeemptyspace();

		ptr[i].pID = i + 1;

		printf("Name: "); fgets(ptr[i].pName, 
			30, stdin);
		ptr[i].pName[strlen(ptr[i].pName)-1] = '\0';
		

		printf("Maker: "); fgets(ptr[i].pMaker, 
			30, stdin);
		ptr[i].pMaker[strlen(ptr[i].pMaker)-1] = '\0';
		

		printf("Expiry Date(yyyymmdd): "); 
		scanf("%d", &ptr[i].exDate);


		printf("Is this product only for over 18 years old?\n");
		printf("Press 1 to Yes, Press 0 to No: ");
		scanf("%d", &ptr[i].for_adult);
		// Empty buffer
		getchar();
	
		printf("Price: ");
		scanf("%d", &ptr[i].product_price);

		printf("\n");

		ptr[i].stock_count += 10;
		balance -= ((ptr[i].product_price * 0.1) * 10);

		printf("Press '0' to quit(1 to continue): ");
		scanf("%d", &is_continue);


		++i;	
		printf("\n");
	}
	//수정할 물품 번호 받아서 번호로 찾아가서 수정?? 
	return i;
}

void receiving(struct Product *ptr, int balance)
{
	char target[30] = {"/0", }; // target item's id

	int addition = 0; // add it to stock_count
	int is_continue = 1; //continue to 1 stop to 0

	printf("NOW -> Receiving\n\n");

	while(is_continue != 0){
		// Empty buffer
		removeemptyspace();

		//get target item's id
		printf("Which product do you want to add? ");
		fgets(target, 30, stdin);
		target[strlen(target) - 1] = '\0';

		// add stock & pay
		for(int i = 0; i < 50; ++i)
		{
			if(!strcmp(ptr[i].pName, target))
			{
				printf("We have %d ea\n", ptr[i].stock_count);
				printf("add : ");
				scanf("%d", &addition);

				ptr[i].stock_count += addition;
				printf("Now we have %d ea. \n", ptr[i].stock_count);

				//pay
				balance = balance - ((ptr[i].product_price * 0.3) * addition);
				printf("Current balance: %d\n", balance);	
				break;
			}
		}
		
		printf("\nPress '0' to quit from receiving \n(1 to continue)\n");
		scanf("%d", &is_continue);

	}

}

void searchMenu(struct Product* ptr) {
	// Empty buffer
	removeemptyspace();

	int smenu = 1; // search menu


	while (smenu != 0) {

		printf("NOW -> Searching\n\n");
		printf("1. Search by name \n");
		printf("2. Search by product ID. \n\n");

		printf("Press number(0 to quit): ");
		scanf("%d", &smenu);

		printf("\n");

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
	// Empty buffer
	removeemptyspace();

	char sName[30] = {"/0"};

	printf("NOW -> Search by name\n\n");

	printf("Product name : ");
	fgets(sName, 30, stdin);
	sName[strlen(sName) - 1] = '\0';


	for (int i = 0; i < 50; ++i) {
		if (!strcmp(sName, ptr[i].pName)) {
			printf("%s", ptr[i].pName);
			printf("This product made from %s\n", ptr[i].pMaker);
			printf("price: %d \n", ptr[i].product_price);
			printf("Expiry Date: %d\n", ptr[i].exDate);
			printf("Now available %d ea\n", ptr[i].stock_count);
			break;
		}
		else if (ptr[i].pName == '\0') {
			printf("Can't find!\n");
		}
	}

	printf("\n");
	return;
}

// Search product by product ID
void searchByID(struct Product* ptr) {
	// Empty buffer
	removeemptyspace();

	int sID = 0;

	printf("NOW -> Search by product ID\n\n");

	printf("Product ID : ");
	scanf("%d", &sID);

	printf("\n");

	for (int i = 0; i < 50; ++i) {
		if (sID == ptr[i].pID) {
			printf("%s\n", ptr[i].pName);
			printf("This product made from %s\n", ptr[i].pMaker);
			printf("price: %d \n", ptr[i].product_price);
			printf("Expiry Date(yymmdd): %d\n", ptr[i].exDate);
			printf("Now available %d ea\n", ptr[i].stock_count);
			break;
		}
		else if (ptr[i].pName == '\0') {
			printf("Can't find!\n");
		}
	}

	printf("\n");
	return;
}

// Print stock
void countStock(struct Product *ptr)
{
	printf("NOW -> Show all product. \n\n");

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

void removeemptyspace() {
	// Remove blank characters
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}