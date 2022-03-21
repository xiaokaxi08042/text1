/*
���������
̰���㷨 ��̬�滮 ����
�������û���������
��ֵ����Ϊ���ᣬ��ֵΪ���������ɢ��ͼ
�������Ƚ��зǵ�������
����ѡ���㷨
ָ��{0-1}KP����
������Ž�����ʱ��
��������Ž⡢���ʱ�䡢�������ɱ���Ϊtxt�򵼳�excel�ļ�
�����ύgithub�ֿ�
*/
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
//#include<graphics.h>
#include<math.h>
#define N 100
int V[200][200];//ǰi����Ʒװ������Ϊj�ı����л�õ�����ֵ
int max(int a,int b)
{
   if(a>=b)
       return a;
   else return b;
}
//��̬�滮
int DP(int n,int w[],int v[],int x[],int C)
{
    FILE *fp;
    fp=fopen("1.txt","w+");
    int i,j;
	//���,���е�һ�к͵�һ��ȫΪ0
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
	//�ж���Щ��Ʒ��ѡ��
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
    printf("ѡ�е���Ʒ��:\n");
    for(i=1;i<=n;i++)
        printf("%d ",x[i]);
        printf("\n");
    return V[n][C];

}
//����
typedef struct {

int number;       //��Ʒ������
int volume;       //��������
int curValue;     //�����ִ��ֵ
int curVolume;    //�����ִ�����
int* curBackpack; //�����ڴ����Ʒ���飬curPackage[i] = 1; Ϊ��   �����뱳����
                  //                                  = 0; Ϊδ���뱳����
int maxValue;     //��������ֵ��
int* lastBackpack;//���Žⱳ������Ʒ
int* goodsValue;  //��Ʒ��ֵ����
int* goodsWeight; //��Ʒ��������
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
        printf("�������%d����Ʒ��ֵ:",(j+1));
        scanf("%d",&bp.goodsValue[j]);
        printf("�������%d����Ʒ����:",(j+1));
        scanf("%d",&bp.goodsWeight[j]);
    }

}

void backTrace(int position){
    if((position+1) > bp.number){
        //����Ʒȫ�����Ժ󣬲鿴����ֵ��������µļ�ֵ��������һ�μ�ֵ��
        //�滻�����������ŵ���Ʒ
        if(bp.curValue > bp.maxValue){
            bp.maxValue = bp.curValue;
            for(int i=0;i < bp.number;i++){
                bp.lastBackpack[i] = bp.curBackpack[i];
            }
        }
        return;
    }

//��Ҫͨ��������ͼһ�����˽����
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
//̰��
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
    int xz=1;      //����ѡ��
	FILE *fp;
	fp=fopen("1.txt","w+");
	while(xz!=0){
		printf("----------�㷨ѡ��----------------\n\n");
		fprintf( fp, "%s", "----------�㷨ѡ��----------------\n\n");
	    printf("          1.��̬�滮�㷨      \n");
        fprintf( fp, "%s", "          1.��̬�滮�㷨      \n");
		printf("          2.�����㷨          \n");
        fprintf( fp, "%s", "          2.�����㷨          \n");
		printf("          3.̰���㷨         \n");
        fprintf( fp, "%s", "          3.̰���㷨         \n");
		printf("          4.�ǵ�������        \n");
        fprintf( fp, "%s", "          4.�ǵ�������        \n");
		printf("          5.ɢ��ͼ           \n");
        fprintf( fp, "%s", "          5.ɢ��ͼ           \n");
		printf("----------------------------------\n");
        fprintf( fp, "%s", "----------------------------------\n");
		printf("ѡ��");
        fprintf( fp, "%s", "ѡ��");
		scanf("%d",&xz);
       fprintf( fp, "%d\n",xz);
		switch(xz){
			case 1:
			    printf("-----------1.��̬�滮�㷨-----------\n");
            fprintf( fp, "%s", "-----------1.��̬�滮�㷨-----------\n");
				int s;//��õ�����ֵ
                int w[15];//��Ʒ������
                int v[15];//��Ʒ�ļ�ֵ
                int x[15];//��Ʒ��ѡȡ״̬
                int n,i;
                int C;//�����������
                n=5;
                printf("�����뱳�����������:\n");
    		fprintf( fp, "%s", "�����뱳�����������:\n");
                scanf("%d",&C);
                fprintf( fp, "%d\n",C);

                printf("������Ʒ��:\n");
    		fprintf( fp, "%s", "������Ʒ��:\n");
                scanf("%d",&n);
                fprintf( fp, "%d\n",n);
                printf("��ֱ�������Ʒ������:\n");
            fprintf( fp, "%s", "��ֱ�������Ʒ������:\n");
                    for(i=0;i<n;i++)
                scanf("%d",&w[i]);
                fprintf( fp, "%d\n", w[i]);

                printf("��ֱ�������Ʒ�ļ�ֵ:\n");
            fprintf( fp, "%s", "��ֱ�������Ʒ�ļ�ֵ:\n");
                    for(i=0;i<n;i++)
                scanf("%d",&v[i]);
                fprintf( fp, "%d\n", v[i]);

                s=DP(n,w,v,x,C);//���ö�̬�滮

                printf("�����Ʒ��ֵΪ:\n");
            fprintf( fp, "%s", "�����Ʒ��ֵΪ:\n");
                printf("%d\n",s);
            fprintf(fp,"%d\n",s);
            //fclose(fp);

			case 2:
				printf("-----------2.�����㷨-----------\n");
				int volume,number;
                printf("�����뱳������:");
                scanf("%d",&volume);
                printf("��������Ʒ����:");
                scanf("%d",&number);

                initBackpack(volume, number);
                backTrace(0);

                if(bp.maxValue != 0){
                printf("��������ֵ��Ϊ:%d\n",bp.maxValue);
                printf("�����ڴ�ŵ���ƷΪ:");
                for(int i=0;i < bp.number;i++){
                    if(bp.lastBackpack[i] == 1){
                printf("��%d����Ʒ;",(i+1));
                    }
                }
              printf("\n");
             }else{
                printf("\n�����Ž�\n");
                }


            case 3:
            {
                printf("-----------3.̰���㷨-----------\n");
                int i,j,k;
                float sum;
                printf("��������Ʒ������");
                scanf("%d",&n);
                printf("�����뱳��������");
                scanf("%f",&c);
                printf("���������Ʒ��������ֵ����ʽ��xx��xx����");
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
                printf("-----------4.�����㷨-----------\n");
                int p[N];
                int I,j,t;
                printf("������һ��{0-1}KP����:\n");
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
                printf("�ǵ��������:\n");
                for(I=0;I<N;I++)
                {
                    printf("%d ",p[I]);
                }

                return 0;
  /*int x;
  printf("������һ��{0-1}KP���ݵĸ���:");
  scanf("%d",&x);
  int i,j,k,a,b,num[x];
  printf("��������Ʒ��������:");
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


}//switch(xz){��������

}
}
