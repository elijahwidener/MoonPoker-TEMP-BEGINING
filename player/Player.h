#include "..\deck_of_cards\Deck.h"
using namespace std;

class Player{
    
    public:

        //Create the player Constructor. Calls a deck and a desired number of cards. 
                //In the future will potentially need to call more, like a pot size, or stack size
                //Will also need a position to be held by each player, and be able to rotate position
        Player(Deck& deck, int numberOfCards, int bet) : deck(&deck), numberOfCards(numberOfCards), bet(bet) {
            dealCards(numberOfCards);
        }



        //Deals a player two distinct random cards using the Deck class
        void dealCards( int numberOfCards){
            for(int i= 0; i < numberOfCards; i++ ){
                hand.push_back(deck->deal());
            }
        };

        //mainly for testing, shows the cards
        void showCards(int index, int numberOfCards){
            for(int i= index; i < numberOfCards; i++ ){
                cout << hand[i] << ",";
            }
            cout << endl;
        }
        //puts cards into the muck pile, and removes them from the hand. 
        void muckCards(int numberOfCards, vector<Card>& muckedCards){
            
            //Add the mucked card to the mucked card vector, then remove it form the hand
            for(int i= 0; i < numberOfCards; i++ ){
                muckedCards.push_back(hand.back());
                hand.pop_back();
            }
        };

        

        int action(vector<Card>& muckedCards, int bet, int numberOfCards){
            
            int raiseAmount = 0;
            char playerAction;

            if (bet == 0){
                cout << "'x' to check " << endl;
            }
            if (bet != 0){
                cout << "'c' to call " << endl;
            }
            cout << "'r' to raise " << endl;
            cout << "'f' to fold " << endl;
            cin >> playerAction;
            cout << "------------------"<< endl;


        switch(playerAction) {
            case 'x': 
                return 0;
                break;

            case 'c': 
                return bet;
                break;

            case 'r':
                do {
                    cout << "Enter raise amount (must be at least double the bet): ";
                    cin >> raiseAmount;
                    if (raiseAmount < 2 * bet) {
                        cout << "Raise must be double the bet or more. Please try again." << endl;
                    }
                } while (raiseAmount < 2 * bet);
                return raiseAmount;
                break;

            case 'f':
                muckCards(numberOfCards, muckedCards);
                return -1;

            default:
                cout << "Invalid input! Please enter a valid action." << endl;
                return action(muckedCards, bet, numberOfCards); // Recursive call
                break;
        }
    }

    //Set bet
    void setBet(int newBet) {
        bet = newBet;
    }
    //Get Bet
    int getBet(){
        return bet;
    }
        


    private:
        int bet;
        int numberOfCards;
        Deck* deck;
        std::vector<Card> hand;
        std::vector<Card> muckedCards;
};

//to create a player now, you would write:
//Deck deck
//numCards
// Player player1(deck, numCards, 0)