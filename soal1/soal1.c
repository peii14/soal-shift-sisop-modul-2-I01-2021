#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>
#include <dirent.h>

int status;

void d1() {
        char *wget[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download","-O","Photo_for_Stevany.zip",NULL};
        execv("/bin/wget", wget);
}
void d2() {
        char *wget2[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","-O","Music_for_Stevany.zip",NULL};
        execv("/bin/wget", wget2);
}
void d3() {
        char *wget3[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download","-O","Film_for_Stevany.zip",NULL};
        execv("/bin/wget", wget3);
}
void unz1() {
	char *unzip[] = {"unzip","-q","Photo_for_Stevany.zip","-d","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1",NULL};
	execv("/bin/unzip", unzip);
}
void unz2() {
        char *unzip2[] = {"unzip","-q","Music_for_Stevany.zip","-d","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1",NULL};
        execv("/bin/unzip", unzip2);
}
void unz3() {
        char *unzip3[] = {"unzip","-q","Film_for_Stevany.zip","-d","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1",NULL};
        execv("/bin/unzip", unzip3);
}
void mv1() {
	char *mv[] = {"mv","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/FOTO/","Pyoto",NULL};
	execv("/bin/mv", mv);
}
void mv2() {
        char *mv2[] = {"mv","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/MUSIK/","Musyik",NULL};
        execv("/bin/mv", mv2);
}
void mv3() {
        char *mv3[] = {"mv","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/FILM/","Fylm",NULL};
        execv("/bin/mv", mv3);
}
void zip() {
	char *zip[] = {"zip","-r","Lopyu_Stevany.zip","Pyoto","Musyik","Fylm",NULL};
	execv("/bin/zip", zip);
}
void rm() {
	char *rm[] = {"rm","-r","Fylm","Musyik","Pyoto","Photo_for_Stevany.zip","Music_for_Stevany.zip","Film_for_Stevany.zip",NULL};
	execv("/bin/rm", rm);
}

int main() {
	pid_t pid,sid;
	pid = fork();
	if(pid < 0){
		exit(EXIT_FAILURE);
	}
	if(pid > 0){
		exit(EXIT_SUCCESS);
	}
	umask(0);
	sid = setsid();
	if(sid < 0){
		exit(EXIT_FAILURE);
	}
	if((chdir("/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1")) < 0){
		exit(EXIT_FAILURE);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while(1) {
		time_t t = time (NULL);
		struct tm *tmp = localtime(&t);
		if(tmp->tm_mon+1 == 4 && tmp->tm_mday == 9 && tmp->tm_hour == 16 && tmp->tm_min == 22 && tmp->tm_sec == 0){
		        pid_t child_id = fork();
		        if (child_id < 0) exit(EXIT_FAILURE);
		        if (child_id == 0) d1();
		        else {
		                while((wait(&status))>0);
		                pid_t child_id2 = fork();
		                if (child_id2 < 0) exit(EXIT_FAILURE);
		                if (child_id2 == 0) d2();
		                else {
		                        while((wait(&status))>0);
		                        pid_t child_id3 = fork();
		                        if (child_id3 < 0) exit(EXIT_FAILURE);
		                        if (child_id3 == 0) d3();
		                        else {
		                                while((wait(&status))>0);
		                                pid_t child_id4 = fork();
		                                if (child_id4 < 0) exit(EXIT_FAILURE);
		                                if (child_id4 == 0) unz1();
		                                else {
		                                        while((wait(&status))>0);
		                                        pid_t child_id5 = fork();
		                                        if (child_id5 < 0) exit(EXIT_FAILURE);
		                                        if (child_id5 == 0) unz2();
		                                        else {
		                                                while((wait(&status))>0);
		                                                pid_t child_id6 = fork();
		                                                if (child_id6 < 0) exit(EXIT_FAILURE);
		                                                if (child_id6 == 0) unz3();
		                                                else {
		                                                        while((wait(&status))>0);
		                                                        pid_t child_id7 = fork();
		                                                        if (child_id7 < 0) exit(EXIT_FAILURE);
		                                                        if (child_id7 == 0) mv1();
		                                                        else {
		                                                                while((wait(&status))>0);
		                                                                pid_t child_id8 = fork();
		                                                                if (child_id8 < 0) exit(EXIT_FAILURE);
		                                                                if (child_id8 == 0) mv2();
		                                                                else {
		                                                                        while((wait(&status))>0);
		                                                                        pid_t child_id9 = fork();
		                                                                        if (child_id9 < 0) exit(EXIT_FAILURE);
		                                                                        if (child_id9 == 0) mv3();
		                                                                        else {
		                                                                        	while((wait(&status))>0);
		                                                                        	pid_t child_id10 = fork();
		       	                                                                	if (child_id10 < 0) exit(EXIT_FAILURE);
		                                                                        	if (child_id10 == 0) zip();
		    	                                                                  	else {
			                                                                              	while((wait(&status))>0);
													rm();
		                                                                        	}
		                                                                        }
		                                                                }
		                                                        }
		                                                }
		                                        }
		                                }
		                        }
		                }
		        }
		}
		sleep(1);
	}
}
