#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Row
{
    int index;
    char *val;
} Row;

typedef struct Dictionary
{
    Row *rows;
    int csize, msize;
} Dictionary;

char *getStr();
int insert(Dictionary *dict, char *cur_value, int ind);
bool in_dictionary(Dictionary *dict, char *cur_value);
void show (Dictionary *dict);
Dictionary *LZW_Compressor(Dictionary *dict, char *text);
void del (Dictionary *dict);

int main()
{
    char *text = getStr();
    const int n = strlen(text); //capacity of alphabet
    Dictionary *dict = calloc(1, sizeof(Dictionary));
    dict->rows = calloc(n, sizeof(Row));
    dict->msize = n;
    LZW_Compressor(dict, text);
    show(dict);
    free(text);
    del(dict);
    return 0;
}

Dictionary *LZW_Compressor(Dictionary *dict, char *text)
{
    for (int i=0; i<strlen(text); i++)
    {
        dict->rows[i].index = i + 1;
    }
    char *s = calloc(strlen(text), sizeof(char)), c;
    s[0] = text[0];
    s[1]= '\0';
    int cnt = 0, cnt_text = 1;
    while (cnt_text < strlen(text))
    {
        c = text[cnt_text];
        char *temp = calloc(strlen(s)+2, sizeof(char));
        strcpy(temp, s);
        temp[strlen(s)] = c;
        temp[strlen(s)+1]='\0';
        if (in_dictionary(dict, temp))
        {
            strcpy(s,temp);
            free(temp);
        }
        else
        {
            insert(dict, temp, cnt);
            cnt++;
            s[0]=c;
            s[1]='\0';
        }
        cnt_text++;
    }
    free(s);
    return dict;
}

void del(Dictionary *dict)
{
	for (int i=0; i<dict->csize; i++)
	{
		free(dict->rows[i].val);
		dict->rows[i].val = NULL;
	}
	free(dict->rows);
	dict->rows = NULL;
	free(dict);
}

bool in_dictionary(Dictionary *dict, char *cur_value)
{
    for (int i = 0; i < dict->csize; i++)
    {
        if (strcmp(dict->rows[i].val, cur_value) == 0)
        {
            return true;
        }
    }
    return false;
}

void show (Dictionary *dict)
{
    Row *ptr = dict->rows;
    for (int i=0; i<dict->csize; i++)
    {
        printf("%d\t%s\n", ptr[i].index, ptr[i].val);
    }
}

int insert(Dictionary *dict, char *cur_value, int ind)
{
    dict->rows[ind].val = cur_value;
    (dict->csize)++;
    return 0;
}

char *getStr()
{
    char *s = malloc(sizeof(char)),c;
    int i;
    for (i=0; (c=getchar())!='\n'; i++)
    {
         s[i] = c;
	 s = realloc(s, (i+2)*sizeof(char));
    }
    s[i] = '\0';
    return s;
}
