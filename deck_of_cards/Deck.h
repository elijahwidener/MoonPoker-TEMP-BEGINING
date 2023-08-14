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

};