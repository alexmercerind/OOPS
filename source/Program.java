import java.lang.System;

// * Provides a label.
// * Responsible for runtime-polymorphism.
// * Identifies the type of the object using superclass.
// * "discriminator part".
interface SalaryCalculator {
  public double calculateSalary();
}

class CategoryA implements SalaryCalculator {
  double basicSalary, da;

  // Parameterized constructor.
  CategoryA(double basicSalary, double da) {
    this.basicSalary = basicSalary;
    this.da = da;
  }

  // Implement the calculateSalary from SalaryCalculator interface.
  public double calculateSalary() {
    return (basicSalary + da);
  }
}

class CategoryB implements SalaryCalculator {
  double basicSalary;
  int salesQuanitity;
  static final double commision = 0.5;

  // Parameterized constructor.
  CategoryB(double basicSalary, int salesQuanitity) {
    this.basicSalary = basicSalary;
    this.salesQuanitity = salesQuanitity;
  }

  // Implement the calculateSalary from SalaryCalculator interface.
  public double calculateSalary() {
    return (basicSalary + (salesQuanitity * commision));
  }
}

class Employee {
  String name;
  SalaryCalculator salaryCalculator;

  // Take the employee's name as String & the reference to instance of
  // SalaryCalculator to store the employee's type.
  Employee(String name, SalaryCalculator salaryCalculator) {
    this.name = name;
    this.salaryCalculator = salaryCalculator;
  }

  // Display method to display the employee's name and salary.
  void display() {
    System.out.println("Name: " + name);
    System.out.println("Salary: " + salaryCalculator.calculateSalary());
  }
}

public class Program {
  public static void main(String[] args) {
    CategoryA categoryA = new CategoryA(10000, 4000);
    CategoryB categoryB = new CategoryB(4000, 200);
    Employee employee1 = new Employee("Kritika", categoryA);
    employee1.display();
    Employee employee2 = new Employee("Sumit", categoryB);
    employee2.display();
  }
}