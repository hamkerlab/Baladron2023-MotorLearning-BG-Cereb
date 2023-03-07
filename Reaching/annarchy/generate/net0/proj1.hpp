/*
 *  ANNarchy-version: 4.7.1.5
 */
#pragma once

#include "ANNarchy.h"
#include "LILMatrix.hpp"




extern PopStruct1 pop1;
extern PopStruct1 pop1;
extern double dt;
extern long int t;

extern std::vector<std::mt19937> rng;

/////////////////////////////////////////////////////////////////////////////
// proj1: pop1 -> pop1 with target exc
/////////////////////////////////////////////////////////////////////////////
struct ProjStruct1 : LILMatrix<int, int> {
    ProjStruct1() : LILMatrix<int, int>( 400, 400) {
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





    // Global parameter eta
    double  eta ;

    // Global parameter learning_phase
    double  learning_phase ;

    // Global parameter error
    double  error ;

    // Global parameter mean_error
    double  mean_error ;

    // Global parameter max_weight_change
    double  max_weight_change ;

    // Local variable trace
    std::vector< std::vector<double > > trace;

    // Local variable delta_w
    std::vector< std::vector<double > > delta_w;

    // Local variable w
    std::vector< std::vector<double > > w;




    // Method called to allocate/initialize the variables
    bool init_attributes() {

        // Global parameter eta
        eta = 0.0;

        // Global parameter learning_phase
        learning_phase = 0.0;

        // Global parameter error
        error = 0.0;

        // Global parameter mean_error
        mean_error = 0.0;

        // Global parameter max_weight_change
        max_weight_change = 0.0;

        // Local variable trace
        trace = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local variable delta_w
        delta_w = init_matrix_variable<double>(static_cast<double>(0.0));




        return true;
    }

    // Method called to initialize the projection
    void init_projection() {
    #ifdef _DEBUG
        std::cout << "ProjStruct1::init_projection() - this = " << this << std::endl;
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
        std::cout << "    ProjStruct1::compute_psp()" << std::endl;
    #endif
        double sum;

        if (_transmission && pop1._active){



            for (int i = 0; i < post_rank.size(); i++) {

                sum = 0.0;
                for (int j = 0; j < pre_rank[i].size(); j++) {
                    sum += pop1.r[pre_rank[i][j]]*w[i][j] ;
                }
                pop1._sum_exc[post_rank[i]] += sum;
            }

        } // active

    }

    // Draws random numbers
    void update_rng() {

    }

    // Updates synaptic variables
    void update_synapse() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "    ProjStruct1::update_synapse()" << std::endl;
    #endif

        int rk_post, rk_pre;
        double _dt = dt * _update_period;

        // Check periodicity
        if(_transmission && _update && pop1._active && ( (t - _update_offset)%_update_period == 0L) ){
            // Global variables


            // Semiglobal/Local variables
            for (int i = 0; i < post_rank.size(); i++) {
                rk_post = post_rank[i]; // Get postsynaptic rank

                // Semi-global variables


                // Local variables
                for (int j = 0; j < pre_rank[i].size(); j++) {
                    rk_pre = pre_rank[i][j]; // Get presynaptic rank

                    // trace += if learning_phase < 0.5: power(pre.rprev * (post.delta_x), 3) else: 0.0
                    trace[i][j] += (learning_phase < 0.5 ? power(pop1.delta_x[rk_post]*pop1.rprev[rk_pre], 3) : 0.0);


                    // delta_w = if learning_phase > 0.5: eta * trace * (mean_error) * (error - mean_error) else: 0.0
                    delta_w[i][j] = (learning_phase > 0.5 ? eta*mean_error*trace[i][j]*(error - mean_error) : 0.0);
                    if(delta_w[i][j] < -max_weight_change)
                        delta_w[i][j] = -max_weight_change;
                    if(delta_w[i][j] > max_weight_change)
                        delta_w[i][j] = max_weight_change;


                    // w -= if learning_phase > 0.5: delta_w else: 0.0
                    if(_plasticity){
                    w[i][j] -= (learning_phase > 0.5 ? delta_w[i][j] : 0.0);

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

        if ( name.compare("trace") == 0 ) {

            return get_matrix_variable_all<double>(trace);
        }

        if ( name.compare("delta_w") == 0 ) {

            return get_matrix_variable_all<double>(delta_w);
        }

        if ( name.compare("w") == 0 ) {

            return get_matrix_variable_all<double>(w);
        }


        // should not happen
        std::cerr << "ProjStruct1::get_local_attribute_all_double: " << name << " not found" << std::endl;
        return std::vector<std::vector<double>>();
    }

    std::vector<double> get_local_attribute_row_double(std::string name, int rk_post) {

        if ( name.compare("trace") == 0 ) {

            return get_matrix_variable_row<double>(trace, rk_post);
        }

        if ( name.compare("delta_w") == 0 ) {

            return get_matrix_variable_row<double>(delta_w, rk_post);
        }

        if ( name.compare("w") == 0 ) {

            return get_matrix_variable_row<double>(w, rk_post);
        }


        // should not happen
        std::cerr << "ProjStruct1::get_local_attribute_row_double: " << name << " not found" << std::endl;
        return std::vector<double>();
    }

    double get_local_attribute_double(std::string name, int rk_post, int rk_pre) {

        if ( name.compare("trace") == 0 ) {

            return get_matrix_variable<double>(trace, rk_post, rk_pre);
        }

        if ( name.compare("delta_w") == 0 ) {

            return get_matrix_variable<double>(delta_w, rk_post, rk_pre);
        }

        if ( name.compare("w") == 0 ) {

            return get_matrix_variable<double>(w, rk_post, rk_pre);
        }


        // should not happen
        std::cerr << "ProjStruct1::get_local_attribute: " << name << " not found" << std::endl;
        return 0.0;
    }

    void set_local_attribute_all_double(std::string name, std::vector<std::vector<double>> value) {

        if ( name.compare("trace") == 0 ) {
            update_matrix_variable_all<double>(trace, value);

            return;
        }

        if ( name.compare("delta_w") == 0 ) {
            update_matrix_variable_all<double>(delta_w, value);

            return;
        }

        if ( name.compare("w") == 0 ) {
            update_matrix_variable_all<double>(w, value);

            return;
        }

    }

    void set_local_attribute_row_double(std::string name, int rk_post, std::vector<double> value) {

        if ( name.compare("trace") == 0 ) {
            update_matrix_variable_row<double>(trace, rk_post, value);

            return;
        }

        if ( name.compare("delta_w") == 0 ) {
            update_matrix_variable_row<double>(delta_w, rk_post, value);

            return;
        }

        if ( name.compare("w") == 0 ) {
            update_matrix_variable_row<double>(w, rk_post, value);

            return;
        }

    }

    void set_local_attribute_double(std::string name, int rk_post, int rk_pre, double value) {

        if ( name.compare("trace") == 0 ) {
            update_matrix_variable<double>(trace, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("delta_w") == 0 ) {
            update_matrix_variable<double>(delta_w, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("w") == 0 ) {
            update_matrix_variable<double>(w, rk_post, rk_pre, value);

            return;
        }

    }

    double get_global_attribute_double(std::string name) {

        if ( name.compare("eta") == 0 ) {
            return eta;
        }

        if ( name.compare("learning_phase") == 0 ) {
            return learning_phase;
        }

        if ( name.compare("error") == 0 ) {
            return error;
        }

        if ( name.compare("mean_error") == 0 ) {
            return mean_error;
        }

        if ( name.compare("max_weight_change") == 0 ) {
            return max_weight_change;
        }


        // should not happen
        std::cerr << "ProjStruct1::get_global_attribute_double: " << name << " not found" << std::endl;
        return 0.0;
    }

    void set_global_attribute_double(std::string name, double value) {

        if ( name.compare("eta") == 0 ) {
            eta = value;

            return;
        }

        if ( name.compare("learning_phase") == 0 ) {
            learning_phase = value;

            return;
        }

        if ( name.compare("error") == 0 ) {
            error = value;

            return;
        }

        if ( name.compare("mean_error") == 0 ) {
            mean_error = value;

            return;
        }

        if ( name.compare("max_weight_change") == 0 ) {
            max_weight_change = value;

            return;
        }

    }


    // Access additional


    // Memory management
    long int size_in_bytes() {
        long int size_in_bytes = 0;

        // connectivity
        size_in_bytes += static_cast<LILMatrix<int, int>*>(this)->size_in_bytes();

        // Local variable trace
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * trace.capacity();
        for(auto it = trace.cbegin(); it != trace.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local variable delta_w
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * delta_w.capacity();
        for(auto it = delta_w.cbegin(); it != delta_w.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local variable w
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * w.capacity();
        for(auto it = w.cbegin(); it != w.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Global parameter eta
        size_in_bytes += sizeof(double);

        // Global parameter learning_phase
        size_in_bytes += sizeof(double);

        // Global parameter error
        size_in_bytes += sizeof(double);

        // Global parameter mean_error
        size_in_bytes += sizeof(double);

        // Global parameter max_weight_change
        size_in_bytes += sizeof(double);

        return size_in_bytes;
    }

    // Structural plasticity



    void clear() {
    #ifdef _DEBUG
        std::cout << "ProjStruct1::clear() - this = " << this << std::endl;
    #endif

        // Connectivity
        static_cast<LILMatrix<int, int>*>(this)->clear();

        // trace
        for (auto it = trace.begin(); it != trace.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        trace.clear();
        trace.shrink_to_fit();

        // delta_w
        for (auto it = delta_w.begin(); it != delta_w.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        delta_w.clear();
        delta_w.shrink_to_fit();

        // w
        for (auto it = w.begin(); it != w.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        w.clear();
        w.shrink_to_fit();

    }
};

