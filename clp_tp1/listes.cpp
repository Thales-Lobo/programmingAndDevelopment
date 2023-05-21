/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * listes.cpp
 */

#include <iostream>
#include <forward_list>
#include <functional>
#include <limits>

#include <cstdlib>
#include <ctime>

using int_list_t = std::forward_list< int >;
using int_list_iter_t = int_list_t::const_iterator;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Implementation Functions:
int random_number(int lower, int upper)
{
    return((rand() % (upper - lower + 1)) + lower);
}

int_list_t random_list(unsigned int size){
    int_list_t list;

    for(int i = 0; i < size; i++){
        list.push_front(random_number(0, 99)); 
    }
    return list;
}

void print_list(const int_list_t &list){
    std::cout << "( ";

    for (int item : list)
        std::cout << item << " ";
    std::cout << ") \n" << std::endl;
}

int_list_t map_iter(const int_list_t &list, std::function<int(int)> func){
    int_list_t new_list;
    
    for(auto item : list){
        new_list.push_front(func(item));
    }
    return new_list;
}

int_list_t filter_iter(const int_list_t &list, std::function<bool(int)> func){
    int_list_t new_list;
    
    for(auto item : list){
        if(func(item)){
            new_list.push_front(item);
        }
    }
    return new_list;
}

int reduce(const int_list_t &list, int init, std::function<int(int, int)> func){
    int acc = init;
    for(auto item : list){
        acc = func(acc, item); //acc = func(func(acc, item(-2)), item(-1))
    }
    return acc;
}

int fold_left_aux(int_list_iter_t it, int_list_iter_t it_end, int init, std::function<int(int, int)> func){
    if(it == it_end){
        return init;
    }
    else{
        init = func(init, *it);
        init = fold_left_aux(std::next(it), it_end, init, func);
    }
    return init;
}

int fold_left(const int_list_t &list, int init, std::function<int(int, int)> func){
    int_list_iter_t it = list.cbegin();
    int_list_iter_t it_end = list.cend();

    return fold_left_aux(it, it_end, init, func);
}

int_list_t map_aux(int_list_iter_t it, int_list_iter_t it_end, std::function<int(int)> func){
    int_list_t new_list;
    
    if(it == it_end){
        return new_list;
    }
    else{
        new_list = map_aux(std::next(it), it_end, func);
        new_list.push_front(func(*it));
    }
    return new_list;
}

int_list_t map(const int_list_t &list, std::function<int(int)> func){
    int_list_iter_t it = list.cbegin();
    int_list_iter_t it_end = list.cend();

    return map_aux(it, it_end, func);
}

int_list_t filter_aux(int_list_iter_t it, int_list_iter_t it_end, std::function<bool(int)> func){
    int_list_t new_list;
    if(it == it_end){
        return new_list;
    }
    else{
        new_list = filter_aux(std::next(it), it_end, func);
            if(func(*it)){
                new_list.push_front(*it);
            }
    }
    return new_list;
}

int_list_t filter(const int_list_t &list, std::function<bool(int)> func){
    int_list_iter_t it = list.cbegin();
    int_list_iter_t it_end = list.cend();

    return filter_aux(it, it_end, func);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Test Functions:
void test_21(){
    std::cout << "*** test_21 ***" << std::endl;

    const int_list_t list{random_list(10)};
    std::cout << "Random List:"; 
    print_list(list);
}

void test_22(){
    std::cout << "*** test_22 ***" << std::endl;

    const int_list_t list{random_list(10)};
    std::cout << "Random List:"; 
    print_list(list);

    int_list_t map_list{map_iter(list, [](int item){return 3*item;})};
    std::cout << "Mapped List:"; 
    print_list(map_list);
}

void test_23(){
    std::cout << "*** test_23 ***" << std::endl;

    const int_list_t list{random_list(10)};
    std::cout << "Random List:"; 
    print_list(list);

    int_list_t map_list{map_iter(list, [](int item){return 3*item;})};
    std::cout << "Mapped List:"; 
    print_list(map_list);

    int_list_t filter_list{filter_iter(map_list, [](int item){return (item%2 == 0);})};
    std::cout << "Filtered List:"; 
    print_list(filter_list);
}

void test_24(){
    std::cout << "*** test_24 ***" << std::endl;

    const int_list_t list{random_list(10)};
    std::cout << "Random List:"; 
    print_list(list);

    int rand_number = random_number(1, 5);
    std::cout << "Random Number:" << rand_number << std::endl; 
    int_list_t map_list{map_iter(list, [rand_number](int item){return (rand_number*item);})};
    std::cout << "Mapped List:"; 
    print_list(map_list);

    int_list_t filter_list{filter_iter(map_list, [](int item){return (item%2 == 0);})};
    std::cout << "Filtered List:"; 
    print_list(filter_list);
}

void test_25(){
    std::cout << "*** test_25 ***" << std::endl;

    const int_list_t list{random_list(10)};
    std::cout << "Random List:"; 
    print_list(list);

    int max_number = reduce(list, std::numeric_limits<short>::min(), [](int item_A, int item_B){return std::max(item_A, item_B);});
    int min_number = reduce(list, std::numeric_limits<short>::max(), [](int item_A, int item_B){return std::min(item_A, item_B);});
    std::cout << "Max Number: "<< max_number << std::endl;
    std::cout << "Min Number: "<< min_number << std::endl;
    std::cout << " " << std::endl;
}

void test_31(){
    std::cout << "*** test_31 ***" << std::endl;

    const int_list_t list{random_list(10)};
    std::cout << "Random List:"; 
    print_list(list);


    int max_number = fold_left(list, std::numeric_limits<short>::min(), [](int item_A, int item_B){return std::max(item_A, item_B);});
    int min_number = fold_left(list, std::numeric_limits<short>::max(), [](int item_A, int item_B){return std::min(item_A, item_B);});
    std::cout << "Max Number: "<< max_number << std::endl;
    std::cout << "Min Number: "<< min_number << std::endl;
    std::cout << " " << std::endl;
}

void test_32(){
    std::cout << "*** test_32 ***" << std::endl;

    const int_list_t list{random_list(10)};
    std::cout << "Random List:"; 
    print_list(list);

    int rand_number = random_number(1, 5);
    std::cout << "Random Number:" << rand_number << std::endl; 
    int_list_t map_list{map(list, [rand_number](int item){return (rand_number*item);})};
    std::cout << "Mapped List:"; 
    print_list(map_list);

    int_list_t filter_list{filter(map_list, [](int item){return (item%2 == 0);})};
    std::cout << "Filtered List:"; 
    print_list(filter_list);
}

void test_41(){
    std::cout << "*** test_41 ***" << std::endl;

    const int_list_t list{random_list(10)};
    std::cout << "Random List:"; 
    print_list(list);

    int rand_number = random_number(1, 5);
    std::cout << "Random Number:" << rand_number << std::endl; 
    int_list_t map_list{map(list, [rand_number](int item){return (rand_number*item);})};
    std::cout << "Mapped List:"; 
    print_list(map_list);

    int_list_t filter_list{filter(map_list, [](int item){return (item%2 == 0);})};
    std::cout << "Filtered List:"; 
    print_list(filter_list);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//main:
int main()
{
    std::srand( std::time( nullptr ));

    //Calling test functions
    test_21();
    test_22();
    test_23();
    test_24();
    test_25();
    test_31();
    test_32();

    return 0;
}
