#include "minishell.h"
#include "libft/includes/libft.h"
#include "libft/includes/ft_printf.h"
/*
>>> access <<<

#include <unistd.h>

int access(const char *pathname, int mode);
access проверяет, имеет ли процесс права на чтение или запись, или же просто проверяет, существует ли файл (или другой объект файловой системы), с именем pathname. Если pathname является символьной ссылкой, то проверяются права доступа к файлу, на который она ссылается.
mode -- это маска, состоящая из одного или более флагов R_OK, W_OK, X_OK и F_OK.

R_OK, W_OK и X_OK запрашивают соответственно проверку существования файла и возможности его чтения, записи или выполнения. F_OK просто проверяет существование файла.
В случае успеха возвращается ноль. При ошибке возвращается -1, а errno устанавливается должным образом.
*/

/*
>>> getcwd <<<

#include <unistd.h>

char *getcwd(char *buf, size_t size);
*/
/*
>>> chdir <<<

int chdir(const char *path); 
chdir изменяет текущий каталог каталог на path.
В случае успеха возвращается ноль. При ошибке возвращается -1, а errno устанавливается должным образом.
*/
/*
>>> fork <<<

#include <sys/types.h> 
#include <unistd.h>
pid_t fork(void);  

fork создает процесс-потомок, который отличается от родительского только значениями PID (идентификатор процесса) и PPID (идентификатор родительского процесса), а также тем фактом, что счетчики использования ресурсов установлены в 0. Блокировки файлов и сигналы, ожидающие обработки, не наследуются.
При успешном завершении родителю возвращается PID процесса-потомка, а процессу-потомку возвращается 0. При неудаче родительскому процессу возвращается -1, процесс-потомок не создается, а значение errno устанавливается должным образом.  
*/

int		main(int argc, char **argv, char ** envp)
{
	int i = 1;
	char *buf;
	char *buf1;
	int ret;


	buf = getcwd(buf, 0);
	ft_printf("%s\nchanging to %s..\n", buf, argv[1]);
	free (buf);
	buf = NULL;

	chdir(argv[1]);
	buf = getcwd(buf, 0);
	ft_printf("%s\n", buf);
	while (*envp)
	{
		if (ft_strnequ("PWD", *envp, 3))
		{
			buf1 = ft_strjoin("PWD=", buf);
			*envp = buf1;
		}
		envp++;
	}
	free (buf);
	buf = NULL;
/*
	chdir("..");
	buf = getcwd(buf, 0);
	ft_printf("%s\n", buf);
	if (buf)
		free(buf);*/
	if (argc > 1)
	{
		while (i < argc)
		{
			ft_printf("> %s %s", argv[i], ((ret = access(argv[i], F_OK))  == 0) ? "OK\n" : "FAIL. ");
			if (ret < 0)
				perror("access");
			i++;
		}
	}
else
	ft_printf("enter filepath\n");
//system("leaks minishell");
	return 0;
}