/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:09:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/12 18:41:19 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_error(char *str, pid_t pid)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
	kill(pid, SIGUSR2);
	exit(1);
}

/* if the buffer is full, it displays it and empties it */

static void	handle_buffer(char *buffer, int *i)
{
	if (*i == 4097)
	{
		buffer[*i] = 0;
		ft_putstr_fd(buffer, 1);
		*i = 0;
	}
}

/* decode the message, send confirmation of the reception to the client
 and display the string */

static void	receive_str(int signum, siginfo_t *info, void *x)
{
	static int	i_bit = 0;
	static char	byte = 0;
	static char	buffer[4098];
	static int	i = 0;

	if (signum == SIGUSR2)
		byte += 1 << i_bit;
	++i_bit;
	if (i_bit >= 8)
	{
		buffer[i++] = byte;
		if (!byte)
		{
			ft_putstr_fd(buffer, 1);
			i = 0;
		}
		else
			handle_buffer(buffer, &i);
		byte = 0;
		i_bit = 0;
	}
	// (void)info;
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_error("No such process.", info->si_pid);
	(void)x;
}

int	main(void)
{
	struct sigaction	s;

	s.sa_flags = SA_SIGINFO;
	s.sa_sigaction = receive_str;
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	if (sigaction(SIGUSR1, &s, NULL) < 0)
		return (1);
	if (sigaction(SIGUSR2, &s, NULL) < 0)
		return (1);
	while (1)
		pause();
	return (0);
}
