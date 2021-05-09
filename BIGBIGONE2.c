#include <stdio.h>
typedef struct INFO
{
    int times;
    int cardnumber;
    int cardpass;
    int cardstatus;
    int cardmoney;
    struct INFO *next;
}info;

void recharge(info **head,int *sum)
{
    info *p=*head;
    int cardnumber,money;
    printf("要充值的卡号为：");
    scanf("%d",&cardnumber);
    printf("充值金额为：");
    scanf("%d",&money);
    *sum=*sum+money;
    while(p!=NULL)
    {
        if(p->cardnumber==cardnumber)
        {
            p->cardmoney=p->cardmoney+money;
            printf("充值成功:)\n");
            break;
        }
        p=p->next;
        if(p==NULL)
        printf("输入的卡号有误，数据库中无此卡号!\n");
    }
}

void returnmoney(info **head)
{
    int number;
    info *p=*head;
    printf("请输入要退费的卡号: ");
    scanf("%d",&number);
    while (p!=NULL)
    {
        if(p->cardnumber==number)
        {
        p->cardmoney=0;
        printf("退费操作成功:)\n");
        break;
        }
        p=p->next;
        if(p==NULL)
        printf("该卡号不存在，请检查是否输入错误!\n");
    }

}

int main()
{
    int sum=0;
    info laodan={0,1,123,1,99};
    laodan.next=NULL;
    info *laowang=&laodan;
    //充值卡里面的钱
    // recharge(&laowang,&sum);
    //退费
    returnmoney(&laowang);
    //测试
    printf("%dyes",laowang->cardmoney);
    return 0;
}