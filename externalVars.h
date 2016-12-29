const int cardsInSuit = 13;				//13 cards per suit (Ace to King)
const int noOfSuits = 4;				//4 suits (Hearts, Diamonds, Spades, and Clubs)
extern int deck[noOfSuits*cardsInSuit];	//52 card deck
extern int aiAceCounter;				//Ace counters used in determining whether an ace counts as 1 or 11
extern int playerAceCounter;
extern int playerTotal;
extern int aiTotal;