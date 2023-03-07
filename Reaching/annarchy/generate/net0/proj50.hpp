/*
 *  ANNarchy-version: 4.7.1.5
 */
#pragma once

#include "ANNarchy.h"
#include "LILMatrix.hpp"




extern PopStruct11 pop11;
extern PopStruct15 pop15;
extern double dt;
extern long int t;

extern std::vector<std::mt19937> rng;

/////////////////////////////////////////////////////////////////////////////
// proj50: StrD1_putamen -> SNc_put with target inh
/////////////////////////////////////////////////////////////////////////////
struct ProjStruct50 : LILMatrix<int, int> {
    ProjStruct50() : LILMatrix<int, int>( 1, 120) {
    }


    bool init_from_lil( std::vector<int> &row_indices,
                        std::vector< std::vector<int> > &column_indices,
                        std::vector< std::vector<double> > &values,
                        std::vector< std::vector<int> > &delays) {
        bool success = static_cast<LILMatrix<int, int>*>(this)->init_matrix_from_lil(row_indices, column_indices);
        if (!success)
            return false;


        // Local variable w
        w = init_matrix_variable<double>(static_cast<double>(0.0));
        update_matrix_variable_all<double>(w, values);


        // init other variables than 'w' or delay
        if (!init_attributes()){
            return false;
        }

    #ifdef _DEBUG_CONN
        static_cast<LILMatrix<int, int>*>(this)->print_data_representation();
    #endif
        return true;
    }





    // Transmission and plasticity flags
    bool _transmission, _plasticity, _update;
    int _update_period;
    long int _update_offset;





    // Local parameter tau
    std::vector< std::vector<double > > tau;

    // Local parameter baseline_dopa
    std::vector< std::vector<double > > baseline_dopa;

    // Local variable aux
    std::vector< std::vector<double > > aux;

    // Local variable delta
    std::vector< std::vector<double > > delta;

    // Local variable w
    std::vector< std::vector<double > > w;




    // Method called to allocate/initialize the variables
    bool init_attributes() {

        // Local parameter tau
        tau = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local parameter baseline_dopa
        baseline_dopa = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local variable aux
        aux = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local variable delta
        delta = init_matrix_variable<double>(static_cast<double>(0.0));




        return true;
    }

    // Method called to initialize the projection
    void init_projection() {
    #ifdef _DEBUG
        std::cout << "ProjStruct50::init_projection() - this = " << this << std::endl;
    #endif

        _transmission = true;
        _update = true;
        _plasticity = true;
        _update_period = 1;
        _update_offset = 0L;

        init_attributes();



    }

    // Spiking networks: reset the ring buffer when non-uniform
    void reset_ring_buffer() {

    }

    // Spiking networks: update maximum delay when non-uniform
    void update_max_delay(int d){

    }

    // Computes the weighted sum of inputs or updates the conductances
    void compute_psp() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "    ProjStruct50::compute_psp()" << std::endl;
    #endif
        double sum;

        if (_transmission && pop15._active){



            for (int i = 0; i < post_rank.size(); i++) {

                sum = 0.0;
                for (int j = 0; j < pre_rank[i].size(); j++) {
                    sum += pop11.r[pre_rank[i][j]]*w[i][j] ;
                }
                pop15._sum_inh[post_rank[i]] += sum;
            }

        } // active

    }

    // Draws random numbers
    void update_rng() {

    }

    // Updates synaptic variables
    void update_synapse() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "    ProjStruct50::update_synapse()" << std::endl;
    #endif

        int rk_post, rk_pre;
        double _dt = dt * _update_period;

        // Check periodicity
        if(_transmission && _update && pop15._active && ( (t - _update_offset)%_update_period == 0L) ){
            // Global variables


            // Semiglobal/Local variables
            for (int i = 0; i < post_rank.size(); i++) {
                rk_post = post_rank[i]; // Get postsynaptic rank

                // Semi-global variables


                // Local variables
                for (int j = 0; j < pre_rank[i].size(); j++) {
                    rk_pre = pre_rank[i][j]; // Get presynaptic rank

                    // aux = if (post.sum(exc)>0): 1.0 else: 3.0
                    aux[i][j] = (pop15._sum_exc[rk_post] > 0 ? 1.0 : 3.0);


                    // delta = aux*pos(post.r - baseline_dopa)*pos(pre.r - mean(pre.r))
                    delta[i][j] = aux[i][j]*positive(-pop11._mean_r + pop11.r[rk_pre])*positive(pop15.r[rk_post] - baseline_dopa[i][j]);


                    // tau*dw/_dt = delta
                    double _w = delta[i][j]/tau[i][j];

                    // tau*dw/_dt = delta
                    if(_plasticity){
                    w[i][j] += _dt*_w ;
                    if(w[i][j] < 0)
                        w[i][j] = 0;

                    }

                }
            }
        }

    }

    // Post-synaptic events
    void post_event() {


    }

    // Variable/Parameter access methods

    std::vector<std::vector<double>> get_local_attribute_all_double(std::string name) {

        if ( name.compare("tau") == 0 ) {

            return get_matrix_variable_all<double>(tau);
        }

        if ( name.compare("baseline_dopa") == 0 ) {

            return get_matrix_variable_all<double>(baseline_dopa);
        }

        if ( name.compare("aux") == 0 ) {

            return get_matrix_variable_all<double>(aux);
        }

        if ( name.compare("delta") == 0 ) {

            return get_matrix_variable_all<double>(delta);
        }

        if ( name.compare("w") == 0 ) {

            return get_matrix_variable_all<double>(w);
        }


        // should not happen
        std::cerr << "ProjStruct50::get_local_attribute_all_double: " << name << " not found" << std::endl;
        return std::vector<std::vector<double>>();
    }

    std::vector<double> get_local_attribute_row_double(std::string name, int rk_post) {

        if ( name.compare("tau") == 0 ) {

            return get_matrix_variable_row<double>(tau, rk_post);
        }

        if ( name.compare("baseline_dopa") == 0 ) {

            return get_matrix_variable_row<double>(baseline_dopa, rk_post);
        }

        if ( name.compare("aux") == 0 ) {

            return get_matrix_variable_row<double>(aux, rk_post);
        }

        if ( name.compare("delta") == 0 ) {

            return get_matrix_variable_row<double>(delta, rk_post);
        }

        if ( name.compare("w") == 0 ) {

            return get_matrix_variable_row<double>(w, rk_post);
        }


        // should not happen
        std::cerr << "ProjStruct50::get_local_attribute_row_double: " << name << " not found" << std::endl;
        return std::vector<double>();
    }

    double get_local_attribute_double(std::string name, int rk_post, int rk_pre) {

        if ( name.compare("tau") == 0 ) {

            return get_matrix_variable<double>(tau, rk_post, rk_pre);
        }

        if ( name.compare("baseline_dopa") == 0 ) {

            return get_matrix_variable<double>(baseline_dopa, rk_post, rk_pre);
        }

        if ( name.compare("aux") == 0 ) {

            return get_matrix_variable<double>(aux, rk_post, rk_pre);
        }

        if ( name.compare("delta") == 0 ) {

            return get_matrix_variable<double>(delta, rk_post, rk_pre);
        }

        if ( name.compare("w") == 0 ) {

            return get_matrix_variable<double>(w, rk_post, rk_pre);
        }


        // should not happen
        std::cerr << "ProjStruct50::get_local_attribute: " << name << " not found" << std::endl;
        return 0.0;
    }

    void set_local_attribute_all_double(std::string name, std::vector<std::vector<double>> value) {

        if ( name.compare("tau") == 0 ) {
            update_matrix_variable_all<double>(tau, value);

            return;
        }

        if ( name.compare("baseline_dopa") == 0 ) {
            update_matrix_variable_all<double>(baseline_dopa, value);

            return;
        }

        if ( name.compare("aux") == 0 ) {
            update_matrix_variable_all<double>(aux, value);

            return;
        }

        if ( name.compare("delta") == 0 ) {
            update_matrix_variable_all<double>(delta, value);

            return;
        }

        if ( name.compare("w") == 0 ) {
            update_matrix_variable_all<double>(w, value);

            return;
        }

    }

    void set_local_attribute_row_double(std::string name, int rk_post, std::vector<double> value) {

        if ( name.compare("tau") == 0 ) {
            update_matrix_variable_row<double>(tau, rk_post, value);

            return;
        }

        if ( name.compare("baseline_dopa") == 0 ) {
            update_matrix_variable_row<double>(baseline_dopa, rk_post, value);

            return;
        }

        if ( name.compare("aux") == 0 ) {
            update_matrix_variable_row<double>(aux, rk_post, value);

            return;
        }

        if ( name.compare("delta") == 0 ) {
            update_matrix_variable_row<double>(delta, rk_post, value);

            return;
        }

        if ( name.compare("w") == 0 ) {
            update_matrix_variable_row<double>(w, rk_post, value);

            return;
        }

    }

    void set_local_attribute_double(std::string name, int rk_post, int rk_pre, double value) {

        if ( name.compare("tau") == 0 ) {
            update_matrix_variable<double>(tau, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("baseline_dopa") == 0 ) {
            update_matrix_variable<double>(baseline_dopa, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("aux") == 0 ) {
            update_matrix_variable<double>(aux, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("delta") == 0 ) {
            update_matrix_variable<double>(delta, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("w") == 0 ) {
            update_matrix_variable<double>(w, rk_post, rk_pre, value);

            return;
        }

    }


    // Access additional


    // Memory management
    long int size_in_bytes() {
        long int size_in_bytes = 0;

        // connectivity
        size_in_bytes += static_cast<LILMatrix<int, int>*>(this)->size_in_bytes();

        // Local variable aux
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * aux.capacity();
        for(auto it = aux.cbegin(); it != aux.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local variable delta
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * delta.capacity();
        for(auto it = delta.cbegin(); it != delta.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local variable w
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * w.capacity();
        for(auto it = w.cbegin(); it != w.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local parameter tau
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * tau.capacity();
        for(auto it = tau.cbegin(); it != tau.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local parameter baseline_dopa
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * baseline_dopa.capacity();
        for(auto it = baseline_dopa.cbegin(); it != baseline_dopa.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        return size_in_bytes;
    }

    // Structural plasticity



    void clear() {
    #ifdef _DEBUG
        std::cout << "ProjStruct50::clear() - this = " << this << std::endl;
    #endif

        // Connectivity
        static_cast<LILMatrix<int, int>*>(this)->clear();

        // aux
        for (auto it = aux.begin(); it != aux.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        aux.clear();
        aux.shrink_to_fit();

        // delta
        for (auto it = delta.begin(); it != delta.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        delta.clear();
        delta.shrink_to_fit();

        // w
        for (auto it = w.begin(); it != w.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        w.clear();
        w.shrink_to_fit();

        // tau
        for (auto it = tau.begin(); it != tau.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        tau.clear();
        tau.shrink_to_fit();

        // baseline_dopa
        for (auto it = baseline_dopa.begin(); it != baseline_dopa.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        baseline_dopa.clear();
        baseline_dopa.shrink_to_fit();

    }
};

