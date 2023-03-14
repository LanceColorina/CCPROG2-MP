#include<stdio.h>
#include<string.h>
#include<conio.h>
void addRecord(){
	printf("You are now adding a record");
}

void editRecord(){
	printf("You are now editing a record");
}

void deleteRecord(){
	printf("You are now deleting a record");
}
int password(char password[], int n, char EnteredPassword[])
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

void ManageStart(char passWord[], int n, char *result)
{
	int i,pick;
	char choice;
	char EnteredPassword[n];
	while (password(passWord, n, EnteredPassword) != 0)
	{
		printf("Please Enter your password: ");
		
		for(i = 0; i < n; i++)
		{
			EnteredPassword[i] = getch();
			printf("*");
		}
			EnteredPassword[i] = '\0';
			printf("\n");
	
		password(passWord, n, EnteredPassword);
		if (password(passWord, n, EnteredPassword) == 1)
		{
			printf("Incorrect Password, would you like to try again or go back to the main menu?(Y - try again, N - go back)\n");
			scanf("%c", &choice);
			scanf("%c", &choice);
			
			
			switch(choice)
			{
				case 'Y':
					password(passWord, n, EnteredPassword);
					break;
				case 'N':
					*result = '\0';
					interface(result, passWord);
					break;
				default:
					do{
						pick = 1;
						printf("Character Input is not listed in the Directory please try again\n");
						printf("Incorrect Password, would you like to try again or go back to the main menu?(Y - try again, N - go back)\n");
						scanf("%c", &choice);
						scanf("%c", &choice);
						if(choice == 'Y'){
							pick = 0;
							password(passWord, n, EnteredPassword);
						}
						if (choice == 'N')
						{
							pick = 0;
							*result = '\0';
							interface(result, passWord);
						}
					}while(pick != 0);
					
					break;
			}
		
		}
	}
	
}

void recordManager(char *result, char password[]){
	int choice1;
	char choice2;
	printf("Welcome to the manager data interface, which features would you like to use? (1 - Add, 2 - Edit, 3 - Delete) ");
	scanf("%d", &choice1);
	switch(choice1)
	{
		case 1:
			addRecord();
			break;
		case 2:
			editRecord();
			break;
		case 3:
			deleteRecord();
			break;
		default:
			choice2 = '\0';
			printf("Choice of feature is not listed in the directory\n");
			printf("Would you like to return to the interface or try again? (1 - try again, 2 - return interface) ");
			scanf("%c", &choice2);
			scanf("%c", &choice2);
			if(choice2 == '2'){
				*result = '\0';
				interface(&*result, password);
			}
			if(choice2 == '1'){
				recordManager(&*result, password);
			}
			
			break;
	}
}

void interface(char *result, char password[])
{

	while(*result == '\0')
	{
		printf("Welcome to who doesn't want to fail CCPROG2!!!\nwhich interface would you like to use? (1 - Manage Data, 2 - Play, 3 - Exit) ");
		scanf("%c", &*result);
			switch(*result)
			{
				case '1':
					ManageStart(password, strlen(password), &*result);
					recordManager(&*result, password);
				 	break;
				case '2':
					Play();
					break;
				case '3':
					Exit();
					break;
				default:
					printf("The Character is not listed in the directory, Please enter a new Character.\n");
					*result = '\0';
					break;	
			}
	}
}

void Play()
{
	printf("This is the Play");
}

int Exit()
{
	printf("You are now exiting the program\n");
	return 0;
}

int main()
{
	char result;
	char password[21] = "Lance";
	interface(&result, password);
	
	return 0;
	
}
