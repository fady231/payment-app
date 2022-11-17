
#ifndef __CARD__
#define __CARD__


typedef struct ST_cardData_t
{
uint8_t cardHolderName[25];
uint8_t primaryAccountNumber[20];
uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
C_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;



EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);



void getCardHolderNameTest(void);
void getCardExpiryDateTest (void);
void getCardPANTest (void);

{
    "[c]": {
        "editor.defaultFormatter": "keyhr.42-c-format"
    },
}

#endif 
