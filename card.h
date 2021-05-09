#include "requirements.h"

struct jifei;
typedef struct Cards
{
    int status;
    // 0 means offline, 1 means online, 2 means defaulting, 3 means cancelled
    char id[11];
    char pass[17];
    double balance;
    time_t start_time;
    double cost_per_hour;
    int times[12];
    int countmoney[12];
    struct Cards * next;
} card;

void Add_card(card ** fuckme);
void Cancel_card(card * fuckme);
void Query_card(card * fuckme);
void Go_online(struct jifei ** rates_list, card * card_list);
void Go_offline(card * card_list);
void recharge(card **head);
void returnmoney(card **head);
void record_card(card **head);
void totalmoney(card **head);
void total_turnover(card **head);