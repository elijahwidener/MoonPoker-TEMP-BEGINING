#include "player\Player.h"
#include <map>




// Function to check if a given sequence of cards is a straight
int isStraight(const vector<int>& ranks);

// Function to evaluate a poker hand
//Change to take in player and dealer
    //player and dealer know their hand
    //access it from there to create and PlusBoard vector
int evaluateHand(const vector<Card>& playerCards, const vector<Card>& communityCards) {
    // Combine player's cards with community cards
    vector<Card> handPlusBoard = playerCards;
    handPlusBoard.insert(handPlusBoard.end(), communityCards.begin(), communityCards.end());

    // Count occurrences of each rank
    map<int, int> rankCounts;
    for (const Card& card : handPlusBoard) {
        rankCounts[getRank(card)]++;
    }
    //The key will be integer rank values (2-14) for 2-A
    //The value will be the amount of times it appears



    // Count occurrences of each count (to identify pairs, trips, etc.)
    map<int, int> countCounts;
    for (const auto& [rank, count] : rankCounts) {
        countCounts[count]++;
    }

    // Prepare a sorted list of unique ranks for checking straights
    vector<int> uniqueRanks;
    for (const auto& [rank, count] : rankCounts) {
        uniqueRanks.push_back(rank);
    }
    sort(uniqueRanks.begin(), uniqueRanks.end());

//---------------------------------------------------------------------------------------------------------
//Identifying hand type


    // Straight flush
    if ((isStraight(uniqueRanks) != 0) && isFlush(handPlusBoard)) return 90000 + isStraight(uniqueRanks); 

    // Four of a kind
    if (countCounts[4] == 1){
        int quadsRank = 0;
        for(const auto& [rank, count] : rankCounts) {
            if (count == 4){
                quadsRank = rank;
                break;
            }
        }
        return 80000 + quadsRank; 
    } 

    // Full house
    if (countCounts[3] == 1 && countCounts[2] >= 1){
        int tripsRank = 0;
        int pairs [2] = {0,0};
        for (const auto& [rank, count] : rankCounts) {
            if (count == 3) {
                tripsRank = rank;
            }
            if (count == 2) {
                if (rank > pairs[0]) {
                pairs[1] = pairs[0];
                pairs[0] = rank;
                }
            }
        }
        return 70000 + (tripsRank*1000) + pairs[0]; 
    }

    //Flush
    if  (isFlush(handPlusBoard)) return 60000; 

    //Full House works 6(TR)(HP) 
        //TR = Trips Rank
        //HP = Highest Pair
            //e.g kings full of twos would be 61302

    //Straight
    if (isStraight(uniqueRanks) != 0) return 50000 + isStraight(uniqueRanks);

    // Three of a Kind
    if (countCounts[3] == 1){
        int tripsRank = 0;
        for (const auto& [rank, count] : rankCounts) {
            if (count == 3) {
                tripsRank = rank;
                break;
            }
        }
        return 40000 + tripsRank; 
    }

    //Two Pair
    if (countCounts[2] >= 2) {
        int pairs[3] = {0, 0, 0};

        for (const auto& [rank, count] : rankCounts) {
            if (count == 2) {
                if (rank > pairs[0]) {
                    pairs[2] = pairs[1];
                    pairs[1] = pairs[0];
                    pairs[0] = rank;
                } else if (rank > pairs[1]) {
                    pairs[2] = pairs[1];
                    pairs[1] = rank;
                } else if (rank > pairs[2]) {
                    pairs[2] = rank;
                }
            }
        }
        return 30000 + (pairs[0] * 1000) + pairs[1];
}

    //Two pair works 3(HP)(LP) 
        //HP = higher pair
        //LP = lower pair
            //e.g kings and twos would be 31302

    // One Pair
    if (countCounts[2] == 1) {
        int pairRank = 0;
        for (const auto& [rank, count] : rankCounts) {
            if (count == 2) {
                pairRank = rank;
                break;
            }
        }
        return 20000 + pairRank; 
    }

    //High card
    return uniqueRanks.back(); 

    
    
}



//Get kicker
//sort 7 cards highest to lowest. 
//ensure the pair, two pair, trips, quads, is always in.
//return first then second, and so on. comparing each time. 
//the first time one kicker is higher than another, that should be enough to determine winning hand.




int getRank(Card card) {
    int  rankValue = card.getRank();
    return rankValue;
}

char getSuit(Card card){
    return card.getSuit();
}

int isStraight(const vector<int>& uniqueRanks) {
    int consecutiveCount = 1;
    for (int i = 1; i < uniqueRanks.size(); i++) {
        if (uniqueRanks[i] == uniqueRanks[i-1] + 1) {
            consecutiveCount++;
            if (consecutiveCount == 5) {

                return uniqueRanks[i];
            }
            
        } else {
            consecutiveCount = 1;
        }
    }
    return 0;
}


bool isFlush(const vector<Card>& handPlusBoard) {
    map<Card::Suit, int> suitCounts;
    for (const Card& card : handPlusBoard) {
        suitCounts[card.getSuit()]++;;
    }    
    for (const auto& [suit, count] : suitCounts) {
        if (count >= 5) return true; 
    }
    return false;

}


//IDEA:
//use this function to create a large map of every possibly hand? Would this work or be useful?
    //if two players are equal, then add getKicker
    //if is OK for getKicker to return the pair'd card, logic of how I calculate pair ensures this
    //GetKicker WILL NOT work with full house. If its a full house and two players are equal, its a chop
    //if getKicker happens 5 times, its a chop