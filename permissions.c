#include "requirements.h"
#include "admin.h"

void Add_admin(admin ** admin_list)
{
    system("cls");
    char username[11];
    printf("�����¹���Ա���û�����");
    scanf("%s", username);
    admin * current = * admin_list;
    admin * temp = current;
    while (current)
    {
        if (!strcmp(username, current->username))
        {
            puts("���û����Ѵ��ڣ�");
            system("pause");
            return;
        }
        temp = current;
        current = current->next;
    }
    current = temp;
    temp = (admin *)malloc(sizeof(admin));
    strcpy(temp->username, username);
    printf("�����¹���Ա�����룺");
    scanf("%s", temp->password);
    puts("�����øù���Ա��Ȩ�ޣ�");
    puts("1. ��ͨ����Ա");
    puts("2. ��������Ա��������Ȩ�ޣ�");
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
    puts("�����ɣ�");
    system("pause");
}

void Del_Admin(admin ** admin_list)
{
    system("cls");
    char username[11];
    printf("����Ҫɾ������Ա���û�����");
    scanf("%s", username);
    admin * current = * admin_list;
    admin * prev = current;
    while (current)
    {
        if (!strcmp(username, current->username))
        {
            prev->next = current->next;
            free(current);
            puts("ɾ����ɣ�");
            system("pause");
            return;
        }
        prev = current;
        current = current->next;
    }
    puts("û�з��ϴ��û����Ĺ���Ա��");
    system("pause");
}