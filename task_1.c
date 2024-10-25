/*
 * task_1.c — программа, 
 * которая запускает в дочернем процессе другую программу, путь к файлу которой задается аргументом командной строки, 
 * а также выводит в стандартный поток вывода информацию о статусе завершения этой программы. 
 * 
 * Использованы:
 * 1) функции fork(), execl(), waitpid() 
 * 2) макроопределения WIFEXITED(), WEXITSTATUS(), WIFSIGNALED(), WTERMSIG().
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

int main(int argc, char **argv)
{
    /* Проверка на наличие аргументов */
    if (argc != 2) {
	    fprintf (stderr, "Использование: ./task_1 программа\n");
	    exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    int status;

    /* Вызов функции fork */
    if((pid) < 0){
        fprintf (stderr, "Ошибка создания нового процесса fork\n");
	    exit(EXIT_FAILURE);
    } 

    /* Запуск новой программы */
    if (pid == 0) {
        if (execl(argv[1], argv[1], NULL) < 0){
            fprintf (stderr, "Ошибка запуска новой программы exec\n");
	        exit(EXIT_FAILURE);
        }
    } 
    
    /* waitpid ожидает смену состояния процесса */
    if (waitpid(pid, &status, 0) < 0){
        fprintf (stderr, "Ошибка вызова функции waitpid\n");
        exit(EXIT_FAILURE);
    }

    /* WIFEXITED возвращает true, если код status получен в результате нормального завершения дочернего процесса. 
     * WIFSIGNALED возвращает true, если код status получен в результате аварийного завершения дочернего процесса из-за сигнала, который не был перехвачен.
     * WEXITSTATUS возвращает младшие 8 бит из аргумента, который был передан функции exit. */
   if (WIFEXITED(status)) {
        printf("Процесс завершился с кодом %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)){ 
        printf("Выполнение процесса было прервано сигналом: %d\n", WTERMSIG(status));
    } else if (WEXITSTATUS(status)){ 
        printf("Процесс завершился аварийно \n");
    }

    return 0;

}

/*
 * Материалы:
 * 8.3. Функция fork // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 * 8.4. Функция vfork // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 * 8.5. Функции exit // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 * 8.6. Функции wait и waitpid // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 * 8.7. Функция waitid // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 * Таблица 8.1. Макроопределения для проверки кода завершения, возвращаемого функциями wait и waitpid // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 * Листинг 8.3. Вывод сведений, полученных из кода завершения // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 * waitpid (2) // OpenNET URL: https://www.opennet.ru/man.shtml?topic=waitpid&category=2&russian=0 (дата обращения: 20.11.2022).
 * 8.10. Функции exec // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
*/
