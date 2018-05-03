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

char	*get_env(char *needle, char **envp)
{
//	printf("---> %s\n", __FUNCTION__);
	char	*res;
	size_t	len;

	len = ft_strlen(needle);
	while (*envp != NULL)
	{
		if (ft_strnequ(needle, *envp, len))
		{
			res = ft_strsub(*envp, len + 1, ft_strlen(*envp));
			//printf("%s: %s\n", __FUNCTION__, res);
			return (res);
		}
		envp++;
	}
	if (!res)
	{
		ft_printf("Environement element %s not found\n", needle);
		exit(0);
	}
	return (res);
}

int		main(int argc, char **argv, char ** envp)
{
	int i = 0;
	char *buf;
	char *buf1;
	int ret;
	char *dest;
	char *path;

	buf = getcwd(buf, 0);
	printf("%s\n", buf1);

	/*if (!argv[1])
		dest = get_env("HOME", envp);
	else
	{*/
	path = argv[1];
	printf("path %s\n", path);


	//argv[1] parsing

	char *tmp;
	int j = 0;

	while (/*path[i] != '/' &&*/ path[i])
	{
		printf(">> %s, path[%d] = '%c'\n", path, i, path[i]);
		if (path[i] == '~')
		{
			printf("~\n");
			tmp = get_env("HOME", envp);
			//dest = ft_strjoin(tmp, path + 1);
			//j += ft_strlen(tmp);
			ret = chdir(tmp);
			printf("~ %s\n", getcwd(buf, 0));
		}
		else if (path[i] == '.' && path[i+1] == '.')
		{
			printf("..\n");
			i += 2;
			tmp = getcwd(tmp, 0);
			j = ft_strlen(tmp) - 1;
			while (tmp[j] && tmp[j] != '/')
				j--;
			tmp = ft_strsub(tmp, 0, j);
			ret = chdir(tmp);
			printf(".. %s\n", getcwd(buf, 0));
		}
		else
		{
			printf("else\n");
			if (path[i]  == '/')
				i++;

			j = 0;
			while (path[i] && path[i] != '/')
				j++;
			tmp = ft_strsub(path, i, j);
			ret = chdir(tmp);
			i += j;
			printf("else %s\n", getcwd(buf, 0));
		}
		i++;
		sleep(1);
	}

//}
/*
ret = chdir(dest);
if (ret != 0)
{
	perror(dest);
	return (0);
}
*/
buf = getcwd(buf, 0);

printf("%s\n", buf);
	/*
	while (*envp)
	{
		if (ft_strnequ("PWD", *envp, 3))
		{
			buf1 = ft_strjoin("PWD=", buf);
			*envp = buf1;
		}
		envp++;
	}
	free (buf);*/
	//buf = NULL;
/*
	chdir("..");
	buf = getcwd(buf, 0);
	ft_printf("%s\n", buf);
	if (buf)
		free(buf);*/
	/*
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
	ft_printf("enter filepath\n");*/
//system("leaks minishell");
	return 0;
}