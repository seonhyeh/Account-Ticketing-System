// ============================================================================
//  Assignment: 2 
//  Milestone : 4
//  Student Name  : Seonhye Hyeon
//  Student ID    : 125635193
//  Student Email : shyeon@myseneca.ca
//  Course Section: IPC144ZAA
//

#ifndef TICKET_H_
#define TICKET_H_

#include "account.h"
#include "accountTicketingUI.h"
struct AccountTicketingData;
struct Account;


//a2ms1
struct Message
{
	char accountType; // 'C' or 'A'
	char displayName[31];
	char details[151];
};

struct Ticket
{
	int ticketNum;
	int accountNum;
	int status;
	char subjectLine[31];
	int messageNum;
	struct Message message[20];
};

//a2ms2
void AgentListActiveTickets(struct AccountTicketingData*, const struct Account*);
int isUserTicket(const int, struct Ticket*, const int, int);
void CustomerListMyTickets(struct Ticket* , const int, const struct Account*);
void AgentListNewTickets(struct AccountTicketingData*, const struct Account* );

//a2ms3
void cusmoterCreateNewTicket(struct Ticket*, const int, const struct Account*);
void customerModifyActiveTicket(struct Ticket[], const int, const struct Account*);
int findTicketIndexByTicketNum(int , const struct Ticket[], int, int);
void AgentManageTicket(struct Ticket*, const struct Account*);
void AgentListClosedTickets(struct AccountTicketingData*, const struct Account*);
void displayAllClosedTickets(const struct Ticket*, const int);
void deleteTickets(struct Ticket[], const int, const int);

//a2ms4
int loadTickets(struct Ticket tickets[], int arrSize);
void loadMessages(FILE* fp, struct Message messages[], const int maxMessage);
int saveTicketData(const struct Ticket tickets[], int arrSize);
void saveMessages(FILE* fp, const struct Message messages[], const int maxMessage);
int archivedTickets(struct Ticket tickets[], int arrSize, const int accountNum);
int getArchivedTicketsStatistics(int* messageNum);
#endif // !TICKET_H_
