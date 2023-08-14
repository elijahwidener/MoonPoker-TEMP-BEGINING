#include "player\Player.h"


void playGame(Player&, vector<Player>&, vector<Card>&, Deck&, int);

main(){

    Deck deck;
    int NLHNumCards = 2;
    std::vector<Player> players;
    std::vector<Card> muckedCards;


    //Create the dealer, which will also be the board
    Player dealer(deck, 0);

    //create 6 players with empty hands
    for(int i = 0; i < 6; i++) {
        players.push_back(Player(deck, 0));
    }

    for (int k = 0; k < 3; k++){
        playGame(dealer, players, muckedCards, deck, NLHNumCards);
    }

    return 0;

}


void playGame(Player& dealer, vector<Player>& players, vector<Card>& muckedCards, Deck& deck, int NLHNumCards){

    

    //Shuffle the deck with the mucked cards
    deck.shuffle(muckedCards);
    //clear the mucked cards vector, since they are now in the deck
    muckedCards.clear();

    //deal all cards
    for (int i = 0; i< 6; i++){
        players[i].dealCards(NLHNumCards);
    }
    dealer.dealCards(5);

    //(FOR TESTING) Show cards 
    for(int i = 0; i < 6; i++) {
        players[i].showCards(NLHNumCards);
    }
    
    //Show the board
    dealer.showCards(5);

    //Muck player and dealer cards
    dealer.muckCards(5, muckedCards);
    for(int i = 0; i < 6; i++) {
        players[i].muckCards(NLHNumCards, muckedCards);
    }
}



