/*
 * task_3.c — программа - пример использования функции system()
 *
 * Copyright (c) <2022> <Гордеев Никита>
 * 
 * This code is licensed under a MIT-style license.
 */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "apue.h"

int main(int argc, char **argv)
{
    int status;

    /* Вызов строки с датой и временем */
    if ((status = system("date")) < 0){
        fprintf (stderr, "Ошибка вызова функции system()");
        exit(EXIT_FAILURE);
    }
    printf("Cтатус завершения %d\n", status);

    return 0;
}

/*
 * Материалы:
 * 8.13. Функция system // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 * Листинг 8.13. Вызов функции system // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 */
