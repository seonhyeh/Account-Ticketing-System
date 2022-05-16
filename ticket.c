//============================================================================
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
#include <string.h>
#include "commonHelpers.h"
#include "account.h"
#include "accountTicketingUI.h"
#include "ticket.h"


//a2ms3
int findTicketIndexByTicketNum(int ticketNum, const struct Ticket tickets[], int maxNum, int prompt)
{
	int i;
	int found = -1;

	if (prompt)
	{
		printf("\nEnter ticket number: ");
		ticketNum = getInteger();
	}
	for (i = 0; i < maxNum; i++)
	{
		if (found == -1)
		{
			if (tickets[i].ticketNum == ticketNum)
			{
				found = i;
			}
		}
	}
	return found;
}

//a2ms2
int isUserTicket(const int ticketNum, struct Ticket* tickets, const int maxTicket, int accountNum)
{
	int i = 0;
	struct Ticket* ticket = NULL;
	int found = -1;

	for (i = 0; i < maxTicket; ++i)
	{
		ticket = &tickets[i];
		if (found == -1)
		{
			if (ticket->ticketNum != 0 && ticket->ticketNum == ticketNum && ticket->accountNum == accountNum)
			{
				found = i;
			}
		}
	}
	return found;
}

//a2ms3
void displayAllClosedTickets(const struct Ticket* tickets, const int maxTicket)
{
	int i = 0;
	const struct Ticket* ticket = NULL;

	for (i = 0; i < maxTicket; ++i)
	{
		ticket = &tickets[i];

		if (ticket->ticketNum != 0 && ticket->status == 0)
		{
			printf("%06d %5d %-15s %-6s %-30s %5d\n", ticket->ticketNum, ticket->accountNum, ticket->message[0].displayName, ticket->status == 0 ? "CLOSED" : "ACTIVE", ticket->subjectLine, ticket->messageNum);

		}
	}
	printf("------ ----- --------------- ------ ------------------------------ --------");
}


//a2ms3
void deleteTickets(struct Ticket tickets[], const int maxTicket, const int accountNum)
{
	struct Ticket* ticket;
	int i = 0;

	for (i = 0; i < maxTicket; ++i)
	{
		ticket = &tickets[i];
		if (ticket->accountNum == accountNum)
		{
			ticket->ticketNum = 0;
		}
	}
}


/*Customer*/

//a2ms3-option2
void cusmoterCreateNewTicket(struct Ticket* tickets, const int maxTicket, const struct Account* account)
{
	int index = 0;
	struct Ticket* ticket;
	int ticketMaxNum = 0;
	int i = 0;

	index = findTicketIndexByTicketNum(0, tickets, maxTicket, 0);
	if (index != -1)
	{
		ticket = &tickets[index];
		ticketMaxNum = 0;
		for (i = 0; i < maxTicket; i++)
		{
			if (ticketMaxNum < tickets[i].ticketNum)
			{
				ticketMaxNum = tickets[i].ticketNum;
			}
		}
		ticket->ticketNum = ticketMaxNum + 1;
		ticket->accountNum = account->num;
		ticket->status = 1;
		ticket->messageNum = 1;
		ticket->message[0].accountType = 'C';
		strcpy(ticket->message[0].displayName, account->userlogin.displayName);
		printf("\nNew Ticket (Ticket#:%06d)\n", ticket->ticketNum);
		printf("----------------------------------------\n");
		printf("Enter the ticket SUBJECT (30 chars. maximum): ");
		getCString(ticket->subjectLine, 1, 30);
		printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
		//printf("submit:\n");
		getCString(ticket->message[0].details, 1, 150);
		printf("\n*** New ticket created! ***\n");
		pauseExecution();
	}
	else
	{
		printf("\nERROR: Ticket listing is FULL, call ITS Support!\n");
		pauseExecution();
	}
}

//a2ms3 - customer opion3
void customerModifyActiveTicket(struct Ticket tickets[], const int maxTicket, const struct Account* account)
{
	int ticketNum = 0;
	int selection = 0;
	int option = 0;
	char exit;
	char exitmessage;
	int flag = 0;
	int index = 0;
	struct Ticket* ticket;

	printf("\nEnter ticket number: ");
	ticketNum = getInteger();
	index = findTicketIndexByTicketNum(ticketNum, tickets, maxTicket, 0);

	if (index != -1)
	{
		ticket = &tickets[index];
		if (ticket->status == 0)
		{
			printf("\nERROR: Ticket is closed - changes are not permitted.\n");
		}
		else if (account->num != tickets[index].accountNum)
		{
			printf("\nERROR: Invalid ticket number - you may only modify your own ticket.\n");
		}
		else
		{
			do
			{
				printf("\n----------------------------------------\n");
				printf("Ticket %06d - Update Options\n", ticketNum);
				printf("----------------------------------------\n");
				printf("Status  : %s\n", ticket->status == 0 ? "CLOSED" : "ACTIVE");
				printf("Subject : %s\n", ticket->subjectLine);
				printf("----------------------------------------\n");
				printf("1) Modify the subject\n");
				printf("2) Add a message\n");
				printf("3) Close ticket\n");
				printf("0) Done\n");
				printf("Selection: ");
				selection = getIntFromRange(0, 3);
				option = selection;
				switch (option)
				{
				case 1:
					printf("\nEnter the revised ticket SUBJECT (30 chars. maximum): ");
					getCString(ticket->subjectLine, 1, 30);
					break;
				case 2:
					if (ticket->messageNum < 20) //message[20]
					{
						printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
						//printf("submit:\n");
						getCString(ticket->message[ticket->messageNum].details, 1, 150);
						strcpy(ticket->message[ticket->messageNum].displayName, account->userlogin.displayName);
						ticket->message[ticket->messageNum].accountType = account->type;
						ticket->messageNum++;
					}
					else
					{
						printf("\nERROR: Message limit has been reached, call ITS Support!\n");
					}
					break;
				case 3:
					printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
					exit = getCharOption("YN");
					if (exit == 'Y')
					{
						if (ticket->messageNum < 20)
						{
							printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
							exitmessage = getCharOption("YN");
							if (exitmessage == 'Y')
							{
								printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
								getCString(ticket->message[ticket->messageNum].details, 1, 150);
								strcpy(ticket->message[ticket->messageNum].displayName, account->userlogin.displayName);
								ticket->message[ticket->messageNum].accountType = account->type;
								ticket->messageNum++;
							}
						}
						ticket->status = 0;
						printf("\n*** Ticket closed! ***\n");
						flag = 1;
					}
					break;
				case 0:
					flag = 1;
					break;
				}

			} while (flag == 0);
		}
	}
}

//a2ms2 -Customer option4
void CustomerListMyTickets(struct Ticket* tickets, const int maxTicket, const struct Account* loginUser)
{
	int ticketNum = 0;
	int index = 0;

	do
	{
		displayTicketsHeader();
		displayTicketAllSummaryRecord(tickets, maxTicket, loginUser->num);

		printf("\n\nEnter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");
		ticketNum = getPositiveIntegerZero();

		index = isUserTicket(ticketNum, tickets, maxTicket, loginUser->num);
		if (index != -1)
		{
			displayTicketMessages(&tickets[index]);
		}
		else if (ticketNum != 0)
		{
			printf("\nERROR: Invalid ticket number - you may only access your own tickets.\n");
			pauseExecution();
		}

	} while (ticketNum != 0);

}


/*Agent*/

//a2ms2-agent option6
void AgentListNewTickets(struct AccountTicketingData* data, const struct Account* loginUser)
{
	int ticketNum = 0;
	int index = 0;

	do
	{
		displayNewTicketHeader();
		displayNewTicketSummaryRecord(data->tickets, data->TICKET_MAX_SIZE);

		printf("\n\nEnter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");
		ticketNum = getPositiveIntegerZero();

		index = ticketNumIndex(ticketNum, data->tickets, data->TICKET_MAX_SIZE);
		if (index != -1)
		{
			displayTicketMessages(&data->tickets[index]);
		}
		else if (ticketNum != 0)
		{
			printf("\nERROR: Invalid ticket number.\n");
			pauseExecution();
		}

	} while (ticketNum != 0);

}

//a2ms2- Agent option7
void AgentListActiveTickets(struct AccountTicketingData* data, const struct Account* loginUser)
{
	int ticketNum = 0;
	int index = 0;

	do
	{
		displayNewTicketHeader();
		displayAllActiveTickets(data->tickets, data->TICKET_MAX_SIZE);

		printf("\n\nEnter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");
		ticketNum = getPositiveIntegerZero();

		index = ticketNumIndex(ticketNum, data->tickets, data->TICKET_MAX_SIZE);
		if (index != -1)
		{
			displayTicketMessages(&data->tickets[index]);
		}
		else if (ticketNum != 0)
		{
			printf("\nERROR: Invalid ticket number.\n");
			pauseExecution();
		}

	} while (ticketNum != 0);
}

//a2ms3- agent option8
void AgentListClosedTickets(struct AccountTicketingData* data, const struct Account* loginUser)
{
	int ticketNum = 0;
	int index = 0;

	do
	{
		displayNewTicketHeader();
		displayAllClosedTickets(data->tickets, data->TICKET_MAX_SIZE);

		printf("\n\nEnter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");
		ticketNum = getPositiveIntegerZero();

		index = ticketNumIndex(ticketNum, data->tickets, data->TICKET_MAX_SIZE);
		if (index != -1)
		{
			displayTicketMessages(&data->tickets[index]);
		}
		else if (ticketNum != 0)
		{
			printf("\nERROR: Invalid ticket number.\n");
			pauseExecution();
		}

	} while (ticketNum != 0);
}


//a2ms3-Agent option9
void AgentManageTicket(struct Ticket* ticket, const struct Account* loginUser)
{
	int selection = 0;
	int option = 0;
	char reOpen;
	char exit;
	char exitMessage;
	int flag = 0;

	do
	{
		printf("\n----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", ticket->ticketNum);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", ticket->status == 0 ? "CLOSED" : "ACTIVE");
		printf("Subject : %s\n", ticket->subjectLine);
		printf("Acct#   : %d\n", ticket->accountNum);
		printf("Customer: %s\n", ticket->message[0].displayName);
		printf("----------------------------------------\n");
		printf("1) Add a message\n");
		printf("2) Close ticket\n");
		printf("3) Re-open ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		selection = getIntFromRange(0, 3);
		option = selection;
		switch (option)
		{
		case 1:
			if (ticket->status == 0)
			{
				printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
			}
			else if (ticket->messageNum >= 20)
			{
				printf("\nERROR: Message limit has been reached, call ITS Support!\n");
			}
			else if (ticket->messageNum < 20)
			{
				printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
				//printf("submit:\n");
				getCString(ticket->message[ticket->messageNum].details, 1, 150);
				strcpy(ticket->message[ticket->messageNum].displayName, loginUser->userlogin.displayName);
				ticket->message[ticket->messageNum].accountType = loginUser->type;//0409
				ticket->messageNum++;

                if (ticket->status == 0)
                {
	                printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
                }
			}
			break;
		case 2:
			if (ticket->status == 0)
			{
				printf("\nERROR: Ticket is already closed!\n");
			}
			else
			{
				printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				exit = getCharOption("YN");
				if (exit == 'Y')
				{
					if (ticket->messageNum < 20)
					{
						printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
						exitMessage = getCharOption("YN");
						if (exitMessage == 'Y')
						{
							printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
							getCString(ticket->message[ticket->messageNum].details, 1, 150);
							strcpy(ticket->message[ticket->messageNum].displayName, loginUser->userlogin.displayName);
							ticket->message[ticket->messageNum].accountType = loginUser->type;
							ticket->messageNum++;
						}
					}
					ticket->status = 0;
					printf("\n*** Ticket closed! ***\n");
				}
			}
			break;
		case 3:
			if (ticket->status == 0)
			{
				printf("\nAre you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				reOpen = getCharOption("YN");
				if (reOpen == 'Y')
				{
					ticket->status = 1;
					printf("\n*** Ticket re-opened! ***\n");
				}
			}
			else
			{
				printf("\nERROR: Ticket is already active!\n");
			}
			break;
		case 0:
			flag = 1;
			break;
		}
	} while (flag == 0);
}

//a2ms4
//Reads the contents of a file and stores the records into a Ticket array
int loadTickets(struct Ticket tickets[], int arrSize)
{
	int i = 0;
	char ch = 'x';
	FILE* fp = fopen("tickets.txt", "r"); //read

	if (fp != NULL)
	{
		while (i < arrSize && fscanf(fp, "%d|%d|%d|%30[^|]|%d|",
			&tickets[i].ticketNum, &tickets[i].accountNum, &tickets[i].status,
			tickets[i].subjectLine, &tickets[i].messageNum) == 5)
		{

			loadMessages(fp, tickets[i].message, tickets[i].messageNum);
			fscanf(fp, "%c", &ch);
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
void loadMessages(FILE* fp, struct Message messages[], const int maxMessage)
{
	int i = 0;

	while (i < maxMessage && fscanf(fp, "%c|%30[^|]|%150[^|]|", &messages[i].accountType,
		messages[i].displayName, messages[i].details) == 3)
	{
		i++;
	}
}

//a2ms4
int saveTicketData(const struct Ticket tickets[], int arrSize)
{
	int i;
	int count = 0;
	/*char ch = 'x';*/
	FILE* fp = fopen("tickets.txt", "w");

	if (fp != NULL)
	{
		for (i = 0; i < arrSize; i++)
		{
			if (tickets[i].ticketNum> 0)
			{
				fprintf(fp, "%d|%d|%d|%s|%d|",
					tickets[i].ticketNum, tickets[i].accountNum, tickets[i].status,
					tickets[i].subjectLine, tickets[i].messageNum);
				saveMessages(fp, tickets[i].message, tickets[i].messageNum);
				fprintf(fp, "\n");
				count++;
			}
		}
		fclose(fp);
		fp = NULL;
	}
	return count;
}


//a2ms4
void saveMessages(FILE* fp, const struct Message messages[], const int maxMessage)
{
	int i = 0;
	int count = 0;

	for (i = 0; i < maxMessage; i++)
	{
		if (maxMessage > 0)
		{
			fprintf(fp, "%c|%s|%s|", messages[i].accountType,
				messages[i].displayName, messages[i].details);
			count++;
		}
	}
}


// archived (closed) tickets. agnet-option10
int archivedTickets(struct Ticket tickets[], int arrSize, const int accountNum)
{
	int i = 0;
	int count = 0;
	FILE* fp = fopen("tickets_arc.txt", "a");

	if (fp != NULL)
	{
		for (i = 0; i < arrSize; i++)
		{
			if (tickets[i].ticketNum != 0 && (accountNum == 0 || tickets[i].accountNum == accountNum))
			{
				if (tickets[i].status == 0)
				{
					fprintf(fp, "%d|%d|%d|%s|%d|",
						tickets[i].ticketNum, tickets[i].accountNum, tickets[i].status,
						tickets[i].subjectLine, tickets[i].messageNum);
					saveMessages(fp, tickets[i].message, tickets[i].messageNum);
					fprintf(fp, "\n");
					count++;
					tickets[i].ticketNum = 0;
				}
			}
		}
		fclose(fp);
		fp = NULL;
	}
	return count;
}

//agent option12
int getArchivedTicketsStatistics(int* messageNum)
{
	int messageCount = 0;
	int ticketCount=0;
	struct Ticket ticket;
	char ch = 'x';
	FILE* fp = fopen("tickets_arc.txt", "r"); //read

	if (fp != NULL)
	{
		while (fscanf(fp, "%d|%d|%d|%30[^|]|%d|",
			&ticket.ticketNum, &ticket.accountNum, &ticket.status,
			ticket.subjectLine, &ticket.messageNum) == 5)
		{
			loadMessages(fp, ticket.message, ticket.messageNum);
			fscanf(fp, "%c", &ch);
			if (ch != '\n')
			{
				while (fgetc(fp) != '\n');
			}
			ticketCount++;
			messageCount += ticket.messageNum;
		}
		fclose(fp);
		fp = NULL;
	}
	*messageNum = messageCount;
	return ticketCount;
}











