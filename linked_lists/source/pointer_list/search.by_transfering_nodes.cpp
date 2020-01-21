#include "list_copy_of_the_five_important_numbers.hpp"

#include <stdlib.h>         // EXIT_...
#include <iostream>

namespace app {
    using std::cout, std::endl;

    void display( const Type_<const char*> explanation, const Type_<Node*> head )
    {
        cout << explanation;
        for( Node* p = head; p != nullptr; p = p->next ) {
            cout << " " << p->value;
        }
        cout << "." << endl;
    }

    template< class Func >
    auto transferred_nodes( const Func& has_desired_property, Node*& head )
        -> Node*
    {
        Node*   xfer_head = nullptr;
        Node*   trailing    = nullptr;

        for(    Node* p = head;
                p != nullptr;
                p = p->next ) {
            if( has_desired_property( p->value ) ) {
                Node*& p_this_node = (trailing == nullptr? head : trailing->next);
                unlinked( p_this_node )->link_in_before( xfer_head );
            }
            trailing = p;
        }
        return xfer_head;
    }

    void run()
    {
        struct List     // If you have such class derive this from a `No_copy_or_move`.
        {
            Node* head = list_copy_of_the_five_important_numbers();
            ~List() { delete_list( head ); }        // Auto cleanup also when exception.
        };
        
        List list;

        display( "Original values:", list.head );
    #if defined( DO_NOTHING_PLEASE )

        // If there is no node with value 7 then this code has no effect, hurray! :)

        const auto with_value_7 = [](double x) -> bool { return x == 7; };
        delete_list( transferred_nodes( with_value_7, list.head ) );

    #elif defined( LEAK_MEMORY_PLEASE )

        // Memory leaks like this can be prevented by using C++ RAII (destructors).

        const auto with_value_7 = [](double x) -> bool { return x == 7; };
        auto p = transferred_nodes( with_value_7, list.head );

    #else

        // Delete all nodes that are not 42, in a way that's O(n) efficient for a large list.
        // There is no natural way to get O(n^2) inefficiency. :)

        cout << "O(n)-deleting the too math-ish numbers..." << endl;
        const auto with_not_42 = [](double x) -> bool { return x != 42; };
        delete_list( transferred_nodes( with_not_42, list.head ) );

    #endif
        display( "The list is now", list.head );
    }
}  // namespace app

auto main()
    -> int
{
    using std::exception, std::cerr, std::endl;
    try {
        app::run();
        return EXIT_SUCCESS;
    } catch( const exception& x ) {
        cerr << "!" << x.what() << endl;
    }
    return EXIT_FAILURE;
}
