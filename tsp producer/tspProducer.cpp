#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <set>

using namespace std;

const int Matrix_size = 1000;
const int City_num = 20;
const int INFINETE = 9999999;

struct  City
{
    // index, 0 ~ (Matrix_size-1)
    int x;
    int y;
    // city name
    string name;
};

int main() {
    int k, p;
    set<int> covered_loc;

    // city set
    City city_set[City_num];

    // roads set
    int roads[City_num][City_num];

    for (int i = 0; i < City_num; ++i)
    {
        for (int k = 0; k < City_num; ++k)
        {
            roads[i][k] = INFINETE;
        }
    }

    // set up location
    int tempa, tempb;
    int hash_num;
    char temS[7] = "city"; 
    for (k = 0; k < City_num; ++k)
    {
        while (1) {
            tempa = rand()%Matrix_size;
            tempb = rand()%Matrix_size;
            hash_num = tempa*Matrix_size + tempb;
            if (covered_loc.find(hash_num) == covered_loc.end()) {
                covered_loc.insert(hash_num);
                city_set[k].x = tempa;
                city_set[k].y = tempb;
                cin >> city_set[k].name;
                break;
            }
        }
    }
    printf("establish roads\n");
    printf("city1 city2 distance\n");
    // establish roads
    int rate;
    for (int k = 0; k < City_num; ++k)
    {
        for (int p = k+1; p < City_num; ++p)
        {
            rate = rand()%8;
            if (rate == 0 && roads[k][p] == INFINETE) {
                roads[k][p] = sqrt(pow(city_set[k].x - city_set[p].x, 2)+pow(city_set[k].y - city_set[p].y, 2));
                roads[p][k] = roads[k][p];
                printf("%d %d %d\n", k, p, roads[k][p]);
            }
        }
    }
    return 0;
}
