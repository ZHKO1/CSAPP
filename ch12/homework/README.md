## 12.2
只要进程被终止，内核都会关闭所有打开的文件并释放它们的内存资源
PS：跟waitpid无关

## 12.4
需要将输入参数（代表要读的集合）和输出参数（代表准备好的集合）区分开

## 12.10
一开始有10个写者，然后来了个读者
如果V操作一直在选择重启写者的线程，那就会导致读者饥饿

## 12.14
A. 创建N个元素的数组
B. 数组空间要到全部结束才会被系统释放
PS: 书给出的正确答案是直接传值而不是传指针。优点降低了开销，缺点是假设了指针至少和int一样大，在过去或今后系统可能就不一定了。这里有点鸡蛋挑骨头

## 12.15
B. 会
C. t=1

## 12.19
首先中文版题目第一行就写错了，应该是“因为写者在离开它的临界区”
https://dreamanddead.github.io/CSAPP-3e-Solutions/chapter12/12.19/ 答案可能有问题
正确答案参考 https://zhuanlan.zhihu.com/p/351012714
一个诀窍，题目说的是当写者离开它的临界区的时候
就思考writer还没执行V(&w)时，如果有多个读者，多个写者，分别会卡在什么步骤
然后执行V(&w)，就假设内核坏心眼，就是铁了心卡着读者，这样可以验证答案是否正确

## 12.20
我以为题目的意思是
  当有N个读者正在并发执行时，来了第N+1个读者和一个写者，要如何才能让第N+1个读者或写者等待前N个读者结束再公平竞争机会
然后我做不出来，看了下dreamanddead老兄的答案，他更简单暴力，什么N个读者全都是放屁，一次只能执行一个读者或写者
不知道题目到底是图个啥

## 12.21
TODO
不会做，看别的答案感觉还是不对劲
先放下，看看有没有其他的书给个参考答案。

## 12.22
实际上echoservers.c示例就是答案，所以这题目到底是图个啥

## 12.23
看dreamanddead老兄的意思，如果echoclient在Rio_writen之后不执行Close函数直接exit(0)，服务端就会触发Rio_readlineb error: Connection reset by peer的报错
我这里试了下，确实能重现，但是往往需要echoclient执行几遍才能看到，具体原因不明
还有个问题就是发送的是完整的行，所以这里不确定是不是对应书里提到的发送部分行
假设dreamanddead老兄对题目的理解是对的，那么他给出的解决方法其实就是显式处理问题，而不是靠Rio包内的判断错误逻辑

## 12.25
是线程安全 但不是可重入的

## 12.26
因为没用过gethostbyname，所以懒得做了。
不过可以复习下什么叫加锁-复制技术

## 12.27
参见书里的10.11节

## 12.30
感觉题目质量不行啊，`a<b<c`是什么鬼，看都看不懂

## 12.31
感觉这题应该放在第八章里，而不是这一章

## 12.32
要求对select有更深的了解，看看select是否有关于时间的参数

## 12.33
虽然用线程了，但看起来主线程没法判断多个线程里哪个线程先结束了，不是很优雅

## 12.34
dreamanddead老兄的答案看起来是发挥多核的效果了，线程数量改大是有效果的
那ch12/example/psum-mutex.c 咋就发挥不出来？

## 12.35
跟着dreamanddead老兄用wrk压测
Running 1s test @ http://localhost/
  2 threads and 10 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   793.11us  334.38us   7.93ms   88.57%
    Req/Sec     6.18k     1.01k    9.59k    85.71%
  12914 requests in 1.10s, 22.83MB read
Requests/sec:  11747.74
Transfer/sec:     20.77MB

Running 1s test @ http://localhost/cgi-bin/adder
  2 threads and 10 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency     1.88ms    1.29ms  20.50ms   95.19%
    Req/Sec     2.77k   366.29     3.09k    81.82%
  6058 requests in 1.10s, 1.33MB read
  Socket errors: connect 0, read 6058, write 0, timeout 0
Requests/sec:   5507.91
Transfer/sec:      1.21MB

## 12.36
Running 1s test @ http://localhost/
  2 threads and 10 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   576.52us  154.96us   2.58ms   92.07%
    Req/Sec     8.42k     1.06k    9.62k    63.64%
  18411 requests in 1.10s, 32.55MB read
Requests/sec:  16747.06
Transfer/sec:     29.61MB
比起12.35有优势

Running 1s test @ http://localhost/cgi-bin/adder
  2 threads and 10 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency     6.45ms  794.01us   9.44ms   73.49%
    Req/Sec   770.70     57.00     0.85k    60.00%
  1535 requests in 1.00s, 345.00KB read
  Socket errors: connect 0, read 1535, write 0, timeout 0
Requests/sec:   1534.13
Transfer/sec:    344.80KB
比起12.35反而有性能劣势了，原因是因为这里用Wait来回收处理子进程，影响了效率
PS: 如果不用Wait，Select会报中断错误
虽然感觉用Wait看起来符合场景，但总感觉不太对劲

## 12.37
Running 1s test @ http://localhost/
  2 threads and 10 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   637.68us  177.29us   2.87ms   85.72%
    Req/Sec     7.59k   391.51     8.29k    59.09%
  16596 requests in 1.10s, 29.34MB read
Requests/sec:  15088.95
Transfer/sec:     26.68MB
比起12.35有优势

Running 1s test @ http://localhost/cgi-bin/adder
  2 threads and 10 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency     2.76ms  378.12us   5.53ms   79.97%
    Req/Sec     1.79k    77.82     1.91k    59.09%
  3914 requests in 1.10s, 0.86MB read
  Socket errors: connect 0, read 3914, write 0, timeout 0
Requests/sec:   3558.45
Transfer/sec:    799.67KB
比起12.35反而有性能劣势了，原因不明





