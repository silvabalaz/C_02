#include <fstream> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <time.h> 
#include <sys/time.h>

using namespace std;

int max( int a, int b)
{
	return (a > b)? a : b;

}

/*Generiranje nul-matrice dimenzije duljinaPrvog x duljinaDrugog*/

vector< vector<int> > MatricaBrojeva(string& Prvi, string& Drugi)
{
	vector < vector<int> > Matrica;
	
	
	
	for(int i=0; i<Prvi.size()+1; i++)
		Matrica.push_back(vector<int>(Drugi.size()+1,0));
	

	return Matrica;


}

/*Ispis elemenata matrice*/

void IspisMatrice(vector<vector<int> > Matrica, int duljinaPrvog, int duljinaDrugog)
{
	cout<<"Ispis matrice koja sadrzi duljine LCS-a: "<<endl<<endl<<endl;
	for(int i = 0; i<duljinaPrvog; i++)
	{	 for(int j=0; j<duljinaDrugog; j++)
			cout<<Matrica[i][j]<<" ";
		cout<<endl;
	}		cout<<" ";

}

/*Nalazi najdulji podniza od dana dva stringa*/

string NajduljiPodniz(vector<vector<int> > Matrica, string& stringPrvi, string& stringDrugi)
{
	int duljinaPrvog = stringPrvi.length()+1;
	int duljinaDrugog = stringDrugi.length()+1;

		//generiranje matrice duljina zajednickih podnizova
		for( int i=1; i < duljinaPrvog; i++ )
			for( int j = 1; j < duljinaDrugog; j++ )
			{
		  		 if( stringPrvi[i-1] == stringDrugi[j-1] )
						Matrica[i][j] = Matrica[i-1][j-1] +1;
	
				 else Matrica[i][j] = max( Matrica[i-1][j], Matrica[i][j-1]);	
			}
		        

	cout<<endl;
	
	//IspisMatrice(Matrica,duljinaPrvog,duljinaDrugog);

	


	//ispis najduljeg zajednickog podniza-backtracking

	
      int duljinaPodniza = Matrica[duljinaPrvog-1][duljinaDrugog-1];
	cout<<endl;
	//cout<<"Duljina zajednickog podniza : "<<duljinaPodniza<<endl<<endl;	
	char lcs[duljinaPodniza+1];
	lcs[duljinaPodniza]='\0';

	
   int i = duljinaPrvog-1, j = duljinaDrugog-1;
   while (i > 0 && j > 0)
   {
     
      if ( stringPrvi[i-1] == stringDrugi[j-1] )
      { 
          lcs[duljinaPodniza-1] = stringPrvi[i-1]; 
          i--; j--; duljinaPodniza--;     
      }
 
      
      else if (Matrica[i-1][j] > Matrica[i][j-1])
         i--;
      else
         j--;
   }
 

   
   return lcs;
}

/*Glavna funkcija-unos stringova iz dvije datoteke*/
int main(void)
{
	string stringPrvi,stringDrugi;
	vector< vector <int> > Matrica;

	clock_t start_t, end_t, total_t;

	vector<string> DatotekaPrva; 
      vector<string> DatotekaDruga;

	ifstream datoteka1("10000PrvaB.txt");
 	ifstream datoteka2("10000DrugaB.txt");

	vector<string>::iterator iter;
	cout<<"Ulazni stringovi:"<<endl<<endl;
        for (string Rijec; datoteka1 >> Rijec; ) 
        { 
            DatotekaPrva.push_back(Rijec); 
        } 
    
	for(iter=DatotekaPrva.begin(); iter< DatotekaPrva.end(); iter++)
		cout<<(*iter)<<endl;
	

	for (string Rijec; datoteka2 >> Rijec; ) 
        { 
            DatotekaDruga.push_back(Rijec); 
        } 
    
	for(iter=DatotekaDruga.begin(); iter< DatotekaDruga.end(); iter++)
		
		cout<<(*iter)<<endl<<endl;;
	
	string temp = "";
	start_t = clock();
	
	
		for(int i=0;i< DatotekaPrva.size();i++)
	  for(int j=0; j<DatotekaDruga.size();j++)
		{
		 
		stringPrvi=DatotekaPrva[i];
		stringDrugi=DatotekaDruga[j];

		int duljinaPrvog = stringPrvi.length()+1;
		int duljinaDrugog = stringDrugi.length()+1;

	

		Matrica = MatricaBrojeva(stringPrvi, stringDrugi);
		//IspisMatrice(Matrica,duljinaPrvog,duljinaDrugog);
			 
		string lcs = NajduljiPodniz(Matrica,stringPrvi,stringDrugi);
		
		if(lcs.size() > temp.size()) temp = lcs;
		
		}
		end_t = clock();
		total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
		
		
		cout<< " Najdulji zajednički podniz dvije datoteke je: " << temp << endl << endl;
		cout<< " Ukupno vrijeme izvršavanja  programa: " << total_t << endl << endl;
		
		
	

   			


	exit(0);
}
