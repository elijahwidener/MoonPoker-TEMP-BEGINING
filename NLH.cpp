#include "player\Player.h"


void playGame(Player&, vector<Player>&, vector<Player>&, vector<Card>&, Deck&, int);
int playerActions(vector<Player>& , vector<Card>& , int);
bool allBetsEqual(vector<Player>, int );

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

    playGame(dealer, players, inHand, muckedCards, deck, NLHNumCards);

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
    
    cout << "we got here" << endl;

    int pot = playerActions(inHand, muckedCards, NLHNumCards);

    cout << pot;
    
    //Show the board
    dealer.showCards(5);

    //Muck player and dealer cards
    dealer.muckCards(5, muckedCards);
    for(int i = 0; i < 6; i++) {
        players[i].muckCards(NLHNumCards, muckedCards);
    }
}


int playerActions(vector<Player>& inHand, vector<Card>& muckedCards, int NLHNumCards){
    int currentBet = 0;
    int pot = 0;
    auto actionsOnYou = inHand.begin();

    while(actionsOnYou != inHand.end()){
        actionsOnYou->setBet(actionsOnYou->action(muckedCards, currentBet, NLHNumCards));
        if(actionsOnYou->getBet() == -1){
            //Remove the player from in the hand
            actionsOnYou = inHand.erase(actionsOnYou);
            //no need to increment irrerator since When you erase an element, the iterator becomes invalidated
        }
        else{
            currentBet = actionsOnYou->getBet();
            ++actionsOnYou;
            pot += currentBet;
        }
    }  
        
    while(!allBetsEqual(inHand, currentBet)){
        actionsOnYou = inHand.begin();
        while(actionsOnYou != inHand.end()){
            //check if player is not equal to bet
            if (currentBet != actionsOnYou->getBet()){
                actionsOnYou->setBet(actionsOnYou->action(muckedCards, currentBet, NLHNumCards));
                
                if(actionsOnYou->getBet() == -1){
                    //Remove the player from in the hand
                    actionsOnYou = inHand.erase(actionsOnYou);
                }
                else{
                    currentBet = actionsOnYou->getBet();
                    ++actionsOnYou;
                    pot += currentBet;
                }
            }
            else{
                ++actionsOnYou;
            }
        }
        // Reset the iterator again for the next iteration of the outer loop.
            //This is for check raises
        actionsOnYou = inHand.begin();
    }
    return pot;

}


bool allBetsEqual(vector<Player> inHand, int currentBet){
    for (Player player : inHand){
        if(player.getBet() != currentBet){
            return false;
        }
    }
    return true;
}


