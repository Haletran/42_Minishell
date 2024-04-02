/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:09:49 by ygaiffie          #+#    #+#             */
/*   Updated: 2024/04/02 22:00:41 by bapasqui         ###   ########.fr       */
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

//* ************************************************************************** */
//* ************************************************************************** */
//*
//* 								LIBFT_FUNCTIONS
//*
//* ************************************************************************** */
//* ************************************************************************** */

/**
 * @brief The ft_atoi() function converts the initial portion of the string pointed to by str to int.
 * 
 * @param str Number string.
 * @return int Function returns the converted value.
 */
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

/**
 * @brief  The ft_calloc() function allocates memory for an array of elementCount of size bytes each and returns a pointer to the allocated memory.
 * The memory is set to zero. If elementCount or size is 0, then ft_calloc() returns either NULL, or a unique pointer value that can later be successfully passed to free().
 * 
 * @param elementCount Number of elements to allocate.
 * @param elementSize Size of each element.
 * @return void* 
 */
void					*ft_calloc(size_t elementCount, size_t elementSize);

/**
 * @brief The ft_intlen() function computes the length of the integer nbr.
 * 
 * @param nbr Number to compute the length of.
 * @param count Count of the integer.
 * @return int Function returns the number of characters of the int.
 */
int						ft_intlen(int nbr, int count);

/**
 * @brief the ft_isalnum() function tests for any character for which ft_isalpha() or ft_isdigit() is true.
 * 
 * @param c Character to test.
 * @return t_bool Function returns TRUE if c is a letter or a digit, and FALSE otherwise.
 */
t_bool					ft_isalnum(int c);

/**
 * @brief The ft_isalpha() function tests for any character for which ft_isupper() or ft_islower() is true.
 * 
 * @param c Character to test.
 * @return t_bool Function returns TRUE if c is a letter, and FALSE otherwise.
 */
t_bool					ft_isalpha(int c);

/**
 * @brief The ft_isascii() function tests for an ASCII character, which is any character between 0 and 127 inclusive.
 * 
 * @param c Character to test.
 * @return t_bool Function returns TRUE if c is an ASCII character, and FALSE otherwise.
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
 * @return t_bool Function returns TRUE if c is a lower-case letter, and FALSE otherwise.
 */
t_bool					ft_islower(int c);

/**
 * @brief The ft_isprint() function tests for any printable character, including space.
 * 
 * @param c Character to test.
 * @return t_bool Function returns TRUE if c is a printable character, and FALSE otherwise.
 */
t_bool					ft_isprint(int c);

/**
 * @brief The ft_isupper() function tests for any upper-case letter.
 * 
 * @param c Character to test.
 * @return t_bool Function returns TRUE if c is an upper-case letter, and FALSE otherwise.
 */
t_bool					ft_isupper(int c);

/**
 * @brief The ft_itoa() function allocates (with malloc(3)) and returns a string representing the integer received as an argument.
 * Negative numbers must be handled.
 * 
 * @param n Integer to convert.
 * @return char* Function returns the string representing the integer, or NULL if the allocation fails.
 */
char					*ft_itoa(int n);

/**
 * @brief The ft_memchr() function locates the first occurrence of c (converted to an unsigned char) in the first n bytes of the memory area pointed to by memoryBlock.
 * 
 * @param memoryBlock Memory area to search.
 * @param searchedChar Character to search for.
 * @param size Number of bytes to search.
 * @return void* Function returns a pointer to the located character, or NULL if the character does not appear in the memory area.
 */
void					*ft_memchr(const void *memoryBlock, int searchedChar, size_t size);

/**
 * @brief The ft_memcmp() function compares the first n bytes of the memory areas s1 and s2.
 * 
 * @param s1 First memory area to compare.
 * @param s2 Second memory area to compare.
 * @param n Number of bytes to compare.
 * @return int Function returns an integer less than, equal to, or greater than zero if the first n bytes of s1 is found, respectively, to be less than, to match, or be greater than the first n bytes of s2.
 */
int						ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief The ft_memcpy() function copies n bytes from memory area src to memory area dest.
 * The memory areas must not overlap.
 * 
 * @param dest Destination memory area.
 * @param src Source memory area.
 * @param n Number of bytes to copy.
 * @return void* Function returns the value of dest.
 */
void					*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief The ft_memmove() function copies n bytes from memory area src to memory area dest.
 * 
 * @param dest Destination memory area.
 * @param src Source memory area.
 * @param size Number of bytes to copy.
 * @return void* Function returns the pointer of dest.
 */
void					*ft_memmove(void *dest, const void *src, size_t size);

/**
 * @brief The ft_memset() function writes len bytes of value c (converted to an unsigned char) to the string b.
 * 
 * @param s String to write to.
 * @param c Character to write.
 * @param n Number of bytes to write.
 * @return void* Function returns the value of s.
 */
void					*ft_memset(void *s, int c, size_t n);


/**
 * @brief The ft_putchar_fd() function outputs the character c to the given file descriptor.
 * 
 * @param c C
 * @param fd File descriptor on which to write.
 * @return int Function returns the number of bytes written, or -1 if an error occurred.
 */
int						ft_putchar_fd(char c, int fd);

/**
 * @brief The ft_putendl_fd() function outputs the string s to the given file descriptor, followed by a newline.
 * 
 * @param str String to output.
 * @param fd File descriptor on which to write.
 */
void					ft_putendl_fd(char *str, int fd);

/**
 * @brief The ft_putnbr_fd() function outputs the integer n to the given file descriptor.
 * 
 * @param nb Integer to output.
 * @param fd File descriptor on which to write.
 */
int						ft_putnbr_fd(int nb, int fd);

/**
 * @brief The ft_putstr_fd() function outputs the string s to the given file descriptor.
 * 
 * @param str String to output.
 * @param fd File descriptor on which to write.
 */
int						ft_putstr_fd(char *str, int fd);

/**
 * @brief The ft_split() function allocates (with malloc(3)) and returns an array of strings obtained by splitting s using the character c as a delimiter.
 * The array must be ended by a NULL pointer.
 * 
 * @param s String to split.
 * @param c Delimiter character.
 * @return char** Function returns the array of new strings resulting from the split.
 */
char					**ft_split(char const *s, char c);

/**
 * @brief The ft_strchr() function locates the first occurrence of c (converted to a char) in the string pointed to by s.
 * 
 * @param s String to search.
 * @param c Character to search for.
 * @return char* Function returns a pointer to the located character, or NULL if the character does not appear in the string.
 */
char					*ft_strchr(const char *s, int c);

/**
 * @brief Compares the two strings s1 and s2.
 * 
 * @param s1 The first string to be compared.
 * @param s2 The second string to be compared.
 * @return int Returns 0 if the strings are equal, a positive integer if s1 is greater than s2, and a negative integer if s1 is less than s2.
 */
int						ft_strcmp(char *s1, char *s2);

/**
 * @brief The ft_strcpy() function copies the string pointed to by src, including the terminating null byte (\0), to the buffer pointed to by dest.
 * 
 * @param dest Destination string.
 * @param src Source string.
 * @return char * The ft_strcpy() function returns a pointer to the destination string dest.
 */
char					*ft_strcpy(char *dest, char *src);

/**
 * @brief The ft_strdup() function allocates sufficient memory for a copy of the string s1, does the copy, and returns a pointer to it.
 * 
 * @param src String to copy.
 * @return char* Function returns a pointer to the duplicated string, or NULL if insufficient memory was available.
 */
char					*ft_strdup(char *src);

/**
 * @brief The ft_striteri() function applies the function f to each character of the string passed as argument.
 * 
 * @param s String to iterate.
 * @param f Function to apply to each character.
 */
void					ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * @brief The ft_strjoin() function allocates (with malloc(3)) and returns a new string, which is the result of the concatenation of s1 and s2.
 * 
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return char* Function returns the new string, or NULL if the allocation fails.
 */
char					*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief the ft_strlcat() function appends the NUL-terminated string src to the end of dst.
 * 
 * @param dst Destination string.
 * @param src Source string.
 * @param n n
 * @return size_t Function returns the total length of the string it tried to create.
 */
size_t					ft_strlcat(char *dst, const char *src, size_t n);

/**
 * @brief The ft_strlcpy() function copies up to size - 1 characters from the NUL-terminated string src to dst, NUL-terminating the result.
 * 
 * @param dest Destination string.
 * @param src Source string.
 * @param size n
 * @return size_t Function returns the total length of the string it tried to create.
 */
size_t					ft_strlcpy(char *dst, const char *src, size_t n);

/**
 * @brief The ft_strlen() function computes the length of the string str.
 * 
 * 
 * @param str String to compute the length of.
 * @return size_t Function returns the number of characters that precede the terminating NUL character.
 */
size_t					ft_strlen(const char *str);


/**
 * @brief The ft_strmapi() function applies the function f to each character of the string passed as argument by giving its index as first argument to create a new string resulting from successive applications of f.
 * 
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 * @return char* Function returns the string created from the successive applications of f.
 */
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));

/**
 * @brief The ft_strncmp() function compares the two strings s1 and s2.
 * It compares not more than n characters.
 * 
 * @param s1 First string to compare.
 * @param s2 Second string to compare.
 * @param n Number of characters to compare.
 * @return int Function returns an integer less than, equal to, or greater than zero if s1 is found, respectively, to be less than, to match, or be greater than s2.
 */
int						ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief The ft_strnstr() function locates the first occurrence of the null-terminated string little in the string big, where not more than len characters are searched.
 * Characters that appear after a `\0' character are not searched.
 * 
 * @param big String to search in.
 * @param little String to search for.
 * @param len Number of characters to search.
 * @return char* Function returns a pointer to the first occurrence of little in big, or a NULL pointer if little is not part of big.
 */
char					*ft_strnstr(const char *big, const char *little,
							size_t len);


/**
 * @brief The ft_strrchr() function locates the last occurrence of c (converted to a char) in the string pointed to by s.
 * 
 * @param s String to search.
 * @param c Character to search for.
 * @return char* Function returns a pointer to the located character, or NULL if the character does not appear in the string.
 */
char					*ft_strrchr(const char *s, int c);


/**
 * @brief The ft_strtrim() function allocates (with malloc(3)) and returns a copy of s1 with the characters specified in set removed from the beginning and the end of the string.
 * 
 * @param s1 The string to trim.
 * @param set The set of characters to trim.
 * @return char* Function returns the trimmed string, or NULL if the allocation fails.
 */
char					*ft_strtrim(char const *sc1, char const *set);


/**
 * @brief The substr() function allocates (with malloc(3)) and returns a substring from the string s.
 * 
 * @param s String to create the substring from.
 * @param start Start index of the substring in s.
 * @param len Length of the substring.
 * @return char* Function returns the substring, or NULL if the allocation fails.
 */
char					*ft_substr(char const *s, unsigned int start,
							size_t len);

/**
 * @brief The Function ft_tolower() converts an upper-case letter to the corresponding lower-case letter.
 * 
 * @param c Character to convert.
 * @return int Function returns the corresponding lower-case letter if c is an upper-case letter; otherwise, it returns c.
 */
int						ft_tolower(int c);

/**
 * @brief The ft_toupper() function converts a lower-case letter to the corresponding upper-case letter.
 * 
 * @param c Character to convert.
 * @return int Function returns the corresponding upper-case letter if c is a lower-case letter; otherwise, it returns c.
 */
int						ft_toupper(int c);

//* ************************************************************************** */
//* ************************************************************************** */
//*
//* 								TITLE_SCREEN
//*
//* ************************************************************************** */
//* ************************************************************************** */

/**
 * @brief The title_screen() function displays a title screen in ASCII art with the given title and color.
 * 
 * @param title Title to display.
 * @param color Color to use for the title.
 */
void					title_screen(char *title, char *color);

/**
 * @brief The letter_creation() function creates a chain list of letters from the given model.
 * 
 * @param model Model to create the letters from.
 * @return char** F
 */
char					**letter_creation(const char *model);

/**
 * @brief the for_a_to_l() function creates the letters from A to L.
 * 
 * @param c Character to create.
 * @param chara Chain list of letters.
 */
void					for_a_to_l(char c, t_alphanode **chara);

/**
 * @brief The for_m_to_x() function creates the letters from M to X.
 * 
 * @param c Character to create.
 * @param chara Chain list of letters.
 */
void					for_m_to_x(char c, t_alphanode **chara);

/**
 * @brief The for_y_to_9() function creates the letters from Y to Z and from 0 to 9.
 * 
 * @param c Character to create.
 * @param chara Chain list of letters.
 */
void					for_y_to_9(char c, t_alphanode **chara);


/**
 * @brief The insert_front_alpha() function inserts a letter at the front of the chain list.
 * 
 * @param head Head of the chain list.
 * @param letter Letter to insert.
 */
void					insert_front_alpha(t_alphanode **head, char **letter);

/**
 * @brief The insert_after_alpha() function inserts a letter after the given node in the chain list.
 * 
 * @param prev_node Node after which to insert the letter.
 * @param letter Letter to insert.
 */
void					insert_after_alpha(t_alphanode *prev_node,
							char **letter);

/**
 * @brief The insert_end_alpha() function inserts a letter at the end of the chain list.
 * 
 * @param head Head of the chain list.
 * @param letter Letter to insert.
 */
void					insert_end_alpha(t_alphanode **head, char **letter);

/**
 * @brief The display_alpha() function displays the chain list of letters.
 * 
 * @param node Node to start the display from.
 */
void					display_alpha(t_alphanode *node);

/**
 * @brief The cmp_letter_list() function compares the given letter with the letters in the chain list.
 * 
 * @param node Node to start the comparison from.
 * @param letter Letter to compare.
 * @return int Function returns TRUE if the letter is found in the chain list, and FALSE otherwise.
 */
int						cmp_letter_list(t_alphanode *node, char **letter);

/**
 * @brief The delete_alphanode() function deletes the given node from the chain list.
 * 
 * @param head Head of the chain list.
 * @param del_node Node to delete.
 */
void					delete_alphanode(t_alphanode **head,
							t_alphanode *del_node);

/**
 * @brief The delete_all_alphanodes() function deletes all the nodes from the chain list.
 * 
 * @param head Head of the chain list.
 */
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

//* ************************************************************************** */
//* ************************************************************************** */
//*
//* 								CHAIN LIST
//*
//* ************************************************************************** */
//* ************************************************************************** */

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

//* ************************************************************************** */
//* ************************************************************************** */
//*
//* 								DOUBLE CHAIN LIST
//*
//* ************************************************************************** */
//* ************************************************************************** */

void					delete_node(t_node **head, t_node *del_node);
void					delete_all_nodes(t_node **head);
void					insert_front(t_node **head, int value);
void					insert_after(t_node *prev_node, int value);
void					insert_end(t_node **head, int value);
void					display_list(t_node *stack);
int						cmp_value_list(t_node *node, int value);

//* ************************************************************************** */
//* ************************************************************************** */
//*
//* 								FT_PRINTF_FUNCTIONS
//*
//* ************************************************************************** */
//* ************************************************************************** */

size_t					ft_putptr(size_t nbr, int base, char *table);
void					ft_rev_wr(char *str);
int						ft_printf(const char *format, ...);
int						marshalling(char c, va_list list_arg);
size_t					ft_putchar(char c);
size_t					ft_putstr(char *str);
size_t					ft_putbase(unsigned int nbr, int base, char *table);
size_t					ft_putnbr(long long nb);
int    ft_printf_fd(int fd, const char *format, ...);

//* ************************************************************************** */
//* ************************************************************************** */
//*
//* 								GNL_FUNCTIONS
//*
//* ************************************************************************** */
//* ************************************************************************** */

char					*get_next_line(int fd);

/**
 * @brief The ft_strjoin_f() function allocates (with malloc(3)) and returns a new string, which is the result of the concatenation of s1 and s2.
 * The function also frees the strings s1.
 * 
 * @param s1 String to concatenate and free.
 * @param s2 String to concatenate.
 * @return char* Function returns the new string, or NULL if the allocation fails.
 */
char					*ft_strjoin_f(char *s1, char *s2);

/**
 * @brief The ft_strjoin_f2() function allocates (with malloc(3)) and returns a new string, which is the result of the concatenation of s1 and s2.
 * The function also frees the strings s2.
 * 
 * @param s1 String to concatenate.
 * @param s2 String to concatenate and free.
 * @return char* Function returns the new string, or NULL if the allocation fails.
 */
char					*ft_strjoin_f2(char *s1, char *s2);

char					*fill_bucket(char *buffer);
char					*ft_read(int fd, char *static_buffer);

/**
 * @brief The ft_strlen_endc() function computes the length of the string str up to the character c.
 * 
 * @param str String to compute the length of.
 * @param c Character to stop at.
 * @return int Function returns the number of characters that precede characters passed in argument.
 */
int						ft_strlen_endc(const char *str, int c);

/**
 * @brief The ft_free() function frees the given buffer and returns NULL.
 * 
 * @param buffer Pointer to the buffer to free.
 * @return char* Function returns NULL.
 */
char	*ft_free(char *buffer);

//* ************************************************************************** */
//* ************************************************************************** */
//*
//* 								STATE_FUNCTIONS
//*
//* ************************************************************************** */
//* ************************************************************************** */

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

//* ************************************************************************** */
//* ************************************************************************** */
//*
//* 								ADDITONAL_FUNCTIONS
//*
//* ************************************************************************** */
//* ************************************************************************** */

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
int count_words(const char *s, char c);

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
