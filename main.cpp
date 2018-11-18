/*
 * CISC220-31L LAB 5
 *
 * 	main.cpp
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

#include <iostream>
#include "makeSeuss.hpp"
using namespace std;

int main() {
    makeSeuss("DrSeuss.txt", "test.txt", true, true);
    makeSeuss("DrSeuss.txt", "test2.txt", true, false);
    makeSeuss("DrSeuss.txt", "test3.txt", false, true);
    makeSeuss("DrSeuss.txt", "test4.txt", false, false);
    return 0;
}
