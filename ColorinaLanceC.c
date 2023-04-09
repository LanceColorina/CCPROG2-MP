/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
Colorina, Lance C. , DLSU ID# 12274909
*********************************************************************************************************/

#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_RECORDS 100

//struct for quiz records
typedef struct records{
	char topic[21];
	int number;
	char question[151];
	char choice1[31];
	char choice2[31];
	char choice3[31];
	char answer[31];
} records;

//struct for player info
typedef struct scoreList{
	int rowNum;
	char Name[51];
	int score;
}scores;

//struct for uniquetopics in quiz records and amount of questions
typedef struct topicsList{
	char genre[21];
	int amount;
}topics;

void ManageStart(char password[], int n,records quiz[]);
int checkEmptyIndexQuiz(records quiz[]);
void addRecord(char password[], records quiz[]);
int checkForExistingTopic(char choice[], topics list[]);
void adjustQuestionNumber(char topic[21], records quiz[], int questionNumber);
int topicIndex(char choice[], topics list[]);
void editRecord(char password[], records quiz[]);
void deleteRecord(char password[], records quiz[]);
void importData(char password[], records quiz[]);
void ExportData(char password[], records quiz[]);
void recordManager(char password[], records quiz[]);
void displayScore(char password[], records quiz[]);
int organizeTopics(topics list[],records quiz[]);
int checkEmptyIndexList(topics list[]);
void arrangeRanking(scores playerInfo[], int n);
void playGame(char password[], records quiz[]);
void PlayInterface(char password[], records quiz[]);
void mainInterface(char password[],records quiz[]);
void arrangeRanking(scores playerInfo[], int n);


/* 
	ManageStart asks the user to enter the password and checks if the password typed is correct. If password is incorrect, asks the user
	to choose to go back to the main menu or try again, if correct proceeds to the manage data Interface.
		@ param password - string of the correct password
		@ param n - length of the correct password
		@ param records quiz - struct array of the quiz records
*/
void ManageStart(char password[], int n,records quiz[])
{
	int i;
	
	char choice;
	char EnteredPassword[n];
	
		printf("Please Enter your password: ");
		
		for(i = 0; i < n; i++)
		{
			EnteredPassword[i] = getch();
			printf("*");
		}
			EnteredPassword[i] = '\0';
			printf("\n");
		if(strcmp(password, EnteredPassword) == 0)
		{
			recordManager(password, quiz);
		}
		if (strcmp(password, EnteredPassword) != 0)
		{
			printf("Incorrect Password, would you like to try again or go back to the main menu?(Y - try again, N - go back)\n");
			scanf("%c", &choice);
			scanf("%c", &choice);
			switch(choice)
			{
				case 'Y':
					ManageStart(password,n,quiz);
					break;
				case 'N':
					mainInterface(password, quiz);
					break;
				default:
						printf("Character Input is not listed in the Directory please try again\n");
						printf("Incorrect Password, would you like to try again or go back to the main menu?(Y - try again, N - go back)\n");
						scanf("%c", &choice);
						scanf("%c", &choice);
						switch(choice)
						{
							case 'Y':
								ManageStart(password, strlen(password), quiz);
								break;
							case 'N':
								mainInterface(password, quiz);
								break;
							default:
								printf("ERROR!! INVALID CHOICE, RETURNING TO MAIN MENU\n");
								mainInterface(password, quiz);
								break;		
						}
					break;
			}
		
		}
	
}

/*
	checkEmptyIndexQuiz checks the quiz records which index in the array does not have a question and returns it to the user
		@ param records quiz - struct array of the quiz records
*/
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

/* 
	addRecord will ask the user a question and an answer and checks if the given is already existing in the records, if it is, it will display the record and 
	user will be returned back to the manage data interface, if it is not, it will ask for the remaining information and add it to the empty index.
		@ param password - string of the correct password
		@ param records quiz - struct array of the quiz records
*/
void addRecord(char password[], records quiz[])
{
	records check; // holder for the new records
	topics list[MAX_RECORDS];
	
	int i;
	int num = organizeTopics(list, quiz);
	int n = checkEmptyIndexQuiz(quiz);
	
	char yes,c; // yes & c - for removes the \n in the scanf
	
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
		if(strcmp(check.question, quiz[i].question) == 0 && strcmp(check.answer, quiz[i].answer) == 0) // displays the record if it exists
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
	
	if(i == n) // if "i" reaches the empty index, will ask for the remaining information
	{
		printf("Please input a topic.\n");
		fgets(check.topic, 21, stdin);
		check.topic[strcspn(check.topic,"\n")] = '\0';
		if(topicIndex(check.topic,list) < checkEmptyIndexList(list)) // if the topic given exists, increments the latest records with that topic and puts in the question number
		{
			check.number = list[topicIndex(check.topic,list)].amount + 1;
		}
			else // if topic given is unique, makes the question number 1
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
		mainInterface(password, quiz);
	}
	
}

/*
	checkForExistingTopic returns 0 if the parameter choice is existing in the genre member of struct topics list, returns 1 if not
		@ param choice - a topic to be checked if existing in list
		@ param topics list - a struct array contaning the list of unique topics and amount of questions it has
*/
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
	return 1; // returns 1 if choice is a unique topic not listed
}

/*
	adjustQuestionNumber organizes the question number in the quiz records if topic is the same and the questionNumber is less than the question
	number in that same topic in quiz records
		@ param topic - the topic to be looked in the records
		@ param records quiz - struct array of the quiz records
		@ param questionNumber - the question number limit to be adjusted in the records
*/
void adjustQuestionNumber(char topic[21], records quiz[], int questionNumber)
{
	int i;
	for(i = 0; i < checkEmptyIndexQuiz(quiz); i++)
	{
		if(strcmp(topic, quiz[i].topic) == 0 && questionNumber < quiz[i].number)
		{
			quiz[i].number = quiz[i].number - 1; // decrements the question number if greater than question number and same as topic
		}
	}
}

/*
	topicIndex returns the index of list with the topic that has the same as parameter choice
	@ param choice - a string containing the topic to be checked in list
	@ param topics list - a struct array contaning the list of unique topics and amount of questions it has
*/
int topicIndex(char choice[], topics list[])
{
	int index,i;
	
	for(i = 0; i < checkEmptyIndexList(list);i++)
	{
		if(strcmp(list[i].genre,choice) == 0)
		{
			return i; 
		}
	}
	
	return i;
}
 
/*
	editRecord displays all the unique topics after choosing, displays the list of questions in the chosen topic along with the question number,
	after choosing which question to edit, asks the user which information to edit, after succesful edit, proceeds to go back to main menu
		@ param password - string of the correct password
		@ param records quiz - struct array of the quiz records
*/
void editRecord(char password[], records quiz[])
{
	topics list[MAX_RECORDS];
	records temp; // temporary holder for things to editint i,j,k,l; //looping variables
	
	int i,j,k,l; //looping variables
	int number,edit,latest = -1; // number - chosen question number, edit - holds a choice of what to edit, latest - latest question number of the topic
	int questionNumber; // holds the question number for the edited topic
	int n = organizeTopics(list, quiz);
	
	char c; // used for removing the \n in scanf
	char topicTemp[21]; //holder for previous topic before editing
	char choice[21]; // choice of topic user would like to edit
	
	printf("Choose a topic you would like to edit here\n");
	for(i = 0; i < checkEmptyIndexList(list); i++) // displays the list of unique topics
	{
		printf("%s (%d)\n",list[i].genre, list[i].amount); 
	}
	scanf("%c", &c);
	fgets(choice, 21,stdin);
	choice[strcspn(choice, "\n")] = '\0';
	if(checkForExistingTopic(choice, list) == 1) // checks for invalid topic
	{
		system("cls");
		scanf("%c", &c);
		printf("The topic you have input is not in the listed topic, redirecting you to the main hub...\n");
		mainInterface(password, quiz);
	}
	printf("Choose a question to edit\n");
	for(j = 0; j < checkEmptyIndexQuiz(quiz); j++) // displays the list of questions on that topic
	{
		if(strcmp(quiz[j].topic, choice) == 0)
		{
			printf("%s\n", quiz[j].question);
			printf("%d\n\n", quiz[j].number);
		}
	}
	scanf("%d", &number);
	if(number > list[topicIndex(choice, list)].amount)  // checks for invalid question number
	{
		system("cls");
		scanf("%c", &c);
		printf("The question number you have chosen is not in the listed topic, redirecting you to the main hub...\n");
		mainInterface(password, quiz);
	}
	
	if(number < list[topicIndex(choice, list)].amount)
	{
	system("cls");
	for(k = 0; k < checkEmptyIndexQuiz(quiz); k++)
	{
		if((strcmp(choice, quiz[k].topic) == 0) && (number == quiz[k].number))
		{
			printf("What would you like to edit for this question?\n(1 - topic , 2 - question , 3 - choice1 , 4 - choice2 , 5 - choice3 , 6 - answer)\n");
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
					if(topicIndex(temp.topic, list) < checkEmptyIndexList(list)) //adjusts the question number if topic is changed to an existing one
					{
						for(l = 0; l < checkEmptyIndexList(list); l++)
						{
							if(strcmp(list[l].genre, temp.topic) == 0)
							{
								latest = list[l].amount;
							}
						}
						adjustQuestionNumber(topicTemp,quiz, questionNumber);
						quiz[k].number = latest + 1;
					} 
					if(topicIndex(temp.topic, list) == checkEmptyIndexList(list))
					{
						quiz[k].number = 1;
						adjustQuestionNumber(topicTemp,quiz, questionNumber); 	
					} //sets question number to 1 if topic is unique
					system("cls");			
					printf("Topic for this question has been succesfully edited. Returning to main hub...\n");
					mainInterface(password, quiz);
					break;
				case 2:
					printf("Enter the new question: ");
					fgets(temp.question, 151,stdin);
					temp.question[strcspn(temp.question,"\n")] = '\0';
					strcpy(quiz[k].question, temp.question);
					system("cls");
					printf("Question has been succesfully edited. Returning to main hub...\n");
					mainInterface(password, quiz);
					break;
				case 3:
					printf("Enter the new choice: ");
					fgets(temp.choice1, 21,stdin);
					temp.choice1[strcspn(temp.choice1,"\n")] = '\0';
					strcpy(quiz[k].choice1, temp.choice1);
					system("cls");
					printf("Choice 1 for this question has been succesfully edited. Returning to main hub...\n");
					mainInterface(password, quiz);
					break;
				case 4:
					printf("Enter the new choice: ");
					fgets(temp.choice2, 21,stdin);
					temp.choice2[strcspn(temp.choice2,"\n")] = '\0';
					strcpy(quiz[k].choice2, temp.choice2);
					system("cls");
					printf("Choice 2 for this question has been succesfully edited. Returning to main hub...\n");
					mainInterface(password, quiz);
					break;
				case 5:
					printf("Enter the new choice: ");
					fgets(temp.choice3, 21,stdin);
					temp.choice3[strcspn(temp.choice3,"\n")] = '\0';
					strcpy(quiz[k].choice3, temp.choice3);
					system("cls");
					printf("Choice 3 for this question has been succesfully edited. Returning to main hub...\n");
					mainInterface(password, quiz);
					break;
				case 6:
					printf("Enter the new answer: ");
					fgets(temp.answer, 21,stdin);
					temp.answer[strcspn(temp.answer,"\n")] = '\0';
					strcpy(quiz[k].answer, temp.answer);
					system("cls");
					printf("Choice 1 for this question has been succesfully edited. Returning to main hub...\n");
					mainInterface(password, quiz);
					break;
				default:
					system("cls");
					printf("ERROR!!!\nchoice is not listed in the directory, returning to main hub...\n");
					mainInterface(password, quiz);
			}
		}
	}
	}
	
}

/*
	deleteRecord displays all the unique topics after choosing, displays the list of questions in the chosen topic along with the question number,
	after choosing which question to delete, asks the user which information to edit, after succesful edit, proceeds to go back to main menu
		@ param password - string of the correct password
		@ param records quiz - struct array of the quiz records
*/
void deleteRecord(char password[], records quiz[])
{
	records temp; // temporary holder for things to edit
	topics list[MAX_RECORDS];
	
	int i,j,k,l,m; //looping variables
	int number,del,confirm; // number - chosen question number, del - holds a choice of what to del, confirm - checks if the user wants to delete
	int questionNumber; // holds the question number for the edited topic
	int n = organizeTopics(list, quiz);
	
	char c;
	char topicTemp[21]; //holder for previous topic before editing
	char choice[21]; // choice of topic user would like to edit
	
	printf("Choose a topic you would like to Delete here\n");
	for(i = 0; i < checkEmptyIndexList(list); i++) //displays unique topics
	{
		printf("%s (%d)\n",list[i].genre, list[i].amount); 
	}
	scanf("%c", &c);
	fgets(choice, 21,stdin);
	choice[strcspn(choice, "\n")] = '\0';
	if(checkForExistingTopic(choice, list) == 1) // checks for invalid topic
	{
		system("cls");
		printf("The topic you have input is not in the listed topic, redirecting you to the main hub...\n");
		mainInterface(password, quiz);
	}
	printf("Choose a question to Delete\n");
	for(j = 0; j < checkEmptyIndexQuiz(quiz); j++) // displays list of questions within the topic
	{
		if(strcmp(quiz[j].topic, choice) == 0)
		{
			printf("%s\n", quiz[j].question);
			printf("%d\n\n", quiz[j].number);
		}
	}
	scanf("%d", &number);
	printf("Are you sure you want to delete question number %d (1 - yes, 2 - no)?", number);
	scanf("%d", &confirm);
	if(number > list[topicIndex(choice, list)].amount) //checks for invalid question number
	{
		system("cls");
		scanf("%c", &c);
		printf("The question number you have chosen is not in the listed topic, redirecting you to the main hub...\n");
		mainInterface(password, quiz);
	}
	
	if(confirm == 1 && number < list[topicIndex(choice, list)].amount) // deletes the record after confirming deletion
	{
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
		scanf("%c", &c);
		system("cls");
		printf("Records chosen has been succesfully deleted. Returning to main hub...\n");
		mainInterface(password, quiz);
	}
	else //returns user to main interface if deletion is not confirmed
		if(confirm == 2)
		{
			scanf("%c", &c);
			system("cls");
			printf("Deletion terminated. Returning to main hub...\n");
			mainInterface(password, quiz);
		}
}

/*
	importData first asks the user the name of the file (including the file extension) and imports all of the contents in records quiz.
	 	@ param password - string of the correct password
		@ param records quiz - struct array of the quiz records
*/
void importData(char password[], records quiz[])
{
	topics list[MAX_RECORDS];
	
	FILE *fp;
	
	char filename[51];
	char c;
	
	int num = organizeTopics(list, quiz);
	int choice = 0, i = checkEmptyIndexQuiz(quiz), j = 0, exist;
	
	printf("Enter the name of the file (including the file extension): ");
	scanf("%c", &c);
	fgets(filename, 51, stdin);
	filename[strcspn(filename,"\n")] = '\0';
	fp = fopen(filename, "r");
	if(fp == NULL) // if file doesn't exist
	{
		printf("The file cannot be found, would you like to go back or try again? (1 - go back, 2 - try again)");
		scanf("%d", &choice);
		if(choice == 1)
		{
			mainInterface(password, quiz);
		}
		if(choice == 2)
		{
			importData(password, quiz);
		}
		if(choice != 1 && choice != 2) // for invalid choice
		{
			system("cls");
			printf("chosen number is not registered as a choice, returning to  to main interface...\n");
			mainInterface(password, quiz);
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
			
			for(j = 0; j < checkEmptyIndexList(list); j++)
			{
				if(strcmp(quiz[i].topic, list[j].genre) == 0 && (quiz[i].number <= list[j].amount))
				{
						quiz[i].number = list[j].amount + 1;
						list[j].amount = list[j].amount + 1;
						exist = 1;
				}	
			}
 
			if(exist == 0)
			{
				list[checkEmptyIndexList(list)].amount = 1;
				quiz[i].number = 1;
				strcpy(list[checkEmptyIndexList(list)].genre, quiz[i].topic);
			}
			
			i++;
			
		}while(!feof(fp) == 1);
		printf("import succesful, returning to main interface...\n");
		mainInterface(password, quiz);
	}
}

/*
	exportData first asks the user the name of the file (including the file extension) and exports all of the contents in records quiz to the file.
	 	@ param password - string of the correct password
		@ param records quiz - struct array of the quiz records
*/
void ExportData(char password[], records quiz[])
{
	FILE *fp;
	
	int i = 0;
	
	char filename[31]; //holder for filename including extension 
	char c; // for clearing the \n in scanf
	
	printf("Where should we export the Data (Include the file extension)? ");
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
	mainInterface(password, quiz);
	
}

/* 
	recordManager asks the user to choose which feature in manage data to use
		@ param password - string of the correct password
		@ param records quiz - struct array of the quiz records
*/
void recordManager(char password[], records quiz[])
{
	int choice1;
	
	char choice2;
	
	printf("Welcome to the manager data interface, which features would you like to use? \n(1 - Add, 2 - Edit, 3 - Delete, 4 - Import Data, 5 - Export Data, 6 - Go back) ");
	scanf("%d", &choice1);
	switch(choice1)
	{
		case 1:
			system("cls");
			addRecord(password, quiz);
			break;
		case 2:
			system("cls");
			if(checkEmptyIndexQuiz(quiz) == 0) //if records is empty
			{
				printf("There are no existing records to edit, please try again\n");
				recordManager(password, quiz);
			}
			else
				editRecord(password, quiz);
			break;
		case 3:
			system("cls");
			if(checkEmptyIndexQuiz(quiz) == 0) //if records is empty
			{
				printf("There are no existing records to delete, please try again\n");
				recordManager(password, quiz);
			}
			else
				deleteRecord(password, quiz);
			break;
		case 4:
			system("cls");
			importData(password, quiz);
			break;
		case 5:
			system("cls");
			if(checkEmptyIndexQuiz(quiz) == 0) //if records is empty
			{
				printf("There are no existing records to Export, please try again\n");
				recordManager(password, quiz);
			}
			else
				ExportData(password, quiz);
			break;
		case 6:
			system("cls");
			mainInterface(password,quiz);
			break;
		default:
			choice2 = '\0'; //for invalid inputs
			do{
				printf("Choice of feature is not listed in the directory\n");
				printf("Would you like to return to the interface or try again? (1 - try again, 2 - return interface) ");
				scanf("%c", &choice2);
				scanf("%c", &choice2);
				switch(choice2)
				{
					case '1':
						system("cls");
						recordManager(password, quiz);
						break;
					case '2':
						system("cls");
						mainInterface(password, quiz);
						break;
					default:
						choice2 = '\0';			
				}
			}while(choice2 == '\0');
			break;
	}
}

/* 
	displayScore accesses the score.txt file and collects the scores, arranges and displays the score in ranking form and return the order and 
	put inside the score.txt file
		@ param password - string of the correct password
		@ param records quiz - struct array of the quiz records
*/
void displayScore(char password[], records quiz[])
{
	scores playerInfo[MAX_RECORDS];
		
	FILE *fp;
	FILE *fp2;
	
	char c;
	
	int i = 0,j = 0,k = 0;
	
	fp = fopen("scores.txt", "r");
	if(fp != NULL)
	{
		printf("Rankings:\n\n");
		do{
			fscanf(fp, "%s\n", playerInfo[i].Name);
			fscanf(fp, "%d\n\n", &playerInfo[i].score);
			i++;
		}while(!feof(fp) == 1); 
		arrangeRanking(playerInfo, i); //arranges the players according to their rankings
	}
	fclose(fp);
	
	for(j = 0; j < i; j++) //displays the rankings of the player in list
	{
		printf("%d %s %d\n", playerInfo[j].rowNum, playerInfo[j].Name, playerInfo[j].score);
	}
	
	fp2 = fopen("scores.txt", "w");
	for(k = 0; k < i; k++)
	{
		fprintf(fp2,"%s\n%d\n\n",playerInfo[k].Name, playerInfo[k].score); // overwrites the order in the .txt file according to the rankings
	}
	fclose(fp2);
	printf("\nPress enter to return to Main Hub ");
	scanf("%c", &c);
	scanf("%c", &c);
	switch(c)
	{
		default:
			system("cls");
			mainInterface(password, quiz);
			break;
	}
}

/* 
	organizeTopics organizes the contents of parameter list according to the unique topics and number of questions existing in the records
	and returns the number of unique topics in the parameter list
		@ param topics list - array struct contaning the list of unique topics and amount of questions the topic has
		@ param records quiz - struct array of the quiz records
*/
int organizeTopics(topics list[], records quiz[])
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
		if(checkForExistingTopic(quiz[i].topic, list) == 1)
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

/*
	checkEmptyIndexList checks the list parameter which index in the array does not have a topic and returns the indexto the user
		@ param topics list - array struct contaning the list of unique topics and amount of questions the topic has
*/
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

/*
	arrangeRanking is a sorting algorithm that sorts the list of players in parameter playerInfo according to the highest to lowest
		@ param scores playerInfo - array struct containing the player and its score along with its ranking
		@ param n - number of players existing in records
*/
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

/*
	playGame asks the user to enter a name and plays the quiz game, he can choose a topic and answer a random question of the chosen topic 
	infinitely until he/she chooses to end it and puts the information in scores.txt file
		@ param password - string of the correct password
		@ param records quiz - struct array of the quiz records
*/
void playGame(char password[], records quiz[])
{
	topics list[MAX_RECORDS]; // array struct for topics available and amount for each topic
	scores playerInfo;
	
	int endChoice; // checks if the input topic is listed
	int i = 0,j = 0,k,l,m = 1,o = 0; // int variables for looping
	int scoreCount = 0; // counter for the player's score
	int randomNumber, index, end = 0; // randomNumber - holder for a random number when choosing questions, index - index of the topic in struct topics, end - checks if player wants to end the game
	int n = organizeTopics(list, quiz); // organizes the list of unique topics and the amount of questions listed in the struct
	
	char choice[21]; // holder for topic choice
	char answer[31];// holder for player answer choice
	char c; //for clearing out the \n in every input
	
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
			randomNumber = ((rand() % list[index].amount) + 1);
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
		FILE *fp;
		fp = fopen("scores.txt", "a");
		if(fp != NULL)
		{
				fprintf(fp, "%s\n%d\n\n",playerInfo.Name, playerInfo.score);
		}
		fclose(fp);
		system("cls");
		printf("Thank you for playing who doesnt want to fail CCPROG\n");
		printf("Mr./Mrs. %s\nScore: %d\n", playerInfo.Name, scoreCount);
		printf("Returning you to the main hub...\n\n");
		mainInterface(password, quiz);
	
}

/*
	PlayInterface asks the user which of the features in play he/she wants to use
		@ param password - string of the correct password
		@ param records quiz - struct array of the quiz records
*/
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
			if(checkEmptyIndexQuiz(quiz) == 0) // if records is empty
			{
				printf("Error in initiating the game. Please add a record before playing\n");
				printf("You are now redirected to the play interface\n\n");
				PlayInterface(password,quiz);
			}
			else
				playGame(password, quiz);	
			break;
		case '2':
			system("cls");
			displayScore(password, quiz);
			break;
		case '3':
			system("cls");
			mainInterface(password, quiz);
			break;
		default:			//for invalid inputs
			system("cls");
			printf("Choice input is not listed in the directory, Please try again\n\n");
			PlayInterface(password,quiz);
			break;
	}
	
}

/*
	mainInterface asks the user which of the features in the main hub he/she wants to use
		@ param password - string of the correct password
		@ param records quiz - struct array of the quiz records
*/
void mainInterface(char password[],records quiz[])
{
	char result = '\0';
	
		printf("Welcome to who doesn't want to fail CCPROG2!!!\nwhich interface would you like to use? (1 - Manage Data, 2 - Play, 3 - Exit) ");
		scanf("%c", &result);
			switch(result)
			{
				case '1':
					system("cls");
					ManageStart(password, strlen(password), quiz);
				 	break;
				case '2':
					system("cls");
					PlayInterface(password,quiz);
					break;
				case '3':
					system("cls");
					printf("You are now exiting the program\n");
					printf("Thank you for playing");
					break;
				default:				// for invalid inputs
					system("cls");
					mainInterface(password, quiz);
					break;	
			}
}

int main()
{
	char password[21] = "Lance";
	records quiz[MAX_RECORDS];
	mainInterface(password, quiz);
	return 0;
}
