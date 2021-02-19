#include<stdio.h>
/*b1019163 日置竜輔*/
int main(void){
int a[5], ch, i=0, j=0;
printf("b1019163 日置竜輔\n");
printf("4つの整数の最小値を求めます。\n");
for(int i=0;i<4;i++){
    scanf("%d",&a[i]);
}
printf("1つ目の値 : %d\n",a[0]);
printf("2つ目の値 : %d\n",a[1]);
printf("3つ目の値 : %d\n",a[2]);
printf("4つ目の値 : %d\n",a[3]);
for(int i=0;i<4;i++){
    for(int j=i+1;j<4;j++){
    if(a[i]>a[j]){
        ch=a[i];
        a[i]=a[j];
        a[j]=ch;
    }
    }
}
printf("最小値は%dです。\n",*a);
return 0;
}