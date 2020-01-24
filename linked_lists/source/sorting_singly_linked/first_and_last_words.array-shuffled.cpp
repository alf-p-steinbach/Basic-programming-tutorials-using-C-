﻿#include "../data/english_words_iteration.hpp"
#include "../my_chrono.hpp"
#include "../my_random.hpp"
using data::for_each_english_word;
using my_random::Seed, my_random::random_seed;
using my_chrono::Timer_clock, my_chrono::Time_point, my_chrono::as_seconds;

#include <stddef.h>         // ptrdiff_t
using Size = ptrdiff_t;
using Index = Size;

#include <iostream>
#include <vector>           // std::vector
#include <string_view>      // std::string_view
#include <utility>          // std::swap
using std::vector, std::string_view, std::swap, std::cout, std::clog, std::endl;

auto english_words_vector()
    -> vector<string_view>
{
    vector<string_view> words;
    for_each_english_word( [&]( const string_view& w ) { words.push_back( w ); } );
    return words;
}

void array_shuffle( vector<string_view>& words, const Seed a_seed = random_seed() )
{
    my_random::Generator g( a_seed.value() );
    const Size max_index = words.size() - 1;
    for( Index i = 0; i < max_index - 1; ++i ) {
        const Size n_originals = words.size() - i;
        const Index rpos_other = my_random::Integer_<Index>::from( g, n_originals );
        const Index i_other = max_index - rpos_other;
        if( i != i_other ) {
            swap( words[i], words[i_other] );
        }
    }
}

auto main()
    -> int
{
    vector<string_view> words = english_words_vector();
    const int n = words.size();
    
    #ifdef USE_AVERAGE
        const int n_iterations = 1'000;
    #else
        // Note: a single array shuffle can be too fast to measure (can look like 0 time).
        const int n_iterations = 1;
    #endif
    const Time_point start_time = Timer_clock::now();
    for( int i = 0; i < n_iterations; ++i ) {
        const int seq_nr = 42;
        array_shuffle( words, Seed( seq_nr ) ); // seq_nr => get the same result always.
    }
    const Time_point end_time = Timer_clock::now();
    const double n_seconds = as_seconds( end_time - start_time )/n_iterations;

    clog << n_seconds << " seconds." << endl;
    cout << "Array-shuffled " << n << " words:" << endl;
    for( int i = 0; i < n; ++i ) {
        if( i < 5 or n - 5 <= i ) {
            if( i > 0 ) {
                cout << ", ";
            };
            if( i == n - 5 ) {
                cout << "..., ";
            }
            cout << words[i];
        }
    }
    cout << "." << endl;
}
