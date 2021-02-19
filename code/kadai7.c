#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define String_Max 82
#define Dec_Num 5
#define Inc_Num 10
#define Dec_Threshold 15

/*文字列型キューを実現する構造体*/
typedef struct {
int max; /* キューの容量*/
int num; /* 現在の要素数*/
int front;/* 先頭要素カーソル*/
int rear; /* 末尾要素カーソル*/
char **que; /* キュー本体 (char* へのポインタ配列*/
} StringsQueue;

/*キューの初期化*/
int Initialize(StringsQueue *q, int max){
    q->num = q->front = q->rear = 0;
    if ((q->que = calloc(max, sizeof(char *))) == NULL){
        q->max = 0;/* 配列の確保に失敗*/
        return -1;
    }
    q->max = max;
    return 0;
}

/*キューの後始末*/
void Terminate(StringsQueue *q){
    if (q->que != NULL){
        while( q->num > 0){
            q->num--;
            free(q->que[q->front++]); /* 動的な文字列保存用配列を解放*/
            if (q->front == q->max) q->front = 0;
        }
        free(q->que);
   }
    q->max = q->num = q->front = q->rear = 0;
}

/*キューにデータをエンキュー*/
int Enque(StringsQueue *q, char *x){
    if (q->num >= q->max){ /* キューは満杯*/
        char **tmp = q->que;
        if ((tmp = calloc(q->max+Inc_Num, sizeof(char *))) == NULL) {/* キュー拡張*/
            return -1; /* 配列の確保に失敗*/
        }
        for(q->rear = 0; q->rear < q->num; q->rear++){
            /* 旧キューから新キューへコピー*/
            tmp[q->rear] = q->que[q->front++];
            if (q->front == q->max) q->front = 0;
        }
        free(q->que); /* 旧キュー を解放*/
        q->que = tmp; /* 新キューを設定*/
        q->max += Inc_Num; /* 容量を増加*/
        q ->front = 0;
    }
    q->num++;
    if ((q->que[q->rear] = calloc(strlen(x)+1, sizeof(char))) == NULL)
        /*データをコピーするための動的な文字列保存用配列を確保することに失敗*/
        return -1;
    strcpy(q->que[q->rear++], x);
    if (q->rear == q->max ) q->rear = 0;
    return 0;
}

/*キューからデータをデキュー*/
int Deque(StringsQueue *q, char *x){
    if (q->num <= 0)/* キューは空*/
        return 1;
    q->num--;
    strcpy(x, q->que[q->front]);
    free(q->que[q->front++]);
    if (q->front == q->max) q->front = 0;
    if (q->max - q->num >= Dec_Threshold){
        char **tmp = q->que;
        if ((tmp = calloc(q->max - Dec_Num, sizeof(char *))) == NULL) {/* キュー縮小*/
            return -1; /* 配列の確保に失敗*/
        }
        for(q->rear = 0 ; q->rear < q->num; q->rear++){
            /* 旧キューから新キューへコピー*/
            tmp[q->rear] = q->que[q->front++];
            if (q->front == q->max) q->front = 0;
        }
        free(q->que); /* 旧キューを解放*/
        q->que = tmp; /* 新キューを設定*/
        q->max -= Dec_Num; /* 容量を減少*/
        q->front = 0;
    }
    return 0;
}

/*キューからデータをピーク*/
int Peek(const StringsQueue *q, char *x){
    if (q->num <= 0)
        return -1;
    strcpy(x, q->que[q->front]);
    return 0;
}

/*キューの容量*/
int Capacity(const StringsQueue *q){
    return (q->max);
}

/*キューに蓄えられているデータ数*/
int Size(const StringsQueue *q){
    return (q->num);
}

/*全データの表示*/
void Print(const StringsQueue *q){
    int i;
    for(i = 0; i < q->num; i++)
        printf("%s\n", q->que[((i + q->front)% q->max)]);
}

/*Boyer Moore 法による文字列探索*/
char *bm_match(char *pat, char *txt){
char *pt; /* txt をなぞるカーソル*/
char *pp; /* pat をなぞるカーソル*/
int txt_len = strlen(txt); /* txt の文字数*/
int pat_len = strlen(pat); /* pat の文字数*/
int skip[UCHAR_MAX + 1]; /* スキップテーブル*/
int i;
    for (i = 0; i <= UCHAR_MAX; i++) /* スキップテーブルの作成*/
        skip[i] = pat_len;
    for (pp = pat; *pp != '0'; pp++)
        skip[*pp] = strlen(pp) - 1;
        skip[*(pp - 1)] = pat_len; /* パターンの最後文字の移動距離はパターンの文字数*/

    pt = txt + pat_len - 1; /* pat の末尾と比較する txt の文字を決定*/
    while ( pt < txt + txt_len) { /* txt の比較する文字の位置が txt の末尾を越えるまで*/
        pp = pat + pat_len - 1; /* pat の最後の文字に着目*/
        while (*pt == *pp) {
            if (pp == pat) return (pt); /* 一致した文字がパターンの最初の文字になれば終了*/
            pp--;
            pt--;
        }
        pt += (skip[*pt]> strlen(pp)) ? skip[*pt] : strlen(pp);
    }
    return (NULL);
}

/*キュー中のパターンの数を数える*/
int Count(StringsQueue *q, char *pat){
int count = 0;
int i;
char *pt;
    for(i = 0; i < q->num; i++){
        pt = q->que[((i + q->front)% q->max)];
        while((pt = bm_match(pat, pt))!= NULL) {
        count++;
        pt++;
        }
    }
    return count;
}

int main(void){

    StringsQueue que;

    if (Initialize(&que, 3) == -1) {
        puts(" キューの生成に失敗しました。");
        return 1;
    }

    while (1) {
        int m, count;
        char x[String_Max];
        printf("現在のデータ数：%d/%d\n", Size(&que), Capacity(&que));
        printf("(1) エンキュー (2) デキュー (3) ピーク (4) 表示 (5) パターンの計数 (0) 終了：");
        scanf("%d", &m);
        if (m == 0) break;

        switch(m){
        case 1: printf(" データ：");
            scanf("%s", x);
            if (Enque(&que, x) == -1)
                puts("\a エラー データのエンキューに失敗しました。");
            break;
        case 2:
            if (Deque(&que, x) == -1)
                puts("\a エラー デ キューに失敗しました。");
            else
            printf(" デキューしたデータは %s \n", x);
            break;
        case 3: /* ピーク*/
            if (Peek(&que, x) == -1)
                puts("\a エラー：ピークに失敗しました。");
            else
            printf(" ピークしたデータは %s\n", x);
            break;
        case 4: /* 表示 */
            printf(&que);
            Print(&que);
            break;
        case 5: /* 計数*/
            printf(" 探索する文字列：");
            scanf("%s", x);
            if ((count = Count(&que, x)) <= 0) {
                puts(" パターンは存在しません。");
        } else {
            printf(" 発見したパターン (%s) の数は %d 個です。\n", x, count);
            }
            break;
        }
    }
    Terminate(&que);
    return (0);
}