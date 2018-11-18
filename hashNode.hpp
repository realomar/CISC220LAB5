/*
 * CISC220-31L LAB 5
 *
 * 	hashNode.hpp
 *
 * Debra Yarrington
 *
 * Created on: Nov 10th, 2018
 *
 * TA: Moumita Bhattacharya
 *
 * Authors: omaromar@udel.edu Omar Ahmad
 *  		tamimoz@udel.edu  Ahmad Tamimi
 *
 */

#ifndef HASHNODE_HPP_
#define HASHNODE_HPP_
#include <iostream>
using namespace std;


class hashNode {
    friend class hashMap;

    string keyword; // this is used as the key � each key is only inserted once!

    string *values; // the dynamically allocated array (not linked list!) of words that follow the key in the Dr. Seuss text.

    int valuesSize; // the size of the values array

    int currSize; // the number of words in the values array so far

public:
    hashNode();

    hashNode(string s);

    hashNode(string s, string v);

    void addValue(string v);

    void dblArray();

    string getRandValue();

};

#endif /* HASHNODE_HPP_ */
