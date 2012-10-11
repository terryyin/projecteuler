/*
 * pokerHand.h
 *
 *  Created on: Oct 20, 2011
 *      Author: yinterry
 */

#ifndef POKERHAND_H_
#define POKERHAND_H_

static int cmp_char(const void * s1, const void * s2)
{
	return (*(char *) s1 - *(char *) s2);
}
class pokerHand
{
	enum {CARD_COUNT=5};
public:
	pokerHand(const char *handString)
	{
		char cards[CARD_COUNT];
		for (int i = 0; i < CARD_COUNT; i++) cards[i] = convertCardNumber(handString[i * 3]);
		qsort(cards, CARD_COUNT, sizeof(cards[0]), cmp_char);
		score = 0;
		add_to_score(score, 1);
		add_to_score(score, (getStraight(cards)!=0 && getFlush(handString)!=0) ? 1 : 0);
		add_to_score(score, getSameKind(cards, 4));
		add_to_score(score, (getSameKind(cards, 3)!=0 && getSameKind(cards, 2)!=0) ? 1 : 0);
		add_to_score(score, getFlush(handString));
		add_to_score(score, getStraight(cards));
		add_to_score(score, getSameKind(cards, 3));
		add_to_score(score, getSameKind(cards, 2), 2);
		for (int i = CARD_COUNT - 1; i >= 0; i--)
			add_to_score(cards[i]);
	}
	bool operator<(pokerHand other)
	{
		return compareTo(other) < 0;
	}
	bool operator>(pokerHand other)
	{
		return compareTo(other) > 0;
	}
	long long compareTo(pokerHand& hand)
	{
		return score - hand.score;
	}
	unsigned long long getScore()
	{
		return score;
	}
	unsigned long long getUpperScore()
	{
		return score>>20;
	}
private:
	long long getSameKind(const char * cards, int count)
	{
		unsigned long long s = 0;
		for (int i = (CARD_COUNT - 1); i > count - 2; i--)
		{
			int j;
			for (j = 1; j < count; j++)
			if (cards[i] != cards[i - j])
				break;
			if (j == count){
				if (i < count || cards[i] != cards[i -  count]){
					add_to_score(s, cards[i]);
				}
				i -= (j -1);
			}
		}
		return s;
	}
	long long getStraight(const char * cards) {
		for(int i = 0; i < CARD_COUNT - 1; i++)
			if (cards[i] + 1 != cards[i+1])
				return 0;
		return 1;
	}
	long long getFlush(const char * hand) {
		for(int i = 0; i < CARD_COUNT - 1; i++)
			if (hand[i*3+1] != hand[i * 3 + 4])
				return 0;
		return 1;
	}
	char convertCardNumber(char face)
	{
		switch (face)
		{
		case 'T': return 10;
		case 'J': return 11;
		case 'Q': return 12;
		case 'K': return 13;
		case 'A': return 14;
		}
		return face - '0';
	}
	void add_to_score(unsigned long long& score, unsigned long long value, int count = 1)
	{
		const unsigned long long grade = 4;
		score = (score << (grade * count)) + value;
	}
	void add_to_score(char value)
	{
		add_to_score(score, value);
	}
	unsigned long long score;

};
#endif /* POKERHAND_H_ */
