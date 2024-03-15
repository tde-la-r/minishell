/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 09:44:05 by amolbert          #+#    #+#             */
/*   Updated: 2024/03/06 10:46:07 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	free_exit(int sign, siginfo_t *info, void *context)
{
	(void)context;
	(void)sign;
	(void)info;
	printf("ok2\n");
	//exit(EXIT_SUCCESS);
	printf("ok3\n");
}

int	main()
{
	struct	sigaction	sa;
	
	printf("ok1\n");
	sa.sa_sigaction = &free_exit;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	while (1)
		continue ;
}
