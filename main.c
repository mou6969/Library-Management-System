#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char user[50];
    char pass[50];
}User;
typedef struct{
    int month;
    int year;
}date;
typedef struct{
    char ISBN[20];
    char title[100];
    char aname[50];
    int q;
    float price;
     date D;
     int datedigit;
}books;

char *validate_ISBN(char *ISBN,books *b,int n){char *p; long long is;
    for(int i=0;ISBN[i]!='\0';i++){
        if(ISBN[i]>='0' && ISBN[i]<='9'){continue;}
        else return 0;}
    for(int i=0;i<n;i++){
        if(strcmp(ISBN,b[i].ISBN)==0){
            printf("\nISBN already in system\n");
            return 0;}
    }
    is=strtoll(ISBN,&p,10);
    if(is<=999999999999 || is>9999999999999)return 0;
    else return ISBN;
}
char* titlecheck(char *book){int i;
    if(book[0]>='a' && book[0]<='z'){
        book[0]-=32;}
    for(i=0;book[i]!='\0';i++){
        if(book[i]==' ' || book[i]=='.'){
            if(book[i+1]>='a' && book[0]<='z'){
                book[i+1]-=32;}}
        if(book[i]>='A' && book[i]<='Z'&& book[i-1]!=' ' && book[i-1]!='.' &&i!=0){
            book[i]+=32;}

    }return book;
}
int validate_quantity(char *quantity){char *p; int q;
    for(int i=0;quantity[i]!='\0';i++){
        if(quantity[i]>='0' && quantity[i]<='9'){continue;}
        else return 0;}

    q=strtof(quantity,&p);
    if(q<=0)return 0;
    else return q;
}
float validate_price(char *price){float pr; char *p;
    for(int i=0;price[i]!='\0';i++){
        if((price[i]>='0' && price[i]<='9')|| price[i]=='.'){continue;}
        else return 0;}

    pr=strtof(price,&p);
    if (pr == 0) {return 0;}
    else return pr;
}
int validate_month(char *month){char *p; int mo;
    for(int i=0;month[i]!='\0';i++){
        if(month[i]>='0' && month[i]<='9'){continue;}
        else return 0;}

    mo=strtof(month,&p);
    if(mo<=0 || mo>12)return 0;
    else return mo;
}
int validate_year(char *year){char *p; int ye;
    for(int i=0;year[i]!='\0';i++){
        if(year[i]>='0' && year[i]<='9'){continue;}
        else return 0;}

    ye=strtof(year,&p);
    if(ye<1000 || ye>2023)return 0;//Happy new year!
    else return ye;
}
int validate_title(char *title,books *b, int n){
    titlecheck(title);
    for(int i=0;i<n;i++){
        if(strcmp(title,b[i].title)==0){
            printf("\nBook already in system\n");
            return 0;}
    }return 1;
}
void monthname(int month){
    if(month==1)printf("January ");
    if(month==2)printf("February ");
    if(month==3)printf("March ");
    if(month==4)printf("April ");
    if(month==5)printf("May ");
    if(month==6)printf("June ");
    if(month==7)printf("July ");
    if(month==8)printf("August ");
    if(month==9)printf("September ");
    if(month==10)printf("October ");
    if(month==11)printf("November ");
    if(month==12)printf("December ");}

int load(books *b){FILE *f2; int n=0;
f2 = fopen("books.txt", "r+");
if (f2 == NULL){printf("Error opening file");
return 0;}
int read=0;
int records = 0;
do {
read=fscanf(f2,"%14[^,],%100[^,],%50[^,],%d,%f,%d-%d\n",b[records].ISBN,b[records].title,b[records].aname,
            &b[records].q, &b[records].price, &b[records].D.month, &b[records].D.year);
n+=1;
if (read==7)records++;
if (read!=7 &&!feof(f2)) {
printf("File format incorrect.\n");
return 0;}
if (ferror(f2)){printf("Error reading file"); return 0;
}}while (!feof(f2));
fclose(f2);
for(int i=0;i<n;i++)
    for(int j=0;b[i].title[j];j++){
        if(b[i].title[j]=='#'){
            b[i].title[j]=',';
        }
    }
for(int i=0;i<n;i++){
        b[i].datedigit=(b[i].D.year*100)+b[i].D.month;}//will be used later in sorbyDate

        return n;}

int login(books *b){
    FILE *f1; User u[10]; int n=0; char ans[10];
    f1= fopen("credentials.txt","r");
    while(!feof(f1)){
        fscanf(f1,"%s%s",u[n].user,u[n].pass);
        n++;}
    char username[50]; char password[50];
    printf("Enter username:");
    scanf("%s",username);
    printf("\n");
    printf("Enter password:");
    scanf("%s",password);
    int flag=0;
    for(int i=0;i<10;i++){
        if(strcmp(username,u[i].user)==0 && strcmp(password,u[i].pass)==0){flag=1;load(b);}
    }if(flag==0){
        printf("Incorrect username or password\n");
        printf("Try again?\n yes or no\n");
        scanf("%s",ans);
        if(strcmp(ans,"yes")==0 || strcmp(ans,"Yes")==0)login(b);
        else return 0;
    }
    return 1;
}
int add(books *b, int n){ char ans[5];
    if(n==100){printf("Cannot add more entries. System is full\n"); return n;}
    do{
        printf("Enter ISBN:");
        scanf("%s",b[n].ISBN);}while(!(validate_ISBN(b[n].ISBN,b,n)));
    do{
    printf("Enter book title:");
    scanf("\n%100[^\n]",b[n].title);
    }while(!validate_title(b[n].title,b,n));
    titlecheck(b[n].title);
    printf("Enter author name:");
    scanf("\n%50[^\n]",b[n].aname);
    titlecheck(b[n].aname);
    char quantity[50];
    do{
    printf("Enter quantity of books available:");
    scanf("%s",quantity);}while(!validate_quantity(quantity));
    b[n].q=validate_quantity(quantity);
    char price[20];
    do{
    printf("Enter price of one book:");
    scanf("%s",price);}
    while(!validate_price(price));
    b[n].price=validate_price(price);
    char month[50],year[50];
    do{
    printf("Enter publish month:\n");
    scanf("%s",month);} while (!validate_month(month));
    b[n].D.month=validate_month(month);
    do{
        printf("Enter publish year:\n");
        scanf("%s",year);}while(!validate_year(year));
    b[n].D.year=validate_year(year);

    b[n].datedigit=(b[n].D.year*100)+b[n].D.month;//Used for sortbydate
    n+=1;
    printf("Add more?(yes or no)");
    scanf("%s",ans);
    if(strcmp(ans,"yes")==0 || strcmp(ans,"Yes")==0){n=add(b,n);}
    return n;}

void modify(books *b, int n){char modkey[14]; char ans[10]; int i=0,flag=0; char ans2[10];
    do{
    printf("Enter ISBN:");
    scanf("%s",modkey);}while(strlen(modkey)!=13);
    for(i=0;i<n;i++){
        if(strcmp(modkey,b[i].ISBN)==0){
            printf("%s, %s, %s, %d, %.2f$, %d-%d",b[i].ISBN,b[i].title,b[i].aname,b[i].q,b[i].price,b[i].D.month,b[i].D.year);
            flag=1; break;}}
    if(flag==0){
        printf("ISBN not found.Try again?\n yes or no");//any answer other than yes will be considered a no.
        scanf("%s",ans);
        if(strcmp(ans,"yes")==0){modify(b,n);return;}
    }
    else{
        printf("\nModify ISBN?\n yes or no\n");
        scanf("%s",ans2);
        if(strcmp(ans2,"yes")==0 || strcmp(ans2,"Yes")==0){
            char ISBN[100];
            do{
                printf("Enter new ISBN:");
                scanf("%s",ISBN);}while(!(validate_ISBN(ISBN,b,n)));
        strcpy(b[i].ISBN,ISBN);}
        printf("\nModify Book title?\n yes or no");
        scanf("%s",ans2);
        if(strcmp(ans2,"yes")==0 || strcmp(ans2,"Yes")==0){
            char title[100];
            do{
                printf("Enter book title:");
                scanf("\n%100[^\n]",title);
            }while(!validate_title(title,b,n));
            strcpy(b[i].title,title);
            titlecheck(b[i].title);}
        printf("\nModify author name?\n yes or no");
        scanf("\n%s",ans2);
        if(strcmp(ans2,"yes")==0 || strcmp(ans2,"Yes")==0){
            printf("\nEnter author name:\n");
            scanf("\n%50[^\n]",b[i].aname);
            titlecheck(b[i].aname);}
        printf("\nModify quantity?\n yes or no");
        scanf("\n%s",ans2);
        if(strcmp(ans2,"yes")==0 || strcmp(ans2,"Yes")==0){
            char quantity[50];
            do{
                printf("Enter new quantity:");
                scanf("%s",quantity);}
            while(!validate_quantity(quantity));

            b[i].q=validate_quantity(quantity);}
        printf("\nModify price?\n yes or no");
        scanf("\n%s",ans2);
        if(strcmp(ans2,"yes")==0 || strcmp(ans2,"Yes")==0){
            char price[20];
            do{
                printf("Enter price of one book:");
                scanf("%s",price);}
            while(!validate_price(price));
            b[i].price=validate_price(price);}
        printf("\nModify publish date?\n yes or no");
        scanf("\n%s",ans2);
        if(strcmp(ans2,"yes")==0 || strcmp(ans2,"Yes")==0){char month[50],year[50];
            do{
                printf("Enter publish month:\n");
                scanf("%s",month);} while (!validate_month(month));
            b[n].D.month=validate_month(month);
            do{
                printf("Enter publish year:\n");
                scanf("%s",year);}while(!validate_year(year));
            b[i].D.year=validate_year(year);
            b[i].datedigit=(b[i].D.year*100)+b[n].D.month;
        }
    }}
void save(books *b,int n){int i;
    FILE *f3;
    for(i=0;i<n;i++)
        for(int j=0;b[i].title[j]!='\0';j++){
            if(b[i].title[j]==','){
                b[i].title[j]='#';}
        }
    f3=fopen("books.txt","w+");
    if(f3 == NULL){printf("Error opening file"); return;}
    for(i=0;i<n;i++){
        fprintf(f3,"%s,%s,%s,%d,%.2f,%d-%d\n",b[i].ISBN,b[i].title,b[i].aname,b[i].q,b[i].price,b[i].D.month,b[i].D.year);
    }
    fclose(f3);
}
int delete(books *b,int n){char deletekey[14]; int i,flag=0; char ans[10]; int count=n;
    printf("Enter ISBN for book to be deleted: ");
    scanf("%s",deletekey);
    for(i=0;i<n;i++){
        if(strcmp(deletekey,b[i].ISBN)==0){
            printf("\n%s,%s,%s,%d,%.2f,%d-%d\n", b[i].ISBN, b[i].title, b[i].aname, b[i].q, b[i].price, b[i].D.month,
                   b[i].D.year);
            flag=1;
            n-=1;
            break;}}
    if(flag==1){printf("Are you sure you'd like to delete this entry?\n yes or no");
        scanf("%s",ans);
        if(strcmp(ans,"yes")==0 || strcmp(ans,"Yes")==0){
            for(int j=i;j<n;j++){
                strcpy(b[j].ISBN,b[j+1].ISBN);
                strcpy(b[j].title,b[j+1].title);
                strcpy(b[j].aname,b[j+1].aname);
                b[j].q=b[j+1].q;
                b[j].price=b[j+1].price;
                b[j].D.month=b[j+1].D.month;
                b[j].D.year=b[j+1].D.year;}}}
    if(flag==0){printf("ISBN not found. Try again?\n yes or no");
        scanf("%s",ans);
        if(strcmp(ans,"yes")==0 || strcmp(ans,"Yes")==0)delete(b,n);
        else return n;}
    printf("\nDone!\n");
    return n;
}

void lower_case (char *fnct, int size)
{int lwrcnst='a'- 'A';
    if (size==0){
        if( fnct[0]>= 'a' &&fnct[0]<= 'z'){
            return;}
        else{
            fnct[0]=fnct[0]+lwrcnst;

            return;}
    }

    else if ( fnct[size] < 'a'&& fnct[size]>='A' )
    {
        fnct[size]=fnct[size]+lwrcnst;
        lower_case(fnct,size-1);
    }
    else lower_case(fnct,size-1);}
char *lower_case2 (char *fnct, int size)
{int lwrcnst='a'- 'A';
    if (size==0){
        if( fnct[0]>= 'a' &&fnct[0]<= 'z'){
            return fnct;}
        else{
            fnct[0]=fnct[0]+lwrcnst;

            return fnct;}
    }

    else if ( fnct[size] < 'a'&& fnct[size]>='A' )
    {
        fnct[size]=fnct[size]+lwrcnst;
        return lower_case2(fnct,size-1);
    }
    else return lower_case2(fnct,size-1);

}
void sortbyPrice(books *b,int n){int pass=1; int sorted=0; books temp[20];
    for(int i=0;i<n;i++)
        titlecheck(b[i].title);
    printf("Order after sorting by price:\n");
    for(pass=1; pass<n && !sorted;pass++){
        sorted=1;
        for(int i=0;i<n-pass;i++){
            if(b[i].price>b[i+1].price){
                strcpy(temp[i].ISBN,b[i].ISBN);
                strcpy(temp[i].title,b[i].title);
                strcpy(temp[i].aname,b[i].aname);
                temp[i].q=b[i].q;
                temp[i].price=b[i].price;
                temp[i].D.month=b[i].D.month;
                temp[i].D.year=b[i].D.year;
                temp[i].datedigit=b[i].datedigit;

                strcpy(b[i].ISBN,b[i+1].ISBN);
                strcpy(b[i].title,b[i+1].title);
                strcpy(b[i].aname,b[i+1].aname);
                b[i].q=b[i+1].q;
                b[i].price=b[i+1].price;
                b[i].D.month=b[i+1].D.month;
                b[i].D.year=b[i+1].D.year;
                b[i].datedigit=b[i+1].datedigit;

                strcpy(b[i+1].ISBN,temp[i].ISBN);
                strcpy(b[i+1].title,temp[i].title);
                strcpy(b[i+1].aname,temp[i].aname);
                b[i+1].q=temp[i].q;
                b[i+1].price=temp[i].price;
                b[i+1].D.month=temp[i].D.month;
                b[i+1].D.year=temp[i].D.year;
                b[i+1].datedigit=temp[i].datedigit;
                sorted=0;}}}
    for(int i=0;i<n;i++){
        for(int j=0;b[i].title[j];j++){
            if(b[i].title[j]=='#'){
                b[i].title[j]=',';}
            }}
    for(int i=0;i<n;i++){
        printf("ISBN:%s\nBook title:%s\nAuthor name:%s\nQuantity:%d\nPrice:%.2f$\nPublish Date:", b[i].ISBN, b[i].title, b[i].aname, b[i].q, b[i].price);
        monthname(b[i].D.month);
        printf("%d\n\n",b[i].D.year);
    }}
void sortbyDate(books *b,int n){int max; books temp[20];
    for(int i=0;i<n;i++)
        titlecheck(b[i].title);
    for(int i=0;i<n-1;i++){
        max=i;
        for(int j=i+1;j<n;j++)
            if(b[j].datedigit>b[max].datedigit)max=j;

        if(max!=i){
            strcpy(temp[i].ISBN,b[i].ISBN);
            strcpy(temp[i].title,b[i].title);
            strcpy(temp[i].aname,b[i].aname);
            temp[i].q=b[i].q;
            temp[i].price=b[i].price;
            temp[i].D.month=b[i].D.month;
            temp[i].D.year=b[i].D.year;
            temp[i].datedigit=b[i].datedigit;

            strcpy(b[i].ISBN,b[max].ISBN);
            strcpy(b[i].title,b[max].title);
            strcpy(b[i].aname,b[max].aname);
            b[i].q=b[max].q;
            b[i].price=b[max].price;
            b[i].D.month=b[max].D.month;
            b[i].D.year=b[max].D.year;
            b[i].datedigit=b[max].datedigit;

            strcpy(b[max].ISBN,temp[i].ISBN);
            strcpy(b[max].title,temp[i].title);
            strcpy(b[max].aname,temp[i].aname);
            b[max].q=temp[i].q;
            b[max].price=temp[i].price;
            b[max].D.month=temp[i].D.month;
            b[max].D.year=temp[i].D.year;
            b[max].datedigit=temp[i].datedigit;}}
    for(int i=0;i<n;i++){
        for(int j=0;b[i].title[j];j++){
            if(b[i].title[j]=='#'){
                b[i].title[j]=',';}
        }}
    for(int i=0;i<n;i++){
        printf("ISBN:%s\nBook title:%s\nAuthor name:%s\nQuantity:%d\nPrice:%.2f$\nPublish Date:", b[i].ISBN, b[i].title, b[i].aname, b[i].q, b[i].price);
        monthname(b[i].D.month);
        printf("%d\n\n",b[i].D.year);
    }}
void sortbyTitle(books *b,int n){ int i,j;
    for(i=0;i<n;i++)
        titlecheck(b[i].title);
    books x[100];
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(strcmp(b[i].title,b[j].title)>0){
                strcpy(x[i].ISBN,b[i].ISBN);
                strcpy(b[i].ISBN,b[j].ISBN);
                strcpy(b[j].ISBN,x[i].ISBN);

                strcpy(x[i].title,b[i].title);
                strcpy(b[i].title,b[j].title);
                strcpy(b[j].title,x[i].title);

                strcpy(x[i].aname,b[i].aname);
                strcpy(b[i].aname,b[j].aname);
                strcpy(b[j].aname,x[i].aname);

                x[i].q=b[i].q;
                b[i].q=b[j].q;
                b[j].q=x[i].q;

                x[i].price=b[i].price;
                b[i].price=b[j].price;
                b[j].price=x[i].price;

                x[i].D.month=b[i].D.month;
                b[i].D.month=b[j].D.month;
                b[j].D.month=x[i].D.month;

                x[i].D.year=b[i].D.year;
                b[i].D.year=b[j].D.year;
                b[j].D.year=x[i].D.year;

                x[i].datedigit=b[i].datedigit;
                b[i].datedigit=b[j].datedigit;
                b[j].datedigit=x[i].datedigit;

            }}}
    for(i=0;i<n;i++){
        for(j=0;b[i].title[j];j++){
            if(b[i].title[j]=='#'){
                b[i].title[j]=',';}
        }}
    for(i=0;i<n;i++){

        printf("ISBN:%s\nBook title:%s\nAuthor name:%s\nQuantity:%d\nPrice:%.2f$\nPublish Date:", b[i].ISBN, b[i].title, b[i].aname, b[i].q, b[i].price);
        monthname(b[i].D.month);
        printf("%d\n\n",b[i].D.year);}
}

void advanced(books *b,int n){
    char key[100];int i,flag=0;
    char title[100];

    printf("Enter the characters:");
    scanf("%s",key);
    lower_case2(key,strlen(key));
    for(i=0;i<n;i++){
        strcpy(title,b[i].title);
        lower_case2(title,strlen(title));
        if(strstr(title,key)!=NULL){
            printf("ISBN:%s\nBook title:%s\nAuthor name:%s\nQuantity:%d\nPrice:%.2f$\nPublish Date:", b[i].ISBN, b[i].title, b[i].aname, b[i].q, b[i].price);
            monthname(b[i].D.month);
            printf("%d\n\n",b[i].D.year);
            flag=1;}}
    if(flag==0)printf("No books contain '%s'",key);}
void quit2(books *b){char ans[10];
    printf("Are you sure you'd like to quit? All your changes will be discarded.\nyes or no\n");
    scanf("%s",ans);
    if(strcmp(ans,"yes")==0 || strcmp(ans,"Yes")==0)exit(0);
    return;
}

void quit(books *b){char ans[10];
    printf("Are you sure you'd like to quit? All your changes will be discarded.\nyes or no\n");
    scanf("%s",ans);
    if(strcmp(ans,"yes")==0 || strcmp(ans,"Yes")==0)exit(0);
    else login(b);
}
void query(books *b,int n){
    int i; char l[20]; int flag=1; char ans[5];
    printf("Enter ISBN:");
    scanf("%s",l);
    for(i=0;i<n;i++){
        if(strcmp(l,b[i].ISBN)==0){
            printf("ISBN:%s\nBook title:%s\nAuthor name:%s\nQuantity:%d\nPrice:%.2f$\nPublish Date:", b[i].ISBN, b[i].title, b[i].aname, b[i].q, b[i].price);
            monthname(b[i].D.month);
            printf("%d\n\n",b[i].D.year);
            flag=0;}}
    if(flag==1){printf("ISBN not found. Try again?\n yes or no");
    scanf("%s",ans);
    if(strcmp(ans,"yes")==0)query(b,n);}
    else return;
}
void menu2(books *b,int n){char ans[10];
    int size;
    size= 20;
    char fnct[size];
    printf("Please type your desired system function from the list:\nADD\nDELETE\nMODIFY\nSEARCH\nADVANCED SEARCH\nPRINT\nSAVE\nQUIT\n\n");
    scanf("\n%20[^\n]",fnct);
    lower_case(fnct, strlen(fnct));
    if(!strcmp(fnct,"add")){
        n=add(b,n);
        menu2(b,n);}
    if(!strcmp(fnct,"delete")){
        n=delete(b,n);
        menu2(b,n);}
    if(!strcmp(fnct,"modify")){
        modify(b,n);
        menu2(b,n);}
    if(!strcmp(fnct,"search")){
        query(b,n);
        menu2(b,n);}
    if(!strcmp(fnct,"advanced search")){
        advanced(b,n);
        menu2(b,n);}

    if(!strcmp(fnct,"print")){

        printf("Would you like entries to be sorted by Title, price or date?\nType title, price or date");
    scanf("%s",ans);
    lower_case(ans, strlen(ans));
    if(!strcmp(ans,"title"))sortbyTitle(b,n);
    if(!strcmp(ans,"price"))sortbyPrice(b,n);
    if(!strcmp(ans,"date"))sortbyDate(b,n);
    menu2(b,n);}

    if(!strcmp(fnct,"save")){
        save(b,n);
        menu2(b,n);}

    if(!strcmp(fnct,"quit"))
    {quit2(b);
    menu2(b,n);}
    else menu2(b,n);
}
void menu(books *b,int n)
{char ans[10];
    printf("LOGIN\n\nQUIT\n\n");
    char inpt[10];
    scanf("%10[^\n]",inpt);
    lower_case(inpt,strlen(inpt));
    if (strcmp(inpt,"login")&&strcmp(inpt,"quit"))
    {
        printf("please enter the correct term\n\n");
        scanf("%s",inpt);
        lower_case(inpt,strlen(inpt));
        printf("%s\n\n", inpt);
        if(strcmp(inpt,"login")&&strcmp(inpt,"quit"))menu(b,n);
    }
    if(!strcmp(inpt,"login"))
    {if(login(b)==0)menu(b,n);}
    else if(!strcmp(inpt,"quit"))
    {quit(b);}
    int size;
    size= 20;
    char fnct[size];
    printf("Please type your desired system function from the list:\nADD\nDELETE\nMODIFY\nSEARCH\nADVANCED SEARCH\nPRINT\nSAVE\nQUIT\n\n");
    scanf("\n%20[^\n]",fnct);
    lower_case(fnct, strlen(fnct));
    if(!strcmp(fnct,"add")){
        n=add(b,n);
        menu2(b,n);}
    if(!strcmp(fnct,"delete")){
        n=delete(b,n);
        menu2(b,n);}
    if(!strcmp(fnct,"modify")){
        modify(b,n);
        menu2(b,n);}
    if(!strcmp(fnct,"search")){
        query(b,n);
        menu2(b,n);}
    if(!strcmp(fnct,"advanced search")){
        advanced(b,n);
        menu2(b,n);}
    if(!strcmp(fnct,"print")){

        printf("Would you like entries to be sorted by Title, price or date?\nType title, price or date");
        scanf("%s",ans);
        lower_case(ans, strlen(ans));
        if(!strcmp(ans,"title"))sortbyTitle(b,n);
        if(!strcmp(ans,"price"))sortbyPrice(b,n);
        if(!strcmp(ans,"date"))sortbyDate(b,n);
        menu2(b,n);
    }

    if(!strcmp(fnct,"save")){
    save(b,n);
    menu2(b,n);}
    if(!strcmp(fnct,"quit"))
    {quit2(b);
        menu2(b,n);
    }else menu2(b,n);
}
int main() {books b[100];
    int n=load(b);
    menu(b,n);}
