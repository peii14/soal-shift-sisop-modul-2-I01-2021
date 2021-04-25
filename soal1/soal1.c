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

void d1() {
        char *argv[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download","-O","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Photo_for_Stevany.zip",NULL};
        execv("/bin/wget", argv);
}
void d2() {
        char *argv[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","-O","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Music_for_Stevany.zip",NULL};
        execv("/bin/wget", argv);
}
void d3() {
        char *argv[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download","-O","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Film_for_Stevany.zip",NULL};
        execv("/bin/wget", argv);
}
void unz1() {
	char *argv[] = {"unzip","-q","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Photo_for_Stevany.zip","-d","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1",NULL};
	execv("/bin/unzip", argv);
}
void unz2() {
        char *argv[] = {"unzip","-q","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Music_for_Stevany.zip","-d","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1",NULL};
        execv("/bin/unzip", argv);
}
void unz3() {
        char *argv[] = {"unzip","-q","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Film_for_Stevany.zip","-d","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1",NULL};
        execv("/bin/unzip", argv);
}
void mv1() {
	char *argv[] = {"mv","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/FOTO/","Pyoto",NULL};
	execv("/bin/mv", argv);
}
void mv2() {
        char *argv[] = {"mv","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/MUSIK/","Musyik",NULL};
        execv("/bin/mv", argv);
}
void mv3() {
        char *argv[] = {"mv","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/FILM/","Fylm",NULL};
        execv("/bin/mv", argv);
}
void zip() {
	char *argv[] = {"zip","-rmq","Lopyu_Stevany","Musyik","Pyoto","Fylm",NULL};
        execv("/bin/zip",argv);
}
void rm() {
	char *argv[] = {"rm","-r","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/MUSIK","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/FOTO","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/FILM","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Foto_For_Stevany.zip","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Musik_For_Stevany.zip","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Film_For_Stevany.zip",NULL};
	execv("/bin/rm",argv);
}
void mv(char *basepath,char *destination){
	char path[1000];
	pid_t child_id;
	int status;
	struct dirent *dp;
	DIR *dir = opendir(basepath);
	if(!dir){
		return;
	}
	while((dp = readdir(dir)) != NULL){
		if(strcmp(dp->d_name,".") != 0 && strcmp(dp->d_name,"..") !=0){
			strcpy(path,basepath);
			strcat(path,"/");
			strcat(path,dp->d_name);
			child_id = fork();
			if(child_id < 0){
				exit(EXIT_FAILURE);
			}
			if(child_id == 0){
				char *argv[]= {"mv",path,destination,NULL};
				execv("/bin/mv",argv);
			}
		}
	}
	closedir(dir);
}
void mkd() {
	char *mkd[] = {"mkdir","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Pyoto","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Musyik","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Fylm",NULL};
	execv("/bin/mkdir",mkd);
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
	while(1){
		time_t t = time (NULL);
		struct tm *tmp = localtime(&t);
		if(tmp->tm_mon+1 == 4 && tmp->tm_mday == 9 && tmp->tm_hour == 16 && tmp->tm_min == 22 && tmp->tm_sec == 0){
			int status;
			pid_t child_id1 = fork();
			if(child_id1 < 0) exit(EXIT_FAILURE);
			if(child_id1 == 0){
				char *argv[] = {"mkdir","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Musyik","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Fylm","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Pyoto",NULL};
				execv("/bin/mkdir",argv);
			}
			else{
				while ((wait(&status)) > 0);
				pid_t child_id2 = fork();
				if(child_id2 < 0) exit(EXIT_FAILURE);
				if(child_id2 == 0){
					pid_t child_id3 = fork();
					if(child_id3 < 0) exit(EXIT_FAILURE);
					if(child_id3 == 0){
						char *argv[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","-O","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1//Musik_For_Stevany.zip",NULL};
						execv("/bin/wget",argv);
					}
					else{
						while((wait(&status)) > 0);
						char *argv[] = {"unzip","-q","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Musik_For_Stevany.zip","-d","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1",NULL};
						execv("/bin/unzip",argv);
					}
				}
				else{
					while((wait(&status)) > 0);
					pid_t child_id4 = fork();
					if(child_id4 < 0) exit(EXIT_FAILURE);
					if(child_id4 == 0){
						pid_t child_id5 = fork();
						if(child_id5 < 0) exit(EXIT_FAILURE);
						if(child_id5 == 0){
							char *argv[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download","-O","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Foto_For_Stevany.zip",NULL};
							execv("/bin/wget",argv);
						}
						else{
							while ((wait(&status)) > 0);
							char *argv[] = {"unzip","-q","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Foto_For_Stevany.zip","-d","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1",NULL};
							execv("/bin/unzip",argv);
						}
					}
					else{
						while ((wait(&status)) > 0);
						pid_t child_id6 = fork();
						if(child_id6 < 0) exit(EXIT_FAILURE);
						if(child_id6 == 0){
							pid_t child_id6 = fork();
							if(child_id6 < 0) exit(EXIT_FAILURE);
							if(child_id6 == 0){
								char *argv[] = {"wget","-q","--no-check-certificate","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download","-O","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Film_For_Stevany.zip",NULL};
								execv("/bin/wget",argv);
							}
							else{
								while((wait(&status)) > 0);
								char *argv[] = {"unzip","-q","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Film_For_Stevany.zip","-d","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/",NULL};
								execv("/bin/unzip",argv);
							}
						}
						else{
							while((wait(&status)) > 0);
							pid_t child_id7 = fork();
							if(child_id7 < 0) exit(EXIT_FAILURE);
							if(child_id7 == 0){
								pid_t child_id8 = fork();
								if(child_id8 < 0) exit(EXIT_FAILURE);
								if(child_id8 == 0){
									mv("/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/MUSIK","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Musyik");
									_exit(1);
								}
								else{
									while((wait(&status)) > 0);
									pid_t child_id9 = fork();
									if(child_id9 < 0) exit(EXIT_FAILURE);
									if(child_id9 == 0){
										mv("/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/FOTO","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Pyoto");
										_exit(1);
									}
									else{
										while((wait(&status)) > 0);
										mv("/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/FILM","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1//Fylm");
										_exit(1);
									}
								}
							}
						}
					}
				}
			}
		}
		else if (tmp->tm_mon+1 == 4 && tmp->tm_mday == 9 && tmp->tm_hour == 22 && tmp->tm_min == 22 && tmp->tm_sec == 0){
			int status2;
			pid_t child_id10 = fork();
			if(child_id10 < 0) exit(EXIT_FAILURE);
			if(child_id10 == 0){
				char *argv[] = {"zip","-rmq","Lopyu_Stevany","Musyik","Pyoto","Fylm",NULL};
				execv("/bin/zip",argv);
			}
			else{
				while((wait(&status2)) > 0);
				char *argv[] = {"rm","-r","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/MUSIK","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/FOTO","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/FILM","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Foto_For_Stevany.zip","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Musik_For_Stevany.zip","/home/ascarya/sisop/soal-shift-sisop-modul-2-I01-2021/soal1/Film_For_Stevany.zip",NULL};
				execv("/bin/rm",argv);
			}
		}
		sleep(1);
	}
}
