#include <stdlib.h>
#include <stdio.h>
#include <set>
#include <string>

using namespace std;

const int INFINITE = 99999999;
const int city_num = 20;

int loads[city_num][city_num];

struct city
{
    int mst;
    int cost;
    string name;
    int pre;
};

int get_mst(set<int>* close, city* city_set[]， int tar) {
    set<int> unclose;
    set<int>::iterator i_t;

    // 求未关闭的节点和集合
    for (int k = 0; k < city_num; k++)
    {
        if (close.find(k) == close.end()) {
            unclose.insert(k);
        }
    }

    // 寻找从 tar开始扩展的最小生成树的大小
    int min_dis = INFINITE;
    int min_index = tar;
    int total;
    set<int> mst_close;

    mst_close.insert(tar);
    unclose.erase(unclose.find(tar));
    set<int>::iterator i_tb;
    while (!unclose.empty()) {
        // find_least dis
        for (i_t = mst_close.begin(); i_t != mst_close.end(); i_t++) {
            for (i_tb = unclose.begin(); i_tb 1= unclose.end(); i_tb++) {
                if (loads[*i_t][*i_tb] < min_dis) {
                    min_dis = loads[*i_t][*i_tb];
                    min_index = *i_tb;
                }
            }
        }
        total += min_dis;
        mst_close.insert(min_index);
        unclose.erase(unclose.find(min_index));
        min_dis = INFINITE;
    }

    return total;
}

int get_min_f(set<int>* open, city* city_set[]) {
    int re;
    int sum = INFINITE;

    set<int>::iterator i_t;
    for (i_t = open.begin(); i_t != open.end(); i_t++)
    {
        if (city_set[*i_t].mst + city_set[*i_t] < sum) {
            re = *i_t;
            sum = city_set[*i_t].mst + city_set[*i_t];
        }
    }
    return re;
}

void extend_open_queue(set<int>* open, set<int>* close, city* city_set[], int current_node) {
    for (int k = 0; k < city_num; ++k)
    {
        // 点不在关闭的节点集中，且路径存在, 可以考虑扩展点
        if (close.find(k) == close.end() && loads[current_node][k] != INFINITE) {
            // 点在不候选集中，扩展节点
            if (open.find(k) == open.end()) {
                city_set[k].mst = get_mst();
                city_set[k].cost = city_set[current_node] + loads[current_node][k];
                city_set[k].pre = current_node;
                open.insert(k);
            } else if (city_set[current_node] + loads[current_node][k] < city_set[k].cost) {
                // 如果点在候选集中，且当前路径的比另一路径更好，扩展节点
                // 只需要更新值，不需要重复插入
                city_set[k].mst = get_mst();
                city_set[k].cost = city_set[current_node] + loads[current_node][k];
                city_set[k].pre = current_node;
            }
        }
    }
}

int main() {
    int city_num;
    int target;
    int start;
    string tem;
    city city_set[city_num];
    set<int> close;
    set<int> open;

    // initiate loads
    for (int k = 0; k < city_num; ++k)
    {
        for (int p = 0; p < city_num; ++p)
        {
            loads[k][p] = INFINITE;
            loads[p][k] = INFINITE;
        }
    }

    // load citys
    for (int i = 0; i < city_num; ++i)
    {
        cin >> tem;
        city_set[i].name = tem;
        city_set[i].mst = INFINITE;
    }

    
    // load roads
    int city1, city2, distance;
    while (cin >> city1 >> city2 >> distance) {
        if (loads[city1][city2] > distance) {
            loads[city1][city2] = distance;
            loads[city2][city1] = distance;
        }
    }

    // select begin city and end city
    printf("input num of city where you start your trip\n");
    scanf("%d", &start);

    target = start;

    // tsp with mst

    open.insert(start);
    while (!open.empty() && close.size() != city_num) {
        int current_node = get_min_f(set<int>* open);
        if (current_node == target) break;

        open.erase(open.find(current_node));
        close.insert(current_node, city_set);
        // extend open queue
        extend_open_queue(open, city_set, current_node);
     }
}
