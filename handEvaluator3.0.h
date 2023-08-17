#include "player\Player.h"
#include <map>
#include <cmath>






long long evaluateHand(const vector<Card>& playerCards, const vector<Card>& dealerCards) {
    // Combine player's cards with community cards
    vector<Card> handPlusBoard = playerCards;
    handPlusBoard.insert(handPlusBoard.end(), dealerCards.begin(), dealerCards.end());

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

    int straightStrength = isStraight(uniqueRanks);
    vector<int> topFive;

    // Straight flush
    if ((straightStrength != 0) && isFlush(handPlusBoard)) return 90000000000 + straightStrength; 

    // Four of a kind
    if (countCounts[4] == 1){
        int quadsRank = 0;
        for(const auto& [rank, count] : rankCounts) {
            if (count == 4){
                quadsRank = rank;
        uniqueRanks.erase(find(uniqueRanks.begin(), uniqueRanks.end(), quadsRank));                
                break;
            }
        }
        return 80000000000 + (quadsRank * 1000) + uniqueRanks.back(); 
    } 

    // Full house
    if (countCounts[3] == 1 && countCounts[2] >= 1 || (countCounts[3] == 2)){
        int tripsRank [2]  = {0,0};
        int pairs [2] = {0,0};
        for (const auto& [rank, count] : rankCounts) {
            if (count == 3) {
                if (rank > tripsRank[0]) {
                    tripsRank[1] = tripsRank[0];
                    tripsRank[0] = rank;
                    if(tripsRank[1] !=0){
                        return 70000000000 + (tripsRank[0]*1000) + tripsRank[1];
                    }
                }
            }
            if (count == 2) {
                if (rank > pairs[0]) {
                    pairs[1] = pairs[0];
                    pairs[0] = rank;
                }
                return 70000000000 + (tripsRank[0]*1000) + pairs[0]; 
            }
        }

    }


    //Flush
    //MAKE A HIGH CARD FUNCTION TO GET INT OF HIGH CARDS
    if  (isFlush(handPlusBoard)){
        long long kickerNumber = 0;
        kickerNumber = kickers(uniqueRanks,  5);
        return 60000000000 + kickerNumber; 
    }

    //Straight
    if (straightStrength != 0) return 50000000000 + straightStrength;

    // Three of a Kind
    if (countCounts[3] == 1){
        int tripsRank = 0;
        for (const auto& [rank, count] : rankCounts) {
            if (count == 3) {
                tripsRank = rank;
                uniqueRanks.erase(find(uniqueRanks.begin(), uniqueRanks.end(), tripsRank));
                break;
            }
        }
        long long kickerNumber = 0;
        kickerNumber = kickers(uniqueRanks,  2);
        return 40000000000 + (tripsRank * 100000)  + kickerNumber; 
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
                uniqueRanks.erase(find(uniqueRanks.begin(), uniqueRanks.end(), pairs[0]));
                uniqueRanks.erase(find(uniqueRanks.begin(), uniqueRanks.end(), pairs[1]));
            }
        }
        return 30000000000 + (pairs[0] * 100000) + (pairs[1] * 1000) + uniqueRanks.back();
}


    // One Pair
    if (countCounts[2] == 1) {
        int pairRank = 0;
        for (const auto& [rank, count] : rankCounts) {
            if (count == 2) {
                pairRank = rank;
                uniqueRanks.erase(find(uniqueRanks.begin(), uniqueRanks.end(), pairRank));
                break;
            }
        }
        long long kickerNumber = 0;
        kickerNumber = kickers(uniqueRanks,  4);
        return 20000000000 + kickerNumber; 
    }

    //High card
    return kickers(uniqueRanks, 5); 

    
    
}


int kickers(const std::vector<int>& uniqueRanks, int numberOfKickers) {

    // Sort the vector in descending order
    sort(uniqueRanks.begin(), uniqueRanks.end(), greater<int>());

    int kickerNumber = 0;

    // Take the required number of elements and construct the number
    for(int i = 0; i < numberOfKickers; i++) {
        kickerNumber = kickerNumber * 100 + uniqueRanks[i];
    }

    return kickerNumber;
}




int getRank(Card card) {
    int  rankValue = card.getRank();
    return rankValue;
}

char getSuit(Card card){
    return card.getSuit();
}


//NEED TO ADD if there is an ace, let that ace equal 1 or 13
//wheel tester
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
