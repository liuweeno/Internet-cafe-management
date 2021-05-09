#include "requirements.h"
#include "charging.h"

void creatlink(jifei **head,FILE *file) //相当于初始化，根据文件里面的内容创建新链表
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

int inquire(jifei **head, int silent) //查询调用时的计费标准
{
    system("cls");
    time_t lt;
    struct tm *ptr;
    lt=time(&lt);
    ptr=localtime(&lt);
    int time=ptr->tm_hour;
    //开始遍历找对应的money
    jifei *p=*head;
    while(p!=NULL)
    {
        if(p->time==time)
        {
            if (!silent)
            {
                printf("当前时间段的计费标准为：%d元\n", p->money);
                system("pause");
            }
            return p->money;
        }
        if(p->next==NULL&&p->time!=time)
            if (!silent)
            {
                printf("该时间段无计费标准，请设定对应的计费标准:(\n");
                system("pause");
            }
        p=p->next;
    }
    return -1;
}

void creatstandard(jifei **head) //新增计费标准
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
    //最好加一个验证是否已经存在时间段，懒得搞了，就是加多一个遍历，希望用户聪明点
    printf("要添加计费标准的时间段: ");
    scanf("%d",&p1->time);
    printf("此时间段的计费为: ");
    scanf("%d",&p1->money);
    p1->next=NULL;
    p->next=p1;
    printf("新增完成:)\n");
    system("pause");
}

void delete(jifei **head) //删除计费标准
{
    system("cls");
    jifei *p1=*head,*p2=*head,*p;
    int delete;
    printf("要删除的计费标准的时间是 ");
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
    printf("删除完成:)\n");
    system("pause");
}

void change(jifei **head) //修改计费标准
{
    system("cls");
    int time,money;
    jifei *p=*head;
    printf("要修改的对应的计费标准的时间为: ");
    scanf("%d",&time);
    printf("要将%d时的上网费用修改为 ",time);
    scanf("%d",&money);
    while(p!=NULL)
    {
        if(p->time==time)
        {
            p->money=money;
            printf("修改成功:)\n");
            break;
        }
        if(p->next==NULL)
        printf("无此计费标准，修改不了:(\n");
        p=p->next;
    }
    system("pause");
}

// int main()
// {
//     //把rate文件里面的数据读到链表里面
//     FILE *file;
//     if((file=fopen("data/rate.txt","r"))==NULL)
//     {
//         printf("open error!\n");
//         exit(0);
//     }
//     jifei *head=NULL;
//     //先创建链表
//     creatlink(&head,file);
//     //添加计费标准
//     // creatstandard(&head);
//     //查询
//     int money;
//     // money=inquire(&head);
//     //删除
//     // delete(&head);
//     //修改
//     change(&head);
    
//     //测试
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