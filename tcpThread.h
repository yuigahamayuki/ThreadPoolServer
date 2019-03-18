#ifndef _TCPTHREAD_H_
#define _TCPTHREAD_H_

#include <deque>
#include <pthread.h>
#include <unistd.h>
class ProcessRequest {
public:
    virtual void process(int connfd) = 0;
};

class Task {
private:
    int connfd;
    ProcessRequest *processRequest;

public:
    Task() = default;
    Task(int _connfd) : connfd(_connfd) {}
    void setConnfd(int _connfd) {connfd = _connfd;}
    int getConnfd() {return connfd;}
    void setProcessMethod(ProcessRequest *_processRequest) {processRequest = _processRequest;}
    void performProcess();
};

class ThreadPool {
private:
    static std::deque<Task*> taskList; // task queue
    static bool shutdown; // flag to close server
    int threadCnt;
    pthread_t *pthread_id;

    static pthread_mutex_t mutex;
    static pthread_cond_t cond;

    static void* threadFunc(void* threadData);
    int createThreads();

public:
    ThreadPool(int _threadCnt = 10);
    int addTask(Task *task);
    int stopAll();
    int getTaskCnt() {return taskList.size();}
};
#endif //_TCPTHREAD_H_
