#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;
#endif /* __PROGTEST__ */
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class CControl;
class CButton;
class CInput;
class CLabel;
class CComboBox;
class CPanel;
class CWindow;
//--------------------------------------------------------------------------------------------------
class CControl
 {
   public:
                               CControl                 ( int     id,
                                                          double  x,
                                                          double  y,
                                                          double  w,
                                                          double  h );
    friend  ostream          & operator <<              ( ostream & os, const CControl & src );
    virtual ostream          & Print                    ( ostream & os ) const = 0;
    virtual ostream          & PrintTo                  ( ostream & os, const string & gap = "", bool lastElem = false ) const = 0;
    virtual ostream          & PrintToPanel             ( ostream & os, const string & gap = "", bool lastElem = false ) const = 0;
    virtual CControl         * Clone                    ( void ) const = 0;
    virtual void               Delete                   ( void ) = 0;
    virtual int                GetId                    ( int id = 0 ) const = 0;
    virtual CControl         * PtrToId                  ( int id = 0 ) = 0;
    virtual void               SyncPos                  ( int srcX, int srcY, int srcW, int srcH );

   protected:
    int                        m_Id;
    int                        m_absX;
    double                     m_relX;
    int                        m_absY;
    double                     m_relY;
    int                        m_absW;
    double                     m_relW;
    int                        m_absH;
    double                     m_relH;
 };
//--------------------------------------------------------------------------------------------------
class CButton : public CControl
 {
   public:
                               CButton                  ( int            id,
                                                          double         x,
                                                          double         y,
                                                          double         w,
                                                          double         h,
                                                          const string & title );
    virtual ostream          & Print                    ( ostream & os ) const;
    virtual ostream          & PrintTo                  ( ostream & os, const string & gap = "", bool lastElem = false ) const;
    virtual ostream          & PrintToPanel             ( ostream & os, const string & gap = "", bool lastElem = false ) const;
    virtual CButton          * Clone                    ( void ) const;
    virtual void               Delete                   ( void );
    virtual int                GetId                    ( int id = 0 ) const;
    virtual CButton          * PtrToId                  ( int id = 0 );
           
   protected:
    string                     m_Title;
 };
//--------------------------------------------------------------------------------------------------
class CInput : public CControl
 {
   public:
                               CInput                   ( int            id,
                                                          double         x,
                                                          double         y,
                                                          double         w,
                                                          double         h,
                                                          const string & title );
    virtual ostream          & Print                    ( ostream & os ) const;
    virtual ostream          & PrintTo                  ( ostream & os, const string & gap = "", bool lastElem = false ) const;
    virtual ostream          & PrintToPanel             ( ostream & os, const string & gap = "", bool lastElem = false ) const;
    virtual CInput           * Clone                    ( void ) const;
    virtual void               Delete                   ( void );
    virtual int                GetId                    ( int id = 0 ) const;
    virtual CInput           * PtrToId                  ( int id = 0 );
            void               SetValue                 ( const string & str );
            const string     & GetValue                 ( void ) const;

   protected:
    string                     m_Title;
 };
//--------------------------------------------------------------------------------------------------
class CLabel : public CControl
 {
   public:
                               CLabel                   ( int            id,
                                                          double         x,
                                                          double         y,
                                                          double         w,
                                                          double         h,
                                                          const string & title );
    virtual ostream          & Print                    ( ostream & os ) const;
    virtual ostream          & PrintTo                  ( ostream & os, const string & gap = "", bool lastElem = false ) const;
    virtual ostream          & PrintToPanel             ( ostream & os, const string & gap = "", bool lastElem = false ) const;
    virtual CLabel           * Clone                    ( void ) const;
    virtual void               Delete                   ( void );
    virtual int                GetId                    ( int id = 0 ) const;
    virtual CLabel           * PtrToId                  ( int id = 0 );

   protected:
    string                     m_Title;
 };
//--------------------------------------------------------------------------------------------------
class CComboBox : public CControl
 {
   public:
                               CComboBox                ( int            id,
                                                          double         x,
                                                          double         y,
                                                          double         w,
                                                          double         h );
                             ~ CComboBox                ( void );
    virtual ostream          & Print                    ( ostream & os ) const;
    virtual ostream          & PrintTo                  ( ostream & os, const string & gap = "", bool lastElem = false ) const;
    virtual ostream          & PrintToPanel             ( ostream & os, const string & gap = "", bool lastElem = false ) const;
    virtual CComboBox        * Clone                    ( void ) const;
    virtual void               Delete                   ( void );
    virtual int                GetId                    ( int id = 0 ) const;
    virtual CComboBox        * PtrToId                  ( int id = 0 );
            CComboBox        & Add                      ( const string & str );
            void               SetSelected              ( int idx );
            int                GetSelected              ( void ) const;

   protected:
    string                   * m_Items;
    int                        m_ItemsNr;
    int                        m_ItemsSize;
    int                        m_SelectedIdx;
 };
//--------------------------------------------------------------------------------------------------
class CPanel : public CControl
 {
   public:
                               CPanel                   ( int            id,
                                                          double         x,
                                                          double         y,
                                                          double         w,
                                                          double         h );
                             ~ CPanel                   ( void );
    virtual ostream          & Print                    ( ostream & os ) const;
    virtual ostream          & PrintTo                  ( ostream & os, const string & gap = "", bool lastElem = false ) const;
    virtual ostream          & PrintToPanel             ( ostream & os, const string & gap = "", bool lastElem = false ) const;
    virtual CPanel           * Clone                    ( void ) const;
    virtual void               Delete                   ( void );
    virtual int                GetId                    ( int id = 0 ) const;
    virtual CControl         * PtrToId                  ( int id = 0 );
    CPanel                   & Add                      ( const CControl & ctl );
    virtual void               SyncPos                  ( int srcX, int srcY, int srcW, int srcH );

   protected:
    CControl                ** m_Ctls;
    int                        m_CtlsNr;
    int                        m_CtlsSize;
 };
//--------------------------------------------------------------------------------------------------
class CWindow
 {
   public:
                               CWindow                  ( const string & title,
                                                          int            x,
                                                          int            y,
                                                          int            w,
                                                          int            h );
                             ~ CWindow                  ( void );
                               CWindow                  ( const CWindow & src );
    CWindow                  & operator =               ( const CWindow & src );                           
    friend ostream           & operator <<              ( ostream & os, const CWindow & src );
    CWindow                  & Add                      ( const CControl & ctl );
    void                       SetPosition              ( int x, int y, int w, int h );
    CControl                 * Search                   ( int id ) const;
    
   protected:
    string                     m_Title;
    int                        m_X;
    int                        m_Y;
    int                        m_W;
    int                        m_H;
    CControl                ** m_Ctls;
    int                        m_CtlsNr;
    int                        m_CtlsSize;
 };
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
                               CControl :: CControl     ( int            id,
                                                          double         x,
                                                          double         y,
                                                          double         w,
                                                          double         h )
 {
   m_Id     = id;
   m_relX   = x;
   m_relY   = y;
   m_relW   = w;
   m_relH   = h;
 }
    ostream                  & operator <<              ( ostream & os, const CControl & src )
 {
   return src . Print ( os );
 }
            void               CControl :: SyncPos      ( int srcX, int srcY, int srcW, int srcH )
 {
   m_absX = m_relX * srcW + srcX;
   m_absY = m_relY * srcH + srcY;
   m_absW = m_relW * srcW;
   m_absH = m_relH * srcH;
 }
//--------------------------------------------------------------------------------------------------
                               CButton :: CButton       ( int            id,
                                                          double         x,
                                                          double         y,
                                                          double         w,
                                                          double         h,
                                                          const string & title )
                                                        : CControl ( id, x, y, w, h )
 {
   m_Title = title;
 }
    ostream                  & CButton :: Print         ( ostream & os ) const
 {
   os << "[" << m_Id << "] Button \"" << m_Title << "\" ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;
   return os;
 }
    ostream                  & CButton :: PrintTo       ( ostream & os, const string & gap, bool lastElem ) const
 {
   os << gap << "+- [" << m_Id << "] Button \"" << m_Title << "\" ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;
   return os;
 }
    ostream                  & CButton :: PrintToPanel  ( ostream & os, const string & gap, bool lastElem ) const
 {
   os << gap << "+- [" << m_Id << "] Button \"" << m_Title << "\" ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;
   return os;
 }
    CButton                  * CButton :: Clone         ( void ) const
 {
   CButton * tmp = new CButton ( m_Id, m_relX, m_relY, m_relW, m_relH, m_Title );   
   return tmp;
 }
    void                       CButton :: Delete        ( void )
 {
   delete this;
 }
    int                        CButton :: GetId         ( int id ) const
 {
   return m_Id;
 }
    CButton                  * CButton :: PtrToId       ( int id )
 {
   return this;
 }
//--------------------------------------------------------------------------------------------------
                               CInput :: CInput         ( int            id,
                                                          double         x,
                                                          double         y,
                                                          double         w,
                                                          double         h,
                                                          const string & title )
                                                        : CControl ( id, x, y, w, h )
 {
   m_Title = title;
 }  
    ostream                  & CInput :: Print          ( ostream & os ) const
 {
   os << "[" << m_Id << "] Input \"" << m_Title << "\" ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;   
   return os;
 }
    ostream                  & CInput :: PrintTo        ( ostream & os, const string & gap, bool lastElem ) const
 {
   os << gap << "+- [" << m_Id << "] Input \"" << m_Title << "\" ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;   
   return os;
 }
    ostream                  & CInput :: PrintToPanel   ( ostream & os, const string & gap, bool lastElem ) const
 {
   os << gap << "+- [" << m_Id << "] Input \"" << m_Title << "\" ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;   
   return os;
 }
    CInput                   * CInput :: Clone          ( void ) const
 {
   CInput * tmp = new CInput ( m_Id, m_relX, m_relY, m_relW, m_relH, m_Title );
   return tmp;
 }
    void                       CInput :: Delete         ( void )
 {
   delete this;
 }
    int                        CInput :: GetId          ( int id ) const
 {
   return m_Id;
 }
    CInput                   * CInput :: PtrToId       ( int id )
 {
   return this;
 }
    void                       CInput :: SetValue       ( const string & str )
 {
   m_Title = str;
 }
    const string             & CInput :: GetValue       ( void ) const
 {
   return m_Title;
 }
//--------------------------------------------------------------------------------------------------
                               CLabel :: CLabel         ( int            id,
                                                          double         x,
                                                          double         y,
                                                          double         w,
                                                          double         h,
                                                          const string & title )
                                                        : CControl ( id, x, y, w, h )
 {
   m_Title = title;
 }
    ostream                  & CLabel :: Print          ( ostream & os ) const
 {
   os << "[" << m_Id << "] Label \"" << m_Title << "\" ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;
   return os;
 }
    ostream                  & CLabel :: PrintTo        ( ostream & os, const string & gap, bool lastElem ) const
 {
   os << gap << "+- [" << m_Id << "] Label \"" << m_Title << "\" ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;
   return os;
 }
    ostream                  & CLabel :: PrintToPanel   ( ostream & os, const string & gap, bool lastElem ) const
 {
   os << gap << "+- [" << m_Id << "] Label \"" << m_Title << "\" ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;
   return os;
 }
    CLabel                   * CLabel :: Clone          ( void ) const
 {
   CLabel * tmp = new CLabel ( m_Id, m_relX, m_relY, m_relW, m_relH, m_Title );
   return tmp;
 }
    void                       CLabel :: Delete        ( void )
 {
   delete this;
 }
    int                        CLabel :: GetId          ( int id ) const
 {
   return m_Id;
 }
    CLabel                   * CLabel :: PtrToId       ( int id )
 {
   return this;
 }
//--------------------------------------------------------------------------------------------------
                               CComboBox :: CComboBox   ( int            id,
                                                          double         x,
                                                          double         y,
                                                          double         w,
                                                          double         h )
                                                        : CControl ( id, x, y, w, h )
 {
   m_Items       = new string [ 10000 ];
   m_ItemsNr     = 0;
   m_ItemsSize   = 10000;
   m_SelectedIdx = 0;
 }
                               CComboBox :: ~ CComboBox ( void )
 {
   delete [] m_Items;
   m_ItemsNr     = 0;
   m_ItemsSize   = 0;
   m_SelectedIdx = 0;
 }
    ostream                  & CComboBox :: Print       ( ostream & os ) const
 {
   os << "[" << m_Id << "] ComboBox ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;
   
   for ( int i = 0 ; i < m_ItemsNr ; i ++ )
      if ( i == m_SelectedIdx )
         os << "+->" << m_Items [ i ] << "<" << endl;
      else
         os << "+- " << m_Items [ i ] << endl;

   return os;
 }
    ostream                  & CComboBox :: PrintTo     ( ostream & os, const string & gap, bool lastElem ) const
 {
   os << gap << "+- [" << m_Id << "] ComboBox ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;

   if ( lastElem == false )
    {
      for ( int i = 0 ; i < m_ItemsNr ; i ++ )
         if ( i == m_SelectedIdx )
            os << gap << "|" << "  " << "+->" << m_Items [ i ] << "<" << endl;
         else
            os << gap << "|" << "  " << "+- " << m_Items [ i ] << endl;
    }
   else
    {
      for ( int i = 0 ; i < m_ItemsNr ; i ++ )
         if ( i == m_SelectedIdx )
            os << gap << "   " << "+->" << m_Items [ i ] << "<" << endl;
         else
            os << gap << "   " << "+- " << m_Items [ i ] << endl;
    }

   return os;
 }
    ostream                  & CComboBox :: PrintToPanel   ( ostream & os, const string & gap, bool lastElem ) const
 {
   os << gap << "+- [" << m_Id << "] ComboBox ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;

   if ( lastElem == false )
    {
      for ( int i = 0 ; i < m_ItemsNr ; i ++ )
         if ( i == m_SelectedIdx )
            os << gap << "|" << "  " << "+->" << m_Items [ i ] << "<" << endl;
         else
            os << gap << "|" << "  " << "+- " << m_Items [ i ] << endl;
    }
   else
    {
      for ( int i = 0 ; i < m_ItemsNr ; i ++ )
         if ( i == m_SelectedIdx )
            os << gap << "   " << "+->" << m_Items [ i ] << "<" << endl;
         else
            os << gap << "   " << "+- " << m_Items [ i ] << endl;
    }

   return os;
 }
    CComboBox                * CComboBox :: Clone       ( void ) const
 {
   CComboBox * tmp      = new CComboBox ( m_Id, m_relX, m_relY, m_relW, m_relH );
   tmp -> m_ItemsNr     = m_ItemsNr;
   tmp -> m_ItemsSize   = m_ItemsSize;
   tmp -> m_SelectedIdx = m_SelectedIdx;
   
   for ( int i = 0 ; i < m_ItemsNr ; i ++ )
      tmp -> m_Items [ i ] = m_Items [ i ];
   
   return tmp;
 }
    void                       CComboBox :: Delete        ( void )
 {
   delete this;
 }
    int                        CComboBox :: GetId       ( int id ) const
 {
   return m_Id;
 }
    CComboBox                * CComboBox :: PtrToId       ( int id )
 {
   return this;
 }
    CComboBox                & CComboBox :: Add         ( const string & str )
 {
   m_Items [ m_ItemsNr ++ ] = str;
   return * this;
 }
    void                       CComboBox :: SetSelected ( int idx )
 {
   m_SelectedIdx = idx;
 }
    int                        CComboBox :: GetSelected ( void ) const
 {
   return m_SelectedIdx;
 }
//--------------------------------------------------------------------------------------------------
                               CPanel :: CPanel         ( int            id,
                                                          double         x,
                                                          double         y,
                                                          double         w,
                                                          double         h )
                                                        : CControl ( id, x, y, w, h )
 {
   m_Ctls     = new CControl* [ 10000 ];
   m_CtlsNr   = 0;
   m_CtlsSize = 10000;
 }
                               CPanel :: ~ CPanel       ( void )
 {
   for ( int i = 0 ; i < m_CtlsNr ; i ++ )
      m_Ctls [ i ] -> Delete ();
   delete [] m_Ctls;
   m_CtlsNr   = 0;
   m_CtlsSize = 0;
 }
    ostream                  & CPanel :: Print          ( ostream & os ) const
 {
   os << "[" << m_Id << "] Panel ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;

   int i;
   for ( i = 0 ; i < m_CtlsNr - 1 ; i ++ )
      m_Ctls [ i ] -> PrintToPanel ( os, "", 0 );
   m_Ctls [ i ] -> PrintToPanel ( os, "", 1 );
   
   return os; 
 }
    ostream                  & CPanel :: PrintTo        ( ostream & os, const string & gap, bool lastElem ) const
 {
   os << gap << "+- [" << m_Id << "] Panel ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;

   if ( lastElem == false )
    {
      int i;
      for ( i = 0 ; i < m_CtlsNr - 1 ; i ++ )
         m_Ctls [ i ] -> PrintToPanel ( os, gap + "|  ", 0 );
      m_Ctls [ i ] -> PrintToPanel ( os, gap + "|  ", 1 );
    }	
   else
    {
      int i;
      for ( i = 0 ; i < m_CtlsNr - 1 ; i ++ )
         m_Ctls [ i ] -> PrintToPanel ( os, gap + "   ", 0 );
      m_Ctls [ i ] -> PrintToPanel ( os, gap + "   ", 1 );    
    }
   
   return os;
 }
    ostream                  & CPanel :: PrintToPanel        ( ostream & os, const string & gap, bool lastElem ) const
 {
   os << gap << "+- [" << m_Id << "] Panel ("
      << m_absX << "," << m_absY << "," << m_absW << "," << m_absH << ")" << endl;

   if ( lastElem == false )
    {
      int i;
      for ( i = 0 ; i < m_CtlsNr - 1 ; i ++ )
         m_Ctls [ i ] -> PrintToPanel ( os, gap + "|  ", 0 );
      m_Ctls [ i ] -> PrintToPanel ( os, gap + "|  ", 1 );
    }	
   else
    {
      int i;
      for ( i = 0 ; i < m_CtlsNr - 1 ; i ++ )
         m_Ctls [ i ] -> PrintToPanel ( os, gap + "   ", 0 );
      m_Ctls [ i ] -> PrintToPanel ( os, gap + "   ", 1 );    
    }
   
   return os;
 }
    CPanel                   * CPanel :: Clone          ( void ) const
 {
   CPanel * tmp      = new CPanel ( m_Id, m_relX, m_relY, m_relW, m_relH );
   tmp -> m_CtlsNr   = m_CtlsNr;
   tmp -> m_CtlsSize = m_CtlsSize;
   
   for ( int i = 0 ; i < m_CtlsNr ; i ++ )
      tmp -> m_Ctls [ i ] = m_Ctls [ i ] -> Clone ();

   return tmp;
 }
    void                       CPanel :: Delete         ( void )
 {
   delete this;
 }
    int                        CPanel :: GetId          ( int id ) const
 {
   if ( m_Id == id ) return id;
   
   for ( int i = 0 ; i < m_CtlsNr ; i ++ )
      if ( m_Ctls [ i ] -> GetId ( id ) == id )
         return id;

   return m_Id;
 }
    CControl                 * CPanel :: PtrToId       ( int id )
 {
   if ( m_Id == id ) return this;

   for ( int i = 0 ; i < m_CtlsNr ; i ++ )
      if ( m_Ctls [ i ] -> GetId ( id ) == id )
         return m_Ctls [ i ];
   
   return NULL;
 }
    CPanel                   & CPanel :: Add            ( const CControl & ctl )
 {
     CControl * tmpCtl = ctl . Clone ();
     tmpCtl -> SyncPos ( m_absX, m_absY, m_absW, m_absH );
     m_Ctls [ m_CtlsNr ++ ] = tmpCtl;
     return * this;
 }
            void               CPanel :: SyncPos        ( int srcX, int srcY, int srcW, int srcH )
 {
   m_absX = m_relX * srcW + srcX;
   m_absY = m_relY * srcH + srcY;
   m_absW = m_relW * srcW;
   m_absH = m_relH * srcH;
   
   for ( int i = 0 ; i < m_CtlsNr ; i ++ )
      m_Ctls [ i ] -> SyncPos ( m_absX, m_absY, m_absW, m_absH );
 }
//--------------------------------------------------------------------------------------------------
                               CWindow :: CWindow       ( const string & title,
                                                          int            x,
                                                          int            y,
                                                          int            w,
                                                          int            h )
 {
   m_Title    = title;
   m_X        = x;
   m_Y        = y;
   m_W        = w;
   m_H        = h;
   m_Ctls     = new CControl* [ 10000 ];
   m_CtlsNr   = 0;
   m_CtlsSize = 10000;
 }
                               CWindow :: ~ CWindow     ( void )
 {
   for ( int i = 0 ; i < m_CtlsNr ; i ++ )
      m_Ctls [ i ] -> Delete ();
   delete [] m_Ctls;
   m_CtlsNr   = 0;
   m_CtlsSize = 0;
   m_Title . clear ();
   m_X        = 0;
   m_Y        = 0;
   m_W        = 0;
   m_H        = 0;
 }
                               CWindow :: CWindow       ( const CWindow & src )
 {
   m_Title    = src . m_Title;
   m_X        = src . m_X;
   m_Y        = src . m_Y;
   m_W        = src . m_W;
   m_H        = src . m_H;
   m_Ctls     = new CControl* [ src . m_CtlsSize ];
   m_CtlsNr   = src . m_CtlsNr;
   m_CtlsSize = src . m_CtlsSize;
   
   for ( int i = 0 ; i < m_CtlsNr ; i ++ )
    {
      m_Ctls [ i ] = src . m_Ctls [ i ] -> Clone ();
      m_Ctls [ i ] -> SyncPos ( m_X, m_Y, m_W, m_H );
    }
 }
    CWindow                  & CWindow :: operator =    ( const CWindow & src )
 {
   if ( this == & src ) return * this;

   int i;
  
   for ( i = 0 ; i < m_CtlsNr ; i ++ )
      m_Ctls [ i ] -> Delete ();
   delete [] m_Ctls;

   m_Title    = src . m_Title;
   m_X        = src . m_X;
   m_Y        = src . m_Y;
   m_W        = src . m_W;
   m_H        = src . m_H;
   m_Ctls     = new CControl* [ src . m_CtlsSize ];
   m_CtlsNr   = src . m_CtlsNr;
   m_CtlsSize = src . m_CtlsSize;
   
   for ( i = 0 ; i < m_CtlsNr ; i ++ )
    {
      m_Ctls [ i ] = src . m_Ctls [ i ] -> Clone ();;
      m_Ctls [ i ] -> SyncPos ( m_X, m_Y, m_W, m_H );
    }

   return * this;
 }
    ostream                  & operator <<              ( ostream & os, const CWindow & src )
 {
   os << "Window \"" << src . m_Title << "\" ("
      << src . m_X << "," << src . m_Y << "," << src . m_W << "," << src . m_H << ")" << endl;

   int i;
   for ( i = 0 ; i < src . m_CtlsNr - 1 ; i ++ )
      src . m_Ctls [ i ] -> PrintTo ( os, "", 0 );
   src . m_Ctls [ i ] -> PrintTo ( os, "", 1 );
   
   return os;
 }
    CWindow                  & CWindow :: Add           ( const CControl & ctl )
 {
     CControl * tmpCtl = ctl . Clone ();
     tmpCtl -> SyncPos ( m_X, m_Y, m_W, m_H );
     m_Ctls [ m_CtlsNr ++ ] = tmpCtl;
     return * this;
 }
    void                       CWindow :: SetPosition   ( int x, int y, int w, int h )
 {
   m_X = x;
   m_Y = y;
   m_W = w;
   m_H = h;
   
   for ( int i = 0 ; i < m_CtlsNr ; i ++ )
      m_Ctls [ i ] -> SyncPos ( x, y, w, h );
 }
    CControl                 * CWindow :: Search        ( int id ) const
 {
   for ( int i = 0 ; i < m_CtlsNr ; i ++ )
      if ( m_Ctls [ i ] -> GetId ( id ) == id )
         return m_Ctls [ i ] -> PtrToId ( id );
   return NULL;
 }
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
    int                        main                     ( int argc, char * argv [] )
 {
	CWindow a ( "Sample window", 10, 10, 600, 480 );
	a . Add ( CButton ( 1, 0.1, 0.8, 0.3, 0.1, "Ok" ) ) . Add ( CButton ( 2, 0.6, 0.8, 0.3, 0.1, "Cancel" ) );
	a . Add ( CLabel ( 10, 0.1, 0.1, 0.2, 0.1, "Username:" ) );
	a . Add ( CInput ( 11, 0.4, 0.1, 0.5, 0.1, "chucknorris" ) );
	a . Add ( CPanel ( 12, 0.1, 0.3, 0.8, 0.7 ) . Add ( CComboBox ( 20, 0.1, 0.3, 0.8, 0.1 ) 
	  . Add ( "Karate" ) . Add ( "Judo" ) . Add ( "Box" ) . Add ( "Progtest" ) ));
	cout << a;
	/*
	Window "Sample window" (10,10,600,480)
	+- [1] Button "Ok" (70,394,180,48)
	+- [2] Button "Cancel" (370,394,180,48)
	+- [10] Label "Username:" (70,58,120,48)
	+- [11] Input "chucknorris" (250,58,300,48)
	+- [12] Panel (70,154,480,336)
		+- [20] ComboBox (118,254,384,33)
		   +->Karate<
		   +- Judo
		   +- Box
		   +- Progtest
	*/
   cout << "------------------------------------------" << endl;

	CWindow b = a;
	CControl * ctl = b . Search ( 20 );
	cout << *ctl;
	/*
	[20] ComboBox (118,254,384,33)
	+->Karate<
	+- Judo
	+- Box
	+- Progtest
	*/
   cout << "------------------------------------------" << endl;

	CComboBox * cb = dynamic_cast<CComboBox *> ( b . Search ( 20 ) );
	cb -> SetSelected ( 3 );
	CInput * il = dynamic_cast<CInput *> ( b . Search ( 11 ) );
	il -> SetValue ( "chucknorris@fit.cvut.cz" );
	CPanel * pa = dynamic_cast<CPanel *> ( b . Search ( 12 ) );
	pa -> Add ( CComboBox ( 21, 0.1, 0.5, 0.8, 0.1 ) . Add ( "PA2" ) . Add ( "OSY" ) . Add ( "Both" ) );
	cout << b;
	/*
	Window "Sample window" (10,10,600,480)
	+- [1] Button "Ok" (70,394,180,48)
	+- [2] Button "Cancel" (370,394,180,48)
	+- [10] Label "Username:" (70,58,120,48)
	+- [11] Input "chucknorris@fit.cvut.cz" (250,58,300,48)
	+- [12] Panel (70,154,480,336)
		+- [20] ComboBox (118,254,384,33)
		|  +- Karate
		|  +- Judo
		|  +- Box
		|  +->Progtest<
		+- [21] ComboBox (118,322,384,33)
		   +->PA2<
		   +- OSY
		   +- Both
	*/
   cout << "------------------------------------------" << endl;

	b . SetPosition ( 20, 30, 640, 520 );
	cout << b;
	/*
	Window "Sample window" (20,30,640,520)
	+- [1] Button "Ok" (84,446,192,52)
	+- [2] Button "Cancel" (404,446,192,52)
	+- [10] Label "Username:" (84,82,128,52)
	+- [11] Input "chucknorris@fit.cvut.cz" (276,82,320,52)
	+- [12] Panel (84,186,512,364)
		+- [20] ComboBox (135,295,409,36)
		|  +- Karate
		|  +- Judo
		|  +- Box
		|  +->Progtest<
		+- [21] ComboBox (135,368,409,36)
		   +->PA2<
		   +- OSY
		   +- Both
	*/
   cout << "------------------------------------------" << endl;

	pa -> Add ( *pa );
	pa -> Add ( *pa );
	pa -> Add ( *pa );
	cout << b;
	/*
	Window "Sample window" (20,30,640,520)
	+- [1] Button "Ok" (84,446,192,52)
	+- [2] Button "Cancel" (404,446,192,52)
	+- [10] Label "Username:" (84,82,128,52)
	+- [11] Input "chucknorris@fit.cvut.cz" (276,82,320,52)
	+- [12] Panel (84,186,512,364)
		+- [20] ComboBox (135,295,409,36)
		|  +- Karate
		|  +- Judo
		|  +- Box
		|  +->Progtest<
		+- [21] ComboBox (135,368,409,36)
		|  +->PA2<
		|  +- OSY
		|  +- Both
		+- [12] Panel (135,295,409,254)
		|  +- [20] ComboBox (175,371,327,25)
		|  |  +- Karate
		|  |  +- Judo
		|  |  +- Box
		|  |  +->Progtest<
		|  +- [21] ComboBox (175,422,327,25)
		|     +->PA2<
		|     +- OSY
		|     +- Both
		+- [12] Panel (135,295,409,254)
		|  +- [20] ComboBox (175,371,327,25)
		|  |  +- Karate
		|  |  +- Judo
		|  |  +- Box
		|  |  +->Progtest<
		|  +- [21] ComboBox (175,422,327,25)
		|  |  +->PA2<
		|  |  +- OSY
		|  |  +- Both
		|  +- [12] Panel (175,371,327,177)
		|     +- [20] ComboBox (207,424,261,17)
		|     |  +- Karate
		|     |  +- Judo
		|     |  +- Box
		|     |  +->Progtest<
		|     +- [21] ComboBox (207,459,261,17)
		|        +->PA2<
		|        +- OSY
		|        +- Both
		+- [12] Panel (135,295,409,254)
		   +- [20] ComboBox (175,371,327,25)
		   |  +- Karate
		   |  +- Judo
		   |  +- Box
		   |  +->Progtest<
		   +- [21] ComboBox (175,422,327,25)
		   |  +->PA2<
		   |  +- OSY
		   |  +- Both
		   +- [12] Panel (175,371,327,177)
		   |  +- [20] ComboBox (207,424,261,17)
		   |  |  +- Karate
		   |  |  +- Judo
		   |  |  +- Box
		   |  |  +->Progtest<
		   |  +- [21] ComboBox (207,459,261,17)
		   |     +->PA2<
		   |     +- OSY
		   |     +- Both
		   +- [12] Panel (175,371,327,177)
		      +- [20] ComboBox (207,424,261,17)
		      |  +- Karate
		      |  +- Judo
		      |  +- Box
		      |  +->Progtest<
		      +- [21] ComboBox (207,459,261,17)
		      |  +->PA2<
		      |  +- OSY
		      |  +- Both
		      +- [12] Panel (207,424,261,123)
		         +- [20] ComboBox (233,460,208,12)
		         |  +- Karate
		         |  +- Judo
		         |  +- Box
		         |  +->Progtest<
		         +- [21] ComboBox (233,485,208,12)
		            +->PA2<
		            +- OSY
		            +- Both
	*/
   cout << "------------------------------------------" << endl;

	cout << *pa;
	/*
	[12] Panel (84,186,512,364)
	+- [20] ComboBox (135,295,409,36)
	|  +- Karate
	|  +- Judo
	|  +- Box
	|  +->Progtest<
	+- [21] ComboBox (135,368,409,36)
	|  +->PA2<
	|  +- OSY
	|  +- Both
	+- [12] Panel (135,295,409,254)
	|  +- [20] ComboBox (175,371,327,25)
	|  |  +- Karate
	|  |  +- Judo
	|  |  +- Box
	|  |  +->Progtest<
	|  +- [21] ComboBox (175,422,327,25)
	|     +->PA2<
	|     +- OSY
	|     +- Both
	+- [12] Panel (135,295,409,254)
	|  +- [20] ComboBox (175,371,327,25)
	|  |  +- Karate
	|  |  +- Judo
	|  |  +- Box
	|  |  +->Progtest<
	|  +- [21] ComboBox (175,422,327,25)
	|  |  +->PA2<
	|  |  +- OSY
	|  |  +- Both
	|  +- [12] Panel (175,371,327,177)
	|     +- [20] ComboBox (207,424,261,17)
	|     |  +- Karate
	|     |  +- Judo
	|     |  +- Box
	|     |  +->Progtest<
	|     +- [21] ComboBox (207,459,261,17)
	|        +->PA2<
	|        +- OSY
	|        +- Both
	+- [12] Panel (135,295,409,254)
		+- [20] ComboBox (175,371,327,25)
		|  +- Karate
		|  +- Judo
		|  +- Box
		|  +->Progtest<
		+- [21] ComboBox (175,422,327,25)
		|  +->PA2<
		|  +- OSY
		|  +- Both
		+- [12] Panel (175,371,327,177)
		|  +- [20] ComboBox (207,424,261,17)
		|  |  +- Karate
		|  |  +- Judo
		|  |  +- Box
		|  |  +->Progtest<
		|  +- [21] ComboBox (207,459,261,17)
		|     +->PA2<
		|     +- OSY
		|     +- Both
		+- [12] Panel (175,371,327,177)
		   +- [20] ComboBox (207,424,261,17)
		   |  +- Karate
		   |  +- Judo
		   |  +- Box
		   |  +->Progtest<
		   +- [21] ComboBox (207,459,261,17)
		   |  +->PA2<
		   |  +- OSY
		   |  +- Both
		   +- [12] Panel (207,424,261,123)
		      +- [20] ComboBox (233,460,208,12)
		      |  +- Karate
		      |  +- Judo
		      |  +- Box
		      |  +->Progtest<
		      +- [21] ComboBox (233,485,208,12)
		         +->PA2<
		         +- OSY
		         +- Both
	*/
   cout << "-------------------TEST-------------------" << endl;
   
	CWindow x ( "Sample window", 10, 10, 600, 480 );
	x . Add ( CButton ( 1, 0.1, 0.8, 0.3, 0.1, "Ok" ) ) . Add ( CButton ( 2, 0.6, 0.8, 0.3, 0.1, "Cancel" ) );
	x . Add ( CLabel ( 10, 0.1, 0.1, 0.2, 0.1, "Username:" ) );
	x . Add ( CInput ( 11, 0.4, 0.1, 0.5, 0.1, "chucknorris" ) );
	x . Add ( CComboBox ( 20, 0.1, 0.3, 0.8, 0.1 ) . Add ( "Karate" ) . Add ( "Judo" ) . Add ( "Box" ) . Add ( "Progtest" ) );

	CWindow y = x;
	CComboBox * cy = dynamic_cast<CComboBox *> ( y . Search ( 20 ) );
	cy -> SetSelected ( 3 );
	CInput * ily = dynamic_cast<CInput *> ( y . Search ( 11 ) );
	ily -> SetValue ( "chucknorris@fit.cvut.cz" );
	y . Add ( CComboBox ( 21, 0.1, 0.5, 0.8, 0.1 ) . Add ( "PA2" ) . Add ( "OSY" ) . Add ( "Both" ) );
	cout << y;
	/*
	Window "Sample window" (10,10,600,480)
	+- [1] Button "Ok" (70,394,180,48)
	+- [2] Button "Cancel" (370,394,180,48)
	+- [10] Label "Username:" (70,58,120,48)
	+- [11] Input "chucknorris@fit.cvut.cz" (250,58,300,48)
	+- [20] ComboBox (70,154,480,48)
	|  +- Karate
	|  +- Judo
	|  +- Box
	|  +->Progtest<
	+- [21] ComboBox (70,250,480,48)
		+->PA2<
		+- OSY
		+- Both
	*/

	return 0;
 }
#endif /* __PROGTEST__ */


