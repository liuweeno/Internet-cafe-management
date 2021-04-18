#include "requirements.h"
#include "card.h"
#include "admin.h"

void Card_management(card ** cards_list);
void Charging_management(card * cards_list);
int Panel(int super, admin ** admin_list, card ** cards_list);
void Admin_login(admin ** admin_list,card ** cards_list);
void Permission_management(admin ** admin_list);
void Save_file(admin * admin_list, card * cards_list);

int main(void)
{
    system("cls");
    puts("���������С���");
    FILE * file;
    //load card.txt
    if (access("data", F_OK))
    {
        system("mkdir data");
    }
    if (!access("data/card.txt", F_OK))
    {
        file = fopen("data/card.txt", "r");
    }
    else {
        file = fopen("data/card.txt", "w+");
    }
    card * cards_list = NULL;
    while (1)
    {
        card * new = (card *)malloc(sizeof(card));
        if (EOF == fscanf(file, "%d %s %s %lf %ld %lf\n", &new->status, new->id, new->pass, &new->balance, &new->start_time, &new->cost_per_hour))
        {
            free(new);
            break;
        }
        else {
            new->next = cards_list;
            cards_list = new;
        }
    }
    fclose(file);
    //load admin.txt
    if (!access("data/admin.txt", F_OK))
    {
        file = fopen("data/admin.txt", "r");
    }
    else {
        file = fopen("data/admin.txt", "w+");
    }
    admin * admin_list = NULL;
    while (1)
    {
        admin * new = (admin *)malloc(sizeof(admin));
        if (EOF == fscanf(file, "%d %s %s\n", &new->status, new->username, new->password))
        {
            free(new);
            break;
        }
        else {
            new->next = admin_list;
            admin_list = new;
        }
    }
    fclose(file);
    Admin_login(&admin_list, &cards_list);

    return 0;
}

void Admin_login(admin ** admin_list,card ** cards_list)
{
    char id[11];
    char pass[17];
    if (!*admin_list)
    {
        system("cls");
        puts("�������һ��������ϵͳ�����ȣ�����һ������Ա�˺Űɡ�");
        puts("�´�����ϵͳʱ������Ҫʹ���������Ա�˺ŵ�¼��");
        puts("�������Ա�˺Ž����г�������ԱȨ�ޣ���ӵ����ӡ�ɾ������Ա��Ȩ�ޡ�");
        printf("�������˺ŵ��û�����");
        scanf("%s", id);
        printf("���룺");
        scanf("%s", pass);
        *admin_list = (admin *)malloc(sizeof(admin));
        (*admin_list)->next = NULL;
        (*admin_list)->status = 1;
        strcpy((*admin_list)->username, id);
        strcpy((*admin_list)->password, pass);
        puts("ע����ɣ�");
        system("pause");
    }
    while (1)
    {
        system("cls");
        puts("���������Ա�˺��Լ������¼ϵͳ��");
        printf("�û�����");
        scanf("%s", id);
        printf("���룺");
        scanf("%s", pass);
        admin * current = *admin_list;
        while (current)
        {
            if (!strcmp(current->username, id))
            {
                if (!strcmp(current->password, pass))
                {
                    puts("��¼�ɹ���");
                    system("pause");
                    if (!Panel(current->status, admin_list, cards_list))
                        return;
                }
                else {
                    puts("�û��������벻��Ӧ��");
                    system("pause");
                }
                break;
            }
            current = current->next;
        }
        if (!current)
        {
            puts("�����ڴ��˺ţ�");
            system("pause");
        }
    }
}

int Panel(int super, admin ** admin_list, card ** cards_list)
{
    while (1)
    {
        system("cls");
        puts("===== �����շѹ���ϵͳ =====");
        puts("=      1. ������           =");
        puts("=      2. �Ʒѱ�׼����     =");
        puts("=      3. �Ʒѹ���         =");
        puts("=      4. ���ù���         =");
        puts("=      5. ��ѯͳ��         =");
        puts("=      6. �ǳ��˺�         =");
        if (super)
            puts("=      7. Ȩ�޹���         =");
        puts("=      0. �˳�             =");
        puts("============================");
        puts("�������Ӧѡ�����ţ�");
        switch (getch())
        {
        case '1':
            Card_management(cards_list);
            break;
        
        case '2':

            break;
        
        case '3':
            Charging_management(*cards_list);
            break;
        
        case '4':

            break;
        
        case '5':

            break;

        case '6':
            puts("�ǳ��ɹ���");
            system("pause");
            return 1;

        case '7':
            if (super)
            {
                Permission_management(admin_list);
                break;
            }
            else
                break;

        case '0':
            Save_file(*admin_list, *cards_list);
            return 0;

        default:
            break;
        }
    }
}

void Card_management(card ** cards_list)
{
    while (1)
    {
        system("cls");
        puts("======= ������ ========");
        puts("=      1. ��ӿ�      =");
        puts("=      2. ��ѯ��      =");
        puts("=      3. ע����      =");
        puts("=  0. ������һ���˵�  =");
        puts("=======================");
        puts("�������Ӧѡ�����ţ�");
        switch (getch())
        {
        case '1':
            Add_card(cards_list);
            break;
        
        case '2':
            Query_card(*cards_list);
            break;
        
        case '3':
            Cancel_card(*cards_list);
            break;

        case '0':
            return;

        default:
            break;
        }
    }
}

void Charging_management(card * cards_list)
{
    while (1)
    {
        system("cls");
        puts("====== �Ʒѹ��� =======");
        puts("=      1. �ϻ�        =");
        puts("=      2. �»�        =");
        puts("=  0. ������һ���˵�  =");
        puts("=======================");
        puts("�������Ӧѡ�����ţ�");
        switch (getch())
        {
            case '1':
                Go_online(cards_list);
                break;
            
            case '2':
                Go_offline(cards_list);
                break;
            
            case '0':
                return;

            default:
                break;
        }
    }
}

void Permission_management(admin ** admin_list)
{
    while (1)
    {
        system("cls");
        puts("====== Ȩ�޹��� =======");
        puts("=   1. ��ӹ���Ա     =");
        puts("=   2. ɾ������Ա     =");
        puts("=  0. ������һ���˵�  =");
        puts("=======================");
        puts("�������Ӧѡ�����ţ�");
        switch (getch())
        {
            case '1':
                Add_admin(admin_list);
                break;
            
            case '2':
                Del_Admin(admin_list);
                break;
            
            case '0':
                return;

            default:
                break;
        }
    }
}

void Save_file(admin * admin_list, card * cards_list)
{
    FILE * file = fopen("data/card.txt", "w");
    while (cards_list)
    {
        fprintf(file, "%d %s %s %lf %ld %lf\n", cards_list->status, cards_list->id, cards_list->pass, cards_list->balance, cards_list->start_time, cards_list->cost_per_hour);
        card * temp = cards_list;
        cards_list = cards_list->next;
        free(temp);
    }
    fclose(file);

    file = fopen("data/admin.txt", "w");
    while (admin_list)
    {
        fprintf(file, "%d %s %s\n", admin_list->status, admin_list->username, admin_list->password);
        admin * temp = admin_list;
        admin_list = admin_list->next;
        free(temp);
    }
    fclose(file);
}