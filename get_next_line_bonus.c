/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snidbell <snidbell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 10:29:52 by snidbell          #+#    #+#             */
/*   Updated: 2023/12/18 06:14:41 by snidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	fill(char *s1, char *s2, int len)
{
	int	i;

	if (!s1 || !s2)
		return ;
	i = 0;
	while (*s2 && len > 0)
	{
		s1[i] = *s2++;
		i++;
		len--;
	}
	s1[i] = '\0';
}

char	*add_to_list(char **wleft, t_line **lst, int *flag, int ret)
{
	int		i;
	char	*buffer;
	char	*line;

	i = 0;
	buffer = NULL;
	while (i < ret && *wleft && (*wleft)[i] && (*wleft)[i] != '\n')
		i++;
	if (*wleft && (*wleft)[i] && (*wleft)[i++] == '\n')
		*flag = 0;
	line = malloc(i + 1);
	if (!line)
		return (free(*wleft), ft_lstclear(lst), NULL);
	fill(line, *wleft, i);
	if (i < ret)
	{
		buffer = malloc((size_t)BUFFER_SIZE - i + 1);
		if (!buffer)
			return (free(*wleft), free (line), ft_lstclear(lst), NULL);
		fill(buffer, ((*wleft) + i), BUFFER_SIZE - i);
	}
	free(*wleft);
	if (!(new_to_lst(lst, &line)))
		return (free(buffer), NULL);
	return (*wleft = buffer, "done");
}

char	*get_next_line(int fd)
{
	static char	*wleft[1024];
	int			flag;
	t_line		*lst;
	char		*rst;
	int			ret;

	flag = 1;
	lst = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	while (flag)
	{
		ret = read_from_fd(&wleft[fd], fd, &lst, &flag);
		if (ret == -1)
			return (ft_lstclear(&lst), NULL);
		if (ret == 0)
			break ;
	}
	if (!lst)
		return (free(wleft[fd]), wleft[fd] = NULL, NULL);
	rst = ft_lst_groupstr(lst);
	ft_lstclear(&lst);
	return (rst);
}

int	read_from_fd(char **wleft, int fd, t_line **lst, int *flag)
{
	int	ret;

	if (*wleft)
	{
		ret = ft_strlen(*wleft);
		if (!(add_to_list((char **)wleft, lst, flag, ret)))
			return (-1);
	}
	else
	{
		*wleft = (char *)malloc((size_t)BUFFER_SIZE + 1);
		if (!(*wleft))
			return (-1);
		ret = read(fd, *wleft, BUFFER_SIZE);
		if (ret < 0)
			return (free(*wleft), *wleft = NULL, -1);
		if (ret == 0)
			return (free(*wleft), *wleft = NULL, 0);
		(*wleft)[ret] = '\0';
		if (!(add_to_list((char **)wleft, lst, flag, ret)))
			return (-1);
	}
	return (ret);
}
