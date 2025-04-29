/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:23:08 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/04/22 12:23:12 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

volatile sig_atomic_t	g_signal = 0;

/**
 * Handles the SIGINT signal.
 *
 * This function is called when the user presses Ctrl+C.
 * It sets the global variable g_signal to SIGINT and writes a newline
 * character to the standard output.
 *
 * @param signo The signal number (not used in this case).
 */
void	sigint_handler(int signo)
{
	(void)signo;
	g_signal = SIGINT;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * Sets up the signal handlers for the shell.
 *
 * This function sets the signal handler for SIGINT (Ctrl+C) to
 * sigint_handler and ignores the SIGQUIT signal.
 */
void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(sa_int));
	ft_memset(&sa_quit, 0, sizeof(sa_quit));
	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
//TODO: Handle Child process signals
