#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#define MAX_RECORDS 100

typedef struct records{
	char topic[21];
	int number;
	char question[151];
	char choice1[31];
	char choice2[31];
	char choice3[31];
	char answer[31];
} records;

typedef struct scoreList{
	int rowNum;
	char Name[51];
	int score;
}scores;

typedef struct topicsList{
	char genre[21];
	int amount;
}topics;

int checkEmptyIndexList(topics list[]);
void interface(char *result, char password[],records quiz[]);
void recordManager(char *result, char password[], records quiz[]);

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

int checkEmptyIndexQuiz(records quiz[]){
	int i = 0;
	do{
		if(quiz[i].question[0] == '\0'){
			return i;
		}
		i++;
	}while(i != 100);
	return i;
}

void addRecord(char *result, char password[], records quiz[]){
	records check;
	int i;
	int n = checkEmptyIndexQuiz(quiz);
	char yes,c;
	
	if(n == 100){
		printf("The records are already full, please remove a record to use this feature.\n");
		printf("You will now be redirected to the records interface.\n");
		recordManager(&*result, password, quiz);
	}
	
	printf("Please input a question.\n");
	scanf("%c", &yes);
	fgets(check.question, 151, stdin);
	check.question[strcspn(check.question,"\n")] = '\0';
	printf("Please input the answer.\n");
	fgets(check.answer, 31, stdin);
	check.answer[strcspn(check.answer,"\n")] = '\0';
	for(i = 0; i < n; i++){
		if(strcmp(check.question, quiz[i].question) == 0 && strcmp(check.answer, quiz[i].answer) == 0){
		printf("%s\n", quiz[i].topic);
		printf("%d\n", quiz[i].number);
		printf("%s\n", quiz[i].question);
		printf("%s\n", quiz[i].choice1);
		printf("%s\n", quiz[i].choice2);
		printf("%s\n", quiz[i].choice3);
		printf("%s\n", quiz[i].answer);
		printf("The input question and answer is already existing\n");
		printf("You will now be redirected to the records interface.\n");
		recordManager(&*result, password, quiz);
		}
	}	
	
	if(i == n){
		printf("Please input a topic.\n");
		fgets(check.topic, 21, stdin);
		check.topic[strcspn(check.topic,"\n")] = '\0';
		printf("Please input the question number.\n");
		scanf("%d", &check.number);
		scanf("%c", &c);
		printf("Please input the first choice.\n");
		fgets(check.choice1, 31, stdin);
		check.choice1[strcspn(check.choice1,"\n")] = '\0';
		printf("Please input the second choice.\n");
		fgets(check.choice2, 31, stdin);
		check.choice2[strcspn(check.choice2,"\n")] = '\0';
		printf("Please input the third choice.\n");
		fgets(check.choice3, 31, stdin);
		check.choice3[strcspn(check.choice3,"\n")] = '\0';
		quiz[i] = check;
		system("cls");
		printf("Record added success.\n\n");
		*result = '\0';
		interface(&*result, password, quiz);
	}
	
}

void editRecord(){
	printf("You are now editing a record");
}

void deleteRecord(){
	printf("You are now deleting a record");
}

void importData(char *result, char password[], records quiz[]){
	FILE *fp;
	char filename[51];
	char c;
	int choice = 0, i = 0;
	printf("Enter the name of the file: ");
	scanf("%c", &c);
	fgets(filename, 51, stdin);
	filename[strcspn(filename,"\n")] = '\0';
	fp = fopen(filename, "r");
	if(fp == NULL){
		printf("The file cannot be found, would you like to go back or try again? (1 - go back, 2 - try again)");
		scanf("%d", &choice);
		if(choice == 1){
			*result = '\0';
			interface(&*result, password, quiz);
		}
		if(choice == 2){
			importData(&*result, password, quiz);
		}
		if(choice != 1 || choice != 2){
			printf("chosen number is not registered as a choice, type any key to return to main interface...");
			*result = '\0';
			interface(&*result, password, quiz);
		}
	}
	if(fp != NULL){
		do{
			fscanf(fp, "%s\n", quiz[i].topic);
			fscanf(fp, "%d\n", &quiz[i].number);
			fgets(quiz[i].question, 151, fp);
			quiz[i].question[strcspn(quiz[i].question, "\n")] = '\0';
			fscanf(fp, "%s\n", quiz[i].choice1);
			fscanf(fp, "%s\n", quiz[i].choice2);
			fscanf(fp, "%s\n", quiz[i].choice3);
			fscanf(fp, "%s\n\n", quiz[i].answer);
			i++;
		}while(!feof(fp) == 1);
		printf("import succesful, returning to main interface...\n");
		*result = '\0';
		interface(&*result, password, quiz);
	}
}

void ExportData(char *result, char password[], records quiz[]){
	FILE *fp;
	int i = 0;
	char filename[31];
	char c;
	printf("Where should we export the Data? ");
	scanf("%c", &c);
	fgets(filename, 31, stdin);
	filename[strcspn(filename,"\n")] = '\0';
	fp = fopen(filename,"w");
	do{
		fprintf(fp, "%s\n", quiz[i].topic);
		fprintf(fp, "%d\n", quiz[i].number);
		fprintf(fp, "%s\n", quiz[i].question);
		fprintf(fp, "%s\n", quiz[i].choice1);
		fprintf(fp, "%s\n", quiz[i].choice2);
		fprintf(fp, "%s\n", quiz[i].choice3);
		fprintf(fp, "%s\n\n", quiz[i].answer);
		i++;
	}while(quiz[i].question[0] != '\0');
	fclose(fp);
	printf("file has been exported, returning to main hub.....\n\n");
	*result = '\0';
	interface(&*result, password, quiz);
	
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
			addRecord(&*result, password, quiz);
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
			importData(&*result, password, quiz);
			break;
		case 5:
			system("cls");
			ExportData(&*result, password, quiz);
			break;
		default:
			choice2 = '\0';
			do{
				printf("Choice of feature is not listed in the directory\n");
				printf("Would you like to return to the interface or try again? (1 - try again, 2 - return interface) ");
				scanf("%c", &choice2);
				scanf("%c", &choice2);
				switch(choice2){
					case '1':
						recordManager(&*result, password, quiz);
						break;
					case '2':
						*result = '\0';
						interface(&*result, password, quiz);
						break;
					default:
						choice2 = '\0';			
				}
			}while(choice2 == '\0');
			break;
	}
}

void displayScore(char *result, char password[], records quiz[]){
	FILE *fp;
	char c;
	int i = 0;
	scores list[MAX_RECORDS];
	fp = fopen("scores.txt", "r");
	if(fp == NULL){
	}
	if(fp != NULL){
	printf("Rankings:\n\n");
	do{
		fscanf(fp, "%d", &list[i].rowNum);
		fscanf(fp, "%s", list[i].Name);
		fscanf(fp, "%d\n", &list[i].score);
		printf("%d %s %d\n", list[i].rowNum, list[i].Name, list[i].score);
		i++;
	}while(!feof(fp) == 1); 
	}
	fclose(fp);
	printf("\nEnter any key to return to Main Hub ");
	scanf("%c", &c);
	scanf("%c", &c);
	switch(c){
		default:
			system("cls");
			*result = '\0';
			interface(&*result, password, quiz);
			break;
	}
}
int checkExistingTopic(topics list[], char topic[21]){
		int i;
		for(i = 0; i < MAX_RECORDS;i++){
			if(strcmp(list[i].genre, topic) == 0){
				return 1;
			}
		}
		return 0;
}
 
void organizeTopics(topics list[],records quiz[]){
	char check[21];
	int i,j,count;
	
	for(i = 0; i < MAX_RECORDS;i++){
		count = 0;
		if(checkExistingTopic(list, quiz[i].topic) == 0){
				strcpy(check, quiz[i].topic);
				for(j = 0; j < MAX_RECORDS;i++){
					if(strcmp(check, quiz[j].topic) == 0){
						count++; 
					}
				}
			list[checkEmptyIndexList(list)].amount = count;
			strcpy(list[checkEmptyIndexList(list)].genre,quiz[i].topic);
		}
	}
}

int checkEmptyIndexList(topics list[]){
	int i = 0;
	do{
		if(list[i].genre[0] == '\0'){
			return i;
		}
		i++;
	}while(i != MAX_RECORDS);
	return i;
}

void playGame(char *result, char password[], records quiz[]){
	scores playerInfo;
	int i = 0,j,scoreCount = 0;
	char choice[8][21];
	char answer[31];
	char c;
	topics list[MAX_RECORDS];
	organizeTopics(list, quiz);
	printf("Please enter a name: ");
	scanf("%c", &c);
	fgets(playerInfo.Name,51,stdin);
	do{
		printf("Please Choose a topic: \n");
		for(j = 0; j < checkEmptyIndexList(list); j++){
			printf("%s (%d)\n", list[j].genre, list[j].amount);	
		}
		fgets(&choice[i][0],21,stdin);
		if(strcmp(answer, quiz[i].answer) == 0){
		scoreCount++;
		}
		i++;
	}while(i < 7);
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
			if(checkEmptyIndexQuiz(quiz) == 0){
				printf("Error in initiating the game. Please add a record before playing\n");
				printf("You are now redirected to the play interface\n\n");
				PlayInterface(&*result, password,quiz);
			}
			playGame(&*result, password, quiz);
			break;
		case '2':
			system("cls");
			displayScore(&*result, password, quiz);
			break;
		case '3':
			system("cls");
			*result = '\0';
			interface(&*result, password, quiz);
			break;
		default:
			system("cls");
			printf("Choice input is not listed in the directory, Please try again\n\n");
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
					system("cls");
					printf("The Character is not listed in the directory, Please enter a new Character.\n");
					*result = '\0';
					break;	
			}
	}
}

int main()
{
	char result;
	char password[21] = "Lance";
	records quiz[MAX_RECORDS];
	
	interface(&result, password, quiz);
	
	return 0;
	
}
