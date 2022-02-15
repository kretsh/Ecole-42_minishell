# Запуск программы
make && ./minishell

# minishell

Проект по созданию собственного шелла на С (аналогичый Bash). <br>
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
