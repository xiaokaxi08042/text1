/*
需求分析：
贪心算法 动态规划 回溯
数据由用户键盘输入
价值重量为横轴，价值为纵轴的数据散点图
按重量比进行非递增排序
自主选择算法
指定{0-1}KP数据
输出最优解和求解时间
输出的最优解、求解时间、解向量可保存为txt或导出excel文件
代码提交github仓库
*/
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
//#include<graphics.h>
#include<math.h>
#define N 100
int V[200][200];//前i个物品装入容量为j的背包中获得的最大价值
int max(int a,int b)
{
   if(a>=b)
       return a;
   else return b;
}
//动态规划
int DP(int n,int w[],int v[],int x[],int C)
{
    FILE *fp;
    fp=fopen("1.txt","w+");
    int i,j;
	//填表,其中第一行和第一列全为0
    for(i=0;i<=n;i++)
        V[i][0]=0;
    for(j=0;j<=C;j++)
        V[0][j]=0;
    for(i=1;i<=n;i++)
	{
		printf("%d  %d  %d  ",i,w[i-1],v[i-1]);
		fprintf(fp,"%d  %d  %d  ",i,w[i-1],v[i-1]);
        for(j=1;j<=C;j++)
		{
            if(j<w[i-1])
			{
				V[i][j]=V[i-1][j];
				printf("[%d][%d]=%2d  ",i,j,V[i][j]);
				fprintf(fp,"[%d][%d]=%2d  ",i,j,V[i][j]);
			}

            else
			{
                V[i][j]=max(V[i-1][j],V[i-1][j-w[i-1]]+v[i-1]);
				printf("[%d][%d]=%2d  ",i,j,V[i][j]);
				fprintf(fp,"[%d][%d]=%2d  ",i,j,V[i][j]);
			}
		}
		printf("\n");
		fprintf(fp,"\n");
        fclose(fp);
	}
	//判断哪些物品被选中
    j=C;
    for(i=n;i>=1;i--)
    {
        if(V[i][j]>V[i-1][j])
        {
            x[i]=1;
            j=j-w[i-1];
        }
        else
            x[i]=0;
    }
    printf("选中的物品是:\n");
    for(i=1;i<=n;i++)
        printf("%d ",x[i]);
        printf("\n");
    return V[n][C];

}
//回溯
typedef struct {

int number;       //物品总数量
int volume;       //背吧容量
int curValue;     //背包现存价值
int curVolume;    //背包现存容量
int* curBackpack; //背包内存放物品数组，curPackage[i] = 1; 为已   经放入背包中
                  //                                  = 0; 为未放入背包中
int maxValue;     //背包最大价值量
int* lastBackpack;//最优解背包内物品
int* goodsValue;  //物品价值数组
int* goodsWeight; //物品重量数组
}Backpack;


Backpack bp;

void initBackpack(int v, int n){

    bp.number = n;
    bp.volume = v;
    bp.curValue = 0;
    bp.curVolume = 0;
    bp.maxValue = 0;

    bp.goodsValue = (int*)malloc(bp.number * sizeof(int));
    memset(bp.goodsValue, 0, bp.number * (sizeof(int)));
    bp.goodsWeight = (int*)malloc(bp.number * sizeof(int));
    memset(bp.goodsWeight, 0, bp.number * (sizeof(int)));
    bp.curBackpack = (int*)malloc(bp.number * sizeof(int));
    memset(bp.curBackpack, 0, bp.number * (sizeof(int)));
    bp.lastBackpack = (int*)malloc(bp.number * sizeof(int));
    memset(bp.lastBackpack, 0, bp.number * (sizeof(int)));

    for(int j=0;j < bp.number;j++){
        printf("请输入第%d个物品价值:",(j+1));
        scanf("%d",&bp.goodsValue[j]);
        printf("请输入第%d个物品重量:",(j+1));
        scanf("%d",&bp.goodsWeight[j]);
    }

}

void backTrace(int position){
    if((position+1) > bp.number){
        //当物品全部测试后，查看最大价值量，如何新的价值量大于上一次价值量
        //替换掉，并记忆存放的物品
        if(bp.curValue > bp.maxValue){
            bp.maxValue = bp.curValue;
            for(int i=0;i < bp.number;i++){
                bp.lastBackpack[i] = bp.curBackpack[i];
            }
        }
        return;
    }

//需要通过二叉树图一步步了解回溯
if((bp.curVolume + bp.goodsWeight[position]) <= bp.volume){
    bp.curVolume += bp.goodsWeight[position];
    bp.curValue += bp.goodsValue[position];
    bp.curBackpack[position] = 1;
    backTrace(position+1);
    bp.curVolume -= bp.goodsWeight[position];
    bp.curValue -= bp.goodsValue[position];
}

    bp.curBackpack[position] = 0;
    backTrace(position+1);
}
//贪心
typedef struct bao
{
    int num;
    float w;
    float v;
};
typedef struct avg
{
    int num;
    float val;
    float w;
    float v;
};
struct bao b[N];
struct avg d[N];

int n;
float c;

void Sort()
{
    int i,j,k;
    struct avg temp[N];
    for(i=0;i<n-1;i++)
    {
        k=i;
        for(j=i+1;j<n;j++)
            if(d[k].val<d[j].val) k=j;
                if(k!=i)
                {
                    temp[i]=d[i];
                    d[i]=d[k];
                    d[k]=temp[i];
                }
    }
}

float knapsack()
{
    int i;
    float x[N],sum=0;
    for(i=0;i<n;i++) x[i]=0;
    for(i=0;i<n;i++)
    {
        if(d[i].w>c) break;
        x[d[i].num]=1;
        sum+=d[i].v;
        c=d[i].w;
    }
    if(i<n)
    {
        x[d[i].num]=c/d[i].w;
        sum+=x[d[i].num]*d[i].v;
    }
    return sum;
}
void main()
{
    int xz=1;      //输入选项
	FILE *fp;
	fp=fopen("1.txt","w+");
	while(xz!=0){
		printf("----------算法选择----------------\n\n");
		fprintf( fp, "%s", "----------算法选择----------------\n\n");
	    printf("          1.动态规划算法      \n");
        fprintf( fp, "%s", "          1.动态规划算法      \n");
		printf("          2.回溯算法          \n");
        fprintf( fp, "%s", "          2.回溯算法          \n");
		printf("          3.贪心算法         \n");
        fprintf( fp, "%s", "          3.贪心算法         \n");
		printf("          4.非递增排序        \n");
        fprintf( fp, "%s", "          4.非递增排序        \n");
		printf("          5.散点图           \n");
        fprintf( fp, "%s", "          5.散点图           \n");
		printf("----------------------------------\n");
        fprintf( fp, "%s", "----------------------------------\n");
		printf("选择：");
        fprintf( fp, "%s", "选择：");
		scanf("%d",&xz);
       fprintf( fp, "%d\n",xz);
		switch(xz){
			case 1:
			    printf("-----------1.动态规划算法-----------\n");
            fprintf( fp, "%s", "-----------1.动态规划算法-----------\n");
				int s;//获得的最大价值
                int w[15];//物品的重量
                int v[15];//物品的价值
                int x[15];//物品的选取状态
                int n,i;
                int C;//背包最大容量
                n=5;
                printf("请输入背包的最大容量:\n");
    		fprintf( fp, "%s", "请输入背包的最大容量:\n");
                scanf("%d",&C);
                fprintf( fp, "%d\n",C);

                printf("输入物品数:\n");
    		fprintf( fp, "%s", "输入物品数:\n");
                scanf("%d",&n);
                fprintf( fp, "%d\n",n);
                printf("请分别输入物品的重量:\n");
            fprintf( fp, "%s", "请分别输入物品的重量:\n");
                    for(i=0;i<n;i++)
                scanf("%d",&w[i]);
                fprintf( fp, "%d\n", w[i]);

                printf("请分别输入物品的价值:\n");
            fprintf( fp, "%s", "请分别输入物品的价值:\n");
                    for(i=0;i<n;i++)
                scanf("%d",&v[i]);
                fprintf( fp, "%d\n", v[i]);

                s=DP(n,w,v,x,C);//调用动态规划

                printf("最大物品价值为:\n");
            fprintf( fp, "%s", "最大物品价值为:\n");
                printf("%d\n",s);
            fprintf(fp,"%d\n",s);
            //fclose(fp);

			case 2:
				printf("-----------2.回溯算法-----------\n");
				int volume,number;
                printf("请输入背包容量:");
                scanf("%d",&volume);
                printf("请输入物品数量:");
                scanf("%d",&number);

                initBackpack(volume, number);
                backTrace(0);

                if(bp.maxValue != 0){
                printf("背包最大价值数为:%d\n",bp.maxValue);
                printf("背包内存放的物品为:");
                for(int i=0;i < bp.number;i++){
                    if(bp.lastBackpack[i] == 1){
                printf("第%d个物品;",(i+1));
                    }
                }
              printf("\n");
             }else{
                printf("\n无最优解\n");
                }


            case 3:
            {
                printf("-----------3.贪心算法-----------\n");
                int i,j,k;
                float sum;
                printf("请输入物品总数：");
                scanf("%d",&n);
                printf("请输入背包容量：");
                scanf("%f",&c);
                printf("请输入各物品重量及价值（格式：xx，xx）：");
                for(i=0;i<n;i++)
                {
                    scanf("%f,%f",&b[i].w,&b[i].v);
                }
                for(i=0;i<n;i++) b[i].num=d[i].num=i+1;
                for(i=0;i<n;i++)
                {
                    d[i].val=b[i].v/b[i].w;
                    d[i].v=b[i].v;
                    d[i].w=b[i].w;
                }
                Sort();
                sum=knapsack();
                printf("%2f\n",sum);
                fprintf( fp, "%2f\n",sum);
                fclose(fp);
}
            case 4:
                printf("-----------4.排序算法-----------\n");
                int p[N];
                int I,j,t;
                printf("请输入一组{0-1}KP数据:\n");
                for(I=0;I<N;I++)
                {
                    scanf("%d",&p[I]);
                }
                for(I=0;I<N;I++)
                {
                    for(j=I+1;j<N;j++)
                    {
                        if(p[I]>p[j])
                        {
                            t=p[I];
                            p[I]=p[j];
                            p[j]=t;
                        }
                    }
                }
                printf("非递增排序后:\n");
                for(I=0;I<N;I++)
                {
                    printf("%d ",p[I]);
                }

                return 0;
  /*int x;
  printf("请输入一组{0-1}KP数据的个数:");
  scanf("%d",&x);
  int i,j,k,a,b,num[x];
  printf("请输入物品的重量比:");
  for(i=0;i<x;i++)
    scanf("%d",&num[i]);
  for(j=0;j<x;j++)
  {
    for(k=j+1;k<x;k++)
      if(num[k]>num[j])
    {
      a=num[j];
      num[j]=num[k];
      num[k]=a;
    }
  }
  for(b=0;b<x;b++)
  printf("%d ",num[b]);
  return 0;*/
           /*case 5:
               {
                    int gdriver,gmode,i,j,m,a;
   struct fillsettingstype save;
    gdriver=DETECT;
    initgraph(&gdriver,&gmode," ");
    setbkcolor(0);
    cleardevice();
    setcolor(3);
    settextstyle(1,0,5);
    outtextxy(50,300,"I am from class JI KE 0903");
    outtextxy(150,200,"xuehao");
    outtextxy(70,100,"My name is*****");
    getch();
    cleardevice();
    setlinestyle(0,0,3);
    setfillstyle(1,4);
    for(j=0;j<15;j++)
    {
        setcolor(j);
        line(320,160,295,205);
        line(320,160,345,205);
        line(295,205,250,205);
        line(345,205,390,205);
        line(250,205,285,250);
        line(390,205,355,250);
        line(285,250,280,310);
        line(355,250,360,310);
        line(280,310,320,280);
        line(360,310,320,280);
        floodfill(320,240,j);
        for(i=1;i<=40;i++)
        {
            for(m=0;m<=320;m=m+10)
            {
             line(320+(85+m)*cos(i*pi/20),240-(85+m)*sin(i*pi/20),320+(87+m)*cos(i*pi/20),240-(87+m)*sin(i*pi/20));
            }
            delay(15000);
        }
    }
    cleardevice();
    SetBkcolor(10);
    Setcolor(9);
    setextstyle(1,0,10);
    outtextxy(20,160,"Goodbye!");
    getch();
    closegraph();
               }*/


}//switch(xz){的右括号

}
}
