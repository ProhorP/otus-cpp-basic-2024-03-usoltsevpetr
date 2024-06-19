//
// Created by user on 6/2/24.
//
#include "MyVector.h"
#include "MyForvardList.h"
#include "MyList.h"

int main() {
//        MyVector v1;
//    MyForvardList v1;
    MyList v1;
    for (int i = 1; i < 11; ++i) {
        v1.push_back(i);
    }
//    MyVector v2 = std::move(v1);
//    MyForvardList v2 = std::move(v1);
    MyList v2 = std::move(v1);
    std::cout << v2 << std::endl;
    v2.insert(0, 5);
    std::cout << v2 << std::endl;
    v2.erase(0);
    std::cout << v2 << std::endl;
}
