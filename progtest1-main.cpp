#ifndef  __PROGTEST__
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cctype>
using namespace std;
#endif /* __PROGTEST__ */


bool sumBill ( const char * fileName, 
			   double     & sum )
 {
 	char    line [ 1024 ];
 	int     lineLen, i, cntDigitPrice = 0, cntDigitQuant = 0;
 	int     quantity = 1, decPoint = 0;
 	double  price = 0;

 	sum = 0;
 
 	ifstream inFile ( fileName );
 	if ( ! inFile ) return false;
		
	while ( inFile . getline ( line, 1024 ) )																	// nacitani radek
	{
		lineLen = inFile . gcount ();
		
		if ( ! ( line [ lineLen - 2 ] >= '0' && line [ lineLen - 2 ] <= '9' ) )									// posledni znak pred '\n' 
		{																										// nebo 'EOF' musi byt cislo
			inFile . close ();
			return false;
		}

		for ( i = lineLen - 2 ; i >= 0 ; i -- )																	// precteni ceny
		{
			if ( ( line [ i ] >= '0' && line [ i ] <= '9' ) || line [ i ] == '.' )
			{
				cntDigitPrice ++;
				
				if ( line [ i ] == '.' )
					decPoint ++;
			}	
			else
				if ( cntDigitPrice > 0 && decPoint < 2 )
				{
					price = atof ( line + ( lineLen - cntDigitPrice - 1 ) );
					break;
				}
				else
				{
					inFile . close ();
					return false;
				}
		}
		
		if ( line [ lineLen - cntDigitPrice - 3 ] == 'x' && line [ lineLen - cntDigitPrice - 4 ] == ' ' )		// precteni mnozstvi
		{
			for ( i = lineLen - cntDigitPrice - 5 ; i >= 0 ; i -- )
			{
				if ( line [ i ] >= '0' && line [ i ] <= '9' )
					cntDigitQuant ++;
				else
					if ( line [ i ] == ' ' && cntDigitQuant > 0 )
					{
						quantity = atoi ( line + ( lineLen - cntDigitPrice - cntDigitQuant - 4 ) );
						break;
					}
					else
						break;
			}
		}
		
		sum += quantity * price;
		
		quantity      = 1;
		price         = 0;
		cntDigitPrice = 0;
		cntDigitQuant = 0;
		decPoint	  = 0;
	}
	
	inFile . close ();
	return true;
 }


#ifndef  __PROGTEST__
int main ( int argc, char * argv[] )
 {
	bool   res;
    double sum;
	
	res = sumBill ( "input5.txt", sum );
	cout <<  "res = " << res << ", sum = " << sum << endl;
	res = sumBill ( "input6.txt", sum );
	cout <<  "res = " << res << ", sum = " << sum << endl;	
	res = sumBill ( "input7.txt", sum );
	cout <<  "res = " << res << ", sum = " << sum << endl;	
	res = sumBill ( "input8.txt", sum );
	cout <<  "res = " << res << ", sum = " << sum << endl;
	cout << "- - - - -" << endl;
	
    /* input1.txt:
    milk 500 ml 8.50
    bread 28.90
    beer 10 x 14.50
    */
    res = sumBill ( "input1.txt", sum ); // res = true, sum = 182.400000
	cout <<  "res = " << res << ", sum = " << sum << endl;
	
    /* input2.txt:
    yogurt 4 x 250 g 4 x 32.30
    wine 99
    dark chocolate 70 + 42.50
	*/
    res = sumBill ( "input2.txt", sum ); // res = true, sum = 270.700000
	cout <<  "res = " << res << ", sum = " << sum << endl;
	    
    /* input3.txt:
    fish
  	*/
    res = sumBill ( "input3.txt", sum ); // res = false
	cout <<  "res = " << res << ", sum = " << sum << endl;
    
    /* input4.txt:
    ham 37.20 
	*/
    res = sumBill ( "input4.txt", sum ); // res = false
	cout <<  "res = " << res << ", sum = " << sum << endl;
    
    return 0;
 }
#endif /* __PROGTEST__ */


