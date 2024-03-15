/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_wait.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-la-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:01:57 by tde-la-r          #+#    #+#             */
/*   Updated: 2024/03/04 12:08:21 by tde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>

void	error(char *err)
{
	perror(err);
	exit (1);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t			pid;
	struct rusage	data;

	(void) argc;
	pid = fork();
	if (pid == -1)
		error("fork");
	if (!pid)
	{
		execve(argv[1], argv + 1, envp);
		error("execve");
	}
	if (wait4(pid, NULL, 0, &data) == -1)
		error("wait4");
	printf("user CPU time used : ");
	printf("seconds : %ld ", data.ru_utime.tv_sec);
	printf("nanoseconds : %ld\n", data.ru_utime.tv_usec);
	printf("system CPU time used : ");
	printf("seconds : %ld ", data.ru_stime.tv_sec);
	printf("nanoseconds : %ld\n", data.ru_stime.tv_usec);
	printf("max resident set size : %ld\n", data.ru_maxrss);
	printf("integral shared memory size : %ld\n", data.ru_ixrss);
	printf("integral unshared data size: %ld\n", data.ru_idrss);
	printf("integral unshared stack size : %ld\n", data.ru_isrss);
	printf("page reclaims (soft page faults) : %ld\n", data.ru_minflt);
	printf("page faults (hard page faults) : %ld\n", data.ru_majflt);
	printf("swaps : %ld\n", data.ru_nswap);
	printf("block input operations : %ld\n", data.ru_inblock);
	printf("block output operations : %ld\n", data.ru_oublock);
	printf("IPC messages sent : %ld\n", data.ru_msgsnd);
	printf("IPC messages received : %ld\n", data.ru_msgrcv);
	printf("signals received : %ld\n", data.ru_nsignals);
	printf("voluntary context switches : %ld\n", data.ru_nvcsw);
	printf("involuntary context switches : %ld\n", data.ru_nivcsw);
}
