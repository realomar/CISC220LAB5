/*
 * CISC220-31L LAB 5
 *
 * 	hashMap.cpp
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

#include "hashMap.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;


hashMap:: hashMap(bool hash1, bool coll1){
    h1 = hash1;
    c1 = coll1;
    mapSize = 199;
    map = new hashNode*[mapSize];
    collisionct1 = 0;
    collisionct2 = 0;
    numKeys = 0;
}

int hashMap:: calcHash(string k){
    //adds together all ASCII values of characters in k
    int val = 0;

    for(int i = 0; i < k.length(); i++){
        val += k[i];
    }
    return val % mapSize;
}

int hashMap:: calcHash2(string k){
    //combines ASCII values of characters in k, alternating
    //between adding and subtracting
    int val = 0;
    bool sub = false;

    for(int i = 0; i < k.length(); i++){
        if(!sub){
            val += k[i];
            sub = true;
        }
        else{
            val -= k[i];
            sub = false;
        }
    }
    return abs(val) % mapSize;
}

int hashMap:: getClosestPrime(){
    int p = mapSize * 2;
    bool isPrime = false;
    int divisors = 0;

    do{
        p++;
        divisors = 0;

        for(int i = 2; i <= p; i++){
            if(p % i == 0){
                divisors++;
            }
        }
        if(divisors == 1){
            isPrime = true;
        }
    }
    while(!isPrime);

    return p;
}

void hashMap:: addKeyValue(string k, string v){
    int index = getIndex(k);

    if(map[index] == NULL){
        map[index] = new hashNode(k);
        map[index]->addValue(v);
    }
    else{
        map[index]->addValue(v);
    }

}

int hashMap:: collHash1(int i, string k){
    //collision handling by linear probing
    int newIndex = i;

    while(1==1){
        if(map[newIndex % mapSize] == NULL || map[newIndex % mapSize]->keyword == k){
            return newIndex % mapSize;
        }
        else{
            newIndex++;
            if(newIndex > mapSize){
                newIndex -= mapSize;
            }
        }
    }
}

int hashMap:: collHash2(int i, string k){
    //collision handling by quadratic probing
    int newIndex = i;
    int quad = 1;

    while(1==1){
        if(map[newIndex % mapSize] == NULL || map[newIndex % mapSize]->keyword == k){
            return newIndex % mapSize;
        }
        else{
            newIndex += quad * quad;
            quad++;
            if(newIndex > mapSize){
                newIndex -= mapSize;
            }
        }
    }

}

int hashMap:: findKey(string k){
    int ret;
    int collIndex;

    if(h1){
        ret = calcHash(k);
    }
    else{
        ret = calcHash2(k);
    }

    if(c1){
        collIndex = collHash1(ret, k);
    }
    else{
        collIndex = collHash2(ret, k);
    }

    if(map[ret]->keyword != k || map[ret] == NULL){
        if(map[collIndex]==NULL || map[collIndex]->keyword != k){
            return -1;
        }
        else{
            return collIndex;
        }
    }
    else{
        return ret;
    }
}

bool hashMap:: overLoad(){
    int total = 0;

    for(int i = 0; i < mapSize; i++){
        if(map[i] != NULL){
            total++;
        }
    }
    return total / mapSize >= 0.7;
}

void hashMap:: reHash(){

    hashNode** tmp = map;
    int tmpSize = mapSize;

    mapSize = getClosestPrime();
    map = new hashNode*[mapSize];

    for(int i = 0; i < tmpSize; i++){
        if(tmp[i] != NULL){
            for(int j = 0; j < tmp[i]->currSize; j++){
                addKeyValue(tmp[i]->keyword, tmp[i]->values[j]);
            }
        }
    }
}

int hashMap:: getIndex(string k){
    int index;
    if(overLoad()){reHash();}

    if(h1){
        index = calcHash(k);
    }
    else{
        index = calcHash2(k);
    }

    if(map[index] == NULL || map[index]->keyword == k){
        return index;
    }
    else{
        if(c1){
            return collHash1(index, k);
        }
        else{
            return collHash2(index, k);
        }
    }

}

void hashMap:: printMap(){

    for(int i = 0; i < mapSize; i++){
        if(map[i] != NULL){
            cout << map[i]->keyword << ":";
        }
    }
}
