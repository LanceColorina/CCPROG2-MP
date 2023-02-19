#include<stdio.h>
#include<string.h>

void interface(int *result)
{
	while(*result == 0)
	{
		printf("Welcome to who doesn't want to fail CCPROG2!!!\nwhich interface would you like to use? (1 - Manage Data, 2 - Play, 3 - Exit) ");
		scanf("%d", &*result);
			switch(*result)
			{
				case 1:
					*result = 1;
					break;
				case 2:
					*result = 2;
					break;
				case 3:
					*result = 3;
					break;
				default:
					printf("The Character is not listed in the directory, Please enter a new Character.\n");
					*result = 0;
					break;	
			}
	}
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

void Play()
{
	printf("This is the Play");
}

void Exit()
{
	printf("You will now Exit");
}

void ManageStart(char passWord[], int n)
{
	char EnteredPassword[n];
	while (password(passWord, n, EnteredPassword) != 0)
	{
		printf("Please Enter your password (Maximum of 20 characters): ");
		scanf("%s", &*EnteredPassword);
		password(passWord, n, EnteredPassword);
		if (password(passWord, n, EnteredPassword) == 1)
		{
			printf("Incorrect Password, Please try again\n");
			password(passWord, n, EnteredPassword);
		}
	}
	
		printf("The password is correct you are pogi HIHI");
}

int main()
{
	int result;
	char password[21];
	printf("Hello user, Before we start please input a password as an admin:\n");
	scanf("%s", &*password);
	interface(&result);
	
	switch(result)
	{
		case 1:
			ManageStart(password, strlen(password));
			break;
		case 2:
			Play();
			break;
		case 3:
			Exit();
			break;
	}	
	return 0;
	
}
