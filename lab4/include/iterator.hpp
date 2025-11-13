/* Image iterator.
 * @file
 * @date 2018-08-05
 * @author Anonymous
 */

#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <cmath>
#include <iterator>
#include <type_traits>
#include <utility>

#include <boost/iterator/iterator_adaptor.hpp>

//{ image iterator
template<class Iterator>
class image_iterator: public boost::iterator_adaptor<
    image_iterator<Iterator>,
    Iterator,
    typename std::iterator_traits<Iterator>::value_type,
    boost::random_access_traversal_tag>
{
public:
    image_iterator()
        : image_iterator::iterator_adaptor_(), width_(0), stride_(0)
    {}

    explicit image_iterator(Iterator it, size_t width, size_t stride)
        : image_iterator::iterator_adaptor_(it), row_begin_(it), width_(width), stride_(stride)
    {}

private:
    friend class boost::iterator_core_access;

    void increment()
    {
        advance(1);
    }

    void decrement()
    {
        advance(-1);
    }

    void advance(typename image_iterator::difference_type n)
    {
        if (n == 0)
            return;

        // Current position relative to row_begin_
        auto col = this->base() - row_begin_;
        
        // Calculate new absolute column position
        auto new_col = col + n;
        
        // Calculate how many full rows to skip
        auto row_delta = new_col / static_cast<typename image_iterator::difference_type>(width_);
        
        // Calculate final column in the new row
        auto final_col = new_col % static_cast<typename image_iterator::difference_type>(width_);
        
        // Handle negative modulo correctly
        if (final_col < 0)
        {
            --row_delta;
            final_col += width_;
        }
        
        // Move row_begin_ by the number of rows
        row_begin_ += row_delta * stride_;
        
        // Set the base iterator to the new position
        this->base_reference() = row_begin_ + final_col;
    }

    typename image_iterator::difference_type distance_to(const image_iterator& other) const
    {
        // Calculate row difference
        auto row_diff = (other.row_begin_ - row_begin_) / static_cast<typename image_iterator::difference_type>(stride_);
        
        // Calculate column positions
        auto this_col = this->base() - row_begin_;
        auto other_col = other.base() - other.row_begin_;
        
        // Total distance in logical image coordinates
        return row_diff * width_ + (other_col - this_col);
    }

    Iterator row_begin_;  // Points to the beginning of the current row
    size_t width_;        // Image width (logical width)
    size_t stride_;       // Row stride (physical width including padding)
};
//}

#endif // __ITERATOR_HPP__
