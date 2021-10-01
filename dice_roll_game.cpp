#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

int Deposit_money(int curr_amount)
{
    int amount;
    cout << "Enter the amount you want to deposit: ";
    bool tmp = false;
    while (tmp == false)
    {
        cin >> amount;
        if ((amount > 0 && amount <= 5000) || (amount + curr_amount <= 5000))
        {
            cout << "RS." << amount << " Depositted successfully." << endl;
            curr_amount = curr_amount + amount;
            tmp = true;
        }
        else if (amount <= 0)
        {
            cout << "ERROR: please enter amount greater than RS.0. ";
        }
        else
        {
            int depositable_amount = 5000 - curr_amount;
            cout << "ERROR: Account limit reached. you can add maximum RS." << depositable_amount << endl;
        }
    }
    return curr_amount;
}

int choose_bet(int curr_amount)
{
    int bets[] = {100, 300, 500};
    char input;
    int input_bet;
    cout << "Choose your bet. " << endl;
    bool tmp = false;
    while (tmp == false)
    {
        cout << "Please press 1 for RS.100 , 2 for RS.300 , 3 for RS.500 ";
        cin >> input_bet;
        if ((input_bet == 1) || (input_bet == 2) || (input_bet == 3))
        {
            
            if ((input_bet == 1 &&curr_amount < 100) || (input_bet == 2 && curr_amount < 300) || (input_bet == 3 && curr_amount < 500))
            {
                cout << "Error: Your current balance is not enough to play on this bet." << endl;
                bool tmp2 = false;
                while (tmp2 == false)
                {
                    cout << "Press d to deposit money or c to change bet.";
                    cin >> input;
                    if (input == 'd')
                    {
                        tmp2 = true;
                        curr_amount = Deposit_money(curr_amount);
                        cout << "Current Balance = " << curr_amount << endl;
                        return choose_bet(curr_amount);
                    }
                    else if (input == 'c')
                    {
                        tmp2 = true;
                        return choose_bet(curr_amount);
                    }
                    else
                    {
                        cout<<"Error: ";
                    }
                }
            }
            else
            {
                return bets[input_bet - 1];
            }
            tmp = true;
        }
        else
        {
            cout << "Error: ";
        }
    }
}

int Start_game(string user1,int bet, int curr_amount)
{
    string user2="computer";
    string round_winner[3];
    cout << "Press s to start the game. ";
    char input;
    cin>>input;
    bool tmp=false;
    while (tmp==false)
    {
        if(input=='s')
        {
            for(int i=0;i<3;i++)
            {
                cout<<"---------------------"<<endl;
                cout<<"Round "<<i+1<<endl;
                cout<<"---------------------"<<endl;
                cout<<">>>>>> Your turn >>>>>> "<<endl;
                int user1_turn;
                bool tmp2=false;
                while (tmp2==false)
                {
                    cout<<"Press r to roll the dice : ";
                    cin>>input;
                    
                    if(input=='r')
                    {
                        tmp2=true;
                        srand(time(0));
                        user1_turn= rand() % 6 + 1;
                        cout<<user1<<" = "<<user1_turn<<endl;
                    }
                    else
                    {
                        cout<<"Error: ";
                    }
                }
                cout<<">>>>>> Computer's turn >>>>>>"<<endl;
                int user2_turn = rand() % 6 + 1;
                cout<<user2<<" = "<<user2_turn<<endl;
                if(user1_turn>user2_turn)
                {
                    round_winner[i]=user1;
                }
                else if(user1_turn<user2_turn)
                {
                    round_winner[i]=user2;
                }
                if(i==1 && round_winner[0]==round_winner[1])
                {
                     if(round_winner[1]==user1)
                     {
                        cout<<"*********************"<<endl;
                        cout<<"SUPERB. You Won!!"<<endl;
                        cout<<"*********************"<<endl;
                        curr_amount=curr_amount+(2*bet);
                     }
                    else
                    {
                        cout<<"*********************"<<endl;
                        cout<<"ALAS. You lose!!"<<endl;
                        cout<<"*********************"<<endl;
                    }
                    return curr_amount;
                }
                else if (i==2)
                {
                    if(round_winner[2]==user1)
                    {
                        cout<<"*********************"<<endl;
                        cout<<"SUPERB. You Won!!"<<endl;
                        cout<<"*********************"<<endl;
                        curr_amount=curr_amount+(2*bet);
                    }
                    else
                    {
                        cout<<"*********************"<<endl;
                        cout<<"ALAS. You lose!!"<<endl;
                        cout<<"*********************"<<endl;
                    }
                    return curr_amount;
                }         
            }
        }
    }
}


int main()
{
    cout << "WELCOME to the Dice Roller Game!" << endl;
    cout << "Enter your name :";
    string name;
    cin >> name;
    int account_balance = 0;
    cout << "Current Balance = " << account_balance << endl;
    bool tmp =false;
    char input;
    while(tmp==false)
    {
        cout << "Press d if you want to deposit money. ";
        input='d';
        cin >> input;
        if (input == 'd')
        {
            tmp=true;
            account_balance = Deposit_money(account_balance);
        }
        else
        {
            cout<<"ERROR: ";
        }
    }
    cout << "Current Balance = " << account_balance << endl<< endl;
    cout << "Press p if you want to play. ";
    cin >> input;
    int games_won=0;
    int i=0;
    while (input == 'p')
    {
        int bet=choose_bet(account_balance);
        int remaining_balance=account_balance-bet;
        cout << "Remaining Balance = " << remaining_balance << endl<< endl;
        
        account_balance = Start_game(name,bet,remaining_balance);
        cout << "Current Balance = " <<account_balance<< endl<< endl;
        if(account_balance>remaining_balance)
        {
            games_won=games_won+1;
        }
        cout << "Press p to play again or q to quit.";
        cin >> input;
        i++;
    }
    cout<<"-----------------"<<endl;
    cout<<"Summary: "<<endl;
    cout<<"player = "<<name<<endl;
    cout<<"Account Balance = "<<account_balance<<endl;
    cout<<"Total number of games played = "<<i<<endl;
    cout<<"Games won = "<<games_won<<endl;
    return 0;
}