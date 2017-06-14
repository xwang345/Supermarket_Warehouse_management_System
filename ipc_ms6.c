#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Item {
   double price;
   int sku;
   int isTaxed;
   int quantity;
   int minQuantity;
   char name[21];
};

void searchTest();
void updateTest();
void addTest();
void addOrUpdateTest();
void adjustQtyTest();

/********************************************************************
Milestones 1 to 4  prototypes, definitions and etc...*/
struct Item GI[21] = {
   { 4.4,275,0,10,2,"Royal Gala Apples" },//1
   { 5.99,386,0,20,4,"Honeydew Melon" },//2
   { 3.99,240,0,30,5,"Blueberries" },//3
   { 10.56,916,0,20,3,"Seedless Grapes" },//4
   { 2.5,385,0,5,2,"Pomegranate" },//5
   { 0.44,495,0,100,30,"Banana" },//6
   { 0.5,316,0,123,10,"Kiwifruit" },//7
   { 4.49,355,1,20,5,"Chicken Alfredo" },//8
   { 5.49,846,1,3,5,"Veal Parmigiana" },//9
   { 5.29,359,1,40,5,"Beffsteak Pie" },//10
   { 4.79,127,1,30,3,"Curry Checken" },//11
   { 16.99,238,1,10,2,"Tide Detergent" },//12
   { 3.69,538,1,1,5,"Lays Chips S&V"},//13
   { 10.99,491,1,50,5,"Tide Powder Det." },//14
   { 3.69,538,1,1,5,"Lays Chips S&V" },//15
   { 3.29,649,1,15,5,"Joe Org Chips" },//16
   { 1.79,731,1,100,10,"Allen's Apple Juice" },//17
   { 6.69,984,1,30,3,"Coke 12 Pack" },//18
   { 7.29,350,1,50,5,"Nestea 12 Pack" },//19
   { 6.49,835,1,20,2,"7up 12 pack" }//20
};
int GNoOfRecs = 20;

/**************************************************************/

/*************************************************************
Student Milestone 3 definitions and prototypes go here:
(Do not copy struct Item since it is already implimented above*/
#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0

void welcome(void);
void prnTitle(void);
void prnFooter(double gTotal);
void pause(void);
void clrKyb(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);

double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
struct Item itemEntry(int sku);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);
int yes(void);


const double TAX = 0.13;//Global variable;

/*End of Student Milestone 3 definitions and prototypes
*************************************************************/

/*************************************************************
Milestone 4 defintions and prototypes:*/
// write the define statements here:
//#define MAX_ITEM_NO 	21
#define MAX_QTY 		999
#define SKU_MAX 		999
#define SKU_MIN 		100
// function prototypes in order of implementation:
void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQty(struct Item item[], int NoOfRecs, int stock);


/*End of Milestone 4 defintions and prototypes:
***************************************************************/




/*End of milestone 1 to 4 stuff
*********************************************************************/



/********************************************************************
Milestone 5 prototypes*/

#define DATAFILE "ipc_ms5_long.txt"
#define MAX_ITEM_NO 500   
//#define DATAFILE "items.txt" 

void GrocInvSys(void);
void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(struct Item* item, char fileName[], int NoOfRecs);
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr);

/*End of milestone 5 prototypes
*********************************************************************/
/********************************************************************/
//M 6 prototypes
void deleteItem(struct Item* item, int* NoOfRecs);
void searchByName(struct Item* item, int NoOfItems);

/**************************************************************************
    TTTTTTTTT   EEEEEEEE   SSSSSSSS   TTTTTTTTTT   EEEEEEEEE   RRRRRRRR                                                      
       TT       EE         SS             TT       EE          RR     RR          
       TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RRRRRRRR
       TT       EE               SS       TT       EE          RR  RR
       TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RR    RR
***************************************************************************
Tester for saveItem, loadItem, saveItems and loadItems:
uncomment this to test your functions prior to putting all the code together by adding a * and / here:



void prnFile() {
   FILE* tp = fopen("test.txt", "r");
   char ch;
   if (tp) {
      for (; fscanf(tp,"%c", &ch) == 1; putch(ch));
      fclose(tp);
   }
   else {
      printf("text.txt not found\n");
   }
}


int main(void) {
   int i, n;
   struct Item GI[3] = {
      { 4.4,275,0,10,2,"Royal Gala Apples" },
      { 5.99,386,0,20,4,"Honeydew Melon" },
      { 3.99,240,0,30,5,"Blueberries" },
   };
   struct Item I;
   struct Item IN[3];
   printf("***********Testing saveItem:\n");
   printf("Your saveItem saved the following in test.txt: \n");
   FILE* tp = fopen("test.txt", "w");
   if (tp) {
      for (i = 0; i < 3; i++) saveItem(GI[i], tp);
      fclose(tp);
      prnFile();
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("275,10,2,4.40,0,Royal Gala Apples\n");
   printf("386,20,4,5.99,0,Honeydew Melon\n");
   printf("240,30,5,3.99,0,Blueberries\n");
   printf("***********END Testing saveItem!\n\n\n");
   pause();
   printf("***********Testing loadItem:\n");
   printf("Your loadItem loaded the following from test.txt: \n");
   tp = fopen("test.txt", "r");
   if (tp) {
      for (i = 0; i < 3; i++) {
         loadItem(&I, tp);
         dspItem(I, LINEAR);
      }
      fclose(tp);
      tp = fopen("test.txt", "w");
      fclose(tp);
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
   printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
   printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
   printf("***********END Testing loadItem!\n\n\n");
   pause();
   printf("***********Testing saveItems:\n");
   printf("Your saveItems saved the following in test.txt: \n");
   saveItems(GI, "test.txt", 3);
   prnFile();
   printf("*******************************\nThey have to match the following:\n");
   printf("275,10,2,4.40,0,Royal Gala Apples\n");
   printf("386,20,4,5.99,0,Honeydew Melon\n");
   printf("240,30,5,3.99,0,Blueberries\n");
   printf("***********END Testing saveItems!\n\n\n");
   pause();
   printf("***********Testing loadItems:\n");
   printf("Your loadItems loaded the following from test.txt: \n");
   loadItems(IN, "test.txt", &n);
   for (i = 0; i < n; i++) {
      dspItem(IN[i], LINEAR);
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
   printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
   printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
   printf("***********END Testing loadItems!\n\n\n");
   pause();
   printf("Done!\n");
   return 0;
}

End MS5 functions' tester
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/


/*******************************************************************
Main function to run the application
uncomment this to test your functions after putting all the code together by adding a * and / here:
*/

int main(void) {
	GrocInvSys();
	return 0;
}
/*
End Main function
********************************************************************/





/********************************************************************
Milestone 5 functions*/
void saveItem(struct Item item, FILE* dataFile) {
	fprintf(dataFile, "%d,%d,%d,%.2lf,%d,%s\n", item.sku, item.quantity, item.minQuantity, item.price, item.isTaxed, item.name);
}

int loadItem(struct Item* item, FILE* dataFile) {
	int all_exists_items = 0;
	if (fscanf(dataFile, "%d,%d,%d,%lf,%d,%[^\n]%*c", &(*item).sku, &(*item).quantity, &(*item).minQuantity, &(*item).price, &(*item).isTaxed, (*item).name) == 6){
		all_exists_items = 1;// The function returns true if fscanf reads the six items successfully.
	}
	return all_exists_items;
}

int saveItems(struct Item* item, char fileName[], int NoOfRecs) {
	int i, true_false = 0;
	FILE* tp = fopen(fileName, "w");
	if (tp) {
		true_false = 1;
		for (i = 0; i < NoOfRecs; i++) saveItem(item[i], tp);
		fclose(tp);
	}
	return true_false;
}

int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr) {
	int true_false = 0;
	FILE* tp = fopen(fileName, "r");
	if (tp) {
		*NoOfRecsPtr = 0;
		while (loadItem(&item[*NoOfRecsPtr], tp)) {
			*NoOfRecsPtr = *NoOfRecsPtr + 1;
		}
		true_false = 1;
		fclose(tp);
	}
	return true_false;
}

void ifSaveItems(struct Item* item, char fileName[], int NoOfRecs) {
	if (!(saveItems(item, fileName, NoOfRecs))) printf("could not update data file %s\n", DATAFILE);
}
/*End of milestone 5 functions
*********************************************************************/
//M 6 functions
void deleteItem(struct Item* item, int* NoOfRecs){
	int SKU,a;
	int option_delete;
	//int index;
	int e;
	printf("Please enter the SKU: ");
	
	SKU = getIntLimited(SKU_MIN,SKU_MAX);
	a = locateItem(item, *NoOfRecs, SKU,&SKU);
	if(a==0){
		printf("Item not found!\n");
	}else{
		//==========check array index number===============
		/*for(i=0;i<*NoOfRecs;i++){
			if(item[i].sku==SKU){
				index=i;
			}
		}*/
		//==============================================
		dspItem(item[SKU],FORM);
		printf("This item will be deleted, are you sure? (Y)es/(No): ");
		option_delete = yes();
		if(option_delete==1)/*1 is Y*/{
			for(e=SKU; e< *NoOfRecs; e++){
            	// Copy next element value to current element
            	item[e] = item[e+1];
        	}
        (*NoOfRecs)=*NoOfRecs-1;
			printf("Item deleted!\n");
		}else{
			printf("Delete aborted!\n");
		}
	}
}
//==================Search by name==================================

void searchByName(struct Item* item, int NoOfItems)
{
//	int i=0;
	char search_name[21];
	printf("Please enter partial name: ");
	scanf("%s",search_name);

	if(strcmp(GI.name[21],search_name)==0){
		dspItem(item.name,1);
	}
	//iif(strstr(search_name, item.GI)!= NULL){
	//	dspItem(item.name,1);
	//}
	/*for(i=0; search_name[i]!='\0';i++){
		if(search_name[i]==item.name){
			dspItem(item[i],1);
		}else{
			printf("No matches found!\n");
		}*/
	//	printf("%d\n",i);
//	}
}

/********************************************************************
Milestones 1  to 4 functions*/
void search(const struct Item item[], int NoOfRecs) {
	int SKU,i,a;
	printf("Please enter the SKU: ");
	SKU = getIntLimited(SKU_MIN,SKU_MAX);
	a = locateItem(item,NoOfRecs, SKU,&SKU);
	
	if(a==0){
		printf("Item not found!\n");
	}else{
		for(i=0;i<21;i++){
			if(SKU ==i){
				printf("        SKU: %d\n",item[i].sku);
				printf("       Name: %s\n", item[i].name);
				printf("      Price: %.2lf\n", item[i].price);
				printf("   Quantity: %d\n", item[i].quantity);
				printf("Minimum Qty: %d\n", item[i].minQuantity);

				if (item[i].isTaxed){
					printf("   Is Taxed: Yes\n");
				}
				else{
					printf("   Is Taxed: No\n");
				}
			}
		}
	}
}


void updateItem(struct Item* itemptr) {
	struct Item instance;
	int SKU=0;
	int a;
	
	printf("Enter new data:\n");
	instance = itemEntry(itemptr[SKU].sku);
	printf("Overwrite old data? (Y)es/(N)o: ");
	a = yes();
	
	if(a==0){
		printf("--== Aborted! ==--\n");
	}else{
		*itemptr = instance;
		printf("--== Updated! ==--\n");
	}
	
}

void addItem(struct Item item[], int *NoOfRecs/*20*/, int sku/*222*/) {
	struct Item instance;
	int a;
//	printf("%d\n",*NoOfRecs);
	if(*NoOfRecs==MAX_ITEM_NO){
		printf("Can not add new item; Storage Full!\n");
		return;
	}else{
		instance = itemEntry(sku);
		printf("Add Item? (Y)es/(N)o: ");
		a = yes();
		
	}
		if(a==0){
			printf("--== Aborted! ==--\n");
		}else{
			(*NoOfRecs)=*NoOfRecs+1;
			printf("--== Added! ==--\n");
			item[*NoOfRecs-1].sku=instance.sku;//item[*NoOfRecs - 1].sku=instance.sku
			item[*NoOfRecs-1].price=instance.price;
			item[*NoOfRecs-1].quantity=instance.quantity;
			item[*NoOfRecs-1].minQuantity=instance.minQuantity;
			item[*NoOfRecs-1].isTaxed=instance.isTaxed;
			/*int i;
			for (i = 0; i < strlen(instance.name); i++) {
				item[*NoOfRecs - 1].name[i] = instance.name[i];
			}*/
			strcpy(item[*NoOfRecs-1].name, instance.name);
			//item[*NoOfRecs-1].name=instance.name;
		}
}

void addOrUpdateItem(struct Item item[], int* NoOfRecs) {
	int SKU,i,a,b,index=0;
	printf("Please enter the SKU: ");
	SKU = getIntLimited(SKU_MIN,SKU_MAX);
	a = locateItem(item,*NoOfRecs, SKU,&b);

	if(a==0)/*0 is not found*/{
		addItem(item,NoOfRecs,SKU);
	}else{
 //==========check array index number===============
		for(i=0;i<*NoOfRecs;i++){
			if(item[i].sku==SKU){
				index=i;
			}
		}
//==============================================
		dspItem(item[index],FORM);
		printf("Item already exists, Update? (Y)es/(N)o: ");
		a = yes();

		if(a==0)/*0 is not update the information*/ {
			printf("--== Aborted! ==--\n");
		}else{
//			printf("%d",index);
			updateItem(&item[index]);
			//*NoOfRecs= *NoOfRecs++;
		}

	}
}

void adjustQty(struct Item item[], int NoOfRecs, int stock) {
	int searchSKU, index, add_remove;
	int max;
	char *stock_print;
	int test = stock;
	printf("Please enter the SKU: ");
	searchSKU = getIntLimited(SKU_MIN, SKU_MAX);
	if (locateItem(item, NoOfRecs, searchSKU, &index)) {
		dspItem(item[index], FORM);
		
		if (test == STOCK) {
			stock_print = "to stock";
			max = MAX_QTY - item[index].quantity;
		}
		else {
			stock_print = "to checkout";
			max = item[index].quantity;
		}
		
		printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", stock_print, max);
		add_remove = getIntLimited(0, max);
		
		if (add_remove == 0){
			printf("--== Aborted! ==--\n");
		}else if (test == CHECKOUT){
			item[index].quantity = item[index].quantity + add_remove;
			printf("--== Stocked! ==--\n");
		}else {
			item[index].quantity = item[index].quantity - add_remove;
			printf("--== Checked out! ==--\n");
			
			if (item[index].quantity <= item[index].minQuantity){
				printf("Quantity is low, please reorder ASAP!!!\n");
			} 
		}
	}
	else printf("SKU not found in storage!\n");
}

/*End of Milestone 4 functions
******************************************************************/

/*****************************************************************
Milestone 3 function implementations:
Please copy your milestone 3 functions here: */
double totalAfterTax(struct Item item) {
	double Total_Price = 0;
	Total_Price = item.price * item.quantity;
	if(item.isTaxed)
	{
		Total_Price = Total_Price * (1 + TAX);
	}
	return Total_Price;
}
//==================================================================
int isLowQty(struct Item item) {
	int low_quantity = 0;

	if (item.quantity < item.minQuantity)
	{
		low_quantity = 1;
	 }

	return low_quantity;
}

//==================================================================

struct Item itemEntry(int sku) {
	struct Item SKUEntry;
	SKUEntry.sku = sku;
	printf("        SKU: %d\n", SKUEntry.sku);
	printf("       Name: ");
	scanf("%20[^\n]",SKUEntry.name);
	clrKyb();

	printf("      Price: ");//promto user enter price
	SKUEntry.price = getDbl();//Call getDbl function

	printf("   Quantity: ");//Promto user enter quantity
	SKUEntry.quantity = getInt();//Call getInt function

	printf("Minimum Qty: ");
	SKUEntry.minQuantity = getInt();

	printf("   Is Taxed: ");
	SKUEntry.isTaxed = yes();
	return SKUEntry;

}

//=====================================================================

void dspItem(struct Item item, int linear) {
	int i;
	if (linear)
	{
		printf("|%3d|", item.sku);
		for (i = 0; item.name[i] != '\0'; i++) {
			printf("%c", item.name[i]);
		}

		while (i < 20) {
			printf(" ");
			i++;
		}

		printf("|%8.2lf|  ", item.price);

		if (item.isTaxed){
	 		printf("Yes| ");
	 	}else{
	 		printf(" No| ");
	 		//printf("%3d | %3d |", item.quantity, item.minQuantity);
		}
		printf("%3d | %3d |", item.quantity, item.minQuantity);
		if (item.isTaxed) {
			printf("%12.2lf|", (item.price * item.quantity * (1 + TAX)));
		}else{
			printf("%12.2lf|", (item.price * item.quantity));
		}

		if ((item.minQuantity-item.quantity) > 0 ){
			printf("***");
		}
		printf("\n");
	}else{
		printf("        SKU: %d\n", item.sku);
		printf("       Name: ");

	//	for (i = 0; item.name[i] != '\0'; i++) {
		//for (i = 0; i<21; i++) {
			//printf("%c", item.name[i]);
		//}
		printf("%s", item.name);
		printf("\n      Price: %.2lf\n", item.price);
		printf("   Quantity: %d\n", item.quantity);
		printf("Minimum Qty: %d\n", item.minQuantity);

		if (item.isTaxed){
			printf("   Is Taxed: Yes\n");
		}
		else{
			printf("   Is Taxed: No\n");
		}

		if (item.quantity <= item.minQuantity) {
			printf("WARNING: Quantity low, please order ASAP!!!\n");
		}

	}

}

//===============================================================================

void listItems(const struct Item item[], int NoOfItems) {
	int i;
	double grand_total = 0;
	prnTitle();
	for (i = 0; i < NoOfItems; i++) {
		printf("%-4d", i+1 );
		dspItem(item[i], LINEAR);

		if (item[i].isTaxed)
		{
			grand_total = grand_total + (item[i].price * item[i].quantity * (1 + TAX));
		 }
		else{
			grand_total = grand_total + (item[i].price * item[i].quantity);
		}
	}
	prnFooter(grand_total);
}

//========================================================================================

int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index) {
	int i, true_false = 0;
	for (i = 0; i < NoOfRecs; i++) {
		if (item[i].sku == sku) {
			true_false = 1;
			*index = i;
			break;
		}
	}
	return true_false;
}
//======================================================================================


/*ms1 and 2 functions: */

void welcome(void)
{
	printf("---=== Grocery Inventory System ===---\n\n");
	return;
}

void prnTitle(void)
{
	printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
	printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
	return;
}

void prnFooter(double gTotal)
{
	printf("--------------------------------------------------------+----------------\n");
	if (gTotal > 0) printf("                                           Grand Total: |%12.2lf\n", gTotal);
	return;
}

void clrKyb(void)
{
	while(getchar() != '\n')
	{
		;
	}
}

void pause(void)
{
	printf("Press <ENTER> to continue...");
	clrKyb();

}

int getInt(void)
{
	char NL = 'x';
	int Value;

	while(NL != '\n')
	{
		scanf("%d%c", &Value, &NL);
		if(NL != '\n')
		{
			clrKyb();
			printf("Invalid integer, please try again: ");
		}
	}

	return Value;
}

double getDbl(void)
{
	char NL = 'x';
	double Value;
	
	while(NL != '\n')
	{
		scanf("%lf%c", &Value, &NL);
		if(NL != '\n')
		{
			clrKyb();
			printf("Invalid number, please try again: ");
		}
	}

	return Value;
}

int getIntLimited(int lowerLimit, int upperLimit)
{
	int Value = getInt();

	while(Value<lowerLimit||Value>upperLimit){

			printf("Invalid value, %d <= value <= %d: ", SKU_MIN, SKU_MAX);
			Value = getInt();
		}


	return Value;
}

double getDblLimited(double lowerLimit, double upperLimit)
{
	double Value = getDbl();

	while(Value<lowerLimit||Value>upperLimit){

			printf("Invalid value, %d <= value <= %d: ", SKU_MIN, SKU_MAX);
			Value = getDbl();
		}


	return Value;
}

int yes(void) {
	char CH;
	int RET = 0;

	do{
  		scanf("%c",&CH);
		clrKyb();

  		if(CH !='Y'&&CH !='y'&&CH!='N'&&CH!='n')
  		{
  			printf("Only (Y)es or (N)o are acceptable: ");
		  }

	}while(CH !='Y'&&CH !='y'&&CH !='N'&&CH !='n');

	if(CH =='Y'||CH == 'y'){
 		RET=1;
	}

	return RET;
}

int menu(void) {
	int option;
	printf("1- List all items\n");
	printf("2- Search by SKU\n");
	printf("3- Checkout an item\n");
	printf("4- Stock an item\n");
	printf("5- Add new item or update item\n");
	printf("6- Delete item\n");
	printf("7- Search by name\n");
	printf("8- Sort Items\n");
	printf("0- Exit program\n");
	printf("> ");
	do
	{
		scanf("%d", &option);
		clrKyb();
		if (option < 0 || option > 8) printf("Invalid value, 0 < value < 8: ");
	} while (option < 0 || option > 7);
	return option;
};

void GrocInvSys(void) {
	int menu_choise, DONE = 0, NoOfRecs = 0;
	struct Item GI[MAX_ITEM_NO];
	welcome();
	if (!(loadItems(GI, DATAFILE, &NoOfRecs))) {
		printf("Could not read from %s.\n", DATAFILE);
	}
	else{
		while (DONE == 0) {
			menu_choise = menu();

			switch (menu_choise) {
			case 1:		//	List Items!
				listItems(GI, NoOfRecs);
				pause();
				break;

			case 2:		//	Search Items!
				search(GI, NoOfRecs);
				pause();
			break;

			case 3:		//	Checkout Item!
				adjustQty(GI, NoOfRecs, CHECKOUT);
				//if (!(saveItems(GI, DATAFILE, NoOfRecs))) printf("could not update data file %s\n", DATAFILE);
				ifSaveItems(GI, DATAFILE, NoOfRecs);
				pause();
			break;

			case 4:		//	Stock Item!
				adjustQty(GI, NoOfRecs, STOCK);
				//if (!(saveItems(GI, DATAFILE, NoOfRecs))) printf("could not update data file %s\n", DATAFILE);
				ifSaveItems(GI, DATAFILE, NoOfRecs);
				pause();
			break;

			case 5:		//	Add/Update Item!
				addOrUpdateItem(GI, &NoOfRecs);
				//if (!(saveItems(GI, DATAFILE, NoOfRecs))) printf("could not update data file %s\n", DATAFILE);
				ifSaveItems(GI, DATAFILE, NoOfRecs);
				pause();
			break;
			
			case 6:
				deleteItem(GI, &NoOfRecs);
				
				pause();
			break;
			
			case 7:
				searchByName(GI, NoOfRecs);
						
				pause();
			break;
			
			case 8:
				printf("Not implemented!\n");
				pause();
			break;

			default:
				printf("Exit the program? (Y)es/(N)o): ");
				DONE = yes();
			} 
		}
	}
}

/*End of Milestone 3 functions.
*******************************************************************/

/***************************************************************
Tester Functions DO NOT MODIFY */

void searchTest() {
   printf("================Search Test:\n");
   printf("Enter 731: \n");
   search(GI, GNoOfRecs);
   printf("Enter 222: \n");
   search(GI, GNoOfRecs);
}
void updateTest() {
   struct Item I = { 11.11,111,1,11,1,"Ones!" };
   printf("================Update Test:\n");
   printf("Enter the follwoing: \n");
   printf(
      "         SKU: 111\n"
      "        Name: Grape\n"
      "      Price : 22.22\n"
      "   Quantity : 22\n"
      "Minimum Qty : 2\n"
      "   Is Taxed : y\n"
      "Overwrite old data? (Y)es/(N)o: n\n");
   updateItem(&I);
   printf("Unchanged Item Data:\n");
   dspItem(I, FORM);
   printf("Enter the follwoing: \n");
   printf(
      "         SKU: 111\n"
      "        Name: Grape\n"
      "      Price : 22.22\n"
      "   Quantity : 22\n"
      "Minimum Qty : 2\n"
      "   Is Taxed : y\n"
      "Overwrite old data? (Y)es/(N)o: y\n");
   updateItem(&I);
   printf("Updated Item: \n");
   dspItem(I, FORM);
}
void addTest() {
   printf("================Add Test:\n");
   printf("Total items in Storage: %d, Max no: %d\n", GNoOfRecs, MAX_ITEM_NO);
   printf("Enter the follwoing: \n");
   printf(
      "         SKU: 222\n"
      "        Name: Grape\n"
      "      Price : 22.22\n"
      "   Quantity : 22\n"
      "Minimum Qty : 2\n"
      "   Is Taxed : y\n"
      "Add Item? (Y)es/(N)o: n\n");
   addItem(GI, &GNoOfRecs, 222); //n
   printf("Garbage here! Nothing is added, No of items in storage: %d\n", GNoOfRecs);
   dspItem(GI[GNoOfRecs], FORM);
   printf("Enter the follwoing: \n");
   printf(
      "         SKU: 222\n"
      "        Name: Grape\n"
      "      Price : 22.22\n"
      "   Quantity : 22\n"
      "Minimum Qty : 2\n"
      "   Is Taxed : y\n"
      "Add Item? (Y)es/(N)o: y\n");
   addItem(GI, &GNoOfRecs, 222); //y
   printf("New item is added, No of itemsinstorage: %d\n", GNoOfRecs);
   dspItem(GI[GNoOfRecs - 1], FORM);
   printf("Adding 333: \n");
   addItem(GI, &GNoOfRecs, 333);
}
void addOrUpdateTest() {
   GNoOfRecs = MAX_ITEM_NO;
   printf("================AddOrUpdate Test:\n");
   printf("Enter 731 and then \'n\':\n");
   addOrUpdateItem(GI, &GNoOfRecs); // n
   printf("Enter 731, \'y\' and then:\n"
      "       Name: Apple\n"
      "      Price: 1.80\n"
      "   Quantity: 101\n"
      "Minimum Qty: 11\n"
      "   Is Taxed: n\n"
      "Overwrite old data? (Y)es/(N)o: y\n");
   addOrUpdateItem(GI, &GNoOfRecs); // yes new data Yes
   printf("Updated Item: \n");
   dspItem(GI[16], FORM);
   printf("Enter 444: \n");
   addOrUpdateItem(GI, &GNoOfRecs); //n
}

void adjustQtyTest() {
   printf("================AdjustQty Test:\n");
   printf("Invalid SKU Test; Enter 444:\n");
   adjustQty(GI, GNoOfRecs, STOCK);//STOCK 1
//   printf("------------------------------------------------------------%d\n",STOCK);
   printf("Aborting Entry test; Enter 731 and then 0:\n");
   adjustQty(GI, GNoOfRecs, CHECKOUT);//CHECKOUT 0
//   printf("------------------------------------------------------------%d\n",CHECKOUT);
   printf("Checking out with low quantity warning; Enter 731 and then 90:\n");
   adjustQty(GI, GNoOfRecs, CHECKOUT);
   printf("Stocking; Enter 731 and then 50:\n");
   adjustQty(GI, GNoOfRecs, STOCK);
   dspItem(GI[16], FORM);
}


/*End of milestone 1 to 4 functions
*********************************************************************/








/* ms5 Tester output

***********Testing saveItem:
Your saveItem saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItem!


Press <ENTER> to continue...
***********Testing loadItem:
Your loadItem loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItem!


Press <ENTER> to continue...
***********Testing saveItems:
Your saveItems saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItems!


Press <ENTER> to continue...
***********Testing loadItems:
Your loadItems loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItems!


Press <ENTER> to continue...
Done!


*/
