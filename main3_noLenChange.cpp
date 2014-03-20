#include "md5.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

#define CCC 1000000;
#define MH1 2
#define MH2 32

using namespace std;

bool checkreq(char *c) {
	for ( ; *c ; c++ ) {
		if ( *c >= 'A' && *c <= 'F' ) *c = *c -'A'+'a';
		if ( !(*c >= '0' && *c <= '9') && !(*c >= 'a' && *c <= 'f') ) {
			cout << "Requirement string doesn't confirm to md5 out. Please retry.\n";
			return false;
		}
	}
	return true;
}

char basechange(int t) {
	if ( t >= 0 && t <= 25 ) return t+'a';
	if ( t >= 26 && t <= 51 ) return t-26+'A';
	if ( t >= 52 && t <= 61 ) return t-52+'0';
	return '+';
}

void gen(int t, string &a) {
	a = "";
//	t = rand()%t+1;
	for ( int i = 0 ; i < t ; i++ ) {
		char c = basechange(rand()%61);
		a.push_back(c);
	}
}

int main() {
	int MH;
	cout << "Enter max prehash length: ";
	cin >> MH;
	if ( MH < MH1 ) MH = MH1;
	if ( MH > MH2 ) MH = MH2;
	while(1){
	bool done = false;
	MD5 md5;
	
	char seed[100],req[100];
	string dig,a,b;
	
	cout << "\n\nEnter requirement: ";
	cin >> req;
	
	if ( !checkreq(req) ) continue;
	
	a = seed;
	//int len = a.length();
	//a = req;
	//len = min(len,int(a.length()));
	//int len = 123;
	dig = md5.digestString(seed);
	
	int count = CCC;
	
	while ( dig.find(req) != 0 && !done ) {
		int len;
		if(count-- <= 0) {
			cout << "Seems to be taking too long... Do you wanna exit?"; 
			char c;
			cin >> c;
			if ( c == 'y' || c == 'Y' ){
				done = true;
				break;
			}
			count = CCC;
		}
		gen(MH,a);
		dig = md5.digestString(const_cast<char*>(a.c_str()));
		if ( dig.find(req) == 0 ) {
			break;
		}
	}
	
	cout << a << " gives " << dig << endl;
	
	}
	return 0;
}
