#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// |Farmer| model to bind attributes together.
class Farmer {
 public:
  // Parameterized constructor.
  // Initialize the class attributes from parameters.
  Farmer(string name, string fruit, string city, int quantity)
      : name_(name), fruit_(fruit), city_(city), quantity_(quantity) {}

  // Default constructor.
  Farmer() : name_(""), fruit_(""), city_(""), quantity_(0) {}

  // Getters.
  string& name() { return name_; }
  string& fruit() { return fruit_; }
  string& city() { return city_; }
  int quantity() const { return quantity_; }

 private:
  string name_;
  string fruit_;
  string city_;
  int quantity_;
};

// Actual program implementation.
class Program {
 public:
  Program(int farmer_count) : farmer_count_(farmer_count) {}

  // Take a list of farmers_ from terminal input & store it in
  // array of |Farmer|s.
  void TakeFarmerDataInput() {
    for (int i = 0; i < farmer_count_; i++) {
      cout << "Enter details about farmer " << i + 1 << ":\n";
      string name, fruit, city, quantity;
      cout << "Enter farmer name:";
      getline(cin, name);
      cout << "Enter fruit name:";
      getline(cin, fruit);
      cout << "Enter city name:";
      getline(cin, city);
      cout << "Enter quantity:";
      getline(cin, quantity);
      cout << "\n";
      farmers_.push_back(Farmer(name, fruit, city, stoi(quantity)));
    }
    std::cout << "Entered data:\n";
    for (int i = 0; i < farmers_.size(); i++) {
      char line[400];
      // Padding strings to keep table columns equal.
      sprintf(line, "|%-20s|%-20s|%-20s|%-20d|\n", farmers_[i].name().c_str(),
              farmers_[i].fruit().c_str(), farmers_[i].city().c_str(),
              farmers_[i].quantity());
      cout << line;
    }
  }

  // Save the farmers' data to a text file.
  // |sorted| argument distinguishes the method behavior.
  // |sorted| = true -> save sorted farmer data into `sorted.txt` in tabular
  // manner. |sorted| = false -> save unsorted farmer data into `output.txt` in
  // tabular manner.
  void SaveToNotePad(bool sorted) {
    fstream file(sorted ? "sorted.txt" : "output.txt", ios::out);
    for (Farmer& farmer : (sorted ? GetSortedFarmersArray() : farmers_)) {
      char line[400];
      // Padding strings to keep table columns equal.
      sprintf(line, "|%-20s|%-20s|%-20s|%-20d|\n", farmer.name().c_str(),
              farmer.fruit().c_str(), farmer.city().c_str(), farmer.quantity());
      file << line;
    }
    file.flush();
    file.close();
    cout << "Saved in " << (sorted ? "sorted.txt" : "output.txt") << "\n";
  }

  // Searches a |Farmer| based on its name (using linear search).
  void SearchFarmer(string name) {
    for (int i = 0; i < farmers_.size(); i++) {
      if (farmers_[i].name() == name) {
        cout << "Farmer is FOUND!\n";
        char line[400];
        // Padding strings to make output readable.
        sprintf(line, "|%-20s|%-20s|%-20s|%-20d|\n", farmers_[i].name().c_str(),
                farmers_[i].fruit().c_str(), farmers_[i].city().c_str(),
                farmers_[i].quantity());
        cout << line;
        return;
      }
    }
    cout << "Farmer is NOT FOUND!\n";
  }

 private:
  // Helper function to return sorted array of |Farmer|s based on quantity.
  vector<Farmer> GetSortedFarmersArray() {
    // Deep-copy |farmers_| to |sorted_farmers_array| & return after sorting.
    vector<Farmer> sorted_farmers_array{farmers_.begin(), farmers_.end()};
    // Bubble sort.
    for (int i = 0; i < farmer_count_; i++) {
      for (int j = 0; j < farmer_count_ - i - 1; j++) {
        if (sorted_farmers_array[j].quantity() >
            sorted_farmers_array[j + 1].quantity()) {
          swap(sorted_farmers_array[j], sorted_farmers_array[j + 1]);
        }
      }
    }
    // Equivalent method available in C++'s standard library for sorting.
    // sort(sorted_farmers_array.begin(), sorted_farmers_array.end(),
    //      [](const Farmer& a, const Farmer& b) {
    //        return a.quantity() < b.quantity();
    //      });
    return sorted_farmers_array;
  }

  int farmer_count_;
  vector<Farmer> farmers_;
};

// Entry point of the program.

int main() {
  Program* program = new Program(10);
  // Take farmer data from terminal input.
  program->TakeFarmerDataInput();
  // Save unsorted data to `output.txt`.
  program->SaveToNotePad(false);
  // Save sorted data to `sorted.txt`.
  program->SaveToNotePad(true);
  // Search for a farmer.
  while (true) {
    cout << "Enter farmer name to search:";
    string name;
    getline(cin, name);
    program->SearchFarmer(name);
  }
  delete[] program;
}
