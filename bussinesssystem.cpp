#include<iostream>
using namespace std;
//once the code is done add minimum intial balance to impress
class account{
    public:
    string name;
    int accountNumber;
    int balance;
    int password;
    accDetails(string a, int p, int b ) {
        name = a;
        password = p;
        balance = b;
    }
    



}
int blnc(int depo, int with, int available){

    
    account.balance = available + depo - with;

}

int main() {
    cout<<"Welcome to iiti bank"<<endl;
    cout<<"To open new account press 'n'"<<endl;
    cout<<"To deposit cash enter 'd'"<<endl;
    cout<<"To check balance enter 'b' "<<endl;
    cout<<"To transfer money enter 't'"<<endl;
    cout<<"To withdraw cash enter 'w'"<<endl;
    char command;





    return 0;
}