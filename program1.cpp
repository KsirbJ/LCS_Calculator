/** 
 *	This program caculates the LCS of two strings using a dynamic programming
 *	bottom-up approach. 
 *
 *	@author Jake Brisk
 *	@version 1.0 3/14/17
 */

#include <string>		// for strings and such
#include <iostream>		// cin, cout
#include <fstream>		// file I/O
#include <vector>		// for lookup table
#include <chrono>		// to measure running time


using namespace std;

// used for a combined b and c lookup table
struct table_item {
	int max; // the max subsequance at this point
	char direction; // should be ^ < or > (for diagonally left)
};

int main(int argc, char const *argv[]) {
	
	// Expects argc to be 4 
	if(argc < 4){
		cout << "Program usage is: ./program1 <filex.txt> <filey.txt> <output1.txt>" << endl;
		exit(1);
	}

	ifstream xfile, yfile; // input and output files
	string xline, yline; // input strings

	xfile.open(argv[1]); // assumes argv[1] is file containing x
	yfile.open(argv[2]); // assumes argv[2] is file containing y

	// try to read from files, exit if they're empty
	if(! (getline(xfile, xline) && getline(yfile, yline))){ 
		cerr << "Couldn't read line from file" << endl;
		exit(1);
	}

	xfile.close();
	yfile.close();

	// store the length of the 2 strings
	int xlength = xline.length(), ylength = yline.length();

	// start timing the program execution
	auto start = chrono::high_resolution_clock::now();

	// initialize lookup table
	table_item t;
	t.max = 0;
	t.direction = '^'; // default direction is up
	vector< vector<table_item> > lookup_table(xlength+1, vector<table_item>(ylength+1, t));


	for(int i = 1; i < xlength+1; ++i){
		for(int j = 1; j < ylength+1; ++j){ 
			if(xline[i-1] == yline[j-1]){ 
				// found a match, get the lcs up to this point and set direction
				lookup_table[i][j].max = lookup_table[i-1][j-1].max+1;
				lookup_table[i][j].direction = '>';
			}else if(lookup_table[i-1][j].max > lookup_table[i][j-1].max){
				lookup_table[i][j].max = lookup_table[i-1][j].max;
				lookup_table[i][j].direction = '^';
			}else{
				lookup_table[i][j].max = lookup_table[i][j-1].max;
				lookup_table[i][j].direction = '<';
			}
		}
	}
	// get the actual length of the LCS
	int lcs_length = lookup_table[xlength][ylength].max;

	// end the timer
	auto end = chrono::high_resolution_clock::now();
	// calculate the duration
	auto span = chrono::duration_cast<chrono::duration<double>>(end - start);

	/**********        OUTPUT SECTION          *************/

	// open the output file and write to it
	ofstream of;
	of.open(argv[3]); // assumes argv[3] is the output file

	// what should we write?
	if (xlength < 11 && ylength < 11) {

		// print out the lookup table, row by row
		for(int i = 0; i < xlength+1; ++i){
			for (int j = 0; j < ylength+1; ++j)
				of << lookup_table[i][j].max << " " << lookup_table[i][j].direction << " ";
			of << endl;
		}

		// print the actual LCS
		int x = xlength, y = ylength;
		string lcs = "";
		while (x >= 0 && y >= 0) {
			if(lookup_table[x][y].direction == '>'){
				lcs = xline[x-1] + lcs; // match at this index
				x--, y--;

			// no match, find previous index
			}else if(lookup_table[x][y].direction == '<'){
				y--;
			}else{
				x--;
			}
		}
		of << lcs << endl;

	} else {
		// print the length of the LCS
		of << lcs_length << endl;
	}

	// output the running time
	of << span.count() << endl;

	of.close();

	return 0;
}