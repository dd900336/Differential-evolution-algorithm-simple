#ifndef Individual_hpp
#define Individual_hpp

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <random>

using namespace std;

class Individual //個體
{
public:
    Individual(); //建構子
    void show_x() { for(int i=0;i<size;i++) { cout<<x[i]<<" "; } cout<<endl; }
    void show_fitness() { cout<<fitness_fun(x)<<endl; }
    double get_fitness() { return fitness_fun(x); }
    
    const static int size = 5; //公式參數數量
    vector<double> x; //參數陣列
    
private:
    static double fitness_fun(vector<double> v); //fitness function
};

#endif /* Individual_hpp */
