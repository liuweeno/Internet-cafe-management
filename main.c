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
                    if (!Panel(current->status, admin_list, cards_list))
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

int Panel(int super, admin ** admin_list, card ** cards_list)
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

            break;
        
        case '3':
            Charging_management(*cards_list);
            break;
        
        case '4':

            break;
        
        case '5':

            break;

        case '6':
            puts("登出成功！");
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

void Charging_management(card * cards_list)
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