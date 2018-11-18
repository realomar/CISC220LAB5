/*
 * CISC220-31L LAB 5
 *
 * 	makeSeuss.hpp
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

#ifndef MAKESEUSS_HPP_
#define MAKESEUSS_HPP_

#include "hashMap.hpp"
#include <iostream>
using namespace std;

class makeSeuss {
    hashMap *ht;
    string fn; // file name for input (�DrSeuss.txt�)
    string newfile; // name of output file
public:
    makeSeuss(string file,string newf,bool h1, bool c1);
    void readFile();
    void writeFile();
    hashMap* getHt();
};

#endif /* MAKESEUSS_HPP_ */
