/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:22:07 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 16:53:57 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	sigaction_handler(int SIGNUM, siginfo_t *siginfo, void *dunno)
{
	(void) SIGNUM;
	(void) siginfo;
	(void) dunno;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_catcher(void)
{
	struct sigaction	sigstruct_c;
	struct sigaction	sigstruct_other;
	struct termios		silence;

	tcgetattr(STDIN_FILENO, &silence);
	silence.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &silence);
	sigstruct_c = (struct sigaction){};
	sigstruct_other = (struct sigaction){};
	sigstruct_c.sa_flags = SA_SIGINFO;
	sigstruct_c.sa_sigaction = sigaction_handler;
	sigstruct_other.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sigstruct_c, NULL);
	sigaction(SIGQUIT, &sigstruct_other, NULL);
	sigaction(SIGTERM, &sigstruct_other, NULL);
}

void	sig_quit_catch(t_data *data)
{
	free_envp_list(data->envp_list);
	(void) data;
	rl_clear_history();
	write(2, "exit\n", 5);
	exit(EXIT_NO_ERROR);
}
