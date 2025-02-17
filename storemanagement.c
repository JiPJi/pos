#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pos.c"

struct Product{
	int pID;
	char pName[30]; // product's name
	char pMaker[30]; // where the product is maked
	char exDate[9]; // Expirement date
	bool for_adult; // Is IdCard needed when buy this  
	int product_price; // price
	int stock_count; // stock count
};

extern int balance;

void registerProduct(struct Product*); 
void receiving(struct Product*, int); // adding product 
void searchMenu(struct Product*); // search product  
void searchByName(struct Product*);
void searchByID(struct Product*);
void checkProduct(struct Product*); // print how many product do they have
void checkExDate(); // check Expirement date


int main()
{
	struct Product stock[50] = { 0, '0', '0', '0', false, 0, 0};
	struct Product *ptr_stock = stock;

	int menu = 0; //Option Menu
	

	// Print Option
	printf("Option \n\n");
	printf("1. Register product \n");
	printf("2. Receiving \n");
	printf("3. Search\n");
	printf("4. Show all product\n");
	printf("5. Check Expiry date");

	while(1){
		printf("Move to: ");
		scanf("%d", &menu);

		switch(menu)
		{	
			// Register product
			case 1:
				registerProduct(ptr_stock);
				break;
			
			// Product Receiving
			case 2:
				receiving(ptr_stock, balance);
				break;
			
			// Search
			case 3:
				
				break;
		
			// Show all product 
			case 4:
				checkProduct(ptr_stock);
				break;
			
			// Check expiry date
			case 5:
				
				break;
			
			case 6:

				break;
		}

	return 0;
	}
}


void registerProduct(struct Product *ptr) 
{
	int is_continue = 1;

	if(ptr->pID == 0)
	{
		printf("First Addition");
	}
	
	while(is_continue != 0)
	{
		++ptr->pID;

		printf("Name: "); fgets(ptr->pName, 
				strlen(ptr->pName), stdin);
		ptr->pName[strlen(ptr->pName)-1] = '\0';
		
		printf("Maker: "); fgets(ptr->pMaker, 
				strlen(ptr->pMaker), stdin);
		ptr->pMaker[strlen(ptr->pMaker)-1] = '\0';
		
		printf("Expirement Date: "); fgets(ptr->exDate, 
				strlen(ptr->exDate), stdin);
		ptr->exDate[strlen(ptr->exDate)-1] = '\0';
		
		printf("Is this product only for over 18 years old?\n");
		printf("Press 1 to Yes, Press 0 to No: ");
		scanf("%d", ptr->for_adult);
	
		printf("Price: ");
	   	scanf("%d", ptr->product_price);
		
		printf("Press '0' to quit(1 to continue)\n");
		scanf("%d", &is_continue);
	}

	//수정할 물품 번호 받아서 번호로 찾아가서 수정?? 
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
				balance = balance - ((ptr->product_price - ptr->product_price * 0.7) * addition);
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

void searchByName(struct Product* ptr) {
	char sName[30] = { '/0', };

	printf("Product name : ");
	fgets(sName, strlen(sName), stdin);

	for (int i = 0; i < 50; ++i) {
		if (!strcmp(sName, ptr[i]->pName)) {
			printf("%s", ptr[i]->pName);
			printf("This product made from %s", ptr[i]->pMaker);
			printf("price: %d \n", ptr[i]->product_price);
			printf("Expiry Date: %s", ptr[i]->exDate);
			printf("Now available %d ea", ptr[i]->stock_count);
			break;
		}
	}
}

void searchByID(struct Product* ptr) {
	int sID = 0;

	printf("Product ID : ");
	scanf("%d", &sID);

	for (int i = 0; i < 50; ++i) {
		if (sID == ptr[i]->pID) {
			printf("%s", ptr[i]->pName);
			printf("This product made from %s", ptr[i]->pMaker);
			printf("price: %d \n", ptr[i]->product_price);
			printf("Expiry Date: %s", ptr[i]->exDate);
			printf("Now available %d ea", ptr[i]->stock_count);
			break;
		}
	}
}

void checkProduct(struct Product *ptr)
{
	for (int i = 0; i < 50; ++i) {
		printf("%s : ", ptr->pName);
		for (int j = 0; j < ptr->stock_count; ++j) {
			printf("*");
		}
		printf("\n");
	}
}
/*
void checkEpDate()
{

}
