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
    puts("加载数据中……");
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
        puts("这是你第一次启动本系统。首先，创建一个管理员账号吧。");
        puts("下次启动系统时，你需要使用这个管理员账号登录。");
        puts("这个管理员账号将具有超级管理员权限，即拥有添加、删除管理员的权限。");
        printf("请输入账号的用户名：");
        scanf("%s", id);
        printf("密码：");
        scanf("%s", pass);
        *admin_list = (admin *)malloc(sizeof(admin));
        (*admin_list)->next = NULL;
        (*admin_list)->status = 1;
        strcpy((*admin_list)->username, id);
        strcpy((*admin_list)->password, pass);
        puts("注册完成！");
        system("pause");
    }
    while (1)
    {
        system("cls");
        puts("请输入管理员账号以及密码登录系统。");
        printf("用户名：");
        scanf("%s", id);
        printf("密码：");
        scanf("%s", pass);
        admin * current = *admin_list;
        while (current)
        {
            if (!strcmp(current->username, id))
            {
                if (!strcmp(current->password, pass))
                {
                    puts("登录成功！");
                    system("pause");
                    if (!Panel(current->status, admin_list, cards_list, rates_list))
                        return;
                }
                else {
                    puts("用户名与密码不对应！");
                    system("pause");
                }
                break;
            }
            current = current->next;
        }
        if (!current)
        {
            puts("不存在此账号！");
            system("pause");
        }
    }
}

bool Panel(int super, admin ** admin_list, card ** cards_list, jifei ** rates_list)
{
    while (1)
    {
        system("cls");
        puts("===== 网吧收费管理系统 =====");
        puts("=      1. 卡管理           =");
        puts("=      2. 计费标准管理     =");
        puts("=      3. 计费管理         =");
        puts("=      4. 费用管理         =");
        puts("=      5. 查询统计         =");
        puts("=      6. 登出账号         =");
        if (super)
            puts("=      7. 权限管理         =");
        puts("=      0. 退出             =");
        puts("============================");
        puts("请输入对应选项的序号：");
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
            puts("登出成功！");
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
        puts("======= 卡管理 ========");
        puts("=      1. 添加卡      =");
        puts("=      2. 查询卡      =");
        puts("=      3. 注销卡      =");
        puts("=  0. 返回上一级菜单  =");
        puts("=======================");
        puts("请输入对应选项的序号：");
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
        puts("====== 计费管理 =======");
        puts("=      1. 上机        =");
        puts("=      2. 下机        =");
        puts("=  0. 返回上一级菜单  =");
        puts("=======================");
        puts("请输入对应选项的序号：");
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
        puts("====== 权限管理 =======");
        puts("=   1. 添加管理员     =");
        puts("=   2. 删除管理员     =");
        puts("=  0. 返回上一级菜单  =");
        puts("=======================");
        puts("请输入对应选项的序号：");
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
        puts("===== 计费标准管理 ======");
        puts("=   1. 新增计费标准     =");
        puts("=   2. 查询计费标准     =");
        puts("=   3. 删除计费标准     =");
        puts("=   4. 修改计费标准     =");
        puts("=   0. 返回上一级菜单   =");
        puts("=========================");
        puts("请输入对应选项的序号：");
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
        puts("====== 费用管理 =======");
        puts("=      1. 充值        =");
        puts("=      2. 退费        =");
        puts("=  0. 返回上一级菜单  =");
        puts("=======================");
        puts("请输入对应选项的序号：");
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
        puts("======== 查询统计 =========");
        puts("=    1. 查询消费记录      =");
        puts("=    2. 统计总营业额      =");
        puts("=    3. 统计月营业额      =");
        puts("=    0. 返回上一级菜单    =");
        puts("===========================");
        puts("请输入对应选项的序号：");
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