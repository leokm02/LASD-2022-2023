#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../list/list.hpp"
#include "../vector/vector.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../queue/vec/queuevec.hpp"

#include <string>

#define VECTOR_ID 1
#define LIST_ID 2
#define STACKVEC_ID 3
#define STACKLST_ID 4
#define QUEUEVEC_ID 5
#define QUEUELST_ID 6

#define INT_ID 1
#define FLOAT_ID 2
#define STRING_ID 3

#define DEFAULT_SIZE 10

void mytest();

unsigned short selectStructure();
unsigned short selectType();

void fillVector(lasd::Vector<int> &);
void fillVector(lasd::Vector<float> &);
void fillVector(lasd::Vector<std::string> &);

void fillList(lasd::List<int> &);
void fillList(lasd::List<float> &);
void fillList(lasd::List<std::string> &);

void fillStack(lasd::Stack<int> &);
void fillStack(lasd::Stack<float> &);
void fillStack(lasd::Stack<std::string> &);

void fillQueue(lasd::Queue<int> &);
void fillQueue(lasd::Queue<float> &);
void fillQueue(lasd::Queue<std::string> &);

template <typename Data>
void testVector(lasd::Vector<Data> &);

template <typename Data>
void testList(lasd::List<Data> &);

template <typename Data>
void testStackVec(lasd::StackVec<Data> &);

template <typename Data>
void testStackLst(lasd::StackLst<Data> &);

template <typename Data>
void testQueueVec(lasd::QueueVec<Data> &);

template <typename Data>
void testQueueLst(lasd::QueueLst<Data> &);

int generateInt();
float generateFloat();
std::string generateString();

void getValue(int &);
void getValue(unsigned short &);
void getValue(unsigned long &);
void getValue(float &);
void getValue(std::string &);

#endif