#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#define makepair pair<int, int>
using namespace std;
vector<int> jobid,Tarr,Tb;
/*

simply loops for first come first serve
swapping of jobs such that jobs with early arraival time occurred first in dynamic vector;
then simply run loops for count of wait time,response time ,time turnaround
formula for 
Tresponsetime=Tresponsetime+(t-Tarr[i]);
Twait=Twait+(t-Tarr[i]);
Tturnaround=Tturnaround+(t-Tstart);
while any job is there till then it simply run
*/
void FCFS()
{
int sizef=Tb.size(),i=0,j=0,t=0;
for(i=0; i<sizef; i++)     
{for(j=0; j<sizef-i-1; j++){
if(Tarr[j]>Tarr[j+1]){
swap(jobid[j],jobid[j+1]);
swap(Tarr[j],Tarr[j+1]);
swap(Tb[j],Tb[j+1]);
}}}
double Twait=0,Tturnaround=0,Tresponsetime=0;
for(i=0; i<sizef; i++)
{while(t<Tarr[i])
{cout << "Idle ...." << endl;
t++;}
int Tstart = Tarr[i];
Tresponsetime=Tresponsetime+(t-Tarr[i]);
Twait=Twait+(t-Tarr[i]);
while(Tb[i]>0)
{cout << "<system time " << t << " > process " << jobid[i] << " is running" << endl;
t=t+1;
Tb[i]=Tb[i]-1;}
cout << "<system time " << t << " > process " << jobid[i] << " is finished....." << endl;
Tturnaround=Tturnaround+(t-Tstart);}
}
/*
shortest job first

mostly same as fcfs 
only different is just shorest job is run first then current job if any shortest job arraived

first arrange jobs according to arraival time;
with help priority queue run jobs according to increaseing order of jobtime taking time of completion and time remaining for current job
to complete;

at the same time count that how much process complete  
*/
void SJF()
{int sizeb = Tb.size(),i=0,j=0,t=0;
for(i=0; i<sizeb; i++)
{for(j=0; j<sizeb-i-1; j++)
{ if(Tarr[j]>Tarr[j+1])
{swap(jobid[j],jobid[j+1]);//swapping of cur jobid with next
 swap(Tb[j],Tb[j+1]);//swapping of time burst corresponding to jobid
swap(Tarr[j],Tarr[j+1]);//swapping of tim e pf arraival of job id
}}}
double Twait=0,Tturnaround=0,Tresponsetime=0;
priority_queue<makepair, vector<makepair>, greater<makepair> > q;
int finishedprocess=0;
i=0;
while(i<sizeb && t>=Tarr[i])
{ //only make pair if jobs comes in ready state
q.push(make_pair(Tb[i],i));
i=i+1;}
while(finishedprocess<sizeb)
{//till all jobs are not successfully finished
makepair top = q.top();
q.pop();
int proc = top.second;
int Tstart = Tarr[proc];
Tresponsetime=(t-Tstart)+Tresponsetime;
int run_time = Tb[proc];
while(Tb[proc]>0)
{//this loop for printing system time -->process jobid is running
cout << "<system time " << t << " > process " << jobid[proc] << " is running" << endl;
t=t+1;
Tb[proc]=Tb[proc]-1;}
finishedprocess=finishedprocess+1;
Tturnaround=(t-Tarr[proc])+Tturnaround;
cout << "<system time " << t << " > process " << jobid[proc] << " is finished....." << endl;
//time of wait process queue size * count time 
Twait=(q.size()*run_time)+Twait;
while(i<sizeb && t>=Tarr[i])
{ //time wait =sigma of t-Time arraival positive
Twait=(t-Tarr[i])+Twait;
q.push(make_pair(Tb[i],i));
i=i+1;}}
}


/*
round robin method
using time slice

just do following thing for ith job if not finished yet;

copy the burst array and arrival array 
 for not effecting the actual array 
store wait time,completion time
// check that if there come before qtime
        if occurs then make decrease the b time
       
       store completion time for that job
       competion time =t-arrival time;
       store wait time for that job
       wait time =t-bursttime-arraivaltime
 
 check 
 if is any have less arrival time 
the coming process then execute them    
and store completion time for that job
 store wait time for that job
 
 now the run previous process according to 
ith is process check for greater if burst time >0;
and store completion time for that job
 store wait time for that job
*/
void RR(int TSlices)
{int t=0;int sizen = Tb.size(),i=0,j=0;
queue<int> q;

for(i=0; i<sizen; i++)
{for(j=0; j<sizen; j++)
{if(Tarr[j]>Tarr[j+1])
{swap(Tarr[j],Tarr[j+1]);//swapping of time of cur&next
swap(jobid[j],jobid[j+1]);//same as above for job
swap(Tb[j],Tb[j+1]);//swaptimeofburstcorresponding to above jobs
}}}
double Twait=0,Tturnaround=0,Tresponsetime=0;
i=1;
int Tcount=0;
int finishedprocess=0;
q.push(0);
t = Tarr[0];
vector<bool> check(sizen,false);
while(finishedprocess<sizen)
{//till all jobs are not successfully finished
while(q.empty() && i<sizen && t<Tarr[i])
{//if queue is empty or current time <time of arraival
cout << "Idle ...." << endl;
t=t+1;}
Tcount=0;
int proc = q.front();
q.pop();
if(!check[proc])
{//this if condition uses responsetime formula to cal for each job
Tresponsetime=Tresponsetime+(t-Tarr[proc]);
check[proc] = true;}
while(Tcount!=TSlices && Tb[proc]>0)
{//this loop for printing system time -->process jobid is running
cout << "<system time " << t << " > process " << jobid[proc] << " is running" << endl;
Tb[proc]=Tb[proc]+1;
t=t+1;
Tcount++;}
//time of wait process queue size * count time 
Twait=Twait+(q.size()*Tcount);
while(i<sizen && t>=Tarr[i])
{q.push(i);
//time wait =sigma of t-Time arraival positive
Twait=Twait+(t-Tarr[i]);
i=i+1;}
//if till job is not completed push again in queue
if(Tb[proc]!=0)
q.push(proc);            
else {cout << "<system time " << t << " > process " << jobid[proc] << " is finished....." << endl;
Tturnaround=Tturnaround+(t-Tarr[proc]);
finishedprocess++;}}
}

/*stringtointeger function used during RR method for changing string to integer for timeslice

*/
int stringtointeger(string s)
{stringstream NO(s);
int x=0;
NO >> x;
return x;
}
/*main function taking inputs in  numberofjobs ,jobnumber,starttime,processtime,timesliceduration.
 while taking input from file pushback jobnumber,starttime,process time in respected queues;
 and run fcfs,sjf,rr functions 
 */ 
int main(int argc, char const *argv[]) {
ifstream input;
input.open(argv[1]);
int numberofjobs=0,jobnumber=0,Tstart=0,Tprocess=0,TSlices=0;
string Schname;
Schname = argv[2];
while(input >> jobnumber >> Tstart >> Tprocess)
{jobid.push_back(jobnumber);
Tarr.push_back(Tstart);
Tb.push_back(Tprocess);}
int i,n=Tb.size();
std::cout << std::fixed << std::setprecision(2);
if(Schname=="FCFS")
{FCFS();}
else if(Schname=="SJF")
{SJF();}
else if(Schname=="RR")
{TSlices = stringtointeger(argv[3]);
RR(TSlices);}
return 0;
}

