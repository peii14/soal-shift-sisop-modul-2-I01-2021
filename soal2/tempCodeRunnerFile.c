_id;
  int status;

  child_id = fork();
  if(child_id == 0)
  {
    if(fork()==0)
    {
      char *argvmk[] = {"mkdir", "-p", "/home/damdum/modul2/petshop","/home/damdum/modul2/petshop/cat","/home/damdum/modul2/petshop/turtle", NULL};
      execv("/bin/mkdir",argvmk);
    }
    // if(fork() == 0)
    // {
    //   char *argvmk[] = {"mkdir", "-p", , NULL};
    //   execv("/bin/mkdir",argvmk);
    // }
    if(fork()==0)
    execl("/usr/bin/unzip","unzip","pets", "-d","/home/damdum/modul2/petshop",NULL);

    while((wait(&status)) > 0);
    if(chdir("/home/damdum/modul2/petshop") == 0)
    {
      execl("/usr/bin/rm","rm","-rf", "/home/damdum/modul2/petshop/apex_cheats", "/home/damdum/modul2/petshop/unimportant_files", "/home/damdum/modul2/petshop/musics",NULL);
    }
  }