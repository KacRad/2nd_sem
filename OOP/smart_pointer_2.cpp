#include <iostream>
#include <memory>

//REFERENCE_COUNTER_CLASS========================================

class Reference_Counter{
private:
    uint32_t counter;
public:
    Reference_Counter()
        : counter(0) {}
    
    void operator++()       { counter++; }
    void operator++(int)    { counter++; }

    void operator--()       { counter--; }
    void operator--(int)    { counter--; }

    uint32_t get() { return counter; }
    
};

//SHARED_POINTER_CLASS===========================================

template<typename T>
class Sh_Ptr{
    T* sh_pointer;
    Reference_Counter* counter;
public:

//CONSTRUCTORS===================================================

//Constructor
    explicit Sh_Ptr(T* ptr = nullptr)
        : sh_pointer(ptr), counter(new Reference_Counter())
    {
        if(ptr) (*counter)++;
    }
 
//Copy constructor
    Sh_Ptr(const Sh_Ptr<T>& Copy)
    {
        sh_pointer = Copy.sh_pointer;
        counter = Copy.counter;
        (*counter)++;
    }

//Move constructor
    Sh_Ptr(Sh_Ptr<T>&& passed_pointer) noexcept
        : sh_pointer(nullptr)
     //or un_pointer(std::move(passed_pointer.sh_pointer))
    {
        std::cout << "Created and moved!\n";
        swap(passed_pointer);
    }

//Destructor
    ~Sh_Ptr(){
        *counter--;
        if(counter == 0) delete sh_pointer;
    }

//OPERATORS======================================================

    Sh_Ptr<T>& operator=(Sh_Ptr<T>&& Assign) noexcept {
        this->sh_pointer = Assign.sh_pointer;
        return *this;
    }

    T& operator*() const { return *sh_pointer; }
    
    T* operator->() const { return sh_pointer; }

    bool operator== (const Sh_Ptr<T>& Compare){
        if(this->sh_pointer == Compare.sh_pointer){
            return true;
        }
        return false;
    }

    bool operator!= (const Sh_Ptr<T>& Compare){
        if(this->sh_pointer != Compare.sh_pointer){
            return true;
        }
        return false;
    }

//METHODS========================================================
    T* get() const { return sh_pointer; }

    void swap(Sh_Ptr<T>& To_Swap){
        std::swap(sh_pointer, To_Swap.sh_pointer);
        std::swap(counter, To_Swap.counter);
    }

    uint32_t get_counter() const { return counter->get(); }

};

//===============================================================
//SOME_CHECKS
int main(){
    int* a = new int(5);
    int* b = new int(5);

    Sh_Ptr<int> ptr1(a);
    Sh_Ptr<int> ptr2 = ptr1;
    Sh_Ptr<int> ptr3(ptr2);

    ptr1 = std::move(ptr2);

    std::cout << "ptr1: " << ptr1.get() << std::endl;
    std::cout << "ptr2: " << ptr2.get() << std::endl;
    std::cout << "ptr3: " << ptr3.get() << std::endl;

    std::cout << std::endl << std::endl;

    ptr1.swap(ptr3);

    std::cout << "ptr1: " << ptr1.get() << std::endl;
    std::cout << "ptr3: " << ptr3.get() << std::endl;

    std::cout << std::endl << std::endl;

    std::cout << "ptr1: " << ptr1.get_counter() << std::endl;
    std::cout << "ptr2: " << ptr2.get_counter() << std::endl;
    std::cout << "ptr3: " << ptr3.get_counter() << std::endl;

    return 0;
}