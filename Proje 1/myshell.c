#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>



int main(int argc, char *argv[])
{
	printf("myshell>>> ");
	while(1)
	{	

		/*
		*
		* user'dan komut girilmesi
		*/
		char *command[50];
		char command_str[200];   
		fgets(command_str,200,stdin);
		command[0] = strtok (command_str," ");
		
		/*
		*
		* girilen komutlarin tokenlarina ayrilmasi
		*/
		int counter=0;
		while (command[counter] != NULL){
			counter++;
			command[counter] = strtok (NULL, " ");
		}

		/*
		*
		* girilen komutta '&' olup olmadiginin kontrol edilmesi
		* varsa ampersandExists = 1
		*/
		int ampersandExists = 0;
		int i;
		for (i = 0; i < counter; i++){
			if(strcmp(command[i],"&") == 0){
				ampersandExists = 1;
				break;
			}
		}

		
		/*
		*
		* myshell döngüsü bu kisimda
		* first_part => girilen komutun ilk ampersand isaretine kadar olan kismini
		* ayirt etmek icin kullanilan bir flag
		* 
		*/
		int first_part = 0; // girilne komut serinin ilk '&'
		for (i = 0; i < counter; i++){
			if (first_part == 0){
				/*
				*
				* Bu kisma bir kez giriliyor sadece ilk part icin 
				* ornek: mul 4 2 & div 4 2
				* mul 4 2 kismi ilk part, burada calisacak 
				* div ise ikinci if icerisinde '&' tan sonraki kisim olarak
				* calisacak
				*/
				command[counter-1][strlen(command[counter-1])-1]=0;
				if(!strcmp(command[0],"exit")){
					exit(0);
				}else if(!strcmp(command[0],"rakam")){ // rakam
					if((ampersandExists == 0 && counter == 2)|| ampersandExists==1){
						char *cmdargs[] = {"./rakam.out",
											command[1],
											NULL
										};
						system("gcc -o ./rakam.out ./rakam.c"); // rakam.c'yi compile ediyoruz
						execv(cmdargs[0], cmdargs);
					}else{
						printf("myshell ERROR: Parametre hatasi\n");
					}	
				}else if(!strcmp(command[0],"div")){  // div
					if((ampersandExists == 0 && counter == 3) || ampersandExists == 1){
						pid_t pid;
						pid = fork();		
						if(pid==0){ 
							//child process bu kismi calistiriyor
							char *cmdargs[] = {"./div.out",
												command[1],
												command[2],
												NULL
											};
							system("gcc -o ./div.out ./div.c"); // div.c'yi compile ediyoruz
							execv(cmdargs[0], cmdargs);
					
						}else{ //parent process bu kismi calistiriyor
							wait(NULL); //parent, cocugun islemini bitirmesini bekliyor
						}
					}
					else{
						printf("myshell ERROR: Parametre hatasi\n");
					}

				}else if(!strcmp(command[0],"mul")){ // mul
					if((ampersandExists == 0 && counter == 3) || ampersandExists == 1){
						pid_t pid;
						pid = fork();		
						if(pid==0){ //child process
							char *cmdargs[] = {"./mul.out",
												command[1],
												command[2],
												NULL
											};
							system("gcc -o ./mul.out ./mul.c"); // mul.c'yi compile ediyoruz
							execv(cmdargs[0], cmdargs);
						}else{
							wait(NULL); //parent, cocugun islemini bitirmesini bekliyor
						}
					}
					else{
						printf("myshell ERROR: Parametre hatasi\n");
					}

				}else if(!strcmp(command[0],"cat")){// cat
					printf("cat: %s\n", command[1]);
				}else if(!strcmp(command[0],"clear")){// clear
					system("clear");
				}else{ // yanlis komut girisinde hata mesaji bas
					printf("myshell ERROR: Yanlis bir komut girdiniz\n");
				}
				first_part = 1;
			}

			if(strcmp(command[i],"&") == 0){
				/* 
				* Komut tokenlarinin listesi boyunca for loopta dolasirken
				* her gordugumuz '&' icin, onun indexinin index+1 veya index+2
				* ekleyerek komutlari sirayla run ederiz
				*/
				command[counter-1][strlen(command[counter-1])-1]=0;
				if(!strcmp(command[i+1],"exit")){
					exit(0);
				}else if(strcmp(command[i+1],"rakam") == 0){ // rakam
					char *cmdargs[] = {"./rakam.out",
										command[i+2],
										NULL
									};
					system("gcc -o ./rakam.out ./rakam.c"); // rakam.c'yi compile ediyoruz
					execv(cmdargs[0], cmdargs);
				}else if(strcmp(command[i+1],"div") == 0){  // div
					pid_t pid;
					pid = fork();		
					if(pid==0){ 
						//child process bu kismi calistiriyor
						char *cmdargs[] = {"./div.out",
											command[i+2],
											command[i+3],
											NULL
										};
						system("gcc -o ./div.out ./div.c"); // div.c'yi compile ediyoruz
						execv(cmdargs[0], cmdargs);
					}else{ //parent process bu kismi calistiriyor
						wait(NULL); //parent, cocugun islemini bitirmesini bekliyor
					}

				}else if(strcmp(command[i+1],"mul") == 0){ // mul
					pid_t pid;
					pid = fork();		
					if(pid==0){ //child process
						char *cmdargs[] = {"./mul.out",
											command[i+2],
											command[i+3],
											NULL
										};
						system("gcc -o ./mul.out ./mul.c"); // mul.c'yi compile ediyoruz
						execv(cmdargs[0], cmdargs);
					}else{
						wait(NULL); //parent, cocugun islemini bitirmesini bekliyor
					}

				}else if(strcmp(command[i+1],"cat") == 0){// cat
					printf("cat: %s\n", command[i+2]);
				}else if(!strcmp(command[i+1],"clear")){// clear
					system("clear");
				}else{ // yanlis komut girisinde hata mesaji bas
					printf("myshell: %s: yanlis bir komut girdiniz\n", command[0]);
				}
			}
		}
		
		printf("myshell>> ");
	}
	
	return 0;
}