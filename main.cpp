#include "md5.h"
#include <iostream>
#include <string>
#include <algorithm>

#define CCC 1000000;
#define MH1 2
#define MH2 12

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
	
	cout << "\n\nEnter seed and requirement: ";
	cin >> seed >> req;
	
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
		b = dig.substr(0,MH);
		for ( len = 1 ; len <= MH ; len++ ) {
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
			a = b.substr(0,len);
			dig = md5.digestString(const_cast<char*>(a.c_str()));
			if ( dig.find(req) == 0 ) {
				break;
			}
		}
	}
	
	cout << a << " gives " << dig << endl;
	
	}
	return 0;
}
