#include "card.h"
#include "requirements.h"

void Go_online(card * card_list)
{
    char id[11];
    char pass[17];

    system("cls");
    printf("请输入要上机的卡号：");
    scanf("%s", id);
    printf("请输入密码：");
    scanf("%s", pass);
    while (card_list)
    {
        if (!strcmp(id, card_list->id))
        {
            if (!strcmp(pass, card_list->pass))
            {
                if (0 == card_list->status)
                {
                    card_list->status = 1;
                    card_list->start_time = time(NULL);
                    puts("上机成功！");
                }
                else if (1 == card_list->status)
                    puts("该卡号已上机，请勿重复上机。");
                else if (2 == card_list->status)
                    puts("该卡号已欠费，无法上机。");
                else if (3 == card_list->status)
                    puts("该卡号已被注销，无法上机。");
                system("pause");
                return;
            }
            else {
                puts("输入的卡号与密码不对应！");
                system("pause");
                return;
            }
        }
        card_list = card_list->next;
    }
    puts("该卡号不存在！");
    system("pause");
}

void Go_offline(card * card_list)
{
    char id[11];

    system("cls");
    printf("请输入要下机的卡号：");
    scanf("%s", id);
    while (card_list)
    {
        if (!strcmp(id, card_list->id))
        {
            if (card_list->status == 1)
            {
                card_list->status = 0;
                time_t stoptime = time(NULL);
                long online_hours = (stoptime - card_list->start_time) % 3600 ? (stoptime - card_list->start_time) : (stoptime - card_list->start_time) + 1;
                double consume = online_hours * card_list->cost_per_hour;
                card_list->balance -= consume;
                printf("成功下机。本次使用消费了 %g 元，剩余余额 %g 元。\n", consume, card_list->balance);
                if (card_list->balance < 0)
                {
                    card_list->status = 2;
                    printf("该卡现已欠费，请通知用户及时充值，否则将无法正常上机。");
                }
            }
            else puts("该卡没有上机！");
            system("pause");
            return;
        }
        card_list = card_list->next;
    }
    puts("该卡号不存在！");
    system("pause");
}