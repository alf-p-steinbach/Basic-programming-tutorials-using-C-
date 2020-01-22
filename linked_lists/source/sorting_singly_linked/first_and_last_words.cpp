#include "english_words_list.hpp"
namespace e = oneway_sorting_examples;

#include <iostream>
using std::cout, std::endl;

auto main()
    -> int
{
    e::List words = e::english_words_list();
    const int n = words.count();
    
    cout << n << " words:" << endl;
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
