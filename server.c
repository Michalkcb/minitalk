/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:15:58 by mbany             #+#    #+#             */
/*   Updated: 2024/10/16 17:52:35 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static int		bits = 0;
	static char		character = 0;

	(void)context;
	if (signum == SIGUSR1)
		character |= (1 << bits);
	bits++;
	if (bits == 8)
	{
		if (character == '\0')
			kill(info->si_pid, SIGUSR1);
		write(1, &character, 1);
		bits = 0;
		character = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("Server PID: ");
	ft_putnbr(getpid());
	ft_putstr("\n");
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr("Error setting up signal handlers.\n");
		return (EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr("Error setting up signal handlers.\n");
		return (EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}
