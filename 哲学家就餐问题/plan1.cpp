/*
 * 既要避免只有一个哲学家就餐，又要避免出现死锁。
 * 计划： 偶数哲学家先拿左边再拿右边， 奇数哲学家先拿右边再拿左边
 */

#define N 5             // 哲学家个数
semaphore fork[5]       // 每个叉子一个信号量， 初值为 1
void smart_people(int i ){                  //i 为哲学家编号
    while(true){
        think();         // 哲学家思考
        if( i % 2 == 0){
            P(fork[i]);  // 去拿左边的叉子
            P(fork[(i + 1) % N ])    // 去拿右边的叉子
        }
        else{
            P(fork[(i + 1) % N])  // 去拿右边的叉子
            P(fork[i]);         //去拿左边的叉子
        }

        eat();              // 哲学家就餐

        V(fork[i]) ;        // 放下左边的叉子
        V(fork[(i+1) % N]); // 放下右边的叉子
    }
}