/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snidbell <snidbell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:05:34 by snidbell          #+#    #+#             */
/*   Updated: 2023/12/17 16:36:19 by snidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct t_line
{
	char			*str;
	struct t_line	*next;
}t_line;

char	*get_next_line(int fd);
char	*ft_lst_groupstr(t_line *lst);
char	*add_to_list(char **wleft, t_line **lst, int *flag, int ret);
void	ft_lstclear(t_line **lst);
size_t	ft_strlen(const char *s);
char	*new_to_lst(t_line **lst, char **st);
void	fill(char *s1, char *s2, int len);
int		read_from_fd(char **wleft, int fd, t_line **lst, int *flag);

#endif
