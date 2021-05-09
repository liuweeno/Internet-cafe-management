#include <stdio.h>
#include <stdlib.h>
typedef struct INFO
{
    int times[12]; //Ҫ��ʼ��Ĭ��Ϊ0����
    int countmoney[12];  //Ҫ��ʼ��Ĭ��Ϊ0����
    int cardnumber;  
    int cardpass;  
    int cardstatus;
    int cardmoney;
    struct INFO *next;
}info;

//��ѯһ�ſ���һ��ʱ���ڵ����Ѽ�¼
void record_card(info **head)
{
    int  counttimes,countmoney;
    int number,tamp;
    printf("������Ҫ��ѯ���Ѽ�¼�Ŀ���: ");
    scanf("%d",&number);
    printf("������Ҫ��ѯ�����Ѽ�¼���·����䣬�����·��ÿո����\n");
    int start,end;
    scanf("%d%d",&start,&end);
    start=start-1; //��Ϊ��������
    end=end-1;
    info *p=*head;
    while(p!=NULL)
    {
        if(p->cardnumber==number)  //�ҵ���Ӧ�����
        {
            for(tamp=start;tamp<=end;tamp++)  //�ѽ�������ָ�������������
            {
                countmoney=countmoney+p->countmoney[tamp];
                counttimes=counttimes+p->times[tamp];
            }
            printf("%d�·ݵ�%d�·ݣ����˻����ϻ�%d�Σ�����ֵ%dԪ\n",start+1,end+1,counttimes,countmoney);
            break;
        }
        p=p->next;
    }
}

//ͳ��һ��ʱ�����Ӫҵ��
void totalmoney(info **head)
{
    info *p=*head;
    int i,j;
    printf("������Ҫ��ѯ�����Ѽ�¼���·����䣬�����·��ÿո����\n");
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
    printf("%d�·ݵ�%d�·ݣ���Ӫҵ��Ϊ%d\n",start+1,end+1,totalmoney);
}

//ͳ��һ���У�ÿ���µ��ϻ�������Ӫҵ����ұ������ļ���    
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
    printf("����һ����12���µ�Ӫҵ������п��ŵ��ϻ�����ͳ��:\n");
    printf("�·� Ӫҵ�� �ϻ�����\n");
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
    int i;  //ÿ�ν���һ���µĽ�㶼Ҫʹ֮Ϊ0
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
 //ÿ�ν���һ���µĽ�㶼Ҫʹ֮Ϊ0
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