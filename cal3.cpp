#include<iostream>
using namespace std;
int exponent(int n1, int n2){
    int result = 1;
    int calc = 1;
    int mul =0;
    while(mul < n2) {
    result = calc*n1;
    calc = result;
       mul++;  
       
    }
    
    
    return result;
}
 
int main() {
    double num1;
    double num2;
    char opt;
    double result;
    cout<<"for selecting sin enter 's' "<<endl;
    cout<<"for selecting cos enter 'c'"<<endl;
    cout<<"for selecting e^x enter 'e'"<<endl;
    cout<<"for selecting a^b enter 'a'"<<endl;
    cout<<"enter operator ";
    cin>>opt;
    switch(opt) {
        case '+':
        cout<<"enter first number ";
        cin>>num1;
        cout<<"enter second number ";
        cin>>num2;
        result = num1 + num2;
        break;
        case '-':
        cout<<"enter first number ";
        cin>>num1;
        cout<<"enter second number ";
        cin>>num2;
        result = num1 - num2;
        break;
        case '*':
        cout<<"enter first number ";
        cin>>num1;
        cout<<"enter second number " ;
        cin>>num2;
        result = num1*num2;
        break;
        case '/':
        cout<<"enter first number ";
        cin>>num1;
        cout<<"enter second number ";
        cin>>num2;
        result = num1/num2;
        break;
        case 's':
        cout<<"enter the angle in radians ";
        cin>>num1;
        result = num1 - num1*num1*num1/6 + num1*num1*num1*num1*num1/120 ;
        break; 
        case 'c':
        cout<<"enter the angle in radians ";
        cin>>num1;
        result =  1 - num1*num1/2 + num1*num1*num1*num1/24 ;
        break;
        case 'e':
        cout<<"enter the number ";
        cin>>num1;
        result = 1 + num1 + num1*num1/2 ;
        break;
        case 'a':
        cout<<"enter a ";
        cin>>num1;
        cout<<"enter b ";
        cin>>num2;
        result = exponent(num1, num2);
        break;
        default :
        cout<<"invalid operator selected";
        
    }
   
   cout<<result;
   
   return 0; 
}