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
    printf("Ҫ��ֵ�Ŀ���Ϊ��");
    scanf("%d",&cardnumber);
    printf("��ֵ���Ϊ��");
    scanf("%d",&money);
    *sum=*sum+money;
    while(p!=NULL)
    {
        if(p->cardnumber==cardnumber)
        {
            p->cardmoney=p->cardmoney+money;
            printf("��ֵ�ɹ�:)\n");
            break;
        }
        p=p->next;
        if(p==NULL)
        printf("����Ŀ����������ݿ����޴˿���!\n");
    }
}

void returnmoney(info **head)
{
    int number;
    info *p=*head;
    printf("������Ҫ�˷ѵĿ���: ");
    scanf("%d",&number);
    while (p!=NULL)
    {
        if(p->cardnumber==number)
        {
        p->cardmoney=0;
        printf("�˷Ѳ����ɹ�:)\n");
        break;
        }
        p=p->next;
        if(p==NULL)
        printf("�ÿ��Ų����ڣ������Ƿ��������!\n");
    }

}

int main()
{
    int sum=0;
    info laodan={0,1,123,1,99};
    laodan.next=NULL;
    info *laowang=&laodan;
    //��ֵ�������Ǯ
    // recharge(&laowang,&sum);
    //�˷�
    returnmoney(&laowang);
    //����
    printf("%dyes",laowang->cardmoney);
    return 0;
}