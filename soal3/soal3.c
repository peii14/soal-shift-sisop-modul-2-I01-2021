#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <unistd.h>
#include <time.h>

// run with gcc -o soal soal3.c -lcurl
struct waktu{
   int hours, minutes, seconds, day, month, year;
};

typedef struct waktu Struct;
Struct getTime(){
   //setup time
   time_t now;
   time(&now);
   struct tm *local = localtime(&now);
   
   Struct n;
   
   n.day = local->tm_mday;
   //month start form 0 to 11           
   n.month = local->tm_mon + 1;
   // year start from 1900      
   n.year = local->tm_year + 1900;  
   n.hours = local->tm_hour;          
   n.minutes = local->tm_min;        
   n.seconds = local->tm_sec; 
   
   return n;

};

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(){
   int createdir;
   char image[30];
   Struct timeNow;
   //take present time
   timeNow=getTime();

   //concate folder name
   char folder[30];
   snprintf(folder,30,"./%02d-%02d-%02d_%02d:%02d:%02d",timeNow.year,timeNow.month,timeNow.day,timeNow.hours,timeNow.minutes,timeNow.seconds);

   //owner can read, group can read, other can read
   //owner can execute, also group and other
   createdir= mkdir(folder, S_IRUSR | S_IRGRP | S_IROTH | S_IXUSR | S_IXGRP | S_IXOTH);
   
   //download image
   for(int i=0;i<10;i++){
      if(fork()==0){
         printf("Duar\n");
         //update present time in every loop
         timeNow=getTime();
         //image naming
         snprintf(image,30,"%02d-%02d-%02d_%02d:%02d:%02d.jpg",timeNow.year,timeNow.month,timeNow.day,timeNow.hours,timeNow.minutes,timeNow.seconds);
         execl("/usr/bin/wget", "wget", "-O",image, "https://picsum.photos/200.jpg", NULL);
      }
      sleep(5);
   }
   return 0;
}