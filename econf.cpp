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
		cout << "How many electrons in atom?\n> ";
		int atomicNumber;
		cin >> atomicNumber;
		cout << "[" << atomicNumber << " p+]: " << toStr(atomicNumber) << "\n";
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
char orbitType(unsigned char orbital)
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
string toStr(int atomicNumber)
{
	unsigned char thisOrbital;
	ostringstream s;
	for(int i=0;i<sizeof(orbitalFillOrder)/sizeof(char);i++)
	{
		thisOrbital=orbitalFillOrder[i];
		if(gPE(thisOrbital) <= atomicNumber)
		{
			atomicNumber -= gPE(thisOrbital);
			s <<  (thisOrbital&ORBITALBITS) <<  orbitType(thisOrbital) << gPE(thisOrbital) << "  ";
		}
		else if(atomicNumber>0)
		{
			s << (thisOrbital&ORBITALBITS) << orbitType(thisOrbital) << atomicNumber << " ";
			atomicNumber=0;
		}
	}
	return s.str();
}
	
