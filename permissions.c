#include "requirements.h"
#include "admin.h"

void Add_admin(admin ** admin_list)
{
    system("cls");
    char username[11];
    printf("输入新管理员的用户名：");
    scanf("%s", username);
    admin * current = * admin_list;
    admin * temp = current;
    while (current)
    {
        if (!strcmp(username, current->username))
        {
            puts("该用户名已存在！");
            system("pause");
            return;
        }
        temp = current;
        current = current->next;
    }
    current = temp;
    temp = (admin *)malloc(sizeof(admin));
    strcpy(temp->username, username);
    printf("输入新管理员的密码：");
    scanf("%s", temp->password);
    puts("请配置该管理员的权限：");
    puts("1. 普通管理员");
    puts("2. 超级管理员（可配置权限）");
    while (1)
    {
        switch (getch())
        {
            case '1':
                temp->status = 0;
                break;
            
            case '2':
                temp->status = 1;
                break;
            
            default:
                continue;
        }
        break;
    }
    temp->next = NULL;
    current->next = temp;
    puts("添加完成！");
    system("pause");
}

void Del_Admin(admin ** admin_list)
{
    system("cls");
    char username[11];
    printf("输入要删除管理员的用户名：");
    scanf("%s", username);
    admin * current = * admin_list;
    admin * prev = current;
    while (current)
    {
        if (!strcmp(username, current->username))
        {
            prev->next = current->next;
            free(current);
            puts("删除完成！");
            system("pause");
            return;
        }
        prev = current;
        current = current->next;
    }
    puts("没有符合此用户名的管理员。");
    system("pause");
}