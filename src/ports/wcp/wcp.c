#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>     
#define COUNT(c)       \
           ccount++;        \
           if ((c) == '\n') \
             lcount++;
struct file_n{
	char filename[1000];
};
FILE *fp;
int ch;
char *total[10];
int word_count=0,c2=0,newline_count=0,bytes_count=0,count=0,line_count=0;
struct file_n fn[10000];
int fn_cnt=0,tword_count=0,ct2=0,tnewline_count=0,tbytes_count=0,countt=0,tline_count=0;
int flg[10];
int count_i=0;
void init_i(){
	for(count_i=0;count_i<10;count_i++)
		flg[count_i]=0;
}
int find_filename(char *argx){
	if(argx[0]!='-'){
		strcpy(fn[fn_cnt].filename,argx);
		//fp=fopen(fn[fn_cnt].filename,"r");
		fn_cnt++;
		return 1;	
	}
	return 0;
}
struct str{
	char arg[10];

};
int search_short(char *argx){
	struct str foo[6];
	int i;
	strcpy(foo[0].arg,"-c");
	strcpy(foo[1].arg,"-m");
	strcpy(foo[2].arg,"-l");
	strcpy(foo[3].arg,"-L");
	strcpy(foo[4].arg,"-w");
	for(i=0;i<5;i++){
		if(!strcmp(argx,foo[i].arg)){
			return 1;
		}
	}
	return 0;
}
int search_long(char *argx){
	struct str foo[8];
	int i;
	strcpy(foo[0].arg,"--bytes");
	strcpy(foo[1].arg,"--chars");
	strcpy(foo[2].arg,"--lines");
	strcpy(foo[3].arg,"--files0-from=");
	strcpy(foo[4].arg,"--max-line-length");
	strcpy(foo[5].arg,"--words");
	strcpy(foo[6].arg,"--help");
	strcpy(foo[7].arg,"--version");
	for(i=0;i<8;i++){
		if(!strcmp(argx,foo[i].arg)){
			return 1;
		}
	}
	return 0;
}
void error_args(char *argx){
	int i;
	if(argx[0]=='-' && argx[1]!='-'){
		for(i=1;i<strlen(argx);i++){
			if((argx[i]=='w'|| argx[i]=='l' || argx[i]=='c' || argx[i]=='m' || argx[i]=='L')==0){
				printf("wcp: invalid option -- \'%c\'\nTry \'wcp --help\' for more information.",argx[i]);
				exit(0);
			}
		}
	}
}
typedef unsigned long count_t; 
     count_t ccount;
     count_t wcount;
     count_t lcount;
     count_t total_ccount = 0;
     count_t total_wcount = 0;
     count_t total_lcount = 0;
static int isword (unsigned char c){
       return isalpha (c);
     }
int getword (FILE *fp){
       int c;
       
       if (feof (fp))
         return 0;
           
       while ((c = getc (fp)) != EOF)
         {
           if (isword (c))
             {
               wcount++;
               break;
             }
           COUNT (c);
         }
     
       for (; c != EOF; c = getc (fp))
         {
           COUNT (c);
           if (!isword (c))
             break;
         }
     
       return c != EOF;
     }
           
void counter(){
       ccount = wcount = lcount = 0;
       while (getword (fp))
         ;
       total_ccount += ccount;
       total_wcount += wcount;
       total_lcount += lcount;
     }
void disp_s(char *argx){
	int i;
	if(argx[0]=='-' && argx[1]!='-'){
		for(i=1;i<strlen(argx);i++){
			if(argx[i]=='w'){
				if(flg[0]==1)
					continue;
				//printf("%5d ",wcount);
				printf("%5d",word_count);
				flg[0]=1;
			}
			if(argx[i]=='l'){
				if(flg[1]==1)
					continue;
				printf("%5d ",newline_count);
				flg[1]=1;
			}
			if(argx[i]=='c' || argx[i]=='m'){
				if(flg[2]==1)
					continue;
				printf("%5d ",bytes_count);
				flg[2]=1;
			}
			if(argx[i]=='L'){
				if(flg[3]==1)
					continue;
				printf("%5d ",line_count);
				flg[3]=1;
			}
		}
	}

}
void disp_l(char *argx){
	if(strcmp(argx,"--bytes")==0){
		printf("%5d ",bytes_count);	
	}
	if(strcmp(argx,"--chars")==0){
		printf("%5d ",bytes_count);

	}
	if(strcmp(argx,"--lines")==0){
		printf("%5d ",newline_count);

	}
	if(strcmp(argx,"--max-line-length")==0){
		printf("%5d ",line_count);
	
	}
	if(strcmp(argx,"--words")==0){
		printf("%5d ",word_count);	
	
	}
}
void disp_h(char *argx){
	if(strcmp(argx,"--help")==0){
		printf("Usage: wcp [OPTION]... [FILE]...\n  or:  wcp [OPTION]... --files0-from=F\nPrint newline, word, and byte counts for each FILE, and a total line if\nmore than one FILE is specified.  A word is a non-zero-length sequence of\ncharacters delimited by white space.\n\nWith no FILE, or when FILE is -, read standard input.\n\nThe options below may be used to select which counts are printed, always in\nthe following order: newline, word, character, byte, maximum line length.\n  -c, --bytes            print the byte counts\n  -m, --chars            print the character counts]\n  -l, --lines            print the newline counts\n      --files0-from=F    read input from the files specified by\n                           NUL-terminated names in file F;\n                           If F is - then read names from standard input\n  -L, --max-line-length  print the maximum display width\n  -w, --words            print the word counts\n      --help     display this help and exit\n      --version  output version information and exit\n\nWritten by Partha Pratim Sarma\nCopyright (C) 2017 Partha Pratim Sarma.\n");
	}
	if(strcmp(argx,"--version")==0){
		printf("wcp v 1.0 \nCopyright (C) 2017 Partha Pratim Sarma.\nThis is free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n\nWritten by Partha Pratim Sarma\n");
	}
	exit(0);

}
void disp_st(char *argx){
	int i;
	if(argx[0]=='-' && argx[1]!='-'){
		for(i=1;i<strlen(argx);i++){
			if(argx[i]=='w'){
				printf("%5d ",tword_count);
				
			}
			if(argx[i]=='l'){
				printf("%5d ",tnewline_count);

			}
			if(argx[i]=='c' || argx[i]=='m'){
				printf("%5d ",tbytes_count);

			}
			if(argx[i]=='L'){
				printf("%5d ",tline_count);
			
			}
		}
	}
}
void disp_lt(char *argx){
	if(strcmp(argx,"--bytes")==0){
		printf("%5d ",tbytes_count);	
	}
	if(strcmp(argx,"--chars")==0){
		printf("%5d ",tbytes_count);

	}
	if(strcmp(argx,"--lines")==0){
		printf("%5d ",tnewline_count);

	}
	if(strcmp(argx,"--files0-from=")==0){}
	if(strcmp(argx,"--max-line-length")==0){
		printf("%5d ",tline_count);
	
	}
	if(strcmp(argx,"--words")==0){
		printf("%5d ",tword_count);	
	
	}	
	
}
int search_files0(char *str){
    char search[20]="--files0-from=";
    int count1 = 0, count2 = 0, i, j, flag = 1;
    while (str[count1] != '\0')
        count1++;
    while (search[count2] != '\0')
        count2++;
    for (i = 0; i <= count1 - count2; i++)
    {
        for (j = i; j < i + count2; j++)
        {
            flag = 1;
            if (str[j] != search[j - i])
            {
       			flag = 0;
        	        break;
            }
        }
        	if (flag == 1)
        	    break;
    	}
    	if (flag == 1)
        	return 1;
    	else
        	return 0;
}
void stdin_files0(char *str){
	char *token = strtok(str, " ");
   	while (token != NULL){
        	printf("%s\n", token);
        	token = strtok(NULL, " ");
    	}
}
void get_files0(){
	int ch;
	char str[100];
	int i=0;
	while((ch=getc(stdin))!=EOF){
		if(ch=='\0'){
			str[i]=ch;
			strcpy(fn[fn_cnt++].filename,str);
			i=0;
		}
		else{
			str[i]=ch;
			i++;
		}
	}
}
	

int handle_files0(char *str){
	char *token = strtok(str, "=");
       	token=strtok(NULL, "=");
	printf("%s\n", token);
	if(strcmp(token,"-")==0){
		get_files0();
	}
        return 0;
}
void foo_stdin(){
	while((ch=getc(stdin))!=EOF){
		if(ch==' '){
				word_count++;
				c2++;
			}
			count++;
			if(ch=='\n'){
				newline_count++;
				word_count++;
				count--;
				if(count>line_count){
					line_count=count;
				}
				count=0;

			}
			bytes_count++;
	}
}
void foo_rig(){
	word_count=0,c2=0,newline_count=0,bytes_count=0,count=0,line_count=0;
	while((ch=getc(fp))!=EOF){
			if(ch==' '){
				word_count++;
				c2++;
			}
			count++;
			if(ch=='\n'){
				newline_count++;
				word_count++;
				count--;
				if(count>line_count){
					line_count=count;
				}
				count=0;

			}
			bytes_count++;
		}	
		tword_count+=word_count;
		ct2+=c2;
		tnewline_count+=newline_count;
		tline_count+=line_count;
		tbytes_count+=bytes_count;
}	
void disp_all(){
	printf("%5d",newline_count);
	printf(" %5d",word_count);
	printf(" %5d",bytes_count);
}
void disp_allt(){
	printf("%5d",tnewline_count);
	printf(" %5d",tword_count);
	printf(" %5d",tbytes_count);
}
int main(int argc,char *argv[]){
		int i,j;
		int flag=0;
		init_i();
		for(i=1;i<argc;i++){
			if((strcmp(argv[i],"--help")==0) || (strcmp(argv[i],"--version")==0))
				disp_h(argv[i]);
		}
		for(i=1;i<argc;i++){
			find_filename(argv[i]);
		}
		for(i=1;i<argc;i++){
			if(search_files0(argv[i])==1){
				handle_files0(argv[i]);				
				for(j=0;j<fn_cnt;j++){
				fp=fopen(fn[j].filename,"r");
				foo_rig();
				for(i=1;i<argc;i++){
					error_args(argv[i]);
					disp_s(argv[i]);
				}
				for(i=1;i<argc;i++){
					disp_l(argv[i]);
				}

					disp_all();		
				printf("  %s\n",fn[j].filename);
				fclose(fp);		
			}
				disp_allt();
			printf("  total\n");
			exit(0);			
			}
			
			
		}
		for(i=1;i<argc;i++){
				if(argv[i][0]=='-')
					flag=1;			
			}
		if(fn_cnt==0){
			foo_stdin();
			if(flag==1){
			for(i=1;i<argc;i++){
				error_args(argv[i]);
				disp_s(argv[i]);
			}
			for(i=1;i<argc;i++){
				disp_l(argv[i]);
			}
			}
			else{
				disp_all();
			}
		}
		else{
			for(j=0;j<fn_cnt;j++){
				fp=fopen(fn[j].filename,"r");
				foo_rig();
				if(flag==1){
				for(i=1;i<argc;i++){
					error_args(argv[i]);
					disp_s(argv[i]);
				}
				for(i=1;i<argc;i++){
					disp_l(argv[i]);
				}
				}
				else{
					disp_all();		
				}
				printf("  %s\n",fn[j].filename);
				fclose(fp);		
			}
		}
		if(fn_cnt>1){
			if(flag==1){
			for(i=1;i<argc;i++){
				disp_st(argv[i]);
			}
			for(i=1;i<argc;i++){
				disp_lt(argv[i]);
			}
			}
			else{
				disp_allt();
			}
			printf("  total\n");
			}
                 return 0;
	}
