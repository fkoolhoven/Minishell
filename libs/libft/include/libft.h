/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 13:26:40 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/07 11:27:08 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/select.h>
# include "./../src/printf/ft_printf.h"
# include "./../src/get_next_line/get_next_line.h"

//FUNCTIONS WITH CHARS -----------------------
int		ft_isalpha(int nb);
/*This function returns one when the input is 
 * a uppercase or lowercase letter in ASCII. 
 * Otherwise, it returns zero.*/
int		ft_isdigit(int nb);
/*This function returns one when 
 * the input represents a digit in ASCII. 
 * Otherwise, it returns a zero.*/
int		ft_isalnum(int nb);
/*This function returns one when the input 
 * is a capital letter, lowercase letter or 
 * digit in ASCII. 
 * Otherwise, it returns zero.*/
int		ft_isascii(int nb);
/*This function returns one when the input 
 * is an ASCII value. 
 * Otherwise, it returns zero.*/
int		ft_isprint(int nb);
/*This function returns a one when the input 
 * represents a printable character in ASCII. 
 * Otherwise, it returns a zero.*/
int		ft_toupper(int c);
/*This function returns the uppercase letter 
 * representation in ASCII of c if c is a lowercase letter. 
 * Otherwise, it returns c.*/
int		ft_tolower(int c);
/*This function returns the lowercase letter 
 * representation in ASCII of c if c is an uppercase letter. 
 * Otherwise, it returns c.*/

// FUNCTIONS FOR CONVERSION ---------------------
int		ft_atoi(const char *str);
/*This function converts the initial portion of 
 * the input string pointed to by str to an int and 
 * returns this value. 
 * If an error occurs the function returns zero. 
 * Not protected for overflow.*/
char	*ft_itoa(int n);
/*This function converts the input to a string. 
 * If an error occurs the function returns NULL.*/
char	*ft_itoa_base(int n, int base, char *base_str);
/*This function converts the integer n to a string. 
 * The integer n will be converted in the given base 
 * as given in the base string pointed to by base_str. 
 * If an error occurs the function returns a NULL-pointer.*/
char	*ft_luitoa_base(long unsigned int n, int base, char *base_str);
/*This function converts the long unsigned integer n to a string. 
 * The integer n will be converted in the given base as 
 * given in the base string pointed to by base_str. 
 * If an error occurs the function returns a NULL-pointer.*/

// FUNCTIONS TO OUTPUT TO FD --------------------
void	ft_putchar_fd(char c, int fd);
/*Outputs the given character c to the given file descriptor.*/
void	ft_putstr_fd(char *s, int fd);
/*Outputs the given string s to the given file descriptor.*/
void	ft_putendl_fd(char *s, int fd);
/*Outputs the given string s to the given 
 * file descriptor followed by a newline.*/
void	ft_putnbr_fd(int n, int fd);
/*Outputs the given number n in base ten 
 * to the given file descriptor.*/
void	ft_putnbr_fd_base(int n, int base, char *sbase, int fd);
/*Outputs the given number n in base base 
 * to the given file descriptor.*/
void	ft_putlui_fd_base(long unsigned int n, int base, char *sb, int fd);
/*Outputs the given number n in base base 
 * to the given file descriptor.*/

// FUNCTIONS FOR MEMORY ------------------------
void	*ft_memset(void *b, int c, size_t len);
/*This function changes the memory pointed to by b 
 * until len bytes to the given value c. 
 * If b is a NULL-pointer, 
 * the function returns b without changing its contents.*/
void	ft_bzero(void *str, size_t n);
/*This function sets everything until n bytes 
 * in the container pointed to by str to NULL.*/
void	*ft_memcpy(void *dst, const void *src, size_t n);
/*This function copies n bytes of the 
 * content in src to dst. 
 * It returns NULL if src or dst is a NULL-pointer. 
 * Otherwise, it returns dst. 
 * If n is bigger than the size of dst or src, 
 * this function has undefined behavior.*/
void	*ft_memmove(void *dst, const void *src, size_t n);
/*This function moves n bytes from src in to dst. 
 * If src or dst is a NULL-pointer, 
 * the function returns NULL. 
 * Otherwise, the function returns dst. 
 * If n is bigger than size of src or dst, 
 * the function has undefined behavior.*/
void	*ft_memchr(const void *str, int c, size_t n);
/*This function searches n bytes for c in str byte by byte. 
 * If it found c, it returns a pointer to c in str. 
 * Otherwise, the function returns NULL. 
 * If str is NULL, it returns NULL.*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);
/*This function compares n bytes of s1 and s2 
 * byte by byte and returns the difference between two bytes.*/
void	*ft_calloc(size_t cnt, size_t size);
/*This function allocates memory of size*cnt and 
 * returns a pointer pointing to this memory. 
 * When an error occurs this function returns NULL.*/

// FUNCTIONS FOR STRINGS --------------------
size_t	ft_strlen(const char *str);
/*This function returns the amount of characters in 
 * the string pointed to by str. 
 * If str is a NULL-pointer, it returns zero.*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
/*This function copies (dstsize - 1) bytes of 
 * string src in to string dst, and null-terminates string dst. 
 * This function always returns the length of string src.*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
/*This function concatenates src to dst, 
 * if dstsize allows it. 
 * The return value is the length of 
 * the string the function tried to create.*/
char	*ft_strchr(const char *str, int c);
/*This function looks for the character c in str. 
 * It returns the pointer to the character in str. 
 * If str is a NULL-pointer or c does not appear in str, 
 * it returns NULL.*/
char	*ft_strrchr(const char *str, int c);
/*This function looks for the character c 
 * in str from end to beginning. 
 * It returns the pointer to the character in str. 
 * If str is a NULL-pointer or c does not appear in str, 
 * it returns NULL.*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/*This function compares two strings, 
 * and returns the difference between either the last characters, 
 * or two charachters which are different.*/
char	*ft_strnstr(const char *hay, const char *ndl, size_t len);
/*This function returns a pointer to the first character 
 * of ndl found in hay.
 * If ndl is not found in hay, 
 * or ndl or hay is NULL, the function returns NULL.*/
char	*ft_strdup(const char *str);
/*This function makes a new string and copies str 
 * in to the new string. 
 * It returns the pointer to the new string, 
 * or NULL if an error occurs.*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
/*This function creates a new string containing 
 * the characters in s from start to (start+len). 
 * If an error occurs or s is NULL, 
 * the function returns NULL.*/
char	*ft_strjoin(char const *s1, char const *s2);
/*This function creates a new string, 
 * and fills it with the characters in s1 and 
 * then with the characters in s2. 
 * If s1 and s2 are NULL, 
 * or an error occurs the function returns NULL.*/
char	*ft_strtrim(char const *s, char const *set);
/*This function allocates with malloc and 
 * returns a copy of s1 with the characters specified 
 * in set removed from beginning and end of the string. 
 * If malloc fails the function returns NULL. 
 * If s1 is NULL or s1 and set are NULL, 
 * the function returns NULL. */
char	**ft_split(char const *s, char c);
/*This function allocates (with malloc) and 
 * returns an array of strings obtained 
 * by splitting s using the character c as a delimiter. 
 * The array ends with NULL. If a malloc fails, 
 * or s is NULL, the function returns NULL.*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/*This function allocates and 
 * returns a string obtained from succesive applications 
 * of f to each character of the string s. 
 * If s is NULL or the malloc failed, the function returns NULL.*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
/*This function changes the character in s 
 * by applying the function f() on each character of s, 
 * passing the function f() its index first and 
 * then the pointer to the character. 
 * If s is NULL, the function does not do anything.*/

// SINGLE LINKED LIST STRUCT AND FUNCTIONS ------
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
/*Allocates (with malloc) and 
 * returns a new list element with the given content.*/
void	ft_lstadd_front(t_list **lst, t_list *new);
/*This function adds the list element new to the front of the list *lst.*/
int		ft_lstsize(t_list *lst);
/*This function returns the amount of list elements in the given lst.*/
t_list	*ft_lstlast(t_list *lst);
/*This function returns the pointer to the last list element 
 * of the list lst. 
 * If lst is NULL, it returns NULL.*/
void	ft_lstadd_back(t_list **lst, t_list *new);
/*This function adds the new list element to the end of the list lst.*/
void	ft_lstiter(t_list *lst, void (*f)(void *));
/*This function iterates through the list lst and 
 * applies the given function f to the content of each node.*/
void	ft_lstclear(t_list **lst, void (*del)(void *));
/*This function deletes and frees every node in lst 
 * using the given del function and free. 
 * The pointer to list is set to NULL.*/
void	ft_lstdelone(t_list *lst, void (*del)(void *));
/*This function deletes and frees the list node pointed to by lst, 
 * using the given delete function.*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/*This function iterates the list lst and 
 * applies the given function f on the content of 
 * each node to create a new list. 
 * To create a new node, this function allocates memory using malloc, 
 * if malloc fails the function returns NULL.*/

#endif
