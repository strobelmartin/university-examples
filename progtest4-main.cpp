#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;


class InvalidCarException 
 {
   public:
      InvalidCarException ( const string & rz ) :
        m_RZ ( rz ) {}
    friend ostream & operator << ( ostream & os, const InvalidCarException & e ) 
     { return os << e . m_RZ; }
   private:
    string m_RZ;
 };
 
class InvalidDriverException 
 {
   public:
      InvalidDriverException ( const string & name, const string & surname ) : 
        m_Name ( name ), m_Surname ( surname ) {}
    friend ostream & operator << ( ostream & os, const InvalidDriverException & e ) 
     { return os << e . m_Name << ' ' << e . m_Surname; }
   private:
    string m_Name;
    string m_Surname;
 };

class CTester;
#endif /* __PROGTEST__ */


class CDriver;
class CCar;
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class CDriver
 {
   public:
                     CDriver      ( const string    & name,
                                    const string    & surname );
                   ~ CDriver      ( void );
                     CDriver      ( const CDriver   & src );
    CDriver        & operator =   ( const CDriver   & src );
    friend ostream & operator <<  ( ostream         & os,
                                    const CDriver   & src );
    friend ostream & operator <<  ( ostream         & os,
                                    const CCar      & src );
    void             SortLog      ( void );
    const string   & GetName      ( void ) const;
    const string   & GetSurname   ( void ) const;
    int              GetLogNr     ( void ) const;
    const string   & GetLogDate   ( int LogNr ) const;
    CCar           * GetLogCar    ( int LogNr ) const;
    void             SetLogDate   ( int LogNr, const string & date );
    void             SetLogCar    ( int LogNr, CCar * car );
    void             SetLogNr     ( int val );
    friend class ::CTester;
    
   protected:
    struct TLog
     {
       string        m_Date;
       CCar        * m_Car;
     };
    string           m_Name;
    string           m_Surname;
    TLog           * m_Log;
    int              m_LogNr;
    int              m_LogSize;
 };
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class CCar 
 {
   public:
                     CCar         ( const string    & RZ );
                   ~ CCar         ( void );
                     CCar         ( const CCar      & src );
    CCar           & operator =   ( const CCar      & src );
    friend ostream & operator <<  ( ostream         & os,
                                    const CCar      & src );
    friend ostream & operator <<  ( ostream         & os,
                                    const CDriver   & src );
    void             SortLog      ( void );
    const string   & GetRZ        ( void ) const;
    int              GetLogNr     ( void ) const;
    const string   & GetLogDate   ( int LogNr ) const;
    CDriver        * GetLogDriver ( int LogNr ) const;
    void             SetLogDate   ( int LogNr, const string & date );
    void             SetLogDriver ( int LogNr, CDriver * driver );
    void             SetLogNr     ( int val );
    friend class ::CTester;
    
   protected:
    struct TLog
     {
       string        m_Date;
       CDriver     * m_Driver;
     };
    string           m_RZ;
    TLog           * m_Log;
    int              m_LogNr;
    int              m_LogSize;
 }; 
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class CDatabase
 {
   public:
                     CDatabase    ( void );
                   ~ CDatabase    ( void );
                     CDatabase    ( const CDatabase & src );
    CDatabase      & operator =   ( const CDatabase & src );
    bool             Add          ( const string    & date, 
                                    const string    & name, 
                                    const string    & surname, 
                                    const string    & RZ );
    const CCar     & FindCar      ( const string    & RZ ) const;
          CCar     * FindLogCar   ( const string    & RZ ) const;
    const CDriver  & FindDriver   ( const string    & name, 
                                    const string    & surname ) const;
          CDriver  * FindLogDriver( const string    & name, 
                                    const string    & surname ) const;
    friend ostream & operator <<  ( ostream         & os,
                                    const CDatabase & src );
    friend class ::CTester;
    
   protected:
    CDriver       ** m_Drivers;
    int              m_DriversNr;
    int              m_DriversSize;
    void             SortDrivers  ( void );
    
    CCar          ** m_Cars;
    int              m_CarsNr;
    int              m_CarsSize;
    void             SortCars     ( void );
 }; 
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
                     CDriver :: CDriver      ( const string    & name,
                                               const string    & surname )
 {
   m_Name    = name;
   m_Surname = surname;
   m_Log     = new TLog [ 100 ];
   m_LogNr   = 0;
   m_LogSize = 100;
 }
//--------------------------------------------------------------------------------------------------
                     CDriver :: ~ CDriver    ( void )
 {
   m_Name    . clear ();
   m_Surname . clear ();
   delete [] m_Log;
   m_LogNr   = 0;
   m_LogSize = 0;
 }
//--------------------------------------------------------------------------------------------------
                     CDriver :: CDriver      ( const CDriver   & src )
 {
   m_Name    = src . m_Name;
   m_Surname = src . m_Surname;
   m_Log     = new TLog [ src . m_LogSize ];
   m_LogNr   = src . m_LogNr;
   m_LogSize = src . m_LogSize;
   
   for ( int i = 0 ; i < m_LogNr ; i ++ )
    {
      m_Log [ i ] . m_Date = src . m_Log [ i ] . m_Date;
      m_Log [ i ] . m_Car  = src . m_Log [ i ] . m_Car;
    }
 }
//--------------------------------------------------------------------------------------------------
    CDriver        & CDriver :: operator =   ( const CDriver   & src )
 {
   if ( this == & src ) return * this;
   
   m_Name    . clear ();
   m_Surname . clear ();
   delete [] m_Log;
   m_LogNr   = 0;
   m_LogSize = 0;
   
   m_Name    = src . m_Name;
   m_Surname = src . m_Surname;
   m_Log     = new TLog [ src . m_LogSize ];
   m_LogNr   = src . m_LogNr;
   m_LogSize = src . m_LogSize;
   
   for ( int i = 0 ; i < m_LogNr ; i ++ )
    {
      m_Log [ i ] . m_Date = src . m_Log [ i ] . m_Date;
      m_Log [ i ] . m_Car  = src . m_Log [ i ] . m_Car;
    }
   
   return * this;
 }
//--------------------------------------------------------------------------------------------------
           ostream &            operator <<  ( ostream         & os,
                                               const CDriver   & src )
 {
   os << src . m_Name << " " << src . m_Surname;
   
   for ( int i = 0 ; i < src . m_LogNr ; i ++ )
    {
      os << endl << "   ";
      os << src . m_Log [ i ] . m_Date << ": " << src . m_Log [ i ] . m_Car -> m_RZ;
    }
   
   os << endl;
   
   return os;
 }
//--------------------------------------------------------------------------------------------------
    void             CDriver :: SortLog      ( void )
 {
   int       i, j, minIdx;
   TLog      tmpLog;
   
   for ( i = 0 ; i < m_LogNr - 1 ; i ++ )
    {
      minIdx = i;
      
      for ( j = i + 1 ; j < m_LogNr ; j ++ )
         if ( m_Log [ j ] . m_Date <  m_Log [ minIdx ] . m_Date )
            minIdx = j;

      tmpLog . m_Date = m_Log [ minIdx ] . m_Date;
      tmpLog . m_Car  = m_Log [ minIdx ] . m_Car;
      
      m_Log [ minIdx ] . m_Date = m_Log [ i ] . m_Date;
      m_Log [ minIdx ] . m_Car  = m_Log [ i ] . m_Car;
      
      m_Log [ i ] . m_Date = tmpLog . m_Date;
      m_Log [ i ] . m_Car  = tmpLog . m_Car;
    }
 }
//--------------------------------------------------------------------------------------------------
    const string   & CDriver :: GetName      ( void ) const
 {
   return m_Name;
 }
//--------------------------------------------------------------------------------------------------
    const string   & CDriver :: GetSurname   ( void ) const
 {
   return m_Surname;
 }
//--------------------------------------------------------------------------------------------------
    int              CDriver :: GetLogNr     ( void ) const
 {
   return m_LogNr;
 }
//--------------------------------------------------------------------------------------------------
    const string   & CDriver :: GetLogDate   ( int LogNr ) const
 {
   return m_Log [ LogNr ] . m_Date;
 }
//-------------------------------------------------------------------------------------------------- 
    CCar           * CDriver :: GetLogCar    ( int LogNr ) const
 {
   return m_Log [ LogNr ] . m_Car;
 }
//-------------------------------------------------------------------------------------------------- 
    void             CDriver :: SetLogDate   ( int LogNr, const string & date )
 {
   m_Log [ LogNr ] . m_Date = date;
 }
//--------------------------------------------------------------------------------------------------    
    void             CDriver :: SetLogCar    ( int LogNr, CCar * car )
 {
   m_Log [ LogNr ] . m_Car = car;
 }
//-------------------------------------------------------------------------------------------------- 
    void             CDriver :: SetLogNr     ( int val )
 {
   m_LogNr = val;
 }
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
                     CCar    :: CCar         ( const string    & RZ )
 {
   m_RZ      = RZ;
   m_Log     = new TLog [ 100 ];
   m_LogNr   = 0;
   m_LogSize = 100;
 }
//--------------------------------------------------------------------------------------------------
                     CCar    :: ~ CCar       ( void )
 {
   m_RZ      . clear ();
   delete [] m_Log;
   m_LogNr   = 0;
   m_LogSize = 0;
 }
//--------------------------------------------------------------------------------------------------
                     CCar    :: CCar         ( const CCar      & src )
 {
   m_RZ      = src . m_RZ;
   m_Log     = new TLog [ src . m_LogSize ];
   m_LogNr   = src . m_LogNr;
   m_LogSize = src . m_LogSize;
   
   for ( int i = 0 ; i < m_LogNr ; i ++ )
    {
      m_Log [ i ] . m_Date   = src . m_Log [ i ] . m_Date;
      m_Log [ i ] . m_Driver = src . m_Log [ i ] . m_Driver;
    }
 }
//--------------------------------------------------------------------------------------------------
    CCar           & CCar    :: operator =   ( const CCar      & src )
 {
   if ( this == & src ) return * this;
   
   m_RZ      . clear ();
   delete [] m_Log;
   m_LogNr   = 0;
   m_LogSize = 0;
   
   m_RZ      = src . m_RZ;
   m_Log     = new TLog [ src . m_LogSize ];
   m_LogNr   = src . m_LogNr;
   m_LogSize = src . m_LogSize;
   
   for ( int i = 0 ; i < m_LogNr ; i ++ )
    {
      m_Log [ i ] . m_Date   = src . m_Log [ i ] . m_Date;
      m_Log [ i ] . m_Driver = src . m_Log [ i ] . m_Driver;
    }
   
   return * this;
 }
//--------------------------------------------------------------------------------------------------
           ostream &            operator <<  ( ostream         & os,
                                               const CCar      & src )
 {
   os << src . m_RZ;
   
   for ( int i = 0 ; i < src . m_LogNr ; i ++ )
    {
      os << endl << "   ";
      os << src . m_Log [ i ] . m_Date << ": " << src . m_Log [ i ] . m_Driver -> m_Name << " "
                                               << src . m_Log [ i ] . m_Driver -> m_Surname;
    }
   
   os << endl;
    
   return os;
 }
//--------------------------------------------------------------------------------------------------
    void             CCar    :: SortLog      ( void )
 {
   int       i, j, minIdx;
   TLog      tmpLog;
   
   for ( i = 0 ; i < m_LogNr - 1 ; i ++ )
    {
      minIdx = i;
      
      for ( j = i + 1 ; j < m_LogNr ; j ++ )
         if ( m_Log [ j ] . m_Date <  m_Log [ minIdx ] . m_Date )
            minIdx = j;

      tmpLog . m_Date   = m_Log [ minIdx ] . m_Date;
      tmpLog . m_Driver = m_Log [ minIdx ] . m_Driver;
      
      m_Log [ minIdx ] . m_Date   = m_Log [ i ] . m_Date;
      m_Log [ minIdx ] . m_Driver = m_Log [ i ] . m_Driver;
      
      m_Log [ i ] . m_Date   = tmpLog . m_Date;
      m_Log [ i ] . m_Driver = tmpLog . m_Driver;
    }
 }
//--------------------------------------------------------------------------------------------------
    const string   & CCar    :: GetRZ        ( void ) const
 {
   return m_RZ;
 }
//--------------------------------------------------------------------------------------------------
    int              CCar    :: GetLogNr     ( void ) const
 {
   return m_LogNr;
 }
//--------------------------------------------------------------------------------------------------
    const string   & CCar    :: GetLogDate   ( int LogNr ) const
 {
   return m_Log [ LogNr ] . m_Date;
 }
//-------------------------------------------------------------------------------------------------- 
    CDriver        * CCar    :: GetLogDriver ( int LogNr ) const
 {
   return m_Log [ LogNr ] . m_Driver;
 }
//-------------------------------------------------------------------------------------------------- 
    void             CCar    :: SetLogDate   ( int LogNr, const string & date )
 {
   m_Log [ LogNr ] . m_Date = date;
 }
//--------------------------------------------------------------------------------------------------    
    void             CCar    :: SetLogDriver ( int LogNr, CDriver * driver )
 {
   m_Log [ LogNr ] . m_Driver = driver;
 }
//-------------------------------------------------------------------------------------------------- 
    void             CCar    :: SetLogNr     ( int val )
 {
   m_LogNr = val;
 }
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
                     CDatabase :: CDatabase    ( void )
 {
   m_Drivers     = new CDriver* [ 100 ];
   m_DriversNr   = 0;
   m_DriversSize = 100;
   
   m_Cars        = new CCar* [ 100 ];
   m_CarsNr      = 0;
   m_CarsSize    = 100;
 }
//--------------------------------------------------------------------------------------------------
                     CDatabase :: ~ CDatabase  ( void )
 {
   int i;
   
   for ( i = 0 ; i < m_DriversNr ; i ++ )
      delete m_Drivers [ i ];
   delete [] m_Drivers;
   m_DriversNr   = 0;
   m_DriversSize = 0;
   
   for ( i = 0 ; i < m_CarsNr ; i ++ )
      delete m_Cars [ i ];
   delete [] m_Cars;
   m_CarsNr      = 0;
   m_CarsSize    = 0;
 }
//--------------------------------------------------------------------------------------------------
                     CDatabase :: CDatabase    ( const CDatabase & src )
 {
   m_Drivers     = new CDriver* [ src . m_DriversSize ];
   m_DriversNr   = src . m_DriversNr;
   m_DriversSize = src . m_DriversSize;
   
   m_Cars        = new CCar* [ src . m_CarsSize ];
   m_CarsNr      = src . m_CarsNr;
   m_CarsSize    = src . m_CarsSize;
   
   int i, j;
   
   for ( i = 0 ; i < m_DriversNr ; i ++ )
      m_Drivers [ i ] = new CDriver ( * src . m_Drivers [ i ] );

   for ( i = 0 ; i < m_CarsNr ; i ++ )
      m_Cars    [ i ] = new CCar    ( * src . m_Cars [ i ] );
      
   for ( i = 0 ; i < m_DriversNr ; i ++ )
      for ( j = 0 ; j < m_Drivers [ i ] -> GetLogNr () ; j ++ )
         m_Drivers [ i ] -> SetLogCar ( j, this -> FindLogCar ( m_Drivers [ i ] -> GetLogCar ( j ) -> GetRZ () ) );

   for ( i = 0 ; i < m_CarsNr ; i ++ )
      for ( j = 0 ; j < m_Cars [ i ] -> GetLogNr () ; j ++ )
         m_Cars [ i ] -> SetLogDriver ( j, this -> FindLogDriver ( m_Cars [ i ] -> GetLogDriver ( j ) -> GetName (),
                                                                   m_Cars [ i ] -> GetLogDriver ( j ) -> GetSurname () ) );
 }
//--------------------------------------------------------------------------------------------------
    CDatabase      & CDatabase :: operator =   ( const CDatabase & src )
 {
   if ( this == & src ) return * this;
   
   int i, j;
   
   for ( i = 0 ; i < m_DriversNr ; i ++ )
      delete m_Drivers [ i ];
   delete [] m_Drivers;
   m_DriversNr   = 0;
   m_DriversSize = 0;
   
   for ( i = 0 ; i < m_CarsNr ; i ++ )
      delete m_Cars [ i ];
   delete [] m_Cars;
   m_CarsNr      = 0;
   m_CarsSize    = 0;

   m_Drivers     = new CDriver* [ src . m_DriversSize ];
   m_DriversNr   = src . m_DriversNr;
   m_DriversSize = src . m_DriversSize;
   
   m_Cars        = new CCar* [ src . m_CarsSize ];
   m_CarsNr      = src . m_CarsNr;
   m_CarsSize    = src . m_CarsSize;
   
   for ( i = 0 ; i < m_DriversNr ; i ++ )
      m_Drivers [ i ] = new CDriver ( * src . m_Drivers [ i ] );

   for ( i = 0 ; i < m_CarsNr ; i ++ )
      m_Cars    [ i ] = new CCar    ( * src . m_Cars [ i ] );
      
   for ( i = 0 ; i < m_DriversNr ; i ++ )
      for ( j = 0 ; j < m_Drivers [ i ] -> GetLogNr () ; j ++ )
         m_Drivers [ i ] -> SetLogCar ( j, this -> FindLogCar ( m_Drivers [ i ] -> GetLogCar ( j ) -> GetRZ () ) );

   for ( i = 0 ; i < m_CarsNr ; i ++ )
      for ( j = 0 ; j < m_Cars [ i ] -> GetLogNr () ; j ++ )
         m_Cars [ i ] -> SetLogDriver ( j, this -> FindLogDriver ( m_Cars [ i ] -> GetLogDriver ( j ) -> GetName (),
                                                                   m_Cars [ i ] -> GetLogDriver ( j ) -> GetSurname () ) );
   return * this;
 }
//--------------------------------------------------------------------------------------------------
    bool             CDatabase :: Add          ( const string    & date, 
                                                 const string    & name, 
                                                 const string    & surname, 
                                                 const string    & RZ )
 {
   int d, dLog, c, cLog;
   
   // testovani, zda uz dany ridic v dany den neridil jiny automobil
   for ( d = 0 ; d < m_DriversNr ; d ++ )
      if ( m_Drivers [ d ] -> GetName () == name && m_Drivers [ d ] -> GetSurname () == surname )
       {
         for ( dLog = 0 ; dLog < m_Drivers [ d ] -> GetLogNr () ; dLog ++ )
            if ( m_Drivers [ d ] -> GetLogDate ( dLog ) == date )
               return false;
         break;
       }

	// testovani, zda uz dany automobil v dany den nebyl pouzivan jinym ridicem
   for ( c = 0 ; c < m_CarsNr ; c ++ )
      if ( m_Cars [ c ] -> GetRZ () == RZ )
       {
         for ( cLog = 0 ; cLog < m_Cars [ c ] -> GetLogNr () ; cLog ++ )
            if ( m_Cars [ c ] -> GetLogDate ( cLog ) == date )
               return false;
         break;
       }
  
	// dany ridic jeste neni v evidenci - zaradit na misto podle abecedy
   if ( d == m_DriversNr )
    {
      m_Drivers [ d ] = new CDriver ( name, surname );
      m_DriversNr ++;
    }

	// dany automobil jeste neni v evidenci - zaradit na misto podle abecedy
   if ( c == m_CarsNr )
    {
      m_Cars [ c ] = new CCar ( RZ );
      m_CarsNr ++;
    }

   // vlozeni zaznamu do logu ridice
   m_Drivers [ d ] -> SetLogDate   ( m_Drivers [ d ] -> GetLogNr (), date );
   m_Drivers [ d ] -> SetLogCar    ( m_Drivers [ d ] -> GetLogNr (), m_Cars [ c ] );
   m_Drivers [ d ] -> SetLogNr     ( m_Drivers [ d ] -> GetLogNr () + 1 );
   m_Drivers [ d ] -> SortLog      ();

   // vlozeni zaznamu do logu automobilu   
   m_Cars    [ c ] -> SetLogDate   ( m_Cars [ c ] -> GetLogNr (), date );
   m_Cars    [ c ] -> SetLogDriver ( m_Cars [ c ] -> GetLogNr (), m_Drivers [ d ] );
   m_Cars    [ c ] -> SetLogNr     ( m_Cars [ c ] -> GetLogNr () + 1 );
   m_Cars    [ c ] -> SortLog      ();
   
   SortDrivers ();
   SortCars    ();
   
   return true;
 }
//--------------------------------------------------------------------------------------------------
    const CCar     & CDatabase :: FindCar      ( const string    & RZ ) const
 {
   for ( int i = 0 ; i < m_CarsNr ; i ++ )
      if ( m_Cars [ i ] -> GetRZ () == RZ )
         return * m_Cars [ i ];

   throw InvalidCarException ( RZ );
 }
//--------------------------------------------------------------------------------------------------
          CCar     * CDatabase :: FindLogCar   ( const string    & RZ ) const
 {
   for ( int i = 0 ; i < m_CarsNr ; i ++ )
      if ( m_Cars [ i ] -> GetRZ () == RZ )
         return m_Cars [ i ];
         
   throw InvalidCarException ( RZ );
 }
//--------------------------------------------------------------------------------------------------
    const CDriver  & CDatabase :: FindDriver   ( const string    & name, 
                                                 const string    & surname ) const
 {
   for ( int i = 0 ; i < m_DriversNr ; i ++ )
      if ( m_Drivers [ i ] -> GetName () == name && m_Drivers [ i ] -> GetSurname () == surname )
         return * m_Drivers [ i ];

   throw InvalidDriverException ( name, surname );
 }
//--------------------------------------------------------------------------------------------------
          CDriver  * CDatabase :: FindLogDriver( const string    & name, 
                                                 const string    & surname ) const
 {
   for ( int i = 0 ; i < m_DriversNr ; i ++ )
      if ( m_Drivers [ i ] -> GetName () == name && m_Drivers [ i ] -> GetSurname () == surname )
         return m_Drivers [ i ];

   throw InvalidDriverException ( name, surname );
 }
//--------------------------------------------------------------------------------------------------
           ostream &              operator <<  ( ostream         & os,
                                                 const CDatabase & src )
 {
   int i, j;
   
   os << "Drivers:";
   for ( i = 0 ; i < src . m_DriversNr ; i ++ )
    {
      os << endl <<  "   " << src . m_Drivers [ i ] -> GetName () << " "
                           << src . m_Drivers [ i ] -> GetSurname ();
   
      for ( j = 0 ; j < src . m_Drivers [ i ] -> GetLogNr () ; j ++ )
       {
         os << endl << "      ";
         os << src . m_Drivers [ i ] -> GetLogDate ( j ) << ": "
            << src . m_Drivers [ i ] -> GetLogCar  ( j ) -> GetRZ ();
       }
    }
   
   os << endl << "Cars:";
   for ( i = 0 ; i < src . m_CarsNr ; i ++ )
    {
      os << endl << "   " << src . m_Cars [ i ] -> GetRZ ();
   
      for ( j = 0 ; j < src . m_Cars [ i ] -> GetLogNr () ; j ++ )
       {
         os << endl << "      ";
         os << src . m_Cars [ i ] -> GetLogDate   ( j ) << ": "
            << src . m_Cars [ i ] -> GetLogDriver ( j ) -> GetName () << " "
            << src . m_Cars [ i ] -> GetLogDriver ( j ) -> GetSurname ();
       }
    }
   
   os << endl;
   
   return os;
 }
//--------------------------------------------------------------------------------------------------
    void             CDatabase :: SortDrivers  ( void )
 {
   int       i, j, minIdx;
   
   for ( i = 0 ; i < m_DriversNr - 1 ; i ++ )
    {
      minIdx = i;
      
      for ( j = i + 1 ; j < m_DriversNr ; j ++ )
         if (
                 ( m_Drivers [ j ] -> GetSurname () <  m_Drivers [ minIdx ] -> GetSurname () )
              || ( m_Drivers [ j ] -> GetSurname () == m_Drivers [ minIdx ] -> GetSurname () &&
                   m_Drivers [ j ] -> GetName ()    <  m_Drivers [ minIdx ] -> GetName () )
            )
               minIdx = j;

      CDriver * tmpDriver  = m_Drivers [ minIdx ];
      m_Drivers [ minIdx ] = m_Drivers [ i ];
      m_Drivers [ i ]      = tmpDriver;
    }
 }
//--------------------------------------------------------------------------------------------------
    void             CDatabase :: SortCars     ( void )
 {
   int       i, j, minIdx;
   
   for ( i = 0 ; i < m_CarsNr - 1 ; i ++ )
    {
      minIdx = i;
      
      for ( j = i + 1 ; j < m_CarsNr ; j ++ )
         if ( m_Cars [ j ] -> GetRZ () <  m_Cars [ minIdx ] -> GetRZ () )
            minIdx = j;

      CCar * tmpCar     = m_Cars [ minIdx ];
      m_Cars [ minIdx ] = m_Cars [ i ];
      m_Cars [ i ]      = tmpCar;
    }
 }
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
    int              main                      ( int argc, char * argv [] )
 {
	CDatabase    * a, * b, *c;
	bool          st;

	a = new CDatabase;
	st = a -> Add ( "2012-03-01", "John", "Nowak", "ABC-12-34" ); // st = true
	cout << "st = " << st << endl;
	st = a -> Add ( "2012-03-02", "John", "Nowak", "ABC-12-34" ); // st = true
	cout << "st = " << st << endl;
	st = a -> Add ( "2012-03-03", "John", "Nowak", "DEF-56-67" ); // st = true
	cout << "st = " << st << endl;
	st = a -> Add ( "2012-03-02", "George", "Smith", "DEF-56-67" ); // st = true
	cout << "st = " << st << endl;
	
	cout << *a;	
	/*
	Drivers:
		John Nowak
		   2012-03-01: ABC-12-34
		   2012-03-02: ABC-12-34
		   2012-03-03: DEF-56-67
		George Smith
		   2012-03-02: DEF-56-67
	Cars:
		ABC-12-34
		   2012-03-01: John Nowak
		   2012-03-02: John Nowak
		DEF-56-67
		   2012-03-02: George Smith
		   2012-03-03: John Nowak
	*/
	cout << "-------------------------------------" << endl;
	
	cout << a -> FindCar ( "ABC-12-34" );
	/*
	ABC-12-34
		2012-03-01: John Nowak
		2012-03-02: John Nowak
	*/
	cout << "-------------------------------------" << endl;
	
	cout << a -> FindDriver ( "John", "Nowak" );
	/*
	John Nowak
		2012-03-01: ABC-12-34
		2012-03-02: ABC-12-34
		2012-03-03: DEF-56-67
	*/
	cout << "-------------------------------------" << endl;
	
//	cout << a -> FindCar ( "XYZ-99-88" ) << endl;
	// InvalidCarException thrown, cout << e => "XYZ-99-88"
//	cout << "-------------------------------------" << endl;
	
//	cout << a -> FindDriver ( "John", "Smith" ) << endl;
	// InvalidDriverException thrown, cout << e => "John Smith"
//	cout << "-------------------------------------" << endl;
	
	delete a;

	a = new CDatabase;
	st = a -> Add ( "2012-03-01", "John", "Nowak", "ABC-12-34" ); // st = true
	cout << "st = " << st << endl;
	st = a -> Add ( "2012-03-02", "George", "Smith", "DEF-56-67" ); // st = true
	cout << "st = " << st << endl;
	
	cout << *a;
	/*
	Drivers:
		John Nowak
		   2012-03-01: ABC-12-34
		George Smith
		   2012-03-02: DEF-56-67
	Cars:
		ABC-12-34
		   2012-03-01: John Nowak
		DEF-56-67
		   2012-03-02: George Smith
	*/
	cout << "-------------------------------------" << endl;
	
	st = a -> Add ( "2012-03-01", "John", "Nowak", "XYZ-99-99" ); // st = false
	cout << "st = " << st << endl;
	st = a -> Add ( "2012-03-02", "Peter", "McDonald", "DEF-56-67" ); // st = false
	cout << "st = " << st << endl;
	
	cout << *a;
	/*
	Drivers:
		John Nowak
		   2012-03-01: ABC-12-34
		George Smith
		   2012-03-02: DEF-56-67
	Cars:
		ABC-12-34
		   2012-03-01: John Nowak
		DEF-56-67
		   2012-03-02: George Smith
	*/
	cout << "-------------------------------------" << endl;
	
	delete a;

	a = new CDatabase;
	b = new CDatabase;
	st = a -> Add ( "2012-03-01", "John", "Nowak", "ABC-12-34" ); // st = true
	cout << "st = " << st << endl;
	st = a -> Add ( "2012-03-02", "John", "Nowak", "DEF-56-67" ); // st = true
	cout << "st = " << st << endl;
	st = a -> Add ( "2012-03-01", "George", "Smith", "DEF-56-67" ); // st = true
	cout << "st = " << st << endl;
	st = a -> Add ( "2012-03-02", "George", "Smith", "ABC-12-34" ); // st = true
	cout << "st = " << st << endl;
	
	cout << *a;
	/*
	Drivers:
		John Nowak
		   2012-03-01: ABC-12-34
		   2012-03-02: DEF-56-67
		George Smith
		   2012-03-01: DEF-56-67
		   2012-03-02: ABC-12-34
	Cars:
		ABC-12-34
		   2012-03-01: John Nowak
		   2012-03-02: George Smith
		DEF-56-67
		   2012-03-01: George Smith
		   2012-03-02: John Nowak
	*/
	cout << "-------------------------------------" << endl;
	
	*b = *a;
	c = new CDatabase ( *a );
	st = b -> Add ( "2012-03-03", "Homer", "Simpson", "ABC-12-34" ); // st = true
	cout << "st = " << st << endl;
	st = c -> Add ( "2012-03-03", "Homer", "Simpson", "DEF-56-67" ); // st = true
	cout << "st = " << st << endl;
	
	delete a;
	
	cout << *b;
	/*
	Drivers:
		John Nowak
		   2012-03-01: ABC-12-34
		   2012-03-02: DEF-56-67
		Homer Simpson
		   2012-03-03: ABC-12-34
		George Smith
		   2012-03-01: DEF-56-67
		   2012-03-02: ABC-12-34
	Cars:
		ABC-12-34
		   2012-03-01: John Nowak
		   2012-03-02: George Smith
		   2012-03-03: Homer Simpson
		DEF-56-67
		   2012-03-01: George Smith
		   2012-03-02: John Nowak
	*/

	
	cout << *c;
	/*
	Drivers:
		John Nowak
		   2012-03-01: ABC-12-34
		   2012-03-02: DEF-56-67
		Homer Simpson
		   2012-03-03: DEF-56-67
		George Smith
		   2012-03-01: DEF-56-67
		   2012-03-02: ABC-12-34
	Cars:
		ABC-12-34
		   2012-03-01: John Nowak
		   2012-03-02: George Smith
		DEF-56-67
		   2012-03-01: George Smith
		   2012-03-02: John Nowak
		   2012-03-03: Homer Simpson
	*/
	
	delete b;
	delete c;
   
   return 0;
 }
#endif /* __PROGTEST__ */


