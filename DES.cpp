#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;


int ROTATION_SHIFTS[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};



const char HEX_DIGITS[] = "0123456789ABCDEF";


//This is the Substitution box fot the feistel function(gotten from geeksforgeeks)
const int S[8][4][16] = {
    // S1
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},

    // S2
    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},

    // S3
    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},

    // S4
    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},

    // S5
    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},

    // S6
    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},

    // S7
    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},

    // S8
    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}
};

const int PERMUTATION_FUNCTION[100] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25
};


int INITIAL_PERMUTATION[100] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

const int FINAL_PERMUTATION[100] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};



// Expansion Permutation (E)
const int EXPANSION_PERMUTATION[100] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

const int PERMUTED_CHOICE_1[100] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

const int PERMUTED_CHOICE_2[100] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};


// This is to check whether the string is a hexadecimal or not.
bool isHexadecimal(const string &str) {
    for (char c : str) {
        if (!isxdigit(c)){
            return false;
        } 
    }
    return true;
}

// This converts a hexadecimal value to its binary equivalent
string hexadecimalToBinary(const string &hexadecimalString) {
    string binaryString = "";
    for (char hexChar : hexadecimalString) {
        int decimalValue = stoi(string(1, hexChar), nullptr, 16);
        binaryString += bitset<4>(decimalValue).to_string();
    }
    return binaryString;
}

    // Rotatation of a specific binary string to the left by a specified number of positions
string leftRotate(const string &binaryString, int shiftAmount) {
        return binaryString.substr(shiftAmount) + binaryString.substr(0, shiftAmount);
}




// Do a permutation based on the given table
string applyPermutation(const string &inputString, const int *permutationTable, int tableLength) {
    string permutedString(tableLength, '0');
    for (int i = 0; i < tableLength; i++) {
        permutedString[i] = inputString[permutationTable[i] - 1];
    }
        return permutedString;
}



// this is to do XOR operation for two binary strings
string binaryXOR(const string &binaryString1, const string &binaryString2) {
    string xorResult = "";
    for (size_t i = 0; i < binaryString1.size(); i++) {
        if (binaryString1[i] == binaryString2[i]) {
            xorResult += '0';
        } else {
            xorResult += '1';
        }
        
    }
    return xorResult;
}



string feistelFunction(const string &rightHalf, const string &subkey) {
    //  use the expansion table to increase the 32-bit right half to 48 bits
    string expandedRight = applyPermutation(rightHalf, EXPANSION_PERMUTATION, 48);

    // Use the XOR with the subkey
    string xoredResult = binaryXOR(expandedRight, subkey);

    // Using the S box
    string sBoxOutput = "";
    for (int i = 0; i < 8; i++) {
        string sixBitBlock = xoredResult.substr(i * 6, 6);
        int rowIndex = stoi(sixBitBlock.substr(0, 1) + sixBitBlock.substr(5, 1), nullptr, 2);
        int columnIndex = stoi(sixBitBlock.substr(1, 4), nullptr, 2);
        sBoxOutput += bitset<4>(S[i][rowIndex][columnIndex]).to_string();
    }

    // use poermutation on the S box output using
    return applyPermutation(sBoxOutput, PERMUTATION_FUNCTION, 32);
}

vector<string> generateSubkeys(const string &key) {
    // this does permutation on the key
    string permutedKey = applyPermutation(key, PERMUTED_CHOICE_1, 56);


    string leftHalf = permutedKey.substr(0, 28);
    string rightHalf = permutedKey.substr(28, 28);

    vector<string> subkeys;
    for (int i = 0; i < 16; i++) {
        leftHalf = leftRotate(leftHalf, ROTATION_SHIFTS[i]);
        rightHalf = leftRotate(rightHalf, ROTATION_SHIFTS[i]);

        string combinedKey = leftHalf + rightHalf;
        string subkey = applyPermutation(combinedKey, PERMUTED_CHOICE_2, 48);
        subkeys.push_back(subkey);
    }

    return subkeys;
}


string desEncryption(const string &key, const string &plaintext) {
    // begin to convert the plaintext and key from hexadecimal to binary
    string binaryPlaintext = hexadecimalToBinary(plaintext);
    string binaryKey = hexadecimalToBinary(key);

    // this starts the initial permutation
    string permutedText = applyPermutation(binaryPlaintext, INITIAL_PERMUTATION, 64);

    // these represent the left and right halves
    string leftHalf = permutedText.substr(0, 32);
    string rightHalf = permutedText.substr(32, 32);

    // this creates keys
    vector<string> subkeys = generateSubkeys(binaryKey);

    // this will run the Feistel structure 16 times
    for (int i = 0; i < 16; i++) {
        string newRightHalf = binaryXOR(leftHalf, feistelFunction(rightHalf, subkeys[i]));
        leftHalf = rightHalf;
        rightHalf = newRightHalf;
    }

    // Switch and put in the final permutation
    string combinedHalves = rightHalf + leftHalf;
    string finalPermutationResult = applyPermutation(combinedHalves, FINAL_PERMUTATION, 64);

    // convert binary result to hexadecimal
    string hexCiphertext;
    for (size_t i = 0; i < finalPermutationResult.size(); i += 4) {
        hexCiphertext += HEX_DIGITS[stoi(finalPermutationResult.substr(i, 4), nullptr, 2)];
    }

    return hexCiphertext;
}

// DES Decryption (same as encryption but with reversed subkey order)
string desDecryption(const string &key, const string &ciphertext) {
    // This converts  the ciphertext and key from hexadecimal to binary
    string binaryCiphertext = hexadecimalToBinary(ciphertext);
    string binaryKey = hexadecimalToBinary(key);

    // This is the initial Permutation
    string permutedText = applyPermutation(binaryCiphertext, INITIAL_PERMUTATION, 64);

    // these represent the left and right halves
    string leftHalf = permutedText.substr(0, 32);
    string rightHalf = permutedText.substr(32, 32);

    // this is the creating 16 subkeys and then reverse them for the decryption process
    vector<string> subkeys = generateSubkeys(binaryKey);
    reverse(subkeys.begin(), subkeys.end());

    // this will run the Feistel structure 16 times
    for (int i = 0; i < 16; i++) {
        string newRightHalf = binaryXOR(leftHalf, feistelFunction(rightHalf, subkeys[i]));
        leftHalf = rightHalf;
        rightHalf = newRightHalf;
    }

    // Switch and put in the final permutation
    string combinedHalves = rightHalf + leftHalf;
    string finalPermutationResult = applyPermutation(combinedHalves, FINAL_PERMUTATION, 64);

    // convert binary result to hexadecimal
    string hexPlaintext;
    for (size_t i = 0; i < finalPermutationResult.size(); i += 4) {
        hexPlaintext += HEX_DIGITS[stoi(finalPermutationResult.substr(i, 4), nullptr, 2)];
    }

    return hexPlaintext;
}


int main() {
    
    string key;
    string input;
    int choice;
    
    cout << "*******************3730 PROGRAMMING ASSIGNMENT*****************" << endl;
    cout << "Choose which operation you want to do: \n1 for Encrypt\n2 for Decrypt\nEnter choice: ";
    cin >> choice;

    if (choice != 1 && choice != 2) {
        cout << "Wrong choice. Please follow instructions. Enter 1 for Encryption or 2 for Decryption, not "<< choice << endl;
        return 1;
    }


    cout << "Enter the 16-character key in hexadecimal: ";
    cin >> key;

    if ( key.length() != 16 ||  !isHexadecimal(key)) {
        cout << "The Key must be exactly 16 hexadecimal characters (0-9, A-F)." << " What is this: " << key << " bruh." << endl;
        return 1;
    }

    cout << "Enter the  text in hexadecimal and it must be a multiple of 16 characters please!!: ";
    cin >> input;

    if (!isHexadecimal(input) || input.length() % 16 != 0) {
        cout << "Na this is crazy. the text must be a valid hexadecimal and a multiple of 16 characters." << "What are you doing!" << endl;
        return 1;
    }

    string output;
    if (choice == 1) {
        output = desEncryption(key, input);
        cout << "Encrypted output in Hexadecimal: " << output << endl;
    } else if (choice == 2) {
        output = desDecryption(key, input);
        cout << "Decrypted output Hexadecimal: " << output << endl;
    } else{
        cout << "Wake up to reality!" << endl;
    }

    return 0;
}
