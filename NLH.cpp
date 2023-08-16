#include "player\Player.h"


void playGame(Player&, vector<Player>&, vector<Player>&, vector<Card>&,
            Deck&, int);
void playerActions(Player&, vector<Player>&, vector<Card>& , int);
bool allBetsEqual(vector<Player>, int );
void gameAction(Player&, vector<Player>&, vector<Card>&, int, int);

main(){

    Deck deck;
    int NLHNumCards = 2;
    int zeroBet = 0;
    int tempStack = 100;
    std::vector<Player> players;
    std::vector<Player> inHand;
    std::vector<Card> muckedCards;


    //Create the dealer, which will also be the board
    Player dealer(deck, 0, zeroBet, 0);

    //create 6 players with empty hands
    for(int i = 0; i < 6; i++) {
        players.push_back(Player(deck, 0, zeroBet, tempStack));
    }

    playGame(dealer, players, inHand, muckedCards, deck, NLHNumCards);

    return 0;

}


void playGame(Player& dealer, vector<Player>& players, vector<Player>& inHand, 
            vector<Card>& muckedCards, 
    
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
    int pot = 0;

    //(FOR TESTING) Show cards 
    for(int i = 0; i < 6; i++) {
        players[i].showCards(0,NLHNumCards);
    }
    
    cout << "we got here" << endl;


//change to run while there is more than one player in hand
    gameAction(dealer, inHand, muckedCards, NLHNumCards, pot);


//Change to players still in hand muck
    //Muck player and dealer cards
    dealer.muckCards(5, muckedCards);
    for(int i = 0; i < 6; i++) {
        players[i].muckCards(NLHNumCards, muckedCards);
    }
}


void playerActions(Player& dealer, vector<Player>& inHand, vector<Card>& muckedCards, int NLHNumCards){
    int currentBet = 0;
    int previousBet = 0;
    auto actionsOnYou = inHand.begin();

    while(actionsOnYou != inHand.end()){
        actionsOnYou->setBet(actionsOnYou->action(muckedCards, currentBet, NLHNumCards, previousBet, *actionsOnYou));
        if(actionsOnYou->getBet() == -1){
            //Remove the player from in the hand
            actionsOnYou = inHand.erase(actionsOnYou);
            //no need to increment irrerator since When you erase an element, the iterator becomes invalidated
        }
        else{
            previousBet = currentBet;
            currentBet = actionsOnYou->getBet();
            dealer.plusStack(currentBet);
            ++actionsOnYou;
        }
    }  
        
    while(!allBetsEqual(inHand, currentBet)){
        actionsOnYou = inHand.begin();
        while(actionsOnYou != inHand.end()){
            //check if player is not equal to bet
            if (currentBet != actionsOnYou->getBet()){
                actionsOnYou->setBet(actionsOnYou->action(muckedCards, currentBet, NLHNumCards, previousBet, *actionsOnYou));
                
                if(actionsOnYou->getBet() == -1){
                    //Remove the player from in the hand
                    actionsOnYou = inHand.erase(actionsOnYou);
                }
                else{
                    previousBet = currentBet;
                    currentBet = actionsOnYou->getBet();
                    dealer.plusStack(currentBet);
                    ++actionsOnYou;
                    
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

}


bool allBetsEqual(vector<Player> inHand, int currentBet){
    for (Player player : inHand){
        if(player.getBet() != currentBet){
            return false;
        }
    }
    return true;
}

void gameAction(Player& dealer, vector<Player>& inHand, vector<Card>& muckedCards, 
                int NLHNumCards, int pot){

    //Preflop
    playerActions(dealer, inHand, muckedCards, NLHNumCards);

    //flop
    //set previous_bet to 0
    dealer.showCards(0,3);
    playerActions(dealer, inHand, muckedCards, NLHNumCards);
    
    //turn
    dealer.showCards(3,4);
    playerActions(dealer, inHand, muckedCards, NLHNumCards);
    
    //river
    dealer.showCards(4,5);
    playerActions(dealer, inHand, muckedCards, NLHNumCards);
    
}
