// Rekurzivni (Memoization)

#include <fstream> 
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <time.h> 
#include<vector>
#include <sys/time.h>

using namespace std;


string char_to_string(char c) { return string(1, c); }

map< pair< pair<string, string>, string>, string > hash;



string lcsRec(string s1, string s2, string lcs = "") {

    pair<string, string> s1s2 = make_pair(s1, s2);
    pair< pair<string, string>, string> lcsTriplet = make_pair(s1s2,lcs);

    if (hash.count(lcsTriplet)) {
        return hash[lcsTriplet];
    }

    if (s1.size() == 0 || s2.size() == 0)
        return hash[lcsTriplet] = lcs;

    string s1Minus1 = s1.substr(0, s1.size() - 1);
    string s2Minus1 = s2.substr(0, s2.size() - 1);

     if (s1[s1.size() - 1] == s2[s2.size() - 1])
        return hash[lcsTriplet] = lcsRec(s1Minus1, s2Minus1, char_to_string(s1[s1.size() - 1]) + lcs);

    string tren1 = lcsRec(s1Minus1, s2, lcs);
    string tren2 = lcsRec(s1, s2Minus1, lcs);

    return hash[lcsTriplet] = (tren1.size() > tren2.size()) ? tren1 : tren2;
}




int main() {
    // cout << lcsRec("ooappleoot", "motot") << endl;
    // hash.clear();
    // cout << lcsRec("hello", "hello") << endl;
    // hash.clear();
   
	string stringPrvi,stringDrugi;

	clock_t start_t, end_t, total_t;

	vector<string> DatotekaPrva; 
      vector<string> DatotekaDruga;

	ifstream datoteka1("100Prva.txt");
 	ifstream datoteka2("100Druga.txt");

	vector<string>::iterator iter;
	string temp="";

        for (string Rijec; datoteka1 >> Rijec; ) 
        { 
            DatotekaPrva.push_back(Rijec); 
        } 
    
	  /*for(iter=DatotekaPrva.begin(); iter< DatotekaPrva.end(); iter++)
		cout<<(*iter)<<endl;*/


	  for (string Rijec; datoteka2 >> Rijec; ) 
        { 
            DatotekaDruga.push_back(Rijec); 
        } 
    	/*
	  for(iter=DatotekaDruga.begin(); iter< DatotekaDruga.end(); iter++)
		cout<<(*iter)<<endl;*/


	start_t = clock();
		

	for( int i = 0; i < DatotekaPrva.size(); i++ )
	  for( int j = 0; j < DatotekaDruga.size(); j++ )
		{
		
		stringPrvi = DatotekaPrva[i];
		stringDrugi = DatotekaDruga[j];

		int duljinaPrvog = stringPrvi.length()+1;
		int duljinaDrugog = stringDrugi.length()+1;

		cout<< endl <<" PRVI STRING: " << stringPrvi << " , " << " DRUGI STRING: " << stringDrugi << endl << endl;

		string LCS = lcsRec( stringPrvi, stringDrugi, "" );

		if( LCS.size() > temp.size() ) temp = LCS;
		
		
		
		

	
/*
	cout<<"ISPIS STA JE U MAPI: "<<endl<<endl<<endl;
	
     for(map< pair< pair<string, string>, string>,string >::iterator iter = hash.begin(); iter != hash.end(); ++iter) {
         cout << iter->first.first.first << " " << iter->first.first.second << " " << iter->first.second <<" " << iter->first.second << " lcs: "<<iter->second<<endl;*/

	hash.clear();
     }
	
	
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	
	cout << endl << " Najdulji zajedniÄki podniz dvije datoteke je:  "<< temp << endl<<endl;
	cout<< " Vrijeme izvrĊĦavanja programa : "<< total_t << endl << endl << endl;

	

}
