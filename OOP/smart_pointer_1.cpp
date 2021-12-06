#include <iostream>
#include <memory>

template<typename T>
class Un_Ptr{
    T* un_pointer;
public: 

//CONSTRUCTORS===================================================

//Constructor
    explicit Un_Ptr(T* ptr = nullptr)
        : un_pointer(ptr)
    {
    }

//Move constructor
    Un_Ptr(Un_Ptr<T>&& passed_pointer) noexcept
        : un_pointer(nullptr)
     //or un_pointer(std::move(passed_pointer.un_pointer))
    {
        std::cout << "Created and moved!\n";
        swap(passed_pointer);
    }

//Destructor
    ~Un_Ptr(){
        delete un_pointer;
    }

//OPERATORS======================================================

    Un_Ptr<T>& operator=(Un_Ptr<T>&& Assign) noexcept {
        swap(Assign);
        Assign.un_pointer = nullptr;
        return *this;
    }

    T& operator*() const { return *un_pointer; }
    
    T* operator->() const { return un_pointer; }

    bool operator== (const Un_Ptr<T>& Compare){
        if(this->un_pointer == Compare.un_pointer){
            return true;
        }
        return false;
    }

    bool operator!= (const Un_Ptr<T>& Compare){
        if(this->un_pointer != Compare.un_pointer){
            return true;
        }
        return false;
    }

//METHODS========================================================
    T* get() const { return un_pointer; }

    void swap(Un_Ptr<T>& To_Swap){
        std::swap(this->un_pointer,To_Swap.un_pointer);
    }
};

//===============================================================
//SOME_CHECKS:
int main(){
    int* a = new int(5);
    int* b = new int(5);

    Un_Ptr<int> ptr1(a);
    Un_Ptr<int> ptr2(b);
    Un_Ptr<int> ptr3(new int(50));

    ptr1 = std::move(ptr2);

        std::cout << "ptr1: " << ptr1.get() << std::endl;
        std::cout << "ptr2: " << ptr2.get() << std::endl;
        std::cout << "ptr3: " << ptr3.get() << std::endl;

        std::cout << std::endl << std::endl;

        ptr1.swap(ptr3);

        std::cout << "ptr1: " << ptr1.get() << std::endl;
        std::cout << "ptr3: " << ptr3.get() << std::endl;

    return 0;
}