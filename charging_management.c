#include "card.h"
#include "requirements.h"

void Go_online(card * card_list)
{
    char id[11];
    char pass[17];

    system("cls");
    printf("������Ҫ�ϻ��Ŀ��ţ�");
    scanf("%s", id);
    printf("���������룺");
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
                    puts("�ϻ��ɹ���");
                }
                else if (1 == card_list->status)
                    puts("�ÿ������ϻ��������ظ��ϻ���");
                else if (2 == card_list->status)
                    puts("�ÿ�����Ƿ�ѣ��޷��ϻ���");
                else if (3 == card_list->status)
                    puts("�ÿ����ѱ�ע�����޷��ϻ���");
                system("pause");
                return;
            }
            else {
                puts("����Ŀ��������벻��Ӧ��");
                system("pause");
                return;
            }
        }
        card_list = card_list->next;
    }
    puts("�ÿ��Ų����ڣ�");
    system("pause");
}

void Go_offline(card * card_list)
{
    char id[11];

    system("cls");
    printf("������Ҫ�»��Ŀ��ţ�");
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
                printf("�ɹ��»�������ʹ�������� %g Ԫ��ʣ����� %g Ԫ��\n", consume, card_list->balance);
                if (card_list->balance < 0)
                {
                    card_list->status = 2;
                    printf("�ÿ�����Ƿ�ѣ���֪ͨ�û���ʱ��ֵ�������޷������ϻ���");
                }
            }
            else puts("�ÿ�û���ϻ���");
            system("pause");
            return;
        }
        card_list = card_list->next;
    }
    puts("�ÿ��Ų����ڣ�");
    system("pause");
}