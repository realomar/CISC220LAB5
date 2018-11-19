#include "hashNode.hpp"
#include <time.h>
#include <stdlib.h>
using namespace std;
//------------------------------------------------------------------------------------------------------------------
/*Function hashNode()
 * Purpose
 * 		Constructor for the hashNode class
 * Input
 * 		None
 * Returns
 * 		None
 */
hashNode::hashNode(){
    keyword = "";
    valuesSize = 0;
    currSize = 0;
    values = NULL;
}
//------------------------------------------------------------------------------------------------------------------
/*Function hashNode(string s)
 * Purpose
 * 		Overloaded Constructor for the hashNode class
 * Input
 * 		S : keyword for the node, but no values are inserted into the values array
 * Returns
 * 		None
 */
hashNode::hashNode(string s){
    keyword = s;
    valuesSize = 1000;
    currSize = 0;
    values = new string[valuesSize];
}
//------------------------------------------------------------------------------------------------------------------
/*Function hashNode(string s, string v)
 * Purpose
 * 		Overloaded Constructor for the hashNode class
 * Input
 * 		String s : keyword for the associated value v
 * 		String v : value that goes with the keyword s
 * Returns
 * 		None
 */
hashNode::hashNode(string s, string v){
    keyword = s;
    valuesSize = 1000;
    currSize = 1;
    values = new string[valuesSize];
    values[0] = v;
}
//--------------------------------------------------------------------------------------------------------------------
/*Function addValue(string v)
 * Purpose
 * 		adds the value to the valuesArray of the hashNode
 * Input
 * 		string v : the value to be added.
 * Returns
 * 		None
 */
void hashNode::addValue(string v){
    if(currSize < valuesSize){
        values[currSize] = v;
        currSize = currSize + 1;
        cout << currSize << " currSize has increased" << endl;
    }
    else{
        dblArray();
        values[currSize] = v;
        currSize = currSize + 1;
        cout << currSize << " currSize has increased" << endl;
    }

}
//--------------------------------------------------------------------------------------------------------------------
/*Function dblArray()
 * Purpose
 * 		doubles the size of the values array
 * Input
 * 		None
 * Returns
 * 		None
 */
void hashNode::dblArray(){
    string *tmp = new string[valuesSize*2];

    for(int i = 0; i < valuesSize; i++){
        tmp[i] = values[i];
    }
    values = tmp;
    valuesSize = valuesSize * 2;

}
//-------------------------------------------------------------------------------------------------------------------
/*Function getRandValue()
 * Purpose
 * 		Returns a random value in the values array
 * Input
 * 		None
 * Returns
 * 		None
 */
string hashNode::getRandValue(){
    cout << currSize << endl;
    if(currSize == 0){
        return("");
    }
    else{
        cout << "Current size " << currSize<< endl;
        int rand1 = rand() % currSize;
        return(values[rand1]);
    }
}