int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	while (ft_isdigit(*str))
		result = (result * 10) + (*str++ - '0');
	return (result * sign);
}

void	ft_bzero(void *str, size_t nby)
{
	ft_memset(str, 0, nby);
}

void	*ft_calloc(size_t num_el, size_t numby)
{
	void	*memaloc;
	size_t	finsize;

	memaloc = NULL;
	finsize = num_el * numby;
	if (num_el == 0 || numby == 0 || finsize / num_el != numby)
		return (NULL);
	memaloc = malloc(finsize);
	if (memaloc)
		ft_bzero(memaloc, finsize);
	return (memaloc);
}

int	ft_isalnum(int chdig)
{
	if (chdig >= '0' && chdig <= '9')
		return (1);
	if ((chdig >= 'a' && chdig <= 'z')
		|| (chdig >= 'A' && chdig <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z')
		|| (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isascii(int var)
{
	if (var >= 0 && var <= 127)
		return (1);
	else
		return (0);
}

int	ft_isdigit(int dig)
{
	if (dig >= '0' && dig <= '9')
		return (1);
	else
		return (0);
}

int	ft_isprint(int var)
{
	if (var >= ' ' && var <= '~')
		return (1);
	else
		return (0);
}

static int	ft_intlen(long int num)
{
	int	cnt;

	cnt = 0;
	if (num <= 0)
	{
		cnt++;
		num = -num;
	}
	while (num > 0)
	{
		cnt++;
		num /= 10;
	}
	return (cnt);
}

char	*ft_itoa(int num)
{
	long int	absnum;
	int			numlen;
	char		*str;

	absnum = num;
	numlen = ft_intlen(absnum);
	str = ft_calloc(numlen + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (absnum < 0)
		absnum = -absnum;
	while (numlen > 0)
	{
		str[--numlen] = absnum % 10 + '0';
		absnum /= 10;
	}
	if (num < 0)
		str[0] = '-';
	return (str);
}

void	*ft_memchr(const void *str, int ch, size_t numby)
{
	if (numby == '\0')
		return (NULL);
	while (numby--)
	{
		if (*(char *)str == (char)ch)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

int	ft_memcmp(const void *str0, const void *str1, size_t numby)
{
	long int	cnt;

	cnt = -1;
	if (numby == 0)
		return (0);
	while (++cnt < (long int)numby)
		if (*(unsigned char *)(str0 + cnt) != *(unsigned char *)(str1 + cnt))
			return (*(unsigned char *)(str0 + cnt) -
			*(unsigned char *)(str1 + cnt));
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t numby)
{
	long int	cnt;

	cnt = -1;
	if (!dest && !src)
		return (NULL);
	while (++cnt < (long int)numby)
		*(char *)(dest + cnt) = *(char *)(src + cnt);
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t numby)
{
	if (!dest && !src)
		return (NULL);
	if (dest < src)
		return (ft_memcpy(dest, src, numby));
	while (numby--)
		*(char *)(dest + numby) = *(char *)(src + numby);
	return (dest);
}

void	*ft_memset(void *buffer, int value, size_t len)
{
	while (len--)
		*(unsigned char *)(buffer + len) = value;
	return (buffer);
}

void	ft_putchar_fd(char ch, int fd)
{
	write(fd, &ch, 1);
}

void	ft_putendl_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	ft_putnbr_fd(int num, int fd)
{
	long int	nwnum;

	nwnum = num;
	if (nwnum < 0)
	{
		nwnum *= -1;
		ft_putchar_fd('-', fd);
	}
	if (nwnum > 9)
		ft_putnbr_fd(nwnum / 10, fd);
	ft_putchar_fd(nwnum % 10 + '0', fd);
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

static void	mksplit(char const *str, char ch, size_t cnt, char **substr)
{
	char	*str1;
	size_t	strini;
	size_t	strlen;

	while (str[cnt])
	{
		if (str[cnt] && str[cnt] != ch)
		{
			strini = cnt;
			while (str[cnt] && str[cnt] != ch)
				cnt++;
			strlen = (cnt - strini) + 1;
			str1 = malloc(sizeof(char) * strlen);
			ft_strlcpy(str1, &str[strini], strlen);
			*(char **)(substr++) = str1;
		}
		if (str[cnt] && str[cnt] == ch)
			while (str[cnt] && str[cnt] == ch)
				cnt++;
	}
	substr = NULL;
}

static size_t	cntwords(char const *str, char ch)
{
	size_t	words;

	words = 0;
	while (*str)
	{
		if (*str && *str != ch)
		{
			while (*str && *str != ch)
				str++;
			words++;
		}
		if (*str && *str == ch)
			while (*str && *str == ch)
				str++;
	}
	return (words + 1);
}

char	**ft_split(char const *str, char ch)
{
	size_t	numstrmk;
	char	**strsplit;

	if (!str)
		return (NULL);
	numstrmk = cntwords(str, ch);
	strsplit = ft_calloc((numstrmk), sizeof(char *));
	if (!strsplit)
		return (NULL);
	mksplit(str, ch, 0, strsplit);
	return (strsplit);
}

char	*ft_strchr(const char *str, int ch)
{
	while (*str && *str != (char)ch)
		str++;
	if ((char)ch == *str)
		return ((char *)str);
	return (0);
}

char	*ft_strdup(const char *str0)
{
	int		cnt;
	char	*str1;

	cnt = 0;
	str1 = malloc(ft_strlen(str0) + 1);
	if (!str1)
		return (NULL);
	while (*str0)
		str1[cnt++] = *str0++;
	str1[cnt] = '\0';
	return (str1);
}

void	ft_striteri(char *str, void (*ftn)(unsigned int, char*))
{
	int		cnt;

	cnt = -1;
	while (str[++cnt])
		ftn(cnt, &str[cnt]);
}

char	*ft_strjoin(char const *str0, char const *str1)
{
	char	*nwstr;
	size_t	len0;
	size_t	len1;

	len0 = ft_strlen(str0);
	len1 = ft_strlen(str1);
	nwstr = malloc((len0 + len1 + 1) * sizeof(char));
	if (nwstr == NULL)
		return (NULL);
	ft_strlcpy(nwstr, str0, len0 + 1);
	ft_strlcpy(&nwstr[len0], str1, len1 + 1);
	return (nwstr);
}

size_t	ft_strlcat(char *dest, const char *src, size_t destsz)
{
	size_t	lenx;
	size_t	len0;
	size_t	len1;

	lenx = 0;
	len0 = ft_strlen(dest);
	len1 = ft_strlen(src);
	if (destsz <= len0)
		return (len1 + destsz);
	while (src[lenx] && (len0 + 1) < destsz)
		dest[len0++] = src[lenx++];
	dest[len0] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[lenx]));
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	cnt;

	cnt = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (cnt < (size - 1) && src[cnt])
	{
		dest[cnt] = src[cnt];
		cnt++;
	}
	dest[cnt] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlen(const char *var)
{
	size_t	cnt;

	cnt = 0;
	while (var[cnt] != '\0')
	{
		cnt++;
	}
	return (cnt);
}

char	*ft_strmapi(char const *str, char (*ftn)(unsigned int, char))
{
	int		cnt;
	char	*result;

	if (!str || !ftn)
		return (NULL);
	cnt = -1;
	result = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (str[++cnt])
		result[cnt] = ftn(cnt, str[cnt]);
	result[cnt] = '\0';
	return (result);
}

int	ft_strncmp(const char *str0, const char *str1, size_t numby)
{
	size_t	cnt;

	cnt = 0;
	if (numby == 0)
		return (0);
	while (str0[cnt] && (str0[cnt] == str1[cnt]) && cnt < (numby - 1))
		cnt++;
	return ((unsigned char)str0[cnt] - (unsigned char)str1[cnt]);
}

char	*ft_strnstr(const char *big, const char *ltl, size_t lench)
{
	size_t	lenb;
	size_t	lenl;

	lenb = 0;
	lenl = ft_strlen(ltl);
	if (lenl == 0)
		return ((char *)big);
	while (*big && lenb <= lench)
	{
		if (lench - lenb++ >= lenl && !ft_strncmp(big, ltl, lenl))
			return ((char *)big);
		big++;
	}
	return (0);
}

char	*ft_strrchr(const char *str, int ch)
{
	int	cnt;

	cnt = ft_strlen(str);
	while (cnt != 0 && str[cnt] != (char)ch)
		cnt--;
	if (str[cnt] == (char)ch)
		return ((char *)str + cnt);
	return (NULL);
}

char	*ft_strtrim(char const *str0, char const *set)
{
	char	*nwstr;
	size_t	cnt;

	if (!str0 || !set)
		return (NULL);
	while (*str0 && ft_strchr(set, *str0))
		str0++;
	cnt = ft_strlen(str0) + 1;
	while (cnt && ft_strchr(set, str0[cnt - 1]))
		cnt--;
	nwstr = (char *) malloc((cnt + 1) * sizeof(char));
	if (!nwstr)
		return (NULL);
	ft_strlcpy(nwstr, str0, cnt + 1);
	return (nwstr);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*nwstr;
	size_t	lenstr;

	if (!str)
		return (NULL);
	lenstr = ft_strlen(str);
	if (start >= lenstr)
		return (ft_strdup(""));
	if (lenstr - start >= len)
		nwstr = malloc((len + 1) * sizeof(char));
	else
		nwstr = malloc((lenstr - start + 1) * sizeof(char));
	if (nwstr)
	{
		if (len > lenstr + 1)
			len = lenstr + 1;
		ft_strlcpy(nwstr, (str + start), (len + 1));
	}
	else
		return (NULL);
	return (nwstr);
}

int	ft_tolower(int ch)
{
	if (ch >= 'A' && ch <= 'Z')
		ch += 32;
	return (ch);
}

int	ft_toupper(int ch)
{
	if (ch >= 'a' && ch <= 'z')
		ch -= 32;
	return (ch);
}