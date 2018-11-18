/*
 * CISC220-31L LAB 5
 *
 * 	hashNode.cpp
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

#include "hashNode.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
using namespace std;

hashNode:: hashNode() {
    keyword = "";
    valuesSize = 0;
    currSize = 0;
    values = NULL;
    srand(time(0));
}

hashNode:: hashNode(string s){
    keyword = s;
    valuesSize = 100;
    currSize = 0;
    values = new string[valuesSize];
    srand(time(0));

}

void hashNode:: addValue(string v){
    values[currSize] = v;
    currSize++;
    if(currSize == valuesSize){
        dblArray();
    }
}

void hashNode:: dblArray(){
    string *tmp = new string[valuesSize * 2];

    for(int i = 0; i < valuesSize; i++){
        tmp[i] = values[i];
    }
    valuesSize *= 2;
    values = tmp;
}

string hashNode:: getRandValue(){

    if(currSize == 0){
        return "";
    }
    else {

        int rando = rand() % currSize;
        return values[rando];

    }
}
