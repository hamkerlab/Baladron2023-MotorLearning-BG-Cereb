#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <deque>
#include <queue>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <random>
#include <cassert>
// only included if compiled with -fopenmp
#ifdef _OPENMP
    #include <omp.h>
#endif

// Intrinsic operations (Intel/AMD)
#ifdef __x86_64__
    #include <immintrin.h>
#endif

/*
 * Built-in functions
 *
 */

#define positive(x) (x>0.0? x : 0.0)
#define negative(x) (x<0.0? x : 0.0)
#define clip(x, a, b) (x<a? a : (x>b? b :x))
#define modulo(a, b) long(a) % long(b)
#define ite(a, b, c) (a?b:c)

// power function for integer exponent
inline double power(double x, unsigned int a){
    double res=x;
    for (unsigned int i=0; i< a-1; i++){
        res *= x;
    }
    return res;
};


/*
 * Custom constants
 *
 */


/*
 * Custom functions
 *
 */


/*
 * Structures for the populations
 *
 */
#include "pop0.hpp"
#include "pop1.hpp"
#include "pop2.hpp"
#include "pop3.hpp"
#include "pop4.hpp"
#include "pop5.hpp"
#include "pop6.hpp"
#include "pop7.hpp"
#include "pop8.hpp"
#include "pop9.hpp"
#include "pop10.hpp"
#include "pop11.hpp"
#include "pop12.hpp"
#include "pop13.hpp"
#include "pop14.hpp"
#include "pop15.hpp"
#include "pop16.hpp"
#include "pop17.hpp"
#include "pop18.hpp"

/*
 * Structures for the projections
 *
 */
#include "proj0.hpp"
#include "proj1.hpp"
#include "proj2.hpp"
#include "proj3.hpp"
#include "proj4.hpp"
#include "proj5.hpp"
#include "proj6.hpp"
#include "proj7.hpp"
#include "proj8.hpp"
#include "proj9.hpp"
#include "proj10.hpp"
#include "proj11.hpp"
#include "proj12.hpp"
#include "proj13.hpp"
#include "proj14.hpp"
#include "proj15.hpp"
#include "proj16.hpp"
#include "proj17.hpp"
#include "proj18.hpp"
#include "proj19.hpp"
#include "proj20.hpp"
#include "proj21.hpp"
#include "proj22.hpp"
#include "proj23.hpp"
#include "proj24.hpp"
#include "proj25.hpp"
#include "proj26.hpp"
#include "proj27.hpp"
#include "proj28.hpp"
#include "proj29.hpp"
#include "proj30.hpp"
#include "proj31.hpp"
#include "proj32.hpp"
#include "proj33.hpp"
#include "proj34.hpp"
#include "proj35.hpp"
#include "proj36.hpp"
#include "proj37.hpp"
#include "proj38.hpp"
#include "proj39.hpp"
#include "proj40.hpp"
#include "proj41.hpp"
#include "proj42.hpp"
#include "proj43.hpp"
#include "proj44.hpp"
#include "proj45.hpp"
#include "proj46.hpp"
#include "proj47.hpp"
#include "proj48.hpp"
#include "proj49.hpp"
#include "proj50.hpp"


/*
 * Declaration of the populations
 *
 */
extern PopStruct0 pop0;
extern PopStruct1 pop1;
extern PopStruct2 pop2;
extern PopStruct3 pop3;
extern PopStruct4 pop4;
extern PopStruct5 pop5;
extern PopStruct6 pop6;
extern PopStruct7 pop7;
extern PopStruct8 pop8;
extern PopStruct9 pop9;
extern PopStruct10 pop10;
extern PopStruct11 pop11;
extern PopStruct12 pop12;
extern PopStruct13 pop13;
extern PopStruct14 pop14;
extern PopStruct15 pop15;
extern PopStruct16 pop16;
extern PopStruct17 pop17;
extern PopStruct18 pop18;


/*
 * Declaration of the projections
 *
 */
extern ProjStruct0 proj0;
extern ProjStruct1 proj1;
extern ProjStruct2 proj2;
extern ProjStruct3 proj3;
extern ProjStruct4 proj4;
extern ProjStruct5 proj5;
extern ProjStruct6 proj6;
extern ProjStruct7 proj7;
extern ProjStruct8 proj8;
extern ProjStruct9 proj9;
extern ProjStruct10 proj10;
extern ProjStruct11 proj11;
extern ProjStruct12 proj12;
extern ProjStruct13 proj13;
extern ProjStruct14 proj14;
extern ProjStruct15 proj15;
extern ProjStruct16 proj16;
extern ProjStruct17 proj17;
extern ProjStruct18 proj18;
extern ProjStruct19 proj19;
extern ProjStruct20 proj20;
extern ProjStruct21 proj21;
extern ProjStruct22 proj22;
extern ProjStruct23 proj23;
extern ProjStruct24 proj24;
extern ProjStruct25 proj25;
extern ProjStruct26 proj26;
extern ProjStruct27 proj27;
extern ProjStruct28 proj28;
extern ProjStruct29 proj29;
extern ProjStruct30 proj30;
extern ProjStruct31 proj31;
extern ProjStruct32 proj32;
extern ProjStruct33 proj33;
extern ProjStruct34 proj34;
extern ProjStruct35 proj35;
extern ProjStruct36 proj36;
extern ProjStruct37 proj37;
extern ProjStruct38 proj38;
extern ProjStruct39 proj39;
extern ProjStruct40 proj40;
extern ProjStruct41 proj41;
extern ProjStruct42 proj42;
extern ProjStruct43 proj43;
extern ProjStruct44 proj44;
extern ProjStruct45 proj45;
extern ProjStruct46 proj46;
extern ProjStruct47 proj47;
extern ProjStruct48 proj48;
extern ProjStruct49 proj49;
extern ProjStruct50 proj50;


/*
 * Recorders
 *
 */
#include "Recorder.h"

extern std::vector<Monitor*> recorders;
int addRecorder(Monitor* recorder);
Monitor* getRecorder(int id);
void removeRecorder(Monitor* recorder);

/*
 * Simulation methods
 *
 */
void run(const int nbSteps);
int run_until(const int steps, std::vector<int> populations, bool or_and);
void step();

/*
 *  Initialization
 */
void initialize(const double dt_) ;
void init_rng_dist();

/*
 * Time export
 *
*/
long int getTime();
void setTime(const long int t_);
double getDt();
void setDt(const double dt_);

/*
 * Number of threads
 *
*/
void setNumberThreads(int threads, std::vector<int> core_list);

/*
 * Seed for the RNG
 *
*/
void setSeed(long int seed, int num_sources, bool use_seed_seq);

