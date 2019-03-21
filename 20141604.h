




void dir_print(DIR** dir_info);

typedef struct _history{
    int num;
    struct _history* next;
    struct _history* prev;
    char mnemonic[90];
}history;

void history_made(history** head,int* index,char* Input);
