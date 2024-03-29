// file Vector_farmerkeith.h:
// This is a library for class "vector" similar to "std::vector"
// with access checking compatible with the Arduino environment
// which does not support the try-throw-catch model used by std::vector
// This software has been tested with a WeMos D1 mini pro (ESP8266 processor)
// last update 11 September 2019

# ifndef FARMERKEITH_VECTOR_H
# define FARMERKEITH_VECTOR_H

// These are needed in the definition of class vector
using std::initializer_list;
using std::copy;
using std::allocator;

//*********************************************************************************
//                               vector
//*********************************************************************************

// References are to "Programming" by Bjarne Stroustrup, 2nd edition, Addison Wesley 2014.
// See page 601, page 630, 677, 691, ...
// Thanks to Zac Staples whose version of a vector got me going on this.

// As for std::vector, unchecked access is provided with the operator [], and checked
// access is provided with the function at().
// In this version, vector access outside the defined range from 0 to size-1 using at() results in the
// return of a default T object. In the case of a read access, the returned object is
// typically 0 or the empty string. In the case of a write access, the object for
// writing is written into the memory reserved for that purpose (an object named "extra").
// In both cases the out-of-range index is stored in an integer variable "out_of_range".
// The function at() provides for a second, optional parameter, which if provided is
// written with a 0 for in-range access and a 1 for out-of-range access.

template<typename T, typename A = allocator<T>> // for all types T and allocator A
class vector { // vector of Ts
    A alloc;         // instance of allocator type
    uint16_t sz{0};       // size                           , 2 bytes
    uint16_t space{0};    // size + free slots for expansion, 2 bytes
    T* elem;         // pointer to the first element        , 4 bytes
    T extra{T{}};    // single T element to use for out of range access
    uint16_t out_of_range_index = 0; //                       2 bytes

  public:
    // this structure "debugBits" provides debug printout controls for each
    // vector function. Default is all set to 0. Setting an individual bit
    // to "1" enables a Serial.print() message or messages from that function.
    // To change the values, go the the function "setDebugBits" at the end of this file
    // or write the values directly, eg "v.debug.ZeroLength = 1;"
    // where v is the name of your vector.
    struct debugBits { //                                     2 bytes
      unsigned ZeroLength       : 1 ; // 13
      unsigned NonZeroLength    : 1 ; // 12
      unsigned InitializerList  : 1 ; // 11
      unsigned CopyConstructor  : 1 ; // 10
      unsigned MoveConstructor  : 1 ; // 9
      unsigned CopyAssignment   : 1 ; // 8
      unsigned MoveAssignment   : 1 ; // 7
      unsigned Access           : 1 ; // 6
      unsigned OutOfRangeAccess : 1 ; // 5
      unsigned Delete           : 1 ; // 4
      unsigned Resize           : 1 ; // 3
      unsigned Reserve          : 1 ; // 2
      unsigned PushBack         : 1 ; // 1
      unsigned Clear            : 1 ; // 0
    } debug;     // was 13 bool -> 13 bytes

    using size_type = uint16_t;          //    page 730
    using value_type = T;
    using iterator = T*;                 // pointer to element
    using const_iterator = const T*;

    vector(); // constructor for zero length vector

    explicit vector(int s); // "normal" constructor (s is the element count) p643

    vector(initializer_list<T>lst);    // initializer_list constructor

    vector (const vector& arg);        // copy constructor, see p633

    vector& operator=(const vector& arg); // copy assignment, see p635

    vector(vector&& arg);             // move constructor, see p639

    vector& operator=(vector&& arg);  // move assignment, see p639

    ~vector(); // destructor

    T& operator[](int n) {   // unchecked access for read/write
      if (debug.Access) Serial.print("\n(debug) unchecked access for vector");
      if (sz == 0 && space == 0) return extra; else return elem[n]; // access, return reference, see page 646
    }

    const T& operator[](int n) const { // unchecked access for read/write to a const vector
      if (debug.Access) Serial.print("\n(debug) Unchecked access for const vector");
      if (sz == 0 && space == 0) return T{}; else return elem[n]; // Write access, return reference, see 648
    }

    const T& at(int n, bool& out_of_range) const; // checked access for read/write

    const T& at(int n) const {  // checked access for read/write without return value
      bool out_of_range;
      return at(n, out_of_range); // out_of_range is discarded
    }

    T& at(int n, bool& out_of_range); // checked access for read/write // was T&

    T& at(int n) {  // checked access for read/write without return value // was T&
      bool out_of_range;
      return at(n, out_of_range); // out_of_range is discarded
    }

    size_type size() const {
      return sz;     // get size
    }

    int capacity() const {
      return space;  // get space (aka capacity)
    }

    int out_of_range() const {
      return out_of_range_index;  // get out_of_range
    }

    // this function (get_extra()) returns the value stored in extra
    // and also clears it back to default (eg 0 for numbers, empty for String)
    T get_extra() {  // get value stored in extra[0]
      T t1 = extra;  // make local copy of extra
      extra = T{};   // reset stored value to default/null
      return t1;
    }

    void resize(uint16_t newsize, T); // growth see p692. Definition below.

    void push_back (const T& d);      // see p692. Definition below.

    void reserve (uint16_t newalloc); // see p692. Definition below.

    void setDebugBits();  // control printing of debug messages, see definition below.

    iterator begin() {
      return &elem[0]; //   page 730
    }
    const_iterator begin() const {
      return &elem[0]; // pointer to the first element
    }
    iterator end() {
      return &elem[sz];
    }
    const_iterator end() const {
      return &elem[sz];
    }

    // the following insert and erase are not range checked
    iterator insert (iterator p, const T& val); // inserts val at vector position p
    iterator erase (iterator p); // removes the vector element at position p

    // clear function - resets size to 0 and writes a default value into the memory reserved for elements
    void clear();

  private:
    uint16_t calcSpace() {
      return max(space + 4, (int)((float)space * 1.1)); // "magic constants" 4 & 1.1
      // note that std::vector uses 8 and 2 so uses up more space usually
    }
}; // end of class vector

template<typename T, typename A>
vector<T, A>::vector() : elem(0) // constructor for zero length vector
{
  setDebugBits();
  if (debug.ZeroLength) Serial.print("\n(debug) constructor for zero length vector");
} // end of constructor for zero length vector

template<typename T, typename A>
vector<T, A>::vector(int s) // "normal" constructor (s is the element count) p643
  : sz{s}, space{s}   // initialize sz and space
  , extra{T{}}        // initialise extra to default value
{
  setDebugBits();
  T* p = alloc.allocate(sz); // get a new memory allocation for elem
  for (int i = 0; i < sz; ++i) alloc.construct(&p[i], T{}); // initialize to T{}
  elem = p;                       // point elem to new memory location
  if (debug.NonZeroLength)
    Serial.print("\n(debug) constructor for vector with capacity " +
                 String(s) + " elements");
} // end of constructor for vector(int s)

template<typename T, typename A>
vector<T, A>::vector(initializer_list<T>lst)    // initializer_list constructor
  : sz{lst.size()}, space{lst.size()} // initialize sz and space
  , extra{T{}}    // initialise extra to default value
{
  setDebugBits();
  T* p = alloc.allocate(sz); // get a new memory allocation for elem
  for (int i = 0; i < sz; ++i) alloc.construct(&p[i], T{}); // initialize to T{}
  elem = p;                       // point elem to new memory location
  copy(lst.begin(), lst.end(), elem); // copy list elements using std::copy
  if (debug.InitializerList)
    Serial.print("\n(debug) constructor for InitializerList vector");
} // end of vector(initializer_list<T>lst)

template<typename T, typename A>
vector<T, A>::vector (const vector& arg) // copy constructor, see p633
  : sz{arg.sz}, space{arg.space} 
  , extra{T{}}    // initialise extra to default value
{
  setDebugBits();
  T* p = alloc.allocate(arg.sz); // get a new memory allocation for elem
  for (int i = 0; i < arg.sz; ++i) alloc.construct(&p[i], arg.elem[i]); // copy members from arg
  elem = p;                       // point elem to new memory location
  // for (int i = 0; i < arg.sz; i++) *(elem + i) = arg.elem[i]; // copy members from arg
  if (debug.CopyConstructor) Serial.print("\n(debug) Copy Constructor for vector");
} // end of vector (const vector& arg)

template<typename T, typename A> 
vector<T, A>& vector<T, A>::operator=(const vector& arg) // copy assignment, see p635
{
  setDebugBits();
  T* p = alloc.allocate(arg.space); // get a new memory allocation the size of copy origin
  // T* p = new T[arg.sz]; // pointer to new space for copy of elements
  for (int i = 0; i < arg.sz; ++i) alloc.construct(&p[i], arg.elem[i]); // copy existing elem into new
  for (int i = arg.sz; i < arg.space; ++i) alloc.construct(&p[i], T{}); // set empty new space to default
  for (int i = 0; i < sz; ++i) alloc.destroy (&elem[i]);    // destoy old elem 0 to sz
  alloc.deallocate(elem, space);  // deallocate old elem space (start at elem, count is space)
  // delete[] elem;               // deallocate old space
  elem = p;                       // reset elem to point to the new copy
  sz = arg.sz;
  space = arg.space;
  if (debug.CopyAssignment) Serial.print("\n(debug) Copy Assignment for vector");
  return *this;
} // end of vector& operator= (copy assignment)

template<typename T, typename A>
vector<T, A>::vector(vector&& arg) // move constructor, see p639
  : sz{arg.sz}, space{arg.space}
  , extra{arg.extra} // initialize the target vector with the original values
  , elem{arg.elem}   
{ setDebugBits();
  arg.sz = 0;        // set original vector to empty/null
  arg.space = 0;
  arg.elem = nullptr;
  arg.extra = T{}; 
  if (debug.MoveConstructor) Serial.print("\n(debug) Move Constructor for vector");
} // end of vector(vector&& arg) // move constructor

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(vector&& arg) // move assignment, see p639
{ delete[] elem; // ?? ToDo: check this
  elem = arg.elem;
  extra = arg.extra;
  sz = arg.sz;
  space = arg.space;
  setDebugBits();
  arg.elem = nullptr;
  arg.extra = T{};
  arg.sz = 0;        // set original vector to empty/null
  arg.space = 0;
  if (debug.MoveAssignment) Serial.print("\n(debug) Move assignment for vector");
  return *this;
} // end of vector<T,A>& operator=(vector&& arg) // move assignment

template<typename T, typename A>
vector<T, A>::~vector() // destructor
{ if (debug.Delete) Serial.print("\n(debug) Delete vector");
  for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]); // from Zac
  alloc.deallocate(elem, space);  // deallocate space
} // end of ~vector() (destructor)

// --------------------------------------------------
template<typename T, typename A>
void vector<T, A>::clear() // clear function
{ if (debug.Clear) Serial.print("\n(debug) Clear vector");
  for (int i = 0; i < sz; ++i) elem[i] = T{};
  sz = 0;
  extra = T{};
} // end of vector<T, A>::clear()

template<typename T, typename A>
const T& vector<T, A>::at(int n, bool& out_of_range) const {  // checked access for read/write // was T&
  if (debug.Access) Serial.print("\n(debug) Checked access for const vector");
  if (n < 0 || n >= sz) { // n is out of range
    if (debug.OutOfRangeAccess) Serial.print("\n(debug) out of range access to vector");
    out_of_range = 1;
    out_of_range_index = n;
    return extra;
  }
  else {                  // n is in range
    out_of_range = 0;
    if (sz == 0 && space == 0) return T{}; else return elem[n]; // acess, return reference, see 648
  }
} // end of const T& at(int n, bool& out_of_range) const

template<typename T, typename A>
T& vector<T, A>::at(int n, bool& out_of_range) {  // checked access for read/write // was T&
  if (debug.Access) Serial.print("\n(debug) Checked access for vector");
  if (n < 0 || n >= sz) { // n is out of range
    if (debug.OutOfRangeAccess) Serial.print("\n(debug) out of range access to vector");
    out_of_range = 1;
    out_of_range_index = n;
    return extra;
  }
  else {                 // n is in range
    out_of_range = 0;
    if (sz == 0 && space == 0) return extra; else return elem[n]; // access, return reference, see 648
  }
} // end of T& at(int n, bool& out_of_range)

template<typename T, typename A>
void vector<T, A>::reserve(uint16_t newalloc) { // page 692
  if (debug.Reserve) {
    Serial.print("\n(debug) Reserve for vector, new space ");
    Serial.print(String(newalloc) + ", copy and destroy old " + String(space));
  }
  T* p = alloc.allocate(newalloc); // get a new memory allocation for elem the size of newalloc
  for (int i = 0; i < sz; ++i) alloc.construct(&p[i], elem[i]); // copy existing elem into new
  for (int i = sz; i < newalloc; ++i) alloc.construct(&p[i], T{}); // set empty new space to default
  for (int i = 0; i < sz; ++i) alloc.destroy (&elem[i]);    // destoy old elem 0 to sz
  alloc.deallocate(elem, space);  // deallocate old elem space (start at elem, count is space)
  elem = p;                       // point elem to new memory location
  space = newalloc;               // update space info
} // end of void vector<T, A>::reserve

template<typename T, typename A>
void vector<T, A>::push_back(const T& val) { // page 692
  if (debug.PushBack) {
    if (sz<20 || sz % 100 == 0) { // reduce prints for large vectors
      Serial.print("\n(debug) push_back sz=");
      Serial.print(sz);
      Serial.print(" space=");
      Serial.print(space);
    }
  }
  uint16_t newSpace = calcSpace();
  if (debug.PushBack) {
    if (sz<20 || sz % 100 == 0) {
      Serial.print("\n(debug) newSpace=");
      Serial.print(newSpace);
    }
  }
  if (debug.PushBack)
    if (sz == space)
      Serial.print("\n(debug) push_back call reserve " + (String)newSpace);
  if (space == 0) reserve(4);       //start small
  else if (sz >= space) reserve(newSpace); // get more space
  alloc.construct(&elem[sz], val);     // add val at end
  ++sz;                                // increase the size
} // end of void vector<T, A>::push_back

template<typename T, typename A>
void vector<T, A>::resize(uint16_t newspace, T val = T()) { // page 692
  if (debug.Resize) Serial.print("\n(debug line 384) Resize for vector");
  // Cases are:
  // newspace > space: allocate newspace, copy old elements into new allocation
  // newspace == space: do nothing
  // sz <= newspace < space: as for newspace > space
  // newspace < sz: set newspace to sz and do as for newspace > space
  if (newspace != space) {    // do main action
    if (newspace <= sz) newspace = sz;
    if (debug.Resize) Serial.print("\n(debug) calling reserve " + (String)newspace);
    reserve(newspace); // allocate new space, copy old into new, remove old, set space.
  }

  if (debug.Resize) Serial.print("\n(debug) End of resize for vector");
} // end of void vector<T, A>::resize

template<typename T, typename A>  // removes the vector element at position p
typename vector<T, A>::iterator vector<T, A>::erase (iterator p) {  // page 746
  if (p == end()) return p;
  for (auto pos = p + 1; pos != end(); ++pos)
    *(pos - 1) = *pos;           // copy element one to the left
  alloc.destroy(&*(end() - 1));  // destroy surplus copy of last element
  --sz;
  return p;
} // end of typename vector<T, A>::iterator vector<T, A>::erase (iterator p)

template<typename T, typename A> // inserts val at vector position p
typename vector<T, A>::iterator vector<T, A>::insert (iterator p, const T& val) {  // page 746
  uint16_t index = p - begin(); // p will become invalid if reserve() is used
  if (size() == capacity()) reserve (calcSpace()); // same function used by push_back
  alloc.construct (elem + sz, *end()); // new space needs to be initialized ("constructed")
  ++sz;
  iterator pp = begin() + index; // the place to put val.
  for (auto pos = end() - 1; pos != pp; --pos)
    *pos = *(pos - 1);           // copy element one to the right
  *(begin() + index) = val;      // store val
  return pp;
} // end of typename vector<T, A>::iterator vector<T, A>::insert (iterator p, const T& val)

template<typename T, typename A>
void vector<T, A>::setDebugBits() {
  debug.ZeroLength       = 0; // 13
  debug.NonZeroLength    = 0; // 12
  debug.InitializerList  = 0; // 11
  debug.CopyConstructor  = 0; // 10
  debug.MoveConstructor  = 0; // 9
  debug.CopyAssignment   = 0; // 8
  debug.MoveAssignment   = 0; // 7
  debug.Access           = 0; // 6
  debug.OutOfRangeAccess = 0; // 5
  debug.Delete           = 0; // 4
  debug.Resize           = 0; // 3
  debug.Reserve          = 0; // 2
  debug.PushBack         = 0; // 1
  debug.Clear            = 0; // 0
} // end of void setDebugBits()

#endif
// end of file
