#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <random>

#include "Individual.hpp"


using namespace std;

double f = 0.5;
double cr = 0.7;

vector<Individual> population;

Individual mutate(int n);
Individual crossover(Individual donor_vector,int n);
bool compare(Individual a,Individual b);

int main(int argc, const char * argv[])
{
    for(int i=0;i<1000;i++) //population size
    {
        Individual t;
        population.push_back(t);
    }
    
    cout<<"iteration: ";
    int c = 0;
    for(int j=0;j<1000;j++) //迭代次數
    {
        cout<<++c<<" ";
        
        for(int i=0;i<population.size();i++)
        {
            Individual donor_vector = mutate(i); //產生捐獻向量
            Individual trial_vector = crossover(donor_vector,i); //產生試驗向量
            
            if(population[i].get_fitness() > trial_vector.get_fitness()) //selection
            {
                population.erase(population.begin()+i);
                population.push_back(trial_vector);
            }
        }
    }
    
    sort(population.begin(), population.end(), compare);
    
    cout<<endl<<endl;
    
    population[0].show_x();
    population[0].show_fitness();
    
    cout<<endl;
    
    return 0;
}


Individual mutate(int n)
{
    srand((unsigned)time(NULL));
 
    int x1,x2,x3; //隨機取三個與target vector不同的vector
    do{ x1 = rand()%population.size(); }while(x1 == n);
    do{ x2 = rand()%population.size(); }while(x2 == n || x2 == x1);
    do{ x3 = rand()%population.size(); }while(x3 == n || x3 == x1 || x3 == x2);
    
    Individual donor_vector;
    for(int j=0;j<Individual::size;j++)
    {
        donor_vector.x[j] = population[x1].x[j] + f * ( population[x2].x[j] - population[x3].x[j] );
    }
    
    return donor_vector; //變異產生捐贈向量
        
}
    
Individual crossover(Individual donor_vector, int n)
{
    random_device rd; // 種子產生器
    mt19937 gen = mt19937(rd()); //使用mt19937引擎
    uniform_real_distribution<> dis(0, 1); //使用平均分佈
    auto randfun = bind(dis, gen); //將引擎和分佈綁在一起變成新函數 randfun
    
    Individual trial_vector;
    for(int j=0;j<Individual::size;j++)
    {
        double t = randfun();
        
        if(t <= cr)
        {
            trial_vector.x[j] = donor_vector.x[j];
        }
        else
        {
            trial_vector.x[j] = population[n].x[j];
        }
    }
    
    return trial_vector; //交配產生試驗向量
    
}

bool compare(Individual a, Individual b)
{
    if(a.get_fitness() < b.get_fitness()) return 1;
    else return 0;
}

