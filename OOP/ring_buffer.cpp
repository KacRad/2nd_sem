#include <iostream>
#include <array>
#include <iterator>
#include <unistd.h>
#include <stdlib.h>


template<typename T, size_t N>
class RingBuffer{
    private:
    std::array<T, N> ringBufferArray;
    int head = 0;
    int tail = 0;
    int counter = 0;
    int index = 0;
    int incr;
//=============================================================================

    public:
    RingBuffer(){
        std::array<T, N> ringBufferArray;
        initialize();
    }

    RingBuffer(const RingBuffer& Copy){
        ringBufferArray = Copy.ringBufferArray;
        head = Copy.head;
        tail = Copy.tail;
    }

    ~RingBuffer(){}

    void initialize(){
        for(auto &i : ringBufferArray){
            i = 0;
        }
    }

//OPERATOR OVERLOADING=========================================================
    T &operator[](int index){
        return ringBufferArray.at(index);
    }

    bool operator !=(const RingBuffer& rhs) const{
        return !(*this == rhs);
    }

    int operator *(){
        return index;
    }

    RingBuffer operator++(){
        RingBuffer temp;
        temp.incr= incr++;
        return temp;
    }

    RingBuffer operator++(int){
        RingBuffer temp;
        temp.incr = incr++;
        return temp;
    }

    size_t maxSize(){
        return N;
    }

    size_t size(){
        return counter;
    }

    T* begin(){
        return &ringBufferArray.at(0);        
    }

    T* end(){
        return &ringBufferArray[N];
    }


//PUSH / POP METHODS===========================================================
    void push(T elem){
        incrementTailIndex();
        ringBufferArray.at(tail) = elem;
        std::cout << "Added " << elem << " | On index: " << tail << std::endl;
        if(counter <= (N - 1)){ 
            counter++;
        }
        if (counter == N && head == tail){
            incrementHeadIndex();
        }
    }

    T pop(){
        if(!isEmpty()){
            T value = ringBufferArray.at(head);
            ringBufferArray.at(head) = 0;
            incrementHeadIndex();
            if(counter > 0) counter--;
            return value;
        } else {
            std::cout << "Ring Buffer is empty!" << std::endl;
            return 0;
        }
    }

//INCREMENT INDEXES============================================================
    void incrementTailIndex(){
        tail = (tail + 1) % N;
    }

    void incrementHeadIndex(){
        head = (head + 1)% N;
    }

    int getHead(){
        return head;
    }
    int getTail(){
        return tail;
    }

//IS EMPTY / IS FULL METHODS==================================================
    bool isEmpty(){
        if(counter == 0 || head == tail) return true;
        return false;
    }

    bool isFull(){
        if(head == (tail % maxSize) + 1) return true;
        return false;
    }

//PRINT METHODS FOR CHECKING=================================================
    void printTailIndex(){
        std::cout << " | Tail index: " << tail ;
    }
    
    void printHeadIndex(){
        std::cout << "Head index: " << head ;
    }

    void printCounter(){
        std::cout << " | Counter: " << counter << std::endl;
    }
    
    void printData(){
        printHeadIndex();
        printTailIndex();
        printCounter();
        for ( auto& i : ringBufferArray) { std::cout << " | " << i << " | ";}
        std::cout<<std::endl<<std::endl;
    }
};

//=============================================================================
int main(){
    RingBuffer<int, 5> bingRuffer;

    std::cout << "Pushing: " << std::endl;
    bingRuffer.printData();

    for(int i = 1; i < 15; i++){
    bingRuffer.push(i);
    bingRuffer.printData();
    }

    std::cout << "Popping: " << std::endl;
    for(int i = 0; i < 3; i++){
    bingRuffer.pop();
    bingRuffer.printData();
    }

    std::cout << "Ranged for: " << std::endl;
    for(auto& i : bingRuffer){
        std::cout << i << std::endl;
    }

    return 0;
}