#ifndef STOCK_H
#define STOCK_H

struct Product{
	int pID; // Product ID
	char pName[30]; // Product's Name
	char pMaker[30]; // Where the product is maked
	char exDate[9]; // Expiry Date
	bool for_adult; // Is Idcard needed to buy this
	int product_price; // Price
	int stock_count; // Stock
};

extern struct Product stock[50];
extern struct Product *ptr_stock;

void printallproduct(struct Product*); // Print all product
void chooseproduct(struct Product*); // Can choose product in this
int printShopCart(struct Product*); // Print element of shopping cart & total
int checkadult(); // Check user is qualified
int checkfresh(char[9]); // Check Today is before than Expiry Date
int payByCard(int); // Get card number and add money to balnce
int payByCash(int); // Return change and add money to balance
#endif
