#include "requirements.h"
#include "charging.h"

void creatlink(jifei **head,FILE *file) //�൱�ڳ�ʼ���������ļ���������ݴ���������
{
    jifei *p,*p2;
    while (!feof(file))
    {
        if((p=(jifei *)malloc(sizeof(jifei)))==NULL)
        {
            printf("Error!");
            exit(0);
        }

        fscanf(file,"%d%d",&p->time,&p->money);
        p->next=NULL;
        if(*head==NULL)
        *head=p;    
        else
        {
            p2->next=p;
        }
        p2=p;
    }
}

int inquire(jifei **head, int silent) //��ѯ����ʱ�ļƷѱ�׼
{
    system("cls");
    time_t lt;
    struct tm *ptr;
    lt=time(&lt);
    ptr=localtime(&lt);
    int time=ptr->tm_hour;
    //��ʼ�����Ҷ�Ӧ��money
    jifei *p=*head;
    while(p!=NULL)
    {
        if(p->time==time)
        {
            if (!silent)
            {
                printf("��ǰʱ��εļƷѱ�׼Ϊ��%dԪ\n", p->money);
                system("pause");
            }
            return p->money;
        }
        if(p->next==NULL&&p->time!=time)
            if (!silent)
            {
                printf("��ʱ����޼Ʒѱ�׼�����趨��Ӧ�ļƷѱ�׼:(\n");
                system("pause");
            }
        p=p->next;
    }
    return -1;
}

void creatstandard(jifei **head) //�����Ʒѱ�׼
{
    system("cls");
    jifei *p=*head,*p1;
    while (p->next!=NULL)
        p=p->next;
    if((p1=(jifei *)malloc(sizeof(jifei)))==NULL)
    {
        printf("Error!\n");
        exit(0);
    }
    //��ü�һ����֤�Ƿ��Ѿ�����ʱ��Σ����ø��ˣ����ǼӶ�һ��������ϣ���û�������
    printf("Ҫ��ӼƷѱ�׼��ʱ���: ");
    scanf("%d",&p1->time);
    printf("��ʱ��εļƷ�Ϊ: ");
    scanf("%d",&p1->money);
    p1->next=NULL;
    p->next=p1;
    printf("�������:)\n");
    system("pause");
}

void delete(jifei **head) //ɾ���Ʒѱ�׼
{
    system("cls");
    jifei *p1=*head,*p2=*head,*p;
    int delete;
    printf("Ҫɾ���ļƷѱ�׼��ʱ���� ");
    scanf("%d",&delete);
    while(p2!=NULL)
    {
        if(p1==*head&&p2==*head&&p2->time==delete)
        {
            p1=(*head)->next;
            p2=(*head)->next;
            *head=(*head)->next;
        }
        else
        {
            p1=p2;
            p2=p2->next;
        }
        if(p2==NULL)
        break;
        if(p2->time==delete)
        {
            p1->next=p2->next;
            free(p2);
            p2=p1->next;
        }    
    }
    printf("ɾ�����:)\n");
    system("pause");
}

void change(jifei **head) //�޸ļƷѱ�׼
{
    system("cls");
    int time,money;
    jifei *p=*head;
    printf("Ҫ�޸ĵĶ�Ӧ�ļƷѱ�׼��ʱ��Ϊ: ");
    scanf("%d",&time);
    printf("Ҫ��%dʱ�����������޸�Ϊ ",time);
    scanf("%d",&money);
    while(p!=NULL)
    {
        if(p->time==time)
        {
            p->money=money;
            printf("�޸ĳɹ�:)\n");
            break;
        }
        if(p->next==NULL)
        printf("�޴˼Ʒѱ�׼���޸Ĳ���:(\n");
        p=p->next;
    }
    system("pause");
}

// int main()
// {
//     //��rate�ļ���������ݶ�����������
//     FILE *file;
//     if((file=fopen("data/rate.txt","r"))==NULL)
//     {
//         printf("open error!\n");
//         exit(0);
//     }
//     jifei *head=NULL;
//     //�ȴ�������
//     creatlink(&head,file);
//     //��ӼƷѱ�׼
//     // creatstandard(&head);
//     //��ѯ
//     int money;
//     // money=inquire(&head);
//     //ɾ��
//     // delete(&head);
//     //�޸�
//     change(&head);
    
//     //����
//     // jifei *p1=head;
//     // while(p1!=NULL)
//     // {
//     //     printf("%d ",p1->time);
//     //     printf("%d ",p1->money);
//     //     p1=p1->next;
//     // }
//     if(fclose(file))
//     {
//         printf("close error!\n");
//         exit(0);
//     }

    
    

//     return 0;
// }