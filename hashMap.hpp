/*
 * CISC220-31L LAB 5
 *
 * 	hashMap.hpp
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

#ifndef HASHMAP_HPP_
#define HASHMAP_HPP_
#include "hashNode.hpp"
#include <iostream>
using namespace std;


class hashMap {
    friend class makeSeuss;

    hashNode **map; //a single dimensional dynamically allocated array of pointers to hashNodes
    string first; // for first keyword for printing to a file
    int numKeys;
    int mapSize;
    bool h1; // if true, first hash function used, otherwise second hash function is used
    bool c1; //if true, first collision method used, otherwise second collision method is used.
    int collisionct1; //count of original collisions (caused by the hashing function used)
    int collisionct2; //count of secondary collisions (caused by the collision handling method used)

public:
    hashMap(bool hash1, bool coll1);

    void addKeyValue(string k, string v);

    int getIndex(string k);

    int calcHash(string k); // hash function

    int calcHash2(string k); // hash function 2

    int getClosestPrime();

    void reHash();

    int collHash1(int i, string k);

    int collHash2(int i, string k);

    int findKey(string k);

    bool overLoad();

    void printMap();

};


#endif /* HASHMAP_HPP_ */
