#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(){
   int hours, minutes, seconds, day, month, year, createdir;
    // time_t is arithmetic time type
   time_t now;
   time(&now);
   struct tm *local = localtime(&now);
          
   day = local->tm_mday;
   //month start form 0 to 11           
   month = local->tm_mon + 1;
   // year start from 1900      
   year = local->tm_year + 1900;  
   //concate folder name
   hours = local->tm_hour;          
   minutes = local->tm_min;        
   seconds = local->tm_sec; 
   char folder[20];
   snprintf(folder,20,"%02d-%02d-%02d_%02d:%02d:%02d",year,month,day,hours,minutes,seconds);
   //owner can read, group can read, other can read
   //owner can execute, also group and other
   createdir= mkdir(folder, S_IRUSR | S_IRGRP | S_IROTH | S_IXUSR | S_IXGRP | S_IXOTH);
   
}