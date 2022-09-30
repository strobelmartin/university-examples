#ifndef __PROGTEST__
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cstdlib>
#include <string>
using namespace std;
#endif /* __PROGTEST__ */
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class CDateTime
 {
	public:
						  CDateTime					( int y  = 2000, 
													  int m  = 1, 
													  int d  = 1, 
													  int h  = 0, 
													  int mi = 0, 
													  int s  = 0 );
		CDateTime 		& operator =				( const string & setStr );
		CDateTime 		  operator + 				( long long int s ) const;
		long long int	  operator - 				( const CDateTime & minuend ) const;
		bool 			  operator == 				( const CDateTime & with ) const;
		bool 			  operator != 				( const CDateTime & with ) const;
		bool 			  operator < 				( const CDateTime & with ) const;
		bool 			  operator > 				( const CDateTime & with ) const;
		bool 			  operator <= 				( const CDateTime & with ) const;
		bool 			  operator >= 				( const CDateTime & with ) const;
		int 			  operator [] 				( const string show ) const;
		friend ostream	& operator << 				( ostream & os, const CDateTime & src );
		friend istream	& operator >>				( istream & is, CDateTime & dest );
	
	private:
		long long int	  CntSeconds				( void ) const;
		int 			  year;
		int 			  month;
		int 			  day;
		int 			  hour;
		int 			  minute;
		int 			  second;
 };
//--------------------------------------------------------------------------------------------------
						  CDateTime :: CDateTime	( int y, 
													  int m, 
													  int d, 
													  int h, 
													  int mi, 
													  int s )
 {
	year   = y;
	month  = m;
	day    = d;
	hour   = h;
	minute = mi;
	second = s;
 }
//--------------------------------------------------------------------------------------------------
		CDateTime 		& CDateTime :: operator =	( const string & setStr )
 {
	stringstream ss_year   ( setStr . substr ( 0,  4 ) );
	stringstream ss_month  ( setStr . substr ( 5,  2 ) );
	stringstream ss_day    ( setStr . substr ( 8,  2 ) );
	stringstream ss_hour   ( setStr . substr ( 11, 2 ) );
	stringstream ss_minute ( setStr . substr ( 14, 2 ) );
	stringstream ss_second ( setStr . substr ( 17, 2 ) );
	
	ss_year   >> year;
	ss_month  >> month;
	ss_day    >> day;
	ss_hour   >> hour;
	ss_minute >> minute;
	ss_second >> second;

	return * this;
 }
//--------------------------------------------------------------------------------------------------
		CDateTime 		  CDateTime :: operator + 	( long long int s ) const
 {
	CDateTime res ( year, month, day, hour, minute, second );
	
	int i;
	
	int cntDays = s / 86400ll;
	s -= cntDays * 86400ll;
	
	int cntHours = s / 3600ll;
	s -= cntHours * 3600ll;
	
	int cntMinutes = s / 60ll;
	s -= cntMinutes * 60ll;
	
	int cntSeconds = s;
	
//	cout << cntDays << " " << cntHours << " " << cntMinutes << " " << cntSeconds << endl;
	
	for ( i = 0 ; i < cntDays ; i ++ )
	 {
		res . day ++;
		
		if ( 
			 ( res . day > 30 && ( res . month == 4 || res . month == 6 || res . month == 9 || res . month == 11 ) ) ||
			 ( res . day > 31 && ( res . month == 1 || res . month == 3 || res . month == 5 || res . month == 7 || res . month == 8 ||
			 				  res . month == 10 || res . month == 12 ) ) ||
			 ( res . day > 29 && res . month == 2 && ( res . year % 4 == 0 && ( res . year % 100 != 0 || res . year % 400 == 0 ) ) ) ||
			 ( res . day > 28 && res . month == 2 && ( res . year % 4 != 0 || ( res . year % 100 == 0 && res . year % 400 != 0 ) ) )
		   )
		 {
			res . day = 1;
			res . month ++;
				
			if ( res . month > 12 )
			 {
				res . month = 1;
				res . year ++;
			 }
		 }
	 }
	
	for ( i = 0 ; i < cntHours ; i ++ )
	 {
		res . hour ++;
		
		if ( res . hour > 23 )
		 {
			res . hour = 0;
			res . day ++;
		 }
		 
		if ( 
			 ( res . day > 30 && ( res . month == 4 || res . month == 6 || res . month == 9 || res . month == 11 ) ) ||
			 ( res . day > 31 && ( res . month == 1 || res . month == 3 || res . month == 5 || res . month == 7 || res . month == 8 ||
			 				  res . month == 10 || res . month == 12 ) ) ||
			 ( res . day > 29 && res . month == 2 && ( res . year % 4 == 0 && ( res . year % 100 != 0 || res . year % 400 == 0 ) ) ) ||
			 ( res . day > 28 && res . month == 2 && ( res . year % 4 != 0 || ( res . year % 100 == 0 && res . year % 400 != 0 ) ) )
		   )
		 {
			res . day = 1;
			res . month ++;
				
			if ( res . month > 12 )
			 {
				res . month = 1;
				res . year ++;
			 }
		 }
	 }
	 
	for ( i = 0 ; i < cntMinutes ; i ++ )
	 {
		res . minute ++;
		
		if ( res . minute > 59 )
		 {
			res . minute = 0;
			res . hour ++;
		 }
		
		if ( res . hour > 23 )
		 {
			res . hour = 0;
			res . day ++;
		 }
		 
		if ( 
			 ( res . day > 30 && ( res . month == 4 || res . month == 6 || res . month == 9 || res . month == 11 ) ) ||
			 ( res . day > 31 && ( res . month == 1 || res . month == 3 || res . month == 5 || res . month == 7 || res . month == 8 ||
			 				  res . month == 10 || res . month == 12 ) ) ||
			 ( res . day > 29 && res . month == 2 && ( res . year % 4 == 0 && ( res . year % 100 != 0 || res . year % 400 == 0 ) ) ) ||
			 ( res . day > 28 && res . month == 2 && ( res . year % 4 != 0 || ( res . year % 100 == 0 && res . year % 400 != 0 ) ) )
		   )
		 {
			res . day = 1;
			res . month ++;
				
			if ( res . month > 12 )
			 {
				res . month = 1;
				res . year ++;
			 }
		 }
	 }
	 
	for ( i = 0 ; i < cntSeconds ; i ++ )
	 {
		res . second ++;
		
		if ( res . second > 59 )
		 {
			res . second = 0;
			res . minute ++;
		 }
		 
		if ( res . minute > 59 )
		 {
			res . minute = 0;
			res . hour ++;
		 }
		
		if ( res . hour > 23 )
		 {
			res . hour = 0;
			res . day ++;
		 }
		 
		if ( 
			 ( res . day > 30 && ( res . month == 4 || res . month == 6 || res . month == 9 || res . month == 11 ) ) ||
			 ( res . day > 31 && ( res . month == 1 || res . month == 3 || res . month == 5 || res . month == 7 || res . month == 8 ||
			 				  res . month == 10 || res . month == 12 ) ) ||
			 ( res . day > 29 && res . month == 2 && ( res . year % 4 == 0 && ( res . year % 100 != 0 || res . year % 400 == 0 ) ) ) ||
			 ( res . day > 28 && res . month == 2 && ( res . year % 4 != 0 || ( res . year % 100 == 0 && res . year % 400 != 0 ) ) )
		   )
		 {
			res . day = 1;
			res . month ++;
				
			if ( res . month > 12 )
			 {
				res . month = 1;
				res . year ++;
			 }
		 }
	 }

	return res;
 }
//--------------------------------------------------------------------------------------------------
		long long int	  CDateTime :: operator - 	( const CDateTime & minuend ) const
 {
//	long long int min = CntSeconds ( minuend );
//	long long int sub = CntSeconds ( * this );
//	long long int result = min - sub;
	long long int min = ( * this ) . CntSeconds ();
	long long int sub = ( minuend ) . CntSeconds ();
	long long int result = min - sub;
	
	return result;
 }
//--------------------------------------------------------------------------------------------------
		bool 			  CDateTime :: operator == 	( const CDateTime & with ) const
 {
	if ( year == with . year && month  == with . month  && day    == with . day &&
		 hour == with . hour && minute == with . minute && second == with . second )
		return true;
	
	return false;
 }
//--------------------------------------------------------------------------------------------------
		bool 			  CDateTime :: operator != 	( const CDateTime & with ) const
 {
	if ( year == with . year && month  == with . month  && day    == with . day &&
		 hour == with . hour && minute == with . minute && second == with . second )
		return false;
	
	return true;
 }
//--------------------------------------------------------------------------------------------------
		bool 			  CDateTime :: operator < 	( const CDateTime & with ) const
 {
	if ( ( year <  with . year ) || 
		 ( year == with . year && month <  with . month ) || 
		 ( year == with . year && month == with . month && day <  with . day ) ||
		 ( year == with . year && month == with . month && day == with . day && 
		 	hour <  with . hour ) ||
		 ( year == with . year && month == with . month && day == with . day && 
		 	hour == with . hour	&& minute <  with . minute ) ||
		 ( year == with . year && month == with . month && day == with . day && 
		 	hour == with . hour	&& minute == with . minute && second < with . second ) )
		return true;
	
	return false;
 }
//--------------------------------------------------------------------------------------------------
		bool 			  CDateTime :: operator > 	( const CDateTime & with ) const
 {
	if ( ( year <  with . year ) || 
		 ( year == with . year && month <  with . month ) || 
		 ( year == with . year && month == with . month && day <  with . day ) ||
		 ( year == with . year && month == with . month && day == with . day && 
		 	hour <  with . hour ) ||
		 ( year == with . year && month == with . month && day == with . day && 
		 	hour == with . hour	&& minute <  with . minute ) ||
		 ( year == with . year && month == with . month && day == with . day && 
		 	hour == with . hour	&& minute == with . minute && second < with . second ) )
		return false;
	
	return true;
 }
//--------------------------------------------------------------------------------------------------
		bool 			  CDateTime :: operator <= 	( const CDateTime & with ) const
 {
	if ( year == with . year && month  == with . month  && day    == with . day &&
		 hour == with . hour && minute == with . minute && second == with . second )
		return true;
		
	if ( ( year <  with . year ) || 
		 ( year == with . year && month <  with . month ) || 
		 ( year == with . year && month == with . month && day <  with . day ) ||
		 ( year == with . year && month == with . month && day == with . day && 
		 	hour <  with . hour ) ||
		 ( year == with . year && month == with . month && day == with . day && 
		 	hour == with . hour	&& minute <  with . minute ) ||
		 ( year == with . year && month == with . month && day == with . day && 
		 	hour == with . hour	&& minute == with . minute && second < with . second ) )
		return true;
		
	return false;
 }
//--------------------------------------------------------------------------------------------------
		bool 			  CDateTime :: operator >= 	( const CDateTime & with ) const
 {
	if ( year == with . year && month  == with . month  && day    == with . day &&
		 hour == with . hour && minute == with . minute && second == with . second )
		return true;
		
	if ( ( year <  with . year ) || 
		 ( year == with . year && month <  with . month ) || 
		 ( year == with . year && month == with . month && day <  with . day ) ||
		 ( year == with . year && month == with . month && day == with . day && 
		 	hour <  with . hour ) ||
		 ( year == with . year && month == with . month && day == with . day && 
		 	hour == with . hour	&& minute <  with . minute ) ||
		 ( year == with . year && month == with . month && day == with . day && 
		 	hour == with . hour	&& minute == with . minute && second < with . second ) )
		return false;
		
	return true;
 }
//--------------------------------------------------------------------------------------------------
		int 			  CDateTime :: operator [] 	( const string show ) const
 {
	if ( show == "year"  ) return year;
	if ( show == "month" ) return month;
	if ( show == "day"   ) return day;
	if ( show == "hour"  ) return hour;
	if ( show == "min"   ) return minute;
	if ( show == "sec"   ) return second;
	
	return 0;
 }
//--------------------------------------------------------------------------------------------------
		ostream			& operator << 				( ostream & os, const CDateTime & src )
 {
	os << setw ( 4 ) << setfill ( '0' ) << src . year   << "-" 
	   << setw ( 2 ) << setfill ( '0' ) << src . month  << "-" 
	   << setw ( 2 ) << setfill ( '0' ) << src . day    << " " 
	   << setw ( 2 ) << setfill ( '0' ) << src . hour   << ":" 
	   << setw ( 2 ) << setfill ( '0' ) << src . minute << ":" 
	   << setw ( 2 ) << setfill ( '0' ) << src . second;
	
	return os;
 }
//--------------------------------------------------------------------------------------------------
		istream			& operator >> 				( istream & is, CDateTime & dest )
 {
	string tmpY, tmpM, tmpD, tmpH, tmpMi, tmpS;
	
	getline ( is, tmpY,  '-' );
	getline ( is, tmpM,  '-' );
	getline ( is, tmpD,  ' ' );
	getline ( is, tmpH,  ':' );
	getline ( is, tmpMi, ':' );
	getline ( is, tmpS       );
	
	int valY  = atoi ( tmpY  . c_str() );
	int valM  = atoi ( tmpM  . c_str() );
	int valD  = atoi ( tmpD  . c_str() );
	int valH  = atoi ( tmpH  . c_str() );
	int valMi = atoi ( tmpMi . c_str() );
	int valS  = atoi ( tmpS  . c_str() );
	
	cout << tmpY << " " << tmpM << " " << tmpD << " " << tmpH << " " << tmpMi << " "
		<< tmpS << endl;
	cout << valY << " " << valM << " " << valD << " " << valH << " " << valMi << " "
		<< valS << endl;

	if ( valS > 59 || valMi > 59 || valH > 23 || valM > 12 || valM == 0 || valD == 0 ||
		 ( valD > 30 && ( valM == 4 || valM == 6 || valM == 9 || valM == 11 ) ) ||
		 ( valD > 31 && ( valM == 1 || valM == 3 || valM == 5 || valM == 7 || valM == 8 ||
		 				  valM == 10 || valM == 12 ) ) ||
		 ( valD > 29 && valM == 2 && ( valY % 4 == 0 && ( valY % 100 != 0 || valY % 400 == 0 ) ) ) ||
		 ( valD > 28 && valM == 2 && ( valY % 4 != 0 || ( valY % 100 == 0 && valY % 400 != 0 ) ) ) )
	 {
		is . setstate ( ios :: failbit );
		return is;
	 }
	
	dest . year   = valY;
	dest . month  = valM;
	dest . day    = valD;
	dest . hour   = valH;
	dest . minute = valMi;
	dest . second = valS;
	
	return is;
 }
//--------------------------------------------------------------------------------------------------
		long long int	  CDateTime :: CntSeconds	( void ) const
 {
/*	int  y, m;
	long long int sum = 0, ysec = 0, msec = 0;
	
    for ( y = 0 ; y < year ; y ++ )
		if ( y % 4 == 0 && ( y % 100 != 0 || y % 400 == 0 ) )
			ysec += 31622400ll;
		else
			ysec += 31536000ll;

	for ( m = 0 ; m < month ; m ++ )
		switch ( m )
		 {
		 	case 0:
		 		msec += 0;
			case 2:
				if ( year % 4 == 0 && ( year % 100 != 0 || year % 400 == 0 ) )
					 msec += 2505600ll;
				else
					 msec += 2419200ll;
			case 4:  msec += 2592000ll;
			case 6:  msec += 2592000ll;
			case 9:  msec += 2592000ll;
			case 11: msec += 2592000ll;
			default: msec += 2678400ll;
		 }

	sum = ysec + msec + ( day  * 86400ll ) + ( hour * 3600ll ) + ( minute * 60ll ) + second ;
	
	return sum;
*/
	  long long int m, r, rdays=0, mdays=0, sum=0;

    for(r=0;r<year;r++) {
      if(((r%4==0) && (r<1584)) || (((r%4==0) && (r%100!=0 || (r%400==0 && r%4000!=0))) && (r>1584))) {
        rdays+=366;
      }
      else if(r==1584) {
        rdays+=356;
      }
      else {
        rdays+=365;
      }
    }

    for(m=0;m<month;m++) {
      if((m==1) || (m==3) || (m==5) || (m==7) || (m==8) || (m==10) || (m==12)) {
        mdays+=31;
      }
      else if((m==4) || (m==6) || (m==9) || (m==11)) {
        mdays+=30;
      }
      else if(m==2) {
        if(((year%4==0) && (year<=1584)) || (((year%4==0) && (year%100!=0 || (year%400==0 && year%4000!=0))) && (year>1584))) {
          mdays+=29;
        }
        else {
          mdays+=28;
        }
      }
    }

    sum=rdays+mdays+day;
    sum *= 86400ll;
    sum = sum + ( hour * 3600ll ) + ( minute * 60ll ) + second;
    return(sum);
	
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
		int				  main						( int argc, char * argv [] )
 {
	CDateTime     a, b;
	istringstream is;
	bool          st;

	b = "2011-03-01 14:50:20";
	a = "2011-12-30 21:08:14";
	
	cout << a << endl; // 2011-12-30 21:08:14
	cout << a - b << endl; // 26288274
	cout << "- - - - - - - -" << endl;
	
	a = a + 259200;
	cout << a << endl; // 2012-01-02 21:08:14
	cout << "- - - - - - - -" << endl;

	is . clear ();
	is . str ( "2000-01-01 12:00:00" );
	is >> a; // is . fail () = false
	cout << is . fail () << endl;
	cout << "- - - - - - - -" << endl;

	cout << a["year"] << endl; // 2000
	cout << a["month"] << endl; // 1
	cout << a["day"] << endl; // 1
	cout << a["hour"] << endl; // 12
	cout << a["min"] << endl; // 0
	cout << a["sec"] << endl; // 0
	cout << "- - - - - - - -" << endl;
	
	st = a == b; // st = false
	cout << st << endl;
	st = a != b; // st = true
	cout << st << endl;
	st = a >= b; // st = false
	cout << st << endl;
	st = a <= b; // st = true
	cout << st << endl;
	st = a >  b; // st = false
	cout << st << endl;
	st = a <  b; // st = true
	cout << st << endl;
	cout << "- - - - - - - -" << endl;

	a = "2000-12-31 00:00:00";
	
	is . clear ();
	is . str ( "2010-13-27 00:00:00" );
	is >> a; // is . fail () = true
	cout << is . fail () << endl;
	
	is . clear ();
	is . str ( "2003-02-29 00:00:00" );
	is >> a; // is . fail () = true
	cout << is . fail () << endl;
	
	is . clear ();
	is . str ( "2004-2-29 1:2:3" );
	is >> a; // is . fail () = false
	cout << is . fail () << endl;
	
	is . clear ();
	is . str ( "1900-02-29 00:00:00" );
	is >> a; // is . fail () = true
	cout << is . fail () << endl;
	
	is . clear ();
	is . str ( "2000-02-29 00:00:00" );
	is >> a; // is . fail () = false
	cout << is . fail () << endl;
	
	is . clear ();
	is . str ( "1600-00-00 00:00:00" );
	is >> a;
	cout << is . fail () << endl;

	is . clear ();
	is . str ( "2000-01-01 24:00:00" );
	is >> a;
	cout << is . fail () << endl;
		
	return 0;
 }
#endif /* __PROGTEST__ */


