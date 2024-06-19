//
// Created by user on 6/2/24.
//
#include "MyForvardList.hpp"
#include "MyList.hpp"
#include "MyVector.h"

int main() {
//        MyVector v1;
    MyForvardList<int> v1;
//    MyList<int> v1;
    for (int i = 0; i < 10; ++i) {
        v1.push_back(i);
    }
//    MyVector v2 = std::move(v1);
    MyForvardList v2 = std::move(v1);
//    MyList v2 = std::move(v1);
    std::cout << v2 << std::endl;

    std::cout << v2.size() << std::endl;

    //т.к. после удаления идет смещение массива, то позиция удаления для пятого и 7-го элементов будет
    //смещена на 1 для 5-го и на 2 для 7-го элементов
    v2.erase(2);
    v2.erase(3);
    v2.erase(4);
    std::cout << v2 << std::endl;

    v2.insert(0, 10);
    std::cout << v2 << std::endl;

    v2.insert(v2.size()/2, 20);
    std::cout << v2 << std::endl;

    v2.push_back(30);
    std::cout << v2 << std::endl;

    std::cout << v2[0] << std::endl;
}
