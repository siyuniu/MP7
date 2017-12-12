# include <string.h>
# include <stdlib.h>
#include<iostream>
#include <fstream>
using namespace std;
//---------------------- Book---------------------------------------------------------


class Book	             // A book's inventory records
{
    char bookNo[15]; 	     //book number
    char bookName[10];	 //book numer 
    int  Num;		     //number of inventory
public:
    Book(char *bNo=NULL, char *bNa=NULL, int n=0);	//construct the function
    void Show();				                   //display book information
    
    void setInfo(char *nop, char *nap, int n);	       //set inventory records information
    void setNum(int n);			                   //set the number of inventory
    int getNum();			                       //get the number of inventory
    friend class bookList;	                       //make bookList a friend class
   
};

Book::Book(char *bNo, char *bNa, int n)
{
	if (bNo)
		strcpy(bookNo, bNo);
	else
		bookNo[0]='\a';
	if (bNa)
		strcpy(bookName, bNa);
	else
		bookName[0]='\0';

	Num=n;
}


void Book::Show()
{
	cout << bookNo << '\t' << bookName << '\t' << Num << endl;
}





void Book::setInfo(char *nop, char *nap, int n)
{
	strcpy(bookNo, nop);
	strcpy(bookName, nap);
	Num=n;
}


void Book::setNum(int n)
{
	Num=n;
}


int Book::getNum()
{
	return Num;
}

//----------------------- bookList----------------------------------------------------


class bookList	                                 //book inventory records table(linear)
{
    Book *Books;	                             //pointer
    int curLen;	                                 //current number of books
    int maxLen;	                                 //max length
public:
    bookList(int Len=20);	                     //construct the function and initialize book list
    ~ bookList ( ); 	                         //destructor, release space
    void appendBook(char *nop,char *nap, int n); //add book to book list
    int isIn(char *bkNo);	                     //find the book based on book number
    Book & getBooks(int i);		                 //return the book with its stock
    void deleteBook(char * bkNo);	             //delete a book with specific book number
    void sortBooks();                            //sort books based on book number 
	
    void showAll( );	                         //display all books
    
    
};


bookList::bookList(int Len)
{
	maxLen = Len;
	curLen = 0;

	if (Len)
		Books = new Book[Len];
	else
		Books = NULL;
}


bookList::~ bookList ( )
{
	if (Books) delete []Books;
}


void bookList::appendBook(char *nop, char *nap, int n)     // add the input book to book list
{
	if (curLen==maxLen)                             // if full
	{
		Book *newptr;
		
		newptr = new Book[maxLen+10];    // apply for additional linear space

		for (int i=0; i<curLen; i++)
			newptr[i] = Books[i];           // deep copy the elements from original linear list to new linear list

		delete[ ]Books;                    // release original linear list space
		maxLen += 10;
		Books = newptr;                   // change the pointer 
	}
	strcpy(Books[curLen].bookNo, nop);
	strcpy(Books[curLen].bookName, nap);
	Books[curLen].Num=n;

	curLen++;
}


int bookList::isIn(char *bkNo)
{
	for(int i=0; i<curLen; i++)
		if ( strcmp(bkNo, Books[i].bookNo)==0)
			return i;

    return -1;
}


Book & bookList::getBooks(int i)
{
	return Books[i];                   
}


void bookList::deleteBook(char * bkNo)    
{
	int i, j;

	if((i=isIn(bkNo))  > -1)
	{
		for (j=i; j<curLen-1; j++)
			Books[j]=Books[j+1];
		curLen--;

	}
	else
		cout << "Book does not exist!" << endl;
}


void bookList::sortBooks()                     //sort books based on book number 
{
	Book t;
	int p, i, j;

	for (i=0; i<curLen; i++)
	{
		p=i;
		for(j=i+1; j<curLen; j++)
			if (strcmp(Books[j].bookNo,Books[p].bookNo)<0)
				p=j;
		if (p!=i)
		{
			t=Books[i]; Books[i]=Books[p]; Books[p]=t;
		}
	}
}





void bookList::showAll()
{
	if (curLen==0)
	{
		cout << "Empty inventory" << endl;
		return;
	}

	for (int i=0; i<curLen; i++)
		Books[i].Show();
	cout << endl;

}












//------------------------main function-------------------------


void appendRecord(bookList &booksObj)
{
	char no[20], name[20];
	int num;
	cout << "Please enter the book's information (book number book name quantity)";
	cin >> no >> name >> num;
	booksObj.appendBook(no, name, num);
}


void delRecord(bookList &booksObj)
{
	char no[20], ans;
	int i;

	cout << "Please enter the book number of the book you want to delete";
	cin >> no;
	if((i=booksObj.isIn(no)) > -1)
	{
		cout << "The book is:";
		booksObj.getBooks(i).Show();
		cout << "Are you sure to delete? y/n: ";
		cin >> ans;
		if(ans=='y')
		{
			booksObj.deleteBook(no);
			cout << "Deleted" << endl;

		}
	}
	else
		cout << "Book does not exist!" << endl;
}


void showAll(bookList &booksObj)
{
	booksObj.showAll();
}


void query(bookList &booksObj)
{  
	char no[20];
	int i;
	cout << "Please enter the book number: ";
	cin >> no;
	if (( i=booksObj.isIn(no)) > -1)
	{
		cout << "The book is: ";
		booksObj.getBooks(i).Show();
	}
	else
		cout << "Book does not exist!" << endl;

}


void addBooks(bookList &booksObj)
{
	char no[20],name[20];
	int i,num;

	cout << "Please enter the book number and the quantity" ;
	cin >> no >> num;
	if((i=booksObj.isIn(no)) > -1)
	{
		int oldnum=booksObj.getBooks(i).getNum();
		booksObj.getBooks(i).setNum(oldnum+num);
	}
	else
	{
		cout << "Book does not exist, please enter the book name: ";
		cin >> name;
		booksObj.appendBook(no,name,num);
	}
}


void sellBooks(bookList &booksObj)
{
	char no[20];
	int i, num;

	cout << "Please enter the book number: ";
	cin >> no >> num;
	if ((i=booksObj.isIn(no)) > -1)
	{
		int oldnum=booksObj.getBooks(i).getNum();     //booksObj.books[i].getNum()
		if (oldnum<num)
			cout << "Not enough inventory!" << endl;
		else
		{
			booksObj.getBooks(i).setNum(oldnum-num);
		}
	}
	else
		cout << "Book does not exist!" << endl;
}










void sortByNo(bookList &booksObj)
{
	booksObj.sortBooks();
}







//--------------------------main function and the definition of menu function------------------------------------------

int menu_select( );                      

int main()
{   
	
	bookList   booksObj;                  // define book list object 
    int sel;
    
	

    
	for (   ;   ;   )
    {   
		switch(  sel = menu_select()  ) 
        {	
		case 1: appendRecord(booksObj);         
			system("pause");   break;
	
		case 2: delRecord(booksObj);              
			system("pause");    break;
 	
		case 3: showAll(booksObj);                  
			system("pause");    break;
 	
		case 4: query(booksObj);                    
			system("pause");    break;
	
		case 5: addBooks(booksObj); 	          
			system("pause");    break;
	
		case 6: sellBooks(booksObj);  	          
			system("pause");    break;
	
		
	
		
	
		
        }
        if(sel==0)    
			break;  
    }
}


int menu_select( )                            
{    
	char *menu[ ]={   
	                 "   1.	Add book record",
                     "   2.	Delete book record",
		             "   3.	Display all books' record",
		             "   4.	Search book",
		             "   5.	Put book in inventory",
		             "   6.	Delete all books' record",
		            
		             NULL   
                   };




    int choice;

    do {	
		system("cls");                              //  clear the screen   
	    cout<<"\n\n ==============book record management============== \n\n";
	    for(int i=0; menu[i]; i++)      cout<<menu[i]<<endl;
	        cout<<"\n ======================================= \n";
	    
			
		cout<<"Please enter selection";
	    cin>>choice;
    } while(choice<0 || choice>8);
      
	return(choice);
}
