#include "..\deck_of_cards\Deck.h"


class Player{
    
    public:
        //Create the player Constructor. Calls a deck and a desired number of cards. 
                //In the future will potentially need to call more, like a pot size, or stack size
        Player(Deck& deck, int desiredNumCards) : deck(deck) {
            dealCards(desiredNumCards); // Deal initial cards
    }
        //Deals a player two distinct random cards using the Deck class
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