
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>

#include "../Card/card.h"
#include "terminal.h"

    
 
    
   ST_terminalData_t ttest;

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    EN_terminalError_t state =T_OK;

    uint8_t transaction_date[11] ;
    
    printf(" Please enter transaction date: DD/MM/YYYY  \n");
    gets(transaction_date);
    if( (transaction_date==NULL) || (strlen(transaction_date) < 10) || (strlen(transaction_date) > 10) ||(transaction_date[2] != '/' || transaction_date[5] != '/')||((transaction_date[0])>'3')||((transaction_date[0]=='3')&&(transaction_date[1])>'1')||( ((transaction_date[3])>'1')||(transaction_date[4])>'2')||(transaction_date[6]!='2')||(transaction_date[7]!='0'))
    {
        state = WRONG_DATE;
    }
    else
    {
        strcpy(termData->transactionDate, transaction_date);
    }

    return state;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    EN_terminalError_t state =EXPIRED_CARD;

            if(termData->transactionDate[9]<cardData->cardExpirationDate[4])
            {
                state =T_OK;
            }
            else 
            {
                if (termData->transactionDate[9]==cardData->cardExpirationDate[4])
                {
			          if ((termData->transactionDate[3]) < (cardData->cardExpirationDate[0] ))
                      {
                      state =T_OK;
                      }
                      else 
                      {
                        if(termData->transactionDate[3]==cardData->cardExpirationDate[0])
                        {
                             if(( termData->transactionDate[4]) <= ( cardData->cardExpirationDate[1]))
                             {
                                state =T_OK;
                             }
                             else
                             {
                                state =  EXPIRED_CARD;
                             }
                        }

                      }
                }
			
            }
    return state;
}



EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{

EN_terminalError_t state = T_OK;

    float Amount = 0;
     printf("Please enter the transaction amount: ");
    scanf("%f", &Amount);

    if( (0 >= Amount) )
    {
        state = INVALID_AMOUNT;
    }
    else
    {
       
        termData->transAmount = Amount;
        
    }
    return state;
   
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t state =T_OK;

    if( (termData->transAmount > termData->maxTransAmount) )
    {
        state = EXCEED_MAX_AMOUNT;
    }
    

    return state;
} 

 EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
   EN_terminalError_t state = T_OK;
    
    if( (0 >= maxAmount) )
    {
        state = INVALID_MAX_AMOUNT;
    }
    else
    {
        termData->maxTransAmount = maxAmount;
    }

    return state;
}
 void getTransactionDateTest(void){
    printf("Tester Name:fady raouf ");
    printf("Function Name: getTransactionDate");


    printf("Test Case 1:  try null ");
    printf("expexted:  invalid Transaction  date ");
    if(getTransactionDate(&ttest)!=T_OK) printf(" invalid Transaction  date  ");

    printf("Test Case 2:  try less than 9 ");
    printf("expexted:  invalid Transaction  date  ");
   if(getTransactionDate(&ttest)!=T_OK) printf(" invalid Transaction  date ");

    printf("Test Case 3:  try more than 10 ");
      printf("expexted:  invalid Transaction  date  ");
   if(getTransactionDate(&ttest)!=T_OK) printf(" invalid Transaction  date ");

       printf("Test Case 4: try day more than 31 ");
      printf("expexted:  invalid Transaction  date  ");
   if(getTransactionDate(&ttest)!=T_OK) printf(" invalid Transaction  date ");


    printf("Test Case 5:  try month more than 12");
    printf("expexted:  invalid Transaction  date  ");
   if(getTransactionDate(&ttest)!=T_OK) printf(" invalid Transaction  date ");

    printf("Test Case 6:  try year doesn't start with 20");
    printf("expexted:  invalid Transaction  date  ");
   if(getTransactionDate(&ttest)!=T_OK) printf(" invalid Transaction  date ");

    printf("Test Case 7:  correct form");
    printf("expexted:  correct expiry date  ");
   if(getTransactionDate(&ttest)==T_OK) printf(" correct expiry date ");

}


 void isCardExpriedTest(void){
    printf("Tester Name:fady raouf ");
    printf("Function Name: isCardExpried");


    printf("Test Case 1:  try transaction date greater than expired date  ");
    printf("expexted:  expired card ");
    if(isCardExpired(&ctest,&ttest)!=T_OK) printf(" expired card  ");

    printf("Test Case 2:  try transaction date smaller than expired date  ");
    printf("expexted: valid card  ");
   if(isCardExpired(&ctest,&ttest)==T_OK) printf(" valid card  ");

    
}

void getTransactionAmountTest(void)
{

  printf("Tester Name:fady raouf ");
    printf("Function Name: getTransactionAmount");


    printf("Test Case 1:  amount greater than 1  ");
    printf("expexted:  valid amount ");
    if(isCardExpired(&ctest,&ttest)==T_OK) printf(" valid amount ");

    printf("Test Case 2:  try amount greater than zero  ");
    printf("expexted: invalid amount  ");
   if(isCardExpired(&ctest,&ttest)==T_OK) printf(" invalid amount  ");

       printf("Test Case 3:  try amount equal to  zero  ");
    printf("expexted: invalid amount  ");
   if(isCardExpired(&ctest,&ttest)==T_OK) printf(" invalid amount  ");


}

