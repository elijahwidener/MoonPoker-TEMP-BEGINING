#include "player\Player.h"

//in the future make a game info enum which stores num players and num cards for each game

void playGame(Player&, vector<Player>&, vector<Card>&, Deck&, int);

main(){

    Deck deck;
    int desiredNumCards = 2;
    std::vector<Player> players;
    std::vector<Card> muckedCards;


    //Create the dealer, which will also be the board
    Player dealer(deck, 5);

    //create 6 players
    for(int i = 0; i < 6; i++) {
        players.push_back(Player(deck, desiredNumCards));
    }

    for (int k = 0; k < 3; k++){
        playGame(dealer, players, muckedCards, deck, desiredNumCards);
    }

    return 0;

}


void playGame(Player& dealer, vector<Player>& players, vector<Card>& muckedCards, Deck& deck, int desiredNumCards){

    //Muck player and dealer cards
    dealer.muckCards(5, muckedCards);
    for(int i = 0; i < 6; i++) {
        players[i].muckCards(desiredNumCards, muckedCards);
    }

    //Shuffle the deck with the mucked cards
    deck.shuffle(muckedCards);
    //clear the mucked cards vector, since they are now in the deck
    muckedCards.clear();

    //deal all cards
    for (int i = 0; i< 6; i++){
        players[i].dealCards(desiredNumCards);
    }
    dealer.dealCards(5);

    //(FOR TESTING) Show cards then muck cards 
    for(int i = 0; i < 6; i++) {
        players[i].showCards(desiredNumCards);
    }
    
    //Show the board
    dealer.showCards(5);
}



