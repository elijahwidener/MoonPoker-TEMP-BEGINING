#include "player\Player.h"


void playGame(Player&, vector<Player>&, vector<Player>&, vector<Card>&, Deck&, int);

main(){

    Deck deck;
    int NLHNumCards = 2;
    int zeroBet = 0;
    std::vector<Player> players;
    std::vector<Player> inHand;
    std::vector<Card> muckedCards;


    //Create the dealer, which will also be the board
    Player dealer(deck, 0, 0);

    //create 6 players with empty hands
    for(int i = 0; i < 6; i++) {
        players.push_back(Player(deck, 0, 0));
    }

    for (int k = 0; k < 3; k++){
        playGame(dealer, players, inHand, muckedCards, deck, NLHNumCards);
    }

    return 0;

}


void playGame(Player& dealer, vector<Player>& players, vector<Player>& inHand, vector<Card>& muckedCards, 
        Deck& deck, int NLHNumCards){

    

    //Shuffle the deck with the mucked cards
    deck.shuffle(muckedCards);
    //clear the mucked cards vector, since they are now in the deck
    muckedCards.clear();

    //deal all cards
    for (int i = 0; i< 6; i++){
        players[i].dealCards(NLHNumCards); //give the player cards
        inHand.push_back(players[i]);      //put the player in the hand
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


void playerActions(vector<Player>& inHand, vector<Card>& muckedCards, int bet, int NLHNumCards){
    int currentBet;
    
    auto actionsOnYou = inHand.begin();

    while(actionsOnYou != inHand.end()){
        actionsOnYou->setBet(actionsOnYou->action(muckedCards, bet, NLHNumCards));
        if(actionsOnYou->getBet() == -1){
            //Remove the player from in the hand
            inHand.erase(actionsOnYou);
        }
        else{
            currentBet = actionsOnYou->getBet();
            ++actionsOnYou;
            //Add bet to pot
        }
    }  
        
    while(!allBetsEqual(inHand, currentBet)){
        while(actionsOnYou != inHand.end()){
            actionsOnYou->setBet(actionsOnYou->action(muckedCards, bet, NLHNumCards));
            if(actionsOnYou->getBet() == -1){
                //Remove the player from in the hand
                inHand.erase(actionsOnYou);
            }
            else{
                currentBet = actionsOnYou->getBet();
                ++actionsOnYou;
                //Add bet to pot
            }
        }
    }

    //create a function that checks if all bets are equal

    //while allBetsEqual is false, ask the players in the hand who dont equal the current bet again
}


bool allBetsEqual(vector<Player> inHand, int currentBet){
    for (Player player : inHand){
        if(player.getBet() != currentBet){
            return false;
        }
    }
    return true;
}


/*void takeAction(vector<Player>& players, vector<Card>& muckedCards, int bet, int NLHNumCards){
    player.setBet(player.action(muckedCards, bet, NLHNumCards));
        if(player.getBet() == -1){
            //Remove the player from in the hand
            inHand.pop(player);
        }
        else{
            currentBet = player.getBet();
            //Add bet to pot
        }
}*/


