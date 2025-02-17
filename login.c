#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h> //terminal os header file for get password
#include <unistd.h>
#include <time.h>

struct User{
	char userid[20]; // user id
	char userpw[20]; //user password
};	

void getidpw(struct User*); //get id and password
bool isright(struct User*, struct User*); //check user entered right id and password
void printUserInfo(struct User*); // print userinfo
		
int main()
{
	struct User user_check = {"jihyun", "1234"}; // initialize
	struct User *ptr_userck = &user_check;

	struct User user1 = {"/0", '0'};
	struct User *ptr_user = &user1;
	

	// get id&pw until enter right id&pw
	while(isright(ptr_userck, ptr_user))
	{
		getidpw(ptr_user);
	
	}

	// is entered right one, print user information
	// and save starting time
	printUserInfo(ptr_user);
	
	return 0;
}

// get id and password
void getidpw(struct User *ptr) // 나중에 입력설정 변경필요(비밀번호가 *로 표시되게)
{
	printf("ID: "); fgets(ptr->userid, sizeof(ptr->userid), stdin);
	printf("Password: "); fgets(ptr->userpw, sizeof(ptr->userpw), stdin);
}

//check user entered right id and password
bool isright(struct User *ptr_ch, struct User *ptr)
{
	// remove blank space
	int idlen = strlen(ptr->userid);
	ptr->userid[idlen - 1] = 0;
	int pwlen = strlen(ptr->userpw);
	ptr->userpw[pwlen - 1] = 0;	
	
	// check user id & pw
	if(!strcmp(ptr_ch->userid, ptr->userid) && !strcmp(ptr_ch->userpw, ptr->userpw))
	{
		return false;
	}
	else return true;
	
}

 // print userinfo
void printUserInfo(struct User *user)
{
	time_t now = time(NULL);
	struct tm tm = *localtime(&now);

	printf("Hello, %s\n", user->userid);
	printf("Start from: %d-%d-%d %d-%d-%d\n",
		  tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
		tm.tm_hour, tm.tm_min, tm.tm_sec);	  
}


