#include "tcpThread.h"

class ProcessHttp : public ProcessRequest {
public:
    void process(int connfd) override;
};
