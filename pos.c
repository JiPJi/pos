#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int balance = 1234000;
void calcearnings(time_t*); //(22) end time - start time


int main()
{
	// Try login
	system("./LOGIN");

	time_t startTime = time(NULL);
	struct tm sTm = *localtime(&startTime);
	
	//printf("Current balance: %d\n", balance);

	system("./STOREMANAGER");


	calcEarnings(startTime);

	return 0;
}

void calcEarnings(time_t startTime)
{
	struct tm sTm = *localtime(&startTime);

	time_t endTime = time(NULL);
	struct tm eTm = *localtime(&endTime);
	
	// calculating time for today's work
	int workMin = ((sTm.tm_hour - eTm.tm_hour) * 60) + (sTm.tm_min - eTm_min);

	// print current time, how many times he/she worked
	// and earnings for today
	printf("Now: %d-%d-%d %d-%d-%d\n", etm.tm_year, etm.tm_mon, etm.tm_mday, 
			etm.tm_hour, etm.tm_min, etm.tm_sec);	
	printf("Work is ended!\n");
	printf("Today's work: %d min.\n", workMin);
	printf("Today's earning: %d won.\n", workMin * 9200);

}
