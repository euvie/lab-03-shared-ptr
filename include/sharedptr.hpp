// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_SHAREDPTR_HPP_
#define INCLUDE_SHAREDPTR_HPP_

#include <iostream>
#include <atomic>

template <typename T>
class sharedPtr{
 public:
  sharedPtr():
      pointer(nullptr)
      ,numberOfPointers(nullptr)
  {
  }


  sharedPtr(T *ptr):
      pointer(ptr)
      , numberOfPointers(nullptr)
  {
    if(pointer){
      numberOfPointers = new std::atomic_int;
      *numberOfPointers = 1;
    }
    else{
      numberOfPointers = nullptr;
    }
  }


  sharedPtr(const sharedPtr& r):
      pointer(r.pointer)
      ,numberOfPointers(r.numberOfPointers)
  {
    if(numberOfPointers){
      ++*numberOfPointers;
    }
  }


  sharedPtr(sharedPtr&& r):
      pointer(r.pointer)
      , numberOfPointers(r.numberOfPointers)
  {
    r.pointer = nullptr;
    r.numberOfPointers = nullptr;
  }

  ~sharedPtr(){
    reset();
  }

  auto operator=(const sharedPtr& r) -> sharedPtr&{
    if(this == &r){
      return *this;
    }
    else{
      pointer = r.pointer;
      numberOfPointers = r.numberOfPointers;
    }
    return *this;
  }
  auto operator=(sharedPtr&& r)->sharedPtr&
  {
    if(this == &r) return *this;
    else{
      pointer = r.pointer;
      r.pointer = nullptr;
      numberOfPointers = r.numberOfPointers;
      r.numberOfPointers = nullptr;
    }
    return *this;
  }

  operator bool() const
  {
    if(pointer != nullptr)
      return true;
    else return false;
  }
  auto operator*() const -> T&
  {
    if(pointer == nullptr) {
      throw std::runtime_error("U cannot use * with nullptr");
    }
    else {
      return *pointer;
    }
  }
  auto operator->() const ->T*
  {
    if(pointer == nullptr) {
      throw std::runtime_error("U cannot use -> with nullptr");
    }
    else {
      return pointer;
    }
  }

  auto get()-> T*
  {
    return pointer;
  }
  void reset()
  { if(numberOfPointers != nullptr && pointer != nullptr) {
      if (*numberOfPointers == 1) {
        delete pointer;
        delete numberOfPointers;
      } else {
        --*(numberOfPointers);
      }
      numberOfPointers = nullptr;
      pointer = nullptr;
    }
  }
  void reset(T *ptr)
  {
    reset();
    pointer = ptr;
    numberOfPointers = new std::atomic_int;
    *numberOfPointers = 1;
  }
  void swap(sharedPtr& r){
    std::swap(pointer, r.pointer) ;
    std::swap(numberOfPointers, r.numberOfPointers);
  }
  auto useCount() const -> size_t
  {
    if(numberOfPointers){
      return *numberOfPointers;
    }
    else return 0;
  }

 private:
  T *pointer;
  std::atomic_int *numberOfPointers;


};

#endif // INCLUDE_SHAREDPTR_HPP_
