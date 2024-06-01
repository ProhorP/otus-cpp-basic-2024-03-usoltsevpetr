//
// Created by user on 6/2/24.
//
#include "MyVector.h"

int main(){
    MyVector v;
    for (int i = 1; i < 11; ++i) {
        v.push_back(i);
    }
    std::cout << v << std::endl;

}
