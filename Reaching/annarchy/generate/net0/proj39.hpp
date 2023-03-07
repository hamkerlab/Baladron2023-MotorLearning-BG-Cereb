/*
 *  ANNarchy-version: 4.7.1.5
 */
#pragma once

#include "ANNarchy.h"
#include "LILMatrix.hpp"




extern PopStruct13 pop13;
extern PopStruct13 pop13;
extern double dt;
extern long int t;

extern std::vector<std::mt19937> rng;

/////////////////////////////////////////////////////////////////////////////
// proj39: SNr_putamen -> SNr_putamen with target exc
/////////////////////////////////////////////////////////////////////////////
struct ProjStruct39 : LILMatrix<int, int> {
    ProjStruct39() : LILMatrix<int, int>( 120, 120) {
    }


    bool init_from_lil( std::vector<int> &row_indices,
                        std::vector< std::vector<int> > &column_indices,
                        std::vector< std::vector<double> > &values,
                        std::vector< std::vector<int> > &delays) {
        bool success = static_cast<LILMatrix<int, int>*>(this)->init_matrix_from_lil(row_indices, column_indices);
        if (!success)
            return false;

        w = values[0][0];


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





    // Local parameter reversal
    std::vector< std::vector<double > > reversal;

    // Global parameter w
    double  w ;




    // Method called to allocate/initialize the variables
    bool init_attributes() {

        // Local parameter reversal
        reversal = init_matrix_variable<double>(static_cast<double>(0.0));




        return true;
    }

    // Method called to initialize the projection
    void init_projection() {
    #ifdef _DEBUG
        std::cout << "ProjStruct39::init_projection() - this = " << this << std::endl;
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
        std::cout << "    ProjStruct39::compute_psp()" << std::endl;
    #endif
        double sum;

        if (_transmission && pop13._active){



            for (int i = 0; i < post_rank.size(); i++) {

                sum = 0.0;
                for (int j = 0; j < pre_rank[i].size(); j++) {
                    sum +=  w*positive(-pop13.r[pre_rank[i][j]] + reversal[i][j]) ;
                }
                pop13._sum_exc[post_rank[i]] += sum;
            }

        } // active

    }

    // Draws random numbers
    void update_rng() {

    }

    // Updates synaptic variables
    void update_synapse() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "    ProjStruct39::update_synapse()" << std::endl;
    #endif


    }

    // Post-synaptic events
    void post_event() {


    }

    // Variable/Parameter access methods

    std::vector<std::vector<double>> get_local_attribute_all_double(std::string name) {

        if ( name.compare("reversal") == 0 ) {

            return get_matrix_variable_all<double>(reversal);
        }


        // should not happen
        std::cerr << "ProjStruct39::get_local_attribute_all_double: " << name << " not found" << std::endl;
        return std::vector<std::vector<double>>();
    }

    std::vector<double> get_local_attribute_row_double(std::string name, int rk_post) {

        if ( name.compare("reversal") == 0 ) {

            return get_matrix_variable_row<double>(reversal, rk_post);
        }


        // should not happen
        std::cerr << "ProjStruct39::get_local_attribute_row_double: " << name << " not found" << std::endl;
        return std::vector<double>();
    }

    double get_local_attribute_double(std::string name, int rk_post, int rk_pre) {

        if ( name.compare("reversal") == 0 ) {

            return get_matrix_variable<double>(reversal, rk_post, rk_pre);
        }


        // should not happen
        std::cerr << "ProjStruct39::get_local_attribute: " << name << " not found" << std::endl;
        return 0.0;
    }

    void set_local_attribute_all_double(std::string name, std::vector<std::vector<double>> value) {

        if ( name.compare("reversal") == 0 ) {
            update_matrix_variable_all<double>(reversal, value);

            return;
        }

    }

    void set_local_attribute_row_double(std::string name, int rk_post, std::vector<double> value) {

        if ( name.compare("reversal") == 0 ) {
            update_matrix_variable_row<double>(reversal, rk_post, value);

            return;
        }

    }

    void set_local_attribute_double(std::string name, int rk_post, int rk_pre, double value) {

        if ( name.compare("reversal") == 0 ) {
            update_matrix_variable<double>(reversal, rk_post, rk_pre, value);

            return;
        }

    }

    double get_global_attribute_double(std::string name) {

        if ( name.compare("w") == 0 ) {
            return w;
        }


        // should not happen
        std::cerr << "ProjStruct39::get_global_attribute_double: " << name << " not found" << std::endl;
        return 0.0;
    }

    void set_global_attribute_double(std::string name, double value) {

        if ( name.compare("w") == 0 ) {
            w = value;

            return;
        }

    }


    // Access additional


    // Memory management
    long int size_in_bytes() {
        long int size_in_bytes = 0;

        // connectivity
        size_in_bytes += static_cast<LILMatrix<int, int>*>(this)->size_in_bytes();

        // Local parameter reversal
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * reversal.capacity();
        for(auto it = reversal.cbegin(); it != reversal.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Global parameter w
        size_in_bytes += sizeof(double);

        return size_in_bytes;
    }

    // Structural plasticity



    void clear() {
    #ifdef _DEBUG
        std::cout << "ProjStruct39::clear() - this = " << this << std::endl;
    #endif

        // Connectivity
        static_cast<LILMatrix<int, int>*>(this)->clear();

        // reversal
        for (auto it = reversal.begin(); it != reversal.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        reversal.clear();
        reversal.shrink_to_fit();

    }
};

