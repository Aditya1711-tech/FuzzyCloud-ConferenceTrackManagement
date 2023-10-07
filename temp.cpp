#include<iostream>
#include<vector>
#include<string>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#define ll long long int
using namespace std;

int countNumberOfDays(vector<int> &timings)
{
    int totalTime = 0;
    for (auto it : timings)
    {
        totalTime += it;
    }
    int totalHours = totalTime / 60;
    int totalDays = ceil((double)totalHours / (double)7);
    return totalDays;
}

bool generateTrackes(int ind, int minuits, int limit,int countLunch,int countDay,int days,int cntEvents,int n, vector<int> &vis, vector<int> &timings,
              vector<pair<int, int> > &sessions)
{
    if (countDay == days && countLunch == days && cntEvents == n)
    {
        return true;
    }

    if (countDay == days && countLunch == days && (cntEvents < n || cntEvents > n))
    {
        return false;
    }

    if(minuits > limit) return false;

    if(minuits == limit && countLunch == countDay){
        sessions.push_back(make_pair(60,-1));
        if (generateTrackes(ind, 0, 240,countLunch+1,countDay,days,cntEvents,n,vis, timings, sessions))
                return true;
        sessions.pop_back();
    }

    if(minuits > 180 && minuits <= limit && countLunch > countDay){
        sessions.push_back(make_pair(60,-2));
        if (generateTrackes(ind, 0, 180,countLunch,countDay+1,days,cntEvents,n,vis, timings, sessions))
                return true;
        sessions.pop_back();
    }

    for (int i = 0; i < timings.size(); i++)
    {
        if (!vis[i] && minuits + timings[i] <= limit)
        {
            vis[i] = 1;
            sessions.push_back(make_pair(timings[i],i));
            if (generateTrackes(i, minuits + timings[i], limit,countLunch,countDay,days,cntEvents+1,n,vis, timings, sessions))
                return true;
            sessions.pop_back();
            vis[i] = 0;
        }
    }
    return false;
}

void printOutput(vector<pair<int, int> >& sessions,vector<string>& timingsStr, int& days){
    int h = 9,m = 0; 
    int track = 1;
    cout<<endl<<"Track: "<<track<<endl;
    for (auto it : sessions)
    {
        cout << h << ":";
        if(m == 0){
            cout<<m<<0<<" ";
        }else{
            cout<<m<<" ";
        }
        if (it.second == -1)
            cout << "Luch time";
        else if (it.second == -2){
            cout << "Network session"<<endl<<endl;
            track++;
            if(track <= days){
                cout<<"Track: "<<track;
            }
            h = 8;
            m = 0;
        }
        else
            cout << timingsStr[it.second];
        cout << endl;

        m += it.first;
        if(m >= 60){
            h += 1;
            m -= 60;
        } 
        if(h != 12) h %= 12;
    }
}

int main()
{
    int n;
    cout << "Enter number of events: ";
    cin >> n;
    cout << "Start entering timings of events: " << endl;
    int tempN = n;
    vector<int> timings;
    vector<string> timingsStr;
    while (tempN--)
    {
        string x;
        getline(cin >> ws, x);
        string strInt = "";
        string str = "";
        string light = "";
        if(x[x.size()-1] == 'g'){
            timings.push_back(5);
        }
        else{
            for (int i = x.length() - 4; i >= x.length() - 5; i--)
            {
                strInt = x[i] + strInt;
            }
            int xInt = stoi(strInt);

            timings.push_back(xInt);
        }
        timingsStr.push_back(x);
    }
    for(auto it:timings) cout<<it<<" ";

    vector<int> vis(n, 0);
    int days = countNumberOfDays(timings);
    vector<pair<int, int> > sessions;

    int tempDays = days;
    int minuts = ((days*7)*60);
    for(int i=0;i<vis.size();i++){
        if(!vis[i]){
            if(generateTrackes(i,0,180,0,0,days,0,n,vis,timings,sessions))
                break;
        }
    }
    printOutput(sessions,timingsStr,days);
    return 0;
}

/*------------------- Input -----------------*/
/*
n = 19

Writing Fast Tests Against Enterprise Rails 60min
Overdoing it in Python 45min
Lua for the Masses 30min
Ruby Errors from Mismatched Gem Versions 45min
Common Ruby Errors 45min
Rails for Python Developers lightning
Communicating Over Distance 60min
Accounting-Driven Development 45min
Woah 30min
Sit Down and Write 30min
Pair Programming vs Noise 45min
Rails Magic 60min
Ruby on Rails: Why We Should Move On 60min
Clojure Ate Scala (on my project) 45min
Programming in the Boondocks of Seattle 30min
Ruby vs. Clojure for Back-End Development 30min
Ruby on Rails Legacy App Maintenance 60min
A World Without HackerNews 30min
User Interface CSS in Rails Apps 30min
*/

/*------------------- Output -----------------*/
/*
Track: 1
9:00 Writing Fast Tests Against Enterprise Rails 60min
10:00 Overdoing it in Python 45min
10:45 Lua for the Masses 30min
11:15 Ruby Errors from Mismatched Gem Versions 45min
12:00 Luch time
1:00 Common Ruby Errors 45min
1:45 Rails for Python Developers lightning 60min
2:45 Communicating Over Distance 60min
3:45 Accounting-Driven Development 45min
4:30 Woah 30min
5:00 Network session

Track: 2
9:00 Sit Down and Write 30min
9:30 Pair Programming vs Noise 45min
10:15 Rails Magic 60min
11:15 Clojure Ate Scala (on my project) 45min
12:00 Luch time
1:00 Ruby on Rails: Why We Should Move On 60min
2:00 Programming in the Boondocks of Seattle 30min
2:30 Ruby vs. Clojure for Back-End Development 30min
3:00 Ruby on Rails Legacy App Maintenance 60min
4:00 A World Without HackerNews 30min
4:30 User Interface CSS in Rails Apps 30min
5:00 Network session
*/