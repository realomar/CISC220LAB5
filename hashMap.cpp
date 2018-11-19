#include "hashMap.hpp"
#include <time.h>
#include <stdlib.h>
using namespace std;

//----------------------------------------------------------------------------------------------------------
/*Function hashMap(bool hash1, bool coll1)
 * Purpose
 * 		Constructor for the hashmap class
 * Input
 * 		bool hash1, bool coll1 : booleans to detrmine what hash and collision function that should be used
 * Returns
 * 		None
 */
hashMap::hashMap(bool hash1, bool coll1){
    h1 = hash1;
    c1 = coll1;
    first = "";
    numKeys = 0;
    mapSize = 5;
    collisionct1 = 0;
    collisionct2 = 0;
    map = new hashNode*[mapSize];
    for(int i = 0; i < mapSize; i++){
        map[i] = NULL;
    }

}
//----------------------------------------------------------------------------------------------------------
/*Function addKeyValue(string k, string v)
 * Purpose
 * 		adding a new key value to the hashmap
 * Input
 * 		String K
 * 			key value for the new added value
 * 		String V
 * 			value assigned to the key
 * Returns
 * 		None
 */
void hashMap::addKeyValue(string k, string v){
    cout << k << endl;

    int key;
    if(h1){
        key = calcHash(k); //logic for determining what hash function to use
    }
    if(!h1){
        key = calcHash2(k);
    }
    if(map[key] == NULL){
        map[key] = new hashNode(k,v); //if the index in the map is NULL we need to place a new node there
        numKeys++;
    }
    else{
        if(map[key]->keyword == k){
            map[key]->addValue(v); //if the node in the index has the same keyword we just need to call the add value function
        }
        else{
            if(map[key]->keyword != k){
                if(c1){
                    key = collHash1(key, -1, k); //if the node in the index doesnt have the same keyword we need to call one of the collision functions
                }
                if(!c1){
                    key = collHash2(key, -1, k);
                }
                if(map[key]!=NULL && map[key]->keyword == k){
                    map[key]->addValue(v); //if after the collision function the index has the same keyword of as the one you are searching we need to call the add value functions
                }
                else{
                    map[key] = new hashNode(k,v); //if the new index is NULL we need to create a new node to go in the space
                    numKeys++;
                }

            }
        }
    }
    double load = (double) numKeys / (double) mapSize;
    if(load > 0.7){
        reHash(); //if the load is more than 70% we need to call the reHash function
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------
/*Function getIndex(string k))
 * Purpose
 * 		returns the index of a certain key value using the hash and collision functions
 * Input
 * 		string k
 * 			the key value that we want the index for
 * Returns
 * 		int : that the string k hash's to
 */
int hashMap::getIndex(string k){
    int index;
    if(h1){
        index = calcHash(k); //calculates the index that the keyword hashes to
    }
    if(!h1){
        index = calcHash2(k);
    }
    if(c1){
        if(map[index]->keyword != k && map[index] != NULL){
            index = collHash1(index, -1, k);
            cout << (map[index] == NULL) << endl; //if there is a collision the respective collision function is called
        }
    }
    if(!c1){
        if(map[index]->keyword != k && map[index] != NULL){
            index = collHash2(index, -1, k);
        }
    }
    return(index);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------
/*Function collHash1(int h, int i, string k)
 * Purpose
 * 		The first collision function, using linear probing
 * Input
 * 		int h: old index
 * 		int i: used as a flag to make sure it exits out of the loop if the value is not within the map
 * 		string k: the key associated with the index h;
 * Returns
 * 		int: new index that doesn't have a collision
 */
int hashMap::collHash1(int h, int i, string k){
    int index = h;
    while(map[index] != NULL && map[index]->keyword != k){ //collHash1 is linear probing
        index++;
        if(index >= mapSize){
            index = index % mapSize;
        }
        if(index == i && i!= 0){ // if it fully loops through the entire map it will return negative one
            return(-1);
        }
    }

    return(index);
}
//------------------------------------------------------------------------------------------------------------------------------------
/*Function getClosestPrime()
 * Purpose
 * 		returns the closest prime number to the current map size
 * Input
 * 		none
 * Returns
 * 		returns the closest prime to double the current mapSize
 */
int hashMap::getClosestPrime(){
    int currentPrime = 2*mapSize;
    int divisor = mapSize - 1;

    bool findNewPrime = false;
    while(!findNewPrime){
        if(divisor != 1){ //this loop will divide the number by every number below it and increment that number until we find the next prime
            if(currentPrime % divisor != 0){
                divisor--;
            }
            else{
                currentPrime = currentPrime + 1;
                divisor = currentPrime - 1;
            }
        }
        else{
            findNewPrime = true; //sets the flag to true so the while loop will stop
        }

        //needs to  be moved outside the loop, also there is a load in the rehash function that is upside down
    }
    return (currentPrime);
}
//---------------------------------------------------------------------------------------------------------------------
/*Function reHash()
 * Purpose
 * 		if the load of the hasMap goes over 0.70 we have to double the map size, and rehash all the old values into that new map
 * Input
 * 		None
 * Returns
 * 		None
 */
void hashMap::reHash(){
    int oldMapS = mapSize; //stores the oldMapS
    int newMapSize = getClosestPrime(); //calculates the new mapSize
    hashNode **tmp = map; //stores the old map
    map = new hashNode*[newMapSize]; //doubles the mapSize
    mapSize = newMapSize;
    for(int i = 0; i < mapSize; i++){
        map[i] = NULL; //sets all of the new map spots to NULL
    }
    for(int i = 0; i < oldMapS; i++){
        int index;
        if(tmp[i] != NULL){ //if the index in the old map is not null we need to recalculate its new position in the doubled map
            if(h1){
                index = calcHash(tmp[i]->keyword);
            }
            else{index = calcHash2(tmp[i]->keyword);}

            if(map[index] != NULL){
                if(c1){index = collHash1(index, -1, tmp[i]->keyword);}
                else{index = collHash2(index, -1, tmp[i]->keyword);}
            }
            map[index] = tmp[i];
            cout << map[index]->keyword << endl; //Used for testing purposes
            cout << map[index]->currSize << endl;
        }
    }

}

//---------------------------------------------------------------------------------------------------------------------
/*Function findKey(string k)
 * Purpose
 * 		finds a key in the hashmap using the collision and calchash functions
 * Input
 * 		string k : the keyword for the value that you wish to find
 * Returns
 * 		returns the index of the key you wish to find
 */
int hashMap::findKey(string k){
    int index;
    if(h1){index = calcHash(k);} //uses the appropriate hash function to calculated an index
    else{index = calcHash2(k);}
    int originalIndex = index;
    if(map[index]->keyword != k){
        if(c1){index = collHash1(index, originalIndex,k);} //uses a collision function to calculate a new index if there s a collision
        else{index = collHash2(index, originalIndex, k);}
    }
    return(index);
}
//-----------------------------------------------------------------------------------------------------------------------
/*Function calchash()
 * Purpose
 * 		the first hash function that takes the ascii value of the first character in the string and multiplies it by 20
 * Input
 * 		string k : the string that is the k for the hashmap
 * Returns
 * 		returns the index that this hash function calculates
 */
int hashMap::calcHash(string k){
    int length = sizeof(k);
    int sum = 0;
    sum = (int) k[0] * 20; //takes the ascii value of the first character of the string and multiplies it by 20.
    return(sum % mapSize);
}
//-----------------------------------------------------------------------------------------------------------------------
/*Function calcHash2(string k)
 * Purpose
 * 		the second hash function that squares the ascii value of the first character of the string, and if it is greater than 1000 multiplies by 25 and if it is less than 1000 subtracts 10;
 * Input
 * 		string k : the keyword that we wish to calculate the hash function for
 * Returns
 * 		returns the index that is associated with that k
 */
int hashMap::calcHash2(string k){
    int index = ((int) k[0]) * ((int)k[0]); //squares the first ascii value of a string
    if(index > 1000){
        index = index * 25; //if it is more than 1000 we multiply by 25
    }
    else{
        index - 10; //if less than 1000 we subtract 10
    }
    index = index % mapSize;
    return(index);
}
//-----------------------------------------------------------------------------------------------------------------------
/*Function collHash2(int h, int i, string k)
 * Purpose
 * 		the second collision function that is quadratic probing
 * Input
 * 		int h: old index
 * 		int i: a flag variable that is being used to make sure it isn't an infinite loop
 * 		int k : the keyword that we want the index fo
 * Returns
 * 		an integer of the index that is associated with the keyword.
 */
int hashMap::collHash2(int h, int i, string k){
    int index = h;
    int numCol = 1;
    while(map[index] != NULL && map[index]->keyword != k){ //second collision function

        index = index + (numCol * numCol); //quadratic probing

        if(index >= mapSize){
            index = index % mapSize;
        }
        numCol++;
    }

    if(index == i && i!= 0){ //prevents infinite loops
        return(-1);
    }

    return(index);
}