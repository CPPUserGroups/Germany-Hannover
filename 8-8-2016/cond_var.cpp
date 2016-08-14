#include <thread>
#include <deque>

template < typename T >
class queue
{
public:
    void push( const T& );
    T pop();

private:
    std::deque< T >             queue_;

    std::mutex                  mutex_;
    std::condition_variable     not_empty_;
};

template < typename T >
void queue< T >::push( const T& element )
{
    {
        std::lock_guard< std::mutex > lock( mutex_ );

        queue_.push_back( element );
    }

    not_empty_.notify_one();
}

template < typename T >
T queue< T >::pop()
{
    std::lock_guard< std::mutex > lock( mutex_ );

    while ( queue_.empty() )
        not_empty_.wait( lock );

    const T result = queue_.front();
    queue_.pop_front();

    return result;
}
