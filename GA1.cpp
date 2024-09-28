#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <bitset>
#include <cstring>
#include <algorithm> 
#include <time.h>

#define MAX_POPULATION 1000
#define MAX_EVALUATION 1000
#define CROSSOVER_RATE 0.6
#define MUTATION_RATE 0.01

using namespace std;
/*
initial population
generation
 while eva < eva_max
    selection
    cross over
    mutation
    evaluation
*/

struct population
{
    int capacity;
    int value;
    char * position;
};

bool compare_profit(struct population x, struct population y)
{
    return x.value < y.value;
}
bool compare_cp(struct population x, struct population y)
{
    double x_cp = (float)x.value/x.capacity;
    double y_cp = (float)y.value/y.capacity;
    return x_cp > y_cp;
}
void crossover(struct population & x, struct population & y, string mask, int weight[], int profit[], int num)
{
    //mask =  mask.substr(32-num, 31);
    //reverse(mask.begin(),mask.end());
    
    mask = mask.substr(32-num, 31);
    //cout << mask << endl;
    for(int j=0;j<num;j++)
    {
        if(mask[32-j] == '1')
        {
            if(x.position[j] == '0' && y.position[j] == '1')
            {
                x.capacity += weight[j];
                x.value += profit[j];
                x.position[j] = '1';
                y.capacity -= weight[j];
                y.value -= profit[j];
                y.position[j] = '0';
                //cout << "Crossedover\n";
            }
            else if(x.position[j] == '1' && y.position[j] == '0')
            {
                x.capacity -= weight[j];
                x.value -= profit[j];
                x.position[j] = '0';
                y.capacity += weight[j];
                y.value += profit[j];
                y.position[j] = '1';
                //cout << "Crossedover\n";
            }
        }
    }
   // cout << "end\n";
}

int evaluation(struct population & x, int weight[], int profit[], int capacity, int num)
{
    int count = 0;
    /*int count = 0;
    vector<int> index;
    for(int i = 0;i <num;i++)
    {
        if(x.position[i] == '1')
        {
            count++;
            index.push_back(i);
        }
    }
    srand(time(NULL));*/
    while(x.capacity > capacity)
    {
        //int p = rand()%count;
        //int to_erase = index[p];
        
        int min=999;
        int to_erase;
        for(int i = 0;i<num;i++)
        {
            if(x.position[i]=='1' && profit[i]/weight[i] < min)
            {
                min = profit[i]/weight[i];
                to_erase = i;
            }
        }
        count++;
        x.capacity -= weight[to_erase];
        x.value -= profit[to_erase];
        x.position[to_erase] = '0';
        //index.erase(index.begin()+p);
        //count--;
    }
    return count;
}

int GA(ifstream& data)
{
    
    //ifstream data("dataset/dt01/item.txt");
    //cout << argv[1];
    int num, capacity;
    data >> num >> capacity;
    int weight[num];
    int profit[num];
    int MAX=-1;
    //vector<int> weight;
    //vector<int> profit;
    bitset<32> sol;

    vector <population> s;

    for(int i=0;i<num;i++)
    {
        data >> weight[i] >> profit[i];
        // input the data
    }
    //random_shuffle(&weight[0],&weight[num-1]);
    //random_shuffle(&profit[0], &profit[num-1]);
    int z=pow(2,num);

    /*this can travel from 00000 to 111111 by adding 1
    e.g. 0000 0001 0010 0011 .......
    */
   //generation
    srand(time(NULL));
    for(int i = 0;i < MAX_POPULATION; i++)
    {
        int x = rand()%z;

        bitset<32> current(x);
        string temp = current.to_string();
        temp = temp.substr(31-num+1, 31);
        //cout << temp << endl;
        //reverse(temp.begin(), temp.end());
        struct population t;
        t.capacity = 0;
        t.value = 0;
        char * temp2 = new char[num];
        strcpy(temp2,temp.c_str());
        t.position = temp2;
        int count = 0;

        //store the index of item that is picked to random drop item when excedd capacity
        //vector<int> picked_inedex; 

        for(int j = 0;j<num;j++)
        {
            if(temp[j] == '1')
            {
                t.value +=  profit[j];
                t.capacity += weight[j];
                //count++;
                //picked_inedex.push_back(j);
            }
        }
        
        s.push_back(t);
    }
    /*
    for(int i = 0; i<MAX_POPULATION;i++)
    {
        for(int j = 0;j<num;j++)
            cout << s[i].position[j];
        cout << endl;
    }
    */
   /*
    for(int i = 0;i<MAX_POPULATION;i++)
    {
        if(s[i].capacity > capacity)
            evaluation(s[i], weight, profit, capacity,num);
    }
    */
   /*
    for(int i = 0; i<MAX_POPULATION;i++)
    {
        for(int j = 0;j<num;j++)
            cout << s[i].position[j];
        cout << endl;
    }
    */
    /*
        while(t.capacity > capacity)
        {
            int index = rand()%count;
            t.capacity -= weight[index];
            t.value -= profit[index];
            t.position[index] = '0';
            picked_inedex.erase(picked_inedex.begin()+index);
        }*/
    
    int eva = 0;
    int population_size = s.size();
    int tournament_size = population_size/5;
    while (eva < MAX_EVALUATION)
    {
        //cout << "Selection\n";
        //selection
        //random_shuffle(s.begin(),s.end());
        //record the selected data
        vector<population> selected;

        for(int i = 0; i<tournament_size; i++)
        {
            int index_to_select = rand()%s.size();
            int second_index_to_select = rand()%s.size();
            //cout << index_to_select << endl;
            if(compare_cp(s[index_to_select],s[second_index_to_select]))
            {
                selected.push_back(s[index_to_select]);
                s.erase(s.begin()+index_to_select);
            }
            else
            {
                selected.push_back(s[second_index_to_select]);
                s.erase(s.begin()+second_index_to_select);
            }
            
            //cout << "Sucessful erase\n";
        }

        // Now the selected generation is in the vector selected

        //Crossover
        
        
        sort(selected.begin(),selected.end(),compare_cp);
        for(int i = 0; i<tournament_size-1;i = i+2)
        {
            double p = ((double) rand() / (RAND_MAX));
            if(p <= CROSSOVER_RATE)
            {
                int random_position = rand()% z;
                bitset<32 > choose(random_position);
                
                string mask = choose.to_string();
                
                //cout << mask << endl;
                //mask = "1111100000";
                crossover(selected[i], selected[i+1], mask,weight,profit, num);
            }
        }
        s.insert(s.end(),selected.begin(),selected.end());

        //mutation
        for(int i = 0; i<s.size();i++)
        {
            double p = ((double) rand() / (RAND_MAX));
            if(p>=MUTATION_RATE)
            {
                int index = rand()%num;
                if(s[i].position[index] == '1')
                {
                    s[i].capacity -= weight[index];
                    s[i].value -= profit[index];
                    s[i].position[index] = '0';
                }
                else if(s[i].position[index] == '0')
                {
                    s[i].capacity += weight[index];
                    s[i].value += profit[index];
                    s[i].position[index] = '1';
                }
            }
        }

        //evaluation
        for(int i = 0;i<MAX_POPULATION;i++)
        {
            if(s[i].capacity > capacity)
                eva=eva+evaluation(s[i], weight, profit, capacity,num);
        }
        
    }
    
    sort(s.begin(),s.end(),compare_profit);
    /*
    for(int i = 0; i<s.size();i++)
        cout << s[i].value << endl;
    */
    for(int i = 0; i<num;i++)
    {
        cout << s[MAX_POPULATION-1].position[i];
    }
    cout << endl;
    return s[MAX_POPULATION-1].value;
    
}

int main(int argc,char **argv)
{
    
    long sum=0;
    
    for(int i = 0; i<30;i++)
    {
        ifstream data("dataset/dt01/item.txt");
        int temp = GA(data);
        cout << temp << endl;
        sum += temp;
    }
    cout << sum/30<< endl;
    
   //ifstream data(argv[1]);
   //ifstream data("dataset/dt03/item.txt");
   //cout << GA(data) << endl;
   //cout << GA(data) << endl;
}
