/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * tris.cpp
 */

#include <iostream>
#include <vector>
#include <utility>
#include <functional>

#include <cstdlib>
#include <ctime>
//using namespace std;

using int_tab_t = std::vector< int >;

//Implementation Functions:
void print_tab(const int_tab_t &tab){
    std::cout << "[ ";
    for (int item : tab)
        std::cout << item << " ";
    std::cout << "] \n" << std::endl;
}

void random_tab(int_tab_t &tab){
    int upper = 10;
    int lower = -10;

    for (int item = 0; item < tab.size(); item++){
        tab[item] = (rand() % (upper - lower + 1)) + lower;
    }
}

void sort_tab_1(int_tab_t &tab){
    int i, j;
    for (i = 0; i < tab.size() - 1; i++){
        for (j = 0; j < tab.size() - i - 1; j++){
            if ( tab[j] >  tab[j + 1]){
                std::swap( tab[j],  tab[j + 1]);
            }
        }
    }
}

bool less(int num_A, int num_B){
    return (num_A < num_B);
}

bool greater(int num_A, int num_B){
    return (num_A > num_B);
}

void sort_tab_2(int_tab_t &tab, bool (*comparation)(int, int) ){
    int i, j;
    for (i = 0; i < tab.size() - 1; i++){
        for (j = 0; j < tab.size() - i - 1; j++){
            if (comparation(tab[j], tab[j + 1])){
                std::swap( tab[j],  tab[j + 1]);
            }
        }
    }
}

void sort_tab_3(int_tab_t &tab, std::function<bool(int, int)> comparation){
    int i, j;
    for (i = 0; i < tab.size() - 1; i++){
        for (j = 0; j < tab.size() - i - 1; j++){
            if (comparation(tab[j], tab[j + 1])){
                std::swap( tab[j],  tab[j + 1]);
            }
        }
    }
}

//Test Functions:
void test_11(){
    std::cout << "*** test_11 ***" << std::endl;
    const int_tab_t tab{ 1, -2, 3, -4, 5, -6 };

    print_tab(tab);
}

void test_12(){
    std::cout << "*** test_12 ***" << std::endl;
    int_tab_t tab{ 1, 2, 3, 4, 5, 6,7, 8, 9, 10};

    random_tab(tab);
    std::cout << "Random Table:"; 
    print_tab(tab);
}

void test_13(){
    std::cout << "*** test_13 ***" << std::endl;
    int_tab_t tab{ 1, 2, 3, 4, 5, 6,7, 8, 9, 10};

    random_tab(tab);
    std::cout << "Random Table:"; 
    print_tab(tab);

    sort_tab_1(tab);
    std::cout << "Ordered Table:"; 
    print_tab(tab);
}

void test_14(){
    std::cout << "*** test_14 ***" << std::endl;
    int_tab_t tab{ 1, 2, 3, 4, 5, 6,7, 8, 9, 10};

    random_tab(tab);
    std::cout << "Random Tab:"; 
    print_tab(tab);

    sort_tab_2(tab, less);
    std::cout << "Decreasing sorting:"; 
    print_tab(tab);

    sort_tab_2(tab, greater);
    std::cout << "Increasing sorting:"; 
    print_tab(tab);
}

void test_15(){
    std::cout << "*** test_15 ***" << std::endl;
    int_tab_t tab{ 1, 2, 3, 4, 5, 6,7, 8, 9, 10};

    random_tab(tab);
    std::cout << "Random Tab:"; 
    print_tab(tab);

    sort_tab_3(tab, [](int num_A, int num_B) { return (num_A < num_B); });
    std::cout << "Decreasing sorting:"; 
    print_tab(tab);

    sort_tab_3(tab, [](int num_A, int num_B) { return (num_A > num_B); });
    std::cout << "Increasing sorting:"; 
    print_tab(tab);
}

//main:
int main()
{
    srand(  time( nullptr ));

    //Calling test functions
    test_11();
    test_12();
    test_13();
    test_14();
    test_15();

    return 0;
}

