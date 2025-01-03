#ifndef HASH_GRID_HPP
#define HASH_GRID_HPP

#include <stdint.h>
#include <LRE/linalg/vector4.hpp>

class HashGrid
{

 private:

     int32_t num_dims;
     int32_t cell_size;

 public:

     HashGrid(const HashGrid & other) = delete;

     HashGrid();

     void insert(const Vector4 & point);

     void find(const Vector4 & point) const;

     void erase(const Vector4 & point);
};

#endif
