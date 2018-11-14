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
                break;
            }
    }
    return number;
}

int main(int argc, char *argv[])
{
    int num1= strtoint(argv[1]);
    int num2= strtoint(argv[2]);
    if (num1 == -1 || num2 == -1){
        printf("\nParametre Hatasi\n");
    }
    else{
        printf(" %d * %d = %d \n",num1, num2, num1*num2);   
    }
    
    
    return 0;
}