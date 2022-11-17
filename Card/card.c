
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "card.h"


ST_cardData_t ctest;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{

    EN_cardError_t state = C_OK;
    uint8_t falg =0;
    uint8_t NAME[25];
    
    printf("Please enter the name of the card holder : \n");
    gets(NAME);

    for(uint8_t i=0;i<24;i++)
    {      
         if ((NAME[i] >= 'a' && NAME[i] <= 'z') || (NAME[i]>= 'A' && NAME[i] <= 'Z'))
         {
              falg=1;
         }   
    }

     if( (falg ==0||NAME == NULL)||(strlen(NAME) < 20) || (strlen(NAME) > 24))
       {
        state = WRONG_NAME;
        }
        else strcpy(cardData->cardHolderName, NAME);
 
    
    return state;
}


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    EN_cardError_t state = C_OK;

    uint8_t card_expiration_date[6];
    
    printf(" Please enter the card expiration date as MM/YY: \n");
    gets(card_expiration_date);

  
   
    if((card_expiration_date == NULL)||(strlen(card_expiration_date) < 5) || (strlen(card_expiration_date) > 5) ||(card_expiration_date[2] !='/' )||((card_expiration_date[0])>'1')||((card_expiration_date[1])>'2'))
    {
        state = WRONG_EXP_DATE;
    }
    else 
    {
        strcpy(cardData->cardExpirationDate, card_expiration_date);
    }
    
    return state;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    EN_cardError_t state = C_OK;

    uint8_t PAN[20];
      
    printf("Please enter the primary account number of the card: \n");
    gets(PAN);
    
    

    if( (PAN == NULL) || (strlen(PAN) < 16) || (strlen(PAN) > 20) )
    {
        state = WRONG_PAN;
    }
    else 
    {
        strcpy(cardData->primaryAccountNumber, PAN);
    }
    
    return state;
}



void getCardHolderNameTest(void){
    printf("Tester Name:fady raouf \n");
    printf("Function Name: getCardHolderName\n");

    printf("Test Case 1:  try numbers \n");
    printf("expexted:  invalid name \n");
    if(getCardHolderName(&ctest)!=C_OK) printf(" invalid name \n");

    printf("Test Case 2:  try less than 20 \n");
    printf("expexted:  invalid name \n");
    if(getCardHolderName(&ctest)!=C_OK) printf(" invalid name \n");

    printf("Test Case 3:  try more than 24 \n");
    printf("expexted:  invalid name \n");
    if(getCardHolderName(&ctest)!=C_OK) printf(" invalid name \n");

    printf("Test Case 4:  try null \n");
    printf("expexted:  invalid name \n");
    if(getCardHolderName(&ctest)!=C_OK) printf(" invalid name \n");

    printf("Test Case 5:  try correct name \n");
    printf("expexted: it's ok  \n");
    if(getCardHolderName(&ctest)!=C_OK) printf(" it's ok \n");

}

void getCardExpiryDateTest (void){


    printf("Tester Name:fady raouf \n");
    printf("Function Name: getCardExpiryDateTest\n");

    printf("Test Case 1:  try null \n");
    printf("expexted:  invalid expiry date \n");
    if(getCardHolderName(&ctest)!=C_OK) printf(" invalid expiry date \n");

    printf("Test Case 2:  try less than 5 \n");
    printf("expexted:  invalid expiry date  \n");
   if(getCardHolderName(&ctest)!=C_OK) printf(" invalid expiry date \n");

    printf("Test Case 3:  try more than 5 \n");
      printf("expexted:  invalid expiry date  \n");
   if(getCardHolderName(&ctest)!=C_OK) printf(" invalid expiry date \n");


    printf("Test Case 4:  try month more than 12\n");
    printf("expexted:  invalid expiry date  \n");
   if(getCardHolderName(&ctest)!=C_OK) printf(" invalid expiry date \n");

    printf("Test Case 7:  correct form\n");
    printf("expexted:  correct expiry date  \n");
   if(getCardHolderName(&ctest)==C_OK) printf(" correct expiry date \n");

}


void getCardPANTest (void)
{

printf("Tester Name:fady raouf \n");
    printf("Function Name: getCardPAN\n");

    printf("Test Case 1:  try null \n");
    printf("expexted:  invalid pan \n");
    if(getCardPAN(&ctest)!=C_OK) printf(" invalid pan \n");

    printf("Test Case 2:  try less than 16 \n");
    printf("expexted:  invalid pan\n");
    if(getCardPAN(&ctest)!=C_OK) printf(" invalid name \n");

    printf("Test Case 3:  try more than 19 \n");
    printf("expexted:  invalid pan \n");
    if(getCardPAN(&ctest)!=C_OK) printf(" invalid name \n");

  



}