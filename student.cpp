#include<cstdio>
#include<gdbm.h>
#include<cstring>
#include<cstdlib>
using namespace std;
class Student{
	private:
		int id,password,bookid;
		char name[25],book[25];
	public:
		Student(){}
		Student(int i, int pass,int bid , char *n , char *b){
			id=i;
			password=pass;
			bookid=bid;
			strcpy(name,n);
			strcpy(book,b);
		}
		void operator=(const Student& s){
			id=s.id;
			password=s.password;
			bookid=s.bookid;
			strcpy(name,s.name);
			strcpy(book,s.book);
		}
		 void setId(int i){id=i;}
       		 void setName(char *n){strcpy(name,n);}
       		 void setPassword(int p){password=p;}
       		 void setBookid(int bid){bookid=bid;}
       		 void setBook(char *b){strcpy(book,b);}
       		 int getId(){return id;}
       		 char *getName(){return name;}
       		 int getPassword(){return password;}
       		 int getBookid(){return bookid;}
       		 char *getBook(){return book;}
		 friend class LMS;
		 friend class CMS;
};
class Faculty{
	private:
		int id,password,bookid;
		char name[25],book[25];
	public:
		Faculty(){}
		Faculty(int i, int pass,int bid , char *n , char *b){
			id=i;
			password=pass;
			bookid=bid;
			strcpy(name,n);
			strcpy(book,b);
		}
		void operator=(const Faculty f){
			id=f.id;
			password=f.password;
			bookid=f.bookid;
			strcpy(name,f.name);
			strcpy(book,f.book);
		}
		 void setId(int i){id=i;}
       		 void setName(char *n){strcpy(name,n);}
       		 void setPassword(int p){password=p;}
       		 void setBookid(int bid){bookid=bid;}
       		 void setBook(char *b){strcpy(book,b);}
       		 int getId(){return id;}
       		 char *getName(){return name;}
       		 int getPassword(){return password;}
       		 int getBookid(){return bookid;}
       		 char *getBook(){return book;}
		 friend class FMS;
		 friend class CMS;
};
class Librarian{
	private:
		int password,sid;
		char name[25],author[25],book[25],publisher[25];
	public:
		Librarian(){}
		Librarian( int pass,int bid ,char *n, char *a , char *b,char *p){

			password=pass;
			sid=bid;
			strcpy(name,n);
			strcpy(author,a);
			strcpy(book,b);
			strcpy(publisher,p);
		}
		void operator=(const Librarian l){
		
			password=l.password;
			sid=l.sid;
			strcpy(name,l.name);
			strcpy(author,l.author);
			strcpy(book,l.book);
			strcpy(publisher,l.publisher);
		}
		 
		 void setSid(int s){sid=s;}
       		 void setName(char *n){strcpy(name,n);}
       		 void setPassword(int p){password=p;}
       		 void setAuthor(char *a){strcpy(author,a);}
       		 void setPublisher(char *p){strcpy(publisher,p);}
       		 void setBook(char *b){strcpy(book,b);}
       		 
       		 char *getName(){return name;}
       		 char *getAuthor(){return author;}
       		 char *getPublisher(){return publisher;}
       		 int getPassword(){return password;}
       		 int getSid(){return sid;}
       		 char *getBook(){return book;}
		 friend class CMS;
		 friend class LMS;
		 friend class FMS;
};
class CMS{
	private:
		GDBM_FILE db=NULL;
		datum key,value;
		char keybuf[100],valuebuf[256];
		static CMS *lInstance;
		CMS(){
			if(db==NULL){
				db=gdbm_open("CMS.db",0,GDBM_WRCREAT,0666,0);
			}
		}
	public:
		static CMS *create(){
			if(lInstance==NULL)lInstance=new CMS();
			return lInstance;
		}
		~CMS(){gdbm_close(db);}
		void addRecord(Librarian& l, int flag){
           		 sprintf(valuebuf," %d %d %s %s %s %s",l.password,l.sid,l.name,l.author,l.book,l.publisher);
           		 //printf("%s\n",valuebuf);
           		 value.dsize=strlen(valuebuf)+1;
           		 value.dptr=valuebuf;
           		 sprintf(keybuf,"%d",l.sid);
           		 key.dsize=strlen(keybuf)+1;
           		 key.dptr=keybuf;
           		 gdbm_store(db,key,value, flag);
        }
		Librarian getRecord(int sid){
           		 sprintf(keybuf,"%d",sid);
           		 key.dsize=strlen(keybuf)+1;
           		 key.dptr=keybuf;
           		 value=gdbm_fetch(db,key);
           		 int pi,id;
           		 char n[25],b[25],a[25],p[25];
           		 sscanf(value.dptr," %d %d %s %s %s %s",&pi,&id,n,a,b,p);
           		 return Librarian(pi,id,n,a,b,p);
        }
		void deleteRecord(int sid){
			sprintf(keybuf,"%d",sid);
			key.dsize=strlen(keybuf)+1;
			key.dptr=keybuf;
			gdbm_delete(db,key);
		}

		void displayAll(){
			printf("%s %3s %5s %7s %7s %7s","pass","ID","name","authore","bookname","publisher\n");
			key=gdbm_firstkey(db);
			while(key.dptr){
				value=gdbm_fetch(db,key);
				printf("%s\n",value.dptr);
				datum nextkey;
				nextkey=gdbm_nextkey(db,key);
				free(key.dptr);
				key=nextkey;
			}
			return;
		}
};

class LMS{
	private:
		GDBM_FILE db=NULL;
		datum key,value;
		char keybuf[100],valuebuf[256];
		static LMS *eInstance;
		LMS(){
			if(db==NULL){
				db=gdbm_open("LMS.db",0,GDBM_WRCREAT,0666,0);
			}
		}
	public:
		static LMS *create(){
			if(eInstance==NULL)eInstance=new LMS();
			return eInstance;
		}
		~LMS(){gdbm_close(db);}
		void addRecord(Student& s, int flag){
           		 sprintf(valuebuf,"%d %d %d %s %s",s.id,s.password,s.bookid,s.name,s.book);
           		 //printf("%s\n",valuebuf);
           		 value.dsize=strlen(valuebuf)+1;
           		 value.dptr=valuebuf;
           		 sprintf(keybuf,"%d",s.id);
           		 key.dsize=strlen(keybuf)+1;
           		 key.dptr=keybuf;
           		 gdbm_store(db,key,value, flag);
        }
		Student getRecord(int id){
           		 sprintf(keybuf,"%d",id);
           		 key.dsize=strlen(keybuf)+1;
           		 key.dptr=keybuf;
           		 value=gdbm_fetch(db,key);
           		 int i,p,bid;
           		 char n[25],b[25];
           		 sscanf(value.dptr,"%d %d %d %s %s",&i,&p,&bid,n,b);
           		 return Student(i,p,bid,n,b);
        }
		void deleteRecord(int id){
			sprintf(keybuf,"%d",id);
			key.dsize=strlen(keybuf)+1;
			key.dptr=keybuf;
			gdbm_delete(db,key);
		}

		void displayAll(){
			key=gdbm_firstkey(db);
			while(key.dptr){
				value=gdbm_fetch(db,key);
				printf("%s\n",value.dptr);
				datum nextkey;
				nextkey=gdbm_nextkey(db,key);
				free(key.dptr);
				key=nextkey;
			}
			return;
		}
};
class FMS{
	private:
		GDBM_FILE db=NULL;
		datum key,value;
		char keybuf[100],valuebuf[256];
		static FMS *fInstance;
		FMS(){
			if(db==NULL){
				db=gdbm_open("FMS.db",0,GDBM_WRCREAT,0666,0);
			}
		}
	public:
		static FMS *create(){
			if(fInstance==NULL)fInstance=new FMS();
			return fInstance;
		}
		~FMS(){gdbm_close(db);}
		void addRecord(Faculty& f, int flag){
           		 sprintf(valuebuf,"%d %d %d %s %s",f.id,f.password,f.bookid,f.name,f.book);
           		 //printf("%s\n",valuebuf);
           		 value.dsize=strlen(valuebuf)+1;
           		 value.dptr=valuebuf;
           		 sprintf(keybuf,"%d",f.id);
           		 key.dsize=strlen(keybuf)+1;
           		 key.dptr=keybuf;
           		 gdbm_store(db,key,value, flag);
        }
		Faculty getRecord(int id){
           		 sprintf(keybuf,"%d",id);
           		 key.dsize=strlen(keybuf)+1;
           		 key.dptr=keybuf;
           		 value=gdbm_fetch(db,key);
           		 int i,p,bid;
           		 char n[25],b[25];
           		 sscanf(value.dptr,"%d %d %d %s %s",&i,&p,&bid,n,b);
           		 return Faculty(i,p,bid,n,b);
        }
		void deleteRecord(int id){
			sprintf(keybuf,"%d",id);
			key.dsize=strlen(keybuf)+1;
			key.dptr=keybuf;
			gdbm_delete(db,key);
		}

		void displayAll(){
			key=gdbm_firstkey(db);
			while(key.dptr){
				value=gdbm_fetch(db,key);
				printf("%s\n",value.dptr);
				datum nextkey;
				nextkey=gdbm_nextkey(db,key);
				free(key.dptr);
				key=nextkey;
			}
			return;
		}
};
LMS *LMS::eInstance=NULL;
FMS *FMS::fInstance=NULL;
CMS *CMS::lInstance=NULL;

void addStudent(LMS *ls){
	int id,password,bookid;
	char name[25],book[25];

	printf("********************Enter the Students details*************\n");
	printf("\tEnter the student ID :\t");scanf("%d",&id);
	printf("\tEnter the student Name :\t");scanf("%s",name);
	printf("\tEnter the student password :\t");scanf("%d",&password);
	printf("\tEnter the student BookID :\t");scanf("%d",&bookid);
	printf("\tEnter the student Book name :\t");scanf("%s",book);
	Student s(id,password,bookid,name,book);
	ls->addRecord(s,GDBM_INSERT);
	printf("Record added\n");
	return;
}
void addFaculty(FMS *fs){
	int id,password,bookid;
	char name[25],book[25];

	printf("********************Enter the Faculty details*************\n");
	printf("\tEnter the Faculty ID :\t");scanf("%d",&id);
	printf("\tEnter the faculty Name :\t");scanf("%s",name);
	printf("\tEnter the faculty password :\t");scanf("%d",&password);
	printf("\tEnter the faculty BookID :\t");scanf("%d",&bookid);
	printf("\tEnter the faculty Book name :\t");scanf("%s",book);
	Faculty s(id,password,bookid,name,book);
	fs->addRecord(s,GDBM_INSERT);
	printf("Record added\n");
	return;
}
/*void addLibrarian(CMS *cs){
	int id,password;
	char name[25],author[25],book[25],publisher[25];

	printf("********************Enter the Students details*************\n");
	printf("\tEnter the  your ID :\t");scanf("%d",&id);
	printf("\tEnter the your Name :\t");scanf("%s",name);
	password=0;
	printf("\tEnter the auther name :\t");scanf("%s",author);
	printf("\tEnter the  Book name :\t");scanf("%s",book);
	printf("\tEnter the  Publishers  name :\t");scanf("%s",publisher);
	Librarian l(password,id,name,author,book,publisher);
	cs->addRecord(l,GDBM_INSERT);
	printf("Record added\n");
	return;
}*/
void addLibrarianpass(CMS *cs){
	int id,password;
	char name[25],author[25],book[25],publisher[25];

	//printf("********************Enter the Students details*************\n");
	printf("\tEnter the  ID :\t");scanf("%d",&id);
	//printf("\tEnter the requester Name :\t");scanf("%s",name);
	printf("\tEnter the  password :\t");scanf("%d",&password);
	strcpy(name,"na");
	strcpy(publisher,"na");
	strcpy(book,"na");
	strcpy(author,"na");
	Librarian l(password,id,name,author,book,publisher);
	cs->addRecord(l,GDBM_INSERT);
	printf("Record added\n");
	return;
}




void changePassword(LMS *ls){
	printf("Enter the Student id :");
	int id; scanf("%d",&id);
	Student s=ls->getRecord(id);
	int p=s.getPassword();
	printf("Enter the old password:");
	int op; scanf("%d",&op);
	if(op!=p){
		printf("Incorrect password.Enter again.\n");
		changePassword(ls);
	}
	else 
	{
		printf("****Password contain only number 0-9****\n");
aaa:		printf("Enter the new Password:");
		int p1;scanf("%d",&p1);
		printf("Enter again new Password:");
		int p2;scanf("%d",&p2);
		if(p1!=p2) {
			printf("Password not matching.Enter again.\n");
			goto aaa;
		}
		s.setPassword(p1);
		ls->addRecord(s, GDBM_REPLACE);
		printf("Password changed.\n");
	}
	return;
}
void changePassword(CMS *cs){
	printf("Enter the admin id :");
	int id; scanf("%d",&id);
	Librarian l=cs->getRecord(id);
	int p=l.getPassword();
	printf("Enter the old password:");
	int op; scanf("%d",&op);
	if(op!=p){
		printf("Incorrect password.Enter again.\n");
		changePassword(cs);
	}
	else 
	{
		printf("****Password contain only number 0-9****\n");
aaa:		printf("Enter the new Password:");
		int p1;scanf("%d",&p1);
		printf("Enter again new Password:");
		int p2;scanf("%d",&p2);
		if(p1!=p2) {
			printf("Password not matching.Enter again.\n");
			goto aaa;
		}
		l.setPassword(p1);
		cs->addRecord(l, GDBM_REPLACE);
		printf("Password changed.\n");
	}
	return;
}
void changePassword(FMS *fs){
	printf("Enter the Faculty id :");
	int id; scanf("%d",&id);
	Faculty f=fs->getRecord(id);
	int p=f.getPassword();
	printf("Enter the old password:");
	int op; scanf("%d",&op);
	if(op!=p){
		printf("Incorrect password.Enter again.\n");
		changePassword(fs);
	}
	else 
	{
		printf("****Password contain only number 0-9****\n");
aaa:		printf("Enter the new Password:");
		int p1;scanf("%d",&p1);
		printf("Enter again new Password:");
		int p2;scanf("%d",&p2);
		if(p1!=p2) {
			printf("Password not matching.Enter again.\n");
			goto aaa;
		}
		f.setPassword(p1);
		fs->addRecord(f, GDBM_REPLACE);
		printf("Password changed.\n");
	}
	return;
}

void selectNewbook(LMS *ls,int id){
	char book[25];
	int bid;
	Student s=ls->getRecord(id);
	printf("Enter new book name:");
	scanf("%s",book);
	s.setBook(book);
	printf("Enter new bookID:");
	scanf("%d",&bid);
	s.setBookid(bid);
	ls->addRecord(s,GDBM_REPLACE);
	return;
}
void selectNewbook(FMS *fs,int id){
	char book[25];
	int bid;
	Faculty f=fs->getRecord(id);
	printf("Enter new book name:");
	scanf("%s",book);
	f.setBook(book);
	printf("Enter new bookID:");
	scanf("%d",&bid);
	f.setBookid(bid);
	fs->addRecord(f,GDBM_REPLACE);
	return;
}


void showStudent(LMS *ls,int id){
	Student s=ls->getRecord(id);
	printf("Name : %s\n",s.getName());
	printf("books / journals borrowed : %s\n",s.getBook());
	printf("books / journals ID : %d\n",s.getBookid());
	return;
}
void showFaculty(FMS *fs,int id){
	Faculty f=fs->getRecord(id);
	printf("Name : %s\n",f.getName());
	printf("books / journals borrowed : %s\n",f.getBook());
	printf("books / journals ID : %d\n",f.getBookid());
	return;
}

void getStudent(CMS *cs,LMS *ls){
	printf("Enter the student ID:");
	int id; scanf("%d",&id);
	showStudent(ls,id);
	return;
}
void getFaculty(CMS *cs,FMS *fs){
	printf("Enter the Faculty ID:");
	int id; scanf("%d",&id);
	showFaculty(fs,id);
	return;
}


void requsetParchase(CMS *cs){
	int pass=0000,id;
	printf("Enter your ID:");
	scanf("%d",&id);
	printf("Enter your name:");
	char name[25]; scanf("%s",name);
	printf("Enter the book to purchase:");
	char book[25];scanf("%s",book);
	printf("Enter the Author name:");
	char author[25]; scanf("%s",author);
	printf("Enter the Publisher of book:");
	char publisher[25]; scanf("%s",publisher);
	Librarian l(pass,id,name,author,book,publisher);
	cs->addRecord(l,GDBM_INSERT);
        printf("Request send\n");
        return;
}
void deleteRequest(CMS *cs){
	printf("Enter ID of rquest to reject: ");
	int id ; scanf("%d",&id);
	cs->deleteRecord(id);
	printf("Record deleted\n");
	return ;
}

void displayStudents(LMS *ls){
	printf("Students in the library database : \n ");
	ls->displayAll();
	return;
}
void displayFaculty(FMS *fs){
	printf("Students in the library database : \n ");
	fs->displayAll();
	return;
}
void displayRequest(CMS *cs){
	printf("Request in the library database : \n ");
	cs->displayAll();
	printf("Press 1 to approve request,2 to reject request:");
	int c;scanf("%d",&c);
	if(c==2)deleteRequest(cs);
	return;
}



void deleteStudent(LMS *ls){
	printf("Enter ID of employee to be deleted ");
	int id ; scanf("%d",&id);
	ls->deleteRecord(id);
	printf("Record deleted\n");
	return ;
}
void deleteFaculty(FMS *fs){
	printf("Enter ID of employee to be deleted ");
	int id ; scanf("%d",&id);
	fs->deleteRecord(id);
	printf("Record deleted\n");
	return ;
}






void student(LMS *ls,CMS *cs,int id){
	Student s=ls->getRecord(id);
	printf("\n");
	printf("Welcome %s \n\n",s.getName());
	printf("Press 1 to change password,press 2 to select new book,press 3 to view your details  and 4 to request book:");
	int choice;
	while(true){
		scanf("%d",&choice);
		if(choice==1)changePassword(ls);
		else if(choice==2)selectNewbook(ls,id);
		else if(choice==3)showStudent(ls,id);
		else if(choice==4)requsetParchase(cs);
		else break;
	}
}
void librarian(CMS *cs,LMS *ls,FMS *fs){
	//Student s=ls->getRecord(id);
	printf("\n");
	//printf("Welcome %s \n\n",s.getName());
	printf("Press 1 to change password,press 2 to add sutdent record,press 3 to add faculty record  and 5 to see requests,6 to delete s record,7 to delete f record,8 to show student details,9 to show faculty details\n");
	int choice;
	while(true){
		scanf("%d",&choice);
		if(choice==1)changePassword(cs);
		else if(choice==2)addStudent(ls);
		else if(choice==3)addFaculty(fs);
		else if(choice==6)deleteStudent(ls);
		else if(choice==7)deleteFaculty(fs);
		else if(choice==5)displayRequest(cs);
		else if(choice==8)getStudent(cs,ls);
		else if(choice==9)getFaculty(cs,fs);
		else break;
	}
}
void faculty(FMS *fs,CMS *cs,int id){
	Faculty f=fs->getRecord(id);
	printf("\n");
	printf("Welcome %s \n\n",f.getName());
	printf("Press 1 to change password,press 2 to select new book,press 3 to view your details  and 4 to request purchase\n");
	int choice;
	while(true){
		scanf("%d",&choice);
		if(choice==1)changePassword(fs);
		else if(choice==2)selectNewbook(fs,id);
		else if(choice==3)showFaculty(fs,id);
		else if(choice==4)requsetParchase(cs);
		else break;
	}
}


void checkPassword(LMS *ls,CMS *cs){
	printf("Enter student ID :\t");
	int id; scanf("%d",&id);
	Student s=ls->getRecord(id);
	int p=s.getPassword();
bbb:	printf("Enter the password:\t");
	int p1; scanf("%d",&p1);
	if(p1!=p){
		printf("Password incorrect.");
		printf("Enter password again.\n");
		goto bbb;
	}
	else
		student(ls,cs,id);
	
	return;
}
void checkPassword(FMS *fs,CMS *cs){
	printf("Enter faculty ID :\t");
	int id; scanf("%d",&id);
	Faculty f=fs->getRecord(id);
	int p=f.getPassword();
bbb:	printf("Enter the password:\t");
	int p1; scanf("%d",&p1);
	if(p1!=p){
		printf("Password incorrect.");
		printf("Enter password again.\n");
		goto bbb;
	}
	else 
		faculty(fs,cs,id);
	return;
}
void checkPassword(CMS *cs,LMS *ls,FMS *fs){
	printf("Enter  ID :\t");
	int id; scanf("%d",&id);
	Librarian l=cs->getRecord(id);
	int p=l.getPassword();
bbb:	printf("Enter the password:\t");
	int p1; scanf("%d",&p1);
	if(p1!=p){
		printf("Password incorrect.");
		printf("Enter password again.\n");
		goto bbb;
	}
	else 
		librarian(cs,ls,fs);
	return;
}




int main(){
	LMS *ls=LMS::create();
	FMS *fs=FMS::create();
	CMS *cs=CMS::create();
	printf("####options 2-4 are only for adim ,here its used for testing####\n\n");
	printf("Press 1 for student login,2 for faculty login,3 to  librarian login,4  :\t");
	int q;
	while(true){
		scanf("%d",&q);
		if(q==1)checkPassword(ls,cs);
		else if(q==2)checkPassword(fs,cs);
		else if(q==3)checkPassword(cs,ls,fs);
		else if(q==4)addLibrarianpass(cs);
		else break;


	}
	return 0;
}



	
                  




	


