/*
 *  ANNarchy-version: 4.7.1.5
 */
#pragma once

#include "ANNarchy.h"
#include "LILMatrix.hpp"




extern PopStruct10 pop10;
extern PopStruct11 pop11;
extern double dt;
extern long int t;

extern std::vector<std::mt19937> rng;

/////////////////////////////////////////////////////////////////////////////
// proj41: Cortex -> StrD1_putamen with target exc
/////////////////////////////////////////////////////////////////////////////
struct ProjStruct41 : LILMatrix<int, int> {
    ProjStruct41() : LILMatrix<int, int>( 120, 8000) {
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

    // Local parameter tau_alpha
    std::vector< std::vector<double > > tau_alpha;

    // Local parameter regularization_threshold
    std::vector< std::vector<double > > regularization_threshold;

    // Local parameter baseline_dopa
    std::vector< std::vector<double > > baseline_dopa;

    // Local parameter K_burst
    std::vector< std::vector<double > > K_burst;

    // Local parameter K_dip
    std::vector< std::vector<double > > K_dip;

    // Local parameter DA_type
    std::vector< std::vector<double > > DA_type;

    // Local parameter threshold_pre
    std::vector< std::vector<double > > threshold_pre;

    // Local parameter threshold_post
    std::vector< std::vector<double > > threshold_post;

    // Local variable alpha
    std::vector< std::vector<double > > alpha;

    // Local variable dopa_sum
    std::vector< std::vector<double > > dopa_sum;

    // Local variable trace
    std::vector< std::vector<double > > trace;

    // Local variable condition_0
    std::vector< std::vector<double > > condition_0;

    // Local variable dopa_mod
    std::vector< std::vector<double > > dopa_mod;

    // Local variable delta
    std::vector< std::vector<double > > delta;

    // Local variable w
    std::vector< std::vector<double > > w;




    // Method called to allocate/initialize the variables
    bool init_attributes() {

        // Local parameter tau
        tau = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local parameter tau_alpha
        tau_alpha = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local parameter regularization_threshold
        regularization_threshold = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local parameter baseline_dopa
        baseline_dopa = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local parameter K_burst
        K_burst = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local parameter K_dip
        K_dip = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local parameter DA_type
        DA_type = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local parameter threshold_pre
        threshold_pre = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local parameter threshold_post
        threshold_post = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local variable alpha
        alpha = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local variable dopa_sum
        dopa_sum = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local variable trace
        trace = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local variable condition_0
        condition_0 = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local variable dopa_mod
        dopa_mod = init_matrix_variable<double>(static_cast<double>(0.0));

        // Local variable delta
        delta = init_matrix_variable<double>(static_cast<double>(0.0));




        return true;
    }

    // Method called to initialize the projection
    void init_projection() {
    #ifdef _DEBUG
        std::cout << "ProjStruct41::init_projection() - this = " << this << std::endl;
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
        std::cout << "    ProjStruct41::compute_psp()" << std::endl;
    #endif
        double sum;

        if (_transmission && pop11._active){



            for (int i = 0; i < post_rank.size(); i++) {

                sum = 0.0;
                for (int j = 0; j < pre_rank[i].size(); j++) {
                    sum += pop10.r[pre_rank[i][j]]*w[i][j] ;
                }
                pop11._sum_exc[post_rank[i]] += sum;
            }

        } // active

    }

    // Draws random numbers
    void update_rng() {

    }

    // Updates synaptic variables
    void update_synapse() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "    ProjStruct41::update_synapse()" << std::endl;
    #endif

        int rk_post, rk_pre;
        double _dt = dt * _update_period;

        // Check periodicity
        if(_transmission && _update && pop11._active && ( (t - _update_offset)%_update_period == 0L) ){
            // Global variables


            // Semiglobal/Local variables
            for (int i = 0; i < post_rank.size(); i++) {
                rk_post = post_rank[i]; // Get postsynaptic rank

                // Semi-global variables


                // Local variables
                for (int j = 0; j < pre_rank[i].size(); j++) {
                    rk_pre = pre_rank[i][j]; // Get presynaptic rank

                    // tau_alpha*dalpha/_dt  + alpha = pos(post.mp - regularization_threshold)
                    double _alpha = (-alpha[i][j] + positive(pop11.mp[rk_post] - regularization_threshold[i][j]))/tau_alpha[i][j];

                    // tau_alpha*dalpha/_dt  + alpha = pos(post.mp - regularization_threshold)
                    alpha[i][j] += _dt*_alpha ;


                    // dopa_sum = 2.0*(post.sum(dopa) - baseline_dopa)
                    dopa_sum[i][j] = 2.0*(pop11._sum_dopa[rk_post] - baseline_dopa[i][j]);


                    // trace = pos(post.r -  mean(post.r) - threshold_post) * (pre.r - mean(pre.r) - threshold_pre)
                    trace[i][j] = (-pop10._mean_r + pop10.r[rk_pre] - threshold_pre[i][j])*positive(-pop11._mean_r + pop11.r[rk_post] - threshold_post[i][j]);


                    // condition_0 = if (trace>0.0) and (w >0.0): 1 else: 0
                    condition_0[i][j] = (trace[i][j] > 0.0 && w[i][j] > 0.0 ? 1 : 0);


                    // dopa_mod = if (DA_type*dopa_sum>0): DA_type*K_burst*dopa_sum else: condition_0*DA_type*K_dip*dopa_sum
                    dopa_mod[i][j] = (DA_type[i][j]*dopa_sum[i][j] > 0 ? DA_type[i][j]*K_burst[i][j]*dopa_sum[i][j] : DA_type[i][j]*K_dip[i][j]*condition_0[i][j]*dopa_sum[i][j]);


                    // delta = (dopa_mod* trace - alpha*pos(post.r - mean(post.r) - threshold_post)*pos(post.r - mean(post.r) - threshold_post))
                    delta[i][j] = -alpha[i][j]*positive(-pop11._mean_r + pop11.r[rk_post] - threshold_post[i][j])*positive(-pop11._mean_r + pop11.r[rk_post] - threshold_post[i][j]) + dopa_mod[i][j]*trace[i][j];


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

        if ( name.compare("tau_alpha") == 0 ) {

            return get_matrix_variable_all<double>(tau_alpha);
        }

        if ( name.compare("regularization_threshold") == 0 ) {

            return get_matrix_variable_all<double>(regularization_threshold);
        }

        if ( name.compare("baseline_dopa") == 0 ) {

            return get_matrix_variable_all<double>(baseline_dopa);
        }

        if ( name.compare("K_burst") == 0 ) {

            return get_matrix_variable_all<double>(K_burst);
        }

        if ( name.compare("K_dip") == 0 ) {

            return get_matrix_variable_all<double>(K_dip);
        }

        if ( name.compare("DA_type") == 0 ) {

            return get_matrix_variable_all<double>(DA_type);
        }

        if ( name.compare("threshold_pre") == 0 ) {

            return get_matrix_variable_all<double>(threshold_pre);
        }

        if ( name.compare("threshold_post") == 0 ) {

            return get_matrix_variable_all<double>(threshold_post);
        }

        if ( name.compare("alpha") == 0 ) {

            return get_matrix_variable_all<double>(alpha);
        }

        if ( name.compare("dopa_sum") == 0 ) {

            return get_matrix_variable_all<double>(dopa_sum);
        }

        if ( name.compare("trace") == 0 ) {

            return get_matrix_variable_all<double>(trace);
        }

        if ( name.compare("condition_0") == 0 ) {

            return get_matrix_variable_all<double>(condition_0);
        }

        if ( name.compare("dopa_mod") == 0 ) {

            return get_matrix_variable_all<double>(dopa_mod);
        }

        if ( name.compare("delta") == 0 ) {

            return get_matrix_variable_all<double>(delta);
        }

        if ( name.compare("w") == 0 ) {

            return get_matrix_variable_all<double>(w);
        }


        // should not happen
        std::cerr << "ProjStruct41::get_local_attribute_all_double: " << name << " not found" << std::endl;
        return std::vector<std::vector<double>>();
    }

    std::vector<double> get_local_attribute_row_double(std::string name, int rk_post) {

        if ( name.compare("tau") == 0 ) {

            return get_matrix_variable_row<double>(tau, rk_post);
        }

        if ( name.compare("tau_alpha") == 0 ) {

            return get_matrix_variable_row<double>(tau_alpha, rk_post);
        }

        if ( name.compare("regularization_threshold") == 0 ) {

            return get_matrix_variable_row<double>(regularization_threshold, rk_post);
        }

        if ( name.compare("baseline_dopa") == 0 ) {

            return get_matrix_variable_row<double>(baseline_dopa, rk_post);
        }

        if ( name.compare("K_burst") == 0 ) {

            return get_matrix_variable_row<double>(K_burst, rk_post);
        }

        if ( name.compare("K_dip") == 0 ) {

            return get_matrix_variable_row<double>(K_dip, rk_post);
        }

        if ( name.compare("DA_type") == 0 ) {

            return get_matrix_variable_row<double>(DA_type, rk_post);
        }

        if ( name.compare("threshold_pre") == 0 ) {

            return get_matrix_variable_row<double>(threshold_pre, rk_post);
        }

        if ( name.compare("threshold_post") == 0 ) {

            return get_matrix_variable_row<double>(threshold_post, rk_post);
        }

        if ( name.compare("alpha") == 0 ) {

            return get_matrix_variable_row<double>(alpha, rk_post);
        }

        if ( name.compare("dopa_sum") == 0 ) {

            return get_matrix_variable_row<double>(dopa_sum, rk_post);
        }

        if ( name.compare("trace") == 0 ) {

            return get_matrix_variable_row<double>(trace, rk_post);
        }

        if ( name.compare("condition_0") == 0 ) {

            return get_matrix_variable_row<double>(condition_0, rk_post);
        }

        if ( name.compare("dopa_mod") == 0 ) {

            return get_matrix_variable_row<double>(dopa_mod, rk_post);
        }

        if ( name.compare("delta") == 0 ) {

            return get_matrix_variable_row<double>(delta, rk_post);
        }

        if ( name.compare("w") == 0 ) {

            return get_matrix_variable_row<double>(w, rk_post);
        }


        // should not happen
        std::cerr << "ProjStruct41::get_local_attribute_row_double: " << name << " not found" << std::endl;
        return std::vector<double>();
    }

    double get_local_attribute_double(std::string name, int rk_post, int rk_pre) {

        if ( name.compare("tau") == 0 ) {

            return get_matrix_variable<double>(tau, rk_post, rk_pre);
        }

        if ( name.compare("tau_alpha") == 0 ) {

            return get_matrix_variable<double>(tau_alpha, rk_post, rk_pre);
        }

        if ( name.compare("regularization_threshold") == 0 ) {

            return get_matrix_variable<double>(regularization_threshold, rk_post, rk_pre);
        }

        if ( name.compare("baseline_dopa") == 0 ) {

            return get_matrix_variable<double>(baseline_dopa, rk_post, rk_pre);
        }

        if ( name.compare("K_burst") == 0 ) {

            return get_matrix_variable<double>(K_burst, rk_post, rk_pre);
        }

        if ( name.compare("K_dip") == 0 ) {

            return get_matrix_variable<double>(K_dip, rk_post, rk_pre);
        }

        if ( name.compare("DA_type") == 0 ) {

            return get_matrix_variable<double>(DA_type, rk_post, rk_pre);
        }

        if ( name.compare("threshold_pre") == 0 ) {

            return get_matrix_variable<double>(threshold_pre, rk_post, rk_pre);
        }

        if ( name.compare("threshold_post") == 0 ) {

            return get_matrix_variable<double>(threshold_post, rk_post, rk_pre);
        }

        if ( name.compare("alpha") == 0 ) {

            return get_matrix_variable<double>(alpha, rk_post, rk_pre);
        }

        if ( name.compare("dopa_sum") == 0 ) {

            return get_matrix_variable<double>(dopa_sum, rk_post, rk_pre);
        }

        if ( name.compare("trace") == 0 ) {

            return get_matrix_variable<double>(trace, rk_post, rk_pre);
        }

        if ( name.compare("condition_0") == 0 ) {

            return get_matrix_variable<double>(condition_0, rk_post, rk_pre);
        }

        if ( name.compare("dopa_mod") == 0 ) {

            return get_matrix_variable<double>(dopa_mod, rk_post, rk_pre);
        }

        if ( name.compare("delta") == 0 ) {

            return get_matrix_variable<double>(delta, rk_post, rk_pre);
        }

        if ( name.compare("w") == 0 ) {

            return get_matrix_variable<double>(w, rk_post, rk_pre);
        }


        // should not happen
        std::cerr << "ProjStruct41::get_local_attribute: " << name << " not found" << std::endl;
        return 0.0;
    }

    void set_local_attribute_all_double(std::string name, std::vector<std::vector<double>> value) {

        if ( name.compare("tau") == 0 ) {
            update_matrix_variable_all<double>(tau, value);

            return;
        }

        if ( name.compare("tau_alpha") == 0 ) {
            update_matrix_variable_all<double>(tau_alpha, value);

            return;
        }

        if ( name.compare("regularization_threshold") == 0 ) {
            update_matrix_variable_all<double>(regularization_threshold, value);

            return;
        }

        if ( name.compare("baseline_dopa") == 0 ) {
            update_matrix_variable_all<double>(baseline_dopa, value);

            return;
        }

        if ( name.compare("K_burst") == 0 ) {
            update_matrix_variable_all<double>(K_burst, value);

            return;
        }

        if ( name.compare("K_dip") == 0 ) {
            update_matrix_variable_all<double>(K_dip, value);

            return;
        }

        if ( name.compare("DA_type") == 0 ) {
            update_matrix_variable_all<double>(DA_type, value);

            return;
        }

        if ( name.compare("threshold_pre") == 0 ) {
            update_matrix_variable_all<double>(threshold_pre, value);

            return;
        }

        if ( name.compare("threshold_post") == 0 ) {
            update_matrix_variable_all<double>(threshold_post, value);

            return;
        }

        if ( name.compare("alpha") == 0 ) {
            update_matrix_variable_all<double>(alpha, value);

            return;
        }

        if ( name.compare("dopa_sum") == 0 ) {
            update_matrix_variable_all<double>(dopa_sum, value);

            return;
        }

        if ( name.compare("trace") == 0 ) {
            update_matrix_variable_all<double>(trace, value);

            return;
        }

        if ( name.compare("condition_0") == 0 ) {
            update_matrix_variable_all<double>(condition_0, value);

            return;
        }

        if ( name.compare("dopa_mod") == 0 ) {
            update_matrix_variable_all<double>(dopa_mod, value);

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

        if ( name.compare("tau_alpha") == 0 ) {
            update_matrix_variable_row<double>(tau_alpha, rk_post, value);

            return;
        }

        if ( name.compare("regularization_threshold") == 0 ) {
            update_matrix_variable_row<double>(regularization_threshold, rk_post, value);

            return;
        }

        if ( name.compare("baseline_dopa") == 0 ) {
            update_matrix_variable_row<double>(baseline_dopa, rk_post, value);

            return;
        }

        if ( name.compare("K_burst") == 0 ) {
            update_matrix_variable_row<double>(K_burst, rk_post, value);

            return;
        }

        if ( name.compare("K_dip") == 0 ) {
            update_matrix_variable_row<double>(K_dip, rk_post, value);

            return;
        }

        if ( name.compare("DA_type") == 0 ) {
            update_matrix_variable_row<double>(DA_type, rk_post, value);

            return;
        }

        if ( name.compare("threshold_pre") == 0 ) {
            update_matrix_variable_row<double>(threshold_pre, rk_post, value);

            return;
        }

        if ( name.compare("threshold_post") == 0 ) {
            update_matrix_variable_row<double>(threshold_post, rk_post, value);

            return;
        }

        if ( name.compare("alpha") == 0 ) {
            update_matrix_variable_row<double>(alpha, rk_post, value);

            return;
        }

        if ( name.compare("dopa_sum") == 0 ) {
            update_matrix_variable_row<double>(dopa_sum, rk_post, value);

            return;
        }

        if ( name.compare("trace") == 0 ) {
            update_matrix_variable_row<double>(trace, rk_post, value);

            return;
        }

        if ( name.compare("condition_0") == 0 ) {
            update_matrix_variable_row<double>(condition_0, rk_post, value);

            return;
        }

        if ( name.compare("dopa_mod") == 0 ) {
            update_matrix_variable_row<double>(dopa_mod, rk_post, value);

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

        if ( name.compare("tau_alpha") == 0 ) {
            update_matrix_variable<double>(tau_alpha, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("regularization_threshold") == 0 ) {
            update_matrix_variable<double>(regularization_threshold, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("baseline_dopa") == 0 ) {
            update_matrix_variable<double>(baseline_dopa, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("K_burst") == 0 ) {
            update_matrix_variable<double>(K_burst, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("K_dip") == 0 ) {
            update_matrix_variable<double>(K_dip, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("DA_type") == 0 ) {
            update_matrix_variable<double>(DA_type, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("threshold_pre") == 0 ) {
            update_matrix_variable<double>(threshold_pre, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("threshold_post") == 0 ) {
            update_matrix_variable<double>(threshold_post, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("alpha") == 0 ) {
            update_matrix_variable<double>(alpha, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("dopa_sum") == 0 ) {
            update_matrix_variable<double>(dopa_sum, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("trace") == 0 ) {
            update_matrix_variable<double>(trace, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("condition_0") == 0 ) {
            update_matrix_variable<double>(condition_0, rk_post, rk_pre, value);

            return;
        }

        if ( name.compare("dopa_mod") == 0 ) {
            update_matrix_variable<double>(dopa_mod, rk_post, rk_pre, value);

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

        // Local variable alpha
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * alpha.capacity();
        for(auto it = alpha.cbegin(); it != alpha.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local variable dopa_sum
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * dopa_sum.capacity();
        for(auto it = dopa_sum.cbegin(); it != dopa_sum.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local variable trace
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * trace.capacity();
        for(auto it = trace.cbegin(); it != trace.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local variable condition_0
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * condition_0.capacity();
        for(auto it = condition_0.cbegin(); it != condition_0.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local variable dopa_mod
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * dopa_mod.capacity();
        for(auto it = dopa_mod.cbegin(); it != dopa_mod.cend(); it++)
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

        // Local parameter tau_alpha
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * tau_alpha.capacity();
        for(auto it = tau_alpha.cbegin(); it != tau_alpha.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local parameter regularization_threshold
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * regularization_threshold.capacity();
        for(auto it = regularization_threshold.cbegin(); it != regularization_threshold.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local parameter baseline_dopa
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * baseline_dopa.capacity();
        for(auto it = baseline_dopa.cbegin(); it != baseline_dopa.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local parameter K_burst
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * K_burst.capacity();
        for(auto it = K_burst.cbegin(); it != K_burst.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local parameter K_dip
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * K_dip.capacity();
        for(auto it = K_dip.cbegin(); it != K_dip.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local parameter DA_type
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * DA_type.capacity();
        for(auto it = DA_type.cbegin(); it != DA_type.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local parameter threshold_pre
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * threshold_pre.capacity();
        for(auto it = threshold_pre.cbegin(); it != threshold_pre.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        // Local parameter threshold_post
        size_in_bytes += sizeof(std::vector<std::vector<double>>);
        size_in_bytes += sizeof(std::vector<double>) * threshold_post.capacity();
        for(auto it = threshold_post.cbegin(); it != threshold_post.cend(); it++)
            size_in_bytes += (it->capacity()) * sizeof(double);

        return size_in_bytes;
    }

    // Structural plasticity



    void clear() {
    #ifdef _DEBUG
        std::cout << "ProjStruct41::clear() - this = " << this << std::endl;
    #endif

        // Connectivity
        static_cast<LILMatrix<int, int>*>(this)->clear();

        // alpha
        for (auto it = alpha.begin(); it != alpha.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        alpha.clear();
        alpha.shrink_to_fit();

        // dopa_sum
        for (auto it = dopa_sum.begin(); it != dopa_sum.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        dopa_sum.clear();
        dopa_sum.shrink_to_fit();

        // trace
        for (auto it = trace.begin(); it != trace.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        trace.clear();
        trace.shrink_to_fit();

        // condition_0
        for (auto it = condition_0.begin(); it != condition_0.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        condition_0.clear();
        condition_0.shrink_to_fit();

        // dopa_mod
        for (auto it = dopa_mod.begin(); it != dopa_mod.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        dopa_mod.clear();
        dopa_mod.shrink_to_fit();

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

        // tau_alpha
        for (auto it = tau_alpha.begin(); it != tau_alpha.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        tau_alpha.clear();
        tau_alpha.shrink_to_fit();

        // regularization_threshold
        for (auto it = regularization_threshold.begin(); it != regularization_threshold.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        regularization_threshold.clear();
        regularization_threshold.shrink_to_fit();

        // baseline_dopa
        for (auto it = baseline_dopa.begin(); it != baseline_dopa.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        baseline_dopa.clear();
        baseline_dopa.shrink_to_fit();

        // K_burst
        for (auto it = K_burst.begin(); it != K_burst.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        K_burst.clear();
        K_burst.shrink_to_fit();

        // K_dip
        for (auto it = K_dip.begin(); it != K_dip.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        K_dip.clear();
        K_dip.shrink_to_fit();

        // DA_type
        for (auto it = DA_type.begin(); it != DA_type.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        DA_type.clear();
        DA_type.shrink_to_fit();

        // threshold_pre
        for (auto it = threshold_pre.begin(); it != threshold_pre.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        threshold_pre.clear();
        threshold_pre.shrink_to_fit();

        // threshold_post
        for (auto it = threshold_post.begin(); it != threshold_post.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        };
        threshold_post.clear();
        threshold_post.shrink_to_fit();

    }
};

