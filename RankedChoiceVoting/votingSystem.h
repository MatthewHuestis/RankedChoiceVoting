#pragma once
#include <string>
#include <vector>
#include <array>
using std::string;
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
	void tallyVotes(int drop...);
	//vector with vote information
	vector<array<int,6>> votes;
	//data member with total number of votes
	int tally{ 0 };

};

void startVotingSystem() {
	votingSystem alpha;
	alpha.startSystem();
};