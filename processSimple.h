#include "tcpThread.h"

class ProcessSimple : public ProcessRequest {
public:
    void process(int connfd) override;
};
