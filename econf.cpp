#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;
// 01234567
//
//orbital properties:
//  n-orbital (1-7)
//  type (s,p,d,f)
//  count
//    s: 0-2
//    p: 0-6
//    d: 0-10
//    f: 0-14
//
// 5-7: n (orbital)
// 2-4: [unused] 
// 0-1: shell type [0:s 1:p 2:d 3:f]
//
#define TYPE_S 0x00
#define TYPE_P 0x40
#define TYPE_D 0x80
#define TYPE_F 0xC0
#define TYPEBITS 0xC0
#define TYPE(s) ( (s & TYPEBITS) >> 6)
#define ORBITALBITS 0x07
#define ORBITAL(s) ( ( s & ORBITALBITS) )

const unsigned char p=TYPE_P,s=TYPE_S,d=TYPE_D,f=TYPE_F;
//duplicates to make writing fill order easier

//order that program should fill orbitals in
const unsigned char orbitalFillOrder[] = { 
//orbital | type
	1 | s,
	2 | s,
	2 | p,
	3 | s,
	3 | p,
	4 | s,
	3 | d,
	4 | p,
	5 | s,
	4 | d,
	5 | p,
	6 | s,
	4 | f,
	5 | d,
	6 | p,
	7 | s,
	5 | f,
	6 | d,
	7 | p
};

string toStr(int);

int main()
{
	while(true)
	{
		cout << "What is the atomic number of the neutral atom?\n> ";
		int atomicNumber;
		cin >> atomicNumber;
		//get atomic number from user
		
		cout << "[" << atomicNumber << " p+]: " << toStr(atomicNumber) << "\n";
		//print the electron configuration
	}
	return 0;
}





int gPE(char orbital) //get maximum possible electrons for an orbital
{
	int result;
	switch(orbital&TYPEBITS)
	{
		case TYPE_S:
			result=2;
			break;
		case TYPE_P:
			result=6;
			break;
		case TYPE_D:
			result=10;
			break;
		case TYPE_F:
			result=14;
			break;
	}
	return result;
}

char orbitalType(unsigned char orbital) //character to represent orbital type
{
	switch(orbital&TYPEBITS)
	{
		case TYPE_S:
			return 'S';
			break;
		case TYPE_P:
			return 'P';
			break;
		case TYPE_D:
			return 'D';
			break;
		case TYPE_F:
			return 'F';
			break;
	}
}

//create a string to represent the electron configuration
string toStr(int atomicNumber)
{
	unsigned char thisOrbital;
	
	ostringstream s;
	//to write strings to
	
	//iterate through all possible orbitals in order
	for(int i=0;i<sizeof(orbitalFillOrder)/sizeof(char);i++)
	{
		thisOrbital=orbitalFillOrder[i];
		//set the active orbital

		if(gPE(thisOrbital) <= atomicNumber) //if there is room for the entire filled orbital
		{
			atomicNumber -= gPE(thisOrbital);
			s <<  (thisOrbital&ORBITALBITS) <<  orbitalType(thisOrbital) << gPE(thisOrbital) << "  ";
			//add it to the result
		}
		else if(atomicNumber>0) //if only part of the filled orbital will fit
		{
			s << (thisOrbital&ORBITALBITS) << orbitalType(thisOrbital) << atomicNumber << " ";
			atomicNumber=0;
			//add that part to the result
		}
	}
	return s.str();
	//return the result
}
	
