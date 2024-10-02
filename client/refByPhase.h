#ifndef REF_BY_PHASE_CXX
#define REF_BY_PHASE_CXX

class refByPhase{

public:
    virtual ~refByPhase(){};
    virtual float getValueFromPhase(float phase) = 0;
};

#endif