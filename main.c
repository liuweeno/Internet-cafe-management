#include "requirements.h"
#include "card.h"
#include "admin.h"
#include "charging.h"

void Card_management(card ** cards_list);
void Charging_management(jifei ** rates_list, card * cards_list);
bool Panel(int super, admin ** admin_list, card ** cards_list, jifei ** rates_list);
void Admin_login(admin ** admin_list,card ** cards_list, jifei ** rates_list);
void Permission_management(admin ** admin_list);
void Charging_rule(jifei ** rates_list);
void Cost_management(card ** cards_list);
void Statistics(card ** cards_list);
void Save_file(admin * admin_list, card * cards_list, jifei * rates_list);

int main(void)
{
    system("cls");
    puts("?????????С???");
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
        if (EOF == fscanf(file, "%d %s %s %lf %ld %lf %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", &new->status, new->id, new->pass, &new->balance, &new->start_time, &new->cost_per_hour, \
        &new->times[0], &new->times[1], &new->times[2], &new->times[3], &new->times[4], &new->times[5], &new->times[6], &new->times[7], &new->times[8], &new->times[9], &new->times[10], &new->times[11], \
        &new->countmoney[0], &new->countmoney[1], &new->countmoney[2], &new->countmoney[3], &new->countmoney[4], &new->countmoney[5], &new->countmoney[6], &new->countmoney[7], &new->countmoney[8], &new->countmoney[9], &new->countmoney[10], &new->countmoney[11]))
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
    //load rate.txt
    if (!access("data/rate.txt", F_OK))
    {
        file = fopen("data/rate.txt", "r");
    }
    else {
        file = fopen("data/rate.txt", "w+");
    }
    jifei * rates_list = NULL;
    creatlink(&rates_list, file);
    fclose(file);
    Admin_login(&admin_list, &cards_list, &rates_list);

    return 0;
}

void Admin_login(admin ** admin_list,card ** cards_list, jifei ** rates_list)
{
    char id[11];
    char pass[17];
    if (!*admin_list)
    {
        system("cls");
        puts("????????һ????????ϵͳ?????ȣ?????һ??????Ա?˺Űɡ?");
        puts("?´?????ϵͳʱ??????Ҫʹ??????????Ա?˺ŵ?¼??");
        puts("????????Ա?˺Ž????г???????ԱȨ?ޣ???ӵ?????ӡ?ɾ??????Ա??Ȩ?ޡ?");
        printf("???????˺ŵ??û?????");
        scanf("%s", id);
        printf("???룺");
        scanf("%s", pass);
        *admin_list = (admin *)malloc(sizeof(admin));
        (*admin_list)->next = NULL;
        (*admin_list)->status = 1;
        strcpy((*admin_list)->username, id);
        strcpy((*admin_list)->password, pass);
        puts("ע?????ɣ?");
        system("pause");
    }
    while (1)
    {
        system("cls");
        puts("??????????Ա?˺??Լ???????¼ϵͳ??");
        printf("?û?????");
        scanf("%s", id);
        printf("???룺");
        scanf("%s", pass);
        admin * current = *admin_list;
        while (current)
        {
            if (!strcmp(current->username, id))
            {
                if (!strcmp(current->password, pass))
                {
                    puts("??¼?ɹ???");
                    system("pause");
                    if (!Panel(current->status, admin_list, cards_list, rates_list))
                        return;
                }
                else {
                    puts("?û????????벻??Ӧ??");
                    system("pause");
                }
                break;
            }
            current = current->next;
        }
        if (!current)
        {
            puts("?????ڴ??˺ţ?");
            system("pause");
        }
    }
}

bool Panel(int super, admin ** admin_list, card ** cards_list, jifei ** rates_list)
{
    while (1)
    {
        system("cls");
        puts("===== ?????շѹ???ϵͳ =====");
        puts("=      1. ??????           =");
        puts("=      2. ?Ʒѱ?׼????     =");
        puts("=      3. ?Ʒѹ???         =");
        puts("=      4. ???ù???         =");
        puts("=      5. ??ѯͳ??         =");
        puts("=      6. ?ǳ??˺?         =");
        if (super)
            puts("=      7. Ȩ?޹???         =");
        puts("=      0. ?˳?             =");
        puts("============================");
        puts("????????Ӧѡ???????ţ?");
        switch (getch())
        {
        case '1':
            Card_management(cards_list);
            break;
        
        case '2':
            Charging_rule(rates_list);
            break;
        
        case '3':
            Charging_management(rates_list, *cards_list);
            break;
        
        case '4':
            Cost_management(cards_list);
            break;
        
        case '5':
            Statistics(cards_list);
            break;

        case '6':
            puts("?ǳ??ɹ???");
            system("pause");
            return true;

        case '7':
            if (super)
            {
                Permission_management(admin_list);
                break;
            }
            else
                break;

        case '0':
            Save_file(*admin_list, *cards_list, *rates_list);
            return false;

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
        puts("======= ?????? ========");
        puts("=      1. ???ӿ?      =");
        puts("=      2. ??ѯ??      =");
        puts("=      3. ע????      =");
        puts("=  0. ??????һ???˵?  =");
        puts("=======================");
        puts("????????Ӧѡ???????ţ?");
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

void Charging_management(jifei ** rates_list, card * cards_list)
{
    while (1)
    {
        system("cls");
        puts("====== ?Ʒѹ??? =======");
        puts("=      1. ?ϻ?        =");
        puts("=      2. ?»?        =");
        puts("=  0. ??????һ???˵?  =");
        puts("=======================");
        puts("????????Ӧѡ???????ţ?");
        switch (getch())
        {
            case '1':
                Go_online(rates_list, cards_list);
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
        puts("====== Ȩ?޹??? =======");
        puts("=   1. ???ӹ???Ա     =");
        puts("=   2. ɾ??????Ա     =");
        puts("=  0. ??????һ???˵?  =");
        puts("=======================");
        puts("????????Ӧѡ???????ţ?");
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

void Charging_rule(jifei ** rates_list)
{
    while (1)
    {
        system("cls");
        puts("===== ?Ʒѱ?׼???? ======");
        puts("=   1. ?????Ʒѱ?׼     =");
        puts("=   2. ??ѯ?Ʒѱ?׼     =");
        puts("=   3. ɾ???Ʒѱ?׼     =");
        puts("=   4. ?޸ļƷѱ?׼     =");
        puts("=   0. ??????һ???˵?   =");
        puts("=========================");
        puts("????????Ӧѡ???????ţ?");
        switch (getch())
        {
            case '1':
                creatstandard(rates_list);
                break;
            
            case '2':
                inquire(rates_list, 0);
                break;
            
            case '3':
                delete(rates_list);
                break;
            
            case '4':
                change(rates_list);
                break;
            
            case '0':
                return;

            default:
                break;
        }
    }
}

void Cost_management(card ** cards_list)
{
    while (1)
    {
        system("cls");
        puts("====== ???ù??? =======");
        puts("=      1. ??ֵ        =");
        puts("=      2. ?˷?        =");
        puts("=  0. ??????һ???˵?  =");
        puts("=======================");
        puts("????????Ӧѡ???????ţ?");
        switch (getch())
        {
            case '1':
                recharge(cards_list);
                break;
            
            case '2':
                returnmoney(cards_list);
                break;
            
            case '0':
                return;

            default:
                break;
        }
    }
}

void Statistics(card ** cards_list)
{
    while (1)
    {
        system("cls");
        puts("======== ??ѯͳ?? =========");
        puts("=    1. ??ѯ???Ѽ?¼      =");
        puts("=    2. ͳ????Ӫҵ??      =");
        puts("=    3. ͳ????Ӫҵ??      =");
        puts("=    0. ??????һ???˵?    =");
        puts("===========================");
        puts("????????Ӧѡ???????ţ?");
        switch (getch())
        {
            case '1':
                record_card(cards_list);
                break;
            
            case '2':
                totalmoney(cards_list);
                break;      
            
            case '3':
                total_turnover(cards_list);
                break;
            
            case '0':
                return;

            default:
                break;
        }
    }
}

void Save_file(admin * admin_list, card * cards_list, jifei * rates_list)
{
    FILE * file = fopen("data/card.txt", "w");
    while (cards_list)
    {
        fprintf(file, "%d %s %s %lf %ld %lf %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", cards_list->status, cards_list->id, cards_list->pass, cards_list->balance, cards_list->start_time, cards_list->cost_per_hour, \
        cards_list->times[0], cards_list->times[1], cards_list->times[2], cards_list->times[3], cards_list->times[4], cards_list->times[5], cards_list->times[6], cards_list->times[7], cards_list->times[8], cards_list->times[9], cards_list->times[10], cards_list->times[11], \
        cards_list->countmoney[0], cards_list->countmoney[1], cards_list->countmoney[2], cards_list->countmoney[3], cards_list->countmoney[4], cards_list->countmoney[5], cards_list->countmoney[6], cards_list->countmoney[7], cards_list->countmoney[8], cards_list->countmoney[9], cards_list->countmoney[10], cards_list->countmoney[11]);
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

    file = fopen("data/rate.txt", "w");
    while (rates_list)
    {
        fprintf(file, "%d %d", rates_list->time, rates_list->money);
        jifei * temp = rates_list;
        rates_list = rates_list->next;
        if (rates_list)
            fputc(' ', file);
        free(temp);
    }
    fclose(file);
}