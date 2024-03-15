/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:29:14 by amolbert          #+#    #+#             */
/*   Updated: 2024/03/13 16:52:27 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

int	main()
{
	char	*result;

	result = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while ((result = readline("> ")))
	{
		printf("%s\n", result);
		add_history(result);
		free(result);
	}	
	return (0);
}
