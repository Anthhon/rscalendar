#include <stdio.h>
#include <time.h>

unsigned short days_in_month(unsigned month_n){
	unsigned short days[12] = {31, 28, 31, 30, 31, 30,
				   31, 31, 30, 31, 30, 31};
	return days[month_n];
}

void print_current_calendar(){
	/* time_data should store a value like
	 * Thu May 27 20:20:01 2023 
	 * if not this should return NULL value */
	time_t time_data = time(NULL);
	if (&time_data == NULL){
		puts("ERROR: Wasn't possible to retrieve time data!");
		return;
	}
	// Stores formatted time
	struct tm tm = *localtime(&time_data);

	/* For some reason year and month
	 * are not being returned correctly
	 * so these magic numbers are needed*/
	unsigned short year = tm.tm_year + 1900;
	unsigned short day = tm.tm_mday;
	unsigned short month = tm.tm_mon + 1;
	unsigned short month_days = days_in_month(tm.tm_mon);

	// Print calendar in table format
	printf("--------%04d %02d %02d--------", year, day, month);
	for (unsigned short day = 1; day <= month_days; ++day){
		// Break line in each week 
		if (day % 7 == 1) puts("");
		printf("%02i  ", day);
	}
	puts("");

	return;
}

int main(int argc, char *argv){
	// Prompt user the current calendar if none arguments
	if (argc == 1)
		print_current_calendar();
	else
		puts("Doesn't accept arguments yet");

	return 0;
}
