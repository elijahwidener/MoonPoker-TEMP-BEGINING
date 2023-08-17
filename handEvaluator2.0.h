#include "player\Player.h"
#include <map>



class PokerHandEvaluator {


public:
    PokerHandEvaluator() {
    }

    int evaluateHand(const vector<Card>& playerCards, const vector<Card>& dealerCards) {
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

    int straight = isStraight(uniqueRanks);
    // Straight flush
    if ((straight != 0) && isFlush(handPlusBoard)) return 90000 + straight; 

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
    //Full House works 6(TR)(HP) 
        //TR = Trips Rank
        //HP = Highest Pair
            //e.g kings full of twos would be 61302


    //Flush
    if  (isFlush(handPlusBoard)) return 60000; 

    //Straight
    if (straight != 0) return 50000 + straight;

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


    vector<int> getTopFive(const vector<Card>& playerCards, const vector<Card>& dealerCards) {
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

    // Prepare a sorted list of unique ranks 
    vector<int> uniqueRanks;
    for (const auto& [rank, count] : rankCounts) {
        uniqueRanks.push_back(rank);
    }
    sort(uniqueRanks.begin(), uniqueRanks.end());


    vector<int> topFive;
    int currentSize = 0;
    
    if (countCounts[2] == 1){
        for (const auto& [rank, count] : rankCounts) {
            if (count == 2) {
                topFive.push_back(rank);
                topFive.push_back(rank);                
                currentSize = 2;
                uniqueRanks.erase(find(uniqueRanks.begin(), uniqueRanks.end(), rank));
                break;
            }
        }
    }
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
        topFive.push_back(pairs[0]);
        topFive.push_back(pairs[0]);
        topFive.push_back(pairs[1]);
        topFive.push_back(pairs[1]);
        uniqueRanks.erase(find(uniqueRanks.begin(), uniqueRanks.end(), pairs[0]));
        uniqueRanks.erase(find(uniqueRanks.begin(), uniqueRanks.end(), pairs[1]));
        currentSize = 4;

    }
    if (countCounts[3] == 1){
        int tripsRank = 0;
        for (const auto& [rank, count] : rankCounts) {
            if (count == 3) {
                tripsRank = rank;
                break;
            }
        }
        topFive.push_back(tripsRank);
        topFive.push_back(tripsRank);
        topFive.push_back(tripsRank);

        uniqueRanks.erase(find(uniqueRanks.begin(), uniqueRanks.end(), tripsRank));
        currentSize = 3;
    }

    for (currentSize; currentSize < 5; currentSize++){
        topFive.push_back(uniqueRanks.back());
    }

    return topFive;    
    //pairs and trips will be at the front, kickers at the back
    //Highest kicker will be at the back and descend from there
}
    
    
    
    
    private:
    std::map<int, int> rankCounts; 
    std::map<int, int> countCounts; 

    // Private helper functions
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
    
    
    int getRank(Card card) {
        int  rankValue = card.getRank();
        return rankValue;
    }

    char getSuit(Card card){
        return card.getSuit();
    }
};
