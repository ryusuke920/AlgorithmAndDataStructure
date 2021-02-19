#include <stdio.h>
#include <string.h>
#define MAX 10
/*--- 身体データ型 ---*/
typedef struct{
double vision; /* 視力 */
int height; /* 身長 */
} Body ;
/*--- 身体検査データ型 ---*/
typedef struct{
Body body; /* 身体データ型 ---*/
char name[20]; /* 氏名 */
} PhysCheck ;

/*--- int 型スタックを実現する構造体 ---*/
typedef struct {
int max; /* スタックの容量 */
int ptr; /* スタックポインタ */
PhysCheck stk[MAX]; /* スタック本体*/
} PhysCheckStack;
/*--- スタックの初期化 ---*/
int Initialize(PhysCheckStack *s, int max){
s->ptr = 0;
s->max = max;
return 0;
}
/*--- スタックにデータをプッシュ ---*/
int Push(PhysCheckStack *s, PhysCheck x){
if (s->ptr >= s->max) return -1; /* スタック満杯 */
s->stk[s->ptr] = x;
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
*x = s->stk[s->ptr - 1];
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
printf("%lf %d %s", s->stk[i].body.vision, s->stk[i].body.height, s->stk[i].name);
putchar('\n');
}

int Search(PhysCheckStack *s, PhysCheck *x){
    int i,j,ch = 0,a = 0;
    for(i = 0; i < s->ptr;i++){
        ch = 0;
        for(j=0;j<strlen(x->name);j++){
            if(s->stk[i].name[j] != x->name[j]) ch = 1;
        }
    if(ch == 0){
        a++;
        printf("視力 : %lf 身長 : %d 名前 : %s\n",s->stk[i].body.vision,s->stk[i].body.height,s->stk[i].name);
    }
    }
    return a;
}
int main(void){
PhysCheckStack s; //データを積んでいくもの
Initialize(&s, MAX);
while (1) {
int menu;
PhysCheck x;//データが入っているもの
printf("現在のデータ数：%d/%d\n",Size(&s), Capacity(&s));
printf("(1) プッシュ (2) ポップ (3) ピーク (4) 表示 (5)探索 (0) 終了：");
scanf("%d", &menu);
if (menu == 0) break;
switch (menu) {
case 1: /* プッシュ */
printf("データ：");
scanf("%lf %d %s", &x.body.vision, &x.body.height, x.name);
if (Push(&s, x) == -1)
puts("\a エラー：プッシュに失敗しました。");
break;
case 2: /* ポップ */
if (Pop(&s, &x) == -1)
puts("\a エラー：ポップに失敗しました。");
else
printf("ポップしたデータは%d です。\n", x.body.vision, x.body.height, x.name);
break;
case 3: /* ピーク */
if (Peek(&s, &x) == -1)
puts("\a エラー：ピークに失敗しました。");
else
printf("ピークしたデータは%d です。\n", x.body.vision, x.body.height, x.name);
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
}
}
return 0;
}