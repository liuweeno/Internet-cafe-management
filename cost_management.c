#include "requirements.h"
#include "card.h"

void recharge(card **head)
{
    system("cls");
    card *p=*head;
    int money;
    char id[11];
    printf("要充值的卡号为：");
    scanf("%s", id);
    printf("充值金额为：");
    scanf("%d",&money);
    while(p!=NULL)
    {
        if(!strcmp(p->id, id))
        {
            p->balance=p->balance+money;
            if(p->status==2 && p->balance>=0)
            {
                p->status=0;
            }
            //月份
            time_t lt;
            struct tm *ptr;
            lt=time(&lt);
            ptr=localtime(&lt);
            int time=ptr->tm_mon;
            p->countmoney[time]=p->countmoney[time]+money;
            printf("充值成功:)\n");
            break;
        }
        p=p->next;
        if(p==NULL)
        printf("输入的卡号有误，数据库中无此卡号!\n");
    }
    system("pause");
}

void returnmoney(card **head)
{
    system("cls");
    char number[11];
    card *p=*head;
    printf("请输入要退费的卡号: ");
    gets(number);
    while (p!=NULL)
    {
        if(!strcmp(p->id, number))
        {
        p->balance=0;
        printf("退费操作成功:)\n");
        break;
        }
        p=p->next;
        if(p==NULL)
        printf("该卡号不存在，请检查是否输入错误!\n");
    }
    system("pause");
}

// int main()
// {
//     card *laoban;
//     laoban=(card *)malloc(sizeof(card));
//     int i;  //每次建立一个新的结点都要使之为0
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
//  //每次建立一个新的结点都要使之为0
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
//     //充值卡里面的钱
//     recharge(&laobannian);
//     //退费
//     // returnmoney(&laobannian);
//     return 0;
// }