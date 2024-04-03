/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:09:49 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/03 12:20:03 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

//
// -- Activation du debug mode
// -- 0 > Silent Mode
// -- 1 > Display Error
// -- 2 > Custom MSG
//
# define DEBUG_MODE 2

// -- choix fonts pour titre
# include "ascii_Bloody.h"
//# include "ascii_Alligator.h"
//# include "ascii_ANSI_Shadow.h"

// Lib include
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

// Regular text
# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

// Regular bold text
# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define BWHT "\e[1;37m"

// Regular underline text
# define UBLK "\e[4;30m"
# define URED "\e[4;31m"
# define UGRN "\e[4;32m"
# define UYEL "\e[4;33m"
# define UBLU "\e[4;34m"
# define UMAG "\e[4;35m"
# define UCYN "\e[4;36m"
# define UWHT "\e[4;37m"

// Regular background
# define BLKB "\e[40m"
# define REDB "\e[41m"
# define GRNB "\e[42m"
# define YELB "\e[43m"
# define BLUB "\e[44m"
# define MAGB "\e[45m"
# define CYNB "\e[46m"
# define WHTB "\e[47m"

// High intensty background
# define BLKHB "\e[0;100m"
# define REDHB "\e[0;101m"
# define GRNHB "\e[0;102m"
# define YELHB "\e[0;103m"
# define BLUHB "\e[0;104m"
# define MAGHB "\e[0;105m"
# define CYNHB "\e[0;106m"
# define WHTHB "\e[0;107m"

// High intensty text
# define HBLK "\e[0;90m"
# define HRED "\e[0;91m"
# define HGRN "\e[0;92m"
# define HYEL "\e[0;93m"
# define HBLU "\e[0;94m"
# define HMAG "\e[0;95m"
# define HCYN "\e[0;96m"
# define HWHT "\e[0;97m"

// Bold high intensity text
# define BHBLK "\e[1;90m"
# define BHRED "\e[1;91m"
# define BHGRN "\e[1;92m"
# define BHYEL "\e[1;93m"
# define BHBLU "\e[1;94m"
# define BHMAG "\e[1;95m"
# define BHCYN "\e[1;96m"
# define BHWHT "\e[1;97m"

// Reset
# define CRESET "\e[0m"
# define COLOR_RESET "\e[0m"

typedef enum t_bool
{
	FALSE = 0,
	TRUE = 1
}						t_bool;

typedef struct s_node
{
	int					value;
	struct s_node		*prev;
	struct s_node		*next;
}						t_node;

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

typedef struct s_dlist
{
	void				*content;
	struct s_dlist		*prev;
	struct s_dlist		*next;
}						t_dlist;

typedef struct s_dcoord
{
	t_dlist				*first;
	t_dlist				*last;
}						t_dcoord;

typedef struct s_alphanode
{
	char				**letter;
	struct s_alphanode	*prev;
	struct s_alphanode	*next;
}						t_alphanode;

int						ft_atoi(const char *str);

/**
 * @brief  The ft_bzero() function writes n zeroed bytes to the void s.
 * If n is zero, ft_bzero() does nothing.
 *
 * @param s
 * @param n
 * @return void*
 */
void					*ft_bzero(void *s, size_t n);

void					*ft_calloc(size_t elementCount, size_t elementSize);

int						ft_intlen(int nbr, int count);

t_bool					ft_isalnum(int c);

t_bool					ft_isalpha(int c);

/**
 * @brief The ft_isascii() function tests for an ASCII character,
	which is any character between 0 and 127 inclusive.
 *
 * @param c Character to test.
 * @return t_bool Function returns TRUE if c is an ASCII character,
	and FALSE otherwise.
 */
t_bool					ft_isascii(int c);

/**
 * @brief The ft_isdigit() function tests for a decimal digit character.
 *
 * @param c Character to test.
 * @return t_bool Function returns TRUE if c is a digit, and FALSE otherwise.
 */
t_bool					ft_isdigit(int c);

/**
 * @brief The ft_islower() function tests for any lower-case letter.
 *
 * @param c Character to test.
 * @return t_bool Function returns TRUE if c is a lower-case letter,
	and FALSE otherwise.
 */
t_bool					ft_islower(int c);

/**
 * @brief The ft_isprint() function tests for any printable character,
	including space.
 *
 * @param c Character to test.
 * @return t_bool Function returns TRUE if c is a printable character,
	and FALSE otherwise.
 */
t_bool					ft_isprint(int c);

/**
 * @brief The ft_isupper() function tests for any upper-case letter.
 *
 * @param c Character to test.
 * @return t_bool Function returns TRUE if c is an upper-case letter,
	and FALSE otherwise.
 */
t_bool					ft_isupper(int c);

char					*ft_itoa(int n);

void					*ft_memchr(const void *memoryBlock, int searchedChar,
							size_t size);

int						ft_memcmp(const void *s1, const void *s2, size_t n);

void					*ft_memcpy(void *dest, const void *src, size_t n);

void					*ft_memmove(void *dest, const void *src, size_t size);

void					*ft_memset(void *s, int c, size_t n);

int						ft_putchar_fd(char c, int fd);

void					ft_putendl_fd(char *str, int fd);

int						ft_putnbr_fd(int nb, int fd);

int						ft_putstr_fd(char *str, int fd);

char					**ft_split(char const *s, char c);

char					*ft_strchr(const char *s, int c);

/**
 * @brief Compares the two strings s1 and s2.
 *
 * @param s1 The first string to be compared.
 * @param s2 The second string to be compared.
 * @return int Returns 0 if the strings are equal,
	a positive integer if s1 is greater than s2,
	and a negative integer if s1 is less than s2.
 */
int						ft_strcmp(char *s1, char *s2);

/**
 * @brief The ft_strcpy() function copies the string pointed to by src,
	including the terminating null byte (\0), to the buffer pointed to by dest.
 *
 * @param dest Destination string.
 * @param src Source string.
 * @return char
	* The ft_strcpy() function returns a pointer to the destination string dest.
 */
char					*ft_strcpy(char *dest, char *src);

char					*ft_strdup(char *src);

void					ft_striteri(char *s, void (*f)(unsigned int, char *));

char					*ft_strjoin(char const *s1, char const *s2);

size_t					ft_strlcat(char *dst, const char *src, size_t n);

size_t					ft_strlcpy(char *dst, const char *src, size_t n);

size_t					ft_strlen(const char *str);

char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));

/**
 * @brief The ft_strncmp() function compares the two strings s1 and s2.
 * It compares not more than n characters.
 *
 * @param s1 First string to compare.
 * @param s2 Second string to compare.
 * @param n Number of characters to compare.
 * @return int Function returns an integer less than, equal to,
	or greater than zero if s1 is found, respectively, to be less than,
	to match, or be greater than s2.
 */
int						ft_strncmp(const char *s1, const char *s2, size_t n);

char					*ft_strnstr(const char *big, const char *little,
							size_t len);

char					*ft_strrchr(const char *s, int c);

char					*ft_strtrim(char const *sc1, char const *set);

char					*ft_substr(char const *s, unsigned int start,
							size_t len);

int						ft_tolower(int c);

int						ft_toupper(int c);

void					title_screen(char *title, char *color);

char					**letter_creation(const char *model);

void					for_a_to_l(char c, t_alphanode **chara);

/**
 * @brief The for_m_to_x() function creates the letters from M to X.
 *
 * @param c Character to create.
 * @param chara Chain list of letters.
 */
void					for_m_to_x(char c, t_alphanode **chara);

void					for_y_to_9(char c, t_alphanode **chara);

void					insert_front_alpha(t_alphanode **head, char **letter);

void					insert_after_alpha(t_alphanode *prev_node,
							char **letter);

void					insert_end_alpha(t_alphanode **head, char **letter);

/**
 * @brief The display_alpha() function displays the chain list of letters.
 *
 * @param node Node to start the display from.
 */
void					display_alpha(t_alphanode *node);

int						cmp_letter_list(t_alphanode *node, char **letter);

void					delete_alphanode(t_alphanode **head,
							t_alphanode *del_node);

void					delete_all_alphanodes(t_alphanode **head);

/**

	* @brief The title_triage() function triages the characters to create the title.
 *
 * @param c Character to triage.
 * @param chara Chain list of letters.
 */
void					title_triage(char c, t_alphanode **chara);

/**
 * @brief The title_freeway() function organize a list a free for title.
 *
 * @param chara Chain list of letters.
 */
void					title_freeway(t_alphanode **chara);

/**
 * @brief The for_symbol() function creates the symbols.
 *
 * @param c Character to create.
 * @param chara Chain list of letters.
 */
void					for_symbol(char c, t_alphanode **chara);

void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstadd_front(t_list **lst, t_list *new);
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstlast(t_list *lst);
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));
t_list					*ft_lstnew(void *content);
int						ft_lstsize(t_list *lst);

void					delete_node(t_node **head, t_node *del_node);
void					delete_all_nodes(t_node **head);
void					insert_front(t_node **head, int value);
void					insert_after(t_node *prev_node, int value);
void					insert_end(t_node **head, int value);
void					display_list(t_node *stack);
int						cmp_value_list(t_node *node, int value);

size_t					ft_putptr(size_t nbr, int base, char *table);
void					ft_rev_wr(char *str);
int						ft_printf(const char *format, ...);
int						marshalling(char c, va_list list_arg);
size_t					ft_putchar(char c);
size_t					ft_putstr(char *str);
size_t					ft_putbase(unsigned int nbr, int base, char *table);
size_t					ft_putnbr(long long nb);
int						ft_printf_fd(int fd, const char *format, ...);

char					*get_next_line(int fd);

char					*ft_strjoin_f(char *s1, char *s2);
char					*ft_strjoin_f2(char *s1, char *s2);

char					*fill_bucket(char *buffer);
char					*ft_read(int fd, char *static_buffer);

int						ft_strlen_endc(const char *str, int c);

/**
 * @brief The ft_free() function frees the given buffer and returns NULL.
 *
 * @param buffer Pointer to the buffer to free.
 * @return char* Function returns NULL.
 */
char					*ft_free(char *buffer);

void					display_info(char *add_msg, int debug_mode);
void					display_warning(char *add_msg, int debug_mode);
void					display_error(char *add_msg, void *to_free,
							int debug_mode);
int						return_info(int return_code, char *add_msg,
							void *to_free, int debug_mode);
int						return_warning(int return_code, char *add_msg,
							void *to_free, int debug_mode);
int						return_error(int return_code, char *add_msg,
							void *to_free, int debug_mode);
int						exit_error(int return_code, char *add_msg,
							void *to_free, int debug_mode);
int						exit_warning(int return_code, char *add_msg,
							void *to_free, int debug_mode);
int						exit_info(int return_code, char *add_msg, void *to_free,
							int debug_mode);

/**
 * @brief Counts the number of words in a string.
 *
 * This function counts the number of words in a given string, where words are
 * separated by a specified character.
 *
 * @param s The string to count words in.
 * @param c The character used to separate words.
 * @return The number of words in the string.
 */
int						count_words(const char *s, char c);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

# ifndef MAX_FD
#  define MAX_FD 1023
# endif

# ifndef OK
#  define OK 0
# endif

# ifndef KO
#  define KO 1
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

#endif
