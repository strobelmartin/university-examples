#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
#endif /* __PROGTEST__ */
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class CPhoneBook
 {
	public:
		static const int  MAX_PHONES_PER_USER = 16;
		
				  		  CPhoneBook							( void );
						~ CPhoneBook    						( void );
		/*
				  		  CPhoneBook							( const CPhoneBook & from );
		CPhoneBook		& operator =  							( const CPhoneBook & from );
		*/
		bool			  Add									( const string & name,
												  		  		  const string & address,
												  		  		  const string & phone );
		bool			  Del									( const string & name,
												  		  		  const string & address );
		bool			  Del									( const string & phone );
		bool			  Search								( const string & name,
																  const string & address,
																        int      idx,
																        string & phone ) const;
		bool			  Search								( const string & phone,
																        string & name, 
																		string & address ) const;
	private:
		/*
		void			  Sort									( void );
		
		int				  FindIdx_Add							( const string & name,
																  const string & address,
																  const string & phone );
		int				  FindIdx_Del							( const string & name,
																  const string & address,
																        int    * idx [],
																        int    & idxCount );
		*/
		int				  CntPhones 							( const string & name,
																  const string & address );
		void              Resize 								( int newsize );
		string    		* pb_name;
		string    		* pb_address;
		string    		* pb_phone;
		int         	  size;
		int         	  count;
 };
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
				  		  CPhoneBook :: CPhoneBook				( void )
 {
	pb_name     = new string [ 1000 ];
	pb_address  = new string [ 1000 ];
	pb_phone    = new string [ 1000 ];
	size     = 1000;
	count    = 0;
 }
//--------------------------------------------------------------------------------------------------
				  		  CPhoneBook :: ~ CPhoneBook			( void )
 {
	delete [] pb_name;
	delete [] pb_address;
	delete [] pb_phone;
	size     = 0;
	count    = 0;
 }
//--------------------------------------------------------------------------------------------------
/*
				  		  CPhoneBook :: CPhoneBook				( const CPhoneBook & from )
 {
	pb_name    = new string [ from . size ];
	pb_address = new string [ from . size ];
	pb_phone   = new string [ from . size ];
	size  = from . size;
	count = from . count;
	
	for ( int i = 0 ; i < count ; i ++ )
	 {
		pb_name    [ i ] = from . pb_name    [ i ];
		pb_address [ i ] = from . pb_address [ i ];
		pb_phone   [ i ] = from . pb_phone   [ i ];
	 }
 }
//--------------------------------------------------------------------------------------------------
		CPhoneBook		  CPhoneBook :: & operator =  			( const CPhoneBook & from )
 {
	if ( this == & from )
		return * this;

	delete [] pb_name;
	delete [] pb_address;
	delete [] pb_phone;
	pb_name     = new string [ from . size ];
	pb_address  = new string [ from . size ];
	pb_phone    = new string [ from . size ];
	size  = from . size;
	count = from . count;

	for ( int i = 0 ; i < count ; i ++ )
	 {
		pb_name    [ i ] = from . pb_name    [ i ];
		pb_address [ i ] = from . pb_address [ i ];
		pb_phone   [ i ] = from . pb_phone   [ i ];
	 }
 }
*/
//--------------------------------------------------------------------------------------------------
		bool	  		  CPhoneBook :: Add						( const string & name,
												  		  		  const string & address,
												  		  		  const string & phone )
 {
 	//int     i, idx;
 	string  tmpName, tmpAddr;
 	
	if ( Search ( phone, tmpName, tmpAddr ) )
		return false;
	if ( CntPhones ( name, address ) > MAX_PHONES_PER_USER )
		return false;
	
	if ( count + 1 > size )
		Resize ( size * 2 );

	/*
	if ( count < 3 )
	 {	 	
		pb_name    [ count ] = name;
		pb_address [ count ] = address;
		pb_phone   [ count ] = phone;
		
		count ++;
		Sort ();
		return true;
	 }
	 
	idx = FindIdx_Add ( name, address, phone );
	
	for ( i = count - 1 ; i >= idx ; i -- )
	 {
		pb_name    [ i + 1 ] = pb_name    [ i ];
		pb_address [ i + 1 ] = pb_address [ i ];
		pb_phone   [ i + 1 ] = pb_phone   [ i ];
	 }
	
	pb_name    [ idx ] = name;
	pb_address [ idx ] = address;
	pb_phone   [ idx ] = phone;
	*/
	
	pb_name    [ count ] = name;
	pb_address [ count ] = address;
	pb_phone   [ count ] = phone;
	
	count ++;
	
	return true;
 }
//--------------------------------------------------------------------------------------------------
		bool	  		  CPhoneBook :: Del						( const string & name,
												  		  		  const string & address )
 {
 	int     i;//, j , * idx, idxCount = 0;
 	string  tmpPhone;
 	
	if ( ! Search ( name, address, 0 ,tmpPhone ) )
		return false;
	/*
	idx = new int [ 100 ];
	FindIdx_Del ( name, address, & idx, idxCount );
	*/
	
	//for ( i = 0 ; i < idxCount ; i ++ )
	for ( i = 0 ; i < count ; i ++ )
	 {
		if ( pb_name [ i ] == name && pb_address [ i ] == address )
		 {
			pb_name    [ i ] = "nothing";
			pb_address [ i ] = "nothing";
			pb_phone   [ i ] = "nothing";
		 }

		/*
		for ( j = idx [ i ] ; j < count - 2 ; j ++ )
		 {
			pb_name    [ j ] = pb_name    [ j + 1 ];
			pb_address [ j ] = pb_address [ j + 1 ];
			pb_phone   [ j ] = pb_phone   [ j + 1 ];
		 }
	
		pb_name    [ count - 1 ] = "";
		pb_address [ count - 1 ] = "";
		pb_phone   [ count - 1 ] = "";
	
		count --;
		*/
	 }
	
	//delete [] idx;
	return true;
 }
//--------------------------------------------------------------------------------------------------
		bool			  CPhoneBook :: Del						( const string & phone )
 {
	int idx;//, i;
	string tmpName, tmpAddr;
	
	if ( ! Search ( phone, tmpName, tmpAddr ) )
		return false;
	
	for ( idx = 0 ; idx < count ; idx ++ )
		if ( pb_phone [ idx ] == phone ) break;
		
	/*
	for ( i = idx ; i < count - 2 ; i ++ )
	 {
		pb_name    [ i ] = pb_name    [ i + 1 ];
		pb_address [ i ] = pb_address [ i + 1 ];
		pb_phone   [ i ] = pb_phone   [ i + 1 ];
	 }
	
	pb_name    [ count - 1 ] = "";
	pb_address [ count - 1 ] = "";
	pb_phone   [ count - 1 ] = "";
	
	count --;
	*/
	
	pb_name    [ idx ] = "";
	pb_address [ idx ] = "";
	pb_phone   [ idx ] = "";	
	
	return true;
 }
//--------------------------------------------------------------------------------------------------		
		bool			  CPhoneBook :: Search					( const string & name,
																  const string & address,
																        int      idx,
																        string & phone ) const
 { 	
 	int tmpIdx = 0;
 	
	for ( int i = 0 ; i < count && tmpIdx <= idx ; i ++ )
		if ( pb_name [ i ] == name && pb_address [ i ] == address )
		 {			
			if ( tmpIdx == idx )
			 {
				phone = pb_phone [ i ];
				return true;
			 }
			else
			 {
				tmpIdx ++;
				continue;
			 }
		 }

	return false;
 }
//--------------------------------------------------------------------------------------------------																        
		bool			  CPhoneBook :: Search					( const string & phone,
																        string & name, 
																		string & address ) const
 {
	for ( int i = 0 ; i < count; i ++ )
		if ( pb_phone [ i ] == phone )
		 {
			name    = pb_name    [ i ];
			address = pb_address [ i ];
			return true;
		 }
	
	return false;
 }
//--------------------------------------------------------------------------------------------------
/*
		int				  CPhoneBook :: FindIdx_Add				( const string & name,
																  const string & address,
																  const string & phone )
 {
	
 }
*/
//--------------------------------------------------------------------------------------------------
/*
		int				  CPhoneBook :: FindIdx_Del				( const string & name,
																  const string & address,
																        int    * idx [],			// ! pole neni referencovano
																        int    & idxCount )
 {
	
 }
*/
//--------------------------------------------------------------------------------------------------
/*
		void			  CPhoneBook :: Sort					( void )
 {
	int       i, j, minIdx;
	string    tmp_name;
	string    tmp_address;
	string    tmp_phone;

	for ( i = 0 ; i < count - 1 ; i ++ )
	 {
		minIdx = i;

		for ( j = i + 1 ; j < count ; j ++ )
			if ( ( pb_name[ j ] <  pb_name[ minIdx ] ) ||
			     ( pb_name[ j ] == pb_name[ minIdx ] && pb_address[ j ] <  pb_address[ minIdx ] ) ||
			     ( pb_name[ j ] == pb_name[ minIdx ] && pb_address[ j ] == pb_address[ minIdx ] &&
			           pb_phone[ j ] < pb_phone[ minIdx ] ) )
				minIdx = j;

		tmp_name    = pb_name    [ minIdx ];
		tmp_address = pb_address [ minIdx ];
		tmp_phone   = pb_phone   [ minIdx ];
		
		pb_name    [ minIdx ] = pb_name    [ i ];
		pb_address [ minIdx ] = pb_address [ i ];
		pb_phone   [ minIdx ] = pb_phone   [ i ];
		
		pb_name    [ i ] = tmp_name;
		pb_address [ i ] = tmp_address;
		pb_phone   [ i ] = tmp_phone;
	 }
 }
*/
//--------------------------------------------------------------------------------------------------
		int				  CPhoneBook :: CntPhones 				( const string & name,
																  const string & address )
 {
	int cnt = 0;
	
	for ( int i = 0 ; i < count ; i ++ )
		if ( pb_name [ i ] == name && pb_address [ i ] == address )
			cnt ++;
	
	return cnt;
 }
//--------------------------------------------------------------------------------------------------
		void	  		  CPhoneBook :: Resize					( int newsize )
 {
	string  * newName    = new string [ newsize ];
	string  * newAddress = new string [ newsize ];
	string  * newPhone   = new string [ newsize ];
	
	for ( int i = 0 ; i < count ; i ++ )
	 {
		newName    [ i ] = pb_name    [ i ];
		newAddress [ i ] = pb_address [ i ];
		newPhone   [ i ] = pb_phone   [ i ];
	 }
	
	size = newsize;
	
	delete [] pb_name;
	delete [] pb_address;
	delete [] pb_phone;
	
	pb_name    = newName;
	pb_address = newAddress;
	pb_phone   = newPhone;
 }
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
		int 	  		  main									( int argc, char * argv [] )
 {
	bool    status;
	string  phone, name, addr;

	CPhoneBook  b1;
	
	status = b1 . Add ( "Smith", "Oak road", "123456" );			// status = true
	cout << "status = " << status << endl;
	status = b1 . Add ( "Brown", "Second street", "7654321" );		// status = true
	cout << "status = " << status << endl;
	status = b1 . Add ( "Hacker", "5-th avenue", "02348" );			// status = true
	cout << "status = " << status << endl;
	status = b1 . Add ( "Hacker", "7-th avenue", "13278" );			// status = true
	cout << "status = " << status << endl;
	status = b1 . Search ( "Brown", "Second street", 0, phone );	// status = true, phone = "7654321"
	cout << "status = " << status << ", phone = " << phone << endl;
	status = b1 . Search ( "Brown", "Second street", 1, phone );	// status = false
	cout << "status = " << status << endl;
	status = b1 . Search ( "Hacker", "Oak road", 0, phone );		// status = false
	cout << "status = " << status << endl;
	status = b1 . Search ( "Smith", "Oak road", 0, phone );			// status = true, phone = "123456"
	cout << "status = " << status << ", phone = " << phone << endl;
	status = b1 . Search ( "Smith", "Oak road", 1, phone );			// status = false
	cout << "status = " << status << endl;
	status = b1 . Del ( "Smith", "Oak road" );						// status = true
	cout << "status = " << status << endl;
	status = b1 . Search ( "Smith", "Oak road", 0, phone );			// status = false
	cout << "status = " << status << endl;
	status = b1 . Add ( "Dqrppaibba", "Skwkxiqbba", "" ); //=> r=1, s=0
	cout << "status = " << status << endl;
	
	CPhoneBook  b2;
	
	status = b2 . Add ( "Smith", "Michigan avenue", "9123456" );	// status = true
	cout << "status = " << status << endl;
	status = b2 . Search ( "Smith", "Michigan avenue", 0, phone );	// status = true, phone = "9123456"
	cout << "status = " << status << ", phone = " << phone << endl;
	status = b2 . Search ( "Smith", "Michigan avenue", 1, phone );	// status = false
	cout << "status = " << status << endl;
	status = b2 . Del ( "Smith", "Michigan avenue" );				// status = true
	cout << "status = " << status << endl;
	status = b2 . Search ( "Smith", "Michigan avenue", 0, phone );	// status = false
	cout << "status = " << status << endl;
	status = b2 . Del ( "Smith", "Michigan avenue" );				// status = false
	cout << "status = " << status << endl;
	status = b2 . Add ( "Smith", "Michigan avenue", "9123456" );	// status = true
	cout << "status = " << status << endl;
	status = b2 . Search ( "Smith", "Michigan avenue", 0, phone );	// status = true, phone = "9123456"
	cout << "status = " << status << ", phone = " << phone << endl;
	status = b2 . Search ( "Smith", "Michigan avenue", 1, phone );	// status = false
	cout << "status = " << status << endl;
	status = b2 . Add ( "Smith", "Michigan avenue", "9123456" );	// status = false
	cout << "status = " << status << endl;
	status = b2 . Add ( "Smith", "Michigan avenue", "10293847" );	// status = true
	cout << "status = " << status << endl;
	status = b2 . Del ( "Smith", "Michigan avenue" );				// status = true
	cout << "status = " << status << endl;
	status = b2 . Search ( "Smith", "Michigan avenue", 0, phone );	// status = false
	cout << "status = " << status << endl;

	CPhoneBook  b3;
	
	status = b3 . Add ( "Smith", "Michigan avenue", "1234" );		// status = true
	cout << "status = " << status << endl;
	status = b3 . Add ( "Smith", "Michigan avenue", "2233" );		// status = true
	cout << "status = " << status << endl;
	status = b3 . Add ( "Smith", "Michigan avenue", "3344" );		// status = true
	cout << "status = " << status << endl;
	status = b3 . Add ( "Brown", "Oak road", "5678" );				// status = true
	cout << "status = " << status << endl;
	status = b3 . Add ( "Brown", "Oak road", "6677" );				// status = true
	cout << "status = " << status << endl;
	status = b3 . Search ( "Smith", "Michigan avenue", 0, phone );	// status = true, phone = "1234"
	cout << "status = " << status << ", phone = " << phone << endl;
	status = b3 . Search ( "Smith", "Michigan avenue", 1, phone );	// status = true, phone = "2233"
	cout << "status = " << status << ", phone = " << phone << endl;
	status = b3 . Search ( "Smith", "Michigan avenue", 2, phone );	// status = true, phone = "3344"
	cout << "status = " << status << ", phone = " << phone << endl;
	status = b3 . Search ( "Smith", "Michigan avenue", 3, phone );	// status = false
	cout << "status = " << status << endl;
	status = b3 . Search ( "Brown", "Oak road", 0, phone );			// status = true, phone = "5678"
	cout << "status = " << status << ", phone = " << phone << endl;
	status = b3 . Search ( "Brown", "Oak road", 1, phone );			// status = true, phone = "6677"
	cout << "status = " << status << ", phone = " << phone << endl;
	status = b3 . Search ( "Brown", "Oak road", 2, phone );			// status = false
	cout << "status = " << status << endl;
	status = b3 . Search ( "2233", name, addr );					// status = true, name = "Smith", addr = "Michigan avenue"
	cout << "status = " << status << ", name = " << name << ", addr = " << addr << endl;
	status = b3 . Del ( "6677" );									// status = true
	cout << "status = " << status << endl;
	status = b3 . Search ( "Brown", "Oak road", 0, phone );			// status = true, phone = "5678"
	cout << "status = " << status << ", phone = " << phone << endl;
	status = b3 . Search ( "Brown", "Oak road", 1, phone );			// status = false
	cout << "status = " << status << endl;
	status = b3 . Del ( "5678" );									// status = true
	cout << "status = " << status << endl;
	status = b3 . Search ( "Brown", "Oak road", 0, phone );			// status = false
	cout << "status = " << status << endl;
 }
#endif /* __PROGTEST__ */


