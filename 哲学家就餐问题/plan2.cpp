/*
 * plan2 : 用一个数组state 记录每一位哲学家在 进餐， 思考， 还是饥饿的状态， 只有在两个邻居都没有进餐时才可以进入进餐状态。
 */

#define N 5  //哲学家个数
#define LEFT (i + N - 1) % N  // i 的左边邻居编号
#define RIGHT (i + 1) % N    // i 的右边邻居编号

#define THINKING 0 // 思考状态
#define HUNGRY 1 // 饥饿状态
#define EATING 2 // 进餐状态

int state[N];   // 数组记录每个哲学家的状态

semaphore s[5];  // 每个哲学家一个信号量， 初值为0
semaphore mutex; // 互斥信号量， 初值为 1

void test( int i ){        // i 为哲学家编号 0 - 4
    // 如果 i 左边和右边的哲学家都不是进餐状态， 把 i 号哲学家标记为进餐状态
    if( state[i] == HUNGRY &&
        state[LEFT] != EATING &&
        state[RIGHT] != EATING){
        state[i] = EATING; //两把叉子到手， 进餐状态
        V(s[i]) ;     //通知第 i哲学家可以进餐
    }
}

//功能： 要么拿到两把叉子，要么阻塞起来
void take_forks( int i ){    // i 为哲学家编号 0 - 4
    P(mutex);   // 进入临界区
    state[i] = HUNGRY; // 标记哲学家属于饥饿状态
    test(i);  // 尝试获取两把叉子
    V(mutex); // 离开临界区
    P(s[i])  // 没有叉子则阻塞， 有叉子则继续正常执行
}

// 功能： 把两把叉子返回原处， 并在需要的时候， 去唤醒左邻右舍
void put_forks( int i ){     // i 为哲学家的编号 0 - 4
    P(mutex) ;          // 进入临界区
    state[i] = THINKING;
    test(LEFT);        // 检查左边的左邻右舍是否在进餐， 没有则唤醒
    test(RIGHT);   // 检查右边的左邻右舍是否在进餐， 没有则唤醒
    V(mutex); // 离开临界区
}

// 哲学家主代码
void smart_people( int i ) {   // i 为哲学家编号
     while(true){
         think(); // 思考
         take_forks(i) ; // 准备拿叉子去吃饭
         eat();
         put_forks(i); // 吃完放回叉子
     }
}

