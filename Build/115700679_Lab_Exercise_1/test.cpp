using namespace std;
#include <iostream>

//sees if string A is alphabetically befoer string B
// bool isBefore(string& strA, string& strB){
//     int n = 0;

//     //while you are not at the end of StrA
//     while(strA[n] != '/0'){
//         //if the letter in A is smaller (before) the letter in B
//         if(strA[n] < strB[n]){
//             return true;
//         }
//         //if the letters are the same, reevaluate at the next letter
//         else if(strA[n] == strB[n]){
//             n++;
//             continue;
//         }
//         //otherwise return false
//         else{
//             return false;
//         }
//     }

//     //if you reach the end of the string and A was the same so far, it's before
//     return true;
// }

int main() {

    string str1;
    string str2;

    cout << "STR1: ";
    cin >> str1;

    cout << "STR2: ";
    cin >> str2;

    cout << str1 << "   " << str2 << endl;

    //cout << isBefore(str1, str2);

    return 0;
}