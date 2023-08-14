#include "..\deck_of_cards\Deck.h"
using namespace std;

class Player{
    
    public:

        //Create the player Constructor. Calls a deck and a desired number of cards. 
                //In the future will potentially need to call more, like a pot size, or stack size
                //Will also need a position to be held by each player, and be able to rotate position
        Player(Deck& deck, int desiredNumCards) : deck(deck) {
            dealCards(desiredNumCards);
        }

        //Deals a player two distinct random cards using the Deck class
        void dealCards( int numberOfCards){
            for(int i= 0; i < numberOfCards; i++ ){
                hand.push_back(deck.deal());
            }
        };

        void showCards(int numberOfCards){
            for(int i= 0; i < numberOfCards; i++ ){
                cout << hand[i] << ",";
            }
            cout << endl;
        }

        void muckCards(int numberOfCards, vector<Card> muckedCards){
            
            //add the players hand to the muck
            muckedCards.insert(muckedCards.end(), hand.begin(), hand.end());

            for(int i= 0; i < numberOfCards; i++ ){
                hand.pop_back();
            }
        };

        


    private:
        int desiredNumCards;
        Deck& deck;
        std::vector<Card> hand;
        std::vector<Card> muckedCards;
};

//to create a player now, you would write:
//Deck deck
//numCards
// Player player1(deck, numCards)