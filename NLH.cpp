#include "player\Player.h"


//make the deck
//shuffle the deck
//make 6 players
//make a board player
//deal cards (5 to board, 2 to players)
//in the future make a game info enum which stores num players and num cards for each game

void playGame(Player, vector<Player>, vector<Card>, Deck, int);

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

    playGame(dealer, players, muckedCards, deck, desiredNumCards);
    

    return 0;

}


void playGame(Player dealer, vector<Player> players, vector<Card> muckedCards, Deck deck, int desiredNumCards){

    //Shuffle the deck with the mucked cards
    deck.shuffle(muckedCards);
    //clear the mucked cards vector, since they are now in the deck
    muckedCards.clear();

    //deal all cards
    for (int i = 0; i< 6; i++){
        players[i].dealCards(desiredNumCards);
    }

    //(FOR TESTING) Show cards then muck cards 
    for(int i = 0; i < 6; i++) {
        players[i].showCards(desiredNumCards);
        players[i].muckCards(desiredNumCards, muckedCards);
    }
    
    //Show and much the board
    dealer.showCards(5);
    dealer.muckCards(5, muckedCards);
}



