#include "requirements.h"
#include "card.h"

void Add_card(card ** fuckme)
{
    system("cls");
    card * current = *fuckme;
    char temp_id[11];
    
    printf("�����뿨�ţ����Ų��ó��� 10 ���ַ�����");
    scanf("%s", temp_id);
    while ('\n' != getchar());
    if (!*fuckme)
    {
        *fuckme = (card *)malloc(sizeof(card));
        current = *fuckme;
    }
    else {
        card * temp = NULL;
        while (current)
        {
            if (!strcmp(temp_id, current->id))
            {
                puts("�˿����Ѵ��ڣ����ʧ�ܣ�");
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
    printf("���������루���Ų��ó��� 16 ���ַ�����");
    scanf("%s", current->pass);
    while ('\n' != getchar());
    printf("�����뿪����");
    while (1 != scanf("%lf", &current->balance))
    {
        puts("�����Ϊʵ�������������롣");
        printf("�����뿪����");
        while ('\n' != getchar());
    }
    current->status = 0;
    current->start_time = 0;
    current->cost_per_hour = 0;
    memset(current->times, 0, sizeof(int) * 12);
    memset(current->countmoney, 0, sizeof(int) * 12);
    current->next = NULL;
    puts("�����ɣ�");
    system("pause");
}

void Cancel_card(card * fuckme)
{
    system("cls");
    char id[11];
    char pass[17];

    printf("������Ҫע���Ŀ��ţ�");
    scanf("%s", id);
    printf("�����뿨�����룺");
    scanf("%s", pass);
    while (fuckme)
    {
        if (!strcmp(id, fuckme->id))
        {
            if (!strcmp(pass, fuckme->pass))
            {
                fuckme->status = 3;
                puts("ע����ɣ�");
            }
            else {
                puts("���������벻����");
            }
            system("pause");
            return;
        }
        fuckme = fuckme->next;
    }
    puts("�ÿ��Ų����ڣ�");
    system("pause");
}

void Query_card(card * fuckme)
{
    system("cls");
    char id[11];
    char time[50];
    printf("������Ҫ��ѯ�Ŀ��ţ�");
    scanf("%s", id);
    while (fuckme)
    {
        if (!strcmp(fuckme->id, id))
        {
            strftime(time, 50, "%Y-%m-%d %X", localtime(&fuckme->start_time));
            printf("| ���� | %s\n", fuckme->id);
            printf("| ��� | %.2lf\n", fuckme->balance);
            switch (fuckme->status)
            {
                case 0:
                    puts("| ״̬ | ����");
                    printf("| �ϴ��ϻ�ʱ�� | %s\n", time);
                    break;

                case 1:
                    puts("| ״̬ | ����");
                    printf("| �ϻ�ʱ�� | %s\n", time);
                    printf("| �Ʒѱ�׼ | %g Ԫ/Сʱ\n", fuckme->cost_per_hour);
                    break;

                case 2:
                    puts("| ״̬ | Ƿ��");
                    break;

                case 3:
                    puts("| ״̬ | ע��");
                    break;
            }
            system("pause");
            return;
        }
        fuckme = fuckme->next;
    }
    puts("�޷��ҵ��ÿ��ţ�");
    system("pause");
}