#include <stdio.h>
#include <string.h>
#include <limits.h>
/*--- Boyer-Moore 法による文字列探索 ---*/
char *bm_match(char *pat , char *txt){
char *pt; /* txt をなぞるカーソル */
char *pp; /* pat をなぞるカーソル */
int txt_len = strlen(txt); /* txt の文字数 (CAGACAGAGA)*/
int pat_len = strlen(pat); /* pat の文字数 (AGAG)*/
int skip[UCHAR_MAX + 1]; /* スキップテーブル */
int i;
int ans=0;

for (i = 0; i <= UCHAR_MAX; i++) /* スキップテーブルの作成 */
skip[i] = pat_len;//全て4にする
for (pp = pat; *pp != '\0'; pp++)
skip[*pp] = strlen(pp) - 1;
skip[*(pp - 1)] = pat_len; /* パターンの最後文字の移動距離はパターンの文字数 */
pt = txt + pat_len - 1; /* pat の末尾と比較するtxt の文字を決定 */
while ( pt < txt + txt_len) { /* txt の比較する文字の位置がtxt の末尾を越えるまで */
pp = pat + pat_len - 1; /* pat の最後の文字に着目 */
while (*pt == *pp) {
if (pp == pat){
    ans++;
    break;
 } /* 一致した文字がパターンの最初の文字になれば終了 */
pp--;
pt--;
}
pt += (skip[*pt]> strlen(pp)) ? skip[*pt] : strlen(pp);
}
if(ans ==0) puts("テキスト中にパターンは存在しません。");
else printf("%dパターン見つかりました。\n",ans);
return (NULL);
}

int main(void){
char *s;
char s1[80]; /* テキスト */
char s2[80]; /* パターン */
printf("テキスト：");
scanf("%s", s1);
printf("パターン：");
scanf("%s", s2);
s = bm_match(s2, s1); /* 文字列s1 から文字列s2 をBoyer-Moore 法で探索 */
return (0);
}