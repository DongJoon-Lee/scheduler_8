#ifndef __SCHEDULER_8__
#define __SCHEDULER_8__

//include list
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <sys/syscall.h>
#include <pthread.h>

//just define
#define gettid() syscall(__NR_gettid)
#define sec 1000000 // it convert to second

// Scheduler declare part
#include "./scheduler/FCFS.h"
#include "./scheduler/SJF.h"

// Tools declare part
//#include "./scheduler/Tools.h"
#include "./scheduler/Process.h"

//end
#endif
