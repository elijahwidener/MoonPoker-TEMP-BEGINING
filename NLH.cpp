#include "player\Player.h"
#include "handEvaluator3.0.h"


void playGame(Player&, vector<Player>&, vector<Player>&, vector<Card>&,
            Deck&, int, int, int);
void playerActions(Player&, vector<Player>&, vector<Card>& , int);
void playerPreflopActions(Player&, vector<Player>&, vector<Card>& , int);
bool allBetsEqual(vector<Player>, int );
void gameAction(Player&, vector<Player>&, vector<Card>&, int, int, int);

main(){

    Deck deck;
    int NLHNumCards = 2;
    int zeroBet = 0;
    int button = 0;
    int tempStack = 1000;
    int bigBlind = 2;
    std::vector<Player> players;
    std::vector<Player> inHand;
    std::vector<Card> muckedCards;


    //Create the dealer, which will also be the board
    Player dealer(deck, 0, zeroBet, 0);

    //create 6 players with empty hands
    for(int i = 0; i < 6; i++) {
        players.push_back(Player(deck, 0, zeroBet, tempStack));
    }

    playGame(dealer, players, inHand, muckedCards, deck, NLHNumCards, button, bigBlind);

    return 0;

}


void playGame(Player& dealer, vector<Player>& players, vector<Player>& inHand, 
            vector<Card>& muckedCards, Deck& deck, int NLHNumCards, int button, int bigBlind){
    
    
    //Shuffle the deck with the mucked cards
    deck.shuffle(muckedCards);
    //clear the mucked cards vector, since they are now in the deck
    muckedCards.clear();

    //deal all cards
    int playersDealt = 0;
    for (int i = button; i< 6; i++){
        int seatIndex = (button + 1 + i) % 6;      // Calculate the player index considering the dealer position
        players[seatIndex].dealCards(NLHNumCards); //give the player cards
        inHand.push_back(players[seatIndex]);      //put the player in the hand
        playersDealt++;
        
        if(playersDealt  == 6){
            break; // Exit the loop when all 6 players have been dealt
        }
    }
    dealer.dealCards(5);


    //(FOR TESTING) Show cards 
    for(int i = 0; i < 6; i++) {
        players[i].showCards(0,NLHNumCards);
    }
    
    cout << "we got here" << endl;


//change to run while there is more than one player in hand
    gameAction(dealer, inHand, muckedCards, NLHNumCards, button, bigBlind);


//Change to players still in hand muck
    //Muck player and dealer cards
    dealer.muckCards(5, muckedCards);
    for(int i = 0; i < 6; i++) {
        players[i].muckCards(NLHNumCards, muckedCards);
    }

    // Move the dealer button to the next player
    button = (button + 1) % players.size();

}


void playerActions(Player& dealer, vector<Player>& inHand, vector<Card>& muckedCards, int NLHNumCards, int bigBlind){
    int currentBet = 0;
    int previousBet = 0;
    //int difference = 0;
    auto actionsOnYou = inHand.begin();

    while(actionsOnYou != inHand.end()){

        actionsOnYou->resetBetting(); //reset bet and totalBetInRound 

        actionsOnYou->setBet(actionsOnYou->action(muckedCards, currentBet, NLHNumCards, previousBet, *actionsOnYou, bigBlind));
        if(actionsOnYou->getBet() == -1){
            //Remove the player from in the hand
            actionsOnYou = inHand.erase(actionsOnYou);
            //no need to increment irrerator since When you erase an element, the iterator becomes invalidated
        }
        else{
            previousBet = currentBet;
            currentBet = actionsOnYou->getBet();
            dealer.addToPot(currentBet, *actionsOnYou);
            ++actionsOnYou;
        }
    }  
        
    while(!allBetsEqual(inHand, currentBet)){
        actionsOnYou = inHand.begin();
        while(actionsOnYou != inHand.end()){
            //check if player is not equal to bet
            if (currentBet != actionsOnYou->getBet()){
                actionsOnYou->setBet(actionsOnYou->action(muckedCards, currentBet, NLHNumCards, previousBet, *actionsOnYou, bigBlind));
                
                if(actionsOnYou->getBet() == -1){
                    //Remove the player from in the hand
                    actionsOnYou = inHand.erase(actionsOnYou);
                }
                else{
                currentBet = actionsOnYou->getBet();
                dealer.addToPot(currentBet, *actionsOnYou);
                previousBet = currentBet;
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

void preflopPlayerActions(Player& dealer, vector<Player>& inHand, vector<Card>& muckedCards, int NLHNumCards, int bigBlind){
    int currentBet = bigBlind;
    int previousBet = 0;
    //int difference = 0;

    //SB forced bet
    inHand[0].setBet(bigBlind/2);
    dealer.addToPot(currentBet/2, inHand[0]);
    //remv stack
    //BB forced bet
    inHand[1].setBet(bigBlind);
    dealer.addToPot(currentBet, inHand[1]);
    //rmv stack


    auto actionsOnYou = (inHand.begin() + 2);

    while(actionsOnYou != inHand.end()){

        actionsOnYou->resetBetting(); //reset bet and totalBetInRound 

        actionsOnYou->setBet(actionsOnYou->action(muckedCards, currentBet, NLHNumCards, previousBet, *actionsOnYou, bigBlind));
        if(actionsOnYou->getBet() == -1){
            //Remove the player from in the hand
            actionsOnYou = inHand.erase(actionsOnYou);
            //no need to increment irrerator since When you erase an element, the iterator becomes invalidated
        }
        else{
            previousBet = currentBet;
            currentBet = actionsOnYou->getBet();
            dealer.addToPot(currentBet, *actionsOnYou);
            ++actionsOnYou;
        }
    }  
        
    while(!allBetsEqual(inHand, currentBet)){
        actionsOnYou = (inHand.begin());
        while(actionsOnYou != inHand.end()){
            //check if player is not equal to bet
            if (currentBet != actionsOnYou->getBet()){
                actionsOnYou->setBet(actionsOnYou->action(muckedCards, currentBet, NLHNumCards, previousBet, *actionsOnYou, bigBlind));
                
                if(actionsOnYou->getBet() == -1){
                    //Remove the player from in the hand
                    actionsOnYou = inHand.erase(actionsOnYou);
                }
                else{
                currentBet = actionsOnYou->getBet();
                dealer.addToPot(currentBet, *actionsOnYou);
                previousBet = currentBet;
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

//Tests if all bets are Equal
bool allBetsEqual(vector<Player> inHand, int currentBet){
    for (Player player : inHand){
        if(player.getBet() != currentBet){
            return false;
        }
    }
    return true;
}

void gameAction(Player& dealer, vector<Player>& inHand, vector<Card>& muckedCards, 
                int NLHNumCards, int button, int bigBlind){

    //Preflop
    preflopPlayerActions(dealer, inHand, muckedCards, NLHNumCards, bigBlind);

    //flop
    dealer.showCards(0,3);
    cout << endl;
    playerActions(dealer, inHand, muckedCards, NLHNumCards, bigBlind);
    
    //turn
    dealer.showCards(0,4);
    cout << endl;
    playerActions(dealer, inHand, muckedCards, NLHNumCards, bigBlind);
    
    //river
    dealer.showCards(0,5);
    cout << endl;
    playerActions(dealer, inHand, muckedCards, NLHNumCards, bigBlind);

    //showdown
    long long highHand = 0;
    Player* winner = &inHand[0];
    for (int j = 0; j < inHand.size(); j++){
        long long k = evaluateHand(inHand[j].getCards(), dealer.getCards());
        if (k > highHand){
                highHand = k;
                winner = &inHand[j];
        }
    }
        

    winner->winPot(dealer);
    
    
}
