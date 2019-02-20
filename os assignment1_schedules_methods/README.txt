

OS ASSIGNMENT_1

***********How to run program*******************



Usage: sched input_file [FCFS|RR|SJF] [time_quantum]




*************README***************


Functions brief discriptions



1)MAIN FUNCTION

 while taking input from file pushback jobnumber,starttime,process time in respected queues;
 and run fcfs,sjf,rr functions 

2)FCFS

simply loops for first come first serve
swapping of jobs such that jobs with early arraival time occurred first in dynamic vector;
then simply run loops for count of wait time,response time ,time turnaround

while any job is there till then it simply run

3)SJF
shortest job first

mostly same as fcfs 
only different is just shorest job is run first then current job if any shortest job arraived

with help priority queue run jobs according to increaseing order of jobtime taking time of completion and time remaining for current job
to complete;

at the same time count that how much process complete  


4)RR


just do following thing for ith job if not finished yet;

copy the burst array and arrival array 
 for not effecting the actual array 
store wait time,completion time
// check that if there come before qtime
        if occurs then make decrease the b time
       
      
 
 check 
 if is any have less arrival time 
the coming process then execute them    

 now the run previous process according to 
ith is process check for greater if burst time >0;







