#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user
{
    char msg[140];
    char name[40];
    int len;
};

void    secret_backdoor()
{
    char    buf[128];
    fgets(buf, 128, stdin);
    system(buf);
}

void set_username(struct user *user)
{
    char buf[128];
    puts(">: Enter your username");
    printf(">>: ");
    fgets(buf, 128, stdin);
    // if write more than 40 char, rewrite len
    for (int i = 0; i <= 40 && buf[i]; i++)
        user->name[i] = buf[i];
    printf(">: Welcome, %s", user->name);
}

void set_msg(struct user *user)
{
    char buf[1024];

    puts("Message @Unix-Dude");
    printf(">>: ");
    fgets(buf, 128, stdin);
    strncpy(user->msg, buf, user->len);
}

void handle_msg()
{
    struct user user = {.name = {}, .len = 140};
    set_username(&user);
    set_msg(&user);
    puts(">: Msg sent!");
}

int main()
{
    puts("--------------------------------------------\n"
         "|   ~Welcome to l33t-m$n ~    v1337        |\n"
         "--------------------------------------------");
    handle_msg();
}
