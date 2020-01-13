#include <initializer_list>     // Required for deduced type of brace initializer.
#include <iostream>
using std::cout, std::endl;

template< class T > using Type_ = T;

struct Node
{
    Node*   next;
    double  value;

    void link_in_before( Node*& a_next_field )
    {
        next = a_next_field;
        a_next_field = this;
    }
    
    friend auto unlinked( Node*& a_next_field )
        -> Node*
    {
        const auto result = a_next_field;
        a_next_field = result->next;
        return result;
    }
    
    friend void delete_list( Node* head )
    {
        while( head != nullptr ) {
            delete unlinked( head );
        }
    }
};

auto next_field_for_sorted_insertion_of( const double new_value, Node*& list_head )
    -> Node*&
{
    Node* trailing = nullptr;
    for(    Node* p = list_head; 
            p != nullptr and p->value < new_value;
            p = p->next ) {
        trailing = p;
    }
    return (trailing == nullptr? list_head : trailing->next);
}

auto main()
    -> int
{
    const auto data = {3.14, 2.72, 0.0, 42.0, -1.0};
    Node* head = nullptr;

    // Insert the data sorted.
    for( const double v: data ) {
        Node*& next = next_field_for_sorted_insertion_of( v, head );
        (new Node{ nullptr, v})->link_in_before( next );
    }

    // Display the list.
    for( Node*p = head; p != nullptr; p = p->next ) {
        cout << p->value << " ";
    }
    cout << endl;

    // Clean up, just to be nice.
    delete_list( head );
}
