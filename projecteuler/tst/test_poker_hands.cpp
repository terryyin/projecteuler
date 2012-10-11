#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "pokerHand.h"
TEST_GROUP(poker_hand){

};

TEST(poker_hand, comparing){
	CHECK(pokerHand("4H 5C 6S 7S TD")< pokerHand("2C 3S 7S 8D KD"));
	CHECK(!(pokerHand("4H 5C 6S 7S KD")< pokerHand("2C 3S 7S 8D TD")));
	CHECK(pokerHand("4H 5C 6S 7S KD")> pokerHand("2C 3S 7S 8D TD"));
}
TEST(poker_hand, compare_cards){
	CHECK(pokerHand("3H 5C 6S 7S 8D")< pokerHand("4H 5C 6S 7S 9D"));
	CHECK(pokerHand("3H 5C 6S 7S 9D")< pokerHand("4H 5C 6S 7S TD"));
	CHECK(pokerHand("3H 5C 6S 7S TD")< pokerHand("4H 5C 6S 7S JD"));
	CHECK(pokerHand("3H 5C 6S 7S JD")< pokerHand("4H 5C 6S 7S QD"));
	CHECK(pokerHand("3H 5C 6S 7S QD")< pokerHand("4H 5C 6S 7S KD"));
	CHECK(pokerHand("3H 5C 6S 7S KD")< pokerHand("4H 5C 6S 7S AD"));
}
TEST(poker_hand, compare_high_cards_2nd){
	CHECK(pokerHand("3H 5C 6S 7S 9D")< pokerHand("3H 5C 6S 8S 9D"));
}
TEST(poker_hand, compare_high_cards_3nd_4_5){
	CHECK(pokerHand("3H 5C 6S 8S 9D")< pokerHand("3H 5C 7S 8S 9D"));
	CHECK(pokerHand("3H 4C 7S 8S 9D")< pokerHand("3H 5C 7S 8S 9D"));
	CHECK(pokerHand("2H 5C 7S 8S 9D")< pokerHand("3H 5C 7S 8S 9D"));
}
TEST(poker_hand, compare_high_card_and_one_pair){
	CHECK(pokerHand("3H 5C 6S 8S 9D")< pokerHand("3H 5C 7S 8S 8D"));
}
TEST(poker_hand, compare_one_pairs){
	CHECK(pokerHand("3H 5C 6S 9S 9D")> pokerHand("3H 5C 7S 8S 8D"));
	CHECK(pokerHand("5C 6S 9S 9D KD")> pokerHand("5C 7S 8S 8D AD"));
	CHECK(pokerHand("5C 6S 9S 9D KD")< pokerHand("5C 7S 9S 9D AD"));
}

TEST(poker_hand, compare_one_pair_and_two_pairs){
	CHECK(pokerHand("3H 5C 6S 9S 9D")< pokerHand("3H 3C 7S 8S 8D"));
}
TEST(poker_hand, compare_two_pairs){
	CHECK(pokerHand("3H 5C 5S 9S 9D")> pokerHand("3H 3C 7S 8S 8D"));
	CHECK(pokerHand("5C 5S 8S 9S 9D")> pokerHand("3H 3C 7S 9S 9D"));
}
TEST(poker_hand, compare_two_pairs_and_three_of_a_kind){
	CHECK(pokerHand("3H 5C 5S 9S 9D")< pokerHand("3H 3C 3S 8S 9D"));
}
TEST(poker_hand, compare_three_of_a_kind){
	CHECK(pokerHand("3H 5C 5S 5S 8D")> pokerHand("3H 3C 3S 8S 9D"));
	CHECK(pokerHand("3H 5C 5S 5S 8D")> pokerHand("3H 3C 3S 7S 8D"));
}
TEST(poker_hand, compare_three_of_a_kind_and_straight){
	CHECK(pokerHand("3H 5C 5S 5S 8D")< pokerHand("3H 4C 5S 6S 7D"));
}
TEST(poker_hand, compare_straight){
	CHECK(pokerHand("4H 5C 6S 7S 8D")> pokerHand("3H 4C 5S 6S 7D"));
}
TEST(poker_hand, compare_straight_and_flush){
	CHECK(pokerHand("4H 5C 6S 7S 8D")< pokerHand("3H 4H 5H 6H 8H"));
}
TEST(poker_hand, compare_flush){
	CHECK(pokerHand("3C 5C 6C 7C 8C")> pokerHand("3H 4H 5H 6H 8H"));
}
TEST(poker_hand, compare_flush_and_full_house){
	CHECK(pokerHand("3C 5C 6C 7C 8C")< pokerHand("3H 3C 3S 8S 8D"));
}
TEST(poker_hand, compare_full_house){
	CHECK(pokerHand("2H 2D 4C 4D 4S")> pokerHand("3C 3D 3S 9S 9D"));
}
TEST(poker_hand, compare_full_house_and_four_of_a_kind){
	CHECK(pokerHand("2H 2D 4C 4D 4S")< pokerHand("3C 3D 3S 3S 9D"));
}
TEST(poker_hand, compare_four_of_a_kind){
	CHECK(pokerHand("2H 2D 2C 2D TS")< pokerHand("3C 3D 3S 3S 9D"));
}
TEST(poker_hand, compare_four_of_a_kind_and_straight_flush){
	CHECK(pokerHand("2H 3H 4H 5H 6H")> pokerHand("3C 3D 3S 3S 9D"));
}
