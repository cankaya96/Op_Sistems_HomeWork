

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int strtoint(char* charnums)
{
 int number=0;
 int index=0;
 while(charnums[index])
 {
    if(('0'<=charnums[index]) && (charnums[index]<='9'))
    {
    if(!number)
        number= ( (int) charnums[index]) - 48;
    else
    {   
        number = (number * 10) + ((int) charnums[index] - 48);
    }
    index++;
         }
         else
         {
            number=-1;
            printf("\nGecersiz islem");
            break;
         }
 }
 return number;
}

int main(int argc, char *argv[])
{
    char * numbers[10] = {"sifir","bir","iki","uc","dort","bes","alti","yedi","sekiz","dokuz"};
    int number = strtoint(argv[1]);
    printf("%d >> %s\n", number, numbers[number]);
    
    // Re-run myshell 
    char *cmdargs[] = {"./a.out",
				NULL
				};
				execv(cmdargs[0], cmdargs);
    return 0;
}