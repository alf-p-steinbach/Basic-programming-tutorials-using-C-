#include "english_words_list.hpp"
#include "merge_shuffle.hpp"
namespace e = oneway_sorting_examples;
using e::List, e::english_words_list, e::merge_shuffle;
using my_random::Seed;

#include <iostream>
using std::cout, std::endl;

auto main()
    -> int
{
    List words = english_words_list();
    const int n = words.count();
    
    const int seq_nr = 42;
    merge_shuffle( words, Seed( seq_nr ) ); // seq_nr => get the same result every time.
    cout << n << " merge-shuffled words:" << endl;
    int i = 0;
    for( e::Node* p = words.head; p != nullptr; p = p->next ) {
        if( i < 5 or n - 5 <= i ) {
            if( i > 0 ) {
                cout << ", ";
            };
            if( i == n - 5 ) {
                cout << "..., ";
            }
            cout << p-> value;
        }
        ++i;
    }
    cout << "." << endl;
}
