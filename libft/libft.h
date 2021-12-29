/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:11:00 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 18:33:59 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_flags
{
	int		start;
	int		quotes;
	int		d_quotes;
	int		pipe_in;
	int		pipe_out;
	int		and;
	int		or;
	int		argv;
	int		env;
	int		redirect_d_right;
	int		redirect_right;
	int		redirect_d_left;
	int		redirect_left;
	int		cmd;
	int		parenthesis;
	int		remove;
	int		white_space;
	int		wild_card;
	char	*redirect_filename;
}	t_flags;

typedef struct s_cmd
{
	char			*cmd;
	char			*value;
	char			**argv_for_cmd;
	char			c;
	int				error_on_parsing;
	t_flags			flags;
	struct s_cmd	*start_list;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	int				pip[2];
	int				pid;
}	t_cmd;

int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
t_cmd	*ft_lstnew(void *content, void *content2);
void	ft_lstadd_front(t_cmd **lst, t_cmd *new);
int		ft_lstsize(t_cmd *lst);
t_cmd	*ft_lstlast(t_cmd *lst);
void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
void	ft_lstdelone(t_cmd *lst, void (*del)(void*));
void	ft_lstclear(t_cmd **lst, void (*del)(void*));
void	ft_lstiter(t_cmd *lst, void (*f)(void *));
t_cmd	*ft_lstmap(t_cmd *lst, void *(*f)(void *), void (*del)(void *));
int		ft_strcmp(const char *s1, const char *s2);

#endif
