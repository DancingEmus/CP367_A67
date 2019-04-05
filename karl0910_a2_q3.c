#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>


int isLeap(int year){
  if((year%4==0 && year%100!=0) || (year%400==0))
    return 1;
  else
    return -1;
}

int main(int argc, char* argv[]){
  setbuf(stdout, NULL);
  int i;

  //USER
  char* user = getlogin();
  printf("\n\nHello %s\n", user);

  //OFFSET AND PRINT CURR TIME
  time_t date = time(NULL);

  int offsetDays = 0;
  if (argc > 1){
    offsetDays = atoi(argv[1]);
    //Exit if offset > 80 years
    
    if(offsetDays > 29200 || offsetDays < -29200){
      printf("\nERROR (offset > 80 years): Exit program\n\n");
      return 0;
      
    }
    int offset = offsetDays * 86400;
    date += offset;
  }


  struct tm *date2 = localtime(&date);
  char* dateStr = asctime(date2);

  //PRINT DATE
  if (argc > 1){
    printf("Offset by %d days, the date is %s", offsetDays, dateStr);
  }
  else{
    printf("The current date is %s",dateStr);
  }


  //GET CURR MON + DAY
  int currMon = date2->tm_mon + 1;
  int currDay = date2->tm_mday;


  //INPUT
  int day, month;
  printf("Enter your day of birth (DD)\n");
  scanf("%d", &day);
  printf("Enter your month of birth (MM)\n");
  scanf("%d", &month);

  // FIX ME printf("%d %d\n",day, month);


  //BDAY
  int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int flag, days = 0;

  if (currMon == month && currDay == day){
    printf("Happy Birthday!\n\n\n");
    return 0;
  }
  else if(currMon > month || (currMon == month && currDay > day)){
    flag = -1; //Bday has past
  }
  else{
    flag = 1; //Bday still coming
  }

  //CHECK FOR LEAPS
  int currYear = date2->tm_year + 1900;
  int nextYear = currYear + 1;
  int thisLeap = 0, nextLeap = 0;//LEAPS
  //FIX ME printf("%d\n",currYear);
  if( isLeap(currYear) == 1 ){
    thisLeap = 1;
  }
  else if(isLeap(nextYear) == 1){
    nextLeap = 1;
  }


  //Calc days
  if (flag == 1){
    if (currMon == month){
      days = day - currDay;
    }
    else{
      days += (monthDays[currMon-1]  - currDay);
      for(i = currMon; i < month-1; i++){
	days += monthDays[i];
      }
      days += day;
    }

    if(thisLeap == 1 && (currMon <= 2) && month > 2){
      days++;
    }
  }
  else if (flag == -1){
    if (currMon == month){
      int diff = currDay - day;
      days = 365 - diff;
    }
    else{
      days += currDay;
      for(i = currMon - 2; i > month; i--){
	days += monthDays[i];
      }
      days +=  (monthDays[month-1] - day);

      days = 365 - days;
    }

    if (nextLeap == 1 && month > 2) {
      days++;
    }

  }


  if ( day == 29 && month == 2){
    int year = currYear;
    while (isLeap(year) != 1 ){
      days += 365;
      year++;
    }
  }


  printf("There are %d days until your birthday.\n", days);
  printf("\n\n");

  return 0;
}
