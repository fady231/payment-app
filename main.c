#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "Application/application.h"


int main()
{
    
    static uint8_t choice = 0;

    while(1)
    {   system("cls");
        printf("---->Welcome Sir <----- \n");
        printf("----------------------- \n");
        printf("----------------------- \n\n\n");

        printf("Choose  Service \n");

        printf("----------------------- \n");
       

        printf(" 1- To Make Transaction\n");
        printf(" 2- To Exit\n");
      
        scanf("%d" ,&choice);
        fflush(stdin);
        switch(choice)
        {
            case 1: 
            system("cls");      
            appStart(); 
            break;

            case 2: 
            system("cls");
            return 0;   
            default: 
            system("cls");
            printf(" Invalid Choice\n");
                break;
                
                
        }
    }

    printf(" Thanks \n");
   
    return 0;
}