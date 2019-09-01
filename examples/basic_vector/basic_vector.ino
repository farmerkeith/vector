// basic example of vector_farmerkeith
#include <Vector_farmerkeith.h>

void setup() {
  Serial.begin(115200);
  Serial.println("\nVector basic example");
  // example of a String vector
  Serial.print("\nCreating a new string vector");
  vector<String> vs{"Happy", "go", "lucky"};
  Serial.print("\nSize of vector vs is: ");
  Serial.print(vs.size());
  Serial.print("\nContents of vector vs elements is ");
  for (int i = 0; i < vs.size(); i++) {
    Serial.print(vs.at(i));
    Serial.print(' ');
  }
  Serial.print("\n\nAdd a new element at the end of the vector");
  vs.push_back("Grumpy");
  Serial.print("\nSize of vector vs is: ");
  Serial.print(vs.size());
  Serial.print("\nContents of vector vs elements is ");
  for (int i = 0; i < vs.size(); i++) {
    Serial.print(vs.at(i));
    Serial.print(' ');
  }

  Serial.print("\n\nCreating a new vector of floats");
  vector<float> vf{1, 2.1, 1002.5, 45};
  Serial.print("\nSize of vector vf is: ");
  Serial.print(vf.size());
  Serial.print("\nContents of vector vf elements is ");
  for (int i = 0; i < vf.size(); i++) {
    Serial.print(vf.at(i));
    Serial.print(' ');
  }
  Serial.print("\n\nAdd a new element at the end of the vector");
  vf.push_back(25);
  Serial.print("\nSize of vector vf is: ");
  Serial.print(vf.size());
  Serial.print("\nContents of vector vf elements is ");
  for (int i = 0; i < vf.size(); i++) {
    Serial.print(vf.at(i));
    Serial.print(' ');
  }
  Serial.print("\n\nVector works with all standard data types such as");
  Serial.print("\nString, int, float, double, long, bool, etc.");
  Serial.print("\nand also with user-defined types.");
  
}


void loop() {
}
