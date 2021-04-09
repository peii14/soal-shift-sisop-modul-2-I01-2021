# soal-shift-sisop-modul-2-I01-2021

2. Loba works in a famous pet shop, one day he got a zip containing lots of pets photos and he was ordered to categorize the photos of these pets. Loba finds it difficult to do his work manually, moreover there is the possibility that he will be ordered to do the same thing multiple times. You are Loba's best friend and he is asking for your help to help with his work. 

a. First, the program needs to extract the given zip into the folder “/home/[user]/modul2/petshop”. Because Loba's boss is careless, the zip may contain unimportant folders, so the program must be able to distinguish between files and folders so that it can process files that should be worked on and delete unnecessary folders.

    pid_t child, child2;
    child = fork();
    child2 = fork();
    if(child < 0) exit(0);
    if(child2 == 0)
    {
      char *arg[] = {"mkdir", "-p", "/home/damdum/modul2/petshop"};
      execv("/bin/mkdir",arg);
    }
    while(wait(&status) > 0);
    if(child == 0) 
    {
        execl("/usr/bin/unzip","unzip","pets", "-d","/home/damdum/modul2/petshop",NULL);
    }
    
    while(wait(&status) > 0);
    DIR *folder;
    struct dirent *entry;
    folder = opendir("/home/damdum/modul2/petshop");
    while((entry = readdir(folder)) != NULL) 
    {
      if((entry->d_type == DT_DIR) && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) 
      {
        pid_t child;
        child = fork();
        if(child < 0) exit(0);
        if(child == 0) 
        {
          char foldername[500];
          sprintf(foldername, "/home/damdum/modul2/petshop/%s", entry->d_name);
          char *arg[] = {"rm", "-r", foldername, NULL};
          execv("/bin/rm", arg);
        }
      }
    }

b. Pet photos need to be categorized based on the pet's species, so you will need to create a folder for each species that is in the zip file. Since you can't possibly check manually, the program needs to create the required folders according to the contents of the zip file.
Example: Cats will be stored in "/petshop/cat", turtles will be stored in "/petshop/turtle".

    while(wait(&status) > 0);
    DIR *folder2;
    struct dirent *entry2;
    folder2 = opendir("/home/damdum/modul2/petshop");
    char speciesname[500][500];
    int count = 0;
    //mencari dan menyimpan nama jenis hewan peliharaan di array
    while((entry2 = readdir(folder2)) != NULL) 
    {
        if(entry2->d_type == DT_REG) 
        {
            char temp[500], temp2[500];
            memset(speciesname[count], 0, sizeof(speciesname[count]));
            memset(temp2, 0, sizeof(temp2));
            strcpy(temp, entry2->d_name);
            
            int i, found = 0;
            for(i = 0; i < strlen(temp); i++) 
            {
                if(temp[i] == ';') break;
                temp2[i] = temp[i];
            }
            
            for(i = 0; i < count && found == 0; i++)
                if(strcmp(speciesname[i], temp2) == 0)
                    found = 1;
            
            if(found == 0) 
            {
              strcpy(speciesname[count], temp2);
              count++;
            }
        }
    }
    //membuat folder sesuai jenis hewan
    int i;
    for(i = 0; i < count; i++) 
    {
        pid_t child;
        child = fork();
        if(child < 0) exit(0);
        if(child == 0) {
            char temp[500];
            sprintf(temp, "/home/damdum/modul2/petshop/%s", speciesname[i]);
            char *arg[] = {"mkdir", temp, NULL};
            execv("/bin/mkdir", arg);
        }
    }

c. After the folders are created, your program should move the photos to the folder based on their respective species and rename the photo with the pet's name.
Example: "/petshop/cat/joni.jpg"

    while(wait(&status) > 0);
    DIR *folder3;
    struct dirent *entry3;
    folder3 = opendir("/home/damdum/modul2/petshop");
    //ngecek file yg di folder petshop. temp2 temp3 untuk hewan pertama dan kedua
    while((entry3 = readdir(folder3)) != NULL) 
    {
        if(entry3->d_type == DT_REG) 
        {
            char temp[500];
            char temp2_name[500], temp2_species[500], temp2_year[500];
            char temp3_name[500], temp3_species[500], temp3_year[500];
            memset(temp2_name, 0, sizeof(temp2_name));
            memset(temp2_species , 0, sizeof(temp2_species));
            memset(temp2_year , 0, sizeof(temp2_year));
            memset(temp3_name, 0, sizeof(temp3_name));
            memset(temp3_species , 0, sizeof(temp3_species));
            memset(temp3_year , 0, sizeof(temp3_year));
            strcpy(temp, entry3->d_name);
            
            //nyimpen data tiap hewan
            int i, n, double_pet = 0;
            for(i = 0; i < strlen(temp); i++) 
            {
              if(temp[i] == ';') break;
                temp2_species[i] = temp[i];
            }
            i++; 
            n = i;
            for(; i < strlen(temp); i++) 
            {
              if(temp[i] == ';') break;
                temp2_name[i-n] = temp[i];
            }
            i++; 
            n = i;
            for(; i < strlen(temp); i++) 
            {
              if(temp[i] == '_' || (temp[i] == '.' && temp[i+1] == 'j')) break;
                temp2_year[i-n] = temp[i];
            }
            
            pid_t child;
            child = fork();
            if(child < 0) exit(0);
            if(child == 0) 
            {
              char origin[500], destination[300];
              sprintf(origin, "/home/damdum/modul2/petshop/%s", entry3->d_name);
              sprintf(destination, "/home/damdum/modul2/petshop/%s/%s", temp2_species, temp2_name);
              char *arg[] = {"cp", "-r", origin, destination, NULL};
              execv("/bin/cp", arg);
            }

d. Because 1 photo may have more than 1 pet in it, photos must be moved to each corresponding category.
Example: photo with the name "dog;baro;1_cat;joni;2.jpg" is moved to the folder "/petshop/cat/joni.jpg" and "/petshop/dog/baro.jpg"

              if(temp[i] == '_') 
            {
              i++; 
              n = i;
              for(; i < strlen(temp); i++) 
              {
                if(temp[i] == ';') break;
                  temp3_species[i-n] = temp[i];
              }
              i++; 
              n = i;
              for(; i < strlen(temp); i++) 
              {
                if(temp[i] == ';') break;
                  temp3_name[i-n] = temp[i];
              }
              i++; 
              n = i;
              for(; i < strlen(temp); i++) 
              {
                if(temp[i] == '.' && temp[i+1] == 'j') break;
                  temp3_year[i-n] = temp[i];
              }
              double_pet = 1;
            }
            
            if(double_pet == 1) 
            {
              pid_t cid;
              cid = fork();
              if(cid < 0) exit(0);
              if(cid == 0) 
              {
                char asal[300], tujuan[300];
                sprintf(asal, "/home/damdum/modul2/petshop/%s", entry3->d_name);
                sprintf(tujuan, "/home/damdum/modul2/petshop/%s/%s", temp3_species, temp3_name);
                char *arg[] = {"cp", "-r", asal, tujuan, NULL};
                execv("/bin/cp", arg);
              }

e. In each folder, create a file "keterangan.txt" that contains names and ages of all the pets in the folder. Format of "keterangan.txt" must be identical with the example below :

nama : joni
umur  : 3 tahun

nama : miko
umur  : 2 tahun

             //soal e
            //bikin keterangan untuk hewan2 yang barusan dicopy dr temp2 ke tempatnya
            while(wait(&status) > 0);
            char txt[500];
            sprintf(txt, "/home/damdum/modul2/petshop/%s/keterangan.txt", temp2_species);
            FILE *filep;
            filep = fopen(txt, "a+");
            fprintf(filep, "nama : %s\n", temp2_name);
            fprintf(filep, "umur : %s tahun\n\n", temp2_year);  
            fclose(filep);
            
              //soal e
              //bikin keterangan untuk hewan2 dari temp3 yg ngedouble
              while(wait(&status) > 0);
              char txt[500];
              sprintf(txt, "/home/damdum/modul2/petshop/%s/keterangan.txt", temp3_species);
              FILE *filep;
              filep = fopen(txt, "a+");
              fprintf(filep, "nama : %s\n", temp3_name);
              fprintf(filep, "umur : %s tahun\n\n", temp3_year);
              fclose(filep);
    
    //terakhir kita reomve gambar yg udh di copy tadi
    while(wait(&status) > 0);
    DIR *folder4;
    struct dirent *entry4;
    folder4 = opendir("/home/damdum/modul2/petshop");
    while((entry4 = readdir(folder4)) != NULL) 
    {
      if((entry4->d_type == DT_REG) && strcmp(entry4->d_name, ".") != 0 && strcmp(entry4->d_name, "..") != 0) 
      {
        pid_t child;
        child = fork();
        if(child < 0) exit(0);
        if(child == 0) 
        {
          char filename[500];
          sprintf(filename, "/home/damdum/modul2/petshop/%s", entry4->d_name);
          char *arg[] = {"rm", "-r", filename, NULL};
          execv("/bin/rm", arg);
        }
      }
    }
    
Loba appreciates your help, so much so that he'll treat you to dinner next week!

Note:
Every pet is saved with the format [pet species]:[pet name]:[pet age in years]. 
If there exists more than 1 pet, the data is separated with an underscore(_).
You are not allowed to use system(), mkdir(), dan rename() C functions.
Use fork dan exec.


3. Ranora is an Informatics Engineering student who is currently undergoing an internship at a well-known company called "FakeKos Corp.", a company engaged in 
data security. Because Ranora is still an apprentice, the workload is not as big as the workload of the company's permanent workers. On Ranora's first day of 
work, Ranora's apprentice tutor gave her the task of making a program.

A.Ranora must create a C program which every 40 seconds creates a directory with a name according to the timestamp [YYYY-mm-dd_HH:ii:ss].

B.Each directory is filled with 10 images downloaded from https://picsum.photos/, where each image will be downloaded every 5 seconds. Each downloaded image will be named with a timestamp format [YYYY-mm-dd_HH:ii:ss] and the image is square with the size (n% 1000) + 50 pixels where n is the Unix Epoch time.



     for(int i=0;i<10;i++){
               if(fork()==0){
                  printf("Duar\n");
                  //epoch time
                  int epoch = (int)time(NULL);
                  epoch = (epoch % 1000)+100;
                  //update present time in every loop
                  timeNow=getTime();
                  //image naming
                  snprintf(image,sizeof image,"%02d-%02d-%02d_%02d:%02d:%02d.jpg",timeNow.year,timeNow.month,timeNow.day,timeNow.hours,timeNow.minutes,timeNow.seconds);
                  snprintf(imagepath,sizeof imagepath,"./%s/%s",folder,image); 
                  snprintf(link,sizeof link,"https://picsum.photos/%d.jpg",epoch);
                  //blank space due to bugs on wget that are redirecting to log file afterworth
                  //ga ngerti epoch cuy
                  execl("/usr/bin/wget", "wget", "-q","-O",imagepath, link,"", NULL);
               }
               sleep(5);
            }
            encrypt(folder);
            //zip file
            char zipfile[40];
            snprintf(zipfile,sizeof zipfile,"%s.zip",folder);
            execl("/usr/bin/zip","zip","-rm",zipfile,folder,"-x","*.c",NULL);
         }
      }
      else sleep(40);
      

C.After the directory has been filled with 10 images, the program will create a file "status.txt", which contains the message "Download Success" which is 
encrypted with the Caesar Cipher technique and with shift 5. Caesar Cipher is a simple encryption technique which can perform encryption. string according to the 
shift / key that we specify. For example, the letter "A" will be encrypted with shift 4 it will become "E". Because Ranora is a perfectionist and neat person, he 
wants after the file is created, the directory will be zipped and the directory will be deleted, leaving only the zip file.


    void encrypt(char folder[]){
       FILE *fp;
       char txtpath[40];
       snprintf(txtpath,sizeof txtpath,"./%s/status.txt",folder);
       fp  = fopen (txtpath, "w");
       int key=4;
       //caesar cipher algorithm
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
       //write to txt
       printf("Download Success = %s\n",message);
       for (int i = 0;i<16; i++) 
          fputc(message[i], fp);
       fclose(fp);
    }
    


D. To make it easier to control the program, the Ranora apprentice supervisor wants the program to produce an executable "Killer" program, where the program will 
terminate all running program processes and will run itself after the program is run. Because Ranora is interested in something new, Ranora has an idea for the 
"Killer" program that was made, it must be a bash program.

E.The Ranora apprentice supervisor also wants the main program created by Ranora to run in two modes. To activate the first mode, the program must be executed with 
the -z argument, and when it is executed in the first mode, the main program will immediately execute all its operations when the Killer program is run. 
Meanwhile, to activate the second mode, the program must be run with the -x argument, and when run in the second mode, the main program will stop allowing the 
processes in each directory that are still running until it is finished (The directory that has been created will download the image to completion and create a 
txt file, then zip and delete the directory).

     FILE *killer;
       killer = fopen("killer.sh", "w");
       //when -z stop everything immediatly when -x stop after ziping
       if (strcmp(argv[1], "-z") == 0)
          fprintf(killer, "#!/bin/bash\nkill -9 -%d\n rm killer.sh", getpid());
       else if (strcmp(argv[1], "-x") == 0)
          fprintf(killer, "#!/bin/bash\nkill %d\n rm killer.sh", getpid());

       fclose(killer);
       //to be executable bash
       if(fork() == 0){
          char *argvmod[] = {"chmod", "+x", "killer.sh", NULL};
          execv("/bin/chmod", argvmod);
       }
       //close read input and write output
       close(STDIN_FILENO);
       close(STDOUT_FILENO);







