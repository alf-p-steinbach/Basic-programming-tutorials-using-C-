#include "../my_chrono.hpp"
#include "../my_random.hpp"
using my_chrono::Timer_clock, my_chrono::Time_point, my_chrono::as_seconds;
using my_random::Seed;

#include "english_words_list.hpp"
#include "merge_shuffle.hpp"
namespace x = oneway_sorting_examples;
using x::Node, x::List, x::english_words_list, x::merge_shuffle;

#include <iostream>
using std::cout, std::clog, std::endl;

auto main()
    -> int
{
    List words = english_words_list();
    const int n = int( words.count() );
    
    const Time_point start_time = Timer_clock::now();
    const int seq_nr = 42;
    merge_shuffle( words, Seed( seq_nr ) ); // seq_nr => get the same result every time.
    const Time_point end_time = Timer_clock::now();
    const double n_seconds = as_seconds( end_time - start_time );

    clog << n_seconds << " seconds." << endl;
    cout << "Merge-shuffled " << n << " words:" << endl;
    int i = 0;
    for( Node* p = words.head; p != nullptr; p = p->next ) {
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
