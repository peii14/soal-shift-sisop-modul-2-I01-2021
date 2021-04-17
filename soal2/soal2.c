#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>


int main () {

  pid_t child_id, child1, child2, child3, child4, child5;
  char foldername[100], temp[100], filename[100];
  int status;

  child_id = fork();

  if(child_id == 0)
  {
    if(child1 = fork() == 0)
    {
      char *argvmk[] = {"mkdir", "-p", "/home/damdum/modul2/petshop", NULL};
      execv("/bin/mkdir",argvmk);
    }
    else
    {
      while((wait(&status)) > 0);
      int status1;
      if(child2 = fork() ==0)
      {
        execl("/usr/bin/unzip","unzip","pets", "-d","/home/damdum/modul2/petshop",NULL);
      }
      else
      {
        while((wait(&status1)) > 0);
        if(child3 = fork() == 0)
        {
          execl("/usr/bin/rm","rm","-rf", "/home/damdum/modul2/petshop/apex_cheats", "/home/damdum/modul2/petshop/unimportant_files", "/home/damdum/modul2/petshop/musics",NULL);
        }

        sleep(1);
        if(child3 = fork() == 0)
        {
          DIR *type_directory;
          struct dirent *file_directory;
          type_directory = opendir("/home/damdum/modul2/petshop");

          while((file_directory = readdir(type_directory)) != NULL)
          {
            if ( !strcmp( file_directory -> d_name, "."  )) continue;
            if ( !strcmp( file_directory -> d_name, ".." )) continue;

            strcpy(foldername, "/home/damdum/modul2/petshop/");
            strcat(foldername, strtok(file_directory -> d_name, ";"));
            if(child4 = fork() == 0)
            {
              char *argv[] = {"mkdir", "-p", foldername, NULL};
              execv("/bin/mkdir", argv);
            }

            if(child5 = fork() == 0)
            {
              char *args[] = {"mv", file_directory->d_name, foldername, NULL};
              execv("/bin/mv", args);
            }

          }
        }
      }
    }
  }





  return 0;
}