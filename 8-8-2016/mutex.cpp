#include <thread>
#include <vector>

using data = std::tuple< int, int, int >;

class indexed_list
{
public:
    void add( const data& );

    data find_by_first( int ) const;
    data find_by_second( int ) const;

private:
    std::vector< data >         data_;
    std::vector< std::size_t >  first_index_;
    std::vector< std::size_t >  second_index_;

    mutable std::mutex  mutex_;
};

template < std::size_t pos >
void update_index(
    const std::vector< data >& data,
    std::vector< std::size_t >& index );

void indexed_list::add( const data& d )
{
    std::lock_guard< std::mutex > lock( mutex_ );

    data_.push_back( d );
    update_index< 0 >( data_, first_index_ );
    update_index< 1 >( data_, second_index_ );
}

template < std::size_t pos >
data find_by_index(
    const std::vector< data >& data,
    const std::vector< std::size_t >& index,
    int key );

data indexed_list::find_by_first( int first ) const
{
    std::lock_guard< std::mutex > lock( mutex_ );

    return find_by_index< 0 >( data_, first_index_, first );
}
