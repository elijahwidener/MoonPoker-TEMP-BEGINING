#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

class Card{
    public: 
        enum Rank {Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};
        enum Suit {Club, Diamond, Heart, Spade};

    //Constructor with values set to r and s 
    Card (Rank r, Suit s) : r(r), s(s) {}

/*    friend std::ostream& operator<<(std::ostream& os, const Card& card){
        const char* ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
        //Think about changing the suit to be a something more math-y? This could make the program faster since not always ever suit is at play
        const char* suits[] = {"Club", "Diamond", "Heart", "Spade"};
    }
*/
    
    private:

        Rank r;
        Suit s;
};

class Deck{
    public:
        //itterate through all combos of suit and rank to make an array of cards
        Deck() { 
            for (int s = Card::Club; s <= Card::Spade; ++s) {
                for (int r = Card::Two; r <= Card::Ace; ++r) {
                    cards.push_back(Card((Card::Rank)r, (Card::Suit)s));
                }
            }
        }

        void shuffle() {
            std::random_device rd; // Obtain a random number from hardware
            std::mt19937 g(rd()); // Seed the generator
            std::shuffle(cards.begin(), cards.end(), g); // Shuffle the cards using the generator
        }


        Card deal(){
            Card topCard = cards.back();
            cards.pop_back();
            return topCard;
        }

    private:
        std::vector<Card> cards;

}