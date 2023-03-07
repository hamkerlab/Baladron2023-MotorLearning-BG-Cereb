
#include "ANNarchy.h"



/*
 * Internal data
 *
 */
double dt;
long int t;
std::vector<std::mt19937> rng;

// Custom constants


// Populations
PopStruct0 pop0;
PopStruct1 pop1;
PopStruct2 pop2;
PopStruct3 pop3;
PopStruct4 pop4;
PopStruct5 pop5;
PopStruct6 pop6;
PopStruct7 pop7;
PopStruct8 pop8;
PopStruct9 pop9;
PopStruct10 pop10;
PopStruct11 pop11;
PopStruct12 pop12;
PopStruct13 pop13;
PopStruct14 pop14;
PopStruct15 pop15;
PopStruct16 pop16;
PopStruct17 pop17;
PopStruct18 pop18;


// Projections
ProjStruct0 proj0;
ProjStruct1 proj1;
ProjStruct2 proj2;
ProjStruct3 proj3;
ProjStruct4 proj4;
ProjStruct5 proj5;
ProjStruct6 proj6;
ProjStruct7 proj7;
ProjStruct8 proj8;
ProjStruct9 proj9;
ProjStruct10 proj10;
ProjStruct11 proj11;
ProjStruct12 proj12;
ProjStruct13 proj13;
ProjStruct14 proj14;
ProjStruct15 proj15;
ProjStruct16 proj16;
ProjStruct17 proj17;
ProjStruct18 proj18;
ProjStruct19 proj19;
ProjStruct20 proj20;
ProjStruct21 proj21;
ProjStruct22 proj22;
ProjStruct23 proj23;
ProjStruct24 proj24;
ProjStruct25 proj25;
ProjStruct26 proj26;
ProjStruct27 proj27;
ProjStruct28 proj28;
ProjStruct29 proj29;
ProjStruct30 proj30;
ProjStruct31 proj31;
ProjStruct32 proj32;
ProjStruct33 proj33;
ProjStruct34 proj34;
ProjStruct35 proj35;
ProjStruct36 proj36;
ProjStruct37 proj37;
ProjStruct38 proj38;
ProjStruct39 proj39;
ProjStruct40 proj40;
ProjStruct41 proj41;
ProjStruct42 proj42;
ProjStruct43 proj43;
ProjStruct44 proj44;
ProjStruct45 proj45;
ProjStruct46 proj46;
ProjStruct47 proj47;
ProjStruct48 proj48;
ProjStruct49 proj49;
ProjStruct50 proj50;


// Global operations

// Computes the mean value of an array
double mean_value(const double* array, int n)
{
    double sum = array[0];
    for(int i=1; i<n; i++)
    {
        sum += array[i];
    }
    return sum/(double)n;
}


/*
 * Recorders
 */
std::vector<Monitor*> recorders;
int addRecorder(Monitor* recorder){
    int found = -1;

    for (unsigned int i=0; i<recorders.size(); i++) {
        if (recorders[i] == nullptr) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        // fill a previously cleared slot
        recorders[found] = recorder;
        return found;
    } else {
        recorders.push_back(recorder);
        return recorders.size() - 1;
    }
}
Monitor* getRecorder(int id) {
    if (id < recorders.size())
        return recorders[id];
    else
        return nullptr;
}
void removeRecorder(Monitor* recorder){
    for (unsigned int i=0; i<recorders.size(); i++){
        if(recorders[i] == recorder){
            recorders[i] = nullptr;
            break;
        }
    }
}

/*
 *  Simulation methods
 */
// Simulate a single step
void singleStep()
{


    ////////////////////////////////
    // Presynaptic events
    ////////////////////////////////


    // pop1: pop1
    if (pop1._active)
        memset( pop1._sum_exc.data(), 0.0, pop1._sum_exc.size() * sizeof(double));

    // pop1: pop1
    if (pop1._active)
        memset( pop1._sum_in.data(), 0.0, pop1._sum_in.size() * sizeof(double));

    // pop2: RG_Pattern_parm1
    if (pop2._active)
        memset( pop2._sum_exc.data(), 0.0, pop2._sum_exc.size() * sizeof(double));

    // pop2: RG_Pattern_parm1
    if (pop2._active)
        memset( pop2._sum_inh.data(), 0.0, pop2._sum_inh.size() * sizeof(double));

    // pop3: RG_Pattern_parm2
    if (pop3._active)
        memset( pop3._sum_exc.data(), 0.0, pop3._sum_exc.size() * sizeof(double));

    // pop3: RG_Pattern_parm2
    if (pop3._active)
        memset( pop3._sum_inh.data(), 0.0, pop3._sum_inh.size() * sizeof(double));

    // pop4: RG_Pattern_parm3
    if (pop4._active)
        memset( pop4._sum_exc.data(), 0.0, pop4._sum_exc.size() * sizeof(double));

    // pop4: RG_Pattern_parm3
    if (pop4._active)
        memset( pop4._sum_inh.data(), 0.0, pop4._sum_inh.size() * sizeof(double));

    // pop5: RG_Pattern_parm4
    if (pop5._active)
        memset( pop5._sum_exc.data(), 0.0, pop5._sum_exc.size() * sizeof(double));

    // pop5: RG_Pattern_parm4
    if (pop5._active)
        memset( pop5._sum_inh.data(), 0.0, pop5._sum_inh.size() * sizeof(double));

    // pop6: PF_Pattern_parm1
    if (pop6._active)
        memset( pop6._sum_exc.data(), 0.0, pop6._sum_exc.size() * sizeof(double));

    // pop6: PF_Pattern_parm1
    if (pop6._active)
        memset( pop6._sum_inh.data(), 0.0, pop6._sum_inh.size() * sizeof(double));

    // pop7: PF_Pattern_parm2
    if (pop7._active)
        memset( pop7._sum_exc.data(), 0.0, pop7._sum_exc.size() * sizeof(double));

    // pop7: PF_Pattern_parm2
    if (pop7._active)
        memset( pop7._sum_inh.data(), 0.0, pop7._sum_inh.size() * sizeof(double));

    // pop8: Injected_current
    if (pop8._active)
        memset( pop8._sum_exc.data(), 0.0, pop8._sum_exc.size() * sizeof(double));

    // pop8: Injected_current
    if (pop8._active)
        memset( pop8._sum_inh.data(), 0.0, pop8._sum_inh.size() * sizeof(double));

    // pop9: Intermediate
    if (pop9._active)
        memset( pop9._sum_inh.data(), 0.0, pop9._sum_inh.size() * sizeof(double));

    // pop11: StrD1_putamen
    if (pop11._active)
        memset( pop11._sum_dopa.data(), 0.0, pop11._sum_dopa.size() * sizeof(double));

    // pop11: StrD1_putamen
    if (pop11._active)
        memset( pop11._sum_exc.data(), 0.0, pop11._sum_exc.size() * sizeof(double));

    // pop12: StrThal_putamen
    if (pop12._active)
        memset( pop12._sum_inh.data(), 0.0, pop12._sum_inh.size() * sizeof(double));

    // pop13: SNr_putamen
    if (pop13._active)
        memset( pop13._sum_dopa.data(), 0.0, pop13._sum_dopa.size() * sizeof(double));

    // pop13: SNr_putamen
    if (pop13._active)
        memset( pop13._sum_exc.data(), 0.0, pop13._sum_exc.size() * sizeof(double));

    // pop13: SNr_putamen
    if (pop13._active)
        memset( pop13._sum_inh.data(), 0.0, pop13._sum_inh.size() * sizeof(double));

    // pop14: VA_putamen
    if (pop14._active)
        memset( pop14._sum_inh.data(), 0.0, pop14._sum_inh.size() * sizeof(double));

    // pop15: SNc_put
    if (pop15._active)
        memset( pop15._sum_exc.data(), 0.0, pop15._sum_exc.size() * sizeof(double));

    // pop15: SNc_put
    if (pop15._active)
        memset( pop15._sum_inh.data(), 0.0, pop15._sum_inh.size() * sizeof(double));

    // pop16: PM
    if (pop16._active)
        memset( pop16._sum_exc.data(), 0.0, pop16._sum_exc.size() * sizeof(double));

#ifdef _TRACE_SIMULATION_STEPS
    std::cout << "Update psp/conductances ..." << std::endl;
#endif
	proj0.compute_psp();
	proj1.compute_psp();
	proj2.compute_psp();
	proj3.compute_psp();
	proj4.compute_psp();
	proj5.compute_psp();
	proj6.compute_psp();
	proj7.compute_psp();
	proj8.compute_psp();
	proj9.compute_psp();
	proj10.compute_psp();
	proj11.compute_psp();
	proj12.compute_psp();
	proj13.compute_psp();
	proj14.compute_psp();
	proj15.compute_psp();
	proj16.compute_psp();
	proj17.compute_psp();
	proj18.compute_psp();
	proj19.compute_psp();
	proj20.compute_psp();
	proj21.compute_psp();
	proj22.compute_psp();
	proj23.compute_psp();
	proj24.compute_psp();
	proj25.compute_psp();
	proj26.compute_psp();
	proj27.compute_psp();
	proj28.compute_psp();
	proj29.compute_psp();
	proj30.compute_psp();
	proj31.compute_psp();
	proj32.compute_psp();
	proj33.compute_psp();
	proj34.compute_psp();
	proj35.compute_psp();
	proj36.compute_psp();
	proj37.compute_psp();
	proj38.compute_psp();
	proj39.compute_psp();
	proj40.compute_psp();
	proj41.compute_psp();
	proj42.compute_psp();
	proj43.compute_psp();
	proj44.compute_psp();
	proj45.compute_psp();
	proj46.compute_psp();
	proj47.compute_psp();
	proj48.compute_psp();
	proj49.compute_psp();
	proj50.compute_psp();



    ////////////////////////////////
    // Recording target variables
    ////////////////////////////////
#ifdef _TRACE_SIMULATION_STEPS
    std::cout << "Record psp/conductances ..." << std::endl;
#endif
    for (unsigned int i=0; i < recorders.size(); i++){
        recorders[i]->record_targets();
    }

    ////////////////////////////////
    // Update random distributions
    ////////////////////////////////
#ifdef _TRACE_SIMULATION_STEPS
    std::cout << "Draw required random numbers ..." << std::endl;
#endif

    pop1.update_rng();
    pop2.update_rng();
    pop3.update_rng();
    pop4.update_rng();
    pop5.update_rng();
    pop6.update_rng();
    pop7.update_rng();
    pop8.update_rng();
    pop9.update_rng();
    pop10.update_rng();
    pop11.update_rng();
    pop12.update_rng();
    pop13.update_rng();
    pop14.update_rng();
    pop16.update_rng();
    pop17.update_rng();
    pop18.update_rng();



    ////////////////////////////////
    // Update neural variables
    ////////////////////////////////
#ifdef _TRACE_SIMULATION_STEPS
    std::cout << "Evaluate neural ODEs ..." << std::endl;
#endif

    pop1.update(); pop1.spike_gather(); 
    pop2.update(); pop2.spike_gather(); 
    pop3.update(); pop3.spike_gather(); 
    pop4.update(); pop4.spike_gather(); 
    pop5.update(); pop5.spike_gather(); 
    pop6.update(); pop6.spike_gather(); 
    pop7.update(); pop7.spike_gather(); 
    pop8.update(); pop8.spike_gather(); 
    pop9.update(); pop9.spike_gather(); 
    pop10.update(); pop10.spike_gather(); 
    pop11.update(); pop11.spike_gather(); 
    pop12.update(); pop12.spike_gather(); 
    pop13.update(); pop13.spike_gather(); 
    pop14.update(); pop14.spike_gather(); 
    pop15.update(); pop15.spike_gather(); 
    pop16.update(); pop16.spike_gather(); 
    pop17.update(); pop17.spike_gather(); 
    pop18.update(); pop18.spike_gather(); 



    ////////////////////////////////
    // Delay outputs
    ////////////////////////////////
#ifdef _TRACE_SIMULATION_STEPS
    std::cout << "Update delay queues ..." << std::endl;
#endif


    ////////////////////////////////
    // Global operations (min/max/mean)
    ////////////////////////////////
#ifdef _TRACE_SIMULATION_STEPS
    std::cout << "Update global operations ..." << std::endl;
#endif

    pop10.update_global_ops();
    pop11.update_global_ops();



    ////////////////////////////////
    // Update synaptic variables
    ////////////////////////////////
#ifdef _TRACE_SIMULATION_STEPS
    std::cout << "Evaluate synaptic ODEs ..." << std::endl;
#endif

	proj1.update_synapse();
	proj41.update_synapse();
	proj50.update_synapse();



    ////////////////////////////////
    // Postsynaptic events
    ////////////////////////////////


    ////////////////////////////////
    // Structural plasticity
    ////////////////////////////////


    ////////////////////////////////
    // Recording neural / synaptic variables
    ////////////////////////////////

    for (unsigned int i=0; i < recorders.size(); i++){
        recorders[i]->record();
    }


    ////////////////////////////////
    // Increase internal time
    ////////////////////////////////
    t++;


}

// Simulate the network for the given number of steps,
// called from python
void run(const int nbSteps) {
#ifdef _TRACE_SIMULATION_STEPS
    std::cout << "Perform simulation for " << nbSteps << " steps." << std::endl;
#endif

    for(int i=0; i<nbSteps; i++) {
        singleStep();
    }

}

// Simulate the network for a single steps,
// called from python
void step() {

    singleStep();

}

int run_until(const int steps, std::vector<int> populations, bool or_and)
{


    bool stop = false;
    bool cond_activated = false;
    int nb = 0;
    for(int n = 0; n < steps; n++)
    {
        step();
        nb++;
        stop = or_and;


        cond_activated = std::find(populations.begin(), populations.end(), 16) != populations.end();
        if (cond_activated)
            if(or_and)
                stop = stop && pop16.stop_condition();
            else
                stop = stop || pop16.stop_condition();
    

        // HD: stop will be automatically true, if no populations are checked.
        if(stop && (populations.size() > 0))
            break;
    }
    return nb;



}

/*
 *  Initialization methods
 */
// Initialize the internal data and the random numbers generator
void initialize(const double _dt) {


    // Internal variables
    dt = _dt;
    t = static_cast<long int>(0);

    // Populations
    // Initialize populations
    pop0.init_population();
    pop1.init_population();
    pop2.init_population();
    pop3.init_population();
    pop4.init_population();
    pop5.init_population();
    pop6.init_population();
    pop7.init_population();
    pop8.init_population();
    pop9.init_population();
    pop10.init_population();
    pop11.init_population();
    pop12.init_population();
    pop13.init_population();
    pop14.init_population();
    pop15.init_population();
    pop16.init_population();
    pop17.init_population();
    pop18.init_population();


    // Projections
    // Initialize projections
    proj0.init_projection();
    proj1.init_projection();
    proj2.init_projection();
    proj3.init_projection();
    proj4.init_projection();
    proj5.init_projection();
    proj6.init_projection();
    proj7.init_projection();
    proj8.init_projection();
    proj9.init_projection();
    proj10.init_projection();
    proj11.init_projection();
    proj12.init_projection();
    proj13.init_projection();
    proj14.init_projection();
    proj15.init_projection();
    proj16.init_projection();
    proj17.init_projection();
    proj18.init_projection();
    proj19.init_projection();
    proj20.init_projection();
    proj21.init_projection();
    proj22.init_projection();
    proj23.init_projection();
    proj24.init_projection();
    proj25.init_projection();
    proj26.init_projection();
    proj27.init_projection();
    proj28.init_projection();
    proj29.init_projection();
    proj30.init_projection();
    proj31.init_projection();
    proj32.init_projection();
    proj33.init_projection();
    proj34.init_projection();
    proj35.init_projection();
    proj36.init_projection();
    proj37.init_projection();
    proj38.init_projection();
    proj39.init_projection();
    proj40.init_projection();
    proj41.init_projection();
    proj42.init_projection();
    proj43.init_projection();
    proj44.init_projection();
    proj45.init_projection();
    proj46.init_projection();
    proj47.init_projection();
    proj48.init_projection();
    proj49.init_projection();
    proj50.init_projection();


    // Custom constants


}

// Initialize the random distribution objects
void init_rng_dist() {
pop0.init_rng_dist();
pop1.init_rng_dist();
pop2.init_rng_dist();
pop3.init_rng_dist();
pop4.init_rng_dist();
pop5.init_rng_dist();
pop6.init_rng_dist();
pop7.init_rng_dist();
pop8.init_rng_dist();
pop9.init_rng_dist();
pop10.init_rng_dist();
pop11.init_rng_dist();
pop12.init_rng_dist();
pop13.init_rng_dist();
pop14.init_rng_dist();
pop15.init_rng_dist();
pop16.init_rng_dist();
pop17.init_rng_dist();
pop18.init_rng_dist();

}

// Change the seed of the RNG
void setSeed(const long int seed, const int num_sources, const bool use_seed_seq) {
    if (num_sources > 1)
        std::cerr << "WARNING - ANNarchy::setSeed(): num_sources should be 1 for single thread code." << std::endl;

    rng.clear();

    rng.push_back(std::mt19937(seed));

    rng.shrink_to_fit();
}

/*
 * Access to time and dt
 */
long int getTime() {return t;}
void setTime(const long int t_) { t=t_;}
double getDt() { return dt;}
void setDt(const double dt_) { dt=dt_;}

/*
 * Number of threads
 *
*/
void setNumberThreads(const int threads, const std::vector<int> core_list)
{
    std::cerr << "WARNING: a call of setNumberThreads() is without effect on single thread simulation code." << std::endl;
}
