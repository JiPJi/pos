#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h> //terminal os header file for get password
#include <unistd.h>

void getidpw(User*); //get id and password
bool isright(char[],char[]) //check user entered right id and password
void userinfoprint() // print userinfo
bool isworker() // get user info and check user is worker
				
struct User{
	char userid[20]; // user id
	char userpw[20]; //user password
};	

int main()
{
	struct User user = {'0', '0'}; // initailize
	User *ptr_user = &user;
	
	getidpw(ptr_userid, ptr_userpw);

	return 0;
}

void getidpw(User *ptr) // 나중에 입력설정 변경필요(비밀번호가 *로 표시되게)
{
	printf("ID: "); fgets(ptr->userid, sizeof(ptr->userid), stdin);
	printf("Password: "); fgets(ptr->userpw, sizeof(ptr->userpw), stdin);
}

