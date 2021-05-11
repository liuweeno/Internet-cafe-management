#include "requirements.h"
#include "card.h"

void Add_card(card ** cards_list)
{
    system("cls");
    card * current = *cards_list;
    char temp_id[11];
    
    printf("请输入卡号（卡号不得超过 10 个字符）：");
    scanf("%s", temp_id);
    while ('\n' != getchar());
    if (!*cards_list)
    {
        *cards_list = (card *)malloc(sizeof(card));
        current = *cards_list;
    }
    else {
        card * temp = NULL;
        while (current)
        {
            if (!strcmp(temp_id, current->id))
            {
                puts("此卡号已存在，添加失败！");
                system("pause");
                return;
            }
            temp = current;
            current = current->next;
        }
        current = temp;
        temp = (card *)malloc(sizeof(card));
        current->next = temp;
        current = temp;
    }
    strcpy(current->id, temp_id);
    printf("请输入密码（卡号不得超过 16 个字符）：");
    scanf("%s", current->pass);
    while ('\n' != getchar());
    printf("请输入开卡金额：");
    while (1 != scanf("%lf", &current->balance))
    {
        puts("金额须为实数！请重新输入。");
        printf("请输入开卡金额：");
        while ('\n' != getchar());
    }
    current->status = 0;
    current->start_time = 0;
    current->cost_per_hour = 0;
    memset(current->times, 0, sizeof(int) * 12);
    memset(current->countmoney, 0, sizeof(int) * 12);
    current->next = NULL;
    puts("添加完成！");
    system("pause");
}

void Cancel_card(card * cards_list)
{
    system("cls");
    char id[11];
    char pass[17];

    printf("请输入要注销的卡号：");
    scanf("%s", id);
    printf("请输入卡的密码：");
    scanf("%s", pass);
    while (cards_list)
    {
        if (!strcmp(id, cards_list->id))
        {
            if (!strcmp(pass, cards_list->pass))
            {
                cards_list->status = 3;
                puts("注销完成！");
            }
            else {
                puts("卡号与密码不符！");
            }
            system("pause");
            return;
        }
        cards_list = cards_list->next;
    }
    puts("该卡号不存在！");
    system("pause");
}

void Query_card(card * cards_list)
{
    system("cls");
    char id[11];
    char time[50];
    printf("请输入要查询的卡号：");
    scanf("%s", id);
    while (cards_list)
    {
        if (!strcmp(cards_list->id, id))
        {
            strftime(time, 50, "%Y-%m-%d %X", localtime(&cards_list->start_time));
            printf("| 卡号 | %s\n", cards_list->id);
            printf("| 余额 | %.2lf\n", cards_list->balance);
            switch (cards_list->status)
            {
                case 0:
                    puts("| 状态 | 离线");
                    printf("| 上次上机时间 | %s\n", time);
                    break;

                case 1:
                    puts("| 状态 | 在线");
                    printf("| 上机时间 | %s\n", time);
                    printf("| 计费标准 | %g 元/小时\n", cards_list->cost_per_hour);
                    break;

                case 2:
                    puts("| 状态 | 欠费");
                    break;

                case 3:
                    puts("| 状态 | 注销");
                    break;
            }
            system("pause");
            return;
        }
        cards_list = cards_list->next;
    }
    puts("无法找到该卡号！");
    system("pause");
}