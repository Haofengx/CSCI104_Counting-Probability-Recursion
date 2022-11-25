#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t row,
    size_t col,
    vector<size_t> numOfWorker,
    vector<size_t> workerDay
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

    for(unsigned int i = 0; i < avail.size(); i++){
        vector<Worker_T> t;
        for(unsigned int j = 0; j < dailyNeed; j++){
            t.push_back(0);
        }
        sched.push_back(t);
    }
    size_t row = 0, col = 0;
    vector<size_t> numOfWorker(avail.size(), 0);
    vector<size_t> workerDay(avail[0].size(), 0);
    AvailabilityMatrix ava = avail;
    return scheduleHelper(ava, dailyNeed, maxShifts, sched, row, col, numOfWorker, workerDay);
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t row,
    size_t col,
    vector<size_t> numOfWorker,
    vector<size_t> workerDay
){
    // base case: return true
    if(row == avail.size()) return true;
		for(size_t i = col; i < avail[0].size(); i++){
				if(avail[row][i] == 1 && workerDay[i] < maxShifts){
                        AvailabilityMatrix newAvail = avail;
                        newAvail[row][i] = 0;
						sched[row][numOfWorker[row]] = i;
						vector<size_t> newNumOfWorker = numOfWorker;
						newNumOfWorker[row] += 1;
						vector<size_t> newWorkerDay = workerDay;
						newWorkerDay[i] += 1;
						bool status;
						if(newNumOfWorker[row] == dailyNeed){
								status = scheduleHelper
								(newAvail, dailyNeed, maxShifts, sched, row + 1, 0, newNumOfWorker, newWorkerDay);
						}
						else{
								status = scheduleHelper
								(newAvail, dailyNeed, maxShifts, sched, row, col + 1, newNumOfWorker, newWorkerDay); 
						}
						if(status) return true;
				}
		}
    return false;
}