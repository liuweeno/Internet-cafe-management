#include <stdio.h>
#include <stdlib.h>
typedef struct INFO
{
    int times[12]; //要初始化默认为0才行
    int countmoney[12];  //要初始化默认为0才行
    int cardnumber;  
    int cardpass;  
    int cardstatus;
    int cardmoney;
    struct INFO *next;
}info;

//查询一张卡在一段时间内的消费记录
void record_card(info **head)
{
    int  counttimes,countmoney;
    int number,tamp;
    printf("请输入要查询消费记录的卡号: ");
    scanf("%d",&number);
    printf("请输入要查询的消费记录的月份区间，两个月份用空格相隔\n");
    int start,end;
    scanf("%d%d",&start,&end);
    start=start-1; //因为是用数组
    end=end-1;
    info *p=*head;
    while(p!=NULL)
    {
        if(p->cardnumber==number)  //找到对应结点了
        {
            for(tamp=start;tamp<=end;tamp++)  //把结点里面的指定数组给加起来
            {
                countmoney=countmoney+p->countmoney[tamp];
                counttimes=counttimes+p->times[tamp];
            }
            printf("%d月份到%d月份，该账户共上机%d次，共充值%d元\n",start+1,end+1,counttimes,countmoney);
            break;
        }
        p=p->next;
    }
}

//统计一段时间的总营业额
void totalmoney(info **head)
{
    info *p=*head;
    int i,j;
    printf("请输入要查询的消费记录的月份区间，两个月份用空格相隔\n");
    int start,end;
    scanf("%d%d",&start,&end);
    start=start-1;
    end=end-1;
    int totalmoney=0;
    for(i=start;i<=end;i++)
    {
        while(p!=NULL)
        {
            totalmoney=totalmoney+p->countmoney[i];
            p=p->next;
        }
    }
    printf("%d月份到%d月份，总营业额为%d\n",start+1,end+1,totalmoney);
}

//统计一年中，每个月的上机次数、营业额，并且保存在文件中    
void total_turnover(info **head) 
{
    FILE *file;
    if((file=fopen("data/total.txt","w"))==NULL)
    {
        printf("open error!\n");
        exit(0);
    }
    int i,totalmoney,times;
    info *p=*head;
    for(i=0;i<12;i++)
    {
        while(p!=NULL)
        {
            totalmoney=totalmoney+p->countmoney[i];
            times=times+p->times[i];
            p=p->next;
        }
        p=*head;
        fprintf(file,"%d %d %d\n",i+1,totalmoney,times);
        totalmoney=0;
        times=0;
    }
    if(fclose(file))
    {
        printf("Error!\n");
        exit(0);
    }
    if((file=fopen("data/total.txt","r"))==NULL)
    {
        printf("open error!\n");
        exit(0);
    }
    printf("这是一年中12个月的营业额和所有卡号的上机次数统计:\n");
    printf("月份 营业额 上机次数\n");
    int a,b,c;
    for(i=0;i<12;i++)
    {
        fscanf(file,"%d %d %d\n",&a,&b,&c);
        printf("%d\t%d\t%d\n",a,b,c);
    }
    if(fclose(file))
    {
        printf("Error!\n");
        exit(0);
    }
}


int main()
{
    info *laoban;
    laoban=(info *)malloc(sizeof(info));
    int i;  //每次建立一个新的结点都要使之为0
    for(i=0;i<12;i++) 
    {
        laoban->times[i]=0;
        laoban->countmoney[i]=0;
    }
    laoban->times[3]=12;
    laoban->times[7]=8;
    laoban->countmoney[0]=18;
    laoban->countmoney[8]=18;
    laoban->cardnumber=1;
    laoban->cardpass=000;
    laoban->cardstatus=1;
    laoban->cardmoney=100;
    laoban->next=NULL;

    info *laobannian;
    laobannian=(info *)malloc(sizeof(info));
 //每次建立一个新的结点都要使之为0
    for(i=0;i<12;i++) 
    {
        laobannian->times[i]=0;
        laobannian->countmoney[i]=0;
    }
    laobannian->times[3]=12;
    laobannian->times[7]=8;
    laobannian->countmoney[0]=12;
    laobannian->countmoney[8]=18;
    laobannian->cardnumber=2;
    laobannian->cardpass=0000;
    laobannian->cardstatus=1;
    laobannian->cardmoney=100;
    laobannian->next=laoban;
    // totalmoney(&laobannian);
    // record_card(&laobannian);
    total_turnover(&laobannian);
    return 0;
}