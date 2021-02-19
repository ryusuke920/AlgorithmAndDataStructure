/*次に示す「身体検査データを構造体で処理する」プログラムに関して，以下の問いに答えなさい．*/
#include <stdio.h>
#define VMAX 21 /* 視力の最大値2.1 × 10 */
/*--- 身体検査データ型 ---*/
typedef struct{
char name[20];/* 氏名 */
int height; /* 身長 */
double vision; /* 視力 */
} PhysCheck;
/*--- 身長の平均値を求める ---*/
double ave_height(PhysCheck *dat)
{ int n=0;
double sum = 0.0;
while(dat->height > 0){
sum += (dat++)->height;
n++;
}
return (sum/n);
}
/*--- 視力の分布を求める ---*/
void dist_vision(PhysCheck *dat, int dist[]){ 
int vision;
//printf("a=%c\n",dat->name[4]);
while((vision=(int)(10*((dat++)->vision)+0.5))> 0){
if (vision < VMAX) ++*(dist + vision);//①
}
}

int main(void){
int high[100]={};
int sum[100]={};
PhysCheck *y, x[] = {
{"AKASAKA Tadao", 162, 0.3},
{"KATOH Tomiaki", 173, 0.7},
{"SAITOH Syouji", 175, 2.0},
{"TAKEDA Shinya", 171, 1.5},
{"NAGAHAMA Masaki", 168, 0.4},
{"HAMADA Tetsuaki", 174, 1.2},
{"MATSUTOMI Akio", 169, 0.8},
{"", 0, 0.0} /*フラグ*/
};
for (int i=0;i<7;i++){
    high[i]=x[i].height;
    for(int j=140;j<200;j+=3){
        if(high[i]>=j && high[i+1]<j+1){
            sum[j]+=1;
        }
    }
}

/* 視力の分布 */
int *z, vdist[VMAX]={}; 
puts("■□■ 身体検査一覧表 ■□■");
puts(" 氏名 身長 視力 ");
puts("----------------------------");
for(y = x; y->height > 0; y++)
printf("%-18.18s%4d%5.1f\n", y->name, y->height, y->vision);
printf("\n 平均身長：%5.1fcm\n", ave_height(x));
dist_vision(x, vdist); /* 視力の分布を求める ②*/
printf("\n 視力の分布\n");
for (z = vdist ; z < vdist + VMAX ; z++)
if (*z > 0) printf("%3.1f～：%2d 人\n", (z - vdist)/10.0, *z);
/* 身長の分布 */
printf("\n身長の分布\n");
for(int j=140;j<197;j+=3){
if(-sum[j+3]+sum[j]!=0){
        printf("%dcm ~ %dcm : %d人\n",j,j+2,-sum[j+3]+sum[j]);
    }
}

return 0;
}