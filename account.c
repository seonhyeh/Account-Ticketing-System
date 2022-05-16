// ============================================================================
//  Assignment: 2
//  Milestone : 4
//  Student Name  : Seonhye Hyeon
//  Student ID    : 125635193
//  Student Email : shyeon@myseneca.ca
//  Course Section: IPC144ZAA
// ============================================================================

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include "commonHelpers.h"
#include "account.h"
#include <string.h>
//a2ms1
#include <ctype.h>
#include "accountTicketingUI.h"

//Receives a modifiable Account pointer argument. o Does not return anything but does return data for an Account type via the argument pointer variable
void getAccount(struct Account* accountptr)
{
	printf("\nNew Account Data (Account#:%d)\n", accountptr->num); //a2ms1 
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	accountptr->type = getCharOption("AC");
	printf("\n");
}

void passwordCondition(struct UserLogin* userptr)
{
	int i;
	int ch;
	int upperCount = 0;
	int lowerCount = 0;
	int digitCount = 0;
	int chCount = 0;
	char find[] = "!@#$%^&*";

	do
	{
		upperCount = 0;
		lowerCount = 0;
		digitCount = 0;
		chCount = 0;

		printf("Enter the password (must be 8 chars in length): ");
		getCString(userptr->password, 8, 8);

		for (i = 0; i < strlen(userptr->password); i++)
		{
			ch = userptr->password[i];
			if (isupper(ch))
			{
				upperCount++;
			}
			else if (islower(ch))
			{
				lowerCount++;
			}
			else if (isdigit(ch))
			{
				digitCount++;
			}
			else if (strchr(find, ch))
			{
				chCount++;
			}
		}
		if (upperCount != 2 || lowerCount != 2 || digitCount != 2 || chCount != 2)
		{
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");
		}
	} while (upperCount != 2 || lowerCount != 2 || digitCount != 2 || chCount != 2);

}

void getUserLogin(struct UserLogin* userptr)
{
	printf("User Login Data Input\n");
	printf("----------------------------------------\n");

	int i;
	int error = 0;

	do
	{
		error = 0;
		printf("Enter user login (10 chars max): ");
		getCString(userptr->userName, 1, 10);
		for (i = 0; i < strlen(userptr->userName); i++)
		{
			if (userptr->userName[i] == ' ' || userptr->userName[i] == '\t')
			{
				error = 1;
				printf("ERROR:  The user login must NOT contain whitespace characters.\n");
			}
		}

	} while (error);

	printf("Enter the display name (30 chars max): ");
	getCString(userptr->displayName, 1, 30);
	//a2ms1
	passwordCondition(userptr);

	printf("\n");
}


void getDemographic(struct Demographic* demoptr)
{
	int i = 0;

	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");
	printf("Enter birth year (current age must be between 18 and 110): ");
	int year = currentYear();
	demoptr->birthYear = getIntFromRange(year - 110, year - 18);
	printf("Enter the household Income: $");
	demoptr->income = getPositiveDouble();
	printf("Enter the country (30 chars max.): ");
	getCString(demoptr->country, 1, 30);
	for (i = 0; i < strlen(demoptr->country); i++)
	{
		demoptr->country[i] = toupper(demoptr->country[i]);
	}
	printf("\n");
}

//part 4
void updateAccount(struct Account* account)
{
	int selection;
	int option;
	int flag = 0;

	printf("\n");
	do
	{
		printf("Account: %d - Update Options\n", account->num);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", account->type);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 3);
		option = selection;
		switch (option)
		{
		case 0:
			flag = 1;
			//printf("\n");
			break;
		case 1:
			printf("\nEnter the account type (A=Agent | C=Customer): ");
			account->type = getCharOption("AC");
			break;
		case 2:
			updateUserLogin(&account->userlogin);
			printf("\n");
			break;
		case 3:
			updateDemographic(&account->demographic);
			printf("\n");
			break;
		}
	} while (flag == 0);
}

void updateUserLogin(struct UserLogin* user)
{
	int selection;
	int option;
	int flag = 0;

	do
	{
		printf("\nUser Login: %s - Update Options\n", user->userName);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", user->displayName);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 2);
		option = selection;

		switch (option)
		{
		case 1:
			printf("\nEnter the display name (30 chars max): ");
			getCString(user->displayName, 1, 30);
			break;

		case 2:
			printf("\n"); 
			passwordCondition(user);
			break;
		case 0:
			flag = 1;
			break;
		}
	} while (flag == 0);
}

void updateDemographic(struct Demographic* demo)
{
	int selection;
	int option;
	int flag = 0;
	int i = 0;
	do
	{
		printf("\nDemographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", demo->income);
		printf("2) Country (current value: %s)\n", demo->country);
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 2);
		option = selection;

		switch (option)
		{
		case 1:
			printf("\nEnter the household Income: $"); 
			demo->income = getPositiveDouble();
			break;
		case 2:
			printf("\nEnter the country (30 chars max.): "); 
			getCString(demo->country, 1, 30);
			for (i = 0; i < strlen(demo->country); i++)
			{
				demo->country[i] = toupper(demo->country[i]);
			}
			//printf("\n");
			break;
		case 0:
			flag = 1;
			break;
		}
	} while (flag == 0);
}

//a2ms2
int loginSystem(const struct Account* accounts, int maxNum)
{
	char userName[100] = { 0 };
	char password[100] = { 0 };
	int errorCount = 0;
	int index = 0;
	int accountNum;
	char newLine = 'x';

	do
	{
		printf("\nEnter the account#: ");
		accountNum = getInteger();
		index = findAccountIndexByAcctNum(accountNum, accounts, maxNum, 0);
		printf("User Login    : ");
		scanf("%99[^\n]%c", userName, &newLine);
		printf("Password      : ");
		scanf("%99[^\n]%c", password, &newLine);
		if (index == -1 || strcmp(userName, accounts[index].userlogin.userName) != 0 || strcmp(password, accounts[index].userlogin.password) != 0)
		{
			errorCount++;
			printf("INVALID user login/password combination! [attempts remaining:%d]\n", 3 - errorCount);
			index = -1;
		}

	} while (errorCount < 3 && index == -1);

	return index;
}

//a2ms4
//reads the contents of a file and stores the records into a Account array
int loadAccounts(struct Account accounts[], int arrSize)
{
	int i = 0;
	char ch;
	FILE* fp = fopen("accounts.txt", "r"); //read

	if (fp != NULL)
	{
		while (i < arrSize && fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%30[^\n]%c", &accounts[i].num, 
			&accounts[i].type, accounts[i].userlogin.displayName, accounts[i].userlogin.userName, 
			accounts[i].userlogin.password, &accounts[i].demographic.birthYear, 
			&accounts[i].demographic.income, accounts[i].demographic.country, &ch) == 9)
		{
			if (ch != '\n')
			{
				while (fgetc(fp) != '\n');
			}
			i++;
		}
		fclose(fp);
		fp = NULL;
	}

	return i;
}




//a2ms4
/*Returns the number of records written*/
/*
Saving session modifications...
 17 tickets saved.
### LOGGED OUT ###
*/

int saveAccountData(const struct Account accounts[], int arrSize)
{
	int i;
	int count = 0;
	FILE* fp = fopen("accounts.txt", "w");

	if (fp != NULL)
	{
		for (i = 0; i < arrSize; i++)
		{
			if (accounts[i].num > 0)
			{
				fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n", accounts[i].num,
					accounts[i].type, accounts[i].userlogin.displayName, accounts[i].userlogin.userName,
					accounts[i].userlogin.password, accounts[i].demographic.birthYear,
					accounts[i].demographic.income, accounts[i].demographic.country);
				count++;
			}	
			//fflush(fp); //manually push the update
		}
		fclose(fp);
		fp = NULL;
	}
	return count;
}


//a2ms4
//archived (removed) accounts
void archiveAccount(const struct Account* account)
{
	FILE* fp = fopen("accounts_arc.txt", "a");

	if (fp != NULL)
	{
		if (account != NULL)
		{
			fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", account->num,
				account->type, account->userlogin.displayName, account->userlogin.userName,
				account->userlogin.password, account->demographic.birthYear,
				account->demographic.income, account->demographic.country);
		}
		fclose(fp);
	}
}

int getArchivedAccountsStatistics() //0409
{
	int count = 0;
	struct Account account;
	char ch = 'x';

	FILE* fp = fopen("accounts_arc.txt", "r"); //read
	if (fp != NULL)
	{
		while (fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%30[^\n]%c", &account.num,
			&account.type, account.userlogin.displayName, account.userlogin.userName,
			account.userlogin.password, &account.demographic.birthYear,
			&account.demographic.income, account.demographic.country, &ch) == 9)
		{
			if (ch != '\n')
			{
				while (fgetc(fp) != '\n');
			}
			count++;
		}
		fclose(fp);
		fp = NULL;
	}
	return count;
}