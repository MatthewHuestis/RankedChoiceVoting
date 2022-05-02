#include <fstream> 
#include <iomanip>
#include <iostream>
#include <array>
#include <vector>
#include "votingSystem.h"

using namespace std;

void votingSystem::startSystem() {
	readVotes();
	tallyVotes();
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
	
	int row{ 0 };//variable used to keep track of row within file for handeling bad ballots.

	//iterates through each line of the file.
	//store each entry into a vector
	while (file >> county >> A >> B >> C >> D >> E) {
		array<int, 6> entry = { county,A,B,C,D,E };
		if (A == 1) {
			countyVote[county][0]++;
			votes.push_back(entry);
		}
		else if (B == 1) { 
			countyVote[county][1]++; 
			votes.push_back(entry);
		}
		else if (C == 1) {
			countyVote[county][2]++;
			votes.push_back(entry);
		}
		else if (D == 1) { 
			countyVote[county][3]++;
			votes.push_back(entry);
		}
		else if (E == 1) {
			countyVote[county][4]++;
			votes.push_back(entry);
		}
		//in case of bad ballot, the array will not be stored into the vector.
		else cerr << "Bad ballot in row " <<row << '\n';

		row++;
		tally++;
		//cout << county << " " << A << " " << B << " " << C << " " << D << " " << E << "\n"; //testing code
	}
	
}

void votingSystem::tallyVotes() {


	//varaible to show the tally of votes for each candiate;
	int candiate[5] = { 0 };

	//bool value to check if at passing sequence of votes
	bool pass{ false };

	//iterator for votes
	vector<array<int, 6>>::iterator it;

	for (it = votes.begin(); it != votes.end(); it++) {
		if ((*it)[1] == 1) candiate[0]++;
		else if ((*it)[2] == 1) candiate[1]++;
		else if ((*it)[3] == 1) candiate[2]++;
		else if ((*it)[4] == 1) candiate[3]++;
		else if ((*it)[5] == 1) candiate[4]++;
	}

	//array for the percent of each vote for each candiate
	float candPerc[5] = { 0 };

	//loop to calculate the percentage of each candiate vote
	for (int k{ 0 }; k < 5; k++) {
		candPerc[k] = static_cast<float>(candiate[k]) / static_cast<float>(tally);
	}

	//displaying results from iteration.
	cout << "Results from iteration " << iteration << '\n';
	cout << "\tA:" << candPerc[0] * 100 << "%  B:" << candPerc[1] * 100 << "%  C:" << candPerc[2] * 100 << "% D:"
		<< candPerc[3] * 100 << "% E:" << candPerc[4] * 100 << " % \n";
	iteration++;

	//checks if any canidate has <=50% of the votes
	if (candPerc[0] > 0.5) {
		cout << "Winner is, Canidate A!\n";
		pass = true;
	}
	else if (candPerc[1] > 0.5) {
		cout << "Winner is, Canidate B!\n";
		pass = true;
	}
	else if (candPerc[2] > 0.5) {
		cout << "Winner is, Canidate C!\n";
		pass = true;
	}
	else if (candPerc[3] > 0.5) {
		cout << "Winner is, Canidate D!\n";
		pass = true;
	}
	else if (candPerc[4] > 0.5) {
		cout << "Winner is, Canidate E!\n";
		pass = true;
	}

	//failure state, need to drop lowest canidate and rerun
	else {
		
		int drop{ 0 };

		//finding next non dropped canidate that hasnt been dropped yet.
		for (int i{ 0 }; i < 5; i++)
			if (candPerc[i] < candPerc[drop] && candiate[i]> 0)	drop = i;
		//drop lowest candiate
		dropCand(drop+1);

		//recurse the function
		tallyVotes();

	}
	//if at passing condition within recursive function, display final results.
	if (pass == true) {

		cout << "\n----TOTAL VOTES PER COUNTY-----" << endl;
		cout << " COUNTY CODE\t A  B  C  D  E" << endl;
		// note: county FIPS codes are only odd numbers
		for (int i = 1; i < 124; i += 2) {
			cout << setw(5) << i << "\t\t";
			for (int j = 0; j < 5; j++) {
				cout << countyVote[i][j] << " ";
			}
			cout << endl;
		}
	}
}

void votingSystem::dropCand(int cand) {
	//creating an iterator for the vector of voters
	vector<array<int, 6>>::iterator it;
	//for loop that iterates through list, 
	for (it = votes.begin(); it != votes.end(); it++) {
		int dropVal{ (*it)[cand] };
		if (dropVal > 0) {
			for (int k{ 1 }; k < 6; k++) {
				if ((*it)[k] > dropVal) (*it)[k] -= 1;
			}
			(*it)[cand] = 0;
		}
	}
}


