#include "requirements.h"

typedef struct Admins
{
    int status; //0 for admin, 1 for super admin.
    char username[11];
    char password[17];
    struct Admins * next;
} admin;

void Add_admin(admin ** admin_list);
void Del_Admin(admin ** admin_list);