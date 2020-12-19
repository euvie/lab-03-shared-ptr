// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "sharedptr.hpp"
#include <string>
#include <utility>

TEST(nullptr, Constructor) {
  sharedPtr<int> ptr(nullptr);
  EXPECT_EQ(ptr.get(), nullptr);
}

TEST(ptr, Constructor){
  auto *ptr = new double(2.45);
  auto *ptr_ = new double(7.45);
  sharedPtr<double> ptr0(ptr_);
  sharedPtr<double> ptr1(ptr);
  sharedPtr<double> ptr2(ptr1);
  EXPECT_EQ(ptr1.get(), ptr);
  EXPECT_EQ(ptr2.get(), ptr);
  sharedPtr<double> ptr3 = std::move(ptr0);
  sharedPtr<double> ptr4(ptr3);
  EXPECT_EQ(ptr3.get(), ptr_);
  EXPECT_EQ(ptr4.get(), ptr_);
}

TEST(operatorEqvality, ptr){
  auto *ptr_ = new double(7.45);
  sharedPtr<double> ptr0(ptr_);
  sharedPtr<double> ptr1 = ptr0;
  EXPECT_EQ(ptr1.get(), ptr_);
  EXPECT_EQ(ptr0.get(), ptr_);
  sharedPtr<double> ptr3 = std::move(ptr1);
  sharedPtr<double> ptr4 = ptr3;
  EXPECT_EQ(ptr3.get(), ptr_);
  EXPECT_EQ(ptr4.get(), ptr_);
}

TEST(ptr, Bool){
  auto *ptr_ = new double(7.45);
  sharedPtr<double> ptr0(ptr_);
  sharedPtr<double> ptr1(nullptr);
  EXPECT_TRUE(ptr0);
  EXPECT_FALSE(ptr1);
}
struct House{
  int levels;
};

TEST(ptr, operator) {
  auto *ptr = new int(10);
  sharedPtr<int> ptr1(ptr);
  EXPECT_EQ(*ptr1, *ptr);
  auto houseptr = new House;
  houseptr->levels = 12;
  sharedPtr<House> ptr2(houseptr);
  EXPECT_EQ(ptr2->levels, houseptr->levels);
}

TEST(ptr, Get) {
  auto *ptr = new int(10);
  sharedPtr<int> ptr1(ptr);
  sharedPtr<int> ptr2 = ptr1;
  EXPECT_EQ(ptr2.get(), ptr);
}

TEST(ptr, GetNullptr) {
  auto ptr = nullptr;
  sharedPtr<int> ptr1(ptr);
  sharedPtr<int> ptr2 = ptr1;
  EXPECT_EQ(ptr2.get(), nullptr);
}


TEST(ptr, Reset) {
  auto *ptr = new int(10);
  sharedPtr<int> ptr1(ptr);
  ptr1.reset();
  EXPECT_EQ(ptr1.get(), nullptr);
}

TEST(ptr, Reset2){
  auto *param1 = new char('a');
  auto *param2 = new char('b');
  sharedPtr<char> ptr1(param1);
  sharedPtr<char> ptr2(ptr1);
  ptr2.reset(param2);
  sharedPtr<char> ptr3(ptr2);

  EXPECT_EQ(ptr1.get(), param1);
  EXPECT_EQ(ptr2.get(), param2);
  EXPECT_EQ(ptr3.get(), param2);
  EXPECT_EQ(ptr1.useCount(), 1);
  EXPECT_EQ(ptr2.useCount(), 2);
  EXPECT_EQ(ptr3.useCount(), 2);
}

TEST(ptr, Swap){
  auto *ptr = new int(10);
  auto *ptr1 = new int(1);
  sharedPtr<int> ptr2(ptr);
  sharedPtr<int> ptr3(ptr1);
  ptr2.swap(ptr3);
  EXPECT_EQ(ptr2.get(), ptr1);
  EXPECT_EQ(ptr3.get(), ptr);
}

TEST(ptr, SwapNullptr){
  auto ptr = nullptr;
  auto *ptr1 = new int(1);
  sharedPtr<int> ptr2(ptr);
  sharedPtr<int> ptr3(ptr1);
  ptr2.swap(ptr3);
  EXPECT_EQ(ptr2.get(), ptr1);
  EXPECT_EQ(ptr3.get(), nullptr);
}
TEST(ptr, UseCount) {
  auto *ptr = new int;
  *ptr = 10;
  sharedPtr<int> ptr1;
  sharedPtr<int> ptr2(ptr);
  sharedPtr<int> ptr3(ptr2);
  sharedPtr<int> ptr4 = ptr3;
  EXPECT_EQ(ptr2.useCount(), 3);
  EXPECT_EQ(ptr1.useCount(), 0);
  EXPECT_EQ(ptr3.useCount(), 3);
}

TEST(isConstructible, isMovable){
  EXPECT_EQ(std::is_move_assignable<sharedPtr<int>>::value, true);
  EXPECT_EQ(std::is_move_constructible<sharedPtr<int>>::value, true);
}
