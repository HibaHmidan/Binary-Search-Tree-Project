#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 100
#define MAX_LINE_LENGTH 200
#define MAX_DATE_LENGTH 15

// Hiba Ala Ali Hmidan 1230454
// section 4


typedef struct{
    int year;
    int month;
    int day;
}Date;

struct Node{
    int ID;
    char name[MAX_NAME_LENGTH];
    Date date;
    float duration;
    int isPerformed;
    struct Node* Left;
    struct Node* Right;
};
typedef struct Node* TNode;

int TreeBuiltBy=0;//0 for Id, 1 for Name, 2 for Date, 3 for Duration
int isloaded=0;// to ensure that the task file is loaded only once

TNode makeEmpty(TNode T);
TNode findByID(int ID,TNode T);
TNode findByName(char name[],TNode T);
TNode findMin(TNode T);
int treeHight(TNode T);
int treeSize(TNode T);
int numOfLeaves(TNode T);
int numOfInternal(TNode T);
TNode createNode(int id,char name[],Date date,float duration,int isPerformed);
Date createDate(char dateStr[]);
int compareDates(Date d1,Date d2);
TNode insertByID(int id,char name[],Date date,float duration,int isPerformed,TNode T);
void printInOrder(TNode T);
void displayMenu();
TNode LoadTasksFile(TNode T);
TNode addTask(TNode T);
TNode DeleteFunc(TNode T);
TNode DeleteByID(int ID,TNode T);
TNode DeleteByName(char name[],TNode T);
TNode searchForTask(TNode T);
TNode performTask(TNode T);
TNode viewUnPerformedTasks(TNode T);
TNode viewPerformedTasks(TNode T);
TNode findIdTrav(int id,TNode T);
TNode findNameTrav(char name[],TNode T);
TNode restructureBST(TNode T);
TNode insertByName(int id,char name[],Date date,float duration,int isPerformed,TNode T);
TNode rebuildByName(TNode T,TNode newT);
TNode insertByDuration(int id,char name[],Date date,float duration,int isPerformed,TNode T);
TNode rebuildByDuration(TNode T,TNode newT);
TNode insertByDate(int id,char name[],Date date,float duration,int isPerformed,TNode T);
TNode rebuildByDate(TNode T,TNode newT);
void PrintPerformedTasksInOrder(TNode T);
void PrintUnPerformedTasksInOrder(TNode T);
TNode rebuildByID(TNode T,TNode newT);
void viewBSTinfo(TNode T);

int main()
{

    TNode T=NULL;
    int choice;
    printf("Welcome to our Task Management System!\n");
    displayMenu();
    scanf("%d",&choice);
    while(choice!=1)//to make sure that the file is loaded before choosing other options
    {
        printf("First,you have to choose 1 to load tasks from file!\n");
        displayMenu();
        scanf("%d",&choice);
    }
    T=LoadTasksFile(T);
    do{
        displayMenu();
        scanf("%d",&choice);
        printf("\n");
        switch(choice){
        case 1:T=LoadTasksFile(T);
               break;
        case 2:T=addTask(T);
               break;
        case 3:T=DeleteFunc(T);
               break;
        case 4:T=searchForTask(T);
               break;
        case 5:T=performTask(T);
               break;
        case 6:T=viewUnPerformedTasks(T);
               break;
        case 7:T=viewPerformedTasks(T);
               break;
        case 8:T=restructureBST(T);
               break;
        case 9:viewBSTinfo(T);
               break;
        case 10:printf("closing program...Bye!\n");
                break;
        default:printf("please enter a valid choice from 1 to 10!\n");
        }

    }while(choice!=10);

    T=makeEmpty(T);


    return 0;
}

TNode makeEmpty(TNode T){
    if(T!=NULL){
        makeEmpty(T->Left);
        makeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

TNode findByID(int ID,TNode T){
    if(T==NULL)
        return NULL;
    else if(ID<T->ID)
        return findByID(ID,T->Left);
    else if(ID>T->ID)
        return findByID(ID,T->Right);
    else
        return T;
}

TNode findByName(char name[],TNode T){
    if(T==NULL)
        return NULL;
    else if(strcmp(name,T->name)<0)
        return findByName(name,T->Left);
    else if(strcmp(name,T->name)>0)
        return findByName(name,T->Right);
    else
        return T;
}

TNode findMin(TNode T){
   if(T!=NULL)
    while(T->Left!=NULL)
        T=T->Left;
   return T;
}

int treeHight(TNode T){
    if(T==NULL)
        return -1;
    int leftHight=treeHight(T->Left);
    int rightHight=treeHight(T->Right);
    if(leftHight>rightHight)
        return leftHight +1;
    else
        return rightHight+1;
}

int treeSize(TNode T){
    if(T==NULL)
        return 0;
    return treeSize(T->Left)+treeSize(T->Right)+1;
}

int numOfLeaves(TNode T){
    if(T==NULL)
        return 0;
    if(T->Left==NULL && T->Right==NULL)
        return 1;
    int numInLeft=numOfLeaves(T->Left);
    int numInRight=numOfLeaves(T->Right);
    return numInLeft+numInRight;
}

int numOfInternal(TNode T){
    return treeSize(T)-numOfLeaves(T);
}

TNode createNode(int id,char name[],Date date,float duration,int isPerformed){
    TNode node=(TNode)malloc(sizeof(struct Node));
    if(node==NULL)
    {
        printf("out of memory\n");
        return NULL;
    }
    node->ID=id;
    strcpy(node->name,name);
    node->date=date;
    node->duration=duration;
    node->isPerformed=isPerformed;
    node->Right=NULL;
    node->Left=NULL;
    return node;
}

Date createDate(char dateStr[]){
    Date date;
    int day=0,year=0,month=0;
    char* portion=strtok(dateStr,"/");
    if(portion!=NULL)//to make sure that date format is correct
       day=atoi(portion);
    else
        printf("incorrect date format!\n");

    portion=strtok(NULL,"/");
     if(portion!=NULL)
       month=atoi(portion);
     else
        printf("incorrect date format!\n");

    portion=strtok(NULL,"/");
    if(portion!=NULL)
       year=atoi(portion);
     else
        printf("incorrect date format!\n");

    date.day=day;
    date.month=month;
    date.year=year;
    return date;
}

int compareDates(Date d1,Date d2){
    if(d1.year>d2.year)
        return 1;
    else if(d1.year<d2.year)
        return -1;
    else{
        if(d1.month>d2.month)
            return 1;
        else if(d1.month<d2.month)
            return -1;
        else {
            if(d1.day>d2.day)
              return 1;
            else if(d1.day<d2.day)
              return -1;
            else
                return 0;
        }
    }

}

TNode insertByID(int id,char name[],Date date,float duration,int isPerformed,TNode T){
    if(T==NULL){
        T=(TNode)malloc(sizeof(struct Node));
        if(T==NULL)
            printf("out of memory\n");
        else{
            T->ID=id;
            strcpy(T->name,name);
            T->date=date;
            T->duration=duration;
            T->isPerformed=isPerformed;
            T->Right=NULL;
            T->Left=NULL;
        }
    }
    else if(id<T->ID)
        T->Left=insertByID(id,name,date,duration,isPerformed,T->Left);
    else if(id>T->ID)
        T->Right=insertByID(id,name,date,duration,isPerformed,T->Right);
    else
        printf("Task ID %d already exist!\n",id);
    return T;
}

void printInOrder(TNode T){
    if(T==NULL)
        return;
    printInOrder(T->Left);
    printf("%d %s %d/%d/%d %.2f  %d\n",T->ID,T->name,T->date.day,T->date.month,T->date.year,T->duration,T->isPerformed);
    printInOrder(T->Right);
}

void displayMenu(){
    printf("\nMenu:\n");
    printf("1. Load Tasks File\n");
    printf("2. Add a New Task\n");
    printf("3. Delete a Task \n");
    printf("4. Search for a Task\n");
    printf("5. Perform a Task\n");
    printf("6. View Unperformed Tasks\n");
    printf("7. View Performed Tasks\n");
    printf("8. Restructure the Tasks BST\n");
    printf("9. View the tasks BST info\n");
    printf("10. Exit\n");
    printf("Please enter your choice: ");
}

TNode LoadTasksFile(TNode T){

    if(isloaded==1){
        printf("Tasks file already loaded!\n");
        return T;
    }

    FILE *file=fopen("tasks.txt","r");

    if(file==NULL){
        printf("File not found\n");
    }else{
       char line[MAX_LINE_LENGTH];
       int p,id,count=0;
       char *name,*dateStr;
       Date date;
       float duration;

    while(fgets(line,MAX_LINE_LENGTH,file)){
        p=0;// here p will count how many portion do we have in each line to ensure that they are 4(id,name,date,duration)
        char *portion=strtok(line,"#");

        while(portion!=NULL){
            p++;
            switch(p){
            case 1:id=atoi(portion);//ASCII to integer
                   break;
            case 2:name=portion;
                   break;
            case 3:dateStr=portion;
                   break;
            case 4:duration=atof(portion);//ASCII to float
                   break;
            }
            portion=strtok(NULL,"#");
        }
        if(p!=4){
            printf("file format for a line is incorrect!\n");// for example if the a line was: 15#submit project 1#5/4/2025#0.1#data , this is incorrect
        }
        else{
            date=createDate(dateStr);
            if(date.year!=0 && date.month!=0 && date.day!=0){
               count++;
               T=insertByID(id,name,date,duration,0,T);
            }
        }
    }
    fclose(file);

    if(count<50){
        printf("At least 50 tasks are required, tasks.txt has only %d!\n",count);
        T=makeEmpty(T);
    }
    else{
      printf("Loaded data from file successfully!\n");
      isloaded=1;
    }
}
    return T;
}


TNode addTask(TNode T){
   int ID;
   char name[MAX_NAME_LENGTH],dateStr[MAX_DATE_LENGTH];
   Date date;
   float duration;
   printf("Please enter Task information below: \n");
   printf("ID: ");
   scanf("%d",&ID);
   if(TreeBuiltBy==0)
       while(findByID(ID,T)!=NULL){// check if ID has already been given to a previous task
        printf("ID already exists, please enter another ID:");
        scanf("%d",&ID);
       }

   printf("Name : ");
   getchar();//clear newline
   gets(name);

   printf("Date(DD/MM/YYYY) : ");
   gets(dateStr);

   printf("Duration : ");
   scanf("%f",&duration);

   date=createDate(dateStr);
   if(date.year==0 || date.month==0 || date.day==0){
        printf("couldn't add tasks because wrong date format!\n");
        return T;
   }
    if(TreeBuiltBy==0)
        T=insertByID(ID,name,date,duration,0,T);
    else if(TreeBuiltBy==1)
        T=insertByName(ID,name,date,duration,0,T);
    else if(TreeBuiltBy==2)
        T=insertByDate(ID,name,date,duration,0,T);
    else if(TreeBuiltBy==3)
        T=insertByDuration(ID,name,date,duration,0,T);

   return T;
}

TNode DeleteFunc(TNode T){
    int option;
    printf("Enter 0 to delete task by ID, or enter 1 to delete task by name ");
    if(TreeBuiltBy==0)
        printf("(It is faster to choose ID!): ");
    else if(TreeBuiltBy==1)
        printf("(It is faster to choose Name!): ");
    scanf("%d",&option);

    if(option==0){
        if(TreeBuiltBy!=0){//this checks that our tree is built by ID because we want to delete task based on ID
        TNode newT=NULL;
        T=rebuildByID(T,newT);
        TreeBuiltBy=0;
        }
        int id;
        printf("please enter the ID to delete: ");
        scanf("%d",&id);
        if(findByID(id,T)==NULL)
            printf("Task not Found!\n");
        else{
          T=DeleteByID(id,T);
          printf("Deleted Task with ID %d!\n",id);
        }
    }else if(option==1){
        if(TreeBuiltBy!=1){
        TNode newT=NULL;
        T=rebuildByName(T,newT);
        TreeBuiltBy=1;
      }
       char name[MAX_NAME_LENGTH];
        printf("please enter task name to perform:");
        getchar();
        gets(name);
        if(findByName(name,T)==NULL)
            printf("Task not Found!\n");
        else{
          T=DeleteByName(name,T);
          printf("Deleted Task with name %s!\n",name);
        }

    }else
        printf("incorrect entered option!\n");


    return T;
}

TNode DeleteByID(int ID,TNode T){
    TNode temp;
    if(T==NULL)
        printf("Task with id %d not found\n",ID);
    else if(ID<T->ID)
        T->Left=DeleteByID(ID,T->Left);
    else if(ID>T->ID)
        T->Right=DeleteByID(ID,T->Right);
    else{
        if(T->Right && T->Left){//if the node has two children
            temp=findMin(T->Right);
            T->ID=temp->ID;
            strcpy(T->name,temp->name);
            T->date=temp->date;
            T->duration=temp->duration;
            T->isPerformed=temp->isPerformed;
            T->Right=DeleteByID(temp->ID,T->Right);
        }
        else{//if the node has one or zero children
            temp=T;
            if(T->Left==NULL)
                T=T->Right;
            else if(T->Right==NULL)
                T=T->Left;
            free(temp);
        }
    }
    return T;
}

TNode DeleteByName(char name[],TNode T){
    TNode temp;
    if(T==NULL)
        printf("Task with name %s not found\n",name);
    else if(strcmp(name,T->name)<0)
        T->Left=DeleteByName(name,T->Left);
    else if(strcmp(name,T->name)>0)
        T->Right=DeleteByName(name,T->Right);
    else{
        if(T->Right && T->Left){//if the node has two children
            temp=findMin(T->Right);
            T->ID=temp->ID;
            strcpy(T->name,temp->name);
            T->date=temp->date;
            T->duration=temp->duration;
            T->isPerformed=temp->isPerformed;
            T->Right=DeleteByName(temp->name,T->Right);
        }
        else{//if the node has one or zero children
            temp=T;
            if(T->Left==NULL)
                T=T->Right;
            else if(T->Right==NULL)
                T=T->Left;
            free(temp);
        }
    }
    return T;
}

TNode searchForTask(TNode T){
    char name[50];
    printf("Please enter a Task Name to search for: ");
    getchar();
    gets(name);
    TNode found;

    if(TreeBuiltBy==1)// if the tree is already built by name
        found=findByName(name,T);//logn
    else
        found=findNameTrav(name,T);//O(n)

    if(found==NULL)
            printf("Task not found!\n");
        else
           printf("Task ID: %d, Task name: %s, Task date: %d/%d/%d,Task Duration: %.2f, isPerformed=%d\n",found->ID,found->name,found->date.day,found->date.month,found->date.year,found->duration,found->isPerformed);

    return T;
}

TNode performTask(TNode T){
    int option;
    printf("Enter 0 to perform task by ID, or enter 1 to perform task by name ");
    if(TreeBuiltBy==0)
        printf("(It is faster to choose ID now!): ");
    else if(TreeBuiltBy==1)
        printf("(It is faster to choose Name now!): ");
    scanf("%d",&option);

    TNode found;
    if(option==0){
        int id;
        printf("please enter task ID to perform:");
        scanf("%d",&id);

        if(TreeBuiltBy==0)// if the tree is already built by name
            found=findByID(id,T);//logn
        else
            found=findIdTrav(id,T);//O(n)


        if(found==NULL)
            printf("Task not found!\n");
        else{
            if(found->isPerformed==0){
              found->isPerformed=1;
                printf("Performed Task with ID %d successfully!\n",id);
            }
            else
                printf("Task already performed!\n");
        }
    }else if(option==1){
        char name[MAX_NAME_LENGTH];
        printf("please enter task name to perform:");
        getchar();
        gets(name);

        if(TreeBuiltBy==1)// if the tree is already built by name
            found=findByName(name,T);//logn
        else
            found=findNameTrav(name,T);//O(n)

        if(found==NULL)
            printf("Task not found!\n");
        else{
            if(found->isPerformed==0){
              found->isPerformed=1;
                printf("Performed Task with name %s successfully!\n",name);
            }
            else
                printf("Task already performed!\n");
        }
    }
    else
        printf("incorrect entered option!\n");

    return T;
}

TNode viewUnPerformedTasks(TNode T){
    if(TreeBuiltBy!=1){//this makes sure that our tree is built by name because we want to print unerformed tasks based on name
        TNode newT=NULL;
        T=rebuildByName(T,newT);
        TreeBuiltBy=1;
    }
    printf("Unperformed tasks sorted by Task Name:\n\n");
    PrintUnPerformedTasksInOrder(T);
    return T;
}

TNode viewPerformedTasks(TNode T){
    if(TreeBuiltBy!=0){
        TNode newT=NULL;
        T=rebuildByID(T,newT);
        TreeBuiltBy=0;
    }
        printf("Performed tasks sorted by Task ID:\n\n");
        PrintPerformedTasksInOrder(T);
        return T;
}

void PrintPerformedTasksInOrder(TNode T){
    if(T==NULL)
        return;
    PrintPerformedTasksInOrder(T->Left);
    if(T->isPerformed==1)
       printf("Task ID: %-5d,  name: %-25s,  date: %2d/%2d/%4d,    Duration: %.2f \n",T->ID,T->name,T->date.day,T->date.month,T->date.year,T->duration);
    PrintPerformedTasksInOrder(T->Right);
}

void PrintUnPerformedTasksInOrder(TNode T){
    if(T==NULL)
        return;
    PrintUnPerformedTasksInOrder(T->Left);
    if(T->isPerformed==0)
        printf("Name:%-25s,ID: %-5d,    date: %2d/%2d/%4d,    Duration: %.2f  \n",T->name,T->ID,T->date.day,T->date.month,T->date.year,T->duration);
    PrintUnPerformedTasksInOrder(T->Right);
}

TNode findIdTrav(int id,TNode T){//this to find id with O(n) if tree is not built by name
    if(T==NULL)
       return NULL;
    else if(id==T->ID)
        return T;
    TNode inLeft=findIdTrav(id,T->Left);
    if(inLeft!=NULL)
        return inLeft;
    TNode inRight=findIdTrav(id,T->Right);
    return inRight;
}

TNode findNameTrav(char name[],TNode T){//this to find name with O(n) if tree is not built by name
    if(T==NULL)
       return NULL;
    else if(strcmp(name,T->name)==0)
        return T;
    TNode inLeft=findNameTrav(name,T->Left);
    if(inLeft!=NULL)
        return inLeft;
    TNode inRight=findNameTrav(name,T->Right);
    return inRight;
}

TNode restructureBST(TNode T){
    int choice;
    printf("Enter 1 to rebuild tree by task name, 2 to rebuild it by task date, 3 to rebuild it by task duration: ");
    scanf("%d",&choice);
    TNode newT=NULL;
   switch(choice){
    case 1:if(TreeBuiltBy==1)//this is the flag that decides what the tree is built by
             printf("Tree is already structured by Name from previous choices!\n");
            else{
                newT=rebuildByName(T,newT);
                T=newT;
                printf("Tree built successfully by Name!\n");
                TreeBuiltBy=1;
            }
            break;
    case 2:if(TreeBuiltBy==2)
             printf("Tree is already structured by Date from previous choices!\n");
            else{
                newT=rebuildByDate(T,newT);
                T=newT;
                printf("Tree built successfully by Date!\n");
                TreeBuiltBy=2;
            }
           break;
    case 3:if(TreeBuiltBy==3)
             printf("Tree is already structured by Duration from previous choices!\n");
            else{
                 newT=rebuildByDuration(T,newT);
                 T=newT;
                 printf("Tree built successfully by Duration!\n");
                 TreeBuiltBy=3;
            }
           break;
    default: printf("incorrect entered number!\n");
           break;
   }
   return T;
}

TNode insertByName(int id,char name[],Date date,float duration,int isPerformed,TNode T){
    if(T==NULL){
        T=(TNode)malloc(sizeof(struct Node));
        if(T==NULL)
            printf("out of memory\n");
        else{
            T->ID=id;
            strcpy(T->name,name);
            T->date=date;
            T->duration=duration;
            T->isPerformed=isPerformed;
            T->Right=NULL;
            T->Left=NULL;
        }
    }
    else if(strcmp(name,T->name)>0)
        T->Right=insertByName(id,name,date,duration,isPerformed,T->Right);
    else if(strcmp(name,T->name)<0)
        T->Left=insertByName(id,name,date,duration,isPerformed,T->Left);
    else
        printf("Task Name %s already exists!\n",T->name);
    return T;
}

TNode rebuildByName(TNode T,TNode newT){

    if(T!=NULL)
    {
       newT=rebuildByName(T->Left,newT);
       newT=rebuildByName(T->Right,newT);

       newT=insertByName(T->ID,T->name,T->date,T->duration,T->isPerformed,newT);
       free(T);// after we insert each node info to the newT we immediately free it from the previous tree to save space
    }
    return newT;
}

TNode insertByDuration(int id,char name[],Date date,float duration,int isPerformed,TNode T){
    if(T==NULL){
        T=(TNode)malloc(sizeof(struct Node));
        if(T==NULL)
            printf("out of memory\n");
        else{
            T->ID=id;
            strcpy(T->name,name);
            T->date=date;
            T->duration=duration;
            T->isPerformed=isPerformed;
            T->Right=NULL;
            T->Left=NULL;
        }
    }
    else if(duration>T->duration)
        T->Right=insertByDuration(id,name,date,duration,isPerformed,T->Right);
    else if(duration<T->duration)
        T->Left=insertByDuration(id,name,date,duration,isPerformed,T->Left);
    else
        printf("Task Duration %f already exists!\n",T->duration);
    return T;
}

TNode rebuildByDuration(TNode T,TNode newT){

    if(T!=NULL)
    {
      newT=rebuildByDuration(T->Left,newT);
      newT=rebuildByDuration(T->Right,newT);

      newT=insertByDuration(T->ID,T->name,T->date,T->duration,T->isPerformed,newT);
      free(T);// after we insert each node info to the newT we immediately free it from the previous tree to save space
    }
   return newT;
}

TNode insertByDate(int id,char name[],Date date,float duration,int isPerformed,TNode T){
    if(T==NULL){
        T=(TNode)malloc(sizeof(struct Node));
        if(T==NULL)
            printf("out of memory\n");
        else{
            T->ID=id;
            strcpy(T->name,name);
            T->date=date;
            T->duration=duration;
            T->isPerformed=isPerformed;
            T->Right=NULL;
            T->Left=NULL;
        }
    }
    else if(compareDates(date,T->date)<0)
        T->Left=insertByDate(id,name,date,duration,isPerformed,T->Left);
    else if(compareDates(date,T->date)>0)
        T->Right=insertByDate(id,name,date,duration,isPerformed,T->Right);
    else
        printf("Date %d/%d/%d already exist!\n",date.day,date.month,date.year);
    return T;
}

TNode rebuildByDate(TNode T,TNode newT){
    if(T!=NULL)
    {
      newT=rebuildByDate(T->Left,newT);
      newT=rebuildByDate(T->Right,newT);


      newT=insertByDate(T->ID,T->name,T->date,T->duration,T->isPerformed,newT);
      free(T);// after we insert each node info to the newT we immediately free it from the previous tree to save space
    }
   return newT;
}

TNode rebuildByID(TNode T,TNode newT){

    if(T!=NULL)
    {
      newT=rebuildByID(T->Left,newT);
      newT=rebuildByID(T->Right,newT);

      newT=insertByID(T->ID,T->name,T->date,T->duration,T->isPerformed,newT);
      free(T);// after we insert each node info to the newT we immediately free it from the previous tree to save space
    }
   return newT;
}

void viewBSTinfo(TNode T){
    if(TreeBuiltBy==0)//first we check how the tree is built
        printf("Tasks tree is currently built by ID and this is its info:\n");
    else if(TreeBuiltBy==1)
        printf("Tasks tree is currently built by Name and this is its info:\n");
    else if(TreeBuiltBy==2)
        printf("Tasks tree is currently built by Date and this is its info:\n");
    else
        printf("Tasks tree is currently built by Duration and this is its info:\n");

    printf("Tree hight is : %d\n",treeHight(T));
    printf("Tree size is : %d\n",treeSize(T));
    printf("Number of leaves is : %d\n",numOfLeaves(T));
    printf("Number of internal nodes is : %d\n",numOfInternal(T));
}
