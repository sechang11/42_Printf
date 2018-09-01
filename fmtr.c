/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmtr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 17:39:49 by sechang           #+#    #+#             */
/*   Updated: 2018/08/31 17:58:36 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
//if number, uses 0's as fillers if preci > len

int		width_n_c(t_flag *mods, unsigned long long len, char key)
{
	unsigned long long		twidth;
	unsigned long			i;

	i = 0; //(mods->preci > len) ? mods->preci - len : 0;
	if (key == 'n')
		twidth = (mods->width > mods->preci) ? mods->width : mods->preci;
	else
		twidth = mods->width;
//	printf("Entered W_a_b\n");
//	printf("Width= %lu\n", mods->width);
//	printf("Twidth= %llu\n", twidth);
//	printf("pre-len=%llu\n", len);
//	printf("Preci= %lu\n", mods->preci);
//	printf("flag2: %d\n", mods->flag[2]);
//	printf("flag3: %d\n", mods->flag[3]);
	mods->space = ((mods->flag[2] > 0) && (mods->flag[3] == 0)) ? '0' : ' ';
//	printf("Modspace = %c\n", mods->space);
	while (twidth > len++)
		mods->store->buf[mods->i++] = mods->space;
	return (0);
}

// flag 6 = 'h'
// flag 7 = 'l'
// flag 8 = 'j'
// flag 9 = 'z'

// big to small with returns right away - (multiple modifiers, biggest one takes precedence)
char	*numx(t_flag *mods)
{
	if (mods->flag[8] >= 1)
		return(imax_itoa((va_arg(mods->vg, intmax_t))));
	if (mods->flag[7] >= 2)
		return(imax_itoa((va_arg(mods->vg, long long))));
	if (mods->flag[7] == 1)
		return (imax_itoa((va_arg(mods->vg, long))));
	if (mods->flag[9] >= 1)
		return (imax_itoa(va_arg(mods->vg, size_t)));
	if (mods->flag[6] == 1)
		return (imax_itoa((short)(va_arg(mods->vg, int))));
	if (mods->flag[6] >= 2)
		return (imax_itoa(((char)(va_arg(mods->vg, int)))));
	return (ft_itoa(va_arg(mods->vg, int)));
}
///         The following length modifier is valid for the c or s conversion:

//         Modifier    c         s
  //       l (ell)     wint_t    wchar_t *

char	*ouxx(t_flag *mods, int base, char key)
{
	if (mods->flag[10] == 'p')
		return (itoabase((va_arg(mods->vg, unsigned long)), base, key));
	if (mods->flag[8] >= 1)
		return (itoabase((va_arg(mods->vg, uintmax_t)), base, key));
	if (mods->flag[7] >= 2)
		return (itoabase((va_arg(mods->vg, unsigned long long)), base, key));
	if (mods->flag[7] == 1)
		return (itoabase((va_arg(mods->vg, unsigned long)), base, key));
	if (mods->flag[9] >= 1)
		return (itoabase((va_arg(mods->vg, size_t)), base, key));
	if (mods->flag[6] == 1)
		return (itoabase((unsigned short)(va_arg(mods->vg, int)), base, key));
	if (mods->flag[6] >= 2)
		return (itoabase((unsigned char)(va_arg(mods->vg, int)), base, key));
	return (NULL);
}

unsigned long	preci(t_flag *mods, unsigned long len)
{
	while (mods->preci > len)
	{
		mods->store->buf[mods->i++] = '0';
		len++;
	}
	return(len);
}
