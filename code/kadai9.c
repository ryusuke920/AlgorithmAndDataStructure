#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define String_Max 81
#define PHYSCHECK_VISION 1 /* 視力を表す定数値 */
#define PHYSCHECK_HEIGHT 2 /* 身長を表す定数値 */
#define PHYSCHECK_NAME 4 /* 氏名を表す定数値 */

/*--- 身体データ型 ---*/
typedef struct{
 double vision; /* 視力 */
 int height; /* 身長 */
} Body;

/*--- 身体検査データ型 ---*/
typedef struct{
 Body body; /* 身体データ型 ---*/
 char *name; /* 氏名 */
} PhysCheck;

/*--- ノード ---*/
typedef struct __node {
 PhysCheck data; /* データ */
 struct __node *prev;
 struct __node *next; /* 後続ポインタ*/
} Dnode;

/*--- 線形リスト ---*/
typedef struct {
 Dnode *head; /* 先頭ノードへのポインタ */
 Dnode *crnt; /* 着目ノードへのポインタ */
} Dlist;

/*--- 身体検査の身長の比較関数 ---*/
int PhysCheckHeightCmp(const PhysCheck *x, const PhysCheck *y){
 return x->body.height < y->body.height ? -1 : x->body.height > y->body.height ? 1 : 0;
}

/*--- 身体検査の視力の比較関数 ---*/
int PhysCheckVisionCmp(const PhysCheck *x, const PhysCheck *y){
 return x->body.vision < y->body.vision ? -1 : x->body.vision > y->body.vision ? 1 : 0;
}

/*--- 身体検査の氏名の探索関数 ---*/
int PhysCheckNameMach(const PhysCheck *x, const PhysCheck *y){
 return strstr(x->name, y->name) == NULL ? -1: 0;
}

/*--- 身体検査データ（視力と身長と氏名）の表示（改行なし）---*/
void PrintPhysCheck(const PhysCheck *x){
 printf("視力:%5.1f",x->body.vision);
 printf("身長:%4d ", x->body.height);
 printf("氏名:%-18.18s ", x->name);
}

/*--- 身体検査データ（視力と身長と氏名）の表示（改行あり）---*/
void PrintLnPhysCheck(const PhysCheck *x){
 printf("視力:%5.1f",x->body.vision);
 printf("身長:%4d ", x->body.height);
 printf("氏名:%-18.18s \n", x->name);
}

/*--- 身体検査データ（視力と身長と氏名）の読込み ---*/
PhysCheck ScanPhysCheck(const char *message, int sw){
 char name[String_Max];
 PhysCheck temp;
 printf("%s するデータを入力してください。\n", message);
 if (sw & PHYSCHECK_VISION){printf("視力："); scanf("%lf", &temp.body.vision);}
 if (sw & PHYSCHECK_HEIGHT){printf("身長："); scanf("%d", &temp.body.height);}
 if (sw & PHYSCHECK_NAME){printf("氏名："); scanf("%s", name);}
 if ((temp.name = calloc(strlen(name)+1, sizeof(char))) == NULL) exit ;
 strcpy(temp.name, name);
 return temp;
}

/*--- 一つのノードを動的に生成 ---*/
static Dnode *AllocDnode(void)
{
 return calloc(1, sizeof(Dnode));
}

/*--- n の指すノードの各メンバに値を設定 ----*/
static void SetDnode(Dnode *n, const PhysCheck *x,const Dnode *prev ,const Dnode *next)
{
n->data = *x; /* データ */
if ((n ->data.name = calloc(strlen(x->name)+1, sizeof(char))) == NULL) {
return ;
}
strcpy(n ->data.name, x->name);
n->prev = prev;
n->next = next; /* 後続ポインタ */
}

static int IsEmpty(const Dlist *list){
return list->head->next == list->head;
}

/*--- 線形リストを初期化 ---*/
void Initialize(Dlist *list)
{
 Dnode *dummyNode =AllocDnode();   
 list->head = list->crnt = dummyNode;
 dummyNode->prev=dummyNode->next=dummyNode; 
}

/*--- 関数 compare によって x と一致すると判定されるノードを探索 ---*/
Dnode *Search(Dlist *list, const PhysCheck *x,
int compare(const PhysCheck *x, const PhysCheck *y)){
 Dnode *ptr = list->head->next;

 while (ptr != list->head) {
if (compare(&ptr->data, x) == 0) { /* キー値が一致 */
 list->crnt = ptr;
 return ptr; /* 探索成功 */
 }
 ptr = ptr->next; /* 後続ノードに着目 */
 }
 return NULL; /* 探索失敗 */
}

void InsertAfter(Dlist *list, Dnode *p, const PhysCheck *x){
Dnode *ptr =AllocDnode();
Dnode *nxt =p->next;
p->next =p->next->prev=ptr;
SetDnode(ptr,x,p,nxt);
list->crnt=ptr;
}

/*--- 先頭にノードを挿入 ---*/
void InsertFront(Dlist *list, const PhysCheck *x){
  InsertAfter(list,list->head,x);
}

/*--- 末尾にノードを挿入 ---*/
void InsertRear(Dlist *list, const PhysCheck *x){
 InsertAfter(list,list->head->prev,x);
}

void Remove(Dlist *list, Dnode *p){
    p->prev->next=p->next;
    p->next->prev=p->prev;
    list->crnt=p->prev;
    free(p->data.name);
    free(p);
    if(list->crnt==list->head){
        list->crnt=list->head->next;
    }
}

/*--- 先頭ノードを削除 ---*/
void RemoveFront(Dlist *list){
 if(!IsEmpty(list)){
     Remove(list,list->head->next);
 }
}

/*--- 末尾ノードを削除 ---*/
void RemoveRear(Dlist *list){
if(!IsEmpty(list)){
     Remove(list,list->head->prev);
 }
}

/*--- 着目ノードを削除 ---*/
void RemoveCurrent(Dlist *list){
 if(list->crnt != list->head){
     Remove(list,list->crnt);
 }
}

/*--- 全ノードを削除 ---*/
void Clear(Dlist *list){
 while (!IsEmpty(list)){ /* 空になるまで */
 RemoveFront(list); /* 先頭ノードを削除 */
 }
}

/*--- 着目ノードのデータを表示 ---*/
void PrintCurrent(const Dlist *list){
 if (IsEmpty(list)){
 printf("着目ノードはありません。");
 }else{
 PrintPhysCheck(&list->crnt->data);
 }
}

/*--- 着目ノードのデータを表示（改行付き）---*/
void PrintLnCurrent(const Dlist *list){
 PrintCurrent(list);
 putchar('\n');
}

/*--- 全ノードのデータをリスト順に表示 ---*/
void Print(const Dlist *list){
 if (IsEmpty(list))
 puts("ノードがありません。");
 else {
 Dnode *ptr = list->head->next;

 puts("【一覧表】");
 while (ptr!=list->head) {
     PrintLnPhysCheck(&ptr->data);
     ptr = ptr->next; /* 後続ノードに着目 */
 }
 }
}

/*--- 線形リストの後始末 ---*/
void Terminate(Dlist *list){
 Clear(list); /* 全ノードを削除 */
 free(list->head);
}

/*--- メニュー ---*/
typedef enum {
TERMINATE, INS_FRONT, INS_REAR, RMV_FRONT, RMV_REAR, PRINT_CRNT,
RMV_CRNT, SRCH_VISION, SRCH_HEIGHT, SRCH_NAME, PRINT_ALL, CLEAR
} Menu;

/*--- メニュー選択 ---*/
Menu SelectMenu(void)
{
 int i, ch;
 char *mstring[] = {
 "先頭にノードを挿入", "末尾にノードを挿入", "先頭のノードを削除",
 "末尾のノードを削除", "着目ノードを表示", "着目ノードを削除",
 "視力で探索", "身長で探索", "氏名で探索", "全ノードを表示",
 "全ノードを削除" };
 do {
 for (i = TERMINATE; i < CLEAR; i++) {
 printf("(%2d) %-18.18s ", i + 1, mstring[i]);
 if ((i % 3) == 2)
putchar('\n');
 }
 printf("( 0) 終了 ：");
 scanf("%d", &ch);
 } while (ch < TERMINATE || ch > CLEAR);
 return (Menu)ch;
}
/*--- メイン ---*/
int main(void){
 Menu menu;
 Dlist list;
 PhysCheck x;
 Initialize(&list); 
 do {
 switch (menu = SelectMenu()) {
 case INS_FRONT : /* 先頭にノードを挿入 */
 x = ScanPhysCheck("先頭に挿入",
 PHYSCHECK_VISION | PHYSCHECK_HEIGHT | PHYSCHECK_NAME);
 InsertFront(&list, &x);
 break;
 case INS_REAR : /* 末尾にノードを挿入 */
 x = ScanPhysCheck("末尾に挿入",
 PHYSCHECK_VISION | PHYSCHECK_HEIGHT | PHYSCHECK_NAME);
 InsertRear(&list, &x);
 break;
 case RMV_FRONT : /* 先頭ノードを削除 */
 RemoveFront(&list);
 break;
 case RMV_REAR : /* 末尾ノードを削除 */
 RemoveRear(&list);
 break;
 case PRINT_CRNT : /* 着目ノードのデータを表示 */
 PrintLnCurrent(&list);
 break;
 case RMV_CRNT : /* 着目ノードを削除 */
 RemoveCurrent(&list);
 break;
 case SRCH_VISION : /* 視力による探索 */
 x = ScanPhysCheck("探索", PHYSCHECK_VISION);
 if( Search(&list, &x, PhysCheckVisionCmp) != NULL)
PrintLnCurrent(&list);
 else
puts("その視力のデータはありません。");
 break;
 case SRCH_HEIGHT : /* 身長による探索 */
 x = ScanPhysCheck("探索", PHYSCHECK_HEIGHT);
 if( Search(&list, &x, PhysCheckHeightCmp) != NULL)
PrintLnCurrent(&list);
 else
puts("その身長のデータはありません。");
 break;
 case SRCH_NAME : /* 氏名による探索 */
 x = ScanPhysCheck("探索", PHYSCHECK_NAME);
 if (Search(&list, &x, PhysCheckNameMach) != NULL)
PrintLnCurrent(&list);
 else
puts("その名前のデータはありません。");
 break;
 case PRINT_ALL : /* 全ノードのデータを表示 */
 Print(&list);
 break;
 case CLEAR : /* 全ノードを削除 */
 Clear(&list);
 break;
 }
 } while (menu != TERMINATE);

 Terminate(&list);
 return 0;
}