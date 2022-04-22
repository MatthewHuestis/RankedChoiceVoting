#include <list>
#include <fstream> 
#include <iomanip>
#include <iostream>
#include <array>
#include <vector>
#include "votingSystem.h"


using namespace std;

void votingSystem::startSystem() {
	readVotes();
}

void votingSystem::readVotes(){
	//file that contains voting data 
	ifstream file("vote.txt", ios::in);
	//error condition for file reading 
	if (!file) {
		cerr << "Could not open file";
		exit(EXIT_FAILURE);
	}

	//interger values for iterating through list
	int county, A, B, C, D, E;
	//iterates through each line of the file.
	//store each entry into a vector
	while (file >> county >> A >> B >> C >> D >> E) {
		array<int, 6> entry = { county,A,B,C,D,E };
		votes.push_back(entry);
		tally++;
		//cout << county << " " << A << " " << B << " " << C << " " << D << " " << E << "\n";//testing code
	}
}

void votingSystem::tallyVotes(int drop...) {
	//2d array to show total tally of votes
	int county[124][6]={0};
	//varaible to show the tally of votes for each candiate;
	int candiate[6]={0};
	//iterator for votes
	vector<array<int, 6>>::iterator it;

	//talleys the ammount of votes for each canidate
	for (it = votes.begin(); it !=votes.end(); it++) {
		if ((*it)[1] == 1) candiate[1]++, county[(*it)[0]][1]++;
		else if ((*it)[2] == 1) candiate[2]++, county[(*it)[0]][2]++;
		else if ((*it)[3] == 1) candiate[3]++, county[(*it)[0]][3]++;
		else if ((*it)[4] == 1) candiate[4]++, county[(*it)[0]][4]++;
		else if ((*it)[5] == 1) candiate[5]++, county[(*it)[0]][5]++;
	}
	//array for the percent of each vote for each candiate
	short candPerc[6];
	//loop to calculate the percentage of each candiate vote
	for (int k{1}; k < 6; k++) {
		candPerc = static_cast<short>(candiate[k]) / tally;
	}
}
