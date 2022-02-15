# Запуск программы
make && ./minishell

# minishell

Проект по созданию собственного Shell на языке С (аналогичый Bash). [Полный Subject (задача Ecole42)](https://cdn.intra.42.fr/pdf/pdf/43461/en.subject.pdf) <br>
Реализованые задачи:<br>
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
<img width="818" alt="Screenshot 2022-02-15 at 23 28 30" src="https://user-images.githubusercontent.com/28803066/154144005-f5ea1fc5-a489-4efe-9a26-42c8a6a6b775.png">
