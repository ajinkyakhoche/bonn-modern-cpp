#include<iostream>
#include<cstdlib>
#include <experimental/random>

using namespace std;

int main()
{
    //int num=rand(), guess;
    int num=experimental::randint(0, 1000), guess;

    cout<<"Enter a number:"<<endl;
    cin>>guess;

    while(guess!=num)
    {
        if(guess>num)
            cout<<"Your guess is greater"<<endl;
        else if(guess<num)
            cout<<"Your guess is smaller"<<endl;

        cout<<"Enter a number:"<<endl;
        cin>>guess;
    }
    return 0;
}

