// file testing_vector.ino
// file created 31 August 2019 by farmerkeith
// last update 8 September 2019

// using namespace std;
// using std::sort;
// using std::algorithm::sort;
// using namespace std::algorithm;
// using std::algorithm;
// #include <algorithm>
// using algorithm::sort;
// using std::vector;

#include "Vector_farmerkeith.h" // tab file

template<typename T>
void dualVectorPrint(String leader, vector<T> const &v1, vector<T> const &v2) {
  Serial.print(leader);
  Serial.print("v1 size="); Serial.print(v1.size());
  Serial.print(" v2 size="); Serial.print(v2.size());
  for (int i = 0; i < v1.size(); i++)
    Serial.print(" v1[" + String(i) + "]=" + String(v1[i]));
  for (int i = 0; i < v2.size(); i++)
    Serial.print(" v2[" + String(i) + "]=" + String(v2[i]));
  // Serial.print(Value_type<T>);
  // Serial.print(T::Value_type);
  // if(T=='char') Serial.print("char");
}

class userType {
  public:
    bool bo1{0};
    char ch1{' '};
    int in1{0};
    float fl1{0};
    String st1{""};
    // constructors
    userType (bool bo, char ch, int in, float fl, String st) {
      bo1 = bo;
      ch1 = ch;
      in1 = in;
      fl1 = fl;
      st1 = st;
    }
    userType (bool bo) { bo1 = bo; } // constructor
    userType (char ch) { ch1 = ch; }
    userType (int in)  { in1 = in; }
    userType (float fl) {fl1 = fl; }
    userType (String st) { st1 = st;}
    userType () { } // constructor

    String out() {
      String te = String(bo1) + ' ';
      te += String(ch1) + ' ' + String(in1) + ' ' ;
      te += (String)fl1 + ' ' + st1;
      return te;
    } // end of String ()

/*    String operator()() {
      String te = String(bo1) + ' ';
      te += String(ch1) + ' ' + String(in1) + ' ' ;
      te += (String)fl1 + ' ' + st1;
      return te;
    } // end of String ()
*/
};

// test operation of clear() function
void testClear(bool ve) {
  Serial.print("\nTesting clear function");

  vector<String>vs1{"Happy","go","lucky","friends","enemies"};
  Serial.print("\nline 73 0 string vs1.size()="); Serial.print(vs1.size());
  Serial.print(" vs1.capacity()="); Serial.println(vs1.capacity());
  for (String x : vs1) Serial.println (x);
  Serial.print("\nline 76 String vs1.clear()");
  vs1.clear();
  Serial.print("\nline 78 String vs1.resize(10)");
  vs1.resize(10);
  Serial.print("\nline 80 1 string vs1.size()="); Serial.print(vs1.size());
  Serial.print(" vs1.capacity()="); Serial.println(vs1.capacity());
  for (String x : vs1) Serial.println (x);
  vs1.push_back("String healthy");
  Serial.print("\nline 84 2 string vs1.size()="); Serial.print(vs1.size());
  Serial.print(" vs1.capacity()="); Serial.println(vs1.capacity());
  for (String x : vs1) Serial.println (x);


  vector<userType>vut1{(String)"Happy",(String)"go",(String)"lucky",(String)"friends",(String)"enemies"};
  Serial.print("\nline 90 0 userType vut1.size()="); Serial.print(vut1.size());
  Serial.print(" vut1.capacity()="); Serial.println(vut1.capacity());
  for (userType x : vut1) Serial.println (x.out());
  Serial.print("\nline 93 userType vut1.clear()");
  vut1.clear();
  Serial.print("\nlilne 95 userType vut1.resize(1)");
  vut1.resize(1);
  Serial.print("\nline 97 1 userType vut1.size()="); Serial.print(vut1.size());
  Serial.print(" vut1.capacity()="); Serial.println(vut1.capacity());
  for (userType x : vut1) Serial.println (x.out());
  Serial.print("\nline 100 userType vut1.push_back((String)\"userType healthy\")");
  vut1.push_back((String)"userType healthy");
  Serial.print("\nline 102 2 userType vut1.size()="); Serial.print(vut1.size());
  Serial.print(" vut1.capacity()="); Serial.println(vut1.capacity());
  for (userType x : vut1) Serial.println (x.out());

} // end of void testClear(bool ve) 

// test operation of std::algorithms
void testAlgorithms() {
  // ToDo: test userType
  Serial.println("\n\nline 111 testAlgorithms function");
  vector<int> vi = {5, 7, 9, 4, 6, 8}; // vector from std:
  Serial.print("\n whole vector vi is ");
  for (vector<int>::iterator p = vi.begin(); p < vi.end(); p++) {
    Serial.print(*p);
    Serial.print(' ');
  }
  std::sort (vi.begin(), vi.end()); // sort algorithm from std:

  Serial.print("\n whole vector vi is ");
  for (vector<int>::iterator p = vi.begin(); p < vi.end(); p++) {
    Serial.print(*p);
    Serial.print(' ');
  }
  vector<String> vs1{"Happy", "go", "lucky", "and", "many", "happy", "returns"};
  Serial.print("\n whole vector vs1 is ");
  for (vector<String>::iterator p = vs1.begin(); p < vs1.end(); p++) {
    Serial.print(*p);
    Serial.print(' ');
  }
  Serial.print("\n Sorting vector vs1 results in ");
  std::sort (vs1.begin(), vs1.end()); // sort algorithm from std:

  Serial.print("\n whole vector vs1 is ");
  for (vector<String>::iterator p = vs1.begin(); p < vs1.end(); p++) {
    Serial.print(*p);
    Serial.print(' ');
  }

  Serial.print("\n using Find lucky");
  vector<String>::iterator p = std::find(vs1.begin(), vs1.end(), "lucky");
  Serial.print("\n result is ");
  Serial.print(*p);
  Serial.print(" at position ");
  Serial.print((p - vs1.begin()));

  Serial.print("\n Inserting 'at last' in that position results in ");
  vs1.insert(p, "at last");
  Serial.print("\n resulting vector vs1 is ");
  for (vector<String>::iterator p = vs1.begin(); p < vs1.end(); p++) {
    Serial.print(*p);
    Serial.print(' ');
  }
} // end of void testAlgorithms()

// test operation of iterator
void testIterator() {
  // ToDo: userType test(s)
  Serial.println("\n\nline 159 testIterator function");
  Serial.println("\nline 160 Testing vector<int>::size_type and vector<String>::size_type");
  vector<int> vi1{1, 9, 3, 7, 5};
  vector<String> vs1{"Happy", "go", "lucky", "and", "many", "happy", "returns"};
  for (vector<int>::size_type i = 0; i < vi1.size(); i++) {
    Serial.print(vi1.at(i));
    Serial.print(' ');
  }
  for (vector<String>::size_type i = 0; i < vs1.size(); i++) {
    Serial.print(vs1.at(i));
    Serial.print(' ');
  }
  Serial.print("\n\nline 171 Testing vector<int>::iterator and vector<String>::iterator");
  Serial.print("\n begin points to ");
  Serial.print(*vi1.begin());
  Serial.print(' ');
  Serial.print(*vs1.begin());
  Serial.print("\n end points to ");
  Serial.print(*(vi1.end() - 1));
  Serial.print(' ');
  Serial.print(*(vs1.end() - 1));
  Serial.print("\n whole vector is ");
  for (vector<int>::iterator p = vi1.begin(); p < vi1.end(); p++) {
    Serial.print(*p);
    Serial.print(' ');
  }
  Serial.print("\n whole vector is ");
  for (vector<String>::iterator p = vs1.begin(); p < vs1.end(); p++) {
    Serial.print(*p);
    Serial.print(' ');
  }
  Serial.print("\n\nline 190 Testing range for loop with iterator");
  Serial.print("\n whole vector is "); // page 119
  for (int x : vi1) {
    Serial.print(x);
    Serial.print(' ');
  }
  for (String x : vs1) {
    Serial.print(x);
    Serial.print(' ');
  }
  Serial.print("\n\nline 200 Testing erase function");
  vector<int>::iterator q = vi1.begin() + 1;
  Serial.print("\n item be erased is ");
  Serial.print(*q);
  vector<String>::iterator qs = vs1.begin() + 1;
  Serial.print("\n item be erased is ");
  Serial.print(*qs);
  q = vi1.erase(q);  // erase element 1 (2nd element)
  qs = vs1.erase(qs);  // erase element 1 (2nd element)
  Serial.print("\n whole vector is now "); // page 119
  for (int x : vi1) {
    Serial.print(x);
    Serial.print(' ');
  }
  for (String x : vs1) {
    Serial.print(x);
    Serial.print(' ');
  }
  Serial.print("\n item taking the place of the erased item is ");
  Serial.print(*q);
  Serial.print(" and ");
  Serial.print(*qs);

  Serial.print("\n\nline 223 Testing insert function");
  q = vi1.begin() + 1;
  qs = vs1.begin() + 1;
  Serial.print("\n item to be inserted is 24 and 'anything'");
  q = vi1.insert(q, 24);  // insert at element 1 (2nd element)
  qs = vs1.insert(qs, "anything");  // insert at element 1 (2nd element)
  Serial.print("\n whole vector is now ");
  for (int x : vi1) {
    Serial.print(x);
    Serial.print(' ');
  }
  for (String x : vs1) {
    Serial.print(x);
    Serial.print(' ');
  }
  Serial.print("\n item that was inserted is ");
  Serial.print(*q);
  Serial.print(" and ");
  Serial.print(*qs);

  Serial.println();

} // end of void testIterator()

// test constructors for userType class
void testuserType(bool ve) {
  Serial.println("\n\nline 249 testuserType function");
  userType ut1;
  ut1.st1="Entry";
  userType ut2((bool)1);
  userType ut3('a');
  userType ut4((int)100);
  userType ut5((float)10.5);
  userType ut6((String)"Six");
  userType ut7((bool)1, 'a', (int)75, (float)15.6, "Seven");
  Serial.print("\nPrint user types");
  Serial.print("\nut1.out()="); Serial.print(ut1.out());
  Serial.print("\nut2.out()="); Serial.print(ut2.out());
  Serial.print("\nut3.out()="); Serial.print(ut3.out());
  Serial.print("\nut4.out()="); Serial.print(ut4.out());
  Serial.print("\nut5.out()="); Serial.print(ut5.out());
  Serial.print("\nut6.out()="); Serial.print(ut6.out());
  Serial.print("\nut7.out()="); Serial.print(ut7.out());
} // end of void testuserType(bool ve)

// test constructor for zero length vector:  vector<T> v
void testZeroLength(bool ve) {

  Serial.print("\n\nline 271 Testing zero length vector constructor vector<T> v");
  vector<char> vc1;
  if (ve) {
    Serial.print("\nchar     vc1.size()="); Serial.print(vc1.size());
    for (int i = 0; i <= vc1.size(); i++) {
      Serial.print(" vc1[" + String(i) + "]=");
      // Serial.print(String(vc1[i]));
      Serial.print(String(vc1.at(i)));
    }
  }
  vector<int> vi1;
  if (ve) {
    Serial.print("\nint      vi1.size()="); Serial.print(vi1.size());
    for (int i = 0; i <= vi1.size(); i++) {
      // Serial.print(" vi1[" + String(i) + "]=" + String(vi1[i]));
      Serial.print(" vi1[" + String(i) + "]=" + String(vi1.at(i)));
    }
  }
  vector<double> vd1;
  if (ve) {
    Serial.print("\ndouble   vd1.size()="); Serial.print(vd1.size());
    for (int i = 0; i < vd1.size(); i++) {
      // Serial.print(" vd1[" + String(i) + "]=" + String(vd1[i]));
      Serial.print(" vd1[" + String(i) + "]=" + String(vd1.at(i)));
    }
  }
  vector<String> vs1;
  if (ve) {
    Serial.print("\nString   vs1.size()="); Serial.print(vs1.size());
    for (int i = 0; i <= vs1.size(); i++) {
      // Serial.print(" vs1[" + String(i) + "]=" + String(vs1[i]));
      Serial.print(" vs1[" + String(i) + "]=" + String(vs1.at(i)));
    }
  }
  vector<bool> vb1;
  if (ve) {
    Serial.print("\nbool     vb1.size()="); Serial.print(vb1.size());
    for (int i = 0; i < vb1.size(); i++) {
      // Serial.print(" vb1[" + String(i) + "]=" + String(vb1[i]));
      Serial.print(" vb1[" + String(i) + "]=" + String(vb1.at(i)));
    }
  }
  vector<byte> vy1;
  if (ve) {
    Serial.print("\nbyte     vy1.size()="); Serial.print(vy1.size());
    for (int i = 0; i < vy1.size(); i++) {
      // Serial.print(" vy1[" + String(i) + "]=" + String(vy1[i]));
      Serial.print(" vy1[" + String(i) + "]=" + String(vy1.at(i)));
    }
  }
  vector<uint16_t> vu1;
  if (ve) {
    Serial.print("\nuint16_t vu1.size()="); Serial.print(vu1.size());
    for (int i = 0; i < vu1.size(); i++) {
      Serial.print(" vu1[" + String(i) + "]=" + String(vu1[i]));
    }
  }
  vector<unsigned long> vl1;
  if (ve) {
    Serial.print("\nlong     vl1.size()="); Serial.print(vl1.size());
    for (int i = 0; i < vl1.size(); i++) {
      Serial.print(" vl1[" + String(i) + "]=" + String(vl1[i]));
    }
  }
  vector<float> vf1;
  if (ve) {
    Serial.print("\nfloat    vf1.size()="); Serial.print(vf1.size());
    for (int i = 0; i < vf1.size(); i++) {
      Serial.print(" vf1[" + String(i) + "]=" + String(vf1[i]));
    }
  }
  // Serial.println();

  vector<userType> vut1;
  if (ve) {
    Serial.print("\nuserType vut1.size()="); Serial.print(vut1.size());
     for (int i = 0; i < vut1.size(); i++) {
       Serial.print(" vut1[" + String(i) + "]=" + String(vut1[i].out()));
    }
  }
  Serial.println();
} // end of void testZeroLength()

// test constructor for vector of s elements:  vector<T> v(s)
void testNonZeroLength(bool ve) {
  Serial.print("\n\nline 356 Testing non zero length vector constructor vector<T> v(s)");

  vector<userType> vut1(3);
  if (ve) {
    Serial.print("\nuserType vut1.size()="); Serial.print(vut1.size());
    Serial.print(" vut1.capacity()="); Serial.print(vut1.capacity());
     for (int i = 0; i < vut1.size(); i++) {
       // Serial.print("\n vut1[" + String(i) + "]=" + vut1[i].out());
       Serial.print("\n vut1[" + String(i) + "]=" + vut1.at(i).out());
    }
  }
  Serial.print("\nline 368");
  vector<char> vc1(3);
  if (ve) {
    Serial.print("\nchar     vc1.size()="); Serial.print(vc1.size());
    for (int i = 0; i <= vc1.size(); i++) {
      // Serial.print(" vc1[" + String(i) + "]=" + String(vc1[i]));
      Serial.print(" vc1[" + String(i) + "]=" + String(vc1.at(i)));
    }
  }

  vector<int> vi1(3);
  if (ve) {
    Serial.print("\nint      vi1.size()="); Serial.print(vi1.size());
    for (int i = 0; i <= vi1.size(); i++) {
      // Serial.print(" vi1[" + String(i) + "]=" + String(vi1[i]));
      Serial.print(" vi1[" + String(i) + "]=" + String(vi1.at(i)));
    }
  }

  vector<double> vd1(3);
  if (ve) {
    Serial.print("\ndouble   vd1.size()="); Serial.print(vd1.size());
    for (int i = 0; i < vd1.size(); i++) {
      Serial.print(" vd1[" + String(i) + "]=" + String(vd1[i]));
    }
  }
  vector<String> vs1(3);
  if (ve) {
    Serial.print("\nString   vs1.size()="); Serial.print(vs1.size());
    for (int i = 0; i <= vs1.size(); i++) {
      // Serial.print(" vs1[" + String(i) + "]=" + vs1[i]);
      Serial.print(" vs1[" + String(i) + "]=" + vs1.at(i));
    }
  }
  vector<bool> vb1(3);
  if (ve) {
    Serial.print("\nbool     vb1.size()="); Serial.print(vb1.size());
    for (int i = 0; i < vb1.size(); i++) {
      Serial.print(" vb1[" + String(i) + "]=" + String(vb1[i]));
    }
  }
  vector<byte> vy1(3);
  if (ve) {
    Serial.print("\nbyte     vy1.size()="); Serial.print(vy1.size());
    for (int i = 0; i < vy1.size(); i++) {
      Serial.print(" vy1[" + String(i) + "]=" + String(vy1[i]));
    }
  }
  vector<uint16_t> vu1(3);
  if (ve) {
    Serial.print("\nuint16_t vu1.size()="); Serial.print(vu1.size());
    for (int i = 0; i < vu1.size(); i++) {
      Serial.print(" vu1[" + String(i) + "]=" + String(vu1[i]));
    }
  }
  vector<unsigned long> vl1(3);
  if (ve) {
    Serial.print("\nlong     vl1.size()="); Serial.print(vl1.size());
    for (int i = 0; i < vl1.size(); i++) {
      Serial.print(" vl1[" + String(i) + "]=" + String(vl1[i]));
    }
  }
  vector<float> vf1(3);
  if (ve) {
    Serial.print("\nfloat    vf1.size()="); Serial.print(vf1.size());
    for (int i = 0; i < vf1.size(); i++) {
      Serial.print(" vf1[" + String(i) + "]=" + String(vf1[i]));
    }
  }
  Serial.println();
} // end of void testNonZeroLength()

// test constructor for initializer list vector:  vector<T> v{1,2,3}
void testInitializerListVector(bool ve) {
  Serial.print("\n\nline 441 Testing initializer list vector constructor vector<T> v{1,2,3}");
  vector<userType> vut1{{(String)"Happy"}, {(String)"go"}, {(String)"Lucky"}};
  if (ve) {
    Serial.print("\nline 444 userType vut1.size()="); Serial.print(vut1.size());
    Serial.print(" vut1.capacity()="); Serial.print(vut1.capacity());
    for (int i = 0; i < vut1.size(); i++) {
      Serial.print("\n vut1[" + String(i) + "]=" + vut1.at(i).out());
    }
  }

  vector<char> vc1{'a', 'b', 'c'};
  if (ve) {
    Serial.print("\nchar     vc1.size()="); Serial.print(vc1.size());
    for (int i = 0; i <= vc1.size(); i++) {
      // Serial.print(" vc1[" + String(i) + "]=" + String(vc1[i]));
      Serial.print(" vc1[" + String(i) + "]=" + String(vc1.at(i)));
    }
  }
  vector<int> vi1{1, 2, 3};
  if (ve) {
    Serial.print("\nint      vi1.size()="); Serial.print(vi1.size());
    for (int i = 0; i <= vi1.size(); i++) {
      // Serial.print(" vi1[" + String(i) + "]=" + String(vi1[i]));
      Serial.print(" vi1[" + String(i) + "]=" + String(vi1.at(i)));
    }
  }
  vector<double> vd1{1, 2, 3};
  if (ve) {
    Serial.print("\ndouble   vd1.size()="); Serial.print(vd1.size());
    for (int i = 0; i < vd1.size(); i++) {
      Serial.print(" vd1[" + String(i) + "]=" + String(vd1[i]));
    }
  }
  vector<String> vs1{"Happy", "go", "Lucky"};
  if (ve) {
    Serial.print("\nString   vs1.size()="); Serial.print(vs1.size());
    for (int i = 0; i <= vs1.size(); i++) {
      // Serial.print(" vs1[" + String(i) + "]=" + vs1[i]);
      Serial.print(" vs1[" + String(i) + "]=" + vs1.at(i));
    }
  }
  vector<bool> vb1{1, 0, 1};
  if (ve) {
    Serial.print("\nbool     vb1.size()="); Serial.print(vb1.size());
    for (int i = 0; i < vb1.size(); i++) {
      Serial.print(" vb1[" + String(i) + "]=" + String(vb1[i]));
    }
  }
  vector<byte> vy1{1, 2, 3};
  if (ve) {
    Serial.print("\nbyte     vy1.size()="); Serial.print(vy1.size());
    for (int i = 0; i < vy1.size(); i++) {
      Serial.print(" vy1[" + String(i) + "]=" + String(vy1[i]));
    }
  }
  vector<uint16_t> vu1{1, 2, 3};
  if (ve) {
    Serial.print("\nuint16_t vu1.size()="); Serial.print(vu1.size());
    for (int i = 0; i < vu1.size(); i++) {
      Serial.print(" vu1[" + String(i) + "]=" + String(vu1[i]));
    }
  }
  vector<unsigned long> vl1{1, 2, 3};
  if (ve) {
    Serial.print("\nlong     vl1.size()="); Serial.print(vl1.size());
    for (int i = 0; i < vl1.size(); i++) {
      Serial.print(" vl1[" + String(i) + "]=" + String(vl1[i]));
    }
  }
  vector<float> vf1{1, 2, 3};
  if (ve) {
    Serial.print("\nfloat    vf1.size()="); Serial.print(vf1.size());
    for (int i = 0; i < vf1.size(); i++) {
      Serial.print(" vf1[" + String(i) + "]=" + String(vf1[i]));
    }
  }

  Serial.println();
} // end of void testInitializerListVector()

// test copy constructor:  vector() v1
void testCopyConstructor(bool ve) {
  // ToDo: userType test
  Serial.print("\n\nline 518 Testing copy vector constructor vector<T> v1 = v2;");
  vector<char> vc2{'a', 'b', 'c'};
  vector<char> vc1 = vc2;
  if (ve) {
    Serial.print("\nchar     vc1.size()="); Serial.print(vc1.size());
    for (int i = 0; i <= vc1.size(); i++) {
      // Serial.print(" vc1[" + String(i) + "]=" + String(vc1[i]));
      Serial.print(" vc1[" + String(i) + "]=" + String(vc1.at(i)));
    }
  }
  vector<int> vi2{1, 2, 3};
  vector<int> vi1 = vi2;
  if (ve) {
    Serial.print("\nint      vi1.size()="); Serial.print(vi1.size());
    for (int i = 0; i < vi1.size(); i++) {
      Serial.print(" vi1[" + String(i) + "]=" + String(vi1[i]));
    }
  }
  vector<double> vd2{1, 2, 3};
  vector<double> vd1 = vd2;
  if (ve) {
    Serial.print("\ndouble   vd1.size()="); Serial.print(vd1.size());
    for (int i = 0; i <= vd1.size(); i++) {
      // Serial.print(" vd1[" + String(i) + "]=" + String(vd1[i]));
      Serial.print(" vd1[" + String(i) + "]=" + String(vd1.at(i)));
    }
  }
  vector<String> vs2{"Happy", "go", "Lucky"};
  vector<String> vs1 = vs2;
  if (ve) {
    Serial.print("\nString   vs1.size()="); Serial.print(vs1.size());
    for (int i = 0; i <= vs1.size(); i++) {
      // Serial.print(" vs1[" + String(i) + "]=" + vs1[i]);
      Serial.print(" vs1[" + String(i) + "]=" + vs1.at(i));
    }
  }
  if (vs1.out_of_range()) {
    if (ve) {
      Serial.print("\n\nline 303 Out of range with index=");
      Serial.print(vs1.out_of_range());
      Serial.print(" value=");
      Serial.print(vs1.get_extra());
    }
  }
  vector<bool> vb2{1, 0, 1};
  vector<bool> vb1 = vb2;
  if (ve) {
    Serial.print("\nbool     vb1.size()="); Serial.print(vb1.size());
    for (int i = 0; i < vb1.size(); i++) {
      Serial.print(" vb1[" + String(i) + "]=" + String(vb1[i]));
    }
  }
  vector<byte> vy2{1, 2, 3};
  vector<byte> vy1 = vy2;
  if (ve) {
    Serial.print("\nbyte     vy1.size()="); Serial.print(vy1.size());
    for (int i = 0; i < vy1.size(); i++) {
      Serial.print(" vy1[" + String(i) + "]=" + String(vy1[i]));
    }
  }
  vector<uint16_t> vu2{1, 2, 3};
  vector<uint16_t> vu1 = vu2;
  if (ve) {
    Serial.print("\nuint16_t vu1.size()="); Serial.print(vu1.size());
    for (int i = 0; i < vu1.size(); i++) {
      Serial.print(" vu1[" + String(i) + "]=" + String(vu1[i]));
    }
  }
  vector<unsigned long> vl2{1, 2, 3};
  vector<unsigned long> vl1 = vl2;
  if (ve) {
    Serial.print("\nlong     vl1.size()="); Serial.print(vl1.size());
    for (int i = 0; i < vl1.size(); i++) {
      Serial.print(" vl1[" + String(i) + "]=" + String(vl1[i]));
    }
  }
  vector<float> vf2{1, 2, 3};
  vector<float> vf1 = vf2;
  if (ve) {
    Serial.print("\nfloat    vf1.size()="); Serial.print(vf1.size());
    for (int i = 0; i < vf1.size(); i++) {
      Serial.print(" vf1[" + String(i) + "]=" + String(vf1[i]));
    }
  }
  Serial.println();
} // end of void testCopyConstructor()

// test move constructor:  vector() v1 ?

vector<userType> f1UserType() {
  vector<userType> vut2 {{(char)'a'}, {(char)'b'}, {(char)'c'}};
  return vut2;
} // end of vector<char> f1Char()
vector<char> f1Char() {
  vector<char> vc2 {'a', 'b', 'c'};
  return vc2;
} // end of vector<char> f1Char()
vector<int> f1Int() {
  vector<int> vi2 {1, 2, 3};
  return vi2;
} // end of vector<int> f1Int()
vector<double> f1Double() {
  vector<double> vd2 {1, 2, 3};
  return vd2;
} // end of vector<double> f1Double()
vector<String> f1String() {
  vector<String> vs2 {"Happy", "go", "Lucky"};
  return vs2;
} // end of vector<double> f1Double()

void testMoveConstructor(bool ve) {
  // ToDo: add userType test
  Serial.print("\nline 630 Testing move vector constructor vector v1 = ...v2");
  vector<char> vc1 = f1Char();
  if (ve) {
    Serial.print("\nchar     vc1.size()="); Serial.print(vc1.size());
    for (int i = 0; i <= vc1.size(); i++) {
      // Serial.print(" vc1[" + String(i) + "]=" + String(vc1[i]));
      Serial.print(" vc1[" + String(i) + "]=" + String(vc1.at(i)));
    }
  }
  // Serial.println("\n...");
  vector<int> vi1 = f1Int();
  if (ve) {
    Serial.print("\nint      vi1.size()="); Serial.print(vi1.size());
    for (int i = 0; i < vi1.size(); i++) {
      Serial.print(" vi1[" + String(i) + "]=" + String(vi1[i]));
    }
  }
  // Serial.println("\n...");
  vector<double> vd1 = f1Double();
  if (ve) {
    Serial.print("\ndouble   vd1.size()="); Serial.print(vd1.size());
    for (int i = 0; i < vd1.size(); i++) {
      Serial.print(" vd1[" + String(i) + "]=" + String(vd1[i]));
    }
  }
  // Serial.println("\n...");
  vector<String> vs1 = f1String();
  if (ve) {
    Serial.print("\nstring   vs1.size()="); Serial.print(vs1.size());
    for (int i = 0; i <= vs1.size(); i++) {
      // Serial.print(" vs1[" + String(i) + "]=" + String(vs1[i]));
      Serial.print(" vs1[" + String(i) + "]=" + String(vs1.at(i)));
    }
  }
  // Serial.println("\n...");
} // end of void testMoveConstructor()

// test copy assignment:  v1 = v2
void testCopyAssignment(bool ve) {
  // ToDo: test userType
  Serial.print("\n\n line 670 Testing copy vector assignment v1 = v2");
  vector<char> vc2{'d', 'e', 'f'};
  vector<char> vc1{'a', 'b'};
  if (ve) dualVectorPrint("\nbefore char     ", vc1, vc2);
  vc1 = vc2;
  if (ve) dualVectorPrint("\nafter  char     ", vc1, vc2);
  Serial.println();

  vector<int> vi2{4, 5, 6};
  vector<int> vi1{1, 2};
  if (ve) dualVectorPrint("\nbefore int      ", vi1, vi2);
  vi1 = vi2;
  if (ve) dualVectorPrint("\nafter  int      ", vi1, vi2);
  Serial.println();

  vector<double> vd2{4, 5, 6};
  vector<double> vd1{1, 2};
  if (ve) dualVectorPrint("\nbefore double   ", vd1, vd2);
  vd1 = vd2;
  if (ve) dualVectorPrint("\nafter  double   ", vd1, vd2);
  Serial.println();

  vector<String> vs2{"Happy", "go", "Lucky"};
  vector<String> vs1{"Grumpy"};
  if (ve) dualVectorPrint("\nbefore String   ", vs1, vs2);
  vs1 = vs2;
  if (ve) dualVectorPrint("\nafter  String   ", vs1, vs2);
  Serial.println();

  vector<bool> vb2{1, 0, 1};
  vector<bool> vb1{1};
  if (ve) dualVectorPrint("\nbefore bool     ", vb1, vb2);
  vb1 = vb2;
  if (ve) dualVectorPrint("\nafter  bool     ", vb1, vb2);
  Serial.println();

  vector<byte> vy2{4, 5, 6};
  vector<byte> vy1{1};
  if (ve) dualVectorPrint("\nbefore byte     ", vy1, vy2);
  vy1 = vy2;
  if (ve) dualVectorPrint("\nafter  byte     ", vy1, vy2);
  Serial.println();

  vector<uint16_t> vu2{4, 5, 6};
  vector<uint16_t> vu1{1};
  if (ve) dualVectorPrint("\nbefore uint16_t ", vu1, vu2);
  vu1 = vu2;
  if (ve) dualVectorPrint("\nafter  uint16_t ", vu1, vu2);
  Serial.println();

  vector<unsigned long> vl2{4, 5, 6};
  vector<unsigned long> vl1{1};
  if (ve) dualVectorPrint("\nbefore u long  ", vl1, vl2);
  vl1 = vl2;
  if (ve) dualVectorPrint("\nafter  u long  ", vl1, vl2);
  Serial.println();

  vector<float> vf2{4, 5, 6};
  vector<float> vf1{1};
  if (ve) dualVectorPrint("\nbefore float   ", vf1, vf2);
  vf1 = vf2;
  if (ve) dualVectorPrint("\nafter  float   ", vf1, vf2);
  Serial.println();
} // end of void testCopyAssignment()

// test move assignment:  v1 ? v2
// test destructor - see existing tests, eg test move constructor
// test read access int x = v[i] - see existing tests, eg test copy constructor
// test write access v[i] = x
void testWriteAccess(bool ve) {
  // ToDo: test userType
  Serial.print("\n\nline 741 Testing write access v2 = v1");
  vector<char> vc2{'d', 'e', 'f'};
  vector<char> vc1{'a', 'b', 'x', 'y'};
  // char vc2x = vc2.get_extra();
  // Serial.print("\nline 745 Out of range value=" + (String)vc2x);
  // Serial.print("\n          Correct result is '' (empty string)");
  if (ve) dualVectorPrint("\nbefore char     ", vc1, vc2);
  vc2 = vc1;
  if (ve) dualVectorPrint("\nafter  char     ", vc1, vc2);
  bool x = 0;
  if (ve) Serial.print("\nLine 490 write vc2.at(1, x) = 'm';");
  // vc2[1] = 'm';
  vc2.at(1, x) = 'm';
  if (ve) Serial.print("\n\nOut of range flag=" + (String)x);
  dualVectorPrint("\nafter2 char     ", vc1, vc2);
  if (ve) Serial.print("\nLine 494 write vc2.at(10, x ) = 'p';");
  // vc2[1] = 'p';
  vc2.at(10, x ) = 'p';
  if (ve) Serial.print("\n\nOut of range flag=" + (String)x);
  if (ve) dualVectorPrint("\nafter3 char     ", vc1, vc2);
  if (ve) Serial.print("\nLine 500 write vc2.at(0, x ) = 'r';");
  // vc2[0] = 'r';
  vc2.at(0, x ) = 'r';
  if (ve) Serial.print("\n\nOut of range flag=" + (String)x);
  if (ve) dualVectorPrint("\nafter4 char     ", vc1, vc2);
  int x1 = vc2.out_of_range();
  Serial.print("\nOut of range index=" + (String)x1);
  char x2 = vc2.get_extra();
  Serial.print("\nline 508 Out of range value=" + (String)x2);
  Serial.print("\n         Correct result is 'p'");
  if (ve) Serial.print("\nLine 510 read p = vc2.at(10, x )");
  // char p = vc2[1];
  char p = vc2.at(10, x );
  if (ve) {
    Serial.print("\nLine 514 read result p =" + String(p));
    Serial.print("\n     Correct result is '' (empty string)");
    Serial.println();
  }
  vector<int> vi2{1, 2};
  vector<int> vi1{1, 2, 3};
  if (ve) dualVectorPrint("\nbefore int      ", vi1, vi2);
  vi2 = vi1;
  if (ve) dualVectorPrint("\nafter  int      ", vi1, vi2);
  if (ve) Serial.println();

  vector<double> vd2{1, 2};
  vector<double> vd1{1, 2, 3};
  if (ve) dualVectorPrint("\nbefore double   ", vd1, vd2);
  vd2 = vd1;
  if (ve) dualVectorPrint("\nafter  double   ", vd1, vd2);
  if (ve) Serial.println();
  if (ve) Serial.print("\n\n line 531 starting String out of range testing");
  vector<String> vs2{"Grump"};
  String vs2x = vs2.get_extra();
  Serial.print("\nline 534 Out of range value of vs2=" + vs2x);
  Serial.print("\n                 Correct result is '' (empty string)");
  vector<String> vs1{"Ha", "pp", "y"};
  String vs1x = vs1.get_extra();
  Serial.print("\nOut of range value of vs1=" + vs1x);
  Serial.print("\nOut of range value of vs2=" + vs2x);
  if (ve) dualVectorPrint("\nbefore string   ", vs1, vs2);
  Serial.print("\nline 541");
  vs2 = vs1;
  // Serial.print("\nline 543");
  // vs2x = vs2.get_extra();
  // Serial.println("\nline 545 Out of range value of vs2=");
  // Serial.println(vs2x);
  if (ve) dualVectorPrint("\nafter  string   ", vs1, vs2);
  // vs2x = vs2.get_extra();
  // Serial.println("\nline 549 Out of range value of vs2="); Serial.println(vs2x);
  x = 0;
  if (ve) Serial.print("\nLine 551 write vs2.at(1, x) = 'fort';");
  // vs2[1] = "fort";
  vs2.at(1, x) = "fort";
  vs2x = vs2.get_extra();
  Serial.println("\nline 816 Out of range value of vs2="); Serial.println(vs2x);
  if (ve) Serial.print("\n\nOut of range flag=" + (String)x);
  if (ve) dualVectorPrint("\nafter2 string   ", vs1, vs2);
  if (ve) Serial.print("\nLine 819 write vs2.at(8, x) = 'Out';");
  // vs2[1] = "Out";
  vs2.at(8, x) = "Out";
  Serial.print("\nOut of range flag=" + (String)x);
  Serial.print("\nline 823 Out of range value of vs2=" + vs2.get_extra());
  Serial.print("\n                Correct result is 'Out'");

  if (ve) dualVectorPrint("\nafter3 string   ", vs1, vs2);
  if (ve) Serial.print("\nLine 827 write vs2.at(0, x) = 'Orig';");
  // vs2[0] = "Orig";
  vs2.at(0, x) = "Orig";
  Serial.print("\nOut of range flag=" + (String)x);
  if (ve) dualVectorPrint("\nafter4 string   ", vs1, vs2);
  int sx1 = vs2.out_of_range();
  Serial.print("\nOut of range index of vs2=" + (String)vs2.out_of_range());
  String sx2 = vs2.get_extra();
  Serial.print("\nline 835 Out of range value of vs2=");
  Serial.print(vs2.get_extra());
  Serial.print("\n                Correct result is '' (empty string)");
  if (ve) Serial.print("\nLine 577 read String rvs20 = vs2.at(0, x);");
  // String rvs20 = vs2[0];
  String rvs20 = vs2.at(0, x);
  if (ve) Serial.print("\nOut of range flag=" + (String)x);
  int xs1 = vs2.out_of_range();
  Serial.print("\nOut of range index=" + (String)xs1);
  String xs2 = vs2.get_extra();
  Serial.print("\nline 845 Out of range value=");
  Serial.print(xs2);
  Serial.print("\n         Correct result is '' (empty string)");

  if (ve) Serial.print("\nLine 849 read String rvs28 = vs2.at(8, x);");
  // String rvs28 = vs2[1];
  String rvs28 = vs2.at(8, x);
  if (ve) Serial.print("\nOut of range flag=" + (String)x);
  if (ve) Serial.print("\nLine 592 read result rvs28 =" + String(rvs28));
  xs1 = vs2.out_of_range();
  Serial.print("\nline 594 Out of range index=" + (String)xs1);
  xs2 = vs2.get_extra();
  Serial.print("\nLine 857 Out of range value=");
  Serial.print(xs2);
  Serial.print("\n         Correct result is '' ???");

  if (ve) Serial.println();
} // end of void testWriteAccess()

// test size(): int sz = v.size() // see existing test cases
// test capacity(): int cap = v.capacity()
void testCapacity(bool ve) {
  // ToDo: test userType
  Serial.print("\n\nline 868 Testing capacity()");
  vector<char> vc2{'d', 'e', 'f'};
  vector<char> vc1{'a', 'b', 'x', 'y', 'z'};
  if (ve) {
    Serial.print("\nbefore char     vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
    Serial.print("\nchar     vc2.size()="); Serial.print(vc2.size());
    Serial.print(" vc2.capacity()="); Serial.print(vc2.capacity());
  }
  vc2 = vc1;
  if (ve) {
    Serial.print("\nafter  char     vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
    Serial.print("\nchar     vc2.size()="); Serial.print(vc2.size());
    Serial.print(" vc2.capacity()="); Serial.print(vc2.capacity());
    Serial.println();
  }
} // end of void testCapacity()

// test add new element: push_back (elem)
void testPushBackChar(bool ve) {
  
  Serial.print("\n\nline 627 Testing push_back with char");
  vector<char> vc1;
  if (ve) {
    Serial.print("\n0 char     vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
  }
  vc1.push_back('a');
  if (ve) {
    Serial.print("\n1 char     vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
  }
  vc1.push_back('b');
  if (ve) {
    Serial.print("\n2 char     vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
  }
  vc1.push_back('c');
  if (ve) {
    Serial.print("\n3 char     vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
  }
  vc1.push_back('d');
  if (ve) {
    Serial.print("\n4 char     vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
  }
  vc1.push_back('e');
  if (ve) {
    Serial.print("\n5 char     vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
    Serial.println();
  }
} // end of void testPushBackChar()

// ToDo: test userType push_back
void testPushBackString(bool ve) {
  Serial.print("\n\n line 925 Testing push_back with String");
  vector<String> vs1;
  if (ve) {
    Serial.print("\n0 string   vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.print(vs1.capacity());
    for (int i = 0; i < vs1.size(); i++) {
      String vs1S = vs1[i];
      Serial.print("\nvs1["); Serial.print(i); Serial.print("]=");
      Serial.print(vs1S);
    }
  }
  if (ve) Serial.print("\nline 672 vs1.push_back('Happy')");
  vs1.push_back("Happy");
  if (ve) {
    Serial.print("\n1 string   vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.print(vs1.capacity());
    for (int i = 0; i < vs1.size(); i++) {
      String vs1S = vs1[i];
      Serial.print(" vs1["); Serial.print(i); Serial.print("]=");
      Serial.print(vs1S);
    }
  }
  if (ve) Serial.print("\nline 684 vs1.push_back('go')");
  vs1.push_back("go");
  if (ve) {
    Serial.print("\n2 string   vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.print(vs1.capacity());
    for (int i = 0; i < vs1.size(); i++) {
      String vs1S = vs1[i];
      Serial.print(" vs1["); Serial.print(i); Serial.print("]=");
      Serial.print(vs1S);
    }
  }
  if (ve) Serial.print("\nline 695 vs1.reserve(6)");
  vs1.reserve(6);
  if (ve) {
    Serial.print("\nline 691 Vector vs1 size="); Serial.print(vs1.size());
    Serial.print(" capacity="); Serial.print(vs1.capacity());
    for (int i = 0; i < vs1.size(); i++) {
      String vs1S = vs1[i];
      Serial.print(" vs1["); Serial.print(i); Serial.print("]=");
      Serial.print(vs1S);
    }
  }
  vs1.push_back("Lucky");
  if (ve) {
    Serial.print("\n3 string   vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.print(vs1.capacity());
  }
  vs1.push_back("Grumpy");
  if (ve) {
    Serial.print("\n4 string   vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.print(vs1.capacity());
  }
  vs1.push_back("Dwarf");
  if (ve) {
    Serial.print("\n5 string   vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.print(vs1.capacity());
  }
  if (ve) Serial.println("\nline 713 end of void testPushBackString(bool ve)");
} // end of void testPushBackString(bool ve)

// test change size: reserve (newsize) - see test of push_back()

// test change size: resize (newsize)

void testResizeUserType(bool ve) {
  Serial.print("\n\nline 999 Testing resize userType");
  vector<userType> vut1;
  if (ve) {
    Serial.print("\n0 userType vut1.size()="); Serial.print(vut1.size());
    Serial.print(" vut1.capacity()="); Serial.print(vut1.capacity());
  }
  vut1.push_back('a');
  if (ve) {
    Serial.print("\n1 userType vut1.size()="); Serial.print(vut1.size());
    Serial.print(" vut1.capacity()="); Serial.print(vut1.capacity());
    for (int i = 0; i < vut1.size(); i++)
      Serial.print("\n vut1[" + String(i) + "]=" + (vut1[i].out()));
  }
  vut1.push_back('b');
  if (ve) {
    Serial.print("\n2 userType vut1.size()="); Serial.print(vut1.size());
    Serial.print(" vut1.capacity()="); Serial.print(vut1.capacity());
    for (int i = 0; i < vut1.size(); i++)
      Serial.print("\n vut1[" + String(i) + "]=" + (vut1[i].out()));
  }
  if (ve) Serial.print("\n vut1.clear()");
  vut1.clear();
  if (ve) {
    Serial.print("\n3 userType vut1.size()="); Serial.print(vut1.size());
    Serial.print(" vut1.capacity()="); Serial.print(vut1.capacity());
    for (int i = 0; i < vut1.size(); i++)
      Serial.print("\n vut1[" + String(i) + "]=" + (vut1[i].out()));
  }
  if (ve) Serial.print("\n vut1.resize(3)");
  vut1.resize(3);
  if (ve) {
    Serial.print("\n4 userType vut1.size()="); Serial.print(vut1.size());
    Serial.print(" vut1.capacity()="); Serial.print(vut1.capacity());
    for (int i = 0; i < vut1.size(); i++)
      Serial.print("\n vut1[" + String(i) + "]=" + (vut1[i].out()));
  }
  if (ve) Serial.print("\n vut1.push_back('c')");
  vut1.push_back('c');
  if (ve) {
    Serial.print("\n5 userType vc1.size()="); Serial.print(vut1.size());
    Serial.print(" vut1.capacity()="); Serial.print(vut1.capacity());
    for (int i = 0; i < vut1.size(); i++)
      Serial.print("\n vut1[" + String(i) + "]=" + (vut1[i].out()));
  }
  if (ve) Serial.print("\n vut1.resize(1)");
  vut1.resize(1);
  if (ve) {
    Serial.print("\n6 userType vc1.size()="); Serial.print(vut1.size());
    Serial.print(" vut1.capacity()="); Serial.print(vut1.capacity());
    for (int i = 0; i < vut1.size(); i++)
      Serial.print("\n vut1[" + String(i) + "]=" + (vut1[i].out()));
  }
  if (ve) Serial.print("\n vut1.push_back('d')");
  vut1.push_back('d');
  if (ve) {
    Serial.print("\n7 userType vut1.size()="); Serial.print(vut1.size());
    Serial.print(" vut1.capacity()="); Serial.print(vut1.capacity());
    for (int i = 0; i < vut1.size(); i++)
      Serial.print("\n vut1[" + String(i) + "]=" + (vut1[i].out()));
    Serial.println();
  }
} // end of void testResizeUserType()


void testResizeChar(bool ve) {
  Serial.print("\n\nline 993 Testing resize char");
  vector<char> vc1;
  if (ve) {
    Serial.print("\n0 char vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
  }
  vc1.push_back('a');
  if (ve) {
    Serial.print("\n1 char vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
    for (int i = 0; i < vc1.size(); i++)
      Serial.print(" vc[" + String(i) + "]=" + String(vc1[i]));
  }
  vc1.push_back('b');
  if (ve) {
    Serial.print("\n2 char vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
    for (int i = 0; i < vc1.size(); i++)
      Serial.print(" vc1[" + String(i) + "]=" + String(vc1[i]));
  }
  if (ve) Serial.print("\n vc1.resize(3)");
  vc1.resize(3);
  if (ve) {
    Serial.print("\n3 char vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
    for (int i = 0; i < vc1.size(); i++)
      Serial.print(" vc1[" + String(i) + "]=" + String(vc1[i]));
  }
  vc1.push_back('c');
  if (ve) {
    Serial.print("\n4 char vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
    for (int i = 0; i < vc1.size(); i++)
      Serial.print(" vc1[" + String(i) + "]=" + String(vc1[i]));
  }
  if (ve) Serial.print("\n vc1.resize(1)");
  vc1.resize(1);
  vc1.push_back('d');
  if (ve) {
    Serial.print("\n5 char vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.print(vc1.capacity());
    for (int i = 0; i < vc1.size(); i++)
      Serial.print(" vc1[" + String(i) + "]=" + String(vc1[i]));
    Serial.println();
  }
} // end of void testResizeChar()

void testResizeInt(bool ve) {
  Serial.print("\n\nline 1041 Testing resize int");
  vector<int> vi1;
  if (ve) {
    Serial.print("\n0 int  vi1.size()="); Serial.print(vi1.size());
    Serial.print(" vi1.capacity()="); Serial.print(vi1.capacity());
  }
  vi1.push_back(1);
  if (ve) {
    Serial.print("\n1 int  vi1.size()="); Serial.print(vi1.size());
    Serial.print(" vi1.capacity()="); Serial.print(vi1.capacity());
    for (int i = 0; i < vi1.size(); i++)
      Serial.print(" vc[" + String(i) + "]=" + String(vi1[i]));
  }
  vi1.push_back(2);
  if (ve) {
    Serial.print("\n2 int  vi1.size()="); Serial.print(vi1.size());
    Serial.print(" vi1.capacity()="); Serial.print(vi1.capacity());
    for (int i = 0; i < vi1.size(); i++)
      Serial.print(" vi1[" + String(i) + "]=" + String(vi1[i]));
  }
  if (ve) Serial.print("\n vi1.resize(3)");
  vi1.resize(3);
  if (ve) {
    Serial.print("\n3 int  vi1.size()="); Serial.print(vi1.size());
    Serial.print(" vi1.capacity()="); Serial.print(vi1.capacity());
    for (int i = 0; i < vi1.size(); i++)
      Serial.print(" vi1[" + String(i) + "]=" + String(vi1[i]));
  }
  vi1.push_back(3);
  if (ve) {
    Serial.print("\n4 int  vi1.size()="); Serial.print(vi1.size());
    Serial.print(" vi1.capacity()="); Serial.print(vi1.capacity());
    for (int i = 0; i < vi1.size(); i++)
      Serial.print(" vi1[" + String(i) + "]=" + String(vi1[i]));
  }
  if (ve) Serial.print("\n vi1.resize(1)");
  vi1.resize(1);
  vi1.push_back(4);
  if (ve) {
    Serial.print("\n5 int  vi1.size()="); Serial.print(vi1.size());
    Serial.print(" vi1.capacity()="); Serial.print(vi1.capacity());
    for (int i = 0; i < vi1.size(); i++)
      Serial.print(" vi1[" + String(i) + "]=" + String(vi1[i]));
    Serial.println();
  }
} // end of void testResizeInt()

void testResizeString(bool ve) {
  Serial.print("\n line 1088 Testing resize String");
  vector<String> vs1; // (2);
  // vector<String> vs1{"Initial string", "Initial string2"}; // (2);
  // vector<String> vs1(2); // {"Happy","go"};
  if (ve) {
    Serial.print("\n0 string vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.print(vs1.capacity());
    Serial.print("\n vs1.resize(5)");
  }
  vs1.resize(5);
  if (ve) {
    Serial.print("\n1 string vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.print(vs1.capacity());
  }
  for (int i = 0; i < vs1.size(); i++)
    if (ve) {
      Serial.print(" vs1[" + String(i) + "]=" + String(vs1[i]));
    }
  vs1.push_back("Happy");
  if (ve) {
    Serial.print("\n1 string vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.print(vs1.capacity());
    for (int i = 0; i < vs1.size(); i++)
      Serial.print(" vc[" + String(i) + "]=" + String(vs1[i]));
  }
  vs1.push_back("go");
  if (ve) {
    Serial.print("\n2 string vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.print(vs1.capacity());
    for (int i = 0; i < vs1.size(); i++)
      Serial.print(" vs1[" + String(i) + "]=" + String(vs1[i]));
  }
  if (ve) Serial.print("\n vs1.resize(3)");
  vs1.resize(3);
  if (ve) {
    Serial.print("\n3 string vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.print(vs1.capacity());
    for (int i = 0; i < vs1.size(); i++)
      Serial.print(" vs1[" + String(i) + "]=" + String(vs1[i]));
  }
  if (ve) Serial.print("\n adding 'as a' to vs1[0]");
  vs1[0] += " as a";
  vs1.push_back("Lucky");
  if (ve) {
    Serial.print("\n4 string vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.print(vs1.capacity());
    for (int i = 0; i < vs1.size(); i++)
      Serial.print(" vs1[" + String(i) + "]=" + String(vs1[i]));
  }
  if (ve) Serial.print("\n vs1.resize(1)");
  vs1.resize(1);
  vs1.push_back("Grumpy");
  if (ve) {
    Serial.print("\n5 string vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.print(vs1.capacity());
    for (int i = 0; i < vs1.size(); i++)
      Serial.print(" vs1[" + String(i) + "]=" + String(vs1[i]));
  }
  if (ve) Serial.println();
} // end of void testResizeString(bool ve)

// test large vectors
void testLargeVectors(bool ve) {
  // ToDo: test userType
  Serial.print("\n line 1153 testing LargeVectors");
  Serial.print("\n line 1154 testing LargeVectors char");
  int large = 900; // 600 crash at 2000?
  vector<char>vc1;
  for (int i = 0; i < large; i++) {
    vc1.push_back(char((i % 26) + 'a'));
  }
  if (ve) {
    Serial.print("\n0 char   vc1.size()="); Serial.print(vc1.size());
    Serial.print(" vc1.capacity()="); Serial.println(vc1.capacity());
  }
  // for(int i=0; i<vc1.size(); i++) {
  //   Serial.print(" vc1[" + String(i) + "]=" + String(vc1[i]));
  //   if((i+1)%8==0) Serial.println();
  // }

  Serial.print("\n line 1169 testing LargeVectors int");
  vector<int>vi1;
  for (int i = 0; i < large; i++) {
    vi1.push_back(i);
  }
  if (ve) {
    Serial.print("\n0 int    vi1.size()="); Serial.print(vi1.size());
    Serial.print(" vi1.capacity()="); Serial.println(vi1.capacity());
  }
  // for(int i=0; i<vi1.size(); i++) {
  //   Serial.print(" vi1[" + String(i) + "]=" + String(vi1[i]));
  //   if((i+1)%7==0) Serial.println();
  // }

  Serial.print("\n line 1183 testing LargeVectors String");
  vector<String>vs1;
  for (int i = 0; i < large; i++) {
    vs1.push_back(String(i));
  }
  if (ve) {
    Serial.print("\n0 string vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.println(vs1.capacity());
  }
  // for(int i=0; i<vs1.size(); i++) {
  //   Serial.print(" vs1[" + String(i) + "]=" + String(vs1[i]));
  //   if((i+1)%7==0) Serial.println();
  // }
} // end of void testLargeVectors(bool ve)


// test memory leak
void  testMemoryLeak(bool ve) {
  int large = 1200; // max 1400
  // ToDo: test userType
  Serial.print("\n line 1203 testing for memory leak with a String vector");
  // vector<String>vs1(10);         // create 100 size empty vector
  // vector<String>vs1(large);       // create full size empty vector
  vector<String>vs1;              // create zero-length vector
  for (int i = 0; i < large; i++) {   // push-back "large" times
    vs1.push_back(String(i));
  }
  if (ve) {
    Serial.print("\n0 line 943 string vs1.size()="); Serial.print(vs1.size());
    Serial.print(" vs1.capacity()="); Serial.println(vs1.capacity());
  }
  // for (int i = 0; i < vs1.size(); i++) {
  //   Serial.print(" vs1[" + String(i) + "]=" + String(vs1[i]));
  //   if ((i + 1) % 7 == 0) Serial.println();
  // }
} // end of void testMemoryLeak(bool ve)

void checkVectorSize(bool ve) {
  // ToDo: add userType
  vector<bool> vb;
  bool bx2 = vb.get_extra();
  if (ve) Serial.print("\nline 1224 bool  bx2=" + (String)bx2);
  vector<char> vc;
  char cx2 = vc.get_extra();
  if (ve) Serial.print("\nline 1227 char cx2=" + (String)cx2);
  vector<int> vi;
  int ix2 = vi.get_extra();
  if (ve) Serial.print("\nline 1230 int ix2=" + (String)ix2);
  vector<double> vd;
  double dx2 = vd.get_extra();
  if (ve) Serial.print("\nline 1233 double dx2=" + (String)dx2);
  vector<String> vs{"Happy"};
  String sx2 = vs.get_extra();
  if (ve) Serial.print("\nline 1236 string sx2=" + sx2);

  Serial.print("\nSize of vector<bool>   is " + (String)sizeof(vector<bool>) + ' ' + (String)sizeof(vb));
  Serial.print("\nSize of vector<char>   is " + (String)sizeof(vector<char>) + ' ' + (String)sizeof(vc));
  Serial.print("\nSize of vector<int>    is " + (String)sizeof(vector<int>) + ' ' + (String)sizeof(vi));
  Serial.print("\nSize of vector<double> is " + (String)sizeof(vector<double>) + ' ' + (String)sizeof(vd));
  Serial.print("\nSize of vector<String> is " + (String)sizeof(vector<String>) + ' ' + (String)sizeof(vs));
  
} // end of void checkVectorSize()

void setup() {
  Serial.begin(115200);
  Serial.print("\nStarting testing_vector.ino");
  // testZeroLength(1);          // line 45
  // testNonZeroLength(1);        // line 96
  // testInitializerListVector(1); // line 147
  testResizeUserType(1);
  // testResizeString(1); // line 625
  // testResizeInt(1);      // line 589
  // testResizeChar(1);     // line 553
  testClear(1);
  // testuserType(1);
/*
  testAlgorithms();
  testIterator();
  checkVectorSize(1);
  testLargeVectors(1); // line 672
  testMemoryLeak(1);   // line 714
  testPushBackString(0); // line 445
  testPushBackChar(0);   // line 480
  testCapacity(0);       // line 463
  testWriteAccess(0);    // line 380
  testMoveConstructor(0); // line 282
  testCopyAssignment(0);  // line 310
  testCopyConstructor(0); // line 198
*/
  Serial.print("\nEnd of setup test series");
  Serial.println("\nEnd of setup");
} // end of setup()

void loop() {
  static int counter = 0;
  counter++;
  if (counter % 100 == 0) delay(879);
  else delay(400); // 120 ms for testMemoryLeak function, total 1000 ms
  testLargeVectors(0);  // indefinite
  testMemoryLeak(0);    // indefinite

  /*
    testResizeString(0);
    testPushBackString(0); // line 445

    testResizeInt(0);
    testResizeChar(0);

    testPushBackChar(0);
    testCapacity(0);

    testWriteAccess(0); // 166 solo

    testMoveConstructor(0);
    testCopyAssignment(0);

    testCopyConstructor(0);
  */
  // testInitializerListVector(0);
  // testNonZeroLength(0);
  // testZeroLength(0);
  Serial.print("\nEnd of loop() test series,  time is ");
  Serial.print((float)millis() / 1000, 3);
  Serial.println(" counter="  + String(counter));
} // end of loop()
// end of file
