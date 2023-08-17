#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

//Card class will be used to create a Deck class, 
        //Might need to use Card class in the future?
class Card{
    public: 
        enum Rank {Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};
        enum Suit {Club, Diamond, Heart, Spade};

    //Cout operator
    friend std::ostream& operator<<(std::ostream& os, const Card& card) {
        const char* ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
        const char* suits[] = { "c", "d", "h", "s" };
        os << ranks[card.r - 2] << suits[card.s];
        return os; 
    }
    
    //Constructor with values set to r and s 
    Card (Rank r, Suit s) : r(r), s(s) {}

    int getRank(){
        switch(r){
            case Ace: return 14;
            case King: return 13;
            case Queen: return 12;
            case Jack: return 11;
            case Ten: return 10;
            case Nine: return 9;
            case Eight: return 8;
            case Seven: return 7;
            case Six: return 6;
            case Five: return 5;
            case Four: return 4;
            case Three: return 3;
            case Two: return 2;
            default: return 0;
        }
    }
    
    Suit getSuit() const{
        return s;
    }
    private:

        Rank r;
        Suit s;
};


class Deck{
    public:
        //Constructor itterates through all combos of suit and rank to make an array of cards
        Deck() { 
            for (int s = Card::Club; s <= Card::Spade; ++s) {
                for (int r = Card::Two; r <= Card::Ace; ++r) {
                    decksCards.push_back(Card((Card::Rank)r, (Card::Suit)s));
                }
            }
        }

        void shuffle(std::vector<Card> muckedCards) {
            decksCards.insert(decksCards.end(), muckedCards.begin(), muckedCards.end());
            std::random_device rd; // Obtain a random number from hardware
            std::mt19937 g(rd()); // Seed the generator
            std::shuffle(decksCards.begin(), decksCards.end(), g); // Shuffle the cards using the generator
        }

        
        Card deal(){
            Card topCard = decksCards.back();//deal card, 
            decksCards.pop_back(); //remove card from deck once delt
            return topCard;
        }

    private:
        std::vector<Card> muckedCards;
        std::vector<Card> decksCards;

};