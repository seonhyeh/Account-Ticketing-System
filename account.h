// ============================================================================
//  Assignment: 2 
//  Milestone : 4
//  Student Name  : Seonhye Hyeon
//  Student ID    : 125635193
//  Student Email : shyeon@myseneca.ca
//  Course Section: IPC144ZAA
// ============================================================================

#ifndef ACCOUNT_H_
#define ACCOUNT_H_



struct Demographic
{
	int  birthYear;
	double income;
	char country[31];

};

struct UserLogin
{
	char displayName[31];
	char userName[11];
	char password[9];

};

struct Account
{
	int num;
	char type;
	struct UserLogin userlogin;
	struct Demographic demographic;
};

//part3

void getAccount(struct Account*);
void getUserLogin(struct UserLogin*);
void getDemographic(struct Demographic*);

//part4
void updateAccount(struct Account*);
void updateUserLogin(struct UserLogin*);
void updateDemographic(struct Demographic*);

//a2ms2
int loginSystem(const struct Account*, int);

//a2ms4
int loadAccounts(struct Account[], int);
int saveAccountData(const struct Account accounts[], int arrSize);
//int appenAccountData(const struct Account accounts[], int arrSize);
void archiveAccount(const struct Account* account);
int getArchivedAccountsStatistics();

#endif // !ACCOUNT_H_
