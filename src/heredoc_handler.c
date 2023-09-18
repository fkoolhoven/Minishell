/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   heredoc_handler.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: jhendrik <marvin@42.fr>                     +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/09/13 13:05:59 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/09/18 15:00:26 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*st_give_filename(const char *s_nb1, int j)
{
	const char	*tmp;
	char		*filename;
	const char	*s_nb2;

	if (s_nb1 == NULL)
		return (NULL);
	s_nb2 = (const char *)ft_itoa_base(j, 16, "0123456789ABCDEF");
	if (s_nb2 == NULL)
		return (free(s_nb1), NULL);
	tmp = (const char *)ft_strjoin((const char *)"HEREDOC", s_nb1);
	free(s_nb1);
	if (tmp == NULL)
		return (free(s_nb2), NULL);
	filename = ft_strjoin(tmp, s_nb2);
	free(s_nb2);
	free(tmp);
	return (filename);
}

/* The function below has some problems,
   			1.	It does not add the input given for the heredoc 
				to the working history, and you can't just use 
				add_history(user_input) because it will become a 
				seperate entry, which is not how bash handles history with
				heredocs 
			2.	If control+D is used bash gives a warning because the
				heredoc has been ended without using the given delimiter
				... This probably has something to do with signals and signal 
				handling, still have to look into this because the function now
				just stops adding to the heredoc and the other functions using 
				it will go on to check for the other heredocs
			3.	If writing in the function ft_putstr_fd() goes wrong,
				we do not protect for this in this function 
				However, it seems a good idea to look into this again and
				to protect this function against write failures
			4.	Doesn't handle the following cases :
						
					<< EOF cat
						> hello
						> $USER
						> $(USER)
						> \$USER
						> $ USER
						> \$ USER
						> '$USER'
						> "$USER"
						> hello
						> EOF
					USER: command not found
					hello
					jhendrik

					$USER
					$ USER
					$ USER
					'jhendrik'
					"jhendrik"
					hello

	NOTE:
			1.	The function readline gives a string without newline,
				This means that when using heredoc you need to add the
				newline to the temporary file.
				If you doubt, try : 	<< EOF wc -l + own input
										<< EOF << eof wc -l + own input
   */
static void	st_input_to_heredoc(int fd, char *limit)
{
	char	*user_input;
	int		i;

	i = 1;
	while (i == 1)
	{
		user_input = readline(">");
		if (!(user_input))
			i = -1;
		else if (ft_strncmp(user_input, limit, ft_strlen(user_input)) == 0)
			i = 0;
		else
		{
			ft_putstr_fd(user_input, fd);
			ft_putstr_fd("\n", fd);
		}
		free(user_input);
	}
}
/* This function has some problems:
   			1.	It uses the function st_input_to_heredoc, which has problems
			2.	Assumes that node->value is allocated using malloc ...?

   */
static void	st_manage_one_heredoc(char *filename, t_redirect *node)
{
	char	*limit;
	int		fd_heredoc;

	if (filename != NULL && node != NULL)
	{
		fd_heredoc = open(filename, O_CREAT | O_RDWR | O_EXCL, 0644);
		if (fd_heredoc >= 0)
		{
			limit = node->value;
			st_input_to_heredoc(fd_heredoc, limit);
			close(fd_heredoc);
			node->type = HEREDOC_INFILE;
			free(node->value);
			node->value = filename;
		}
		else 
		{
			free(filename);
			node->type = HEREDOC_FAIL;
		}
	}
	else
		node->type == HEREDOC_FAIL;
}

static void	st_check_manage_heredocs(t_redirect *in, int i)
{
	int			j;
	t_redirect	*tmp;
	char		*filename;
	const char	*s_nb1;

	if (in != NULL)
	{
		tmp = in;
		s_nb1 = (const char *)ft_itoa_base(i, 16, "0123456789ABCDEF");
		j = 0;
		while (tmp != NULL)
		{
			if (tmp->type == HEREDOC)
			{	
				filename = st_give_filename(s_nb1, j);
				if (filename != NULL)
					st_manage_one_heredoc(filename, tmp);
				else
					tmp->type = HEREDOC_FAIL;
				j++;
			}
			tmp = tmp->next;
		}
	}
}

/* manage_heredocs():
   		Gaat alle commands in de command_list af opzoek naar
		of de input flow heredocs bevat
		Als er een input flow is (ofwel input != NULL)
		wordt het doorgestuurd naar st_check_manage_heredocs()
		die gaat de hele input flow lijst af om voor heredocs te checken
		Als die een heredoc tegenkomt, zorgt die ervoor dat er een unieke
		file name gemaakt wordt voor de tijdelijke heredoc file en dat hier input inkomt
		Wanneer dat gedaan is wordt het type veranderd naar HEREDOC_INFILE of HEREDOC_FAIL,
		afhankelijk van of het gelukt is 
		Als het type HEREDOC_INFILE is, dan is de value veranderd naar de unieke filename,
		PAS OP !!!! 	---> 	de filename is apart gealloceerd, dit betekent dat deze later
								gefreed moet worden!!!

   */

int	manage_heredocs(t_command *command_list)
{
	t_command	*tmp;
	int			i;

	if (command_list == NULL)
		return (1);
	tmp = command_list;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->in != NULL)
		{
			st_check_manage_heredocs(tmp->in, i);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
