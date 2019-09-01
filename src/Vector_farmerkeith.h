// file Vector_farmerkeith.h:
// This is a library for class "vector" similar to "std::vector"
// with access checking compatible with the Arduino environment
// which does not support the try-throw-catch model used by std::vector
// This software has been tested with a WeMos D1 mini pro (ESP8266 processor)

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
// Vector access outside the defined range from 0 to size-1 using at() results in the
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
      unsigned ZeroLength       : 1 ; // 12
      unsigned NonZeroLength    : 1 ; // 11
      unsigned InitializerList  : 1 ; // 10
      unsigned CopyConstructor  : 1 ; // 9
      unsigned MoveConstructor  : 1 ; // 8
      unsigned CopyAssignment   : 1 ; // 7
      unsigned MoveAssignment   : 1 ; // 6
      unsigned Access           : 1 ; // 5
      unsigned OutOfRangeAccess : 1 ; // 4
      unsigned Delete           : 1 ; // 3
      unsigned Resize           : 1 ; // 2
      unsigned Reserve          : 1 ; // 1
      unsigned PushBack         : 1 ; // 0
    } debug;     // was 13 bool -> 13 bytes

    vector(); // constructor for zero length vector

    explicit vector(int s); // "normal" constructor (s is the element count) p643

    vector(initializer_list<T>lst);    // initializer_list constructor

    vector (const vector& arg); // copy constructor, see p633

    vector& operator=(const vector& arg); // copy assignment, see p635

    vector(vector&& arg); // move constructor, see p639

    vector& operator=(vector&& arg); // move assignment, see p639

    ~vector(); // destructor

    T& operator[](int n) {   // unchecked access for read/write
      if (debug.Access) Serial.print("\n(debug) unchecked access for vector");
      if (sz == 0) return extra; else return elem[n]; // access, return reference, see page 646
    }

    const T& operator[](int n) const { // unchecked access for read/write to a const vector
      if (debug.Access) Serial.print("\n(debug) Unchecked access for const vector");
      if (sz == 0) return T{}; else return elem[n]; // Write access, return reference, see 648
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

    int size() const {
      return sz;  // get size
    }

    int capacity() const {
      return space;  // get space (aka capacity)
    }

    int out_of_range() const {
      return out_of_range_index;  // get out_of_range
    }

    // this function (get_extra()) returns the value stored in extra
    // and also clears it back to default (eg 0 for numbers, empty for String)
    T get_extra() { // get value stored in extra[0]
      T t1 = extra; // make local copy of extra
      extra = T{};   // reset stored value to default/null
      return t1;
    }

    void resize(uint16_t newsize, T); // growth see p692. Definition below.

    void push_back (const T& d); // see p692. Definition below.

    void reserve (uint16_t newalloc); // see p692. Definition below.

    void setDebugBits();

}; // end of class vector

template<typename T, typename A>
vector<T, A>::vector() : elem(0) // constructor for zero length vector
{
  setDebugBits();
  if (debug.ZeroLength) Serial.print("\n(debug) constructor for zero length vector");
} // end of constructor for zero length vector

template<typename T, typename A>
vector<T, A>::vector(int s) // "normal" constructor (s is the element count) p643
  : sz{s}, space{s},   // initialize sz and space
    elem{new T[s]}     // allocate memory for sz Ts, not initialized
{
  setDebugBits();
  for (int i = 0; i < sz; ++i) elem[i] = T{}; // initialize every element to T{} (p327)
  if (debug.NonZeroLength)
    Serial.print("\n(debug) constructor for vector with capacity " +
                 String(s) + " elements");
} // end of constructor for vector(int s)

template<typename T, typename A>
vector<T, A>::vector(initializer_list<T>lst)    // initializer_list constructor
  : sz{lst.size()}, space{lst.size()}, // initialize sz and space
    extra{T{}},    // initialise extra to default value
    elem{new T[sz]}         // allocate memory for sz Ts, not initialized
{
  setDebugBits();
  copy(lst.begin(), lst.end(), elem); // initialize using std::copy
  if (debug.InitializerList)
    Serial.print("\n(debug) constructor for InitializerList vector");
} // end of vector(initializer_list<T>lst)

template<typename T, typename A>
vector<T, A>::vector (const vector& arg) // copy constructor, see p633
  : sz{arg.sz}, space{arg.space},
    elem{new T[arg.sz]} // create data members
{
  setDebugBits();
  for (int i = 0; i < arg.sz; i++) *(elem + i) = arg.elem[i]; // copy members from arg
  if (debug.CopyConstructor) Serial.print("\n(debug) Copy Constructor for vector");
} // end of vector (const vector& arg)

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(const vector& arg) // copy assignment, see p635
{
  setDebugBits();
  T* p = new T[arg.sz]; // pointer to new space for copy of elements
  for (int i = 0; i < arg.sz; i++) { // my version of copying
    *(p + i) = arg.elem[i];
  }
  delete[] elem;  // deallocate old space
  elem = p;       // reset elem to point to the new copy
  sz = arg.sz;
  space = arg.space;
  if (debug.CopyAssignment) Serial.print("\n(debug) Copy Assignment for vector");
  return *this;
} // end of vector& operator= (copy assignment)

template<typename T, typename A>
vector<T, A>::vector(vector&& arg) // move constructor, see p639
  : sz{arg.sz}, space{arg.space}
  , extra{arg.extra}
  , elem{arg.elem}   // copy
{ setDebugBits();
  arg.sz = 0;     // set original vector to empty/null
  arg.space = 0;
  arg.elem = nullptr;
  arg.extra = T{}; // just added, not tested
  if (debug.MoveConstructor) Serial.print("\n(debug) Move Constructor for vector");
} // end of vector(vector&& arg) // move constructor

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(vector&& arg) // move assignment, see p639
{ delete[] elem;
  elem = arg.elem;
  extra = arg.extra;
  sz = arg.sz;
  space = arg.space;
  setDebugBits();
  arg.elem = nullptr;
  arg.extra = T{};
  arg.sz = 0;     // set original vector to empty/null
  arg.space = 0;
  if (debug.MoveAssignment) Serial.print("\n(debug) Move assignment for vector");
  return *this;
} // end of vector<T,A>& operator=(vector&& arg) // move assignment

template<typename T, typename A>
vector<T, A>::~vector() // destructor
{
  if (debug.Delete) Serial.print("\n(debug) line 187 Delete vector");
  for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]); // from Zac
  alloc.deallocate(elem, space);  // deallocate space
} // end of ~vector() (destructor)

template<typename T, typename A>
const T& vector<T, A>::at(int n, bool& out_of_range) const {  // checked access for read/write // was T&
  if (debug.Access) Serial.print("\n(debug) Checked access for const vector");
  if (n < 0 || n >= sz) { // n is out of range
    if (debug.OutOfRangeAccess) Serial.print("\n(debug) out of range access to vector");
    out_of_range = 1;
    out_of_range_index = n;
    return extra;
  }
  else { // n is in range
    out_of_range = 0;
    return elem[n];  // acess, return reference, see 648
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
  else { // n is in range
    out_of_range = 0;
    return elem[n];  // access, return reference, see 648
  }
} // end of T& at(int n, bool& out_of_range)

template<typename T, typename A>
void vector<T, A>::reserve(uint16_t newalloc) { // page 692
  if (debug.Reserve && sz > 500) {
    Serial.print("\n(debug) line 251 Reserve for vector, ");
    if (newalloc <= space) Serial.print("nothing to do");
    else {
      Serial.print(" new space " + String(newalloc) + ", copy and destroy old " + String(space));
    }
  }
  if (newalloc <= space) return;  // nothing to do if space does not increase
  T* p = alloc.allocate(newalloc); // get a new memory allocation for elem
  for (int i = 0; i < sz; ++i) alloc.construct(&p[i], elem[i]); // copy existing elem into new
  for (int i = 0; i < sz; ++i) alloc.destroy (&elem[i]);    // destoy old elem
  alloc.deallocate(elem, space);  // deallocate old elem space
  elem = p;                       // point elem to new memory location
  space = newalloc;               // update space info
} // end of void vector<T, A>::reserve

template<typename T, typename A>
void vector<T, A>::push_back(const T& val) { // page 692
  if (debug.PushBack) {
    if (sz % 100 == 0) {
      Serial.print("\n(debug) push_back line 307 sz=");
      Serial.print(sz);
      Serial.print(" space=");
      Serial.print(space);
    }
  }
  int newSpace = max(space + 4, (int)((float)space * 1.1)); // "magic constants 4 & 1.1"
  if (debug.PushBack) {
    if (sz % 100 == 0) {
      Serial.print("\n(debug) newSpace=");
      Serial.print(newSpace);
    }
  }
  if (debug.PushBack)
    if (sz == space)
      Serial.print("\n(debug) push_back line 274 call reserve " + (String)newSpace);
  if (space == 0) reserve(4);       //start small
  else if (sz >= space) reserve(newSpace); // get more space
  alloc.construct(&elem[sz], val);     // add val at end
  ++sz;                                // increase the size
} // end of void vector<T, A>::push_back

template<typename T, typename A>
void vector<T, A>::resize(uint16_t newsize, T val = T()) { // page 692
  // Cases are:
  // newsize > space: reserve newsize, space = newsize
  // newsize == space: do nothing
  // sz <= newsize < space: destroy elements from newsize up to space, space=newsize
  // newsize < sz: do nothing (do not destroy existing data), space = sz
  reserve(newsize); // add space only if extra is required: OK
  for (int i = sz; i < newsize; ++i) alloc.construct(&elem[i], val); // construct new elements
  for (int i = max(newsize, sz); i < space; ++i) alloc.destroy(&elem[i]); // destroy KH change
  if (newsize < sz) space = sz; else space = newsize; // KH change
  if (debug.Resize) Serial.print("\n(debug) Resize for vector");
} // end of void vector<T, A>::resize

template<typename T, typename A>
void vector<T, A>::setDebugBits() {
      debug.ZeroLength       = 0; // 12
      debug.NonZeroLength    = 0; // 11
      debug.InitializerList  = 0; // 10
      debug.CopyConstructor  = 0; // 9
      debug.MoveConstructor  = 0; // 8
      debug.CopyAssignment   = 0; // 7
      debug.MoveAssignment   = 0; // 6
      debug.Access           = 0; // 5
      debug.OutOfRangeAccess = 0; // 4
      debug.Delete           = 0; // 3
      debug.Resize           = 0; // 2
      debug.Reserve          = 0; // 1
      debug.PushBack         = 0; // 0
    } // end of void setDebugBits()

#endif
// end of file
