// 条件变量实现生产者消费者模型

#include<iostream>
#include<thread>
#include<condition_variable>
#include<deque>
using namespace std;

const int ConsumeSize = 4;
const int ProduceSize = 4;
const int DataSize = 10;
mutex mtx;
condition_variable cv;
deque<int> data;
int num = 0;

void ProduceThread(int n ){
    while(1) {
        unique_lock<mutex> lk(mtx);
        cv.wait(lk,[] {return data.size() < DataSize;});
        data.push_back(num);
        num ++;
        cout << "Producethread: " << n << " producedata: " << num-- << "data size: " << data.size() << endl;
        cv.notify_all();
    }
}

void ConsumeThread(int n){
    while (1){
        unique_lock<mutex> lk(mtx);
        cv.wait(lk,[] {return data.size() > 0; });
        int ans  = 0;
        ans  = data.front();
        data.pop_front();
        cout << "\tConsumethread: " << n << " consume data: " << ans << " data size: " << data.size() << endl;
    }
}

int main(){
    thread Producethreads[ProduceSize];
    thread Consumethreads[ConsumeSize];

    for(int i = 0 ; i < ProduceSize ; i ++){
        Producethreads[i] = thread(ProduceThread, i);
    }

    for(int i = 0 ; i < ConsumeSize ; i ++){
        Consumethreads[i] = thread(ConsumeThread, i);
    }

    for(auto& t : Producethreads){
        t .join();
    }

    for(auto& t : Consumethreads){
        t.join();
    }
    return 0;
}