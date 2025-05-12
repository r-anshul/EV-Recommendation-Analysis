#include <iostream>
#include <string>
#include <unistd.h>
#include "urls.h">

using namespace std;
using namespace sites;

class pdata
{
public:
    int b;  //budget
    string usg; //usage
    char exp; //rider experience
    int dis; //distance
    int a; //age of the user
};
void opensite(string s)
{
	string command = "start " + s;
        	system(command.c_str());
}
void b20k(pdata& P) {
    char tc;
    bool rh; //rough terrain
    cout << "Based on your current budget and experience, let me ask you a few questions"<<endl;
    cout << "Do you look forward to using this bike for 'commute' or 'leisure'? ";
    cin.ignore();
    getline(cin, P.usg);
    if (P.usg=="commuting"||P.usg=="commute"||P.usg=="Commuting"||P.usg=="Commute")
	{
        cout << "A hybrid bike would be good for you.\n";
        cout << "How much is your daily commute?(kms) - \n";
        cin>>P.dis;
        cout << "Does your commute route have bad road patches (Y/N)? -\n";
        cin>>tc;
        rh = tc=='Y'?true:false;
        if(P.dis<=5&&rh)
        {
        	cout<<"A Single speed Hybrid with a suspension will be a good choice for you"<<endl;  //Hybrid Suspension SS
        	cout<<"Let me show you options online!\n";
        	sleep(2);
        	opensite(sites::hsss);
		}
		if(P.dis>5&&rh)
        {
        	cout<<"A geared Hybrid with a suspension will be a good choice for you"<<endl;  //HYbrid
        	cout<<"Let me show you options online!\n";
        	sleep(2);
        	opensite(sites::hgs);
		}
		if(P.dis>5&&!rh)
        {
        	cout<<"A geared Hybrid will be a good choice for you"<<endl;  //Geared Hybrid
        	cout<<"Let me show you options online!\n";
        	sleep(2);
        	opensite(sites::hg);
		}
		if(P.dis<=5&&!rh)
        {
        	cout<<"A single speed Hybrid will be a good choice for you"<<endl;
        	cout<<"Let me show you options online!\n";
        	sleep(2);
        	opensite(sites::hss);
		}
    } else if (P.usg=="leisure"||P.usg == "Leisure")
	{
        cout << "For leisure rides any bicycle can be a good option\n";
        cout<<"Would you like to see Mountain bikes(M) or Road based(R)? - ";
        cin>>tc;
        if(tc=='M'||tc=='m')
        {
        	cout<<"Let me show you options online!\n";
        	sleep(2);
        	opensite(sites::lm);
    	}
        else if(tc=='R'||tc=='r')
        {
        	cout<<"Let me show you options online!\n";
        	sleep(2);
        	opensite(sites::lr);
		} 
    } else {
        cout << "Consider Upgrading your budget for other purposes.\n";
    }
}
void b50k(pdata& P)
{
    char tc;
    bool rh; //rough terrain
    cout << "Based on your current budget and experience, let me ask you a few questions"<<endl;
    cout << "Do you look forward to using this bike for 'commute', 'leisure' or other? ";
    cin.ignore(); // Clear the newline from the previous input
    getline(cin, P.usg);
    if (P.usg=="commuting"||P.usg=="commute"||P.usg=="Commuting"||P.usg=="Commute")
	{
        cout << "A hybrid bike would be good for you.\n";
        cout << "How much is your daily commute?(kms) - ";
        cin>>P.dis;
        cout << "Does your commute route have bad road patches (Y/N)?\n";
        cin>>tc;
        rh = tc=='Y'?true:false;
        if(rh)
        {
        	cout<<"A Hybrid with a suspension will be a good choice for you"<<endl;
        	cout<<"Let me show you some options online!\n";
        	sleep(2);
        	opensite(sites::hs);
		}
		if(!rh)
        {
        	cout<<"A Hybrid will be a good choice for you."<<endl;
        	cout<<"Let me show you some options online!\n";
        	sleep(2);
        	opensite(sites::h);
		}
    }
	else if (P.usg=="leisure"||P.usg == "Leisure")
	{
        cout << "For leisure rides any bicycle can be a good option\n";
        cout<<"Would you like to see Mountain bikes(M) or Road based(R)? - ";
        cin>>tc;
        if(tc=='M'||tc=='m')
        {
        	cout<<"Let me show you some options online!\n";
        	sleep(2);
        	opensite(sites::lm50);
    	}
        else if(tc=='R'||tc=='r')
        {
        	cout<<"Let me show you some options online!\n";
        	sleep(2);
        	opensite(sites::lr50);
		} 
    }
	else
	{
        cout << "Consider Upgrading your budget for other purposes.\n";
    }
}
void c50k(pdata& P)
{
    string cat;  //category
    cout << "Based on your current budget and experience, just a few more questions."<<endl;
    cout << "Do you wish to compete in MTB races or ROAD racing ";
    cin.ignore();
    getline(cin, cat);
    if (cat=="mtb"||cat=="MTB")
	{
        cout<<"Let me show you some MTBs online in your budget.\n";
        sleep(2);
        opensite(sites::cm50);
    }
	else if (cat=="road"||cat=="ROAD")
	{
        cout<<"Road bikes are more expensive as compared to MTBs, let me show you some bikes online that might be near your budget.\n";
        sleep(2);
        opensite(sites::cr50);
    }
}
void c100k(pdata& P)
{
    string cat;  //category
    cout << "Based on your current budget and experience, let me ask you a few questions"<<endl;
    cout << "Do you wish to compete in MTB races, ROAD racing or GRAVEL ";
    cin.ignore();
    getline(cin, cat);
    if (cat=="mtb"||cat=="MTB")
	{
        cout<<"Let me show you some MTBs online in your budget.\n";
        sleep(2);
        opensite(sites::cm100);
    } 
	else if (cat=="road"||cat=="ROAD")
	{
        cout<<"Road bikes are more expensive as compared to MTBs, let me show you some bikes online that might be near your budget.\n";
        sleep(2);
        opensite(sites::cr100);
    }
	else if (cat=="gravel"||cat=="GRAVEL")
	{
        cout<<"Gravel bikes are a mix of RoadBikes and MTBs. Let me show you some options online\n";
        sleep(2);
        opensite(sites::g100);
    }
}
void pro(pdata& P)
{
	char ch,chs,chm,chf;
	cout<<"Which bike type are you interested in?\n";
	cout<<"Road(R), Mountain(M), Gravel(G) or Freestyle(F)\n";
	cin>>ch;
	switch(ch)
	{
		case 'R':
			{
			cout<<"SELECTED - ROAD\n";
			cout<<"Select sub category - Race(R), Endurance(E)\n";
			cin>>chs;
			if(chs=='R'||chs=='r')
			{
				cout<<"You can choose between TT bikes(1) and Road bikes(2)\n";
				int c;
				cin>>c;
				switch(c)
				{
					case 1:
						cout<<"TT bikes are the fastest (and also the most expensive). Let me show you some online.\n";
						sleep(2);
						opensite(sites::tt);
						break;
					case 2:
						cout<<"Let me show you some road bikes online.\n";
						sleep(2);
						opensite(sites::rp);
						break;
				}
			}
			if(chs=='E'||chs=='e')
			{
				cout<<"Do you plan to tour with your bike (Y/N)?\n";
				char che;
				cin>>che;
				if(che=='Y'||che=='y')
				{
					cout<<"Let me show you some touring bikes online.\n";
					sleep(2);
					opensite(sites::en);
				}
				else cout<<"No bikes for your preferences :(\n";
			}
			break;
		}
		case 'G':
			{
				cout<<"Let me show you some Gravel options then.\n";
				sleep(2);
				opensite(sites::g);
				break;
			}
		case 'M':
			{
				cout<<"Are you looking for XC(X), Enduro(E) or Downhill(D) bikes?\n";
				cin>>chm;
				if(chm=='X'||chm=='x')
				{
					cout<<"Let me show you some XC options then.\n";
					sleep(2);
					opensite(sites::x);
				}
				if(chm=='D'||chm=='d')
				{
					cout<<"Let me show you some Downhill options then.\n";
					sleep(2);
					opensite(sites::dh);
				}
				if(chm=='E'||chm=='e')
				{
					cout<<"Let me show you some Enduro options then.\n";
					sleep(2);
					opensite(sites::ed);
				}
				break;
			}
			case 'F':
			{
				cout<<"Would you like to see BMX(B) options or Dirtjumpers(D)?\n";
				cin>>chf;
				if(chf=='B'||chf=='b')
				{
					cout<<"Let me show you some BMX options then.\n";
					sleep(2);
					opensite(sites::bmx);
				}
				if(chf=='D'||chf=='d')
				{
					cout<<"Let me show you some Dirtjumper options then.\n";
					sleep(2);
					opensite(sites::dj);
				}
				break;
			}
	}
}
void welcome(pdata& P)
{
    char chc;  //competitive
    cout<<"Enter Your age - ";
    cin>> P.a;
    cout<<"Plesae note that if you are under 18 years of age, you will be considered a Beginner!!\n";
    cout << "To get started, what would you consider yourself as a cyclist? "<<endl;
    cout << "Beginner(B), Intermediate(I) or Professional(P)"<<endl;
    cin >> P.exp;
    cout << "Now, Please enter a budget - ";
    cin>>P.b;
    if (P.exp=='B'||P.exp=='b'||P.a<=18)
	{
        if(P.b<=20000)
		b20k(P);
		else if (P.b <= 50000&&P.b>20000)
        b50k(P);
    }
    if (P.exp=='I'||P.exp=='i'||P.a>18)
    {
		cout<<"Do you wish to start competitive cycling? (Y/N) \n";
		cin>>chc;
	if (chc=='Y'||chc=='y')
	{
        if(P.b<=20000)
		cout<<"Please consider increasing your budget.\n";
		if (P.b <= 50000&&P.b>20000)
        c50k(P);
        if(P.b>50000&&P.b<=100000)
        c100k(P);
	}
	if(chc=='N'||chc=='n')
	{
		if(P.b<=20000)
		b20k(P);
		else if (P.b<=50000&&P.b>20000)
        b50k(P);
	}
}
	if (P.exp=='P'||P.exp=='p')
    {  
    	cout<<"NOTE - You have selected the 'PROFESSIONAL' category, some results may be out of your bugdet. Choose accordingly.\n";
		pro(P);
	}
}

int main()
{
    pdata P; // Create a pdata object to hold user data
    char c='Y';
	cout << "**** Hi user, WELCOME to the Bike Recommender ****\n" << endl;
	do
	{
	welcome(P);
	cout<<"You can restart the process if you are not satisfied with the results. Restart? (Y/N)\n";
	cin>>c;
	}while (c=='Y');
	cout<<"\n**** THANK YOU FOR USING THIS PROGRAM ****";
    return 0;
}
