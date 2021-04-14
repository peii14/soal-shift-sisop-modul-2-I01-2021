#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <unistd.h>
#include <time.h>
#include <string.h>


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

void encrypt(char folder[]){
   FILE *fp;
   char txtpath[40];
   snprintf(txtpath,sizeof txtpath,"./%s/status.txt",folder);
   fp  = fopen (txtpath, "w");
   int key=4;
   char message[]="Download Success", ch;
   for(int i = 0; message[i] != '\0'; ++i){
		ch = message[i];
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + key;
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			message[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + key;
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			message[i] = ch;
		}
	}
   printf("Download Success = %s\n",message);
   for (int i = 0;i<16; i++) 
      fputc(message[i], fp);
   fclose(fp);
}

int main(){
   int createdir;
   char image[30],folder[30],imagepath[100];
   Struct timeNow;
 
   //take present time
   timeNow=getTime();

   //concate folder name
   snprintf(folder,sizeof folder,"%02d-%02d-%02d_%02d:%02d:%02d",timeNow.year,timeNow.month,timeNow.day,timeNow.hours,timeNow.minutes,timeNow.seconds);

   //owner can read, group can read, other can read
   //owner can execute, also group and other
   createdir= mkdir(folder, S_IRUSR | S_IRGRP | S_IROTH | S_IXUSR | S_IXGRP | S_IXOTH | S_IWUSR | S_IWGRP | S_IWGRP);

   // download image
   for(int i=0;i<10;i++){
      if(fork()==0){
         printf("Duar\n");
         //update present time in every loop
         timeNow=getTime();
         //image naming
         snprintf(image,sizeof image,"%02d-%02d-%02d_%02d:%02d:%02d.jpg",timeNow.year,timeNow.month,timeNow.day,timeNow.hours,timeNow.minutes,timeNow.seconds);
         snprintf(imagepath,sizeof imagepath,"./%s/%s",folder,image); 
         //blank space due to bugs on wget that are redirecting to log file afterworth
         execl("/usr/bin/wget", "wget", "-q","-O",imagepath, "https://picsum.photos/200.jpg","", NULL);
      }
      sleep(5);
   }
   encrypt(folder);
   //zip file
   char zipfile[40];
   snprintf(zipfile,sizeof zipfile,"%s.zip",folder);
   execl("/usr/bin/zip","zip","-rm",zipfile,folder,"-x","*.c",NULL);
   return 0;
}