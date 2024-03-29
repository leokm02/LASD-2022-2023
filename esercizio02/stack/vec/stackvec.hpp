
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec: virtual public Stack<Data>,
                virtual protected Vector<Data> {
protected:

  static const unsigned long DEFAULT_CAPACITY = 10;

  using Container::size;
  using Vector<Data>::elements;
  unsigned long topIndex = 0;

public:

  // Default constructor
  StackVec() : Vector<Data>(DEFAULT_CAPACITY) {}

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const MappableContainer<Data>&); // A stack obtained from a MappableContainer
  StackVec(MutableMappableContainer<Data>&&) noexcept; // A stack obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec&);

  // Move constructor
  StackVec(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec& operator=(const StackVec&);

  // Move assignment
  StackVec& operator=(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const StackVec&) const noexcept;
  inline bool operator!=(const StackVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  inline const Data& Top() const override; // (non-mutable version; concrete function must throw std::length_error when empty)
  inline Data& Top() override; // (mutable version; concrete function must throw std::length_error when empty)
  inline void Pop() override; // (concrete function must throw std::length_error when empty)
  inline Data TopNPop() override; // (concrete function must throw std::length_error when empty)
  inline void Push(const Data&) override; // Copy of the value
  inline void Push(Data&&) noexcept override; // Move of the value

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override; // Override Container member

  inline unsigned long Size() const noexcept override; // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() override; // Override ClearableContainer member
  
  /* ************************************************************************ */

  inline void View() const override;

protected:

  // Auxiliary member functions

  inline void Expand();
  inline void Reduce();

  // Specific member function (inherited from LinearContainer)

  using typename FoldableContainer<Data>::FoldFunctor;
  inline void Fold(FoldFunctor, void *) const override;

  using typename MappableContainer<Data>::MapFunctor;
  inline void Map(MapFunctor) const override;

  using typename MutableMappableContainer<Data>::MutableMapFunctor;
  inline void Map(MutableMapFunctor) override;

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
