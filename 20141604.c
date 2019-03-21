#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "20141604.h"
//TO Git!!!!

int main()
{
    DIR* dir_info;
    char* input;//original one
    char* token;//For parsing the original one 
    char parsed_input[3][90];//After tokenize i'll put strings here.
    history* history_head;
    history* history_tmp;
    int history_index=1;
    history_head=NULL;
    history_tmp=NULL;

    int len=0;//It is the length of the original input
    int i=0,j=0;

    while(1)
    {
        i=0;
        printf("sicsim> ");
        
        input = (char*)malloc(sizeof(char)*90);//memory allocation for mnemonics
        fgets(input,sizeof(char)*91,stdin);//get input words by keyboard
        
 

        //printf("%s\n",input);


        /*For DEBUGGING
        printf("%d\n",len);
        printf("%d\n",strcmp(input,input));
        printf("%ld\n",strlen(input));
        printf("%s",input);
        */
        token = strtok(input," ");
        while(token != NULL){
            strcpy(parsed_input[i],token);
            //printf("token:%s\n",token);
            token = strtok(NULL," ");
            i++;
        }//tokenize strings because some mnemonics have two or more commands
        //printf("%s %s %s",parsed_input[0],parsed_input[1],parsed_input[2]);

        len = strlen(parsed_input[0]);
        //printf("%d\n",len);
        parsed_input[0][len-1] = '\0';
        

        if(strcmp(parsed_input[0],"help") == 0 || strcmp(parsed_input[0],"h") ==0){
            printf("h[elp]\n");
            printf("d[ir]\n");
            printf("q[uit]\n");
            printf("hi[story]\n");
            printf("du[mp] [start, end]\n");
            printf("e[dit] address, value\n");
            printf("f[ill] start, end, value\n");
            printf("reset\n");
            printf("opcode mnemonic\n");
            printf("opcodelist\n");
            history_made(&history_head,&history_index,input);
        }
        else if (strcmp(parsed_input[0],"dir") ==0 || strcmp(parsed_input[0],"d")==0){
            //printf("PLZ show my directory folders\n");
            history_made(&history_head,&history_index,input);
            dir_info=opendir("./");
            dir_print(&dir_info);
        }
        else if (strcmp(parsed_input[0],"quit") ==0 || strcmp(parsed_input[0],"q")==0){
            //printf("Exit SICSIM!!!\n");

            //TODO 
            //history_made() FREE

            return 0;
        }
        else if (strcmp(parsed_input[0],"history")==0 || strcmp(parsed_input[0],"his")==0){
            printf("TODO: you have to make history\n");
            history_made(&history_head,&history_index,input);
            history_tmp = history_head;
            while(1){
                if(history_tmp ==NULL)
                    break;

                printf("%d      %s\n",history_tmp->num,history_tmp->mnemonic);
                history_tmp=history_tmp->next;
            }

        }
        

        free(input);
        free(token);
        for(i=0;i<3;i++){//free the parsed_input array
            for(j=0;j<90;j++)
                parsed_input[i][j]=0;
        }


    }

    return 0;
}
void dir_print(DIR** dir_info)
{
    struct dirent*dir;
    struct stat buf;
    int flag=0;

    if(*dir_info == NULL){
        printf("There is no files and directories\n");
        return;
    }
    if(*dir_info!=NULL){
        while(1){
            dir = readdir(*dir_info);
            if(dir==NULL)
                break;
            stat(dir->d_name,&buf);
            if(S_ISDIR(buf.st_mode)){
                if(strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
                    printf("\t%s/  ",dir->d_name);
                    flag++;
                    if(flag==4){
                        printf("\n");
                        flag=0;
                    }
                }
            }
            else{
                if((buf.st_mode&S_IEXEC)==S_IEXEC){
                    printf("\t%s*  ",dir->d_name);
                    flag++;
                    if(flag==4){
                        printf("\n");
                        flag=0;
                    }
                }
                else{
                    printf("\t%s  ",dir->d_name);
                    flag++;
                    if(flag==4){
                        printf("\n");
                        flag=0;
                    }

                }
            }
        }
    }
    else
        printf("Current Directory does not have Directories and Files.\n");
    printf("\n");
}
void history_made(history** head,int* index, char* Input)
{
    history* tmp=NULL;
    history* moment=NULL;

    if(*index==1){
        *head = (history*)malloc(sizeof(history));
        (*head)->num=1;
        (*head)->next=NULL;
        (*head)->prev=NULL;
        strcpy((*head)->mnemonic,Input);
        (*index)++;
    }
    else{
        tmp=(*head);
        while(1){
            if(tmp->next==NULL)
                break;

            tmp=tmp->next;
        }

        moment=tmp;
        tmp->next=(history*)malloc(sizeof(history));
        tmp=tmp->next;
        tmp->num=(*index);
        tmp->next=NULL;
        tmp->prev=moment;
        strcpy(tmp->mnemonic,Input);
        (*index)++;
    }

}
