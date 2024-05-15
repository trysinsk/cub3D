/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trysinsk <trysinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:23:41 by trysinsk          #+#    #+#             */
/*   Updated: 2024/05/15 11:34:54 by trysinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// enleve la ligne qui a ete envoye a rendu de lus en laissant
// le reste pour les prochains appel de get next line
char	*ft_clean_lus(char *lus)
{
	char	*new_lus;
	int		i;

	i = 0;
	while (lus[i] != '\0' && lus[i] != '\n')
		i++;
	if (lus[i] == '\0')
	{
		free(lus);
		return (NULL);
	}
	new_lus = malloc((ft_strlen(lus) - i + 1) * sizeof(char));
	if (!new_lus)
		return (NULL);
	i++;
	new_lus = ft_strlcpy(new_lus, lus, i);
	free(lus);
	return (new_lus);
}

// extrait la ligne de lus et l'envoie sur une nouvelle string allouee nommee
// rendu avant de la renvoyer dans le programme principal.
// pas besoin de free rendu vu qu'elle sera renvoyee au main.
char	*ft_return_line(char *lus)
{
	char	*rendu;
	int		i;

	i = 0;
	if (!lus[i])
		return (NULL);
	while (lus[i] != '\0' && lus[i] != '\n')
		i++;
	rendu = malloc((i + 2) * sizeof(char));
	if (!rendu)
		return (NULL);
	i = 0;
	while (lus[i] != '\0' && lus[i] != '\n')
	{
		rendu[i] = lus[i];
		i++;
	}
	if (lus[i] != '\0' && lus[i] == '\n')
	{
		rendu[i] = '\n';
		i++;
	}
	rendu[i] = '\0';
	return (rendu);
}

// envoie les contenu de *lus + tas sur une nouvelle string temp,
// free la string actuelle de lus et renvoies temp vers lus
char	*ft_transfert(char *lus, char *tas)
{
	char	*new_lus;

	new_lus = ft_strjoin(lus, tas);
	free(lus);
	return (new_lus);
}

// cette fonction va lire BUFFER_SIZE nombre de caractere et les stocker
// dans *tas puis creer une nouvelle string avec *lus entre chaque appel
// de read jusqu'a trouver un caractere \n dans *lus
char	*ft_read_file(int fd, char *lus, char *tas, int lire)
{
	if (!lus)
	{
		lus = malloc(1 * sizeof(char));
		if (!lus)
			return (NULL);
		lus[0] = '\0';
	}
	while (tas && lire > 0)
	{
		lire = read(fd, tas, 1);
		if (lire == -1)
			return (NULL);
		tas[lire] = '\0';
		lus = ft_transfert(lus, tas);
		if (ft_find_line(tas) == 1)
			break ;
	}
	return (lus);
}

// la fonction lit d'abord x fois jusqu'a trouver \n avec ft_read, stock dans
// lus puis extraie de lus la ligne avant de la placer dans rendu, enfin il
// faut clean ce qui n'est plus nescessaire dans lus avant de renvoyer rendu
char	*get_next_line(int fd)
{
	static char	*lus;
	char		*tas;
	char		*rendu;
	int			lire;

	if (fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	lire = 1;
	tas = malloc((1 + 1) * sizeof(char));
	if (!tas)
		return (NULL);
	lus = ft_read_file(fd, lus, tas, lire);
	free(tas);
	if (!lus)
		return (NULL);
	rendu = ft_return_line(lus);
	lus = ft_clean_lus(lus);
	return (rendu);
}
