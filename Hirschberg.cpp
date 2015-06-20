/* Hirschberg algoritam. */

#include<iostream>
#include<string>
#include<fstream>
#include<time.h>
#include<vector>

using namespace std ;

void B( int m, int n, string str1, string str2, int LL [] )
{
    int k [2] [ n + 1 ] ;
    int i, j;
    for ( j = 0 ; j < ( n + 1 ); j++ )
		k [1] [j] = 0 ;

	for ( i = 0 ; i < m ; i++ )
	{
		for ( j = 0 ; j < ( n + 1 ) ; j++ )
			k [0] [j] = k [1] [j] ;

		for ( j = 1 ; j < ( n + 1 ) ; j++ )
		{
			if ( str1[ i ] == str2[ j - 1 ] ) 
			{
				k [1] [j] = k [0] [j-1] + 1 ; 
			}
			else
			{
				k [1] [j] = max( k [1] [j-1] , k [0] [j] ) ;
			}
		}
	}
    for ( j = 0 ; j < ( n + 1 ); j++ )
		LL [j] = k [1] [j] ;
}

string C( int m, int n, string str1, string str2, string lcs )
{
	
	if( n == 0 )
	{
		lcs = "" ;
		return lcs ;
	}
	else
	{
		if ( m == 1 )
		{
			int found ;
			found = str2.find_first_of( str1[0] );
			if ( found != string::npos )
				lcs = str1[ 0 ] ;
			else
				lcs = "" ;
				return lcs ;
		}
	}
	
	int l1[ n + 1 ], l2[ n + 1 ] ;
	int i = ( int ) ( m / 2 ) ;
	B( i, n, str1.substr( 0, i ), str2, l1 ) ;
	
	
	string str1_rev, str2_rev ;
	string::reverse_iterator rev_iter ;

	for ( rev_iter = str1.rbegin() ; rev_iter < str1.rend() ; rev_iter++ )
		str1_rev.push_back( *rev_iter );
	for ( rev_iter = str2.rbegin() ; rev_iter < str2.rend() ; rev_iter++ )
		str2_rev.push_back( *rev_iter );

    B( i + 1 , n, str1_rev.substr( 0, m - i ), str2_rev, l2 ); 
    
 
	int max = 0, k = 0 ;
	for ( int j = 0 ; j < ( n + 1 ) ; j++ )
	{
		if ( ( l1[ j ] + l2[ n - j ] ) > max )
		{
			max = l1[ j ] + l2[ n - j ] ;
			k = j ;
		}
	}

	string lcs1, lcs2 ;
	
	
	if ( i == 0 ) i++ ; 
	return C( i, k, str1.substr( 0, i ), str2.substr( 0, k ), lcs1 ).append( C( m - i , n - k , str1.substr( i, m ), str2.substr( k, n ), lcs2 ) ) ;
}




int main()
{

	string stringPrvi,stringDrugi,lcs;

	clock_t start_t, end_t, total_t;
   
	vector<string> DatotekaPrva; 
      vector<string> DatotekaDruga;

	ifstream datoteka1("30000PrvaB.txt");
 	ifstream datoteka2("30000DrugaB.txt");

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

	
	string temp;
	start_t = clock();

	for(int i=0;i< DatotekaPrva.size();i++)
	  for(int j=0; j<DatotekaDruga.size();j++)
		{
		 
		stringPrvi=DatotekaPrva[i];
		stringDrugi=DatotekaDruga[j];

		int duljinaPrvog = stringPrvi.length();
		int duljinaDrugog = stringDrugi.length();

		
		 lcs = C ( duljinaPrvog, duljinaDrugog, stringPrvi, stringDrugi, "" ) ;

		 if(lcs.size() > temp.size()) temp = lcs;
		
		}

		

		end_t = clock();

		total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

		cout<< " LCS:  " << temp << " Vrijeme: "<< total_t << endl;

	
  


 	
	return 0;
}
