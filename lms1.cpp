#include<cstdio>
#include<gdbm.h>
#include<cstring>
#include<cstdlib>
using namespace std;
class Student{
	private:
		int id,password,bookid,rbook,message;
		char name[25],book[25];
	public:
		Student(){}
		Student(int i,char *n, int pass,int bid,char *b ,int s,int rb){
			id=i;
			password=pass;
			rbook=rb;
			bookid=bid;
			message=s;
			strcpy(name,n);
			strcpy(book,b);
		}
		void operator=(const Student& s){
			id=s.id;
			rbook=s.rbook;
			message=s.message;
			password=s.password;
			bookid=s.bookid;
			strcpy(name,s.name);
			strcpy(book,s.book);
		}
		 void setId(int i){id=i;}
		 void setRbook(int rb){rbook=rb;}
		 void setMessage(int s){message=s;}
       		 void setName(char *n){strcpy(name,n);}
       		 //void setMessege(char *m){strcpy(messege,m);}
       		 void setPassword(int p){password=p;}
       		 void setBookid(int bid){bookid=bid;}
       		 void setBook(char *b){strcpy(book,b);}
       		 //void setReser(char *r){strcpy(reser,r);}


       		 int getId(){return id;}
       		 int getRbook(){return rbook;}
       		 char *getName(){return name;}
       		 int getMessage(){return message;}
       		 int getPassword(){return password;}
       		 int getBookid(){return bookid;}
       		 char *getBook(){return book;}
       		 //char *getReser(){return reser;}
		 friend class LMS;
		 friend class CMS;
		 friend class LRMS;
};
class Faculty{
	private:
		int id,password,bookid,rbook,message;
		char name[25],book[25];
	public:
		Faculty(){}
		Faculty(int i,char *n, int pass,int bid ,char *b,int rid, int m){
			id=i;
			password=pass;
			rbook=rid;
			message=m;
			bookid=bid;
			strcpy(name,n);
			strcpy(book,b);
		}
		void operator=(const Faculty f){
			id=f.id;
			password=f.password;
			rbook=f.rbook;
			message=f.message;
			bookid=f.bookid;
			strcpy(name,f.name);
			strcpy(book,f.book);
		}
		 void setId(int i){id=i;}
		 void setRbook(int rid){rbook=rid;}
		 void setMessage(int m){message=m;}
       		 void setName(char *n){strcpy(name,n);}
       		 void setPassword(int p){password=p;}
       		 void setBookid(int bid){bookid=bid;}
       		 void setBook(char *b){strcpy(book,b);}


       		 int getId(){return id;}
       		 int getRbook(){return rbook;}
       		 int getMessage(){return message;}
       		 char *getName(){return name;}
       		 int getPassword(){return password;}
       		 int getBookid(){return bookid;}
       		 char *getBook(){return book;}
		 friend class FMS;
		 friend class CMS;
		 friend class LRMS;
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
		 friend class LRMS;
};
class Book{
    private:
        int id,copy;
        char name[50],auname[50],subject[50];
    public:
        Book(){}
        Book(int i, char *n, char *e, char *r,int c){
            id=i;
            strcpy(name,n);
            strcpy(subject,e);
            strcpy(auname,r);
            copy=c;
        }
        void operator=(const Book& e){
            id=e.id;
            strcpy(name,e.name);
            strcpy(subject,e.subject);
            strcpy(auname,e.auname);
            copy=e.copy;
        }
        void setId(int i){id=i;}
        void setName(char *n){strcpy(name,n);}
        void setsubject(char *e){strcpy(subject,e);}
        void setauname(char *r){strcpy(auname,r);}
        void setcopy(int c){copy=c;}
        int getId(){return id;}
        char *getName(){return name;}
        char *getsubject(){return subject;}
        char *getauname(){return auname;}
        int getcopy(){return copy;}
	friend class LRMS;
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
           		 sprintf(valuebuf,"%d\t%s\t\t%d\t\t%d\t%s\t\t%d\t%d",s.id,s.name,s.password,s.bookid,s.book,s.rbook,s.message);
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
           		 int i,p,bid,rb,m;
           		 char n[25],b[25];
           		 sscanf(value.dptr,"%d %s %d %d %s %d %d",&i,n,&p,&bid,b,&rb,&m);
           		 return Student(i,n,p,bid,b,rb,m);
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
		void displayStudents(){
			key=gdbm_firstkey(db);
   	        		value=gdbm_fetch(db,key);
      		while(key.dptr){
	    		value=gdbm_fetch(db,key);
	    		//printf("%s:",key.dptr);
	   		printf("%s\n",value.dptr);
	    		datum nextkey;
	    		nextkey=gdbm_nextkey(db,key);
	    		free(key.dptr);
	    		key=nextkey;
    }

		}


		int *searchId(int id){
                key=gdbm_firstkey(db);
                static int ib[20];
		int j=0;
		

                while(key.dptr){
                        value=gdbm_fetch(db,key);
			int i,p,bid,rb,m;
                         char n[25],b[25];
                         sscanf(value.dptr,"%d %s %d %d %s %d %d",&i,n,&p,&bid,b,&rb,&m);


                        bool t;
                        t=(id==bid);
			if(t==1){	
				ib[j]=i;
			        j++;
			}
			datum nextkey;
			nextkey=gdbm_nextkey(db,key);
			free(key.dptr);
			key=nextkey;
		}
		return ib;
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
           		 sprintf(valuebuf,"%d\t\%s\t\%d\t%d\t%s\t%d\t%d",f.id,f.name,f.password,f.bookid,f.book,f.rbook,f.message);
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
           		 int i,p,bid,rid,m;
           		 char n[25],b[25];
           		 sscanf(value.dptr,"%d %s %d %d %s %d %d",&i,n,&p,&bid,b,&rid,&m);
           		 return Faculty(i,n,p,bid,b,rid,m);
               
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
			void displayFaculities(){
			key=gdbm_firstkey(db);
   	        		value=gdbm_fetch(db,key);
      		while(key.dptr){
	    		value=gdbm_fetch(db,key);
	    		//printf("%s:",key.dptr);
	   		printf("%s\n",value.dptr);
	    		datum nextkey;
	    		nextkey=gdbm_nextkey(db,key);
	    		free(key.dptr);
	    		key=nextkey;
    }

		}
		int *searchId(int id){
                key=gdbm_firstkey(db);
                static int ib[20];
		int j=0;

                while(key.dptr){
                        value=gdbm_fetch(db,key);
			int i,p,bid,rb,m;
                         char n[25],b[25];
                         sscanf(value.dptr,"%d %s %d %d %s %d %d",&i,n,&p,&bid,b,&rb,&m);


                        bool t;
                        t=(id==bid);
			if(t==1){	
				ib[j]=i;
			        j++;
			}
			datum nextkey;
			nextkey=gdbm_nextkey(db,key);
			free(key.dptr);
			           key=nextkey;
                }

                return ib;
                }

	
};
class LRMS{
    private:
        GDBM_FILE db=NULL;
        datum key,value;
        char keybuf[100],valuebuf[256];
        static LRMS *tInstance;
        LRMS(){
            if(db==NULL){
                db=gdbm_open("LRMS.db",0,GDBM_WRCREAT,0666,0);
            }
        }
    public:
        static LRMS *create(){
            if(tInstance==NULL)tInstance=new LRMS();
            return tInstance;
        }
        ~LRMS(){gdbm_close(db);}
        void addRecord(Book& e, int flag){
            printf("ID \t Book Title \t Cateogary \t Author Name \t No.of copies Available");
            sprintf(valuebuf,"\n%d \t %s \t %s \t \t%s \t\t %d",e.id,e.name,e.subject,e.auname,e.copy);
            printf("%s\n",valuebuf);
            value.dsize=strlen(valuebuf)+1;
            value.dptr=valuebuf;
            sprintf(keybuf,"%d",e.id);
            key.dsize=strlen(keybuf)+1;
            key.dptr=keybuf;
            gdbm_store(db,key,value, flag);
        }
        Book getRecord(int id){
            sprintf(keybuf,"%d",id);
            key.dsize=strlen(keybuf)+1;
            key.dptr=keybuf;
            value=gdbm_fetch(db,key);
            int i,c;
            char n[50],e[50],r[50];
            //printf("ID \t Book Title \t Cateogary \t Author Name \t No.of copies Available");
            sscanf(value.dptr,"%d \t %s \t %s \t %s \t %d",&i,n,e,r,&c);
            return Book(i,n,e,r,c);
        }
        void deleteRecord(int id){
            sprintf(keybuf,"%d",id);
            key.dsize=strlen(keybuf)+1;
            key.dptr=keybuf;
            gdbm_delete(db,key);
        }
        void disp(){
    	    key=gdbm_firstkey(db);
   	        value=gdbm_fetch(db,key);
      while(key.dptr){
	    value=gdbm_fetch(db,key);
	    //printf("%s:",key.dptr);
	   printf("%s\n",value.dptr);
	    datum nextkey;
	    nextkey=gdbm_nextkey(db,key);
	    free(key.dptr);
	    key=nextkey;
    }

	}


    int searchRecord(char s[]){
       key=gdbm_firstkey(db);
       int id=0;

    while(key.dptr){
            value=gdbm_fetch(db,key);
            int i,c;
            char n[50],e[50],r[50];
            sscanf(value.dptr,"\n %d \t %s \t %s \t %s \t %d",&i,n,e,r,&c);
           // printf("%s\n",n);
            bool t;
	   t=strcmp(s,n);
	 //  cout<<t<<endl;
	   if(t==0){id=i;}
        datum nextkey;
	nextkey=gdbm_nextkey(db,key);
	free(key.dptr);
	key=nextkey;
		
      }
		return id;
        }
int searchauRecord(char s[]){
       key=gdbm_firstkey(db);
       int p=0;

    while(key.dptr){
            value=gdbm_fetch(db,key);
            int i,c;
            char n[50],e[50],r[50];
            sscanf(value.dptr,"\n %d \t %s \t %s \t %s \t %d",&i,n,e,r,&c);
            bool t,u;
	   t=strcmp(s,r);
	   //cout<<endl;
	   if(t==0){p=1;printf("\n\nID \t Book Title \t Cateogary \t Author Name \t No.of copies Available");printf("\n____________________________________________________________________________\n");printf("%s\n",value.dptr); }
	  u=strcmp(s,e);
	   //cout<<endl;
	   if(u==0){p=1;printf("\n\nID \t Book Title \t Cateogary \t Author Name \t No.of copies Available");printf("\n____________________________________________________________________________\n");printf("%s\n",value.dptr); }
        datum nextkey;
	nextkey=gdbm_nextkey(db,key);
	free(key.dptr);
	key=nextkey;
		
      }
		return p;
}
};
LMS *LMS::eInstance=NULL;
FMS *FMS::fInstance=NULL;
CMS *CMS::lInstance=NULL;
LRMS *LRMS::tInstance=NULL;

void addStudent(LMS *ls){
	int id,password,bookid;
	char name[25],book[25];

	printf("********************Enter the Students details*************\n");
	printf("\tEnter the student ID :\t");scanf("%d",&id);
	printf("\tEnter the student Name :\t");scanf("%s",name);
	printf("\tEnter the student password :\t");scanf("%d",&password);
	printf("\tEnter the student BookID :\t");scanf("%d",&bookid);
	printf("\tTitle of Book Issued :\t");scanf("%s",book);
	int  message=0;
	//char reser[20];strcpy(reser,"NA");
	int rbook=0000;
	Student s(id,name,password,bookid,book,rbook,message);
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
	int message=0;
	int rbook=0000;
	Faculty s(id,name,password,bookid,book,rbook,message);
	fs->addRecord(s,GDBM_INSERT);
	printf("Record added\n");
	return;
}
void sentReservation(LMS *ls, LRMS *ms,FMS *fs,int id,int sid){
        int *p=ls->searchId(id);
	int *q=fs->searchId(id);
        for(int i=0;i<20;i++){
                if(p[i]!=0){
			//printf("%d",p[i]);
                        Student s=ls->getRecord(p[i]);
                        int msg=1;  
                        s.setMessage(msg);
                        ls->addRecord(s, GDBM_REPLACE);
			//printf("%d",s.getMessage());
                }
        }

	for(int k=0;k<20;k++){
                if(q[k]!=0){
                        //printf("%d",p[i]);
                        Faculty f=fs->getRecord(q[k]);
                        int msg=1;
                        f.setMessage(msg);
                        fs->addRecord(f, GDBM_REPLACE);
                        //printf("%d",s.getMessage());
                }
        }



        printf("Reservation sent to Bookholders\n");
	Student s=ls->getRecord(sid);
	s.setRbook(id);
	ls->addRecord(s,GDBM_REPLACE);


        return;
}

void sentReservation(FMS *fs, LRMS *ms,LMS *ls,int id,int sid){
        int *p=fs->searchId(id);
	int *q=ls->searchId(id);
        for(int i=0;i<20;i++){
                if(p[i]!=0){
                        Faculty f=fs->getRecord(p[i]);
                        int msg=1;
                        f.setMessage(msg);
                        fs->addRecord(f, GDBM_REPLACE);
                }
        }

	 for(int k=0;k<20;k++){
                if(q[k]!=0){
                        //printf("%d",p[i]);
                        Student s=ls->getRecord(q[k]);
                        int msg=1;
                        s.setMessage(msg);
                        ls->addRecord(s, GDBM_REPLACE);
                        //printf("%d",s.getMessage());
                }
        }

	 printf("Reservation sent to Bookholders\n");
        Faculty f=fs->getRecord(sid);
        f.setRbook(id);
        fs->addRecord(f,GDBM_REPLACE);


        return;
}




void cancelReservation(LMS *ls,int id,FMS *fs,int sid){
        int *p=ls->searchId(id);
	int *q=fs->searchId(id);
        for(int i=0;i<20;i++){
                if(p[i]!=0){
			//printf("%d",p[i]);
                        Student s=ls->getRecord(p[i]);
                        int msg=0;  
                        s.setMessage(msg);
                        ls->addRecord(s, GDBM_REPLACE);
			//printf("%d",s.getMessage());

                }
        }

	 for(int k=0;k<20;k++){
                if(q[k]!=0){
                        //printf("%d",p[i]);
                        Faculty f=fs->getRecord(q[k]);
                        int msg=0;
                        f.setMessage(msg);
                        fs->addRecord(f, GDBM_REPLACE);
                        //printf("%d",s.getMessage());
                }
        }



	//printf("%d",s.getMessage());
	printf("Reservation Canceled.\n");
	Student s=ls->getRecord(sid);
        s.setRbook(0000);
        ls->addRecord(s,GDBM_REPLACE);
}
void cancelReservation(FMS *fs,int id,LMS *ls,int sid){
        int *p=fs->searchId(id);
	int *q=ls->searchId(id);
        for(int i=0;i<20;i++){
                if(p[i]!=0){
                        Faculty f=fs->getRecord(p[i]);
                        int msg=0;  
                        f.setMessage(msg);
                        fs->addRecord(f, GDBM_REPLACE);
                }
        }

	 for(int k=0;k<20;k++){
                if(q[k]!=0){
                        //printf("%d",p[i]);
                        Student s=ls->getRecord(q[k]);
                        int msg=0;
                        s.setMessage(msg);
                        ls->addRecord(s, GDBM_REPLACE);
                        //printf("%d",s.getMessage());
                }
        }



	printf("Reservation Canceled.\n");
	Faculty f=fs->getRecord(sid);
        f.setRbook(0000);
        fs->addRecord(f,GDBM_REPLACE);
}

	

void showReservation(LMS *ls,FMS *fs,int id,int sid){
	Student s=ls->getRecord(sid);
	int p=s.getRbook();
	if(p!=0000)printf("You had sent a reservation.  bookid(%d)\n",p);
	else printf("No reservation request.\n");
	if(p!=0000){
	printf("Do you want to cancel reservation?(Press 1 to yes/2 for No):");
	int d; scanf("%d",&d);
	if(d==1)cancelReservation(ls,id,fs,sid);
	else return;
	}
	else return;
}

void showReservation(FMS *fs,LMS *ls,int id,int sid){
        Faculty f=fs->getRecord(sid);
        int p=f.getRbook();
        if(p!=0000)printf("You had sent a reservation.  bookid(%d)\n",p);
       else printf("No reservation request.\n");
        if(p!=0000){
        printf("Do you want to cancel reservation?(Press 1 to yes/2 for No):");
        int d; scanf("%d",&d);
        if(d==1)cancelReservation(fs,id,ls,sid);
        else return;
        }
        else return;
}




void addLibrarianpass(CMS *cs){
	int id,password;
	char name[25],author[25],book[25],publisher[25];

	//printf("********************Enter the Students details*************\n");
	printf("\n\tEnter the  ID :\t");scanf("%d",&id);
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
void addBook(LRMS *ms){
    int id,copy;
    char name[50], subject[50], auname[50];
	printf("Enter Book details\n");
    	printf("ID -"); scanf("%d",&id);
    	printf(" Book Title -"); 
    	
    	scanf("%s",name);
    	printf("Subject / Department -"); 
   	
   	scanf("%s",subject);
    	printf("Author name - "); //fgets(auname,50,stdin);
    	
    	scanf("%s",auname);
	printf("No. of Copies Available : ");
	scanf("%d",&copy);    
    	Book e(id, name,subject, auname,copy);
    	ms->addRecord(e, GDBM_INSERT);
    	printf("Record added\n");
    	return;
}

void modifyBook(LRMS *ms){
    printf("Enter id of Book to be modified \n");
    int id; scanf("%d",&id);
    Book e=ms->getRecord(id);
    printf("Edit the number of copy");
    int p; scanf("%d",&p);
    e.setcopy(p);
    ms->addRecord(e, GDBM_REPLACE);
    printf("Record modified\n");
    return;
}
void deleteBook(LRMS *ms){
    printf("Enter id of Book to be delete");
    int id; scanf("%d",&id);
    ms->deleteRecord(id);
    printf("Record deleted\n");
    return;
}
void displayBook(LRMS *ms){
    printf("Enter Book id to display ");
    int id; scanf("%d",&id);
    Book e=ms->getRecord(id);
    printf("\n%d \t %s \t %s \t %s \t %d\n",e.getId(),e.getName(),e.getsubject(),e.getauname(),e.getcopy());
    return;
}
void dispBook(LRMS *ms){
    printf("Books in the libray display \n ");
    printf("ID \t Book Title \t Cateogary \t Author Name \t No.of copies Available");    		printf("\n..........................................................................................................\n");
    ms->disp();
    return;
    }
void search(LRMS *ms){
	printf("Books name want to search \n ");
	char s[50];
	int p;
	scanf("%s",s);
	p=ms->searchRecord(s);
	Book e=ms->getRecord(p);
        printf("\n %d \t %s \t %s \t %s \t %d \n",e.getId(),e.getName(),e.getsubject(),e.getauname(),e.getcopy());	
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

void selectNewbook(LRMS *ms,LMS *ls,FMS *fs,int id){
	int bid,c,s;
a1:	printf("Enter new bookID:");
	scanf("%d",&bid);
	Book e=ms->getRecord(bid);
	printf("\n %d \t %s \t %s \t %s \t %d \n",e.getId(),e.getName(),e.getsubject(),e.getauname(),e.getcopy());
	if(e.getcopy()==0){
		printf("No copy is available\n");
		printf("Do you want to sent Reservation to bookholders ? (press 1 for yes ,2 for no)");
		scanf("%d",&s);
		if(s==1){sentReservation(ls,ms,fs,e.getId(),id);return;}
		else if(s==2)selectNewbook(ms,ls,fs,id) ;
	}
	//if(e.getcopy()==0){printf("No copy is available\n");return;}		
        printf("Enter 1 to add book ");
        scanf("%d",&c);
        if(c==1){
        	Student s=ls->getRecord(id);
        	if(s.getBookid()==bid){printf("You have taken this book\n");goto a1;}
        	if(e.getcopy()==0){printf("No copy is available\n");goto a1;}
       		else{
       		if(s.getBookid()!=0){
        		Book e1=ms->getRecord(s.getBookid());
        		e1.setcopy(e1.getcopy()+1);
        		ms->addRecord(e1, GDBM_REPLACE);}
        		e.setcopy(e.getcopy()-1);
        		ms->addRecord(e, GDBM_REPLACE);
        		s.setBookid(e.getId());
        		s.setBook(e.getName());
        		ls->addRecord(s, GDBM_REPLACE);
        		
        		}
        	}	
        else
tt:	return;
}

void selectNewbook(LRMS *ms,FMS *fs,LMS *ls,int id){
	int bid,c;
a2:	printf("Enter new bookID:");
	scanf("%d",&bid);
	Book e=ms->getRecord(bid);
	printf("\n %d \t %s \t %s \t %s \t %d \n",e.getId(),e.getName(),e.getsubject(),e.getauname(),e.getcopy());
 	if(e.getcopy()==0){
                printf("No copy is available\n");
                printf("Do you want to sent Reservation to bookholders ? (press 1 for yes ,2 for no)");
               int s; scanf("%d",&s);
                if(s==1){sentReservation(fs,ms,ls,e.getId(),id);}
                else if(s==2)selectNewbook(ms,fs,ls,id) ;
        }
	//if(e.getcopy()==0){printf("No copy is available\n");return;}
        printf("Enter 1 to add- ");
        scanf("%d",&c);
        if(c==1){
        	Faculty f=fs->getRecord(id);
        	if(f.getBookid()==bid){printf("You have taken this book\n");goto a2;}
        	if(e.getcopy()==0){printf("No copy is available\n");goto a2;}
       		else{
       		if(f.getBookid()!=0){
        		Book e1=ms->getRecord(f.getBookid());
        		e1.setcopy(e1.getcopy()+1);
        		ms->addRecord(e1, GDBM_REPLACE);}
        		e.setcopy(e.getcopy()-1);
        		ms->addRecord(e, GDBM_REPLACE);
        		f.setBookid(e.getId());
        		f.setBook(e.getName());
        		fs->addRecord(f, GDBM_REPLACE);
        		}
        	}	
        else
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
void getBookdetails(LRMS *ms){
	printf("\nPress \n \t1 to add Book \n 2 to modify Book \n 3 to delete Book \n 4 to display Book \n 5 to print the list of books\n 6 to search book by name and any other key to quit\n");
    int choice;
    while(true){
        scanf("%d",&choice);
        if(choice==1)addBook(ms); 
        else if(choice==2)modifyBook(ms);
        else if(choice==3)deleteBook(ms);
        else if(choice==4)displayBook(ms);
        else if(choice==5)dispBook(ms);
        else if(choice==6)search(ms);
        else break;
    }
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
void approveRequest(CMS *cs,LRMS *ms){
	printf("Enter the ID of requester to approve:");
	int id; scanf("%d",&id);
	Librarian l=cs->getRecord(id);
	printf("Enter the ID for New Book:");
	int iid; scanf("%d",&iid);
	char name[20]; strcpy(name,l.getAuthor());
	printf("Enter the catogary of Book:");
	char catogary[20]; scanf("%s",catogary);
	char book[20]; strcpy(book,l.getBook());
	printf("Number of copy want to purchase :");
	int copy;scanf("%d",&copy);
	Book e(iid,book,catogary,name,copy);
	ms->addRecord(e,GDBM_INSERT);
	printf("Book Purshased and added to Library database.");
	cs->deleteRecord(id);
	return;
}
void displayRequest(CMS *cs,LRMS *ms){
	printf("Request in the library database : \n ");
	cs->displayAll();
	printf("Press 1 to approve request,2 to reject request:");
	int c;scanf("%d",&c);
	if(c==1) approveRequest(cs,ms);
	else deleteRequest(cs);
	return;
}
void displayStudents(LMS *ls){
	printf("Students in the library database : \n ");
	ls->displayAll();
	return;
}
void displayFaculity(FMS *fs){
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
void searchBook(LMS *ls,LRMS *ms,FMS *fs,int id){
aa:	printf("Enter the Name of the Book you want to serach - ");
	char sp[50];
	int p,c,a;
	scanf("%s",sp);
	p=ms->searchRecord(sp);
	Student s=ls->getRecord(id);
	if(p==0){printf("The book not found\n");return;}
	else{
	Book e=ms->getRecord(p);
        printf("\n %d \t %s \t %s \t %s \t %d \n",e.getId(),e.getName(),e.getsubject(),e.getauname(),e.getcopy());
        if(s.getBookid()==p){printf("You have taken this book\n");goto aa;}
	if(e.getcopy()==0){
                printf("No copy is available\n");
                printf("Do you want to sent Reservation to bookholders ? (press 1 for yes ,2 for no)");
                scanf("%d",&a);
                if(a==1)sentReservation(ls,ms,fs,e.getId(),id);
                else if(a==2)searchBook(ls,ms,fs,id);
		}
        printf("Enter 1 to add- ");
        scanf("%d",&c);
        if(c==1){
        	//Student s=ls->getRecord(id);
        	if(s.getBookid()==p){printf("You have taken this book\n");goto aa;}
        	if(e.getcopy()==0){printf("No copy is available\n");return;}
       		else{
       		if(s.getBookid()!=0){
        		Book e1=ms->getRecord(s.getBookid());
        		e1.setcopy(e1.getcopy()+1);
        		ms->addRecord(e1, GDBM_REPLACE);}
        		e.setcopy(e.getcopy()-1);
        		ms->addRecord(e, GDBM_REPLACE);
        		s.setBookid(e.getId());
        		s.setBook(e.getName());
        		ls->addRecord(s, GDBM_REPLACE);
        		}
        	}	
        else
	return;
	}
}
void searchBook(FMS *fs,LRMS *ms,LMS *ls,int id){
bb:	printf("Enter the Name of the Book you want to serach - ");
	char sp[50];
	int p,c,a;
	scanf("%s",sp);
	p=ms->searchRecord(sp);
	Book e=ms->getRecord(p);
	Faculty f=fs->getRecord(id);
        printf("\n %d \t %s \t %s \t %s \t %d \n",e.getId(),e.getName(),e.getsubject(),e.getauname(),e.getcopy());
        if(f.getBookid()==p){printf("You have taken this book\n");goto bb;}	
        if(e.getcopy()==0){
                printf("No copy is available\n");
                printf("Do you want to sent Reservation to bookholders ? (press 1 for yes ,2 for no)");
                scanf("%d",&a);
                if(a==1)sentReservation(fs,ms,ls,e.getId(),id);
                else if(a==2)searchBook(fs,ms,ls,id);

	}

      	printf("Enter 1 to add- ");
        scanf("%d",&c);
        if(c==1){
        	//Faculty f=fs->getRecord(id);
        	if(f.getBookid()==p){printf("You have taken this book\n");goto bb;}
        	if(e.getcopy()==0){printf("No copy is available\n");return;}
       		else{
       		if(f.getBookid()!=0){
        		Book e1=ms->getRecord(f.getBookid());
        		e1.setcopy(e1.getcopy()+1);
        		ms->addRecord(e1, GDBM_REPLACE);}
        		e.setcopy(e.getcopy()-1);
        		ms->addRecord(e, GDBM_REPLACE);
        		f.setBookid(e.getId());
        		f.setBook(e.getName());
        		fs->addRecord(f, GDBM_REPLACE);
        	
        		}
        	}	
        else
	return;
}
void searchauBook(LMS *ls,LRMS *ms,FMS *fs,int id){
	printf("Enter the Name of the Author or catogory you want to serach - ");
	char s[50];
	int p,c;
	scanf("%s",s);
	c=ms->searchauRecord(s);
	if(c==1){printf("Enter the id of BOOK\n");
	selectNewbook(ms,ls,fs,id);
	return;
	}
	else{
	printf("BOOK not fount\n");}
	return;
}
void searchauBook(FMS *fs,LRMS *ms,LMS *ls,int id){
	printf("Enter the Name of the Author or catogory you want to serach - ");
	char s[50];
	int p,c;
	scanf("%s",s);
	c=ms->searchauRecord(s);
	if(c==1){printf("Enter the id of BOOK\n");
	selectNewbook(ms,fs,ls,id);
	return;
	}
	else{
	printf("BOOK not fount\n");}
	return;
}
	
void returnBook(FMS *fs,LRMS *ms,int id){
	      	Faculty f=fs->getRecord(id);
	      	if(f.getBookid()==0){printf("there is no book to return");return;}
        	else{
        	Book e1=ms->getRecord(f.getBookid());
        	e1.setcopy(e1.getcopy()+1);
      		ms->addRecord(e1, GDBM_REPLACE);
      		f.setBookid(00);
      		char a[3];strcpy(a,"na");
      		f.setBook(a);
      		fs->addRecord(f, GDBM_REPLACE);	

	return;
	}
}
void returnBook(LMS *ls,LRMS *ms,int id){
	      	Student s=ls->getRecord(id);
	      	if(s.getBookid()==0){printf("there is no book to return");return;}
        	else{
        	Book e1=ms->getRecord(s.getBookid());
        	e1.setcopy(e1.getcopy()+1);
      		ms->addRecord(e1, GDBM_REPLACE);
      		s.setBookid(00);
      		char a[3];strcpy(a,"na");
      		s.setBook(a);
      		ls->addRecord(s, GDBM_REPLACE);	

	return;
	}
}
void displayStudentList(CMS *cs,LMS *ls){
	 //printf("No.of Students\n ");
	printf("\nID\tStudent Name\tPassword\tBook ID\t\tBook Issued ");
	printf("\n..........................................................................................................\n");
	ls->displayStudents();
	return;
    }

void displayFaculityList(CMS *cs,FMS *fs){
	// printf("No.of Students\n ");
	printf("\nID\tFaculity Name\tPassword\tBook ID\t\tBook Issued ");
	printf("\n..........................................................................................................\n");
	fs->displayFaculities();
	return;
    }


void student(LMS *ls,CMS *cs,FMS *fs,int id,LRMS *ms){
	Student s=ls->getRecord(id);
	int rid=s.getRbook();
	printf("\n");
	printf("Welcome %s \n\n",s.getName());
	//printf("%d",s.getMessage());
	if(s.getMessage()!=0){
		printf("You have a Reservation for book of id %d.Please return within Duedate.\n\n",s.getBookid());
	}
	printf("Press 1 to change password\nPress 2 to select new book\nPress 3 to view your details \nPress 4 to request book\nPress 5 to search\nPress 6 to Return book\nPress 7 to show reservation details\nPress 8 to Search by author/catogary\t\t");
	int choice;
	while(true){
		scanf("%d",&choice);
		if(choice==1)changePassword(ls);
		else if(choice==2)selectNewbook(ms,ls,fs,id);
		else if(choice==3)showStudent(ls,id);
		else if(choice==4)requsetParchase(cs);
		else if(choice==5)searchBook(ls,ms,fs,id);
		else if(choice==6)returnBook(ls,ms,id);
		else if(choice==7)showReservation(ls,fs,rid,id);
		else if(choice==8)searchauBook(ls,ms,fs,id);
		else break;
	}
}
void librarian(CMS *cs,LMS *ls,FMS *fs,LRMS *ms){
	//Student s=ls->getRecord(id);
	printf("\n");
	//printf("Welcome %s \n\n",s.getName());
	printf("____________________________________________________________________________\n");
	printf("____________________________________________________________________________\n");
	printf("Press\n\t 1 ==> Change Password\n\t 2 ==> Add Stutdent Record\n\t 3 ==> Add Faculty Record\n\t 4 ==> Add Book Details \n\t 5 ==> See Requests\n\t 6 ==> Delete Student Record\n\t 7 ==> Delete Faculity Record\n\t 8 ==> Show Student Details\n\t 9 ==> Show Faculty Details\n\t10 ==> Show Student List\n\t11 ==> Show Faculity List\t\t");
	int choice;
	while(true){
		scanf("%d",&choice);
		if(choice==1)changePassword(cs);
		else if(choice==2)addStudent(ls);
		else if(choice==3)addFaculty(fs);
		else if(choice==6)deleteStudent(ls);
		else if(choice==7)deleteFaculty(fs);
		else if(choice==5)displayRequest(cs,ms);
		else if(choice==8)getStudent(cs,ls);
		else if(choice==9)getFaculty(cs,fs);
		else if(choice==4)getBookdetails(ms);
		else if(choice==10)displayStudentList(cs,ls);
		else if(choice==11)displayFaculityList(cs,fs);
		else break;
	}
}
void faculty(FMS *fs,LMS *ls,CMS *cs,int id,LRMS *ms){
	Faculty f=fs->getRecord(id);
	int rid=f.getRbook();
	printf("\n");
	printf("____________________________________________________________________________\n");
	printf("Welcome %s \n\n",f.getName());
	if(f.getMessage()!=0){
                printf("You have a Reservation for book of id %d.Please return within Duedate.\n\n",f.getBookid());
        }

	printf("Press \n\t1 ==> Change Password\n\t2 ==> Select New Book\n\t3 ==> View your Profile\n\t4 ==> Search book\n\t5 ==> Request Purchase\n\t6 ==> Return book\n\t7 ==> show reservation details\n\t8 ==>Search by author/catogary ");
	int choice;
	while(true){
		scanf("%d",&choice);
		if(choice==1)changePassword(fs);
		else if(choice==2)selectNewbook(ms,fs,ls,id);
		else if(choice==3)showFaculty(fs,id);
		else if(choice==4)searchBook(fs,ms,ls,id);
		else if(choice==5)requsetParchase(cs);
		else if(choice==6)returnBook(fs,ms,id);
		else if(choice==7)showReservation(fs,ls,rid,id);
		else if(choice==8)searchauBook(fs,ms,ls,id);
		else break;
	}
}


void checkPassword(LMS *ls,CMS *cs,FMS *fs,LRMS *ms){
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
		student(ls,cs,fs,id,ms);
	
	return;
}
void checkPassword(FMS *fs,LMS *ls,CMS *cs,LRMS *ms){
	printf("Enter faculty ID :\t");
	int id; scanf("%d",&id);
	Faculty f=fs->getRecord(id);
	//printf("%d\t\%s\t\%d\t%d\t%s",f.getId(),f.getName(),f.getPassword(),f.getBookid(),f.getBook());
	int p=f.getPassword();
bbb:	printf("Enter the password:\t");
	int p1; scanf("%d",&p1);
	if(p1!=p){
		printf("Password incorrect.");
		printf("Enter password again.\n");
		goto bbb;
	}
	else 
		faculty(fs,ls,cs,id,ms);
	return;
}
void checkPassword(CMS *cs,LMS *ls,FMS *fs,LRMS *ms){
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
		//LRMS *ms=LRMS ::create();	
		librarian(cs,ls,fs,ms);
	return;
}




int main(){
	LMS *ls=LMS::create();
	FMS *fs=FMS::create();
	CMS *cs=CMS::create();
	LRMS *ms=LRMS::create();
	printf("____________________________________________________________________________\n\n");
	printf("\t\tWELCOME TO ABC LIBRARY\n");
	printf("____________________________________________________________________________\n");
	printf("**************************************************************************\n");
	printf("____________________________________________________________________________\n\n");
	printf("Please Select your Option\n");
	printf("(options 2-4 are only for adim ,here its used for testing)\n\n");
	printf("Press \n\t1 ==> Student LOGIN \n\t2 ==> Faculty LOGIN\n\t3 ==> Librarian LOGIN\n\t4 ==> Reset : \n\t");
	int q;
	while(true){
		scanf("%d",&q);
		if(q==1)checkPassword(ls,cs,fs,ms);
		else if(q==2)checkPassword(fs,ls,cs,ms);
		else if(q==3)checkPassword(cs,ls,fs,ms);
		else if(q==4)addLibrarianpass(cs);
		else break;


	}
	return 0;
}



	
                  




	


