#include <iostream>
#include <vector>
#include <memory>

class MyClass {
public:
    MyClass() {
        std::cout << "Constructor called" << std::endl;
    }

    ~MyClass() {
        std::cout << "Destructor called" << std::endl;
    }
};

class Test {
public:
    Test() {
        for (int i = 0; i != 5; i++)
            myVector.emplace_back(std::make_shared<MyClass>());
    }

    ~Test() {
    myVector.clear();
    }

    private:
        std::vector<std::shared_ptr<MyClass>> myVector;

};

int main()
{
        Test test;
        // for (int i = 0; i != 5; i++)
    // myVector.push_back(std::make_shared<MyClass>());
        // std::cout << "Before clearing sharedPtr" << std::endl;
        // sharedPtr.reset();
        // std::cout << "After clearing sharedPtr" << std::endl;
// 
        // std::cout << "Before clearing myVector" << std::endl;
        // myVector.clear();
        // std::cout << "After clearing myVector" << std::endl;

        return 0;
}