#include "tcpThread.h"
#include <iostream>
void Task::performProcess()
{
    processRequest->process(connfd);
}

std::deque<Task*> ThreadPool::taskList;
bool ThreadPool::shutdown = false;
pthread_mutex_t ThreadPool::mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ThreadPool::cond = PTHREAD_COND_INITIALIZER;

ThreadPool::ThreadPool(int _threadCnt) : threadCnt(_threadCnt)
{
	createThreads();
}

int ThreadPool::createThreads()
{
    pthread_id = new pthread_t[threadCnt];
    for (int i = 0; i < threadCnt; ++i)
    {
        pthread_create(&pthread_id[i], NULL, threadFunc, NULL);
    }

    return 0;
}

void* ThreadPool::threadFunc(void *threadData)
{
    pthread_t tid = pthread_self();
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while (taskList.size() == 0 && !shutdown)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        
        if (shutdown)
        {
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }

	    std::cout << "thread " << tid << " is serving" << std::endl;//debug
        Task* task = taskList.front();
	    //std::cout << "task address before: " << taskList.front() << std::endl;//debug
	    //std::cout << "task size before: " << taskList.size() << std::endl;//debug
        taskList.pop_front();
	    //std::cout << "task address after: " << taskList.front() << std::endl;//debug
	    //std::cout << "task size after: " << taskList.size() << std::endl;//debug
        pthread_mutex_unlock(&mutex);

	    //std::cout << "connfd before: " << task->getConnfd() << std::endl;//debug
        task->performProcess();
	    close(task->getConnfd());
	    //std::cout << "connfd after: " << task->getConnfd() << std::endl;//debug
	    std::cout << std::endl;
    }
}

int ThreadPool::addTask(Task *task)
{
    pthread_mutex_lock(&mutex);
    taskList.push_back(task);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return 0;
}

int ThreadPool::stopAll()
{
    if (shutdown)
    {
        return -1;  // avoid re-execute
    }

    shutdown = true;
    pthread_cond_broadcast(&cond);

    for (int i = 0; i < threadCnt; ++i)
    {
        pthread_join(pthread_id[i], NULL);
    }

    delete[] pthread_id;
    pthread_id = NULL;

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
