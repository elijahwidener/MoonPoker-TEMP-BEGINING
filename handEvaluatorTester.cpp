#include <C:\Users\Elijah Widener\Desktop\MoonPoker\handEvaluator3.0.h>

void testEvaluateHand() {

    vector<Card> playerCards = {Card(Card::Ace, Card::Spade),Card(Card::Ace, Card::Heart)};

    vector<Card> dealerCards = {Card(Card::Two, Card::Spade),Card(Card::King, Card::Club), 
        Card(Card::Four, Card::Spade), Card(Card::Five, Card::Spade), Card(Card::Nine, Card::Heart)};
    
    long long expectedValue = 0;
    long long result = evaluateHand(playerCards, dealerCards);
    
    if (result == expectedValue) {
        cout << "Test passed!" << endl;
    } else {
        cout << "Test failed. Expected " << expectedValue << " but got " << result << "." << endl;
    }
}

int main() {
    testEvaluateHand();
    // Add more test functions here...
    return 0;
}



//StraightFlush Pass
//Quads Pass
//Full House Pass
//Flush Pass
//Straight Pass
    //wheel pass
//Trips Pass
//Two Pair SEGMENTATION FAULT???
//One Pair Pass
//High Card Pass