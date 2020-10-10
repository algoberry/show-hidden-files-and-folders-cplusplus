#include<iostream>
#include<conio.h>
#include<dirent.h>
#include<dir.h>
#include<process.h>
#include<string.h>
#include<stdio.h>
#include<io.h>
#include<dos.h>
#include<sys/stat.h>

struct ffblk vfile;
unsigned long int udata;
char ch,present[MAXPATH];

int next_directory(char *);
void scan_directory(char *);

char base[]="X:\\";

using namespace std;

int main(int account,char *arg[],char *env[])
{   
	clrscr();
	getcwd(present,MAXPATH);
	
	DIR *dir; 
	struct dirent *temp;
	cout<<"\nWelcome to Unhidden for identify the hidden files";
	cout<<"\n\nEnter drive:";
	cin>>ch;
	
	base[0]=ch;
	if((dir = opendir(base)) == NULL)
	{ 
		clrscr();
		cout<<"\nError : Derive not found ";
		getch(); 
		exit(0); 
	}
	
	scan_directory(base);
	while((temp = readdir(dir)) != NULL)
	{
		char  *directory = (char *) malloc(3+strlen(temp->d_name)+1);
		strcpy(directory,base);
		strcat(directory,temp->d_name);
		next_directory(directory);
		free(directory);
	}
	closedir(dir);
	
	clrscr();
	cout<<"\nSystem: Successfully Unhidden it";
	sleep(3);
	
	return 0;
}

int next_directory(char *path)
{
	int count=0;
	DIR *dirtemp; 
	char *hold,*temp;
	struct dirent *ptemp;  
	
	hold=path;
	if ((dirtemp = opendir(path)) != NULL)
	scan_directory(path);
	else
	return 0;
   
	while((ptemp = readdir(dirtemp)) != NULL)
	{     
		char *directory = (char *) malloc(1+strlen(ptemp->d_name)+1);
		directory[0]='\\';
		strcpy(directory+1,ptemp->d_name);
		if(directory[1]!='\.')
		{
			count=strlen(hold);
			temp = (char *) malloc(strlen(hold)+strlen(directory)+1);
			strcpy(temp,hold);
			strcat(temp,directory);
			free(directory);
			if(opendir(temp)!=NULL)
			next_directory(temp); 
			temp[count]='\0'; 
			hold=temp;
		}
		else
		free(directory);
	}
	closedir(dirtemp);
	return 0;
}

void scan_directory(char *tempo)
{
	cout<<"\n"<<tempo;
	unsigned count;
	if(present[0]==tempo[0])
	chdir(tempo);  
	else
	{
		setdisk(tempo[0]-65);
		chdir(tempo); 
	}
	
	udata = findfirst("*.*",&vfile,0x02);
	while(!udata)
	{  
		_dos_getfileattr(vfile.ff_name,&count);
		if (count & _A_HIDDEN)
		{
			_dos_getfileattr(vfile.ff_name,&count);
			count=count & 248;
			_dos_setfileattr(vfile.ff_name,count);
		}
		udata=findnext(&vfile);
	}
						
	if(present[0]==tempo[0])	
	system("cd\\");
	chdir(present); 
}