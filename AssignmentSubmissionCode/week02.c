/*年内の経過日数を求める*/
#include <stdio.h>
/*- 各月の日数 -*/
int mdays[][13] = {
{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
/*--- 西暦year 年のカレンダー ---*/
int *calendar(int year){
if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
return (int *)mdays + 13; /* (int *) 強制的に型変換する命令 */
else
return (int *)mdays ;
}
/*--- 西暦y 年m 月d 日の年内の経過日数を求める ---*/
int dayofyear(int y, int m, int d){
int *i;
int b=0;
int days = d;
/* 日数 */
for (i = calendar(y) + m - 1; *i != 0; i--){
    printf("n回目のループのiの値は%dです。\n",*i);
days += *i ;
b++;
}
printf("bのループ回数%d\n",b);
return (days);
}
int main(void){
int year, month, day; /* 年・月・日 */
int retry; /* もう一度？ */
do {
printf("年："); scanf("%d", &year);
/*printf("%d\n",*year);
printf("%d\n",(*year)+2);
printf("%d\n",(*year+2));
*/

printf("月："); scanf("%d", &month);
printf("日："); scanf("%d", &day);
printf("年内で%d 日目です。\n", dayofyear(year, month, day));
printf("もう一度しますか（1…はい／0…いいえ）：");
scanf("%d", &retry);
} while (retry == 1);
return (0);
}