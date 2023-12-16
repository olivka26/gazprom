#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sqlite3.h>
#include <curl/curl.h>
#include <string>
#include <time.h>
using namespace std;

int main(){
    sqlite3* db;
    int ob;
    ob=sqlite3_open("database.db",&db);
    if(ob){
        fprintf(stderr,"Error open DB\n");
        return -1;
    }else{
        fprintf(stdout,"DB opened successfully\n");
    }
    string createcom = "CREATE TABLE FIBONACCI("
                     "ID BIGINT PRIMARY KEY     NOT NULL, "
                     "MEMBER      BIGINT     NOT NULL); ";
    char* messageerror;
    ob=sqlite3_exec(db,createcom.c_str(),NULL,0,&messageerror);
    if(ob!=SQLITE_OK){
        fprintf(stderr,"Error create \n");
        sqlite3_free(messageerror);
        sqlite3_close(db);
        return -1;
    }
    long long int f0=0,f1=1,index=0;
    while(1){
        char buf[10000], insert[1000000];
        /*if(f0<0){
            fprintf(stderr,"Overflow %lld %lld\n",index,f0);
            return -1;
        }*/
        sprintf(buf,"echo {\"ID\": \"%lld\",\"Member\": \"%lld\"} > member.json",index,f0);
        system(buf);
        printf("%ld", time(NULL));
        sprintf(buf,"curl -X POST \"https://httpbin.org/post\" -H \"Content-Type: application/json; charset=utf-8\" -d @member.json -o result.json");
        system(buf);
        sprintf(insert,"INSERT INTO FIBONACCI VALUES(%lld,%lld)",index,f0);
        ob=sqlite3_exec(db,insert,0,0,&messageerror);
        if(ob!=SQLITE_OK){
            fprintf(stderr,"Error insert\n");
            sqlite3_free(messageerror);
            sqlite3_close(db);
            return -1;
        }/*else{
            fprintf(stdout,"Inserted %lld %lld\n",index,f0);
        }*/
        index+=1;
        sleep(1);
        f0+=f1;
        /*if(f1<0){
            fprintf(stderr,"Overflow %lld %lld\n",index,f1);
            return -1;
        }*/
        sprintf(buf,"echo {\"ID\": \"%lld\",\"Member\": \"%lld\"} > member.json",index,f1);
        system(buf);
        printf("%ld", time(NULL));
        sprintf(buf,"curl -X POST \"https://httpbin.org/post\" -H \"Content-Type: application/json; charset=utf-8\" -d @member.json -o result.json");
        system(buf);
        sprintf(insert,"INSERT INTO FIBONACCI VALUES(%lld,%lld)",index,f1);
        ob=sqlite3_exec(db,insert,NULL,0,&messageerror);
        if(ob!=SQLITE_OK){
            fprintf(stderr,"Error insert\n");
            sqlite3_free(messageerror);
            sqlite3_close(db);
            return -1;
        }/*else{
            fprintf(stdout,"Inserted %lld %lld\n",index,f1);
        }*/
        index+=1;
        sleep(1);
        f1+=f0;
    }
    sqlite3_close(db);
    return 0;
}
