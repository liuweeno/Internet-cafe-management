typedef struct jifei
{
    int time;
    int money;
    struct jifei *next;
}jifei;

void creatlink(jifei **head,FILE *file);
int inquire(jifei **head, int silent);
void creatstandard(jifei **head);
void delete(jifei **head);
void change(jifei **head);