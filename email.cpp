#include<bits/stdc++.h>
#include<time.h>

using namespace std;

struct email
{
    char time_s[20];
    char time_e[20];
    int attempt;
    struct email *next;
};

struct email *front, *rear, *top, *temp;
int t_msg, arrival, sent, que_size,d;

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void enqueue()
{
    time_t lt;
    lt=time(NULL);
    temp = (email*)malloc(sizeof(struct email));
    strcpy(temp->time_s,ctime(&lt));
    temp->attempt=1;
    temp->next = NULL;
    cout<<"Received"<<endl;
    if(front==NULL){
        front = temp;
        rear = temp;
    }
    else{
        rear->next=temp;
        rear = temp;
    }
    t_msg++;
    arrival++;
}

void push(struct email *node)
{
    time_t lt;
    lt=time(NULL);
    struct email *curr;
    curr=(email*)malloc(sizeof(struct email));
    strcpy(curr->time_s,node->time_s);
    strcpy(curr->time_e,ctime(&lt));
    curr->attempt = node->attempt;
    curr->next = NULL;

    if(top==NULL){
        top=curr;
    }
    else{
        curr->next=top;
        top=curr;
    }
}

void dequeue()
{
    if(front!=NULL ){
        temp = front;
        front = front->next;
        if(d<5){
            push(temp);
            free(temp);
            temp = NULL;
            t_msg++;
            sent++;
            d++;
            cout<<"Sent"<<endl;
        }
        else{
            temp->attempt++;
            temp->next=NULL;
            rear->next = temp;
            rear = temp;
        }
    }
    else if(front==NULL){
        cout<<"Inbox is empty!"<<endl;
    }
}

int size_queque()
{
    int s=0;
    struct email *curr;
    curr=front;
    while(curr!=NULL){
        curr = curr->next;
        s++;
    }
    return s;
}


void operation()
{
    int e=0;
    while(clock()<60000){
        srand((unsigned)time(NULL));
        int i=rand()%3;
        switch(i)
        {
        case 0:
            //system("COLOR 0A");//green
            delay(2);
            if(e<10)
                enqueue();
            e++;
            break;
        case 1:
            delay(2);
            //system("COLOR 07");//gray
            if(e<10)
                enqueue();
            e++;
            dequeue();
            break;
        case 2:
            delay(2);
            //system("COLOR 05");//purple
            dequeue();
            break;
        }
    }
    que_size = que_size + size_queque();
    return;
}

void display()
{
    struct email *curr;
    cout<<"The number of messages arrived: "<<arrival<<endl;
    cout<<"The number of messages sent : "<<sent<<endl;
    cout<<"Total messages processed: "<<t_msg<<endl<<endl;
    int i = clock()/60000;
    cout<<"Arrival rate: "<<arrival/i<<endl;
    cout<<"Average number of messages sent per minute: "<<sent/i<<endl;
    cout<<"Average number of messages in the queue in a  minute: "<<que_size/i<<endl;

    int  attem[5]={0,0,0,0,0};
    curr = top;
    while(curr!=NULL){
        if(curr->attempt==1){
            attem[0]++;
        }
        else if(curr->attempt==2){
            attem[1]++;
        }
        else if(curr->attempt==3){
            attem[2]++;
        }
        else if(curr->attempt==4){
            attem[3]++;
        }
        else if(curr->attempt==5){
            attem[4]++;
        }
        curr=curr->next;
    }
    cout<<"The number of messages sent on 1st attempt: "<<attem[0]<<endl;
    cout<<"The number of messages sent on 2nd attempt: "<<attem[1]<<endl;
    cout<<"The number of messages sent on 3rd attempt: "<<attem[2]<<endl;
    cout<<"The number of messages sent on 4th attempt: "<<attem[3]<<endl;
    cout<<"The number of messages sent on 5th attempt: "<<attem[4]<<endl;

}

int main()
{

    front=NULL;
    top=NULL;
    d = 0;
    t_msg=0;
    arrival=0;
    sent=0;
    que_size=0;
    operation();
    cout<<"Operation ok"<<endl;
    display();

}
