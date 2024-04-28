#pragma once


#include <cstdlib>
#include <mutex>
#include <condition_variable>

using namespace std;

namespace pr{

    class Barrier {
        mutable mutex m; 
        int counter; 
        const int max;
        condition_variable cv;

    public :
        Barrier(int max):max(max), counter(0){}

        void done(){        
            unique_lock<mutex> lg(m);
            ++counter;
            if(counter == max){
                cv.notify_all();
            }
        }

        void waitFor(){
            unique_lock<mutex> lg(m);
            while(counter! != max){
                cv.wait(lg);
            }
            
        }

    };

}