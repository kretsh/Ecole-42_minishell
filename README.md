# minishell

Проект по созданию собственного шелла на С (аналогичый Bash). <br>
Доступные функции для использования: 
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, kill, exit, getcwd, chdir, stat,
lstat, fstat, unlink, execve, dup, dup2, pipe,
opendir, readdir, closedir, strerror, perror,
isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr,
tcgetattr, tgetent, tgetflag, tgetnum, tgetstr,
tgoto, tputs
<br>
Реализованые задачи.<br>
1. Имплементированы следующие builtins:<br>
◦ echo <br>
◦ cd <br>
◦ pwd <br>
◦ export <br>
◦ unset <br>
◦ env <br>
◦ exit <br>
2. Реализованы одинарные и двойные кавычки, все Exit коды программ для работы с && (условное логическое И) и || (условное логическое ИЛИ) и коректным их исполнением.<br>
3. Написан heredoc, redirect left, redirect right, double rederect right (дописывание в файл) а так же pipe as bash.<br>
4. Произведена работа с сигналами SIGQUIT, SIGINT и SIGTERM.<br>
5. Обработка ошибок, освобождение памяти. <br>
