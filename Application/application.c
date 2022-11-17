
#include <stdio.h>
#include <stdint.h>

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "application.h"
#define MaxAmount 10000.0

ST_cardData_t Card;
ST_terminalData_t Terminal;
ST_transaction_t Transaction;
void appStart(void)
{

    Transaction.cardHolderData = Card;

    Transaction.terminalData = Terminal;

    static uint8_t choose = 0;
    uint8_t back = 0;

    switch (choose)
    {

    case 0:

        if (getCardHolderName(&Card) != T_OK)
        {
            printf("Invalid Card Name\n");
            appStart();
        }
        else
        {
            choose++;
            appStart();
        }

        break;

    case 1:
        if (getCardExpiryDate(&Card) != T_OK)
        {
            printf("Invalid Card Expiration Date\n");
            appStart();
        }

        else
        {
            choose++;
            appStart();
        }
        break;

    case 2:

        if (getCardPAN(&Card) != T_OK)
        {
            printf("Invalid Card PAN\n");
            appStart();
        }

        else
        {
            choose++;
            appStart();
        }
        break;

    case 3:

        if (getTransactionDate(&Terminal) != T_OK)
        {
            printf("Invalid Transaction Date\n");
            appStart();
        }

        else
        {
            choose++;
            appStart();
        }
        break;

    case 4:

        if (isCardExpired(&Card, &Terminal) != T_OK)
        {
            printf("Card is expired\n");
            choose = 7;
            appStart();
        }

        else
        {
            choose++;
            appStart();
        }
        break;

    case 5:
        if (setMaxAmount(&Terminal, MaxAmount) == T_OK)

        {

            if (getTransactionAmount(&Terminal) == T_OK)
            {

                if (isBelowMaxAmount(&Terminal) == EXCEED_MAX_AMOUNT)
                {
                    printf("Transaction amount exceeded\n");
                    choose = 7;
                    appStart();
                }
                else
                {

                    choose++;
                    appStart();
                }
            }
        }
        else
            appStart();

        break;

    case 6:

        if (recieveTransactionData(&Transaction) == APPROVED)
        {
            printf("Wait for the money and reset \n\n");
            listSavedTransactions();
            choose = 7;
            appStart();
        }

        else
        {

            choose = 7;
            appStart();
        }
        break;

    case 7:
        choose = 0;
        printf("\n\nThank you for using our service  \n");
        printf("\n Press any key to return to the main menu  \n");
        scanf("%d", &back);
        if (back == 1)
            return;
        break;

    default:
        printf("Un Expected Error\n");
          break;
    }
}


{
    "[c]": {
        "editor.defaultFormatter": "keyhr.42-c-format"
    },
}