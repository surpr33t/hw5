#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool backtrack(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    vector<int>& shifts,
    int day,
    int slot
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    int n = avail.size(); 
    int k = avail[0].size();

    //intialixe here 
    sched.assign(n, vector<Worker_T>(dailyNeed, INVALID_ID));

    //shifts worker has 
    vector<int> shifts(k, 0);

    //recursion 
    return backtrack(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);
}

bool backtrack(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    vector<int>& shifts,
    int day,
    int slot
)
{
    //base case, finished all days
    if(day == (int)avail.size())
    {
        return true;
    }

    //move to next day
    if(slot == (int)dailyNeed)
    {
        return backtrack(avail, dailyNeed, maxShifts, sched, shifts, day + 1, 0);
    }

    int k = avail[0].size();

    //try each worker
    for(int w = 0; w < k; w++)
    {
        //must be available, under max shifts
        if(avail[day][w] && shifts[w] < (int)maxShifts)
        {
            // ensure worker not already used today
            bool used = false;
            for(int i = 0; i < slot; i++)
            {
                if(sched[day][i] == w)
                {
                    used = true;
                    break;
                }
            }

            if(used)
            {
                continue;
            }

            //choose
            sched[day][slot] = w;
            shifts[w]++;

            //recurse
            if(backtrack(avail, dailyNeed, maxShifts, sched, shifts, day, slot + 1))
            {
                return true;
            }

            //undo
            shifts[w]--;
            sched[day][slot] = INVALID_ID;
        }
    }

    return false;
}



