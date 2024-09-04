#include "minishell.h"

void	heredoc_in(char *str_cmd, t_token **tok, int *i)
{
	if (str_cmd[*i + 1] == '<')
	{
		create_list(HEREDOC, tok, ft_strdup("<<"));
		*i += 2;
	}
	else
	{
		create_list(IN, tok, ft_strdup("<"));
		*i += 1;
	}
}

void	append_out(char *str_cmd, t_token **tok, int *i)
{
	if (str_cmd[*i + 1] == '>')
	{
		create_list(APPEND, tok, ft_strdup(">>"));
		*i += 2;
	}
	else
	{
		create_list(OUT, tok, ft_strdup(">"));
		*i += 1;
	}
}

void	print_banner()
{
    int fd;
    ssize_t bytes_read;
    char buffer[1024];

    fd = open("init", O_RDONLY);
    if (fd == -1) {
        perror("Error opening banner file");
        return;
    }

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0'; // Null-terminate the buffer
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1) {
        perror("Error reading banner file");
    }

    close(fd);
}
