/*
Pseudocode:

This program first asks the user for a location name from where to read the file and a location name where to save the output file.
Then, it reads the contents into an array ignoring the single character words.
Sorts the contents of the array in alphabetically ascending order and
then start a loop to allow the user to search for one or more words in the array
If the word is found, the program gives the output which array location the word was found in, if not found then it prints an appropriate message.
*/
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>

using namespace std;
/*swaps the value of i and j.*/
void swap(string * arr, int i, int j) {
	string word = arr[i];
	arr[i] = arr[j];
	arr[j] = word;
}
/*sorts the words according to the size when the program is executed.*/
void sortWords(string * arr, int size) {
	int ind;
	for (int i = 0; i < size - 1; ++i) {
		ind = i;
		for (int j = i; j < size; ++j) {
			if (arr[j] < arr[ind]) {
				ind = j;
			}
		}
		swap(arr, i, ind);
	}
}
/*prints the output in the output file after the program is completed.*/
void printArr(ostream & out, string * arr, int size) {
	out << "Sorted Array: " << endl;
	for (int i = 0; i < size; ++i) {
		out << arr[i] << endl;
	}
	out << endl;
}
/*read the words from the file where the words are stored and needs to be searched for.*/
void readWords(string fileName, string * words, int & count) {
	ifstream in(fileName.c_str());
	count = 0;
	string word;
	while (in >> word) {
		if (word.length() > 1) {
			words[count++] = word;
		}
	} in.close();
}
/*searches a sorted array by repeatedly dividing the search interval in half.*/
int binarySearch(string * words, string word, int min, int max) {
	if (min > max) return -1;
	int mid = (min + max) / 2;
	if (words[mid] == word) {
		return mid;
	}
	else if (words[mid] > word) {
		return binarySearch(words, word, min, mid - 1);
	}
	else {
		return binarySearch(words, word, mid + 1, max);
	}
}
/*carries out the first part of the program.*/
int main() {
	string inFileName, outFileName, words[1024], word;
	int count, index;
	cout << "Enter the input file name: ";
	cin >> inFileName;
	cout << "Enter the output file name: ";
	cin >> outFileName;
	ofstream out(outFileName.c_str());
	readWords(inFileName, words, count);/* first read words from the file.*/
	sortWords(words, count);/*then sort the words according to their size.*/
	printArr(out, words, count);/*finally prints the output.*/
	while (true) { /*this loop works until the user enters '-1' when the input is prompted in the screen.*/
		cout << endl << "Enter a word to search(-1 to Exit): ";
		out << endl << "Enter a word to search(-1 to Exit): ";
		cin >> word;
		out << word << endl;
		if (word == "-1") break;/*after the user enters '-1' on the screen the program breaks and stops going any further.*/
		index = binarySearch(words, word, 0, count - 1);
		if (index == -1) {/*if the word does not match what is stored in the input file while entering it will show the following output.*/
			cout << "The word '" << word << "' cannot be found in the word array." << endl;
			out << "The word '" << word << "' cannot be found in the word array." << endl;
		}
		else {
			cout << "The word '" << word << "' is found at index " << index << "." << endl;
			out << "The word '" << word << "' is found at index " << index << "." << endl;
		}
	}
	out.close();
	return 0;
}
