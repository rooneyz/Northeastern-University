/*
 * assignment-5.c
 *
 *  Created on: Jun 1, 2019
 *      Author: phil
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * Monitor for currently dealt card.
 * Simplest way to create monitor, no function calls needed.
 */
pthread_mutex_t card_lock = PTHREAD_MUTEX_INITIALIZER;

/**
 * Condition for player to notify dealer that dealt card was taken.
 * Simplest way to create condition, no function calls needed.
 */
pthread_cond_t taken_cond = PTHREAD_COND_INITIALIZER;

/**
 * Condition for dealer to notify players that card was dealt.
 * Simplest way to create condition, no function calls needed.
 */
pthread_cond_t dealt_cond = PTHREAD_COND_INITIALIZER;

/** Number of players. */
#define N_PLAYERS  4

/** Constant number of cards per hand */
#define N_CARDS  5

/** Type definition for card as unsigned 8-bit value. */
typedef uint8_t card_t;

/** Type definition for a deck of 52 cards */
typedef card_t deck_t[52];

/** Type definition for a hand of N_CARDS */
typedef card_t hand_t[N_CARDS];

/** Constant represents no card. */
#define NO_CARD  0

/**  Currently dealt card. Access only within card_lock monitor. */
card_t dealt_card = NO_CARD;

/** Gets card for suit and value. */
static inline card_t makeCard(unsigned suit, unsigned val) { return suit*16 + val; }

/** Gets suit for card (H=0,  D=1, C=2, S=3). */
static inline unsigned getCardSuit(card_t card) { return card/16; }

/** Gets value for card: A=1, ... J=11, Q=12, K=13. */
static inline unsigned getCardValue(card_t card) { return card%16; }

/**
 * Returns a string representation of the card.
 *
 * @param card the card
 * @param cardstr storage for the string
 */
void cardToStr(card_t card, char cardstr[]) {
	// unicode strings for suits: H, D, C, S
	static char *suits[] = {"\u2661", "\u2662", "\u2667", "\u2664"};
	// strings for values
	static char *values[] = {"", "A", "2", "3", "4", "5", "6",
							 "7", "8", "9", "10", "J", "Q", "K"};
	unsigned suit = getCardSuit(card);
	unsigned val = getCardValue(card);
	sprintf(cardstr, "%s(%s)", values[val], suits[suit]);
}

/**
 * Make deck of 52 cards in 4 suits and 13 values.
 *
 * @param deck the deck
 */
void makeDeck(deck_t deck) {
	int decknum = 0;
	for (unsigned suit = 0; suit <= 3; suit++) {
		for (unsigned val = 1; val <= 13; val++) {
			deck[decknum++] = makeCard(suit, val);
		}
	}
}

/**
 * Shuffle a deck of 52 cards using Fisher-Yates algorithm.
 * Source:
 * https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
 *
 * @param deck the deck
 */
void shuffleDeck(deck_t deck) {
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand(time(NULL));

	for (unsigned cardno = 51; cardno > 0 ; cardno--) {
        // Pick a random index from 0 to i
        unsigned randno = rand() % (cardno+1);

		// exchange cards
		card_t card = deck[cardno];
		deck[cardno] = deck[randno];
		deck[randno] = card;
	}
}

/**
 * This thread function represents a player who
 * is waiting for the next card to be dealt. When
 * a card is available, adds the card to the hand
 * array and sets the dealt card to NO_CARD to
 * indicate that the card was taken.
 *
 * @param arg a hand of N_CARDS to complete
 * 	note: hand[0] initialized to player number
 */
void *player(void *arg) {
	card_t *hand = arg;  // hand_t
	unsigned pnum = hand[0];
	char cardstr[10];

	pthread_mutex_lock(&card_lock);  // card_lock critical section
		// wait for dealt card to become available,
		// then take and signal dealt card taken
		for (unsigned cnum = 0; cnum < N_CARDS; cnum++) {
			// wait for dealt card to become available
			if (dealt_card == NO_CARD) {
				printf("player%d: waiting for card %d\n", pnum, cnum);
				// wait for a card
				do {
					pthread_cond_wait(&dealt_cond, &card_lock); // yields lock
				} while (dealt_card == NO_CARD);

			}

			// take and add dealt card to hand
			cardToStr(dealt_card, cardstr);
			printf("player%d: taking card %d: %s\n", pnum, cnum, cardstr);
			hand[cnum] = dealt_card;
			dealt_card = NO_CARD;

			// signal that dealt card was taken
			pthread_cond_signal(&taken_cond);

		}
	pthread_mutex_unlock(&card_lock); // unlock critical section
	printf("player%d: has a full hand of %d cards\n", pnum, N_CARDS);

	return NULL;
}

/**
 * This function represents a dealer who shuffles a
 * deck of cards, and then deals N_CARDS cards to each
 * of N_PLAYERS from a deck of cards.
 *
 * @param deck deck of 52 cards
 * @return number of cards dealt
 */
unsigned dealer(deck_t deck) {
	char cardstr[10];
	unsigned ndealt = 0;

	// shuffle the deck before dealing
	shuffleDeck(deck);

	pthread_mutex_lock(&card_lock);  // card_lock critical section
		// deal and signal card dealt, and wait for card to be taken
		unsigned n2deal = N_CARDS * N_PLAYERS;
		for (; ndealt < n2deal; ndealt++) {
			// deal card
			dealt_card = deck[ndealt];
			cardToStr(dealt_card, cardstr);
			printf("dealer: dealing card %2d: %s\n", ndealt, cardstr);

			// signal that card was dealt
			pthread_cond_signal(&dealt_cond);

			// wait for dealt card to be taken
			do {
				pthread_cond_wait(&taken_cond, &card_lock); // yields lock
			} while (dealt_card != NO_CARD);
		}
	pthread_mutex_unlock(&card_lock); // unlock critical section
	return ndealt;
}

/**
 * This program represents
 * @return
 */
int main(void) {
	pthread_t players[N_PLAYERS];  // threads for N_PLAYERS
	hand_t hands[N_PLAYERS];  // hands for N_PLAYERS
	char cardstr[10];  // card string representation

	setlinebuf(stdout);

	pthread_mutex_lock(&card_lock);  // card_lock critical section
		// create the players
		for (unsigned pnum = 0; pnum < N_PLAYERS; pnum++) {
			hands[pnum][0] = pnum;  // pass player no.
			pthread_create(players+pnum, NULL, player, hands[pnum]);
		}
	pthread_mutex_unlock(&card_lock); // unlock critical section

	// make deck of cards
	deck_t deck;
	makeDeck(deck);

	// dealer deals deck to players
	unsigned ndealt = dealer(deck);
	printf("main: dealer dealt %u cards to %u players\n", ndealt, N_PLAYERS);

	// print hands
	for (unsigned pnum = 0; pnum < N_PLAYERS; pnum++) {
		pthread_join(players[pnum], NULL);	// wait for player to complete

		printf("hand %d: ", pnum+1);
		for (unsigned cnum = 0; cnum < N_CARDS; cnum++) {
			// print representation of card in player's hand
			cardToStr(hands[pnum][cnum], cardstr);
			printf("%s  ", cardstr);
		}
		printf("\n");
	}
}
