/*
 * task_2.c — программа, 
 * позволяющая проверить, что дочерний и родительский процессы совместно используют текущую позицию файла
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
	    fprintf (stderr, "Использование: ./task_2 программа\n");
	    exit(EXIT_FAILURE);
    }

    int file = open(argv[1], O_WRONLY);
    pid_t pid = fork();
    int position;

    /* Проверка открытия файла */
    if (file == -1){
	    fprintf (stderr, "Невозможно открыть файл для записи %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* Вызов функции fork */
    if((pid) < 0){
        fprintf (stderr, "Ошибка создания нового процесса fork\n");
	    exit(EXIT_FAILURE);
    } else if (pid == 0){
        /* Явное изменение текущей позиции в файле. От начала файла. */
        position = lseek(file, 10, SEEK_SET);
        if (position == -1){
            fprintf (stderr, "Ошибка изменения текущей позиции в файле lseek\n");
    	    exit(EXIT_FAILURE);
		}
        printf("Позиция в дочернем процессе == %d\n", position);
	} else {
        /* waitpid ожидает смену состояния процесса */
	    if (waitpid(pid, NULL, 0) < 0) {
            fprintf (stderr, "Ошибка вызова функции waitpid\n");
            exit(EXIT_FAILURE);
	    }
        /* Явное изменение текущей позиции в файле. от текущей позиции в файле. */
        position = lseek(file, 0, SEEK_CUR);
	    if (position == -1){
            fprintf (stderr, "Ошибка изменения текущей позиции в файле lseek\n");
    	    exit(EXIT_FAILURE);
	    }
	    printf("Позиция в родительском процессе == %d\n", position);
    } 

    if (close(file) < 0){
	    fprintf (stderr, "Ошибка закрытия файла");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/*
 * Материалы:
 * Листинг 8.1. Пример работы с функцией fork // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 * Совместное использование файлов // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 * 8.14. Учет использования ресурсов процессами // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
 * Листинг 8.17. Вывод учетной информации из системного файла учетных данных // UNIX. Профессиональное программирование. URL: https://www.rulit.me/data/programs/resources/pdf/UNIX-Professionalnoe-programmirovanie_RuLit_Me_609965.pdf (дата обращения: 20.11.2022).
*/
