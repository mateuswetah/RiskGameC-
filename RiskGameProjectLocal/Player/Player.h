#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <string>
#include <vector>
#include "../Cards/Card.h"
#include "../ObservablePattern/Observable.h"
#include "../Map/Map.h"

class Player : public Observable
{
public:
	Player();
	Player(int n);
	Player(std::string name);
	/*int getOrder();
	Continent getContinent();
	Card getCard();
	void setOrder();*/
std::string getColor();
	void setColor(std::string color);
	void setName(std::string n);
	void setTurnState(bool state);
	std::string getName();
	int getNumber();
	void setNArmy(int a);
	int getNArmy();
	bool getTurnState();
/*	void incArmy();
	void decArmyToPlace();*/
	void winTerritory();
/*	void loseTerritory(); */
	int getNTerritory();
//	void addCard();
	int getNCard();
	void setNCard(int i);
	void setOrder(int o);
	bool getHasNewTerritory();
	void setHasNewTerritory(bool b);
	void setNReinforcement(int n);
	int getNReinforcement();
	void defineNReinforcement();
//	PlayerDeck* getPDeck();

	void defineNTerritory();
	void defineNCard();
	void defineNArmy();
	void
  setNumber (int number)
  {
    mNumber = number;
  }

	// Getters
	std::vector<Card*> getCards();
	bool getEliminated();

	// Setters
	//void setListCards(int i, int j, int k);
	void setNumOfCards(int num);
	void setCards(std::vector<Card*> set);

	// Others
	void addCard(Card* aCard);
	void removeCard(Card* aCard);
	void printCards();

protected:
  std::string name;

private:
	std::string color;
	int mNumber;

	int nCard;
	int nArmy;
	int nTerritory;
	int nContinent;
	int numOfCard;
	int nReinforcement;
	int nWin;

	bool hasNewTerritory;
	bool turnState;
	bool eliminated;

	//PlayerDeck *pDeck; //New

	std::vector<Card*> cards;

};
#endif /* PLAYER_H_ */
