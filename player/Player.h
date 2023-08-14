#include "..\deck_of_cards\Deck.h"


class Player{
    
    public:

        Player(Deck& deck, int desiredNumCards) : deck(deck) {
            dealCards(desiredNumCards); // Deal initial cards
    }

        void dealCards( int numberOfCards){
            for(int i= 0; i < numberOfCards; i++ ){
                hand.push_back(deck.deal());
            }
        };

        


    private:

        Deck& deck;
        std::vector<Card> hand;
};

//to create a player now, you would write:
//Deck deck
//numCards
// Player player1(deck, numCards)