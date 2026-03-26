/*
 * This program displays the names of all files in the current directory.
 */

#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#define HTML_FILE_SIZE 2000
int endsWith (char *str, char *end) {
    size_t slen = strlen (str);
    size_t elen = strlen (end);
    if (slen < elen)
        return 0;
    return (strcmp (&(str[slen-elen]), end) == 0);
}

void CreateHTML(char *Dir_Name)
{
	DIR *Inside;
	struct dirent *dir;
	int PNG_Count, Folder_Count, cnt;
	char Containt[HTML_FILE_SIZE], File_Name[50];
	FILE * f;
	
	PNG_Count = 0;
	
	sprintf(Containt, " <html>");
	sprintf(Containt, "%s \n\t <head> \n\t\t <title> Datasheet of IC-%s </title> \n\t </head>" ,Containt , Dir_Name);
	sprintf(Containt, "%s \n\t <body>",Containt);
	
	Inside = opendir(Dir_Name);
	if (Inside)
	{
		while ((dir = readdir(Inside)) != NULL)
		{
			if(endsWith(dir->d_name, ".png") )
      			PNG_Count++;
		}
		printf("\n\n PNG file Count : %d", PNG_Count);
		closedir(Inside);
	}
	
	for(cnt=1; cnt <= PNG_Count; cnt++)
	{
		sprintf(Containt, "%s \n\t\t <img src=\"Page-%d.png\"><br/>",Containt , cnt);
	}
	sprintf(Containt, "%s \n\t </body> \n </html>",Containt);
	
	//printf("\n\n\t Containts: \n %s", Containt);
	
	
	sprintf(File_Name, "%s/index.html",Dir_Name);
	f = fopen(File_Name, "w");
	fputs(Containt, f);
	fclose(f);
	printf("\n\t Operation Succeed.");
	printf("\n\t Datasheet file: %s", File_Name);
}

int main(void)
{
	DIR *d, *Inside;
	struct dirent *dir;
	int PNG_Count, Folder_Count;
	
	PNG_Count = 0;
	Folder_Count = 0;
	d = opendir(".");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if(dir->d_type == DT_DIR)
			{
				if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
					continue;
				
				printf("Current Folder: %s\n", dir->d_name);
				CreateHTML(dir->d_name);
				Folder_Count++;
			}
		}
		closedir(d);
	}

	return(0);
}
