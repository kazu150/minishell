/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:23:45 by kaisogai          #+#    #+#             */
/*   Updated: 2025/05/13 16:01:14 by kaisogai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	validate_and_count_base(char *base)
{
	int	base_count;
	int	j;

	base_count = 0;
	j = 1;
	while (base[base_count] != 0)
	{
		if (base[0] == 0 || base[1] == 0)
			return (0);
		if (base[base_count] == '+' || base[base_count] == '-')
			return (0);
		while (base[j] != 0)
		{
			if (base[base_count] == base[j])
				return (0);
			j++;
		}
		base_count++;
		j = base_count + 1;
	}
	return (base_count);
}

void	ft_putnbr_base(unsigned long nbr, char *base)
{
	char			c;
	unsigned long	base_count;

	base_count = validate_and_count_base(base);
	if (!base_count)
		return ;
	c = base[nbr % base_count];
	if (nbr >= base_count)
		ft_putnbr_base(nbr / base_count, base);
	write(1, &c, 1);
}

// int	main(void)
// {
// 	char base[] = "01234567";
// 	ft_putnbr_base(0, base);
// 	printf("\n");
// 	ft_putnbr_base(1, base);
// 	printf("\n");
// 	ft_putnbr_base(2, base);
// 	printf("\n");
// 	ft_putnbr_base(3, base);
// 	printf("\n");
// 	ft_putnbr_base(10, base);
// 	printf("\n");
// 	ft_putnbr_base(1500, base);
// 	printf("\n");
// 	ft_putnbr_base(2147483647, base);
// 	printf("\n");
// 	ft_putnbr_base(-1, base);
// 	printf("\n");
// 	ft_putnbr_base(-2, base);
// 	printf("\n");
// 	ft_putnbr_base(-3, base);
// 	printf("\n");
// 	ft_putnbr_base(-10, base);
// 	printf("\n");
// 	ft_putnbr_base(-1500, base);
// 	printf("\n");
// 	ft_putnbr_base(-2147483648, base);
// 	printf("\n");
// 	char base_invalid1[] = "z-abcdefg";
// 	ft_putnbr_base(1500, base_invalid1);
// 	printf("\n");
// 	char base_invalid2[] = "zabcdefg+";
// 	ft_putnbr_base(1500, base_invalid2);
// 	printf("\n");
// 	char base_invalid3[] = "zabcdefga";
// 	ft_putnbr_base(1500, base_invalid3);
// 	printf("\n");
// 	char base_invalid4[] = "";
// 	ft_putnbr_base(1500, base_invalid4);
// 	printf("\n");
// 	char base_invalid5[] = "a";
// 	ft_putnbr_base(1500, base_invalid5);
// 	printf("\n");
// }