// 最陡爬山法

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <time.h>

using namespace std;

const int QUEEN_NUM = 8;
const int INFINITE = 9999999;

int map_[QUEEN_NUM];

// 被占用的行
int row_cover[QUEEN_NUM];

// 被占用的斜线
int up_[QUEEN_NUM*2-1];
int down_[QUEEN_NUM*2-1];
int current_v;

int cal_multiplicative(int k) {
    int re = 1;
    if (k == 1) return 0;
    while (k) {
        re *= k;
        k--;
    }
    return re/2;
}

int cal_total_conflict() {
    int row_con = 0;
    int up_con = 0;
    int down_con = 0;
    int total = 0;
    // initial
    for (int i = 0; i < QUEEN_NUM; ++i) {row_cover[i] = 0;}

    for (int i = 0; i < QUEEN_NUM*2-1; ++i)
    {
        up_[i] = 0;
        down_[i] = 0;
    }

    for (int i = 0; i < QUEEN_NUM; ++i)
    {
        row_cover[map_[i]]++;
        up_[i+map_[i]]++;
        down_[i-map_[i]+QUEEN_NUM-1]++;
    }


    for (int i = 0; i < QUEEN_NUM; ++i) {
        total += cal_multiplicative(row_cover[i]);
    }

    for (int i = 0; i < QUEEN_NUM*2-1; ++i)
    {
        total += cal_multiplicative(up_[i]);
        total += cal_multiplicative(down_[i]);
    }
    return total;
}

void initiate() {
    // 生成随机初始状态
    srand(time(NULL));
    for (int i = 0; i < QUEEN_NUM; ++i)
    {
        // 对于每一列，随机在一行放置一个皇后
        map_[i] = rand()%QUEEN_NUM;
    }
}

// 这里使用int存储所有列的皇后位置，注意当皇后比较多时int是不适用的，需要修改的
int map_to_int() {
    int re = 0;
    for (int i = 0; i < QUEEN_NUM; ++i)
    {
        re = re*10+map_[i];
    }
    return re;
}

// 复制节点
void equals_node(int b) {
    for (int i = 0; i < QUEEN_NUM; ++i)
    {
        map_[QUEEN_NUM-i-1] = b%10;
        b /= 10;
    }
}

pair<int, int> get_successor() {
    multimap<int, int> candidate;

    // 应当是小于等于该当前值的节点才能成为候选
    int min = current_v;
    // 遍历每列
    for (int i = 0; i < QUEEN_NUM; ++i)
    {
        // 移动这一列的皇后到第k行上去
        for (int k = 0; k < QUEEN_NUM; ++k)
        {   
            // 不移动到原地
            if (k != map_[i]) {
                int tem = map_[i];
                int tem_v;
                int tem_state;
                map_[i] = k;

                tem_v = cal_total_conflict();
                if (tem_v < min) {
                    // 如果出现比所有候选都要小的值，那么清空候选，这样可以降低后面插入的复杂度
                    tem_state = map_to_int();
                    candidate.clear();
                    candidate.insert(pair<int,int>(tem_v, tem_state));
                    min = tem_v;
                } else if (tem_v == min) {
                    // 与候选中的（最小值）相等就直接插入
                    candidate.insert(pair<int,int>(tem_v,tem_state));
                } else {}

                map_[i] = tem;       // 恢复原来的值
            }
        }
    }

    // 得到的候选都是最小值，从这里面随机取一个返回
    int size = candidate.size();
    if (size == 0) {
        // 找不到小于等于当前值的节点就返回一个无限大
        candidate.insert(pair<int, int>(INFINITE, 1));
        size = candidate.size();
    }

    int index = rand()%size;
    multimap<int, int>::iterator i_t =candidate.begin();
    for (int i = 0; i < index; ++i) i_t++;

    return *i_t;
}

bool hill_climbing() {
    initiate();
    current_v = cal_total_conflict();
    //printf("first: %d %d\n",  current_v, map_to_int());
    pair<int, int> next;
    bool flag = 1;

    // 允许侧向移动side_move次
    int side_move = 100;
    while (flag) {
        next = get_successor();
        //printf("next: %d %d\n", next.first, next.second);
        if (next.first == current_v) {
            // 水平移动
            if (side_move) {
                side_move--;
                equals_node(next.second);
                current_v = cal_total_conflict();
            } else {
                flag = 0;
                break;
            }
        } else if (next.first < current_v) {
            equals_node(next.second);
            current_v = cal_total_conflict();
            if (next.first == 0) {
                break;
            }
        } else {
            // 得到一个代价更大的数说明到达山顶，gg
            flag = 0;
            break;
        }
    }
    if (flag == 0) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    int fail_time = 0;
    int test_time = 100000;
    int k = test_time;

    while (k) {
        if (!hill_climbing()) {
            //printf("fail!\n");
            fail_time++;
        } else {
            //printf("success!\n");
        }
        k--;
    }
    printf("fail-times: %d\n", fail_time);
    printf("test_time: %d\n", test_time);
    return 0;
}
