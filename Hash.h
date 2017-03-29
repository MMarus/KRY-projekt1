//
// Created by archie on 3/29/17.
//

#ifndef KRY_PROJEKT1_HASH_H
#define KRY_PROJEKT1_HASH_H

#import <iostream>
using  namespace std;

class Hash {
public:
    static string createSHA256(string msg);
    static bool isHashCorrect(string hash, string msg);
    static void handleErrors();
};


#endif //KRY_PROJEKT1_HASH_H
