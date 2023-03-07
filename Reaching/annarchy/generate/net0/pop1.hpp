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
// Main Structure for the population of id 1 (pop1)
///////////////////////////////////////////////////////////////
struct PopStruct1{

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

    // Global parameter tau
    double  tau ;

    // Local parameter constant
    std::vector< double > constant;

    // Global parameter alpha
    double  alpha ;

    // Global parameter f
    double  f ;

    // Global parameter A
    double  A ;

    // Local variable perturbation
    std::vector< double > perturbation;

    // Local variable noise
    std::vector< double > noise;

    // Local variable x
    std::vector< double > x;

    // Local variable rprev
    std::vector< double > rprev;

    // Local variable r
    std::vector< double > r;

    // Local variable delta_x
    std::vector< double > delta_x;

    // Local variable x_mean
    std::vector< double > x_mean;

    // Local psp _sum_exc
    std::vector< double > _sum_exc;

    // Local psp _sum_in
    std::vector< double > _sum_in;

    // Random numbers
    std::vector<double> rand_0;
    std::uniform_real_distribution< double > dist_rand_0;
        std::vector<double> rand_1;
    std::uniform_real_distribution< double > dist_rand_1;





    // Access methods to the parameters and variables

    std::vector<double> get_local_attribute_all_double(std::string name) {

        // Local parameter constant
        if ( name.compare("constant") == 0 ) {
            return constant;
        }

        // Local variable perturbation
        if ( name.compare("perturbation") == 0 ) {
            return perturbation;
        }

        // Local variable noise
        if ( name.compare("noise") == 0 ) {
            return noise;
        }

        // Local variable x
        if ( name.compare("x") == 0 ) {
            return x;
        }

        // Local variable rprev
        if ( name.compare("rprev") == 0 ) {
            return rprev;
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            return r;
        }

        // Local variable delta_x
        if ( name.compare("delta_x") == 0 ) {
            return delta_x;
        }

        // Local variable x_mean
        if ( name.compare("x_mean") == 0 ) {
            return x_mean;
        }

        // Local psp _sum_exc
        if ( name.compare("_sum_exc") == 0 ) {
            return _sum_exc;
        }

        // Local psp _sum_in
        if ( name.compare("_sum_in") == 0 ) {
            return _sum_in;
        }


        // should not happen
        std::cerr << "PopStruct1::get_local_attribute_all_double: " << name << " not found" << std::endl;
        return std::vector<double>();
    }

    double get_local_attribute_double(std::string name, int rk) {
        assert( (rk < size) );

        // Local parameter constant
        if ( name.compare("constant") == 0 ) {
            return constant[rk];
        }

        // Local variable perturbation
        if ( name.compare("perturbation") == 0 ) {
            return perturbation[rk];
        }

        // Local variable noise
        if ( name.compare("noise") == 0 ) {
            return noise[rk];
        }

        // Local variable x
        if ( name.compare("x") == 0 ) {
            return x[rk];
        }

        // Local variable rprev
        if ( name.compare("rprev") == 0 ) {
            return rprev[rk];
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            return r[rk];
        }

        // Local variable delta_x
        if ( name.compare("delta_x") == 0 ) {
            return delta_x[rk];
        }

        // Local variable x_mean
        if ( name.compare("x_mean") == 0 ) {
            return x_mean[rk];
        }

        // Local psp _sum_exc
        if ( name.compare("_sum_exc") == 0 ) {
            return _sum_exc[rk];
        }

        // Local psp _sum_in
        if ( name.compare("_sum_in") == 0 ) {
            return _sum_in[rk];
        }


        // should not happen
        std::cerr << "PopStruct1::get_local_attribute_double: " << name << " not found" << std::endl;
        return static_cast<double>(0.0);
    }

    void set_local_attribute_all_double(std::string name, std::vector<double> value) {
        assert( (value.size() == size) );

        // Local parameter constant
        if ( name.compare("constant") == 0 ) {
            constant = value;
            return;
        }

        // Local variable perturbation
        if ( name.compare("perturbation") == 0 ) {
            perturbation = value;
            return;
        }

        // Local variable noise
        if ( name.compare("noise") == 0 ) {
            noise = value;
            return;
        }

        // Local variable x
        if ( name.compare("x") == 0 ) {
            x = value;
            return;
        }

        // Local variable rprev
        if ( name.compare("rprev") == 0 ) {
            rprev = value;
            return;
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            r = value;
            return;
        }

        // Local variable delta_x
        if ( name.compare("delta_x") == 0 ) {
            delta_x = value;
            return;
        }

        // Local variable x_mean
        if ( name.compare("x_mean") == 0 ) {
            x_mean = value;
            return;
        }

        // Local psp _sum_exc
        if ( name.compare("_sum_exc") == 0 ) {
            _sum_exc = value;
            return;
        }

        // Local psp _sum_in
        if ( name.compare("_sum_in") == 0 ) {
            _sum_in = value;
            return;
        }


        // should not happen
        std::cerr << "PopStruct1::set_local_attribute_all_double: " << name << " not found" << std::endl;
    }

    void set_local_attribute_double(std::string name, int rk, double value) {
        assert( (rk < size) );

        // Local parameter constant
        if ( name.compare("constant") == 0 ) {
            constant[rk] = value;
            return;
        }

        // Local variable perturbation
        if ( name.compare("perturbation") == 0 ) {
            perturbation[rk] = value;
            return;
        }

        // Local variable noise
        if ( name.compare("noise") == 0 ) {
            noise[rk] = value;
            return;
        }

        // Local variable x
        if ( name.compare("x") == 0 ) {
            x[rk] = value;
            return;
        }

        // Local variable rprev
        if ( name.compare("rprev") == 0 ) {
            rprev[rk] = value;
            return;
        }

        // Local variable r
        if ( name.compare("r") == 0 ) {
            r[rk] = value;
            return;
        }

        // Local variable delta_x
        if ( name.compare("delta_x") == 0 ) {
            delta_x[rk] = value;
            return;
        }

        // Local variable x_mean
        if ( name.compare("x_mean") == 0 ) {
            x_mean[rk] = value;
            return;
        }

        // Local psp _sum_exc
        if ( name.compare("_sum_exc") == 0 ) {
            _sum_exc[rk] = value;
            return;
        }

        // Local psp _sum_in
        if ( name.compare("_sum_in") == 0 ) {
            _sum_in[rk] = value;
            return;
        }


        // should not happen
        std::cerr << "PopStruct1::set_local_attribute_double: " << name << " not found" << std::endl;
    }

    double get_global_attribute_double(std::string name) {

        // Global parameter tau
        if ( name.compare("tau") == 0 ) {
            return tau;
        }

        // Global parameter alpha
        if ( name.compare("alpha") == 0 ) {
            return alpha;
        }

        // Global parameter f
        if ( name.compare("f") == 0 ) {
            return f;
        }

        // Global parameter A
        if ( name.compare("A") == 0 ) {
            return A;
        }


        // should not happen
        std::cerr << "PopStruct1::get_global_attribute_double: " << name << " not found" << std::endl;
        return static_cast<double>(0.0);
    }

    void set_global_attribute_double(std::string name, double value)  {

        // Global parameter tau
        if ( name.compare("tau") == 0 ) {
            tau = value;
            return;
        }

        // Global parameter alpha
        if ( name.compare("alpha") == 0 ) {
            alpha = value;
            return;
        }

        // Global parameter f
        if ( name.compare("f") == 0 ) {
            f = value;
            return;
        }

        // Global parameter A
        if ( name.compare("A") == 0 ) {
            A = value;
            return;
        }


        std::cerr << "PopStruct1::set_global_attribute_double: " << name << " not found" << std::endl;
    }



    // Method called to initialize the data structures
    void init_population() {
    #ifdef _DEBUG
        std::cout << "PopStruct1::init_population(size="<<this->size<<") - this = " << this << std::endl;
    #endif
        _active = true;

        // Global parameter tau
        tau = 0.0;

        // Local parameter constant
        constant = std::vector<double>(size, 0.0);

        // Global parameter alpha
        alpha = 0.0;

        // Global parameter f
        f = 0.0;

        // Global parameter A
        A = 0.0;

        // Local variable perturbation
        perturbation = std::vector<double>(size, 0.0);

        // Local variable noise
        noise = std::vector<double>(size, 0.0);

        // Local variable x
        x = std::vector<double>(size, 0.0);

        // Local variable rprev
        rprev = std::vector<double>(size, 0.0);

        // Local variable r
        r = std::vector<double>(size, 0.0);

        // Local variable delta_x
        delta_x = std::vector<double>(size, 0.0);

        // Local variable x_mean
        x_mean = std::vector<double>(size, 0.0);

        rand_0 = std::vector<double>(size, 0.0);

        rand_1 = std::vector<double>(size, 0.0);

        // Local psp _sum_exc
        _sum_exc = std::vector<double>(size, 0.0);

        // Local psp _sum_in
        _sum_in = std::vector<double>(size, 0.0);






    }

    // Method called to reset the population
    void reset() {



    }

    // Init rng dist
    void init_rng_dist() {

        dist_rand_0 = std::uniform_real_distribution< double >(0.0, 1.0);

        dist_rand_1 = std::uniform_real_distribution< double >(-1.0, 1.0);

    }

    // Method to draw new random numbers
    void update_rng() {
#ifdef _TRACE_SIMULATION_STEPS
    std::cout << "    PopStruct1::update_rng()" << std::endl;
#endif

        if (_active){

            for(int i = 0; i < size; i++) {

                rand_0[i] = dist_rand_0(rng[0]);

                rand_1[i] = dist_rand_1(rng[0]);

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
            std::cout << "    PopStruct1::update()" << std::endl;
        #endif

            // Updating the local variables
            #pragma omp simd
            for(int i = 0; i < size; i++){

                // perturbation = if Uniform(0.0, 1.0) < f/1000.: 1.0 else: 0.0
                perturbation[i] = (rand_0[i] < f/1000.0 ? 1.0 : 0.0);


                // noise = if perturbation > 0.5: A*Uniform(-1.0, 1.0) else: 0.0
                noise[i] = (perturbation[i] > 0.5 ? A*rand_1[i] : 0.0);


                // x += dt*(sum(in) + sum(exc) - x + noise)/tau
                x[i] += dt*(_sum_exc[i] + _sum_in[i] + noise[i] - x[i])/tau;


                // rprev = r
                rprev[i] = r[i];


                // r = if constant == 0.0: tanh(x) else: tanh(constant)
                r[i] = (constant[i] == 0.0 ? tanh(x[i]) : tanh(constant[i]));


                // delta_x = x - x_mean
                delta_x[i] = x[i] - x_mean[i];


                // x_mean = alpha * x_mean + (1 - alpha) * x
                x_mean[i] = alpha*x_mean[i] + x[i]*(1 - alpha);


            }
        } // active

    }

    void spike_gather() {

    }



    // Memory management: track the memory consumption
    long int size_in_bytes() {
        long int size_in_bytes = 0;
        // Parameters
        size_in_bytes += sizeof(double);	// tau
        size_in_bytes += sizeof(double) * constant.capacity();	// constant
        size_in_bytes += sizeof(double);	// alpha
        size_in_bytes += sizeof(double);	// f
        size_in_bytes += sizeof(double);	// A
        // Variables
        size_in_bytes += sizeof(double) * perturbation.capacity();	// perturbation
        size_in_bytes += sizeof(double) * noise.capacity();	// noise
        size_in_bytes += sizeof(double) * x.capacity();	// x
        size_in_bytes += sizeof(double) * rprev.capacity();	// rprev
        size_in_bytes += sizeof(double) * r.capacity();	// r
        size_in_bytes += sizeof(double) * delta_x.capacity();	// delta_x
        size_in_bytes += sizeof(double) * x_mean.capacity();	// x_mean
        // RNGs
        size_in_bytes += sizeof(double) * rand_0.capacity();	// rand_0
        size_in_bytes += sizeof(double) * rand_1.capacity();	// rand_1

        return size_in_bytes;
    }

    // Memory management: destroy all the C++ data
    void clear() {
#ifdef _DEBUG
    std::cout << "PopStruct1::clear() - this = " << this << std::endl;
#endif
        // Variables
        perturbation.clear();
        perturbation.shrink_to_fit();
        noise.clear();
        noise.shrink_to_fit();
        x.clear();
        x.shrink_to_fit();
        rprev.clear();
        rprev.shrink_to_fit();
        r.clear();
        r.shrink_to_fit();
        delta_x.clear();
        delta_x.shrink_to_fit();
        x_mean.clear();
        x_mean.shrink_to_fit();

        // RNGs

        rand_0.clear();
        rand_0.shrink_to_fit();

        rand_1.clear();
        rand_1.shrink_to_fit();

    }
};

