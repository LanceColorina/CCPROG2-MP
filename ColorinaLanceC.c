#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

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

int passWordCheck(char password[], int n, char EnteredPassword[]);
void ManageStart(char password[], int n,records quiz[]);
void Exit();
int checkEmptyIndexQuiz(records quiz[]);
void addRecord(char password[], records quiz[]);
void editRecord(char password[], records quiz[]);
void deleteRecord();
void importData(char password[], records quiz[]);
void ExportData(char password[], records quiz[]);
void recordManager(char password[], records quiz[]);
void displayScore(char password[], records quiz[]);
int checkExistingTopic(topics list[], char topic[21]);
int organizeTopics(topics list[],records quiz[]);
int checkEmptyIndexList(topics list[]);
void playGame(char password[], records quiz[]);
void PlayInterface(char password[], records quiz[]);
void interface(char password[],records quiz[]);
void arrangeRanking(scores playerInfo[], int n);

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

void ManageStart(char password[], int n,records quiz[])
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
					interface(password, quiz);
					break;
				default:
					do{
						pick = 1;
						printf("Character Input is not listed in the Directory please try again\n");
						printf("Incorrect Password, would you like to try again or go back to the main menu?(Y - try again, N - go back)\n");
						scanf("%c", &choice);
						scanf("%c", &choice);
						switch(choice)
						{
							case 'Y':
								pick = 0;
								ManageStart(password, strlen(password), quiz);
								break;
							case 'N':
								pick = 0;
								interface(password, quiz);
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
	exit(0);
}

int checkEmptyIndexQuiz(records quiz[])
{
	int i = 0;
	do{
		if(quiz[i].question[0] == '\0')
		{
			return i;
		}
		i++;
	}while(i != 100);
	return i;
}

int checkTopicIndex(records check, records quiz[])
{
	int i, temp = -1;
	for(i = 0; i < checkEmptyIndexQuiz(quiz); i++)
	{
		if(strcmp(check.topic, quiz[i].topic) == 0)
		{
			temp = i;
		}
	}
	if(temp == -1){
		return -1;
	}
	else
		return temp;
}
void addRecord(char password[], records quiz[])
{
	records check;
	int i;
	int n = checkEmptyIndexQuiz(quiz);
	char yes,c;
	
	if(n == 100)
	{
		printf("The records are already full, please remove a record to use this feature.\n");
		printf("You will now be redirected to the records interface.\n");
		recordManager(password, quiz);
	}
	
	printf("Please input a question.\n");
	scanf("%c", &yes);
	fgets(check.question, 151, stdin);
	check.question[strcspn(check.question,"\n")] = '\0';
	printf("Please input the answer.\n");
	fgets(check.answer, 31, stdin);
	check.answer[strcspn(check.answer,"\n")] = '\0';
	for(i = 0; i < n; i++)
	{
		if(strcmp(check.question, quiz[i].question) == 0 && strcmp(check.answer, quiz[i].answer) == 0)
		{
		printf("%s\n", quiz[i].topic);
		printf("%d\n", quiz[i].number);
		printf("%s\n", quiz[i].question);
		printf("%s\n", quiz[i].choice1);
		printf("%s\n", quiz[i].choice2);
		printf("%s\n", quiz[i].choice3);
		printf("%s\n", quiz[i].answer);
		printf("The input question and answer is already existing\n");
		printf("You will now be redirected to the records interface.\n");
		recordManager(password, quiz);
		}
	}	
	
	if(i == n)
	{
		printf("Please input a topic.\n");
		fgets(check.topic, 21, stdin);
		check.topic[strcspn(check.topic,"\n")] = '\0';
		if(checkTopicIndex(check, quiz) > 1)
		{
		check.number = quiz[checkTopicIndex(check, quiz)].number + 1;
		}
			else
				check.number = 1;
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
		interface(password, quiz);
	}
	
}
int checkForExistingTopic(char choice[], topics list[])
{
	int i;
	for(i = 0; i < checkEmptyIndexList(list); i++)
	{
		if(strcmp(choice, list[i].genre) == 0)
		{
			return 0; 
		}
	}
	return 1;
}

void adjustQuestionNumber(char topic[21], records quiz[], int questionNumber)
{
	int i;
	for(i = 0; i < checkEmptyIndexQuiz(quiz); i++)
	{
		if(strcmp(topic, quiz[i].topic) == 0 && questionNumber < quiz[i].number)
		{
			quiz[i].number = quiz[i].number - 1;
		}
	}
}
int topicIndex(char choice[], topics list[])
{
	int index,i;
	for(i = 0; i < MAX_RECORDS;i++)
	{
		if(strcmp(list[i].genre,choice) == 0)
		{
			return i;
		}
	}
	
	return i;
}
void editRecord(char password[], records quiz[])
{
	int i,j,k; //looping variables
	int number,edit; // number - chosen question number, edit - holds a choice of what to edit
	char c;
	records temp; // temporary holder for things to edit
	char topicTemp[21]; //holder for previous topic before editing
	int questionNumber; // holds the question number for the edited topic
	topics list[MAX_RECORDS];
	char choice[21]; // choice of topic user would like to edit
	int n = organizeTopics(list, quiz);
	printf("Choose a topic you would like to edit here\n");
	for(i = 0; i < checkEmptyIndexList(list); i++)
	{
		printf("%s\n",list[i].genre); 
	}
	scanf("%c", &c);
	fgets(choice, 21,stdin);
	choice[strcspn(choice, "\n")] = '\0';
	if(checkForExistingTopic(choice, list) == 1)
	{
		system("cls");
		printf("The topic you have input is not in the listed topic, redirecting you to the main hub...\n");
		interface(password, quiz);
	}
	printf("Choose a question to edit\n");
	for(j = 0; j < checkEmptyIndexQuiz(quiz); j++)
	{
		if(strcmp(quiz[j].topic, choice) == 0)
		{
			printf("%s\n", quiz[j].question);
			printf("%d\n\n", quiz[j].number);
		}
	}
	scanf("%d", &number);
	if(number > list[topicIndex(choice, list)].amount)
	{
		system("cls");
		printf("The question number you have chosen is not in the listed topic, redirecting you to the main hub...\n");
		interface(password, quiz);
	}
	
	system("cls");
	for(k = 0; k < checkEmptyIndexQuiz(quiz); k++)
	{
		if((strcmp(choice, quiz[k].topic) == 0) && (number == quiz[k].number))
		{
			printf("What would you like to edit for this question?\n(1 - topic ,2 - question? ,3 - choice1 ,4 - choice2 ,5 - choice3 ,6 - answer)\n");
			printf("%s\n", quiz[k].topic);
			printf("%s\n", quiz[k].question);
			printf("%s\n", quiz[k].choice1);
			printf("%s\n", quiz[k].choice2);
			printf("%s\n", quiz[k].choice3);
			printf("%s\n", quiz[k].answer);
			scanf("%d", &edit);
			scanf("%c", &c);
			switch(edit)
			{
				case 1:
					
					printf("Enter the new topic: ");
					strcpy(topicTemp,quiz[k].topic);
					questionNumber = quiz[k].number;
					fgets(temp.topic, 21,stdin);
					temp.topic[strcspn(temp.topic,"\n")] = '\0';
					strcpy(quiz[k].topic, temp.topic);
					if(checkTopicIndex(temp, quiz) > -1)
					{
						quiz[k].number = 1;
					}
						else 
							quiz[k].number = quiz[checkTopicIndex(temp, quiz)].number + 1;
							adjustQuestionNumber(topicTemp,quiz, questionNumber);
					system("cls");			
					printf("Topic for this question has been succesfully edited. Returning to main hub...\n");
					interface(password, quiz);
					break;
				case 2:
					printf("Enter the new question: ");
					fgets(temp.question, 151,stdin);
					temp.question[strcspn(temp.question,"\n")] = '\0';
					strcpy(quiz[k].question, temp.question);
					system("cls");
					printf("Question has been succesfully edited. Returning to main hub...\n");
					interface(password, quiz);
					break;
				case 3:
					printf("Enter the new choice: ");
					fgets(temp.choice1, 21,stdin);
					temp.choice1[strcspn(temp.choice1,"\n")] = '\0';
					strcpy(quiz[k].choice1, temp.choice1);
					system("cls");
					printf("Choice 1 for this question has been succesfully edited. Returning to main hub...\n");
					interface(password, quiz);
					break;
				case 4:
					printf("Enter the new choice: ");
					fgets(temp.choice2, 21,stdin);
					temp.choice2[strcspn(temp.choice2,"\n")] = '\0';
					strcpy(quiz[k].choice2, temp.choice2);
					system("cls");
					printf("Choice 2 for this question has been succesfully edited. Returning to main hub...\n");
					interface(password, quiz);
					break;
				case 5:
					printf("Enter the new choice: ");
					fgets(temp.choice3, 21,stdin);
					temp.choice3[strcspn(temp.choice3,"\n")] = '\0';
					strcpy(quiz[k].choice3, temp.choice3);
					system("cls");
					printf("Choice 3 for this question has been succesfully edited. Returning to main hub...\n");
					interface(password, quiz);
					break;
				case 6:
					printf("Enter the new answer: ");
					fgets(temp.answer, 21,stdin);
					temp.answer[strcspn(temp.answer,"\n")] = '\0';
					strcpy(quiz[k].answer, temp.answer);
					system("cls");
					printf("Choice 1 for this question has been succesfully edited. Returning to main hub...\n");
					interface(password, quiz);
					break;
				default:
					system("cls");
					printf("ERROR!!!\nchoice is not listed in the directory, returning to main hub...\n");
					interface(password, quiz);
			}
		}
	}
	
}

void deleteRecord(char password[], records quiz[])
{
	int i,j,k,l,m; //looping variables
	int number,del; // number - chosen question number, del - holds a choice of what to del
	char c;
	records temp; // temporary holder for things to edit
	char topicTemp[21]; //holder for previous topic before editing
	int questionNumber; // holds the question number for the edited topic
	topics list[MAX_RECORDS];
	char choice[21]; // choice of topic user would like to edit
	int n = organizeTopics(list, quiz);
	printf("Choose a topic you would like to Delete here\n");
	for(i = 0; i < checkEmptyIndexList(list); i++)
	{
		printf("%s\n",list[i].genre); 
	}
	scanf("%c", &c);
	fgets(choice, 21,stdin);
	choice[strcspn(choice, "\n")] = '\0';
	if(checkForExistingTopic(choice, list) == 1)
	{
		system("cls");
		printf("The topic you have input is not in the listed topic, redirecting you to the main hub...\n");
		interface(password, quiz);
	}
	printf("Choose a question to Delete\n");
	for(j = 0; j < checkEmptyIndexQuiz(quiz); j++)
	{
		if(strcmp(quiz[j].topic, choice) == 0)
		{
			printf("%s\n", quiz[j].question);
			printf("%d\n\n", quiz[j].number);
		}
	}
	scanf("%d", &number);
	if(number > list[topicIndex(choice, list)].amount)
	{
		system("cls");
		printf("The question number you have chosen is not in the listed topic, redirecting you to the main hub...\n");
		interface(password, quiz);
	}
	for(k = 0; k < checkEmptyIndexQuiz(quiz); k++)
	{
		if((strcmp(choice, quiz[k].topic) == 0) && (number == quiz[k].number))
		{
			del = k;
		}
	}
	for(l = del; l < checkEmptyIndexQuiz(quiz); l++)
	{
		quiz[l] = quiz[l + 1]; 
	}
	
	for(m = 0; m < checkEmptyIndexQuiz(quiz); m++)
	{
		if(strcmp(choice, quiz[m].topic) == 0 && number < quiz[m].number)
		{
			quiz[m].number = quiz[m].number - 1;
		}
	}
	system("cls");
	printf("Records chosen has been succesfully deleted. Returning to main hub...\n");
	interface(password, quiz);
}


void importData(char password[], records quiz[])
{
	FILE *fp;
	char filename[51];
	char c;
	int choice = 0, i = checkEmptyIndexQuiz(quiz), j = 0, exist;
	printf("Enter the name of the file: ");
	scanf("%c", &c);
	fgets(filename, 51, stdin);
	filename[strcspn(filename,"\n")] = '\0';
	fp = fopen(filename, "r");
	if(fp == NULL)
	{
		printf("The file cannot be found, would you like to go back or try again? (1 - go back, 2 - try again)");
		scanf("%d", &choice);
		if(choice == 1)
		{
			interface(password, quiz);
		}
		if(choice == 2)
		{
			importData(password, quiz);
		}
		if(choice != 1 || choice != 2)
		{
			system("cls");
			printf("chosen number is not registered as a choice, type any key to return to main interface...\n");
			interface(password, quiz);
		}
	}
	if(fp != NULL)
	{
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
		interface(password, quiz);
	}
}

void ExportData(char password[], records quiz[])
{
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
	interface(password, quiz);
	
}
void recordManager(char password[], records quiz[])
{
	int choice1;
	char choice2;
	printf("Welcome to the manager data interface, which features would you like to use? \n(1 - Add, 2 - Edit, 3 - Delete, 4 - Import Data, 5 - Export Data) ");
	scanf("%d", &choice1);
	switch(choice1)
	{
		case 1:
			system("cls");
			addRecord(password, quiz);
			break;
		case 2:
			system("cls");
			if(checkEmptyIndexQuiz(quiz) == 0)
			{
				printf("There are no existing records to edit, please try again\n");
				recordManager(password, quiz);
			}
			editRecord(password, quiz);
			break;
		case 3:
			system("cls");
			if(checkEmptyIndexQuiz(quiz) == 0)
			{
				printf("There are no existing records to delete, please try again\n");
				recordManager(password, quiz);
			}
			deleteRecord(password, quiz);
			break;
		case 4:
			system("cls");
			importData(password, quiz);
			break;
		case 5:
			system("cls");
			if(checkEmptyIndexQuiz(quiz) == 0)
			{
				printf("There are no existing records to Export, please try again\n");
				recordManager(password, quiz);
			}
			ExportData(password, quiz);
			break;
		default:
			choice2 = '\0';
			do{
				printf("Choice of feature is not listed in the directory\n");
				printf("Would you like to return to the interface or try again? (1 - try again, 2 - return interface) ");
				scanf("%c", &choice2);
				scanf("%c", &choice2);
				switch(choice2)
				{
					case '1':
						recordManager(password, quiz);
						break;
					case '2':
						interface(password, quiz);
						break;
					default:
						choice2 = '\0';			
				}
			}while(choice2 == '\0');
			break;
	}
}

void displayScore(char password[], records quiz[])
{
	FILE *fp;
	char c;
	int i = 0,j = 0;
	scores playerInfo[MAX_RECORDS];
	fp = fopen("scores.txt", "r");
	if(fp != NULL)
	{
	printf("Rankings:\n\n");
	do{
		fscanf(fp, "%d", &playerInfo[i].rowNum);
		fscanf(fp, "%s", playerInfo[i].Name);
		fscanf(fp, "%d\n", &playerInfo[i].score);
		i++;
	}while(!feof(fp) == 1); 
	arrangeRanking(playerInfo, i);
	}
	fclose(fp);
	for(j = 0; j < i; j++)
	{
		printf("%d %s %d\n", playerInfo[j].rowNum, playerInfo[j].Name, playerInfo[j].score);
	}
	printf("\nEnter any key to return to Main Hub ");
	scanf("%c", &c);
	scanf("%c", &c);
	switch(c)
	{
		default:
			system("cls");
			interface(password, quiz);
			break;
	}
}

int checkExistingTopic(topics list[], char topic[21])
{
		int i;
		for(i = 0; i < MAX_RECORDS;i++)
		{
			if(strcmp(list[i].genre, topic) == 0)
			{
				return 1;
			}
		}
		return 0;
}
 
int organizeTopics(topics list[],records quiz[])
{
	char check[21];
	int i,j,k,count,index = 0;
	for(k = 0; k < MAX_RECORDS; k++)
	{
		list[k].genre[0] = '\0';	
	}
	for(i = 0; i < checkEmptyIndexQuiz(quiz);i++)
	{
		count = 0;
		if(checkExistingTopic(list, quiz[i].topic) == 0)
		{
				strcpy(check, quiz[i].topic);
				for(j = 0; j < MAX_RECORDS;j++)
				{
					if(strcmp(check, quiz[j].topic) == 0)
					{
						count++; 
					}
				}
			list[checkEmptyIndexList(list)].amount = count;
			strcpy(list[checkEmptyIndexList(list)].genre,quiz[i].topic);
			index++;
		}
	}
	return index;
}

int checkEmptyIndexList(topics list[])
{
	int i = 0;
	do{
		if(list[i].genre[0] == '\0')
		{
			return i;
		}
		i++;
	}while(i != MAX_RECORDS);
	return i;
}
void arrangeRanking(scores playerInfo[], int n)
{
	int i,j,k,min;
	scores temp;
	
	for(i = 0; i < n - 1; i++)
	{
		min = i;
		
		for(j = i + 1; j < n; j++)
		{
			if(playerInfo[i].score < playerInfo[j].score)
			{
				min = j;
			}
		}
		if(i != min)
		{
			temp = playerInfo[i];
			playerInfo[i] = playerInfo[min];
			playerInfo[min] = temp;
		}
	}
	for(k = 0; k < n; k++)
	{
		playerInfo[k].rowNum = k + 1;
	}
	
}
void playGame(char password[], records quiz[])
{
	scores playerInfo;
	int endChoice; // checks if the input topic is listed
	int i = 0,j = 0,k,l,m = 1,o = 0; // int variables for looping
	int scoreCount = 0; // counter for the player's score
	int randomNumber, index, end = 0; // randomNumber - holder for a random number when choosing questions, index - index of the topic in struct topics, end - checks if player wants to end the game
	char choice[21]; // holder for topic choice
	char answer[31];// holder for player answer choice
	char c; //for clearing out the \n in every input
	topics list[MAX_RECORDS]; // array struct for topics available and amount for each topic
	int n = organizeTopics(list, quiz); // organizes the list of unique topics and the amount of questions listed in the struct
	printf("Please enter a name: ");
	scanf("%c", &c);
	fgets(playerInfo.Name,51,stdin);
	playerInfo.Name[strcspn(playerInfo.Name, "\n")] = '\0';
	
	do{
		printf("Please Choose a topic: \n");
		j = 0;
		do{
			printf("%s (%d)\n", list[j].genre, list[j].amount);	
			j++;
		}while(j < n);
		fgets(choice,21,stdin);
		choice[strcspn(choice,"\n")] = '\0';
		for(k = 0; k < n; k++)
		{
			if(strcmp(choice, list[k].genre) == 0)
			{
				index = k;
				system("cls");
			}	
		}
		srand(time(0));
		if(list[index].amount > 1)
		{
			randomNumber = (rand() % (list[index].amount + 1));
		}
		if(list[index].amount == 1)
		{
			randomNumber = 1;
		}
		
		for(l = 0; l < checkEmptyIndexQuiz(quiz); l++)
		{
			if(strcmp(quiz[l].topic, choice) == 0 && randomNumber == quiz[l].number)
			{
				printf("%d\t\t your score is %d\n", quiz[l].number, scoreCount);
				printf("%s\n", quiz[l].question);
				printf("%s\n", quiz[l].choice1);
				printf("%s\n", quiz[l].choice2);
				printf("%s\n", quiz[l].choice3);
				fgets(answer, 31,stdin);
				answer[strcspn(answer,"\n")] = '\0';	
				if(strcmp(answer, quiz[l].answer) == 0)
				{
					scoreCount++;
					printf("Your answer is Correct, would you like to Continue or end the game?(1 - Continue, 2 - end game)\n");
					
				}	
				if(strcmp(answer, quiz[l].answer) != 0)
				{
					printf("Your answer is wrong, would you like to try again or end the game?(1 - try again, 2 - end game)\n");	
				}
				scanf("%d", &endChoice);
				scanf("%c", &c);
				system("cls");
					if(endChoice == 1)
					{
						end = 0;
					}
					if(endChoice == 2)
					{
						end = 1;
					}
			}
		}
			
	}while(end == 0);
	
		playerInfo.score = scoreCount;
		playerInfo.rowNum = 0;
		FILE *fp;
		fp = fopen("scores.txt", "a");
		if(fp != NULL)
		{
				fprintf(fp, "%d %s %d\n", playerInfo.rowNum, playerInfo.Name, playerInfo.score);
		}
		fclose(fp);
		system("cls");
		printf("Thank you for playing who doesnt want to fail CCPROG\n");
		printf("Mr./Mrs. %s\nScore: %d\n", playerInfo.Name, scoreCount);
		printf("Returning you to the main hub...\n\n");
		interface(password, quiz);
	
}

void PlayInterface(char password[], records quiz[])
{
	char choice;
	printf("Welcome to the main hub of ""Who doesn't want to fail CCPROG2""\n");
	printf("Which options would you like to use?(1 - Play, 2 - View Scores, 3 - Exit) ");
	scanf("%c", &choice);
	scanf("%c", &choice);
	
	switch(choice)
	{
		case '1':
			system("cls");
			if(checkEmptyIndexQuiz(quiz) == 0)
			{
				printf("Error in initiating the game. Please add a record before playing\n");
				printf("You are now redirected to the play interface\n\n");
				PlayInterface(password,quiz);
			}
			playGame(password, quiz);
			break;
		case '2':
			system("cls");
			displayScore(password, quiz);
			break;
		case '3':
			system("cls");
			interface(password, quiz);
			break;
		default:
			system("cls");
			printf("Choice input is not listed in the directory, Please try again\n\n");
			PlayInterface(password,quiz);
			break;
	}
	
}

void interface(char password[],records quiz[])
{
	int result;
		printf("Welcome to who doesn't want to fail CCPROG2!!!\nwhich interface would you like to use? (1 - Manage Data, 2 - Play, 3 - Exit) ");
		scanf("%d", &result);
			switch(result)
			{
				case 1:
					system("cls");
					ManageStart(password, strlen(password), quiz);
					recordManager(password, quiz);
				 	break;
				case 2:
					system("cls");
					PlayInterface(password,quiz);
					break;
				case 3:
					system("cls");
					Exit();
					break;
				default:
					system("cls");
					interface(password, quiz);
					break;	
			}
}

int main()
{

	char password[21] = "Lance";
	records quiz[MAX_RECORDS];
	interface(password, quiz);
	
	return 0;
	
}
