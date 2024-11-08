//CAFE MANAGEMENT SYSTEM based on first three units
#include <stdio.h>
int main()
{
  printf("HELLO, WELCOME TO NESCAFE!!\n");
  printf("Would you like to order something?\n");
  int a;
  printf("Enter 1 for yes and 0 for no:\n");
  scanf("%d", &a);
  if (a==1){
    int order;
    printf("Here is our menu\n");
    printf("1. Coffee($1)\n");
    printf("2. Tea($2)\n");
    printf("3. Cold Coffee($3)\n");
    printf("4. Cold Tea($4)\n");
    printf("5. Hot Coffee($5)\n");
    printf("6. Hot Tea($6)\n");
    printf("7. Cold Drinks($7)\n");
    printf("8. Hot Drinks($8)\n");
    printf("9. Sandwiches($9)\n");
    printf("10. Burgers($10)\n");
    printf("Enter the number(1-10) for the item you want to order\n");
    scanf("%d", &order);
    switch (order){
      case 1:printf("Coffee added to the order\n");
        int quantity1;
        printf("Enter the quantity: ");
        scanf("%d", &quantity1);
        printf("Added %d Coffee(s) to the order\n", quantity1);
        printf("The total cost is $%d\n", quantity1*1);  
      break;
      case 2:printf("Tea added to the order\n");
        int quantity2;
        printf("Enter the quantity: ");
        scanf("%d", &quantity2);
        printf("Added %d Tea(s) to the order\n", quantity2);
        printf("The total cost is $%d\n", quantity2*2); 
      break;
      case 3:printf("Cold Coffee added to the order\n");
        int quantity3;
        printf("Enter the quantity: ");
        scanf("%d", &quantity3);
        printf("Added %d Cold Coffee(s) to the order\n", quantity3);
        printf("The total cost is $%d\n", quantity3*3); 
      break;
      case 4:printf("Cold Tea added to the order\n");
        int quantity4;
        printf("Enter the quantity: ");
        scanf("%d", &quantity4);
        printf("Added %d Cold Tea(s) to the order\n", quantity4);
        printf("The total cost is $%d\n", quantity4*4); 
      break;
      case 5:printf("Hot Coffee added to the order\n");
        int quantity5;
        printf("Enter the quantity: ");
        scanf("%d", &quantity5);
        printf("Added %d Hot Coffee(s) to the order\n", quantity5);
        printf("The total cost is $%d\n", quantity5*5); 
      break;
      case 6:printf("Hot Tea added to the order\n");
        int quantity6;
        printf("Enter the quantity: ");
        scanf("%d", &quantity6);
        printf("Added %d Hot Tea(s) to the order\n", quantity6);
        printf("The total cost is $%d\n", quantity6*6); 
      break;
      case 7:printf("Cold Drinks added to the order\n");
        int quantity7;
        printf("Enter the quantity: ");
        scanf("%d", &quantity7);
        printf("Added %d Cold Drink(s) to the order\n", quantity7);
        printf("The total cost is $%d\n", quantity7*7); 
      break;
      case 8:printf("Hot Drinks added to the order\n");
        int quantity8;
        printf("Enter the quantity: ");
        scanf("%d", &quantity8);
        printf("Added %d Hot Drink(s) to the order\n", quantity8);
        printf("The total cost is $%d\n", quantity8*8); 
      break;
      case 9:printf("Sandwiches added to the order\n");
        int quantity9;
        printf("Enter the quantity: ");
        scanf("%d", &quantity9);
        printf("Added %d Sandwich(es) to the order\n", quantity9);
        printf("The total cost is $%d\n", quantity9*9); 
      break;
      case 10:printf("Burgers added to the order\n");
        int quantity10;
        printf("Enter the quantity: ");
        scanf("%d", &quantity10);
        printf("Added %d Burger(s) to the order\n", quantity10);
        printf("The total cost is $%d\n", quantity10*10);
      break;
      default:printf("Order number out of range\n");
    }
  }
  else if (a==0){
    printf("Thank you for visiting Nescafe, have a nice day!!");
  }
  else{
    printf("That is not a valid option");
  }
  printf("Please pay online via UPI we do not accept cash\n");
  printf("Thank you for visiting Nescafe, have a nice day!!");
  return 0;
}