#include <math.h>
#include "../Cards/Card.h"
#include "../Player/Player.h"
#include "../Map/Map.h"


class Reinforcement
{
public:
	// Constructor
	Reinforcement(Player* p, int cardBonusCt);
	
	// Others
	void countTerritories();
	void countContinents();
	void countCards();
	void reinforce();
	bool checkMinCondition();
	void exchangeCards(std::vector<Card*> cards);
	void checkCardName(Card* exchangeSet[3]);
	bool Reinforcement::sameType(Card* exchangeSet[3]);
	bool Reinforcement::uniqueType(Card* exchangeSet[3]);
	int updateCardBonus();
	void updatePDeck(Card* exchangeSet[3]/*c1, Card* c2, Card* c3*/, std::vector<Card*> cards);

private:
	// Attributes
	Player *mCurrent;
	int numOfR;
	int cardBonusCt; // Takes the current reinforcement value of the game
	bool exchange;
	bool useCard;
};


