#include "requirements.h"
#include "card.h"
void record_card(card **head)
{
    system("cls");
    int  counttimes = 0,countmoney = 0;
    int tamp;
    char number[11];
    printf("������Ҫ��ѯ���Ѽ�¼�Ŀ���: ");
    scanf("%s", number);
    printf("������Ҫ��ѯ�����Ѽ�¼���·����䣬�����·��ÿո����\n");
    int start,end;
    scanf("%d%d",&start,&end);
    start=start-1; //��Ϊ��������
    end=end-1;
    card *p=*head;
    while(p!=NULL)
    {
        if(!strcmp(p->id, number))  //�ҵ���Ӧ�����
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
    system("pause");
}

//ͳ��һ��ʱ�����Ӫҵ��
void totalmoney(card **head)
{
    system("cls");
    card *p=*head;
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
    system("pause");
}

//ͳ��һ���У�ÿ���µ��ϻ�������Ӫҵ����ұ������ļ���    
void total_turnover(card **head) 
{
    system("cls");
    FILE *file;
    if((file=fopen("data/total.txt","w"))==NULL)
    {
        printf("open error!\n");
        exit(0);
    }
    int i,totalmoney = 0,times = 0;
    card *p=*head;
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
    system("pause");
}


// int main()
// {
//     card *laoban;
//     laoban=(card *)malloc(sizeof(card));
//     int i;  //ÿ�ν���һ���µĽ�㶼Ҫʹ֮Ϊ0
//     for(i=0;i<12;i++) 
//     {
//         laoban->times[i]=0;
//         laoban->countmoney[i]=0;
//     }
//     laoban->times[3]=12;
//     laoban->times[7]=8;
//     laoban->countmoney[0]=18;
//     laoban->countmoney[8]=18;

//     strcpy(laoban->id,"2");
//     strcpy(laoban->pass,"000000");    
//     laoban->status=1;
//     laoban->balance=100;
//     laoban->next=NULL;

//     card *laobannian;
//     laobannian=(card *)malloc(sizeof(card));
//     //ÿ�ν���һ���µĽ�㶼Ҫʹ֮Ϊ0
//     for(i=0;i<12;i++) 
//     {
//         laobannian->times[i]=0;
//         laobannian->countmoney[i]=0;
//     }
//     laobannian->times[3]=12;
//     laobannian->times[7]=8;
//     laobannian->countmoney[0]=12;
//     laobannian->countmoney[8]=18;
//     strcpy(laobannian->id,"1");
//     strcpy(laobannian->pass,"0000");
//     laobannian->status=1;
//     laobannian->balance=100;
//     laobannian->next=laoban;
//     // totalmoney(&laobannian);
//     // record_card(&laobannian);
//     total_turnover(&laobannian);
//     return 0;
// }