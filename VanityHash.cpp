#include "md5.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

bool checkreq(char *c) { // true if allowed
	for ( ; *c ; c++ ) {
		if ( *c >= 'A' && *c <= 'F' ) *c = *c -'A'+'a';
		if ( !(*c >= '0' && *c <= '9') && !(*c >= 'a' && *c <= 'f') ) {
			cout << "Requirement string doesn't confirm to md5 out. Please retry.\n";
			return false;
		}
	}
	return true;
}

long long fileSize( char* filePath ){
    long long fsize = 0;
    ifstream file( filePath, std::ios::binary );

    fsize = file.tellg();
    file.seekg( 0, std::ios::end );
    fsize = file.tellg() - fsize;
    file.close();

    return fsize;
}

void gen(int l, char *p) {
	for ( int i = 0 ; i < l ; i++ ) {
		*p = (char)(rand()%256);
		p++;
	}
}

char *blob;

const int MH1 = 1;
const int MH2 = 10;
const int CCC = 100000;

string dig;

int main(int argc, char** argv) {
	if ( argc != 3 ) {
		cout << "Usage: VanityHash.exe InputFile OutputFile\n";
		return 0;
	}
	int MH;
	cout << "Enter max prehash length: ";
	cin >> MH;
	if ( MH < MH1 ) MH = MH1;
	if ( MH > MH2 ) MH = MH2;
	
	long long len = fileSize(argv[1]);
	ifstream ifile(argv[1],ios::binary);
	blob = new char[len+MH+1];
	ifile.read(blob,len);
	ifile.close();
	
	bool done = false;
	MD5 md5;
	
	char req[100];
	
	sss:
	cout << "\n\nEnter requirement: ";
	cin >> req;
	if ( !checkreq(req) ) {
		delete[] blob;
		return 0;
	}
	
	int count = CCC;
	
	while ( dig.find(req) != 0 && !done ) {
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
		
		gen(MH,blob+len);
		
		dig = md5.digestMemory((BYTE*)blob,len+MH);

		if ( dig.find(req) == 0 ) {
			break;
		}
	}
	
	ofstream ofile(argv[2],ios::binary);
	ofile.write(blob,len+MH);
	
	cout << "Outfile gives " << dig << endl;
	
	cleanup:
	delete[] blob;
	
	return 0;
}
