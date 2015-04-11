#include <math.h>
#include "../Cards/Card.h"
#include "../Player/Player.h"
#include "../Map/Map.h"


class Reinforcement
{
public:
	// Constructor
	Reinforcement(Player *p, int *cardBonusCt);
	
	// Others
	void countTerritories();
	void countContinents();
	void countCards();
	void reinforce();
		
private:
	// Attributes
	Player *mCurrent;
	int numOfR;
	int *cardBonusCt;
	bool useCard;

	// Methods
	//int* updateCardBonus();
	bool checkMinCondition();
	void exchangeCards();
	void checkCardName(Card* exchangeSet[3]);
};


