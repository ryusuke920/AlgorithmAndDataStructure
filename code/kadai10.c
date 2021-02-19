#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*文字列型スタックを実現する構造体*/
typedef struct{
    int max; /* スタックの容量*/
    int ptr; /* スタックポインタ*/
    char **stk; /* スタック本体*/
} StringsStack;

/*スタックの初期化*/
int Initialize(StringsStack *s, int max){
    s->ptr = 0;
    if ((s->stk = calloc(max, sizeof(char *))) == NULL){
        /* char* の配列の確保に失敗*/
        s->max = 0;
        return -1;
    }
        /* char* の配列の確保に成功*/
        s->max = max;
        return 0;
}

/*スタックの後始末*/
void Terminate(StringsStack *s){
    if (s->stk != NULL){
        while( ++s->ptr < s->max)
            free(s->stk[s->ptr]); /* 動的な文字列保存用配列を解放*/
        free(s->stk);
    }
    s->max = s->ptr = 0;
}

/*スタックにデータをプッシュ*/
int Push(StringsStack *s, char *x){
    if (s->ptr >= s->max) return -1; /* スタック満杯*/
    if ((s->stk[s->ptr] = calloc(strlen(x)+1, sizeof(char))) == NULL)
    /* データをコピーするための動的な文字列保存用配列を確保することに失敗*/
    return -1;
    strcpy(s->stk[s->ptr],x);
    s->ptr++;
    return 0;
}

/*スタックからデータをポップ*/
int Pop(StringsStack *s, char *x){
    if (s->ptr <= 0) return -1; /* スタックは空*/
    s->ptr--;
    strcpy(x, s->stk[s->ptr]);
    free(s->stk[s->ptr]);
    /* ポップしたので，動的な文字列保存用配列を解放*/
    return 0;
}

/*スタックは空か*/
int IsEmpty(const StringsStack *s){
    return s->ptr <= 0;
}

/*真に再帰的な関数recur3*/
void recur3(char *st){
    StringsStack stk;
    char *temp;
    Initialize(&stk, 100);
    if ((temp = calloc(strlen(st) + 1,sizeof(char))) == NULL) return;

    Top:
        if((strlen(st)) > 0){
            Push(&stk,st);
            if (strlen(st) > 1) st += 2;
            else st++;
            goto Top;
        }
        if(!IsEmpty(&stk)){
            st = temp;
            Pop(&stk, st);
            printf("%c",*st);
            st++;
            goto Top;
        }
        free(temp);
}

int main(void){
char x[80];
printf(" 文字列を入力せよ：");
scanf("%s", x);
recur3(x);
printf("\n");
return (0);
}