/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:09:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/08 15:59:48 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"
#include <sys/types.h> 
#include <unistd.h>
#include <signal.h>

void    test(int sig)
{
    printf("sig = %d\n", sig);
}

int main()
{
    pid_t pid;
    pid = getpid();
    printf("PID %d\n", pid);
    while (1)
    {
        signal(SIGUSR1, test);
    }
    return (0);
}
