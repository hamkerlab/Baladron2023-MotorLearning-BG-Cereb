/*
 *  ANNarchy-version: 4.7.1.5
 */
#pragma once

#include "ANNarchy.h"
#include <random>



extern double dt;
extern long int t;
extern std::vector<std::mt19937> rng;


///////////////////////////////////////////////////////////////
// Main Structure for the population of id 2 (RG_Pattern_parm1)
///////////////////////////////////////////////////////////////
struct PopStruct2{

    int size; // Number of neurons
    bool _active; // Allows to shut down the whole population
    int max_delay; // Maximum number of steps to store for delayed synaptic transmission

    // Access functions used by cython wrapper
    int get_size() { return size; }
    void set_size(int s) { size  = s; }
    int get_max_delay() { return max_delay; }
    void set_max_delay(int d) { max_delay  = d; }
    bool is_active() { return _active; }
    void set_active(bool val) { _active = val; }



    // Neuron specific parameters and variables

    // Local parameter tau
    std::vector< double > tau;

    // Local parameter baseline
    std::vector< double > baseline;

    // Local parameter noise
    std::vector< double > noise;

    // Local parameter tau_trace
    std::vector< double > tau_trace;

    // Local parameter factor_exc
    std::vector< double > factor_exc;

    // Local variable mp
    std::vector< double > mp;

    // Local variable trace
    std::vector< double > trace;

    // Local variable r
    std::vector< double > r;

    // Local psp _sum_exc
    std::vector< double > _sum_exc;

    // Local psp _sum_inh
    std::vector< double > _sum_inh;

    // Random numbers
    std::vector<double> rand_0;
    std::uniform_real_distribution< double > dist_rand_0;





    // Access methods to the parameters and variables

    std::vector<double> get_local_attribute_all_double(std::string name) {

        // Local parameter tau
        if ( name.compare("tau") == 0 ) {
            return tau;
        }

        // Local parameter baseline
        if ( name.compare("baseline") == 0 ) {
            return baseline;
        }

        // Local parameter noise
        if ( name.compare("noise") == 0 ) {
            return noise;
        }

        // Local parameter tau_trace
        if ( name.compare("tau_trace") == 0 ) {
            return tau_trace;
        }

        // Local parameter factor_exc
        if ( name.compare("factor_exc") == 0 ) {
            return factor_exc;
        }

        // Local variable mp
        if ( name.compare("mp") == 0 ) {
            return mp;
        }

        // Local variable trace
        if ( name.compare("trace") == 0 ) {
            return trace;
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            return r;
        }

        // Local psp _sum_exc
        if ( name.compare("_sum_exc") == 0 ) {
            return _sum_exc;
        }

        // Local psp _sum_inh
        if ( name.compare("_sum_inh") == 0 ) {
            return _sum_inh;
        }


        // should not happen
        std::cerr << "PopStruct2::get_local_attribute_all_double: " << name << " not found" << std::endl;
        return std::vector<double>();
    }

    double get_local_attribute_double(std::string name, int rk) {
        assert( (rk < size) );

        // Local parameter tau
        if ( name.compare("tau") == 0 ) {
            return tau[rk];
        }

        // Local parameter baseline
        if ( name.compare("baseline") == 0 ) {
            return baseline[rk];
        }

        // Local parameter noise
        if ( name.compare("noise") == 0 ) {
            return noise[rk];
        }

        // Local parameter tau_trace
        if ( name.compare("tau_trace") == 0 ) {
            return tau_trace[rk];
        }

        // Local parameter factor_exc
        if ( name.compare("factor_exc") == 0 ) {
            return factor_exc[rk];
        }

        // Local variable mp
        if ( name.compare("mp") == 0 ) {
            return mp[rk];
        }

        // Local variable trace
        if ( name.compare("trace") == 0 ) {
            return trace[rk];
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            return r[rk];
        }

        // Local psp _sum_exc
        if ( name.compare("_sum_exc") == 0 ) {
            return _sum_exc[rk];
        }

        // Local psp _sum_inh
        if ( name.compare("_sum_inh") == 0 ) {
            return _sum_inh[rk];
        }


        // should not happen
        std::cerr << "PopStruct2::get_local_attribute_double: " << name << " not found" << std::endl;
        return static_cast<double>(0.0);
    }

    void set_local_attribute_all_double(std::string name, std::vector<double> value) {
        assert( (value.size() == size) );

        // Local parameter tau
        if ( name.compare("tau") == 0 ) {
            tau = value;
            return;
        }

        // Local parameter baseline
        if ( name.compare("baseline") == 0 ) {
            baseline = value;
            return;
        }

        // Local parameter noise
        if ( name.compare("noise") == 0 ) {
            noise = value;
            return;
        }

        // Local parameter tau_trace
        if ( name.compare("tau_trace") == 0 ) {
            tau_trace = value;
            return;
        }

        // Local parameter factor_exc
        if ( name.compare("factor_exc") == 0 ) {
            factor_exc = value;
            return;
        }

        // Local variable mp
        if ( name.compare("mp") == 0 ) {
            mp = value;
            return;
        }

        // Local variable trace
        if ( name.compare("trace") == 0 ) {
            trace = value;
            return;
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            r = value;
            return;
        }

        // Local psp _sum_exc
        if ( name.compare("_sum_exc") == 0 ) {
            _sum_exc = value;
            return;
        }

        // Local psp _sum_inh
        if ( name.compare("_sum_inh") == 0 ) {
            _sum_inh = value;
            return;
        }


        // should not happen
        std::cerr << "PopStruct2::set_local_attribute_all_double: " << name << " not found" << std::endl;
    }

    void set_local_attribute_double(std::string name, int rk, double value) {
        assert( (rk < size) );

        // Local parameter tau
        if ( name.compare("tau") == 0 ) {
            tau[rk] = value;
            return;
        }

        // Local parameter baseline
        if ( name.compare("baseline") == 0 ) {
            baseline[rk] = value;
            return;
        }

        // Local parameter noise
        if ( name.compare("noise") == 0 ) {
            noise[rk] = value;
            return;
        }

        // Local parameter tau_trace
        if ( name.compare("tau_trace") == 0 ) {
            tau_trace[rk] = value;
            return;
        }

        // Local parameter factor_exc
        if ( name.compare("factor_exc") == 0 ) {
            factor_exc[rk] = value;
            return;
        }

        // Local variable mp
        if ( name.compare("mp") == 0 ) {
            mp[rk] = value;
            return;
        }

        // Local variable trace
        if ( name.compare("trace") == 0 ) {
            trace[rk] = value;
            return;
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            r[rk] = value;
            return;
        }

        // Local psp _sum_exc
        if ( name.compare("_sum_exc") == 0 ) {
            _sum_exc[rk] = value;
            return;
        }

        // Local psp _sum_inh
        if ( name.compare("_sum_inh") == 0 ) {
            _sum_inh[rk] = value;
            return;
        }


        // should not happen
        std::cerr << "PopStruct2::set_local_attribute_double: " << name << " not found" << std::endl;
    }



    // Method called to initialize the data structures
    void init_population() {
    #ifdef _DEBUG
        std::cout << "PopStruct2::init_population(size="<<this->size<<") - this = " << this << std::endl;
    #endif
        _active = true;

        // Local parameter tau
        tau = std::vector<double>(size, 0.0);

        // Local parameter baseline
        baseline = std::vector<double>(size, 0.0);

        // Local parameter noise
        noise = std::vector<double>(size, 0.0);

        // Local parameter tau_trace
        tau_trace = std::vector<double>(size, 0.0);

        // Local parameter factor_exc
        factor_exc = std::vector<double>(size, 0.0);

        // Local variable mp
        mp = std::vector<double>(size, 0.0);

        // Local variable trace
        trace = std::vector<double>(size, 0.0);

        // Local variable r
        r = std::vector<double>(size, 0.0);

        rand_0 = std::vector<double>(size, 0.0);

        // Local psp _sum_exc
        _sum_exc = std::vector<double>(size, 0.0);

        // Local psp _sum_inh
        _sum_inh = std::vector<double>(size, 0.0);






    }

    // Method called to reset the population
    void reset() {



    }

    // Init rng dist
    void init_rng_dist() {

        dist_rand_0 = std::uniform_real_distribution< double >(-1.0, 1.0);

    }

    // Method to draw new random numbers
    void update_rng() {
#ifdef _TRACE_SIMULATION_STEPS
    std::cout << "    PopStruct2::update_rng()" << std::endl;
#endif

        if (_active){

            for(int i = 0; i < size; i++) {

                rand_0[i] = dist_rand_0(rng[0]);

            }
        }

    }

    // Method to update global operations on the population (min/max/mean...)
    void update_global_ops() {

    }

    // Method to enqueue output variables in case outgoing projections have non-zero delay
    void update_delay() {

    }

    // Method to dynamically change the size of the queue for delayed variables
    void update_max_delay(int value) {

    }

    // Main method to update neural variables
    void update() {

        if( _active ) {
        #ifdef _TRACE_SIMULATION_STEPS
            std::cout << "    PopStruct2::update()" << std::endl;
        #endif

            // Updating the local variables
            #pragma omp simd
            for(int i = 0; i < size; i++){

                // tau*dmp/dt + mp = factor_exc*sum(exc) - sum(inh) + baseline + noise*Uniform(-1.0,1.0)
                double _mp = (_sum_exc[i]*factor_exc[i] - _sum_inh[i] + baseline[i] - mp[i] + noise[i]*rand_0[i])/tau[i];

                // tau_trace*dtrace/dt + trace = r
                double _trace = (r[i] - trace[i])/tau_trace[i];

                // tau*dmp/dt + mp = factor_exc*sum(exc) - sum(inh) + baseline + noise*Uniform(-1.0,1.0)
                mp[i] += dt*_mp ;


                // tau_trace*dtrace/dt + trace = r
                trace[i] += dt*_trace ;


                // r = pos(mp)
                r[i] = positive(mp[i]);


            }
        } // active

    }

    void spike_gather() {

    }



    // Memory management: track the memory consumption
    long int size_in_bytes() {
        long int size_in_bytes = 0;
        // Parameters
        size_in_bytes += sizeof(double) * tau.capacity();	// tau
        size_in_bytes += sizeof(double) * baseline.capacity();	// baseline
        size_in_bytes += sizeof(double) * noise.capacity();	// noise
        size_in_bytes += sizeof(double) * tau_trace.capacity();	// tau_trace
        size_in_bytes += sizeof(double) * factor_exc.capacity();	// factor_exc
        // Variables
        size_in_bytes += sizeof(double) * mp.capacity();	// mp
        size_in_bytes += sizeof(double) * trace.capacity();	// trace
        size_in_bytes += sizeof(double) * r.capacity();	// r
        // RNGs
        size_in_bytes += sizeof(double) * rand_0.capacity();	// rand_0

        return size_in_bytes;
    }

    // Memory management: destroy all the C++ data
    void clear() {
#ifdef _DEBUG
    std::cout << "PopStruct2::clear() - this = " << this << std::endl;
#endif
        // Variables
        mp.clear();
        mp.shrink_to_fit();
        trace.clear();
        trace.shrink_to_fit();
        r.clear();
        r.shrink_to_fit();

        // RNGs

        rand_0.clear();
        rand_0.shrink_to_fit();

    }
};

