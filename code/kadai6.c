#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define String_MAX 80

/*--- 身体データ型 ---*/
typedef struct{
double vision; /* 視力 */
int height; /* 身長 */
} Body ;
/*--- 身体検査データ型 ---*/
typedef struct{
Body body; /* 身体データ型 ---*/
char *name; /* 氏名 */
} PhysCheck ;

/*--- int 型スタックを実現する構造体 ---*/
typedef struct {
int max; /* スタックの容量 */
int ptr; /* スタックポインタ */
PhysCheck *stk; /* スタック本体*/
} PhysCheckStack;

/*--- スタックの初期化 ---*/
int Initialize(PhysCheckStack *s, int max){
s->ptr = 0;
if((s->stk = calloc(max,sizeof(PhysCheckStack)))==NULL){
    s->max = 0;
    return -1;
}
s->max = max;
return 0;
}
/*--- スタックにデータをプッシュ ---*/
void Terminate(PhysCheckStack *s){
if (s->stk != NULL){
    while(--s->ptr >= 0)
    free(s ->stk[s->ptr].name);
    free(s->stk);
}
s->max = s->ptr = 0;
}

/*--- スタックにデータをプッシュ ---*/
int Push(PhysCheckStack *s, PhysCheck x){
if (s->ptr >= s->max) return -1; /* スタック満杯 */
if ((s->stk[s->ptr].name = calloc(strlen(x.name), sizeof(char))) == NULL)
return -1;
strcpy(s->stk[s->ptr].name,x.name);
s->stk[s->ptr].body.height = x.body.height;
s->stk[s->ptr].body.vision = x.body.vision;
s->ptr++;
return 0;
}
/*--- スタックからデータをポップ ---*/
int Pop(PhysCheckStack *s, PhysCheck *x){
if (s->ptr <= 0) return -1; /* スタックは空 */
s->ptr--;
*x = s->stk[s->ptr];
return (0);
}
/*--- スタックからデータをピーク ---*/
int Peek(PhysCheckStack *s, PhysCheck *x){
if (s->ptr <= 0) return -1;
strcpy(x->name,s->stk[s->ptr -1].name);
free(s->stk[s->ptr].name);
x->body = s->stk[s->ptr - 1].body;
return 0;
}
/*--- スタックの容量 ---*/
int Capacity(const PhysCheckStack *s){
return s->max;
}
/*--- スタックに積まれているデータ数 ---*/
int Size(const PhysCheckStack *s){
return s->ptr;
}
/*--- スタックの全データの表示 ---*/
void Print(const PhysCheckStack *s){
int i;
for(i = 0; i < s->ptr; i++)
//PhysCheck型のデータなのでそれぞれ指定する必要がある
printf("名前：%s 身長：%d 視力：%0.2lf\n", s->stk[i].name, s->stk[i].body.height, s->stk[i].body.vision);
putchar('\n');
}
char *bm_match(char *pat, char *txt){
    char *pt, *pp;
    int txt_len = strlen(txt);
    int pat_len = strlen(pat);
    int skip[UCHAR_MAX + 1];
    int i;
    for(i = 0; i <= UCHAR_MAX; i++){
        skip[i] = pat_len;
    }
    for(pp = pat; *pp != '\0'; pp++){
        skip[*pp] = strlen(pp) - 1;
    }
    skip[*(pp-1)] = pat_len;
    pt = txt + pat_len - 1;
    while(pt < txt + txt_len){
        pp = pat + pat_len - 1;
        while(*pt == *pp){
            pp--;
            pt++;
        }
        pt += (skip[*pt] > pat_len - strlen(pp)) ? skip[*pt] : pat_len - strlen(pp);
    }
    return (NULL);
}

int Search(PhysCheckStack *s, PhysCheck *x){
    int i,a = 0;
    char *pat = x->name;
    char *txt;
    char *pt;
    for (i = 0; i < s->ptr; i++){
        int ch = 0;
        txt = s->stk[i].name;
        pt = txt;
        while(bm_match(pat,pt) != NULL){
            pt = bm_match(pat,pt)+1;
            a++;
            ch++;
        }
        if(ch != 0){
            printf("名前：%s 身長：%d 視力：%0.2lf\n", s->stk[i].name, s->stk[i].body.height, s->stk[i].body.vision);
        }
    }
    return a;
}

int main(void){
PhysCheckStack s; //データを積んでいくもの
int max;
printf("スタックの大きさを入力してください。\n");
scanf("%d",&max);
if(Initialize(&s, max) == -1){
    puts("スタックの生成に失敗しました。\n");
    return -1;
} 

while (1) {
int menu;
PhysCheck x;//データが入っているもの
x.name = calloc(String_MAX,1);
printf("現在のデータ数：%d/%d\n",Size(&s), Capacity(&s));
printf("(1) プッシュ (2) ポップ (3) ピーク (4) 表示 (5)探索 (0) 終了：");
scanf("%d", &menu);
if (menu == 0) break;
switch (menu) {
case 1: /* プッシュ */
printf("名前：");
scanf("%s", x.name);
printf("身長：");
scanf("%d", &x.body.height);
printf("視力：");
scanf("%lf", &x.body.vision);
if (Push(&s, x) == -1)
puts("\a エラー：プッシュに失敗しました。");
break;
case 2: /* ポップ */
if (Pop(&s, &x) == -1)
puts("\a エラー：ポップに失敗しました。");
else
printf("ポップしたデータは %s %d %0.2lf です。\n", x.name, x.body.height, x.body.vision);
break;
case 3: /* ピーク */
if (Peek(&s, &x) == -1)
puts("\a エラー：ピークに失敗しました。");
else
printf("ピークしたデータは %s %d %0.2lf です。\n", x.name, x.body.height, x.body.vision);
break;
case 4: /* 表示 */
Print(&s);
break;
case 5:/*探索*/
printf("探索する名前\n");
scanf("%s",x.name);
int count = Search(&s,&x);
if (count == 0){
    printf("パターンは存在しません。\n");
}else{
    printf("%d種類のパターンがありました。\n", count);
}
break;
}
}
Terminate(&s);
return 0;
}