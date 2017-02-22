#include <hashcode.h>

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

t_slice	*make_slice(t_pos pos, t_form form, float mean)
{
	t_slice	*slice;

	if (!(slice = malloc(sizeof(t_slice))))
		return (NULL);
	slice->min = pos;
	slice->max.x = pos.x + form.x - 1;
	slice->max.y = pos.y + form.y - 1;
	slice->next = NULL;
	return (slice);
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

t_slice	*good_slice(t_coord pos, t_form form, t_meta *meta)
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
				return (make_slice(pos, form));
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

void	*filter(char (*fn)(void *, va_list), t_list *lst, char _free, ...)
{
	va_list	args;
	t_list	*res, *tmp, *ptr = NULL;

	va_start(args, _free);
	while ((ptr = lst) && !fn(lst, args))
	{
		lst = lst->next;
		if (_free)
			free(ptr);
	}
	if (!(res = lst))
		return (NULL);
	tmp = res;
	while ((ptr = lst) && (lst = lst->next))
	{
		if (fn(lst, args))
		{
			tmp->next = lst;
			tmp = tmp->next;
		}
		if (_free)
			free(ptr);
	}
	if (_free)
		free(ptr);
	va_end(args);
	return (res);
}

void	*map(void *(*fn)(void *, va_list), t_list *lst, char _free, ...)
{
	va_list	args;
	t_list	*res, *tmp, *ptr = NULL;

	va_start(args, _free);
	if (!lst)
		return (NULL);
	res = fn(lst, args);
	tmp = res;
	ptr = lst;
	while ((lst = lst->next))
	{
		if (_free)
			free(ptr);
		tmp->next = fn(lst, args);
		tmp = tmp->next;
		ptr = lst;
	}
	if (_free)
		free(ptr);
	va_end(args);
	return (res);
}

void	*map_filtred(void *(*fn)(void *, va_list), t_list *lst, char _free, ...)
{
	va_list	args;
	t_list	*res, *tmp, *ptr = NULL;

	va_start(args, _free);
	if (!lst)
		return (NULL);
	while ((ptr = lst) && !(res = fn(lst, args)))
		lst = lst->next;
	tmp = res;
	ptr = lst;
	while ((lst = lst->next))
	{
		if (_free)
			free(ptr);
		if (!(tmp->next = fn(lst, args)))
			tmp = tmp->next;
		ptr = lst;
	}
	if (_free)
		free(ptr);
	va_end(args);
	return (res);
}

void	foreach(void (*fn)(void *, va_list), t_list *lst, char _free, ...)
{
	va_list	args;
	void	*ptr;

	va_start(args, _free);
	if (!lst)
		return ;
	fn(lst, args);
	ptr = lst;
	while ((lst = lst->next))
	{
		if (_free)
			free(ptr);
		fn(lst, args);
		ptr = lst;
	}
	if (_free)
		free(ptr);
	va_end(args);
	return (res);
}

void	free_lst(t_lst	*ptr)
{
	t_lst	*tmp;
	
	while ((tmp = ptr))
	{
		ptr = ptr->next;
		free(tmp);
	}
}

void 	end_list(t_lst *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
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
			tmp->next = filter(filter_good_slice, forms, 0, pos, meta);
			tmp = end_list(tmp);
		}
}
