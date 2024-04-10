/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_triage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aska <aska@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 11:51:39 by aska              #+#    #+#             */
/*   Updated: 2024/02/27 20:20:12 by aska             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	for_a_to_l(char c, t_alphanode **chara)
{
	if (c == 'a' || c == 'A')
		insert_end_alpha(chara, letter_creation(A));
	if (c == 'b' || c == 'B')
		insert_end_alpha(chara, letter_creation(B));
	if (c == 'c' || c == 'C')
		insert_end_alpha(chara, letter_creation(C));
	if (c == 'd' || c == 'D')
		insert_end_alpha(chara, letter_creation(D));
	if (c == 'e' || c == 'E')
		insert_end_alpha(chara, letter_creation(E));
	if (c == 'f' || c == 'F')
		insert_end_alpha(chara, letter_creation(F));
	if (c == 'g' || c == 'G')
		insert_end_alpha(chara, letter_creation(G));
	if (c == 'h' || c == 'H')
		insert_end_alpha(chara, letter_creation(H));
	if (c == 'i' || c == 'I')
		insert_end_alpha(chara, letter_creation(I));
	if (c == 'j' || c == 'J')
		insert_end_alpha(chara, letter_creation(J));
	if (c == 'k' || c == 'K')
		insert_end_alpha(chara, letter_creation(K));
	if (c == 'l' || c == 'L')
		insert_end_alpha(chara, letter_creation(L));
}

void	for_m_to_x(char c, t_alphanode **chara)
{
	if (c == 'm' || c == 'M')
		insert_end_alpha(chara, letter_creation(M));
	if (c == 'n' || c == 'N')
		insert_end_alpha(chara, letter_creation(N));
	if (c == 'o' || c == 'O')
		insert_end_alpha(chara, letter_creation(O));
	if (c == 'p' || c == 'P')
		insert_end_alpha(chara, letter_creation(P));
	if (c == 'q' || c == 'Q')
		insert_end_alpha(chara, letter_creation(Q));
	if (c == 'r' || c == 'R')
		insert_end_alpha(chara, letter_creation(R));
	if (c == 's' || c == 'S')
		insert_end_alpha(chara, letter_creation(S));
	if (c == 't' || c == 'T')
		insert_end_alpha(chara, letter_creation(T));
	if (c == 'u' || c == 'U')
		insert_end_alpha(chara, letter_creation(U));
	if (c == 'v' || c == 'V')
		insert_end_alpha(chara, letter_creation(V));
	if (c == 'w' || c == 'W')
		insert_end_alpha(chara, letter_creation(W));
	if (c == 'x' || c == 'X')
		insert_end_alpha(chara, letter_creation(X));
}

void	for_y_to_9(char c, t_alphanode **chara)
{
	if (c == 'y' || c == 'Y')
		insert_end_alpha(chara, letter_creation(Y));
	if (c == 'z' || c == 'Z')
		insert_end_alpha(chara, letter_creation(Z));
	if (c == '0')
		insert_end_alpha(chara, letter_creation(ZERO));
	if (c == '1')
		insert_end_alpha(chara, letter_creation(ONE));
	if (c == '2')
		insert_end_alpha(chara, letter_creation(TWO));
	if (c == '3')
		insert_end_alpha(chara, letter_creation(THREE));
	if (c == '4')
		insert_end_alpha(chara, letter_creation(FOUR));
	if (c == '5')
		insert_end_alpha(chara, letter_creation(FIVE));
	if (c == '6')
		insert_end_alpha(chara, letter_creation(SIX));
	if (c == '7')
		insert_end_alpha(chara, letter_creation(SEVEN));
	if (c == '8')
		insert_end_alpha(chara, letter_creation(EIGHT));
	if (c == '9')
		insert_end_alpha(chara, letter_creation(NINE));
}

void	for_symbol(char c, t_alphanode **chara)
{
	if (c == ' ')
		insert_end_alpha(chara, letter_creation(SPACE));
	if (c == ',')
		insert_end_alpha(chara, letter_creation(COMMA));
	if (c == '.')
		insert_end_alpha(chara, letter_creation(DOT));
	if (c == '-')
		insert_end_alpha(chara, letter_creation(HYPHEN));
	if (c == '_')
		insert_end_alpha(chara, letter_creation(UNDERSCORE));
	if (c == '(')
		insert_end_alpha(chara, letter_creation(BRACKET_ON));
	if (c == ')')
		insert_end_alpha(chara, letter_creation(BRACKET_OFF));
	if (c == '*')
		insert_end_alpha(chara, letter_creation(ASTERISK));
}
