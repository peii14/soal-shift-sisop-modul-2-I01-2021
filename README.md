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
