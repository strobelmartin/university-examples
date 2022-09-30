#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;


class InvalidIndexException
 {
   public:
    InvalidIndexException ( int idx ) 
     { m_Idx = idx; }
    friend ostream & operator << ( ostream & os, 
                                             const InvalidIndexException & x )
     { return os << x . m_Idx; }
   private:
    int m_Idx;
 };

#endif /* __PROGTEST__ */
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
template <class T>
class CSparseArray
 {
   public:
                                               CSparseArray ( void );
                                             ~ CSparseArray ( void );
                                               CSparseArray ( const CSparseArray<T> & src );
    CSparseArray<T>                          & operator =   ( const CSparseArray<T> & src );
    bool                                       operator ==  ( const CSparseArray<T> & cmp ) const;
    bool                                       operator !=  ( const CSparseArray<T> & cmp ) const;
    T                                        & operator []  ( int idx ) const;
    template <class X>
    friend ostream                           & operator <<  ( ostream               & os,
                                                              const CSparseArray<X> & src );
    CSparseArray<T>                          & Set          ( int idx, const T & val );
    CSparseArray<T>                          & Unset        ( int idx );
    bool                                       IsSet        ( int idx ) const;
    int                                        Size         ( void ) const;

   protected:
    struct TElem
     {
                      TElem        ( int idx, const T & val ) : m_Val ( val )
                                   { m_Next = NULL; m_Idx = idx; }
       TElem        * m_Next;
       int            m_Idx;
       T              m_Val;
     };
    TElem           * m_First;
    TElem           * m_Last;
    int               m_Cnt;
    bool              Compare      ( const TElem * x,
                                     const TElem * y  ) const;
    ostream         & Print        ( ostream     & os ) const;
    void              Sort         ( void );
 };
//--------------------------------------------------------------------------------------------------
template <class T>
                               CSparseArray<T>    :: CSparseArray   ( void )
 {
   m_First = m_Last = NULL;
   m_Cnt = 0;
 }
//--------------------------------------------------------------------------------------------------
template <class T>
                               CSparseArray<T>    :: ~ CSparseArray ( void )
 {
   TElem * del;
   
   while ( m_First != NULL )
    {
      del = m_First;
      m_First = m_First -> m_Next;
      delete del;
    }
 }
//--------------------------------------------------------------------------------------------------
template <class T>
                               CSparseArray<T>    :: CSparseArray   ( const CSparseArray<T> & src )
 {
   TElem    * curr = NULL;
   TElem    * next = NULL;

   if( src . m_First == NULL )
    {
      m_First = m_Last = NULL;
      m_Cnt = 0;
    }
   else
    {
      m_First = new TElem    ( src . m_First -> m_Idx, src. m_First -> m_Val );
      
      curr = m_First;
      next = src . m_First -> m_Next;
    }

   while ( next )
    { 
      curr -> m_Next = new TElem    ( next -> m_Idx, next -> m_Val );
      curr = curr -> m_Next;
      next = next -> m_Next;
    }
   
   curr -> m_Next = NULL;
   m_Last = curr;   
   m_Cnt = src . m_Cnt;
 }
//--------------------------------------------------------------------------------------------------
template <class T>
    CSparseArray<T>            & CSparseArray<T>    :: operator =   ( const CSparseArray<T> & src )
 {
   if ( this == & src ) return * this;
   
   while ( m_First != NULL )
    {
      TElem    * del = m_First;
      m_First = m_First -> m_Next;
      delete del;
    }

   TElem    * curr = NULL;
   TElem    * next = NULL;

   if( src . m_First == NULL )
    {
      m_First = m_Last = NULL;
      m_Cnt = 0;
    }
   else
    {
      m_First = new TElem    ( src . m_First -> m_Idx, src. m_First -> m_Val );
      
      curr = m_First;
      next = src . m_First -> m_Next;
    }

   while ( next )
    { 
      curr -> m_Next = new TElem    ( next -> m_Idx, next -> m_Val );
      curr = curr -> m_Next;
      next = next -> m_Next;
    }
   
   curr -> m_Next = NULL;
   m_Last = curr;
   m_Cnt = src . m_Cnt;
   
   return * this;
 }
//--------------------------------------------------------------------------------------------------
template <class T>
    bool                       CSparseArray<T>    :: operator ==    ( const CSparseArray<T> & cmp ) const
 {
   return Compare ( m_First, cmp . m_First );
 }
//--------------------------------------------------------------------------------------------------
template <class T>
    bool                       CSparseArray<T>    :: operator !=    ( const CSparseArray<T> & cmp ) const
 {
   return ! Compare ( m_First, cmp . m_First );
 }
//--------------------------------------------------------------------------------------------------
template <class T>
    T                        & CSparseArray<T>    :: operator []    ( int idx ) const
 {
   TElem    * curr = m_First;
   
   while ( curr )
    {
      if ( curr -> m_Idx == idx )
         return curr -> m_Val;
      else curr = curr -> m_Next;
    }
   
   throw InvalidIndexException ( idx );
 }
//--------------------------------------------------------------------------------------------------
template <class X>
    ostream                                        & operator <<    ( ostream               & os,
                                                                      const CSparseArray<X> & src )
 {
   return src . Print ( os );
 }
//--------------------------------------------------------------------------------------------------
template <class T>
    CSparseArray<T>          & CSparseArray<T>    :: Set            ( int idx, const T & val )
 {
   TElem    * curr = m_First;
   TElem    * newElem;
   
   while ( curr )
    {
      if ( curr -> m_Idx == idx )
       {
         curr -> m_Val = val;         
         return * this;
       }
      else
       {
         curr = curr -> m_Next;
       }
    }
   
   if ( m_Cnt == 0 )
    {
      newElem = new TElem ( idx, val );
      m_First = newElem;
      m_Last  = newElem;
      m_Cnt ++;
    }
   else
    {
      newElem = new TElem ( idx, val );
      m_Last -> m_Next = newElem;
      m_Last = newElem;
      Sort ();   
      m_Cnt ++;
    }
    
   return * this;
 }
//--------------------------------------------------------------------------------------------------
template <class T>
    CSparseArray<T>             & CSparseArray<T>    :: Unset          ( int idx )
 {
   TElem    * prev = NULL;
   TElem    * curr = m_First;
   
   while ( curr )
    {
      if ( curr -> m_Idx == idx )
       {
         if ( ! prev && ! curr -> m_Next )
            m_First = m_Last = NULL;
         else if ( ! prev )
            m_First = curr -> m_Next;
         else if ( ! curr -> m_Next )
          {
            prev -> m_Next = NULL;
            m_Last = prev;
          }
         else
            prev -> m_Next = curr -> m_Next;
         
         delete curr;
         m_Cnt --;
         return * this;
       }
      else
       {
         prev = curr;
         curr = curr -> m_Next;
       }
    }
   
   return * this;
 }
//--------------------------------------------------------------------------------------------------
template <class T>
    bool                       CSparseArray<T>    :: IsSet          ( int idx ) const
 {
   TElem    * curr = m_First;
   
   while ( curr )
    {
      if ( curr -> m_Idx == idx )
         return true;
      else curr = curr -> m_Next;
    }
   return false;
 }
//--------------------------------------------------------------------------------------------------
template <class T>
    int                        CSparseArray<T>    :: Size           ( void ) const
 {
   return m_Cnt;
 }
//--------------------------------------------------------------------------------------------------
template <class T>
    bool                       CSparseArray<T>    :: Compare        ( const TElem * x,
                                                                      const TElem * y ) const
 {
   if ( x == NULL && y == NULL )
      return true;
   else if ( x == NULL || y == NULL )
      return false;
   else if ( x -> m_Idx != y -> m_Idx ||
             x -> m_Val != y -> m_Val )
      return false;
   else
      return Compare ( x -> m_Next, y -> m_Next );
 }
//--------------------------------------------------------------------------------------------------
template <class T>
    ostream                  & CSparseArray<T>    :: Print          ( ostream     & os ) const
 {
   TElem    * curr = m_First;
   
   os << "{ ";

   while ( curr != m_Last )
    {
      os << "[" << curr -> m_Idx << "] => " << curr -> m_Val << ", ";
      curr = curr -> m_Next;
    }
      
   if ( curr == m_Last && m_Cnt != 0 )
     os << "[" << curr -> m_Idx << "] => " 
               << curr -> m_Val << " ";

   os << "}";
   return os;
 }
//--------------------------------------------------------------------------------------------------
template <class T>
    void                       CSparseArray<T>    :: Sort           ( void )
 {
   TElem    * fst, * snd, * temp;
   fst = m_First;

   while ( fst )
    {
      snd = fst -> m_Next;

      while ( snd )
       {
         if ( fst -> m_Idx > snd -> m_Idx )
          {
            temp = new TElem    ( fst -> m_Idx, fst -> m_Val );
            fst -> m_Idx = snd  -> m_Idx;
            fst -> m_Val = snd  -> m_Val;
            snd -> m_Idx = temp -> m_Idx;
            snd -> m_Val = temp -> m_Val;
            delete temp;
          }
         snd = snd -> m_Next;
       }
      fst = fst -> m_Next;
    }
 }
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
    int                                           main           ( int argc, char * argv [] )
 {

	bool   status;
	int    size;
	int    tempInt;
	string tempStr;

	CSparseArray<int>  A1;
	A1 . Set ( 100, 20 );
	A1 . Set ( 30000, 80 );
	A1 . Set ( -6000, 120 );
	status = A1 . IsSet ( 0 );	// status = false
	cout << "status = " << status << endl;
	status = A1 . IsSet ( 30000 ); // status = true
	cout << "status = " << status << endl;
	tempInt = A1 [ 30000 ]; // tempInt = 80
	cout << "tempInt = " << tempInt << endl;
	size = A1 . Size (); // size = 3
	cout << "size = " << size << endl;
	cout << A1 << endl; // "{ [-6000] => 120, [100] => 20, [30000] => 80 }"
	A1 . Unset ( 100 );
	size = A1 . Size (); // size = 2
	cout << "size = " << size << endl;
	cout << A1 << endl; // "{ [-6000] => 120, [30000] => 80 }"
	A1 . Set ( 30000, 666 );
	size = A1 . Size (); // size = 2
	cout << "size = " << size << endl;
	cout << A1 << endl; // "{ [-6000] => 120, [30000] => 666 }"
//	tempInt = A1 [ 30001 ];
	// InvalidIndexException thrown, cout << ex => "30001"
   cout << "----------------------------------------------" << endl;
	CSparseArray<int>  A2;
	CSparseArray<int>  B2;
	A2 . Set ( 5000, 20 );
	A2 . Set ( 30000, 80 );
	A2 . Set ( -6000, 120 );
	A2 . Set ( -9999999, 444 );
	B2 . Set ( 30000, 80 );
	B2 . Set ( -6000, 120 );
	B2 . Set ( -9999999, 444 );
	cout << A2 << endl; // "{ [-9999999] => 444, [-6000] => 120, [5000] => 20, [30000] => 80 }"
	cout << B2 << endl; // "{ [-9999999] => 444, [-6000] => 120, [30000] => 80 }"
	cout << (A2 == B2) << endl; // false
	cout << (A2 != B2) << endl; // true
	B2 . Set ( 5000, 20 );
	B2 . Set ( 5000, 20 );
	cout << A2 << endl; // "{ [-9999999] => 444, [-6000] => 120, [5000] => 20, [30000] => 80 }"
	cout << B2 << endl; // "{ [-9999999] => 444, [-6000] => 120, [5000] => 20, [30000] => 80 }"
	cout << (A2 == B2) << endl; // true
	cout << (A2 != B2) << endl; // false
   cout << "----------------------------------------------" << endl;
	CSparseArray<int>  A3;
	A3 . Set ( 100, 0 );
	A3 . Set ( 99, 1 );
	A3 . Set ( 102, 2 ) . Set ( 103, 2 );
	cout << A3 << endl; // "{ [99] => 1, [100] => 0, [102] => 2, [103] => 2 }"
	A3 . Unset ( 103 );
	cout << A3 << endl; // "{ [99] => 1, [100] => 0, [102] => 2 }"
	A3 . Unset ( 99 ) . Unset ( 100 );
	cout << A3 << endl; // "{ [102] => 2 }"
	A3 . Unset ( 102 );
	cout << A3 << endl; // "{ }"
   cout << "----------------------------------------------" << endl;
	CSparseArray<string>  S;
	S . Set ( 25, "first" );
	S . Set ( 36, "third" );
	S . Set ( 30, "second" );
	cout << S << endl; // "{ [25] => first, [30] => second, [36] => third }"

   cout << "----------------------TEST--------------------" << endl;
   A1 = A2;
   A1 . Set ( 1234, 5678 );
   cout << A2 << endl;
   cout << A1 << endl;
   cout << A1 [ 1234 ] << endl;
   
   CSparseArray<int> *x;
   x = new CSparseArray<int>;
   x -> Set ( 1234, 5678 );
   cout << *x << endl;
   delete x;
   cout << "----------------------TEST--------------------" << endl;
   
   return 0;
 }
#endif /* __PROGTEST__ */


