
#include "libimp/libft.h"

void debug(t_list *lst)
{
	t_list *aux;

	aux = lst;
	while (aux)
	{
		ft_printf("CONTENT=> %s\n", (char *)aux->content);
		aux = aux->next;
	}
}

int main(int argc, char const *argv[])
{
	t_list	*node_1 = ft_lstnew("hola 1");
	t_list *node_2 = ft_lstnew("hola 2");
	t_list *node_3 = ft_lstnew("hola 3");
	t_list *node_4 = ft_lstnew("hola 4");

	ft_lstadd_back(&node_1, node_2);
	ft_lstadd_back(&node_1, node_3);
	ft_lstadd_back(&node_1, node_4);
	ft_printf("size --> %d \n", ft_lstsize(node_1));
	ft_lstdel_index(&node_1, 0);
	debug(node_1);

	return 0;
}
