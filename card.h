#include "requirements.h"

typedef struct Cards
{
    int status;
    // 0 means offline, 1 means online, 2 means defaulting, 3 means cancelled
    char id[11];
    char pass[17];
    double balance;
    time_t start_time;
    double cost_per_hour;
    struct Cards * next;
} card;

void Add_card(card ** fuckme);
void Cancel_card(card * fuckme);
void Query_card(card * fuckme);
void Go_online(card * card_list);
void Go_offline(card * card_list);