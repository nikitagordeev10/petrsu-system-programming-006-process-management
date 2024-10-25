/*
 * task_4.c — программа аналог функции execlp() (запуск файла на исполнение) 
 * без использования других функций exec*p().
 * 
 * Copyright (c) <2022> <Гордеев Никита>
 * 
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <linux/limits.h>

/* запуск файла на исполнение */
int my_execlp(const char *);

int main(int argc, char *argv[]) {
    /* проверяем кол-во аргументов */
    if (argc < 2) {
	    fprintf (stderr, "Использование: ./task_4 test\n");
        exit(EXIT_FAILURE);
    }

    /* клонируем процесс */
    pid_t pid;
    int status;
    if ((pid = fork()) < 0) {
        perror("Ошибка функции fork()");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* В дочернем процессе запускаем функцию my_execlp */
        if (my_execlp(argv[1]) == -1) {
            exit(EXIT_FAILURE);
        }
    } else {
        /* Ожидаем завершения дочернего процесса */
        if (waitpid(pid, &status, 0) == -1) {
            perror("Ошибка функции waitpid()");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

/* запуск файла на исполнение */
int my_execlp(const char *file) {

    /* составляем путь к файлу */
    int pos = 0;
    char buf[PATH_MAX] = "";
    strcat(buf, file);

    /* если файл существует, прерываем цикл */
    if (execl(buf, buf, NULL) != -1)
        return 0;
    
    /* иначе в имени программы ошибка */
    char *path;
    
    /* получаем переменную PATH */
    if ((path = getenv("PATH")) == NULL) {
        perror("Ошибка вызова getenv()");
        return -1;
    }

    /* ищем имя программы */
    long len = strlen(path);
    for (long ch = 0; ch <= len; ch++) {
        /* делим PATH по двоеточиям */
        if (path[ch] == ':') {
            /* Составляем путь к файлу */
            strcat(buf, "/");
            strcat(buf, file);
            /* и пытаемся запустить */
            if (execl(buf, buf, NULL) != -1) break;
            memset(buf, 0, PATH_MAX);
            pos = 0;
        } else {
            buf[pos] = path[ch];
            pos++;
        }
    }

    /* если программа не была найдена и запущена, то выводим ошибку */
    printf("Файл программы не найден\n");
    return -1;
}

/*
 * Материалы:
 * Идея аналога exec // cyberforum URL: https://www.cyberforum.ru/cpp-beginners/thread2867939.html (дата обращения: 20.11.2022).
 * Аналог явовского exec()-а в С ? // ixbt конференция URL: https://forum.ixbt.com/topic.cgi?id=26:8929 (дата обращения: 21.11.2022).
 * Листинг 8.8. Пример использования функций exec // UNIX. Профессиональное программирование. 3-е изд. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 21.11.2022).
 * 8.13. Функция system // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 * Листинг 8.13. Вызов функции system // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 * execl, execle, execlp, execlpe, execv, execve, execvp, execvpe // Программирование на C и C++ URL: http://www.c-cpp.ru/content/execl-execle-execlp-execlpe-execv-execve-execvp-execvpe (дата обращения: 20.11.2022).
 * Unix2017b/Техника fork — exec // iRunner Wiki URL: https://acm.bsu.by/wiki/Unix2017b/Техника_fork_—_exec (дата обращения: 21.11.2022).
 * Функция strchr // CppStudio URL: http://cppstudio.com/post/726/ (дата обращения: 21.11.2022).
 * Функция strlen // CppStudio URL: http://cppstudio.com/post/664/ (дата обращения: 21.11.2022).
 * Функция getenv // CppStudio URL: http://cppstudio.com/post/879/ (дата обращения: 21.11.2022).
 */
