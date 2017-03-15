/** 
 *	This program caculates the LCS of two strings using a top-down 
 *	dynamic programming approach
 *
 *	@author Jake Brisk
 *	@version 1.0 3/14/17
 */

#include <string>		// for strings and such
#include <iostream>		// cin, cout
#include <fstream>		// file I/O
#include <vector>		// for lookup table
#include <chrono>		// to measure running time
#include <algorithm>	// for max


using namespace std;

int lcs_length(string x, string y, vector<vector<int>> lt);

int main(int argc, char const *argv[]) {
	
	// Expects argc to be 4 
	if(argc < 4){
		cout << "Program usage is: ./program3 <filex.txt> <filey.txt> <output1.txt>" << endl;
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

	// start timing the program execution
	auto start = chrono::high_resolution_clock::now();

	// store the length of the 2 strings
	int xlength = xline.length(), ylength = yline.length();

	// set up lookup table
	vector< vector<int> > lookup_table(xlength+1, vector<int>(ylength+1, -1));
	for(int i = 0; i < xlength; ++i)
		lookup_table[i][0] = 0;
	for(int j = 0; j < ylength; ++j)
		lookup_table[0][j] = 0;

	// get the lcs length
	int length = lcs_length(xline, yline, lookup_table);

	// end the timer
	auto end = chrono::high_resolution_clock::now();
	// calculate the duration
	auto span = chrono::duration_cast<chrono::duration<double>>(end - start);

	/**********        OUTPUT SECTION          *************/

	// open the output file and write to it
	ofstream ofile;
	ofile.open(argv[3]); // assumes argv[3] is the output file

	// out put lcs length
	ofile << length << endl;
	// output the running time
	ofile << span.count() << endl;
	ofile.close();

	return 0;
}

/**
 *	This function recursively calculates the length of the LCS
 *
 *	@param x - the first string
 *	@param y - the second string
 *	@return {int} the LCS length
 */
int lcs_length(string x, string y, vector<vector<int>> lt){

	// base case x or y is ""
	if(x.length() < 1 || y.length() < 1)
		return 0;


	// strone lengths of both strings
	int xlength = x.length(), ylength = y.length();

	// check if this value is already in the table
	if(lt[xlength][ylength] != -1)
		return lt[xlength][ylength];

	if(x[xlength-1] == y[ylength-1])
		// last character of x = last character of y. Return 1 + result for 
		// x[0...len-1] and y[0..len-1]
		return lt[xlength][ylength] = 1 + lcs_length(x.substr(0, xlength-1), y.substr(0, ylength-1), lt);
	else 
		// last characters are not the same.
		// return max of x[0...len-1], y[0...len] and x[0...len], y[0...len-1]
		return lt[xlength][ylength] = max(lcs_length(x.substr(0, xlength-1), y.substr(0, y.length()), lt), 
			lcs_length(x.substr(0, x.length()), y.substr(0, y.length()-1), lt));

	return lt[lt.size()-1][lt[0].size()-1];
}