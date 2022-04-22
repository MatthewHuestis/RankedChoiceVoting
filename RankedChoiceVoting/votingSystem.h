#pragma once
#include <string>
#include <list>
using std::string;
using std::list;

class votingSystem {
public:
	//deconstructor
	~votingSystem();
	//function that will start the system process
	void startSystem();
private:
	//function to read vote information from file.
	void readVotes();
	//recursive function to do the ranked choice voting. drop is the candiate to be dropped.
	void tallyVotes(int drop...);
	//linked list with vote information
	list<int[6]> votes;
	//data member with total number of votes
	int tally{ 0 };

};
