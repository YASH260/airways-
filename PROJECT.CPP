//*************************************************************************//
//*************************************************************************//
	//~~~~~~~~~~~~~~~~~~~~~~~~~~//
//*************************************************************************//
//*************************************************************************//
//******************* PROJECT AIRWAYS MANAGEMENT **************************//
//*************************************************************************//
//*************************************************************************//
//*************************************************************************//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HEADER FILES INCLUDED
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//*************************************************************************//

#include<fstream.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<ctype.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  THIS CLASS DRAWS LINES, BOXES,  ETC.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class DRAW   {
	       public:
	       void LINE_HOR(int, int, int, char);
	       void LINE_VER(int, int, int, char);
	       void BOX(int, int, int, int, char);

	       };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// THIS CLASS CONTROLS ALL THE FUNCTIONS RELATED TO TICKETS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class TICKET {
		protected:
		char fltno[20];
		char from[20];
		char to[20];
		int ecofair, exefair;
		public:
		void ADDITION();
		void ENQUIRY();
		char *FLIGHTNO(int);
	       };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// THIS CLASS CONTROL ALL THE FUNCTIONS RELATED TO PASSENGERS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class PASSANGER
	      {
	      protected:
	      char Class;
	      char name[26], address[40],flit[10], sex;
	      int slno, age, ticketno;
	      public:
	      void ADD_RECORD(int tno, int sno, char Pname[20],
		    char Paddress[36] ,char pfno[],int page, char Psex,
		    char Pclass);
	      void DELETE_TICKET(int);
	      int DELETE_FLIGHT(int);
	      void LIST(void);
	      int LAST_TICKETNO(void);
	      int SEATS(int);
	      int FOUND(int);
	      char *NAME(int);

	      };

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  THIS IS DERIVED CLASS WHICH CONTROLS ALL THE FUNCTIONS
  RELATED TO RESERVATION, CANCELLATION, ETC.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class RESERVE:public TICKET,public PASSANGER
{
	public:
	void RESERVATION();
	void CANCELLATION();
	void DISPLAY_TICKET();
	void DELETE_ALL();
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  FUNCTION TO DRAW HORIZONTAL LINE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void DRAW :: LINE_HOR(int column1, int column2, int row,  char c)
{
	  for(int col= column1; col <= column2; col++)
	  {
		    gotoxy(col, row);
		    cout<<c;
	  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  FUNCTION TO DRAW VERTICAL LINE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void DRAW :: LINE_VER(int row1, int row2, int column, char c)
{
	for(int r = row1; r<=row2; r++)
	{
	     gotoxy(column, r);
	     cout<<c;
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  FUNCTION TO DRAW BOX
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void DRAW :: BOX (int column1, int row1,int column2, int row2, char c)
{
	char ch = 218;
	char c1, c2, c3, c4;
	char f=196, g=179;
	if (c == ch)
	{
		c1=218;
		c2=191;
		c3=192;
		c4=217;
		f=196;
		g=179;
	}
	else
	{
	       c1=c;
	       c2=c;
	       c3=c;
	       c4=c;
	       f=c;
	       g=c;
	 }
	 gotoxy(column1, row1);
	 cout<<c1;
	 gotoxy(column2, row1);
	 cout<<c2;
	 gotoxy(column1, row2);
	 cout<<c3;
	 gotoxy(column2, row2);
	 cout<<c4;
	 column1++;
	 column2--;
	 LINE_HOR(column1,column2,row1,f);
	 LINE_HOR(column1,column2,row2,f);
	 column1--;
	 column2++;
	 row1++;
	 row2--;
	 LINE_VER(row1,row2,column1,g);
	 LINE_VER(row1,row2,column2,g);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNCTION TO GIVE DATA TO THE RECORDS IN TICKET FILE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void TICKET :: ADDITION()
{
	fstream file;
	file.open("TICKET.DAT", ios::app | ios :: binary);
	char ch;
	do
	{
	    clrscr();
	    cout << " Enter the flight no.:  ";
	    cin >> fltno;
	    cout << " Enter the Source : ";
	    gets(from);
	    cout << " Enter the  Destination : ";
	    gets(to);
	    cout << " Enter the Economic Fair : ";
	    cin >> ecofair;
	    cout << " Enter the Executive Fair : ";
	    cin >> exefair;
	    file.write((char*) this ,  sizeof(TICKET));
	    cout << " Wish to enter data (Y/N) : ";
	    cin >> ch;
	}while ( ch == 'Y' || ch == 'y' );
	file.close();
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNCTION TO ADD GIVEN DATA IN THE TICKET FILE (TICKET.DAT)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNCTION TO RETURN FLIGHT NO. FOR THE GIVEN SNO
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

char *TICKET :: FLIGHTNO(int sno)
{
	fstream file;
	file.open("TICKET.DAT", ios::app | ios :: binary);
	int count=0;
	while(file.read((char*) this, sizeof(TICKET)))
	{
		count++;
		if ( sno == count);
		      break;
	}
	file.close();
	return fltno;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNCTION TO DISPLAY LIST OF FLIGHTS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void TICKET :: ENQUIRY()
{
	clrscr();
	fstream file;
	file.open("TICKET.DAT", ios::in | ios :: binary);
	DRAW d;
	d.BOX(1,2,80,24,218);
	d.LINE_HOR(2,79,4,196);
	d.LINE_HOR(2,79,6,196);
	d.LINE_HOR(2,79,22,196);
	gotoxy(30,3);
	cout<<"LIST OF THE FLIGHTS";
	for (int i =2; i<=79; i++)
	{
		gotoxy(i,5);
		cout<<" ";
	}
	gotoxy(2,5);
	cout<<" S.No.  Flight No.\t From\tTo\tEconomic Fair\tExecutive Fair";
	int row=7, sno=1;
	while(file.read((char*) this, sizeof(TICKET)))
	{
		  gotoxy(4,row);
		  cout<< sno;
		  gotoxy(9,row);
		  cout<< fltno;
		  gotoxy(20,row);
		  cout<< from;
		  gotoxy(34,row);
		  cout<<to;
		  gotoxy(52,row);
		  cout<< ecofair;
		  gotoxy(67,row);
		  cout<< exefair;
		  row++;
		  sno++;

	}
	file.close();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  FUNCTION TO RESERVE TICKET FOR THE PASSANGER
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void RESERVE :: RESERVATION(void)
{
	clrscr() ;
	ENQUIRY() ;
	char t1[5] , Pclass ,Pname[26] ,Paddress[36],Psex,Pfltno[10] ;
	int t2 , valid , page , tno , sno ;
	PASSANGER P ;
	tno = P.LAST_TICKETNO() + 1 ;
	do
	{
		valid = 1 ;
		gotoxy(3,23);
		cout <<" PRESS <ENTER> TO EXIT " ;
		gotoxy(3,20);
		cout << " Enter Sno. of the FLIGHT : " ;
		gets( t1 ) ;
		t2 = atoi ( t1 ) ;
		sno = t2 ;
		if(strlen(t1)==0)
		   return;
		if ( sno < 1 || sno > 12 )
		{
			valid = 0 ;
			gotoxy(3,23);
			cout << " ENTER CORRECTLY " << endl ;
		}
	}while (!valid) ;
	int i=1 ;
	fstream file ;
	file.open("TICKET.DAT", ios::in|ios::binary ) ;
	while (file.read((char*)this,sizeof(TICKET)))
	{
		if (sno == i)
		       i++ ;
	}
	file.close() ;
	strcpy(Pfltno, fltno) ;
	if (P.SEATS(sno) >=250)
	{
		gotoxy(5,21);
		cout << " \n sorry! Seats are not available " ;
		getch() ;
		return ;
	}
	gotoxy(3,23);
	cout <<"\t\t\tE=ECONOMIC, X=EXECUTIVE or PRESS <ENTER> TO EXIT" ;
	do
	{
		gotoxy(3,21);
		cout << " \t\t\t By which class you want to travel " ;
		Pclass = getche() ;
		Pclass = toupper(Pclass) ;
		if(Pclass == 13)
			return ;
	} while (Pclass != 'E' && Pclass != 'X') ;
	clrscr() ;
	gotoxy(72,3);
	cout<<"<0>= EXIT";
	gotoxy(34,2);
	cout << "~~-->RESERVATION<--~~ " ;
	gotoxy(5,5);
	cout <<"NAME        : " ;
	gotoxy(5,7);
	cout << "ADDRESS    : " ;
	gotoxy(5,9);
	cout <<" SEX (M/F)  : " ;
	gotoxy(5,11);
	cout << "AGE        : " ;
	do
	{
		valid = 1 ;
		gotoxy(5,23);
		clreol() ;
		cout << "ENTER THE NAME OF THE PASSENGER : " ;
		gotoxy(15,5);
		clreol() ;
		gets(Pname) ;
		if( Pname[0] == '0' )
			return ;
		if( strlen(Pname) < 1 || strlen(Pname) > 20)
		{
			valid = 0 ;
			gotoxy(5,23);
			clreol ;
			cout << "Enter range correctly (Range: 1..20)" ;
		}
	} while (!valid) ;
	do
	{
		valid = 1 ;
		gotoxy(5,23);
		clreol ;
		cout << "\n ENTER THE ADDRESS OF THE PASSENGER : " ;
		gotoxy(15,7);
		clreol() ;
		gets(Paddress) ;
		if( Paddress[0] == '0' )
			return ;
		if( strlen(Paddress) < 1 || strlen(Paddress) > 35 )
		{
			valid = 0 ;
			gotoxy(5,23);
			clreol() ;
			cout << " Enter range correctly (Range: 1..35)" ;
		}
	} while (!valid) ;
	do
	{
		gotoxy(5,23);
		clreol() ;
		cout << " ENTER THE SEX OF THE PASSENGER : " ;
		gotoxy(15,9);
		clreol() ;
		cin >> Psex ;
		Psex = toupper(Psex) ;
		if( Psex == '0')
			return ;
	} while ( Psex != 'M' && Psex != 'F' ) ;
	do
	{
		valid = 1 ;
		gotoxy(5,23);
		clreol() ;
		cout << " ENTER THE AGE OF THE PASSENGER:  " ;
		gotoxy(15,11);
		clreol() ;
		gets(t1) ;
		t2 = atoi(t1) ;
		page = t2 ;
		if( t1[0] == '0' )
			return ;
		if( page < 1 || page > 100 )
		{
			valid = 0 ;
			gotoxy(5,23);
			clreol() ;
			cout << "ENTER CORRECTLY " ;
		}
	} while (!valid) ;
	clrscr() ;
	DRAW d;
	d.BOX(15,5,66,21,'*');
	d.LINE_HOR(16,65,7,'*');
	gotoxy(33,6);
	cout << " Ticket no.: " << tno ;
	gotoxy(17,9);
	cout << from << " to " << to ;
	gotoxy(45,9);
	cout << " Flight no.: " << Pfltno ;
	gotoxy(20,11);
	cout << " Passanger Name :" << Pname ;
	gotoxy(20,13);
	cout << " Address : " << Paddress ;
	gotoxy(20,15);
	cout << " Sex : " << Psex ;
	gotoxy(20,17);
	cout << " Age : " << page ;
	gotoxy(45,19);

	if( Pclass == 'E')
		cout << " Total Fair : " << ecofair ;
	else
		cout << " Total Fair : " << exefair ;
	P.ADD_RECORD( tno, sno, Pname, Paddress,  Pfltno,page, Psex, Pclass ) ;
	getch() ;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNCTION TO ADD THIS GIVEN DATA IN THE PASSANGER'S FILE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void PASSANGER :: ADD_RECORD(int tno, int sno, char Pname[20],
		    char Paddress[36] ,char Pfltno[10],int Page, char Psex,
		    char Pclass)
{

	fstream file ;
	file.open( "PASS.DAT", ios::app|ios::binary ) ;
	ticketno = tno ;
	slno = sno ;
	strcpy(flit, Pfltno);
	strcpy(name, Pname) ;
	strcpy(address, Paddress) ;
	age = Page ;
	sex = Psex ;
	Class = Pclass ;
	file.write( (char *)this, sizeof(PASSANGER) ) ;
	file.close() ;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNCTION RETURNS THE LAST TICKET NO. IN THE PASSANGER FILE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int PASSANGER :: LAST_TICKETNO()
{
	fstream file ;
	file.open ( "PASS.DAT" , ios::in|ios::binary ) ;
	int count = 0 ;
	while ( file.read ((char *)this , sizeof(PASSANGER)))
		count = ticketno ;
	file.close () ;
	return count ;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNTION RETURNS TOTAL NO. OF SEATS IN THE PASSANGER
// FILE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int PASSANGER :: SEATS (int sno)
{
	fstream file ;
	file.open ( "PASS.DAT" , ios::in|ios::binary ) ;
	int count = 0 ;
	while ( file.read ((char *)this , sizeof(PASSANGER)) )
	{
		if (sno == slno)
			count++;

	}
	file.close() ;
	return count ;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNTION RETURNS 0 IF THE TICKET NO. IS NOT FOUND IN THE PASSANGER
// FILE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int PASSANGER :: FOUND (int tno)
{
	fstream file ;
	file.open ( "PASS.DAT" , ios::in|ios::binary ) ;
	int found = 0 ;
	while ( file.read ((char *)this , sizeof(PASSANGER)) )
	{
		if (tno == ticketno)
		{
			found=1;
			break ;
		}
	}
	file.close() ;
	return found ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNCTION RETURNS PASSANGER'S NAME FOR THE GIVEN
// TICKET NO.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

char *PASSANGER :: NAME(int tno)
{
	fstream file ;
	file.open("PASS.DAT" , ios::in|ios::binary) ;
	while ( file.read((char *)this , sizeof(PASSANGER)))
	{
		if( tno == ticketno )
			break ;
	}
	file.close() ;
	return name ;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNCTION DISPLAYS THE LIST OF THE PASSANGERS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void PASSANGER :: LIST(void)
{
	clrscr() ;
	char t1[10] ;
	int t2 , sno , valid ;
	TICKET T ;
	T.ENQUIRY() ;
	int len ;
	do
	{
		valid = 1 ;
		gotoxy(3,23);
		cout << " \t\t PRESS <ENTER> TO EXIT " ;
		gotoxy(3,18);
		cout << "\t\t\t\t" ;
		cout << " Enter Sno. of the FLIGHT for which you want "
		     << " to see list of "
		     <<	" passanger " ;
		gets(t1) ;
		t2 = atoi(t1) ;
		sno = t2 ;
		if ( strlen(t1) == 0 )
			return ;
		if ( sno < 1 || sno > 12 )
		{
			valid = 0 ;
			gotoxy(3,23);
			cout << " \t\t\t ENTER CORRECTLY " ;
			getch() ;
		}
	} while ( !valid ) ;
	clrscr() ;
	int row = 7 , found = 0 , flag = 0 ;
	char ch ;
	DRAW d;
	d.BOX(1,2,80,24,218);
	d.LINE_HOR(2,79,4,196);
	d.LINE_HOR(2,79,6,196);
	d.LINE_HOR(2,79,22,196);
	gotoxy(3,3);
	cout << " \t Flight no. " << T.FLIGHTNO(sno) ;
	gotoxy(32,3);
	cout << " \t\t LIST OF PASSANGER " ;
	textcolor(BLACK);
	textbackground(WHITE);
	gotoxy(2,5);
	cout << " \t TICKET NO. \t     NAME                      CLASS " ;
	textcolor(LIGHTGRAY);
	textbackground(BLACK);
	fstream file ;
	file.open ( "PASS.DAT" , ios::in|ios::binary ) ;
	file.seekg( 0 , ios::beg ) ;
	while ( file.read ((char * )this , sizeof(PASSANGER)))
	{
		if( sno == slno )
		{
			flag = 0 ;
			found = 1 ;
			gotoxy(5,row);
			cout << ticketno ;
			gotoxy(17,row);
			cout << " \t\t " << name ;
			len = strlen(name) ;
			for ( int i = 0 ; i < ( 20-len ) ; i++ )
				cout << " " ;
			if ( Class == 'X' )
				cout << " 		Executive " ;
			else
				cout << " 		Economic " ;
			if ( row == 21 )
			{
				flag = 1 ;
				row = 7 ;
				gotoxy(5,23);
				cout << " \n Press any key to continue "
				     << " or Press <ESC> to exit " ;
				ch = getch() ;
				if ( ch ==27 )
					break ;
				clrscr() ;
				d.BOX(1,2,80,24,218);
				d.LINE_HOR(2,79,4,196);
				d.LINE_HOR(2,79,6,196);
				d.LINE_HOR(2,79,22,196);
				gotoxy(32,3);
				cout << " \t LIST OF PASSANGER " ;
				textcolor(BLACK);
				textbackground(WHITE);
				gotoxy(2,5);
				cout << " \t TICKET NO.        NAME "
				     << " FLIGHT NO.           CLASS " ;
				textcolor(LIGHTGRAY);
				textbackground(BLACK);
			}

			else
				row++ ;
		}
	}
	if ( !found )
	{
		gotoxy(5,10);
		cout << " \t Rcords not found " ;
	}
	if ( !flag )
	{
		gotoxy(5,23);
		cout << " \n Press any key to continue... " ;
		getch() ;
	}
	file.close() ;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//FUNCTION DELETES PASSANGER RECORDS FOR THE GIVEN TICKET NO.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void PASSANGER :: DELETE_TICKET( int tno )
{
	fstream file ;
	file.open("PASS.DAT" , ios::in|ios::binary ) ;
	fstream temp ;
	temp.open("temp.dat" , ios::out|ios::binary ) ;
	file .seekg( 0 , ios::beg ) ;
	while ( !file.eof() )
	{
		file.read(( char * )this  , sizeof(PASSANGER)) ;
		if ( file.eof() )
			break ;
		if ( tno != ticketno )
			temp.write((char *)this, sizeof(PASSANGER)) ;
	}
		file.close() ;
		temp.close() ;
		file.open("PASS.DAT", ios::out|ios::binary) ;
		temp.open("temp.dat", ios::in|ios::binary) ;
		temp.seekg(0,ios::beg) ;
		while (!temp.eof() )
		{
			temp.read((char *)this, sizeof(PASSANGER)) ;
			if ( temp.eof() )
				break ;
			file.write((char *)this, sizeof(PASSANGER)) ;
		}
		file.close() ;
		temp.close() ;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNCTION DELETES ALL PASSANGER RECORDS FOR THE GIVEN FLIGHT NO.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int PASSANGER :: DELETE_FLIGHT(int sno)
{
	fstream file ;
	file.open("PASS.DAT", ios::in|ios::binary) ;
	fstream temp ;
	temp.open("temp.dat", ios::out|ios::binary) ;
	file.seekg(0,ios::beg) ;
	int found = 0 ;
	while (!file.eof() )
	{
		file.read((char *)this, sizeof(PASSANGER)) ;
		if (file.eof())
			break ;
		if ( sno != slno )
			temp.write((char *)this, sizeof(PASSANGER)) ;
		else
			found = 1 ;
	}
	file.close() ;
	temp.close() ;
	file.open("PASS.DAT", ios::out|ios::binary) ;
	temp.open("temp.dat", ios::in|ios::binary) ;
	temp.seekg(0,ios::beg) ;
	while ( !temp.eof() )
	{
		temp.read((char *)this, sizeof(PASSANGER)) ;
		if( temp.eof() )
			break ;
		file.write((char *)this, sizeof(PASSANGER)) ;
	}
	file.close() ;
	temp.close() ;
	return found ;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  FUNCTION CANCELS PASSANGER'S TICKET
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void RESERVE :: CANCELLATION(void)
{
	clrscr() ;
	char t1[10] , ch ;
	int t2 , tno , valid ;
	do
	{
		valid = 1 ;
		gotoxy(3,23);
		clreol() ;
		cout << " PRESS <ENTER> TO SEE LIST or O TO EXIT " ;
		gotoxy(3,20);
		clreol() ;
		cout << " \n Enter TICKET no. of the Passanger to cancel "
		     <<	" the Ticket " ;
		gets(t1) ;
		t2 = atoi(t1) ;
		tno = t2 ;
		if ( t1[0] == 'O' )
			return ;
		if ( strlen(t1) == 0 )
		{
			valid = 0 ;
			LIST();
			clrscr();

		}
		if (!FOUND(tno) && valid)
		{
			valid =0;
			gotoxy(3,23);
			clreol() ;
			cout << " \t Record not found " ;
			getch() ;
		}
	}
	while ( !valid ) ;
	clrscr() ;
	fstream file ;
	file.open("PASS.DAT" , ios::in | ios :: binary ) ;
	while ( file.read(( char * )this , sizeof(PASSANGER)) )
		if ( ticketno == tno )
			break ;
	file.close() ;
	int i = 1 ;
	file.open("TICKET.DAT" , ios::in | ios:: binary) ;
	while ( file.read(( char * )this , sizeof(TICKET) ))
	{
		if ( slno == i )
			break ;
		i++ ;
	}
	file.close() ;
	PASSANGER P ;
	DRAW d;
	d.BOX(15,5,66,21,'*');
	d.LINE_HOR(16,65,7,'*');
	gotoxy(33,6);
	cout << " \t TICKET no. " << tno ;
	gotoxy(17,9);
	cout << from << " \t to "  << to ;
	gotoxy(45,9);
	cout << " \t FLIGHT no. " << fltno ;
	gotoxy(20,11);
	cout << " \t PASSANGER NAME : " << P.NAME(tno) ;
	gotoxy(20,13);
	cout << " \t ADDRESS : "<< address ;
	gotoxy(20,15);
	cout << " \tSex : " << sex ;
	gotoxy(20,17);
	cout << " \tAge : " << age ;
	gotoxy(45,19);
	if ( Class == 'E' )
		cout << " \t Total Fair : " << ecofair ;
	else
		cout << " \t Total Fair : " << exefair ;
	do
	{
		gotoxy(10,23);
		clreol() ;
		cout << " \t Cancel this ticket ( y/n) : " ;
		ch = getche() ;
		ch = toupper(ch) ;
	}
	while ( ch != 'Y' && ch != 'N' ) ;
	if ( ch == 'N' )
		return ;
	DELETE_TICKET(tno) ;
	gotoxy(10,25);
	cout << " \t\t Ticket Cancelled " ;
	getch() ;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FUNCTION DISPLAYS THE PASSANGER'S INFORMATION
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void RESERVE :: DISPLAY_TICKET(void)
{
	clrscr() ;
	char t1[10] , ch ;
	int t2 , tno , valid ;
	do
	{
		valid = 1 ;
		gotoxy(3,23);
		clreol() ;
		cout << " \t PRESS <ENTER> TO SEE LIST or O TO EXIT " ;
		gotoxy(3,20);
		clreol() ;
		cout << " \t Enter Ticket no. of the Passanger " ;
		gets(t1) ;
		t2 = atoi(t1) ;
		tno = t2 ;
		if( t1[0] == '0' )
			return ;
		if( strlen(t1) == 0 )
		{
			valid = 0 ;
			LIST() ;
			clrscr() ;
		}
		if( !FOUND(tno) && valid )
		{
			valid = 0 ;
			gotoxy(3,23);
			clreol() ;
			cout << " \t Record not found " ;
			getch() ;
		}
	} while (!valid) ;
	clrscr() ;
	fstream file ;
	PASSANGER P;
	file.open("PASS.DAT", ios::in|ios::binary ) ;
	while(file.read((char *) this, sizeof(PASSANGER)))
		if ( ticketno == tno )
			break ;
	file.close() ;
	TICKET T;
	int i=1;
	file.open("TICKET.DAT",ios::in|ios::binary) ;
	while( file.read((char *) this, sizeof(TICKET)))
	{
		if( slno == i)
			break ;
			i++;
	}
	file.close() ;
	DRAW d;
	d.BOX(15,5,66,21,'*');
	d.LINE_HOR(16,65,7,'*');
	gotoxy(33,6);
	cout << " \t Ticket no. " << tno ;
	gotoxy(17,9);
	cout <<"\t"<< " from " << from << " to " <<to ;
	gotoxy(45,9);
	cout << " \t Flight no." << fltno ;
	gotoxy(20,11);
	cout << " \t Passanger Name : " <<name ;
	gotoxy(20,11);
	cout << " \t Address : " << address ;
	gotoxy(20,15);
	cout << " \t Age : " << age ;
	gotoxy(20,17);
	cout << " \t Sex : " << sex ;
	gotoxy(45,19);
	if ( Class == 'E')
		cout << " \t Total fair : " << ecofair ;
	else
		cout << " \t Total fair : " << exefair ;
	gotoxy(10,25);
	cout << " \t Press any key to continue " ;
	getch() ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//FUNCTION GIVE FLIGHT NO. TO DELETE ALL PASSANGER RECORDS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void RESERVE :: DELETE_ALL(void)
{
	clrscr() ;
	ENQUIRY();
	char t1[5] ;
	int t2, valid, sno ;
	do
	{
		valid = 1 ;
		gotoxy(3,23);
		cout << "\t\t\t \t Press <ENTER> TO EXIT " ;
		gotoxy(3,20);
		cout << " \t\t\t\t ENTER SNO. of the FLIGHT for which all passanger"
		     <<	"  records to be deleted " ;
		gets(t1) ;
		t2 = atoi(t1) ;
		sno = t2 ;
		if ( strlen(t1) == 0 )
			return ;
		if ( sno < 1 || sno > 12 )
		{
			valid = 0 ;
			gotoxy(3,23);
			cout << " \t\t\t ENTER CORRECTLY " ;
			getch() ;
		}
	} while ( !valid ) ;
	gotoxy(3,23);
	if ( !DELETE_FLIGHT(sno) )
		cout << "\n\tRecords not found. Press an key to continue" ;
	else
		cout << "\n\tRecords deleted. Press any to continue" ;
	getch() ;
}
void welcome()
{
	DRAW d;
	d.BOX(15,5,66,15,'*');
	d.LINE_HOR(16,65,7,'*');
	gotoxy(29,6);
	cout << " WELCOME TO ONS AIRWAYS " ;
	gotoxy(20,9);
	cout<<" PLEASE PRESS ENTER TO RESERVE ";
	gotoxy(27,11);
	cout<<" YOUR AIR TICKET ";
	getch() ;
}
void main_menu()
{
	cout << " \n\t------------------------ " ;
	cout << " \n\tAIR TICKET RESERVATION " ;
	cout << " \n\t------------------------ " ;
	cout << " \n\t1: RESERVATION " ;
	cout << " \n\t2: CANCELLATION " ;
	cout << " \n\t3: PASSANGER RECORDS -> " ;
	cout << " \n\t4: ENQUIRY " ;
	cout << " \n\t5: ADD FLIGHT " ;
	cout << " \n\t6: QUIT " ;

}

void edit_menu()
{
	RESERVE r;
	char opt;
	do
	{
	clrscr() ;
	cout << " \n\tEDIT PASSANGER RECORDS " ;
	cout << " -------------------------- " ;
	cout << " \n\t1: PASSANGER INFORMATION " ;
	cout << " \n\t2: DELETE " ;
	cout << " \n\t0: EXIT " ;
	cout << " \n\tENTER YOUR CHOICE  : " ;
	opt = getche() ;
	switch (opt)
	{
	   case 27 :
	   case '0' : return;
	   case '1' : r.DISPLAY_TICKET() ;
		      break;
	   case '2' : r.DELETE_ALL() ;
	}
     } while ( opt != 27 || opt != '0' );
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// THIS IS MAIN FUNCTION WHICH DISPLAY MENU AND CALLS ALL THE
// OTHER FUNCTIONS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void main()
{
	clrscr();
	clrscr() ;
	PASSANGER P ;
	TICKET ticket ;
	RESERVE r ;
	welcome();
	char ch ;
	do
	{
		clrscr() ;
		main_menu();
		cout << " \n\tENTER YOUR CHOICE " ;
		ch = getche() ;
		clrscr() ;
		switch( ch )
		{
		   case 27 :
		   case '6': return;
		   case '1': r.RESERVATION() ;
			     break;
		   case '2': r.CANCELLATION() ;
			     break;
		   case '3': edit_menu();
			     break;
		   case '4' : ticket.ENQUIRY() ;
			      getch();
			      break;
		   case '5' : ticket.ADDITION();
			      break;
		}
	} while ( ch != '6' || ch != 27 );
}

