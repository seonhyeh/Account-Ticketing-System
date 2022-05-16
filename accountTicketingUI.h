// ============================================================================
//  Assignment: 2 
//  Milestone : 4
//  Student Name  : Seonhye Hyeon
//  Student ID    : 125635193
//  Student Email : shyeon@myseneca.ca
//  Course Section: IPC144ZAA
// ============================================================================

#ifndef ACCOUNT_TICKETING_UI_
#define ACCOUNT_TICKETING_UI_
#include "account.h"
#include "ticket.h"
#include "commonHelpers.h"
//#define ACCOUNT_MAX_SIZE 15//0409

//a2ms1
struct AccountTicketingData
{
	struct Account* accounts; // array of accounts
	const int ACCOUNT_MAX_SIZE;// maximum elements for account array
	struct Ticket* tickets; // array of tickets
	const int TICKET_MAX_SIZE; // maximum elements for ticket array
};

void displayAcccountSummaryHeader(void);
void displayAccountDetailHeader(void);
void displayAccountSummaryRecord(const struct Account*);
void displayAccountDetailRecord(const struct Account*);

//part4
void applicationStartup(struct AccountTicketingData*);
int menuLogin(const struct Account[], int);
void menuAgent(struct AccountTicketingData*, const struct Account*);
int findAccountIndexByAcctNum(int, const struct Account[], int, int);
void displayAllAccountSummaryRecords(const struct Account[], int);
//
void displayAllAccountDetailRecords(const struct Account[], int);
// Pause execution until user enters the enter key
void pauseExecution(void);

//a2ms1
void menuCustomer(struct Ticket*, const int, struct Account*);

//a2ms2
void displayTicketsHeader(void);
void displayTicketSummaryRecord(const struct Ticket*);
void displayTicketAllSummaryRecord(const struct Ticket*, const int, const int);
void displayTicketMessages(const struct Ticket*);
void displayNewTicketHeader(void);
void displayNewTicketSummaryRecord(const struct Ticket*, const int);
void displayAllActiveTickets(const struct Ticket*, const int);
int ticketNumIndex(const int, struct Ticket*, const int);





#endif // !ACCOUNT_TICKETING_UI_


