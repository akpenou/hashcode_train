#include <stdio.h>
#include <stdlib.>
#include <stdarg.h>

typedef struct		s_slice
{
	struct s_slice	*next;
	unsigned int	min_x;
	unsigned int	min_y;
	unsigned int	max_x;
	unsigned int	max_y;
	float			mean;
}					t_slice;

typedef struct		s_meta
{
	unsigned int	rows;
	unsigned int	cols;
	unsigned int	min_ing;
	unsigned int	max_area
	char			**tab;
	unsigned int	**counter_tab;
}					t_meta;

typedef struct		s_form
{
	struct s_form	*next;
	unsigned int	x;
	unsigned int	y;
}					t_form;

typedef struct		s_coord
{
	unsigned int	x;
	unsigned int	y;
}					t_coord;

typedef struct		s_list
{
	struct s_list	*next;
}					t_list;

void	*ft_memalloc(size_t size)
{
	char	*ptr;
	int		i;

	ptr = malloc(size);
	for(i = 0 ; i < size ; i++)
		ptr[i] = 0;
	return (ptr);
}

t_meta	*parsing(char *filename)
{
	int		index;
	FILE	*fd;
	t_meta	*meta;

	fd = fopen(filename, "r");
	meta = malloc(sizeof(t_meta));
	fscanf(fd, "%d %d %d %d", &meta->rows, &meta->cols, &meta->min_ing, &meta->max_area);
	meta->tab = malloc(sizeof(char *) * meta->rows);
	meta->counter_tab = malloc(sizeof(unsigned int *) * meta->rows);
	for (index = 0 ; index < meta->rows ; index++)
	{
		meta->counter_tab[index] = ft_memalloc(sizeof(unsigned int) * meta->cols);
		meta->tab[index] = malloc(sizeof(char) * meta->cols);
		fgets(meta->tab[index], meta->cols, fd);
	}
	return meta;
}

t_form	*make_form(unsigned int x, unsigned int y)
{
	t_form	*form;

	form = malloc(sizeof(t_form));
	form->x = x;
	form->y = y;
	return (form);
}

t_form *get_form(unsigned int min_area, unsigned int max_area)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	area;
	t_form			*forms;
	t_form			*tmp;

	forms = make_form(0, 0);
	tmp = forms;
	for (y = 0 ; y < max_area ; y++)
	{
		for (x = 0 ; x < max_area ; l++)
		{
			area = x * y
			if (min_area > area || max_area < area)
				continue ;
			tmp->next = make_form(x, y);
			tmp = tmp->next:
		}
	}
	tmp->next = NULL;
	tmp = forms->next;
	free(forms);
	return(tmp);
}

char	is_good_slice(t_coord pos, t_form form, t_meta *meta)
{
	int	mushrooms, tomatos = 0;
	t_coord	tmp;

	if (pos.x + form.x > meta->rows || pos.y + form.y > meta->cols)
		return (0);
	for (tmp.y = 0 ; tmp.y < form.y ; tmp.y++)
	{
		for (tmp.x = 0 ; tmp.x < form.x ; tmp.x++)
		{
			if (meta->tab[pos.y + tmp.y] == 'M')
				mushrooms++;
			else
				tomatos++;
			if (mushrooms >= meta.min_ing && tomatos >= meta.min_ing)
				return (1);
		}
	}
	return (0);
}

char	filter_good_slice(t_form *form, va_list args)
{
	char	res;
	va_list	args_cpy;

	va_copy(args_cpy, args);
	res = is_good_slice(va_arg(args_cpy, t_pos), *form, va_arg(args_cpy, t_meta *));
	va_end(args_cpy);
	return (res);
}

void	*filter(char (*fn)(void *, va_list), t_list *lst, ...)
{
	va_list	args;
	t_list	*res, *tmp = NULL;

	va_start(args, lst);
	while (lst && !fn(lst, args))
		lst = lst->next;
	if (!(res = lst))
		return (NULL);
	tmp = res;
	while ((lst = lst->next))
	{
		if (fn(lst, args))
		{
			tmp->next = lst;
			tmp = tmp->next;
		}
	}
	va_end(args);
	return (res);
}

void	*map(void *(*fn)(void *, va_list), t_list *lst, ...)
{
	va_list	args;
	t_list	*res, *tmp = NULL;

	va_start(args, lst);
	if (!lst)
		return (NULL);
	res = fn(lst, args);
	tmp = res;
	while ((lst = lst->next))
	{
		tmp->next = fn(lst, args);
		tmp = tmp->next;
	}
	va_end(args);
	return (res);
}

void	foreach(void (*fn)(void *, va_list), t_list *lst, ...)
{
	va_list	args;

	va_start(args, lst);
	if (!lst)
		return ;
	fn(lst, args);
	while ((lst = lst->next))
		fn(lst, args);
	va_end(args);
	return (res);
}

void	counter(t_meta *meta, t_form *forms)
{
	t_coord	pos;
	t_coord tmp_pos;
	t_form	*res_forms = make_form(0, 0);
	t_form	*tmp;

	tmp = res_forms;
	for (pos.x = 0 ; pos.x < meta->cols ; pos.x++)
		for (pos.y = 0 ; pos.y < meta->rows ; pos.y++)
		{
			tmp->next = filter(filter_good_slice, forms, pos, meta);

		}
}
