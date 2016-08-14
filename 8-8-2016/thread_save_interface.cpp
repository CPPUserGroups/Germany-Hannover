#include <thread>

class key;
class element;

class cache
{
public:
    const element* look_up( const key& k ) const;

    bool insert( const element&, const key& );
private:
    // ...
    mutable std::mutex mutex_;
};

const element* cache::look_up( const key& k ) const
{
    std::lock_guard< std::mutex > lock( mutex_ );

    const element* result = nullptr;
    //...
    return result;
}

bool cache::insert( const element& e, const key& k )
{
    std::lock_guard< std::mutex > lock( mutex_ );

    const element* const found = look_up( k );

    if ( found )
        return false;

    //...
    return true;
}

const element* cache::look_up( const key& k ) const
{
    std::lock_guard< std::mutex > lock( mutex_ );

    return look_up_impl( k );
}

bool cache::insert_impl( const element& e, const key& k )
{
    const element* const found = look_up_impl( k );

    if ( found )
        return false;

    //...
    return true;
}

bool cache::insert( const element& e, const key& k )
{
    std::lock_guard< std::mutex > lock( mutex_ );

    return insert_impl( e, k );
}
