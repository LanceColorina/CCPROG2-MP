#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>


typedef struct records{
	char topic[21];
	char question[151];
	char choice1[31];
	char choice2[31];
	char choice3[31];
	char answer[31];
} records;



int passWordCheck(char password[], int n, char EnteredPassword[])
{
	int i;
	for(i = 0; i < n;i++)
	{
		if(EnteredPassword[i] != password[i])
		{
			return 1;
		}
	}
	return 0;
}

void ManageStart(char password[], int n, char *result, records quiz[])
{
	int i,pick;
	char choice;
	char EnteredPassword[n];
	while (passWordCheck(password, n, EnteredPassword) != 0)
	{
		printf("Please Enter your password: ");
		
		for(i = 0; i < n; i++)
		{
			EnteredPassword[i] = getch();
			printf("*");
		}
			EnteredPassword[i] = '\0';
			printf("\n");
	
		passWordCheck(password, n, EnteredPassword);
		if (passWordCheck(password, n, EnteredPassword) == 1)
		{
			printf("Incorrect Password, would you like to try again or go back to the main menu?(Y - try again, N - go back)\n");
			scanf("%c", &choice);
			scanf("%c", &choice);
			
			
			switch(choice)
			{
				case 'Y':
					passWordCheck(password, n, EnteredPassword);
					break;
				case 'N':
					*result = '\0';
					interface(result, password, quiz);
					break;
				default:
					do{
						pick = 1;
						printf("Character Input is not listed in the Directory please try again\n");
						printf("Incorrect Password, would you like to try again or go back to the main menu?(Y - try again, N - go back)\n");
						scanf("%c", &choice);
						scanf("%c", &choice);
						switch(choice){
							case 'Y':
								pick = 0;
								ManageStart(password, strlen(password), &*result, quiz);
								break;
							case 'N':
								pick = 0;
								*result = '\0';
								interface(&*result, password, quiz);
								break;
							default:
								pick = 1;
						}
							
					}while(pick != 0);
					
					break;
			}
		
		}
	}
	
}

void Exit()
{
	printf("You are now exiting the program\n");
	printf("Thank you for playing");
}



void addRecord(char *result, char password[], records quiz[], int n){
	records check;
	int i;
	printf("Please input a question.\n");
	fgets(check.question, 151, stdin);
	fgets(check.question, 151, stdin);
	printf("Please input the answer.\n");
	fgets(check.answer, 31, stdin);
	for(i = 0; i < n; i++){
		if((strcmp(check.question, quiz[i].question) == 0) && (strcmp(check.answer, quiz[i].answer) == 0)){
			printf("%s\n", quiz[i].topic);
			printf("%s\n", quiz[i].question);
			printf("%s\n", quiz[i].choice1);
			printf("%s\n", quiz[i].choice2);
			printf("%s\n", quiz[i].choice3);
			printf("%s\n", quiz[i].answer);
			printf("The given question and answer is already listed in the records");
			system("cls");
			printf("You will be redirected to the main menu");
			*result = '\0';
			interface(interface(&*result, password, quiz));
		}
	}
	
}

void editRecord(){
	printf("You are now editing a record");
}

void deleteRecord(){
	printf("You are now deleting a record");
}


void recordManager(char *result, char password[], records quiz[]){
	int choice1;
	char choice2;
	printf("Welcome to the manager data interface, which features would you like to use? \n(1 - Add, 2 - Edit, 3 - Delete, 4 - Import Data, 5 - Export Data) ");
	scanf("%d", &choice1);
	switch(choice1)
	{
		case 1:
			system("cls");
			addRecord(&*result, password, quiz, 7);
			break;
		case 2:
			system("cls");
			editRecord();
			break;
		case 3:
			system("cls");
			deleteRecord();
			break;
		case 4:
			system("cls");
			//ImportData();
			break;
		case 5:
			system("cls");
			//ExportData();
			break;
		default:
			choice2 = '\0';
			printf("Choice of feature is not listed in the directory\n");
			printf("Would you like to return to the interface or try again? (1 - try again, 2 - return interface) ");
			scanf("%c", &choice2);
			scanf("%c", &choice2);
			if(choice2 == '2'){
				*result = '\0';
				interface(&*result, password, quiz);
			}
			if(choice2 == '1'){
				recordManager(&*result, password, quiz);
			}
			
			break;
	}
}

void PlayInterface(char *result, char password[], records quiz[])
{
	char choice;
	printf("Welcome to the main hub of ""Who doesn't want to fail CCPROG2""\n");
	printf("Which options would you like to use?(1 - Play, 2 - View Scores, 3 - Exit) ");
	scanf("%c", &choice);
	scanf("%c", &choice);
	
	switch(choice){
		case '1':
			system("cls");
			//playGame();
			break;
		case '2':
			system("cls");
			//scores();
			break;
		case '3':
			system("cls");
			*result = '\0';
			interface(&*result, password, quiz);
			break;
		default:
			system("cls");
			printf("Choice input is not listed in the directory, Please try again\n");
			PlayInterface(&*result, password,quiz);
			break;
	}
	
}

void interface(char *result, char password[],records quiz[])
{

	while(*result == '\0')
	{
		printf("Welcome to who doesn't want to fail CCPROG2!!!\nwhich interface would you like to use? (1 - Manage Data, 2 - Play, 3 - Exit) ");
		scanf("%c", &*result);
			switch(*result)
			{
				case '1':
					system("cls");
					ManageStart(password, strlen(password), &*result, quiz);
					recordManager(&*result, password, quiz);
				 	break;
				case '2':
					system("cls");
					PlayInterface(&*result, password,quiz);
					break;
				case '3':
					system("cls");
					Exit();
					break;
				default:
					printf("The Character is not listed in the directory, Please enter a new Character.\n");
					*result = '\0';
					system("cls");
					break;	
			}
	}
}

int main()
{
	char result;
	char password[21] = "Lance";
	records quiz[7];
	
	interface(&result, password, quiz);
	
	return 0;
	
}
