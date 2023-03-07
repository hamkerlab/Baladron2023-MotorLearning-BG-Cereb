#pragma once
extern long int t;

int addRecorder(class Monitor* recorder);
Monitor* getRecorder(int id);
void removeRecorder(class Monitor* recorder);

/*
 * Recorders
 *
 */
class Monitor
{
public:
    Monitor(std::vector<int> ranks, int period, int period_offset, long int offset) {
        this->ranks = ranks;
        this->period_ = period;
        this->period_offset_ = period_offset;
        this->offset_ = offset;
        if(this->ranks.size() ==1 && this->ranks[0]==-1) // All neurons should be recorded
            this->partial = false;
        else
            this->partial = true;
    };

    ~Monitor() = default;

    virtual void record() = 0;
    virtual void record_targets() = 0;
    virtual long int size_in_bytes() = 0;
    virtual void clear() = 0;

    // Attributes
    bool partial;
    std::vector<int> ranks;
    int period_;
    int period_offset_;
    long int offset_;
};

class PopRecorder0 : public Monitor
{
protected:
    PopRecorder0(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder0 (" << this << ") instantiated." << std::endl;
    #endif

    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder0(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder0 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder0* get_instance(int id) {
        return static_cast<PopRecorder0*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder0::record()" << std::endl;
    #endif

    }

    void record_targets() {

    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder0 ( " << this << " ) " << std::endl;
    #endif


        removeRecorder(this);
    }



};

class PopRecorder1 : public Monitor
{
protected:
    PopRecorder1(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder1 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_in = std::vector< std::vector< double > >();
        this->record__sum_in = false; 
        this->perturbation = std::vector< std::vector< double > >();
        this->record_perturbation = false; 
        this->noise = std::vector< std::vector< double > >();
        this->record_noise = false; 
        this->x = std::vector< std::vector< double > >();
        this->record_x = false; 
        this->rprev = std::vector< std::vector< double > >();
        this->record_rprev = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
        this->delta_x = std::vector< std::vector< double > >();
        this->record_delta_x = false; 
        this->x_mean = std::vector< std::vector< double > >();
        this->record_x_mean = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder1(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder1 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder1* get_instance(int id) {
        return static_cast<PopRecorder1*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder1::record()" << std::endl;
    #endif

        if(this->record_perturbation && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->perturbation.push_back(pop1.perturbation);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1.perturbation[this->ranks[i]]);
                }
                this->perturbation.push_back(tmp);
            }
        }
        if(this->record_noise && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->noise.push_back(pop1.noise);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1.noise[this->ranks[i]]);
                }
                this->noise.push_back(tmp);
            }
        }
        if(this->record_x && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->x.push_back(pop1.x);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1.x[this->ranks[i]]);
                }
                this->x.push_back(tmp);
            }
        }
        if(this->record_rprev && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->rprev.push_back(pop1.rprev);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1.rprev[this->ranks[i]]);
                }
                this->rprev.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop1.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
        if(this->record_delta_x && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->delta_x.push_back(pop1.delta_x);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1.delta_x[this->ranks[i]]);
                }
                this->delta_x.push_back(tmp);
            }
        }
        if(this->record_x_mean && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->x_mean.push_back(pop1.x_mean);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1.x_mean[this->ranks[i]]);
                }
                this->x_mean.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop1._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_in && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_in.push_back(pop1._sum_in);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop1._sum_in[this->ranks[i]]);
                }
                this->_sum_in.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable perturbation
        size_in_bytes += sizeof(std::vector<double>) * perturbation.capacity();
        for(auto it=perturbation.begin(); it!= perturbation.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable noise
        size_in_bytes += sizeof(std::vector<double>) * noise.capacity();
        for(auto it=noise.begin(); it!= noise.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable x
        size_in_bytes += sizeof(std::vector<double>) * x.capacity();
        for(auto it=x.begin(); it!= x.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable rprev
        size_in_bytes += sizeof(std::vector<double>) * rprev.capacity();
        for(auto it=rprev.begin(); it!= rprev.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable delta_x
        size_in_bytes += sizeof(std::vector<double>) * delta_x.capacity();
        for(auto it=delta_x.begin(); it!= delta_x.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable x_mean
        size_in_bytes += sizeof(std::vector<double>) * x_mean.capacity();
        for(auto it=x_mean.begin(); it!= x_mean.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder1 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->perturbation.begin(); it != this->perturbation.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->perturbation.clear();
    
        for(auto it = this->noise.begin(); it != this->noise.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->noise.clear();
    
        for(auto it = this->x.begin(); it != this->x.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->x.clear();
    
        for(auto it = this->rprev.begin(); it != this->rprev.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->rprev.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    
        for(auto it = this->delta_x.begin(); it != this->delta_x.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->delta_x.clear();
    
        for(auto it = this->x_mean.begin(); it != this->x_mean.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->x_mean.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_in
    std::vector< std::vector< double > > _sum_in ;
    bool record__sum_in ; 
    // Local variable perturbation
    std::vector< std::vector< double > > perturbation ;
    bool record_perturbation ; 
    // Local variable noise
    std::vector< std::vector< double > > noise ;
    bool record_noise ; 
    // Local variable x
    std::vector< std::vector< double > > x ;
    bool record_x ; 
    // Local variable rprev
    std::vector< std::vector< double > > rprev ;
    bool record_rprev ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
    // Local variable delta_x
    std::vector< std::vector< double > > delta_x ;
    bool record_delta_x ; 
    // Local variable x_mean
    std::vector< std::vector< double > > x_mean ;
    bool record_x_mean ; 
};

class PopRecorder2 : public Monitor
{
protected:
    PopRecorder2(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder2 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->trace = std::vector< std::vector< double > >();
        this->record_trace = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder2(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder2 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder2* get_instance(int id) {
        return static_cast<PopRecorder2*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder2::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop2.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_trace && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->trace.push_back(pop2.trace);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.trace[this->ranks[i]]);
                }
                this->trace.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop2.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop2._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop2._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop2._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable trace
        size_in_bytes += sizeof(std::vector<double>) * trace.capacity();
        for(auto it=trace.begin(); it!= trace.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder2 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->trace.begin(); it != this->trace.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->trace.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable trace
    std::vector< std::vector< double > > trace ;
    bool record_trace ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class PopRecorder3 : public Monitor
{
protected:
    PopRecorder3(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder3 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->trace = std::vector< std::vector< double > >();
        this->record_trace = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder3(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder3 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder3* get_instance(int id) {
        return static_cast<PopRecorder3*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder3::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop3.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop3.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_trace && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->trace.push_back(pop3.trace);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop3.trace[this->ranks[i]]);
                }
                this->trace.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop3.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop3.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop3._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop3._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop3._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop3._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable trace
        size_in_bytes += sizeof(std::vector<double>) * trace.capacity();
        for(auto it=trace.begin(); it!= trace.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder3 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->trace.begin(); it != this->trace.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->trace.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable trace
    std::vector< std::vector< double > > trace ;
    bool record_trace ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class PopRecorder4 : public Monitor
{
protected:
    PopRecorder4(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder4 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->trace = std::vector< std::vector< double > >();
        this->record_trace = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder4(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder4 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder4* get_instance(int id) {
        return static_cast<PopRecorder4*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder4::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop4.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop4.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_trace && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->trace.push_back(pop4.trace);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop4.trace[this->ranks[i]]);
                }
                this->trace.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop4.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop4.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop4._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop4._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop4._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop4._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable trace
        size_in_bytes += sizeof(std::vector<double>) * trace.capacity();
        for(auto it=trace.begin(); it!= trace.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder4 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->trace.begin(); it != this->trace.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->trace.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable trace
    std::vector< std::vector< double > > trace ;
    bool record_trace ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class PopRecorder5 : public Monitor
{
protected:
    PopRecorder5(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder5 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->trace = std::vector< std::vector< double > >();
        this->record_trace = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder5(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder5 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder5* get_instance(int id) {
        return static_cast<PopRecorder5*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder5::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop5.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop5.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_trace && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->trace.push_back(pop5.trace);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop5.trace[this->ranks[i]]);
                }
                this->trace.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop5.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop5.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop5._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop5._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop5._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop5._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable trace
        size_in_bytes += sizeof(std::vector<double>) * trace.capacity();
        for(auto it=trace.begin(); it!= trace.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder5 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->trace.begin(); it != this->trace.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->trace.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable trace
    std::vector< std::vector< double > > trace ;
    bool record_trace ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class PopRecorder6 : public Monitor
{
protected:
    PopRecorder6(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder6 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->trace = std::vector< std::vector< double > >();
        this->record_trace = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder6(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder6 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder6* get_instance(int id) {
        return static_cast<PopRecorder6*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder6::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop6.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop6.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_trace && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->trace.push_back(pop6.trace);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop6.trace[this->ranks[i]]);
                }
                this->trace.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop6.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop6.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop6._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop6._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop6._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop6._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable trace
        size_in_bytes += sizeof(std::vector<double>) * trace.capacity();
        for(auto it=trace.begin(); it!= trace.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder6 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->trace.begin(); it != this->trace.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->trace.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable trace
    std::vector< std::vector< double > > trace ;
    bool record_trace ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class PopRecorder7 : public Monitor
{
protected:
    PopRecorder7(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder7 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->trace = std::vector< std::vector< double > >();
        this->record_trace = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder7(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder7 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder7* get_instance(int id) {
        return static_cast<PopRecorder7*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder7::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop7.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop7.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_trace && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->trace.push_back(pop7.trace);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop7.trace[this->ranks[i]]);
                }
                this->trace.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop7.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop7.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop7._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop7._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop7._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop7._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable trace
        size_in_bytes += sizeof(std::vector<double>) * trace.capacity();
        for(auto it=trace.begin(); it!= trace.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder7 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->trace.begin(); it != this->trace.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->trace.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable trace
    std::vector< std::vector< double > > trace ;
    bool record_trace ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class PopRecorder8 : public Monitor
{
protected:
    PopRecorder8(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder8 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->trace = std::vector< std::vector< double > >();
        this->record_trace = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder8(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder8 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder8* get_instance(int id) {
        return static_cast<PopRecorder8*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder8::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop8.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop8.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_trace && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->trace.push_back(pop8.trace);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop8.trace[this->ranks[i]]);
                }
                this->trace.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop8.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop8.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop8._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop8._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop8._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop8._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable trace
        size_in_bytes += sizeof(std::vector<double>) * trace.capacity();
        for(auto it=trace.begin(); it!= trace.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder8 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->trace.begin(); it != this->trace.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->trace.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable trace
    std::vector< std::vector< double > > trace ;
    bool record_trace ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class PopRecorder9 : public Monitor
{
protected:
    PopRecorder9(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder9 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->trace = std::vector< std::vector< double > >();
        this->record_trace = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder9(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder9 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder9* get_instance(int id) {
        return static_cast<PopRecorder9*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder9::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop9.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop9.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_trace && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->trace.push_back(pop9.trace);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop9.trace[this->ranks[i]]);
                }
                this->trace.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop9.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop9.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop9._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop9._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop9._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop9._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable trace
        size_in_bytes += sizeof(std::vector<double>) * trace.capacity();
        for(auto it=trace.begin(); it!= trace.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder9 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->trace.begin(); it != this->trace.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->trace.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable trace
    std::vector< std::vector< double > > trace ;
    bool record_trace ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class PopRecorder10 : public Monitor
{
protected:
    PopRecorder10(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder10 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
        this->trace = std::vector< std::vector< double > >();
        this->record_trace = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder10(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder10 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder10* get_instance(int id) {
        return static_cast<PopRecorder10*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder10::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop10.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop10.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop10.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop10.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
        if(this->record_trace && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->trace.push_back(pop10.trace);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop10.trace[this->ranks[i]]);
                }
                this->trace.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop10._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop10._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop10._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop10._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable trace
        size_in_bytes += sizeof(std::vector<double>) * trace.capacity();
        for(auto it=trace.begin(); it!= trace.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder10 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    
        for(auto it = this->trace.begin(); it != this->trace.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->trace.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
    // Local variable trace
    std::vector< std::vector< double > > trace ;
    bool record_trace ; 
};

class PopRecorder11 : public Monitor
{
protected:
    PopRecorder11(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder11 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_dopa = std::vector< std::vector< double > >();
        this->record__sum_dopa = false; 
        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
        this->trace = std::vector< std::vector< double > >();
        this->record_trace = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder11(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder11 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder11* get_instance(int id) {
        return static_cast<PopRecorder11*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder11::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop11.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop11.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop11.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop11.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
        if(this->record_trace && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->trace.push_back(pop11.trace);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop11.trace[this->ranks[i]]);
                }
                this->trace.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_dopa && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_dopa.push_back(pop11._sum_dopa);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop11._sum_dopa[this->ranks[i]]);
                }
                this->_sum_dopa.push_back(tmp);
            }
        }
        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop11._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop11._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop11._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop11._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable trace
        size_in_bytes += sizeof(std::vector<double>) * trace.capacity();
        for(auto it=trace.begin(); it!= trace.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder11 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    
        for(auto it = this->trace.begin(); it != this->trace.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->trace.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_dopa
    std::vector< std::vector< double > > _sum_dopa ;
    bool record__sum_dopa ; 
    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
    // Local variable trace
    std::vector< std::vector< double > > trace ;
    bool record_trace ; 
};

class PopRecorder12 : public Monitor
{
protected:
    PopRecorder12(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder12 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder12(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder12 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder12* get_instance(int id) {
        return static_cast<PopRecorder12*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder12::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop12.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop12.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop12.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop12.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop12._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop12._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop12._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop12._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder12 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class PopRecorder13 : public Monitor
{
protected:
    PopRecorder13(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder13 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_dopa = std::vector< std::vector< double > >();
        this->record__sum_dopa = false; 
        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
        this->trace = std::vector< std::vector< double > >();
        this->record_trace = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder13(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder13 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder13* get_instance(int id) {
        return static_cast<PopRecorder13*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder13::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop13.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop13.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop13.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop13.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
        if(this->record_trace && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->trace.push_back(pop13.trace);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop13.trace[this->ranks[i]]);
                }
                this->trace.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_dopa && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_dopa.push_back(pop13._sum_dopa);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop13._sum_dopa[this->ranks[i]]);
                }
                this->_sum_dopa.push_back(tmp);
            }
        }
        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop13._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop13._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop13._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop13._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable trace
        size_in_bytes += sizeof(std::vector<double>) * trace.capacity();
        for(auto it=trace.begin(); it!= trace.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder13 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    
        for(auto it = this->trace.begin(); it != this->trace.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->trace.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_dopa
    std::vector< std::vector< double > > _sum_dopa ;
    bool record__sum_dopa ; 
    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
    // Local variable trace
    std::vector< std::vector< double > > trace ;
    bool record_trace ; 
};

class PopRecorder14 : public Monitor
{
protected:
    PopRecorder14(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder14 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder14(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder14 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder14* get_instance(int id) {
        return static_cast<PopRecorder14*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder14::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop14.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop14.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop14.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop14.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop14._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop14._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop14._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop14._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder14 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class PopRecorder15 : public Monitor
{
protected:
    PopRecorder15(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder15 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->ex_in = std::vector< std::vector< double > >();
        this->record_ex_in = false; 
        this->s_exc = std::vector< std::vector< double > >();
        this->record_s_exc = false; 
        this->s_inh = std::vector< std::vector< double > >();
        this->record_s_inh = false; 
        this->aux = std::vector< std::vector< double > >();
        this->record_aux = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder15(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder15 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder15* get_instance(int id) {
        return static_cast<PopRecorder15*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder15::record()" << std::endl;
    #endif

        if(this->record_ex_in && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->ex_in.push_back(pop15.ex_in);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop15.ex_in[this->ranks[i]]);
                }
                this->ex_in.push_back(tmp);
            }
        }
        if(this->record_s_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->s_exc.push_back(pop15.s_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop15.s_exc[this->ranks[i]]);
                }
                this->s_exc.push_back(tmp);
            }
        }
        if(this->record_s_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->s_inh.push_back(pop15.s_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop15.s_inh[this->ranks[i]]);
                }
                this->s_inh.push_back(tmp);
            }
        }
        if(this->record_aux && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->aux.push_back(pop15.aux);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop15.aux[this->ranks[i]]);
                }
                this->aux.push_back(tmp);
            }
        }
        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop15.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop15.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop15.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop15.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop15._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop15._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop15._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop15._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable ex_in
        size_in_bytes += sizeof(std::vector<double>) * ex_in.capacity();
        for(auto it=ex_in.begin(); it!= ex_in.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable s_exc
        size_in_bytes += sizeof(std::vector<double>) * s_exc.capacity();
        for(auto it=s_exc.begin(); it!= s_exc.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable s_inh
        size_in_bytes += sizeof(std::vector<double>) * s_inh.capacity();
        for(auto it=s_inh.begin(); it!= s_inh.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable aux
        size_in_bytes += sizeof(std::vector<double>) * aux.capacity();
        for(auto it=aux.begin(); it!= aux.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder15 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->ex_in.begin(); it != this->ex_in.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->ex_in.clear();
    
        for(auto it = this->s_exc.begin(); it != this->s_exc.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->s_exc.clear();
    
        for(auto it = this->s_inh.begin(); it != this->s_inh.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->s_inh.clear();
    
        for(auto it = this->aux.begin(); it != this->aux.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->aux.clear();
    
        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable ex_in
    std::vector< std::vector< double > > ex_in ;
    bool record_ex_in ; 
    // Local variable s_exc
    std::vector< std::vector< double > > s_exc ;
    bool record_s_exc ; 
    // Local variable s_inh
    std::vector< std::vector< double > > s_inh ;
    bool record_s_inh ; 
    // Local variable aux
    std::vector< std::vector< double > > aux ;
    bool record_aux ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class PopRecorder16 : public Monitor
{
protected:
    PopRecorder16(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder16 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder16(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder16 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder16* get_instance(int id) {
        return static_cast<PopRecorder16*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder16::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop16.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop16.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop16.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop16.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop16._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop16._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop16._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop16._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder16 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class PopRecorder17 : public Monitor
{
protected:
    PopRecorder17(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder17 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder17(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder17 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder17* get_instance(int id) {
        return static_cast<PopRecorder17*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder17::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop17.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop17.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop17.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop17.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop17._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop17._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop17._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop17._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder17 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class PopRecorder18 : public Monitor
{
protected:
    PopRecorder18(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "PopRecorder18 (" << this << ") instantiated." << std::endl;
    #endif

        this->_sum_exc = std::vector< std::vector< double > >();
        this->record__sum_exc = false; 
        this->_sum_inh = std::vector< std::vector< double > >();
        this->record__sum_inh = false; 
        this->mp = std::vector< std::vector< double > >();
        this->record_mp = false; 
        this->r = std::vector< std::vector< double > >();
        this->record_r = false; 
    }

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new PopRecorder18(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "PopRecorder18 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static PopRecorder18* get_instance(int id) {
        return static_cast<PopRecorder18*>(getRecorder(id));
    }

    void record() {
    #ifdef _TRACE_SIMULATION_STEPS
        std::cout << "PopRecorder18::record()" << std::endl;
    #endif

        if(this->record_mp && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->mp.push_back(pop18.mp);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop18.mp[this->ranks[i]]);
                }
                this->mp.push_back(tmp);
            }
        }
        if(this->record_r && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->r.push_back(pop18.r);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop18.r[this->ranks[i]]);
                }
                this->r.push_back(tmp);
            }
        }
    }

    void record_targets() {

        if(this->record__sum_exc && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_exc.push_back(pop18._sum_exc);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop18._sum_exc[this->ranks[i]]);
                }
                this->_sum_exc.push_back(tmp);
            }
        }
        if(this->record__sum_inh && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            if(!this->partial)
                this->_sum_inh.push_back(pop18._sum_inh);
            else{
                std::vector<double> tmp = std::vector<double>();
                for (unsigned int i=0; i<this->ranks.size(); i++){
                    tmp.push_back(pop18._sum_inh[this->ranks[i]]);
                }
                this->_sum_inh.push_back(tmp);
            }
        }
    }

    long int size_in_bytes() {
        long int size_in_bytes = 0;
        
        // local variable mp
        size_in_bytes += sizeof(std::vector<double>) * mp.capacity();
        for(auto it=mp.begin(); it!= mp.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        // local variable r
        size_in_bytes += sizeof(std::vector<double>) * r.capacity();
        for(auto it=r.begin(); it!= r.end(); it++) {
            size_in_bytes += it->capacity() * sizeof(double);
        }
        
        return size_in_bytes;
    }

    void clear() {
    #ifdef _DEBUG
        std::cout << "Delete instance of PopRecorder18 ( " << this << " ) " << std::endl;
    #endif

        for(auto it = this->mp.begin(); it != this->mp.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->mp.clear();
    
        for(auto it = this->r.begin(); it != this->r.end(); it++) {
            it->clear();
            it->shrink_to_fit();
        }
        this->r.clear();
    

        removeRecorder(this);
    }



    // Local variable _sum_exc
    std::vector< std::vector< double > > _sum_exc ;
    bool record__sum_exc ; 
    // Local variable _sum_inh
    std::vector< std::vector< double > > _sum_inh ;
    bool record__sum_inh ; 
    // Local variable mp
    std::vector< std::vector< double > > mp ;
    bool record_mp ; 
    // Local variable r
    std::vector< std::vector< double > > r ;
    bool record_r ; 
};

class ProjRecorder0 : public Monitor
{
protected:
    ProjRecorder0(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder0 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj0.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder0(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder0 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder0* get_instance(int id) {
        return static_cast<ProjRecorder0*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor0::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder1 : public Monitor
{
protected:
    ProjRecorder1(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder1 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj1.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();

        this->trace = std::vector< std::vector< std::vector< double > > >();
        this->record_trace = false;

        this->delta_w = std::vector< std::vector< std::vector< double > > >();
        this->record_delta_w = false;

        this->w = std::vector< std::vector< std::vector< double > > >();
        this->record_w = false;


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder1(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder1 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder1* get_instance(int id) {
        return static_cast<ProjRecorder1*>(getRecorder(id));
    }

    void record() {

        if(this->record_trace && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            std::vector< std::vector< double > > tmp;
            for(int i=0; i<this->ranks.size(); i++){
                tmp.push_back(std::move(proj1.get_matrix_variable_row<double>(proj1.trace, this->indices[i])));
            }
            this->trace.push_back(tmp);
            tmp.clear();
        }

        if(this->record_delta_w && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            std::vector< std::vector< double > > tmp;
            for(int i=0; i<this->ranks.size(); i++){
                tmp.push_back(std::move(proj1.get_matrix_variable_row<double>(proj1.delta_w, this->indices[i])));
            }
            this->delta_w.push_back(tmp);
            tmp.clear();
        }

        if(this->record_w && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            std::vector< std::vector< double > > tmp;
            for(int i=0; i<this->ranks.size(); i++){
                tmp.push_back(std::move(proj1.get_matrix_variable_row<double>(proj1.w, this->indices[i])));
            }
            this->w.push_back(tmp);
            tmp.clear();
        }

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor1::clear(): not implemented for openMP paradigm." << std::endl;
    }


    // Local variable trace
    std::vector< std::vector< std::vector< double > > > trace ;
    bool record_trace ;

    // Local variable delta_w
    std::vector< std::vector< std::vector< double > > > delta_w ;
    bool record_delta_w ;

    // Local variable w
    std::vector< std::vector< std::vector< double > > > w ;
    bool record_w ;

};

class ProjRecorder2 : public Monitor
{
protected:
    ProjRecorder2(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder2 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj2.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder2(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder2 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder2* get_instance(int id) {
        return static_cast<ProjRecorder2*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor2::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder3 : public Monitor
{
protected:
    ProjRecorder3(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder3 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj3.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder3(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder3 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder3* get_instance(int id) {
        return static_cast<ProjRecorder3*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor3::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder4 : public Monitor
{
protected:
    ProjRecorder4(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder4 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj4.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder4(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder4 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder4* get_instance(int id) {
        return static_cast<ProjRecorder4*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor4::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder5 : public Monitor
{
protected:
    ProjRecorder5(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder5 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj5.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder5(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder5 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder5* get_instance(int id) {
        return static_cast<ProjRecorder5*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor5::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder6 : public Monitor
{
protected:
    ProjRecorder6(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder6 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj6.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder6(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder6 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder6* get_instance(int id) {
        return static_cast<ProjRecorder6*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor6::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder7 : public Monitor
{
protected:
    ProjRecorder7(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder7 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj7.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder7(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder7 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder7* get_instance(int id) {
        return static_cast<ProjRecorder7*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor7::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder8 : public Monitor
{
protected:
    ProjRecorder8(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder8 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj8.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder8(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder8 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder8* get_instance(int id) {
        return static_cast<ProjRecorder8*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor8::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder9 : public Monitor
{
protected:
    ProjRecorder9(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder9 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj9.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder9(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder9 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder9* get_instance(int id) {
        return static_cast<ProjRecorder9*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor9::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder10 : public Monitor
{
protected:
    ProjRecorder10(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder10 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj10.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder10(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder10 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder10* get_instance(int id) {
        return static_cast<ProjRecorder10*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor10::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder11 : public Monitor
{
protected:
    ProjRecorder11(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder11 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj11.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder11(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder11 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder11* get_instance(int id) {
        return static_cast<ProjRecorder11*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor11::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder12 : public Monitor
{
protected:
    ProjRecorder12(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder12 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj12.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder12(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder12 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder12* get_instance(int id) {
        return static_cast<ProjRecorder12*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor12::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder13 : public Monitor
{
protected:
    ProjRecorder13(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder13 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj13.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder13(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder13 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder13* get_instance(int id) {
        return static_cast<ProjRecorder13*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor13::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder14 : public Monitor
{
protected:
    ProjRecorder14(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder14 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj14.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder14(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder14 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder14* get_instance(int id) {
        return static_cast<ProjRecorder14*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor14::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder15 : public Monitor
{
protected:
    ProjRecorder15(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder15 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj15.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder15(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder15 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder15* get_instance(int id) {
        return static_cast<ProjRecorder15*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor15::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder16 : public Monitor
{
protected:
    ProjRecorder16(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder16 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj16.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder16(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder16 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder16* get_instance(int id) {
        return static_cast<ProjRecorder16*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor16::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder17 : public Monitor
{
protected:
    ProjRecorder17(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder17 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj17.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder17(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder17 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder17* get_instance(int id) {
        return static_cast<ProjRecorder17*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor17::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder18 : public Monitor
{
protected:
    ProjRecorder18(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder18 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj18.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder18(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder18 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder18* get_instance(int id) {
        return static_cast<ProjRecorder18*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor18::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder19 : public Monitor
{
protected:
    ProjRecorder19(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder19 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj19.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder19(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder19 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder19* get_instance(int id) {
        return static_cast<ProjRecorder19*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor19::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder20 : public Monitor
{
protected:
    ProjRecorder20(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder20 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj20.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder20(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder20 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder20* get_instance(int id) {
        return static_cast<ProjRecorder20*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor20::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder21 : public Monitor
{
protected:
    ProjRecorder21(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder21 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj21.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder21(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder21 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder21* get_instance(int id) {
        return static_cast<ProjRecorder21*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor21::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder22 : public Monitor
{
protected:
    ProjRecorder22(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder22 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj22.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder22(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder22 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder22* get_instance(int id) {
        return static_cast<ProjRecorder22*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor22::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder23 : public Monitor
{
protected:
    ProjRecorder23(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder23 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj23.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder23(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder23 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder23* get_instance(int id) {
        return static_cast<ProjRecorder23*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor23::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder24 : public Monitor
{
protected:
    ProjRecorder24(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder24 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj24.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder24(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder24 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder24* get_instance(int id) {
        return static_cast<ProjRecorder24*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor24::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder25 : public Monitor
{
protected:
    ProjRecorder25(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder25 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj25.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder25(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder25 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder25* get_instance(int id) {
        return static_cast<ProjRecorder25*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor25::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder26 : public Monitor
{
protected:
    ProjRecorder26(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder26 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj26.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder26(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder26 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder26* get_instance(int id) {
        return static_cast<ProjRecorder26*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor26::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder27 : public Monitor
{
protected:
    ProjRecorder27(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder27 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj27.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder27(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder27 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder27* get_instance(int id) {
        return static_cast<ProjRecorder27*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor27::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder28 : public Monitor
{
protected:
    ProjRecorder28(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder28 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj28.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder28(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder28 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder28* get_instance(int id) {
        return static_cast<ProjRecorder28*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor28::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder29 : public Monitor
{
protected:
    ProjRecorder29(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder29 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj29.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder29(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder29 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder29* get_instance(int id) {
        return static_cast<ProjRecorder29*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor29::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder30 : public Monitor
{
protected:
    ProjRecorder30(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder30 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj30.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder30(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder30 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder30* get_instance(int id) {
        return static_cast<ProjRecorder30*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor30::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder31 : public Monitor
{
protected:
    ProjRecorder31(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder31 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj31.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder31(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder31 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder31* get_instance(int id) {
        return static_cast<ProjRecorder31*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor31::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder32 : public Monitor
{
protected:
    ProjRecorder32(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder32 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj32.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder32(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder32 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder32* get_instance(int id) {
        return static_cast<ProjRecorder32*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor32::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder33 : public Monitor
{
protected:
    ProjRecorder33(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder33 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj33.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder33(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder33 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder33* get_instance(int id) {
        return static_cast<ProjRecorder33*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor33::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder34 : public Monitor
{
protected:
    ProjRecorder34(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder34 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj34.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder34(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder34 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder34* get_instance(int id) {
        return static_cast<ProjRecorder34*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor34::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder35 : public Monitor
{
protected:
    ProjRecorder35(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder35 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj35.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder35(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder35 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder35* get_instance(int id) {
        return static_cast<ProjRecorder35*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor35::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder36 : public Monitor
{
protected:
    ProjRecorder36(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder36 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj36.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder36(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder36 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder36* get_instance(int id) {
        return static_cast<ProjRecorder36*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor36::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder37 : public Monitor
{
protected:
    ProjRecorder37(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder37 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj37.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder37(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder37 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder37* get_instance(int id) {
        return static_cast<ProjRecorder37*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor37::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder38 : public Monitor
{
protected:
    ProjRecorder38(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder38 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj38.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder38(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder38 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder38* get_instance(int id) {
        return static_cast<ProjRecorder38*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor38::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder39 : public Monitor
{
protected:
    ProjRecorder39(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder39 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj39.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder39(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder39 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder39* get_instance(int id) {
        return static_cast<ProjRecorder39*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor39::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder40 : public Monitor
{
protected:
    ProjRecorder40(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder40 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj40.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder40(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder40 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder40* get_instance(int id) {
        return static_cast<ProjRecorder40*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor40::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder41 : public Monitor
{
protected:
    ProjRecorder41(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder41 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj41.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();

        this->alpha = std::vector< std::vector< std::vector< double > > >();
        this->record_alpha = false;

        this->dopa_sum = std::vector< std::vector< std::vector< double > > >();
        this->record_dopa_sum = false;

        this->trace = std::vector< std::vector< std::vector< double > > >();
        this->record_trace = false;

        this->condition_0 = std::vector< std::vector< std::vector< double > > >();
        this->record_condition_0 = false;

        this->dopa_mod = std::vector< std::vector< std::vector< double > > >();
        this->record_dopa_mod = false;

        this->delta = std::vector< std::vector< std::vector< double > > >();
        this->record_delta = false;

        this->w = std::vector< std::vector< std::vector< double > > >();
        this->record_w = false;


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder41(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder41 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder41* get_instance(int id) {
        return static_cast<ProjRecorder41*>(getRecorder(id));
    }

    void record() {

        if(this->record_alpha && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            std::vector< std::vector< double > > tmp;
            for(int i=0; i<this->ranks.size(); i++){
                tmp.push_back(std::move(proj41.get_matrix_variable_row<double>(proj41.alpha, this->indices[i])));
            }
            this->alpha.push_back(tmp);
            tmp.clear();
        }

        if(this->record_dopa_sum && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            std::vector< std::vector< double > > tmp;
            for(int i=0; i<this->ranks.size(); i++){
                tmp.push_back(std::move(proj41.get_matrix_variable_row<double>(proj41.dopa_sum, this->indices[i])));
            }
            this->dopa_sum.push_back(tmp);
            tmp.clear();
        }

        if(this->record_trace && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            std::vector< std::vector< double > > tmp;
            for(int i=0; i<this->ranks.size(); i++){
                tmp.push_back(std::move(proj41.get_matrix_variable_row<double>(proj41.trace, this->indices[i])));
            }
            this->trace.push_back(tmp);
            tmp.clear();
        }

        if(this->record_condition_0 && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            std::vector< std::vector< double > > tmp;
            for(int i=0; i<this->ranks.size(); i++){
                tmp.push_back(std::move(proj41.get_matrix_variable_row<double>(proj41.condition_0, this->indices[i])));
            }
            this->condition_0.push_back(tmp);
            tmp.clear();
        }

        if(this->record_dopa_mod && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            std::vector< std::vector< double > > tmp;
            for(int i=0; i<this->ranks.size(); i++){
                tmp.push_back(std::move(proj41.get_matrix_variable_row<double>(proj41.dopa_mod, this->indices[i])));
            }
            this->dopa_mod.push_back(tmp);
            tmp.clear();
        }

        if(this->record_delta && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            std::vector< std::vector< double > > tmp;
            for(int i=0; i<this->ranks.size(); i++){
                tmp.push_back(std::move(proj41.get_matrix_variable_row<double>(proj41.delta, this->indices[i])));
            }
            this->delta.push_back(tmp);
            tmp.clear();
        }

        if(this->record_w && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            std::vector< std::vector< double > > tmp;
            for(int i=0; i<this->ranks.size(); i++){
                tmp.push_back(std::move(proj41.get_matrix_variable_row<double>(proj41.w, this->indices[i])));
            }
            this->w.push_back(tmp);
            tmp.clear();
        }

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor41::clear(): not implemented for openMP paradigm." << std::endl;
    }


    // Local variable alpha
    std::vector< std::vector< std::vector< double > > > alpha ;
    bool record_alpha ;

    // Local variable dopa_sum
    std::vector< std::vector< std::vector< double > > > dopa_sum ;
    bool record_dopa_sum ;

    // Local variable trace
    std::vector< std::vector< std::vector< double > > > trace ;
    bool record_trace ;

    // Local variable condition_0
    std::vector< std::vector< std::vector< double > > > condition_0 ;
    bool record_condition_0 ;

    // Local variable dopa_mod
    std::vector< std::vector< std::vector< double > > > dopa_mod ;
    bool record_dopa_mod ;

    // Local variable delta
    std::vector< std::vector< std::vector< double > > > delta ;
    bool record_delta ;

    // Local variable w
    std::vector< std::vector< std::vector< double > > > w ;
    bool record_w ;

};

class ProjRecorder42 : public Monitor
{
protected:
    ProjRecorder42(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder42 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj42.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder42(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder42 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder42* get_instance(int id) {
        return static_cast<ProjRecorder42*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor42::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder43 : public Monitor
{
protected:
    ProjRecorder43(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder43 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj43.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder43(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder43 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder43* get_instance(int id) {
        return static_cast<ProjRecorder43*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor43::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder44 : public Monitor
{
protected:
    ProjRecorder44(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder44 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj44.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder44(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder44 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder44* get_instance(int id) {
        return static_cast<ProjRecorder44*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor44::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder45 : public Monitor
{
protected:
    ProjRecorder45(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder45 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj45.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder45(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder45 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder45* get_instance(int id) {
        return static_cast<ProjRecorder45*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor45::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder46 : public Monitor
{
protected:
    ProjRecorder46(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder46 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj46.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder46(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder46 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder46* get_instance(int id) {
        return static_cast<ProjRecorder46*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor46::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder47 : public Monitor
{
protected:
    ProjRecorder47(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder47 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj47.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder47(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder47 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder47* get_instance(int id) {
        return static_cast<ProjRecorder47*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor47::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder48 : public Monitor
{
protected:
    ProjRecorder48(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder48 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj48.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder48(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder48 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder48* get_instance(int id) {
        return static_cast<ProjRecorder48*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor48::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder49 : public Monitor
{
protected:
    ProjRecorder49(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder49 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj49.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder49(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder49 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder49* get_instance(int id) {
        return static_cast<ProjRecorder49*>(getRecorder(id));
    }

    void record() {

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor49::clear(): not implemented for openMP paradigm." << std::endl;
    }


};

class ProjRecorder50 : public Monitor
{
protected:
    ProjRecorder50(std::vector<int> ranks, int period, int period_offset, long int offset)
        : Monitor(ranks, period, period_offset, offset)
    {
    #ifdef _DEBUG
        std::cout << "ProjRecorder50 (" << this << ") instantiated." << std::endl;
    #endif
        std::map< int, int > post_indices = std::map< int, int > ();
        auto post_rank = proj50.get_post_rank();

        for(int i=0; i<post_rank.size(); i++){
            post_indices[post_rank[i]] = i;
        }
        for(int i=0; i<this->ranks.size(); i++){
            this->indices.push_back(post_indices[this->ranks[i]]);
        }
        post_indices.clear();

        this->aux = std::vector< std::vector< std::vector< double > > >();
        this->record_aux = false;

        this->delta = std::vector< std::vector< std::vector< double > > >();
        this->record_delta = false;

        this->w = std::vector< std::vector< std::vector< double > > >();
        this->record_w = false;


    };

    std::vector <int> indices;

public:

    static int create_instance(std::vector<int> ranks, int period, int period_offset, long int offset) {
        auto new_recorder = new ProjRecorder50(ranks, period, period_offset, offset);
        auto id = addRecorder(static_cast<Monitor*>(new_recorder));
    #ifdef _DEBUG
        std::cout << "ProjRecorder50 (" << new_recorder << ") received list position (ID) = " << id << std::endl;
    #endif
        return id;
    }

    static ProjRecorder50* get_instance(int id) {
        return static_cast<ProjRecorder50*>(getRecorder(id));
    }

    void record() {

        if(this->record_aux && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            std::vector< std::vector< double > > tmp;
            for(int i=0; i<this->ranks.size(); i++){
                tmp.push_back(std::move(proj50.get_matrix_variable_row<double>(proj50.aux, this->indices[i])));
            }
            this->aux.push_back(tmp);
            tmp.clear();
        }

        if(this->record_delta && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            std::vector< std::vector< double > > tmp;
            for(int i=0; i<this->ranks.size(); i++){
                tmp.push_back(std::move(proj50.get_matrix_variable_row<double>(proj50.delta, this->indices[i])));
            }
            this->delta.push_back(tmp);
            tmp.clear();
        }

        if(this->record_w && ( (t - this->offset_) % this->period_ == this->period_offset_ )){
            std::vector< std::vector< double > > tmp;
            for(int i=0; i<this->ranks.size(); i++){
                tmp.push_back(std::move(proj50.get_matrix_variable_row<double>(proj50.w, this->indices[i])));
            }
            this->w.push_back(tmp);
            tmp.clear();
        }

    };

    void record_targets() { /* nothing to do here */ }
    long int size_in_bytes() {
        std::cout << "ProjMonitor::size_in_bytes(): not implemented for openMP paradigm." << std::endl;
        return 0;
    }

    void clear() {
        std::cout << "PopMonitor50::clear(): not implemented for openMP paradigm." << std::endl;
    }


    // Local variable aux
    std::vector< std::vector< std::vector< double > > > aux ;
    bool record_aux ;

    // Local variable delta
    std::vector< std::vector< std::vector< double > > > delta ;
    bool record_delta ;

    // Local variable w
    std::vector< std::vector< std::vector< double > > > w ;
    bool record_w ;

};

