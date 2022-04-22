#include <list>
#include <fstream> 
#include <iomanip>
#include <iostream>
#include "votingSystem.h"


using namespace std;

void votingSystem::readVotes(){
	ifstream file("vote.txt", ios::in);

	if (!file) {
		cerr << "Could not open file";
		exit(EXIT_FAILURE);
	}
	int county, A, B, C, D, E;
	while (file >> county >> A >> B >> C >> D >> E) {
		votes.push_back({ county,A,B,C,D,E });
		tally++;
	}
}
