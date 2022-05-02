#pragma once
#include <vector>
#include <array>
using std::vector;
using std::array;

class votingSystem {
public:
	//function that will start the system process
	void startSystem();
private:
	//function to read vote information from file.
	void readVotes();
	//recursive function to do the ranked choice voting. drop is the candiate to be dropped.
	void tallyVotes();
	//function to change the vote from primary lossing canidate to their next perfered canidate
	void dropCand(int);
	//vector with vote information
	vector<array<int, 6>> votes;
	//array for total votes per county for each canidate 
	int countyVote[124][5]={0};

	//data member with total number of votes
	int tally{ 0 };
	int iteration{ 1 };

};

//currently breaks program
//void startVotingSystem() {
//	votingSystem alpha;
//	alpha.startSystem();
//}