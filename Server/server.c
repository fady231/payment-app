
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"
#include "../Application/application.h"

extern ST_cardData_t Card;
extern ST_terminalData_t Terminal; 
    
    
ST_transaction_t stest;
static uint32_t Sequence = 0;
static uint16_t Index = 0;

static ST_accountsDB_t AccountsDataBase[255] = 
{
    {9000,BLOCKED ,"8989374655536251"},
    {1900, RUNNING,"8989374615535862"},
    {9000,BLOCKED ,"8989315255626851"},
    {8000, RUNNING ,"8989374515462851"},
    {7000, BLOCKED ,"8989374615456621"},
    {4000, RUNNING ,"8985354625446851"},
    {5000,BLOCKED , "5959624615436851"},
    {3000, RUNNING ,"8985354625436851"},
    {2000, BLOCKED, "8989344655536251"},
    {15000, RUNNING ,"8989375652626851"},
    {6000,BLOCKED  ,"8989375655626851"},

};

static ST_transaction_t DataBase[255] = 
{
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
  
};






EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
   EN_serverError_t state = APPROVED;
   
   if(  isValidAccount(&transData->cardHolderData)==ACCOUNT_NOT_FOUND  )
    {
        state = FRAUD_CARD;
        transData->transState = FRAUD_CARD;
        printf("FRAUD  CARD !!! \n");

    }
    else 
   {
        if(  isBlockedAccount(Index)==BLOCKED_ACCOUNT )
       {
        state = DECLINED_STOLEN_CARD;
        printf("STOLEN CARD CALLING 122...  \n");
        
        }
        else 
        {
            if(  isAmountAvailable(&(transData->terminalData))==LOW_BALANCE )
             {
        state = DECLINED_INSUFFECIENT_FUND;
        transData->transState = DECLINED_INSUFFECIENT_FUND;
         printf("We're sorry, there's not enough balance  \n");
            }

            else 
    {
            AccountsDataBase[Index].balance -= transData->terminalData.transAmount;
            transData->transState = APPROVED;
        }
    
            if(  saveTransaction(transData) ==SAVING_FAILED ) 
        {
            state = INTERNAL_SERVER_ERROR;
            printf("We are sorry the machine is not in service   \n");
        }

        }



   }

    return state;
}



EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    EN_serverError_t state = ACCOUNT_NOT_FOUND;

    
   uint8_t i = 0;
    for(i = 0; i < 255; i++)
    {
        if(  strcmp(cardData->primaryAccountNumber, AccountsDataBase[i].primaryAccountNumber)==0 )
        {
           state = SERVER_OK;
            Index = i;
            break;
        }
      
    }
    return state;


}

EN_serverError_t isBlockedAccount(uint8_t index)
{
    EN_serverError_t state =SERVER_OK ;
    if(AccountsDataBase[index].state==BLOCKED)
    {
        state =BLOCKED_ACCOUNT;
         
    }
    
    return state;

}


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
   EN_serverError_t state = SERVER_OK;

    if( (termData->transAmount > AccountsDataBase[Index].balance) )
    {
        state = LOW_BALANCE;
    }
    

    return state;
}




EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    EN_serverError_t state = SERVER_OK;

    

    if(Sequence > 255 )
    {
        state = SAVING_FAILED;
    }
    else
    {
        
        strcpy(DataBase[Sequence].cardHolderData.primaryAccountNumber,transData->cardHolderData.primaryAccountNumber);
        strcpy(DataBase[Sequence].cardHolderData.cardHolderName,transData->cardHolderData.cardHolderName);
        strcpy(DataBase[Sequence].cardHolderData.cardExpirationDate,transData->cardHolderData.cardExpirationDate);
        strcpy(DataBase[Sequence].terminalData.transactionDate,transData->terminalData.transactionDate);
        DataBase[Sequence].terminalData.transAmount=transData->terminalData.transAmount;
        DataBase[Sequence].terminalData.maxTransAmount=transData->terminalData.maxTransAmount;
        DataBase[Sequence].transState = transData->transState;
        
        transData->Sequence = Sequence;
        
    }

    return state;
}



void listSavedTransactions()
{
    printf("Transaction Sequence : %d\n",Sequence+1);
   printf("Transaction Date: %s\n",DataBase[Sequence].terminalData.transactionDate);
   printf("Terminal Max Amount: %f\n",DataBase[Sequence].terminalData.maxTransAmount);
   printf("Transaction Amount: %f\n",DataBase[Sequence].terminalData.transAmount); 
   printf("Your New Balance : %f\n",AccountsDataBase[Index].balance);
                                                                  
   printf("Transaction State: succssfully transaction \n");
   printf("PAN: %s\n",DataBase[Sequence].cardHolderData.primaryAccountNumber); 
   printf("Card Expiration Date: %s\n",DataBase[Sequence].cardHolderData.cardExpirationDate);
   printf("Card holder name: %s\n",DataBase[Sequence].cardHolderData.cardHolderName);
   Sequence++;
}



void recieveTransactionDataTest(void)
{

    printf("Tester Name:fady raouf ");
    printf("Function Name: recieveTransactionData");


    printf("Test Case 1:  try with blocked card   ");
    printf("expexted:  blocked card& no list print");
    if(recieveTransactionData(&stest)!=SERVER_OK) printf(" blocked card& no list print ");

    printf("Test Case 2:  try with running card but with amount above its balance  ");
    printf("expexted: higher than the balance & no list print ");
   if(recieveTransactionData(&stest)!=SERVER_OK) printf(" higher than the balance  & no list print ");

       printf("Test Case 3:  try with running card but with amount lower its balance  ");
    printf("expexted: done with list ");
   if(recieveTransactionData(&stest)==SERVER_OK) printf(" done with list ");


  

}



