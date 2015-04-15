#include <math.h>
#include "../Cards/Card.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "Phase.h"

class Reinforcement :public Phase
{
public:
	// Constructor
	Reinforcement(int ct);
	virtual ~Reinforcement();
	
	// Others
	void countTerritories();
	void countContinents();
	void countCards();
	void reinforce();
	bool checkMinCondition();
	void exchangeCards(std::vector<Card*> cards);
	void checkCardName(Card* exchangeSet[3]);
	bool sameType(Card* exchangeSet[3]);
	bool uniqueType(Card* exchangeSet[3]);
	int updateCardBonus();
	void updatePDeck(Card* exchangeSet[3]/*c1, Card* c2, Card* c3*/, std::vector<Card*> cards);
	void placeReinforcement();
	void run(Player* player);

private:
	// Attributes
	Player *mCurrent;
	int numOfR;
	int cardBonusCt; // Takes the current reinforcement value of the game
	bool exchange;
	bool useCard;
};


