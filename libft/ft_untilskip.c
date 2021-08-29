char	*ft_untilskip(char *str, char c)
{
	while (!(*str == c || *str == '\0'))
		str++;
	return (str);
}
