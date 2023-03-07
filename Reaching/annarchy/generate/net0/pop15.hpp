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
// Main Structure for the population of id 15 (SNc_put)
///////////////////////////////////////////////////////////////
struct PopStruct15{

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

    // Local parameter firing
    std::vector< double > firing;

    // Local parameter inhibition
    std::vector< double > inhibition;

    // Local parameter baseline
    std::vector< double > baseline;

    // Local parameter exc_threshold
    std::vector< double > exc_threshold;

    // Local parameter factor_inh
    std::vector< double > factor_inh;

    // Local variable ex_in
    std::vector< double > ex_in;

    // Local variable s_exc
    std::vector< double > s_exc;

    // Local variable s_inh
    std::vector< double > s_inh;

    // Local variable aux
    std::vector< double > aux;

    // Local variable mp
    std::vector< double > mp;

    // Local variable r
    std::vector< double > r;

    // Local psp _sum_exc
    std::vector< double > _sum_exc;

    // Local psp _sum_inh
    std::vector< double > _sum_inh;

    // Random numbers





    // Access methods to the parameters and variables

    std::vector<double> get_local_attribute_all_double(std::string name) {

        // Local parameter tau
        if ( name.compare("tau") == 0 ) {
            return tau;
        }

        // Local parameter firing
        if ( name.compare("firing") == 0 ) {
            return firing;
        }

        // Local parameter inhibition
        if ( name.compare("inhibition") == 0 ) {
            return inhibition;
        }

        // Local parameter baseline
        if ( name.compare("baseline") == 0 ) {
            return baseline;
        }

        // Local parameter exc_threshold
        if ( name.compare("exc_threshold") == 0 ) {
            return exc_threshold;
        }

        // Local parameter factor_inh
        if ( name.compare("factor_inh") == 0 ) {
            return factor_inh;
        }

        // Local variable ex_in
        if ( name.compare("ex_in") == 0 ) {
            return ex_in;
        }

        // Local variable s_exc
        if ( name.compare("s_exc") == 0 ) {
            return s_exc;
        }

        // Local variable s_inh
        if ( name.compare("s_inh") == 0 ) {
            return s_inh;
        }

        // Local variable aux
        if ( name.compare("aux") == 0 ) {
            return aux;
        }

        // Local variable mp
        if ( name.compare("mp") == 0 ) {
            return mp;
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
        std::cerr << "PopStruct15::get_local_attribute_all_double: " << name << " not found" << std::endl;
        return std::vector<double>();
    }

    double get_local_attribute_double(std::string name, int rk) {
        assert( (rk < size) );

        // Local parameter tau
        if ( name.compare("tau") == 0 ) {
            return tau[rk];
        }

        // Local parameter firing
        if ( name.compare("firing") == 0 ) {
            return firing[rk];
        }

        // Local parameter inhibition
        if ( name.compare("inhibition") == 0 ) {
            return inhibition[rk];
        }

        // Local parameter baseline
        if ( name.compare("baseline") == 0 ) {
            return baseline[rk];
        }

        // Local parameter exc_threshold
        if ( name.compare("exc_threshold") == 0 ) {
            return exc_threshold[rk];
        }

        // Local parameter factor_inh
        if ( name.compare("factor_inh") == 0 ) {
            return factor_inh[rk];
        }

        // Local variable ex_in
        if ( name.compare("ex_in") == 0 ) {
            return ex_in[rk];
        }

        // Local variable s_exc
        if ( name.compare("s_exc") == 0 ) {
            return s_exc[rk];
        }

        // Local variable s_inh
        if ( name.compare("s_inh") == 0 ) {
            return s_inh[rk];
        }

        // Local variable aux
        if ( name.compare("aux") == 0 ) {
            return aux[rk];
        }

        // Local variable mp
        if ( name.compare("mp") == 0 ) {
            return mp[rk];
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
        std::cerr << "PopStruct15::get_local_attribute_double: " << name << " not found" << std::endl;
        return static_cast<double>(0.0);
    }

    void set_local_attribute_all_double(std::string name, std::vector<double> value) {
        assert( (value.size() == size) );

        // Local parameter tau
        if ( name.compare("tau") == 0 ) {
            tau = value;
            return;
        }

        // Local parameter firing
        if ( name.compare("firing") == 0 ) {
            firing = value;
            return;
        }

        // Local parameter inhibition
        if ( name.compare("inhibition") == 0 ) {
            inhibition = value;
            return;
        }

        // Local parameter baseline
        if ( name.compare("baseline") == 0 ) {
            baseline = value;
            return;
        }

        // Local parameter exc_threshold
        if ( name.compare("exc_threshold") == 0 ) {
            exc_threshold = value;
            return;
        }

        // Local parameter factor_inh
        if ( name.compare("factor_inh") == 0 ) {
            factor_inh = value;
            return;
        }

        // Local variable ex_in
        if ( name.compare("ex_in") == 0 ) {
            ex_in = value;
            return;
        }

        // Local variable s_exc
        if ( name.compare("s_exc") == 0 ) {
            s_exc = value;
            return;
        }

        // Local variable s_inh
        if ( name.compare("s_inh") == 0 ) {
            s_inh = value;
            return;
        }

        // Local variable aux
        if ( name.compare("aux") == 0 ) {
            aux = value;
            return;
        }

        // Local variable mp
        if ( name.compare("mp") == 0 ) {
            mp = value;
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
        std::cerr << "PopStruct15::set_local_attribute_all_double: " << name << " not found" << std::endl;
    }

    void set_local_attribute_double(std::string name, int rk, double value) {
        assert( (rk < size) );

        // Local parameter tau
        if ( name.compare("tau") == 0 ) {
            tau[rk] = value;
            return;
        }

        // Local parameter firing
        if ( name.compare("firing") == 0 ) {
            firing[rk] = value;
            return;
        }

        // Local parameter inhibition
        if ( name.compare("inhibition") == 0 ) {
            inhibition[rk] = value;
            return;
        }

        // Local parameter baseline
        if ( name.compare("baseline") == 0 ) {
            baseline[rk] = value;
            return;
        }

        // Local parameter exc_threshold
        if ( name.compare("exc_threshold") == 0 ) {
            exc_threshold[rk] = value;
            return;
        }

        // Local parameter factor_inh
        if ( name.compare("factor_inh") == 0 ) {
            factor_inh[rk] = value;
            return;
        }

        // Local variable ex_in
        if ( name.compare("ex_in") == 0 ) {
            ex_in[rk] = value;
            return;
        }

        // Local variable s_exc
        if ( name.compare("s_exc") == 0 ) {
            s_exc[rk] = value;
            return;
        }

        // Local variable s_inh
        if ( name.compare("s_inh") == 0 ) {
            s_inh[rk] = value;
            return;
        }

        // Local variable aux
        if ( name.compare("aux") == 0 ) {
            aux[rk] = value;
            return;
        }

        // Local variable mp
        if ( name.compare("mp") == 0 ) {
            mp[rk] = value;
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
        std::cerr << "PopStruct15::set_local_attribute_double: " << name << " not found" << std::endl;
    }



    // Method called to initialize the data structures
    void init_population() {
    #ifdef _DEBUG
        std::cout << "PopStruct15::init_population(size="<<this->size<<") - this = " << this << std::endl;
    #endif
        _active = true;

        // Local parameter tau
        tau = std::vector<double>(size, 0.0);

        // Local parameter firing
        firing = std::vector<double>(size, 0.0);

        // Local parameter inhibition
        inhibition = std::vector<double>(size, 0.0);

        // Local parameter baseline
        baseline = std::vector<double>(size, 0.0);

        // Local parameter exc_threshold
        exc_threshold = std::vector<double>(size, 0.0);

        // Local parameter factor_inh
        factor_inh = std::vector<double>(size, 0.0);

        // Local variable ex_in
        ex_in = std::vector<double>(size, 0.0);

        // Local variable s_exc
        s_exc = std::vector<double>(size, 0.0);

        // Local variable s_inh
        s_inh = std::vector<double>(size, 0.0);

        // Local variable aux
        aux = std::vector<double>(size, 0.0);

        // Local variable mp
        mp = std::vector<double>(size, 0.0);

        // Local variable r
        r = std::vector<double>(size, 0.0);

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

    }

    // Method to draw new random numbers
    void update_rng() {
#ifdef _TRACE_SIMULATION_STEPS
    std::cout << "    PopStruct15::update_rng()" << std::endl;
#endif

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
            std::cout << "    PopStruct15::update()" << std::endl;
        #endif

            // Updating the local variables
            #pragma omp simd
            for(int i = 0; i < size; i++){

                // ex_in = if (sum(exc)>exc_threshold): 1 else: 0
                ex_in[i] = (_sum_exc[i] > exc_threshold[i] ? 1 : 0);


                // s_exc = sum(exc)
                s_exc[i] = _sum_exc[i];


                // s_inh = sum(inh)
                s_inh[i] = _sum_inh[i];


                // aux = if (firing>0): (ex_in)*( pos(sum(exc)-baseline-s_inh) + baseline) + (1-ex_in)*(-factor_inh*sum(inh)+baseline)  else: baseline
                aux[i] = (firing[i] > 0 ? ex_in[i]*(baseline[i] + positive(_sum_exc[i] - baseline[i] - s_inh[i])) + (1 - ex_in[i])*(_sum_inh[i]*(-factor_inh[i]) + baseline[i]) : baseline[i]);


                // tau*dmp/dt + mp =  aux
                double _mp = (aux[i] - mp[i])/tau[i];

                // tau*dmp/dt + mp =  aux
                mp[i] += dt*_mp ;


                // r = if (mp>0.0): mp else: 0.0
                r[i] = (mp[i] > 0.0 ? mp[i] : 0.0);


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
        size_in_bytes += sizeof(double) * firing.capacity();	// firing
        size_in_bytes += sizeof(double) * inhibition.capacity();	// inhibition
        size_in_bytes += sizeof(double) * baseline.capacity();	// baseline
        size_in_bytes += sizeof(double) * exc_threshold.capacity();	// exc_threshold
        size_in_bytes += sizeof(double) * factor_inh.capacity();	// factor_inh
        // Variables
        size_in_bytes += sizeof(double) * ex_in.capacity();	// ex_in
        size_in_bytes += sizeof(double) * s_exc.capacity();	// s_exc
        size_in_bytes += sizeof(double) * s_inh.capacity();	// s_inh
        size_in_bytes += sizeof(double) * aux.capacity();	// aux
        size_in_bytes += sizeof(double) * mp.capacity();	// mp
        size_in_bytes += sizeof(double) * r.capacity();	// r
        // RNGs

        return size_in_bytes;
    }

    // Memory management: destroy all the C++ data
    void clear() {
#ifdef _DEBUG
    std::cout << "PopStruct15::clear() - this = " << this << std::endl;
#endif
        // Variables
        ex_in.clear();
        ex_in.shrink_to_fit();
        s_exc.clear();
        s_exc.shrink_to_fit();
        s_inh.clear();
        s_inh.shrink_to_fit();
        aux.clear();
        aux.shrink_to_fit();
        mp.clear();
        mp.shrink_to_fit();
        r.clear();
        r.shrink_to_fit();

        // RNGs

    }
};

