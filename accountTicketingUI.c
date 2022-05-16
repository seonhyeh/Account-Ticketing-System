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
#include "accountTicketingUI.h"
#include "ticket.h"


void displayAcccountSummaryHeader(void)
{
	printf("\nAcct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}

void displayAccountDetailHeader(void)
{
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountSummaryRecord(const struct Account* summary)
{
	printf("%05d %-9s %5d\n", summary->num, summary->type == 'A' ? "AGENT" : "CUSTOMER", summary->demographic.birthYear);
}

void displayAccountDetailRecord(const struct Account* detail)
{
	const char* p = detail->userlogin.password;
	int i = 0;
	char password[100];
	for (; *p; p++, i++)
	{
		if ((i + 1) % 2 == 0)
		{
			password[i] = '*';
		}
		else
		{
			password[i] = *p;
		}
	}
	password[i] = 0;

	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n", detail->num, detail->type == 'A' ? "AGENT" : "CUSTOMER", detail->demographic.birthYear, detail->demographic.income, detail->demographic.country, detail->userlogin.displayName, detail->userlogin.userName, password);

}

//part4

void applicationStartup(struct AccountTicketingData* data)
{
	int index;
	do
	{
		index = menuLogin(data->accounts, data->ACCOUNT_MAX_SIZE);
		if (index != -1)
		{
			if (data->accounts[index].type == 'A')
			{
				menuAgent(data, &data->accounts[index]);
			}
			else if (data->accounts[index].type == 'C')
			{
				menuCustomer(data->tickets, data->TICKET_MAX_SIZE, &data->accounts[index]);//a2ms1
			}

			printf("\n");
		}
	} while (index != -1);

	printf("\n==============================================\n");
	printf("Account Ticketing System - Terminated\n");
	printf("==============================================\n");

}



int menuLogin(const struct Account account[], int maxNum)
{
	int selection;
	int index = -1;
	char exit;

	do
	{
		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n");
		printf("\nSelection: ");
		selection = getIntFromRange(0, 1);

		if (selection == 1)
		{
			index = loginSystem(account, maxNum);

			if (index == -1)
			{
				printf("\nERROR:  Login failed!\n");
				pauseExecution();
			}
		}
		else if (selection == 0)
		{
			printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
			exit = getCharOption("yYnN");
			if (exit == 'n' || exit == 'N')
			{
				selection = 2;
			}
		}
		if (selection != 0 && index == -1)
		{
			printf("\n");
		}
	} while (selection != 0 && index == -1);

	return index;
}


//a2ms2
int ticketNumIndex(const int ticketNum, struct Ticket* tickets, const int maxTicket)
{
	int i = 0;
	struct Ticket* ticket = NULL;
	int found = -1;
	
	for (i = 0; i < maxTicket; ++i)
	{
		ticket = &tickets[i];
		if (found == -1)
		{
			if (ticket->ticketNum != 0 && ticket->ticketNum == ticketNum)
			{
				found = i;
			}
		}
	}

	return found;
}



//a2ms2
void menuAgent(struct AccountTicketingData* data, const struct Account* loginUser) //a2ms1
{
	int selection;
	int option = 0;
	int index = 0;
	char remove;
	int accountNum = 0;
	struct Account* account;
	int i = 0;
	int accountMaxNum = 0;
	int ticketNum = 0;
	int messageCount = 0;
	int ticketCount = 0;
	

	do
	{
		printf("\nAGENT: %s (%d)\n", loginUser->userlogin.displayName, loginUser->num); //a2ms1
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf(" 1) Add a new account\n");
		printf(" 2) Modify an existing account\n");
		printf(" 3) Remove an account\n");
		printf(" 4) List accounts: summary view\n");
		printf(" 5) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		//a2ms1
		printf(" 6) List new tickets\n");
		printf(" 7) List active tickets\n");
		//a2ms3
		printf(" 8) List closed tickets\n");
		printf(" 9) Manage a ticket\n");
		printf("10) Archive closed tickets\n");
		printf("----------------------------------------------\n");
		printf("11) View archived account statistics\n");
		printf("12) View archived tickets statistics\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n");
		printf("\nSelection: ");
		selection = getIntFromRange(0, 12);
		option = selection;
		switch (option)
		{
		case 1: //a2ms1
			index = findAccountIndexByAcctNum(0, data->accounts, data->ACCOUNT_MAX_SIZE, 0);
			if (index != -1)
			{
				account = &data->accounts[index];
				accountMaxNum = 0;
				for (i = 0; i < data->ACCOUNT_MAX_SIZE; i++)
				{
					if (accountMaxNum < data->accounts[i].num)
					{
						accountMaxNum = data->accounts[i].num;
					}
				}
				account->num = accountMaxNum + 1;
				getAccount(account);
				getUserLogin(&account->userlogin);
				getDemographic(&account->demographic);
				printf("*** New account added! ***\n");
				pauseExecution();
			}
			else
			{
				printf("\nERROR: Account listing is FULL, call ITS Support!\n");
				pauseExecution();
			}
			break;
		case 2:
			printf("\nEnter the account#: ");
			accountNum = getInteger();
			index = findAccountIndexByAcctNum(accountNum, data->accounts, data->ACCOUNT_MAX_SIZE, 0);
			if (index != -1)
			{
				updateAccount(&data->accounts[index]);
			}
			else
			{
				printf("Error\n");
			}
			//printf("\n");
			break;
		case 3:
			printf("\nEnter the account#: ");
			accountNum = getInteger();
			index = findAccountIndexByAcctNum(accountNum, data->accounts, data->ACCOUNT_MAX_SIZE, 0);
			if (index != -1)
			{
				if (loginUser->num == data->accounts[index].num)
				{
					printf("\nERROR: You can't remove your own account!\n");
					pauseExecution();
				}
				else
				{
					displayAccountDetailHeader();
					displayAccountDetailRecord(&data->accounts[index]);
					printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
					remove = getCharOption("YN");

					if (remove == 'Y')
					{
						archiveAccount(&data->accounts[index]);
						archivedTickets(data->tickets, data->TICKET_MAX_SIZE, data->accounts[index].num);
						deleteTickets(data->tickets, data->TICKET_MAX_SIZE, data->accounts[index].num);
						printf("\n*** Account Removed! ***\n");
						data->accounts[index].num = 0;
					}
					else
					{
						printf("\n*** No changes made! ***\n");
					}
					pauseExecution();
				}
			}
			break;
		case 4:
			displayAllAccountSummaryRecords(data->accounts, data->ACCOUNT_MAX_SIZE);
			pauseExecution();
			break;
		case 5:
			displayAllAccountDetailRecords(data->accounts, data->ACCOUNT_MAX_SIZE);
			pauseExecution();
			break;
			//a2ms2
		case 6:
			AgentListNewTickets(data, loginUser);
			break;
			//a2ms2
		case 7:
			AgentListActiveTickets(data, loginUser);
			break;
			//a2ms3
		case 8:
			AgentListClosedTickets(data, loginUser);
			break;
		case 9:
			printf("\nEnter ticket number: ");
			ticketNum = getInteger();
			index = findTicketIndexByTicketNum(ticketNum, data->tickets, data->TICKET_MAX_SIZE, 0);
			if (index != -1)
			{
				AgentManageTicket(&data->tickets[index], loginUser);
			}
			break;
		//a2ms4
		case 10: //0409
			printf("\nAre you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			remove = getCharOption("YN");
			//index = findTicketIndexByTicketNum(ticketNum, data->tickets, data->TICKET_MAX_SIZE, 0);
			if (index != -1)
			{
				if (remove == 'Y')
				{
					//deleteTickets(data->tickets, data->TICKET_MAX_SIZE, data->accounts[index].num);
					printf("\n*** %d tickets archived ***\n", archivedTickets(data->tickets, data->TICKET_MAX_SIZE, 0));
				}
				else
				{
					printf("\n*** No changes made! ***\n");
				}
				pauseExecution();//0409
			}
			break;
		//a2ms4
		case 11:
			printf("\nThere are %d account(s) currently archived.\n", getArchivedAccountsStatistics());
			pauseExecution();
			break;
		case 12:
			ticketCount = getArchivedTicketsStatistics(&messageCount);
			printf("\nThere are %d ticket(s) and a total of %d message(s) archived.\n", ticketCount, messageCount);
			pauseExecution();
			break;
		case 0:
			printf("\nSaving session modifications...\n");
			printf("   %d account saved.\n", saveAccountData(data->accounts, data->ACCOUNT_MAX_SIZE));
			printf("   %d tickets saved.\n", saveTicketData(data->tickets, data->TICKET_MAX_SIZE));
			printf("### LOGGED OUT ###\n");
			break;
		}
	} while (selection != 0);
}



//a2ms1 //a2ms2
void menuCustomer(struct Ticket* tickets, const int maxTicket, struct Account* loginUser)
{
	int selection;
	int option = 0;

	do
	{
		printf("\nCUSTOMER: %s (%d)\n", loginUser->userlogin.displayName, loginUser->num); //a2ms1
		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");
		printf("1) View your account detail\n");
		printf("2) Create a new ticket\n");
		printf("3) Modify an active ticket\n");
		printf("4) List my tickets\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n");
		printf("\nSelection: ");
		selection = getIntFromRange(0, 4);
		option = selection;
		switch (option)
		{
		case 1:
			printf("\n");
			displayAccountDetailHeader();
			displayAccountDetailRecord(loginUser);
			pauseExecution();
			break;
			//a2ms3
		case 2:
			cusmoterCreateNewTicket(tickets, maxTicket, loginUser);
			break;
			//a2ms3
		case 3:
			customerModifyActiveTicket(tickets, maxTicket, loginUser);
			pauseExecution();
			break;
			//a2ms2
		case 4:
			CustomerListMyTickets(tickets, maxTicket, loginUser);
			break;
		//a2ms4
		case 0:
			printf("\nSaving session modifications...\n");
			printf("   %d tickets saved.\n",saveTicketData(tickets, maxTicket));
			printf("### LOGGED OUT ###\n");
			break;
		}
	} while (selection != 0);

}


int findAccountIndexByAcctNum(int accountNum, const struct Account accounts[], int maxNum, int prompt)
{
	int i;
	int found = -1;
	if (prompt)
	{
		printf("\nEnter your account#: ");
		accountNum = getInteger();
	}
	for (i = 0; i < maxNum; i++)
	{
		if (found == -1)
		{
			if (accounts[i].num == accountNum)
			{
				found = i;
			}
		}
	}

	return found;
}

void displayAllAccountSummaryRecords(const struct Account accounts[], int maxNum)
{
	int i;

	displayAcccountSummaryHeader();
	for (i = 0; i < maxNum; i++)
	{
		if (accounts[i].num > 0)
		{
			displayAccountSummaryRecord(&accounts[i]);
		}
	}
}

void displayAllAccountDetailRecords(const struct Account accounts[], int maxNum)
{
	int i;

	printf("\n");
	displayAccountDetailHeader();
	for (i = 0; i < maxNum; i++)
	{
		if (accounts[i].num > 0)
		{
			displayAccountDetailRecord(&accounts[i]);
		}
	}
}

// Pause execution until user enters the enter key
void pauseExecution(void)
{
	printf("\n<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	//putchar('\n');
}

//a2ms2
void displayTicketsHeader(void)
{
	printf("\n------ ------ ------------------------------ --------\n");
	printf("Ticket Status Subject                        Messages\n");
	printf("------ ------ ------------------------------ --------\n");
}

//a2ms2
void displayTicketSummaryRecord(const struct Ticket* ticket)
{
	printf("%06d %-6s %-30s %5d\n", ticket->ticketNum, ticket->status == 0 ? "CLOSED" : "ACTIVE", ticket->subjectLine, ticket->messageNum);
}

void displayTicketAllSummaryRecord(const struct Ticket* tickets, const int maxTicket, const int accountNum)
{
	int i = 0;
	const struct Ticket* ticket = NULL;

	for (i = 0; i < maxTicket; ++i)
	{
		ticket = &tickets[i];

		if (ticket->ticketNum != 0 && ticket->accountNum == accountNum)
		{
			displayTicketSummaryRecord(ticket);
		}
	}
	printf("------ ------ ------------------------------ --------");
}


//a2ms2
void displayTicketMessages(const struct Ticket* ticket)
{
	int i = 0;
	const struct Message* message = NULL;
	int paused = 0;

	printf("\n================================================================================\n");
	printf("%06d (%s) Re: %s\n", ticket->ticketNum, ticket->status == 0 ? "CLOSED" : "ACTIVE", ticket->subjectLine);
	printf("================================================================================");

	//a2ms3
	for (i = 0; i < ticket->messageNum; i++)
	{
		paused = 0;
		message = &ticket->message[i];
		printf("\n%s (%s):\n", message->accountType == 'A' ? "AGENT" : "CUSTOMER", message->displayName);
		printf("   %s\n", message->details);
		if ((i + 1) % 5 == 0)
		{
			pauseExecution();
			paused = 1;
		}
	}
	if (paused == 0)
	{
		pauseExecution();
	}
}

//a2ms2
void displayNewTicketHeader(void)
{
	printf("\n------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

//a2ms2
void displayNewTicketSummaryRecord(const struct Ticket* tickets, const int maxTicket)
{
	int i = 0;
	const struct Ticket* ticket = NULL;

	for (i = 0; i < maxTicket; i++)
	{
		ticket = &tickets[i];

		if (ticket->status == 1 && ticket->messageNum == 1)
		{
			printf("%06d %5d %-15s %-6s %-30s %5d\n", ticket->ticketNum, ticket->accountNum, ticket->message[0].displayName, ticket->status == 0 ? "CLOSED" : "ACTIVE", ticket->subjectLine, ticket->messageNum);
		}
	}
	printf("------ ----- --------------- ------ ------------------------------ --------");
}


//a2ms2
void displayAllActiveTickets(const struct Ticket* tickets, const int maxTicket)
{
	int i = 0;
	const struct Ticket* ticket = NULL;

	for (i = 0; i < maxTicket; ++i)
	{
		ticket = &tickets[i];

		if (ticket->ticketNum != 0 && ticket->status == 1)
		{
			printf("%06d %5d %-15s %-6s %-30s %5d\n", ticket->ticketNum, ticket->accountNum, ticket->message[0].displayName, ticket->status == 0 ? "CLOSED" : "ACTIVE", ticket->subjectLine, ticket->messageNum);

		}
	}
	printf("------ ----- --------------- ------ ------------------------------ --------");
}

