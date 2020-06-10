#include "Individual.hpp"


Individual::Individual() //建構子
{
    for(int i=0;i<size;i++)
    {
        double min = -30;
        double max = 30;
        
        random_device rd; // 種子產生器
        mt19937 gen = mt19937(rd()); //使用mt19937引擎
        uniform_real_distribution<> dis(min, max); //使用平均分佈
        auto randfun = bind(dis, gen); //將引擎和分佈綁在一起變成新函數 randfun
    
        x.push_back(randfun());
    }
    
}


double Individual::fitness_fun(vector<double> v) //fitness function，為static function
{
    double sum = 0;
    for(int i=0;i<v.size();i++) { sum += pow(v[i],2); }
    double s1 = -0.2 * sqrt(sum/v.size());
    
    sum = 0;
    for(int i=0;i<v.size();i++) { sum += cos(2*3.1415926*v[i]); }
    double s2 = sum/v.size();
    
    return 20+exp(1)-20*exp(s1)-exp(s2);
}
