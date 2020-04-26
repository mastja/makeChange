/*  Project Name : Make Change
    Date: 4/26/2020
    Programmer: Jacob Mast
    Description: The program to runs the make change problem given in 
                CS 325 HW4 Problem 3.b and 4.  The program has a makeChange function
                which runs the combinatorial optimization algorithm which
                determines a min coins used to make change for a given n value.
                The user input sets the given value of n, as well as the coin
                denominations list using the property denominations[i]=c^i, where i 
                ranges from 0 to k.  The user input gives the value of c and the value
                of k.  
                All input from user is received through an input file labeled "data.txt".
                All output is written to an output file labeled "change.txt".
*/


#include<iostream>
#include<fstream>
using namespace std;

// function drives the program, runs greedy method change making algorithm
int makeChange(int * denom, int c, int n, int k);

// function solves integer exponentiation using recursive divide and conquer
int int_pow(int base, int exponent);


int main(){

    // declare variables
    // c, n, and k variables correspond to the same values in the prompt
    int c, n, k, x, i= 0;
    // dynamically allocate new array
    int * denom = NULL;
    // input file
    ifstream inFile;
    //output file
    ofstream outFile;

    // open input file and verify the file was opened
    inFile.open("data.txt");
    if (!inFile.is_open()){
        cout << "Cannot Open file 'data.txt'.  Check to make sure it is in this directory" << endl;
        return 1;
    }

    // open the output file
    outFile.open("change.txt");

    // Read c value, test cases from input file
    while (!inFile.eof( )){
        inFile >> c;
        inFile >> k;
        inFile >> n;

        // Call function using input from the current line from the data.txt file
        makeChange(denom, c, n, k);

        // clear/delete denom[] array
        delete [] denom;
        denom = NULL; 
    }

    // close the opened file
    inFile.close();

    return 0;

}

/* The makeChange function finds the minimum change for the n value passed to is 
using coin denomination values from the array passed to it.
The function takes a pointer to an array, as well as a n value of money
to be made into change, and k value, which is the length of the denom array - 1.  This
function opens the output file "change.txt" and adds output to end of that file.

source citation: https://www.geeksforgeeks.org/greedy-algorithm-to-find-minimum-number-of-coins/
*/

int makeChange(int * denom, int c, int n, int k){

    // set denom array size
    denom = new int [k + 2];
    
    for (int i = 0; i <= k; i++){
        denom[i] = int_pow(c, i);
    }
    
    //output file
    ofstream outFile;

    // open the output file, usse flag to open and write at end of the file
    outFile.open("change.txt", ios::app);

    // Print first line of output
    outFile<<"Data Input: c = " << c << ", k = " << k << ", n = " << n;
    // Print update message to screen
    cout << "Data Input: c = " << c << ", k = " << k << ", n = " << n;
    
    // traverse through coin denominations
    // begin at i=k which is largest coin denom and traverse
    // to i = 0 which is lowest denom value
    for (int i = k; i >= 0; i--) { 

        // counter for frequency of each coin
        int j = 0;

        // while n is greater than current coin denomination value 
        while (n >= denom[i]) { 
            n -= denom[i];
            // count freq of current coin in solution
            j++;
        }
        
        if (j > 0){
            outFile <<"\nDenomination: " << denom[i] << " Quantity: " << j;
            cout <<"\nDenomination: " << denom[i] << " Quantity: " << j;
        }
        if (j == 0){
            outFile <<"\nDenomination: " << denom[i] << " Quantity: none";
            cout <<"\nDenomination: " << denom[i] << " Quantity: none";
        }
    }

    // go to next line in outFile then close
    outFile << "/n" << endl;
    cout << "/n" << endl;
    outFile.close();

}

/* The function below completes integer exponentiation using the recursive
divide and conquer method

sources citation: https://www.techiedelight.com/power-function-implementation-recursive-iterative/
&
comment by roottraveller at the following link: 
https://stackoverflow.com/questions/101439/the-most-efficient-way-to-implement-an-integer-based-power-function-powint-int
*/

int int_pow(int base, int exponent){

    // base case
    if (exponent == 0)
        return 1;

    // recursive step
    int temp = int_pow(base, exponent/2);
    
    // if exponent is even
    if (exponent % 2 == 0)
        return temp * temp;

    // else exponent is odd
    else
        return base * temp * temp;

}