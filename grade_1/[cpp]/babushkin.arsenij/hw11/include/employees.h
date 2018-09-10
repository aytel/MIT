#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Employee {
public:
  Employee(){};
  virtual ~Employee(){};
  virtual int salary() const = 0;
  friend std::ostream& operator<< (std::ostream& os, Employee *e);
  friend std::istream& operator>> (std::istream& is, Employee *e);
protected:
  std::string name;
  int32_t base_salary;
public:
  virtual void write(std::ostream &os) const = 0;
  virtual void read(std::istream &is) = 0;
  virtual void writeb(std::ofstream &os) const = 0;
  virtual void readb(std::ifstream &is) = 0;
};

std::ostream& operator<< (std::ostream& os, Employee *e);
std::istream& operator>> (std::istream& is, Employee *e);

class Developer : public Employee {
public:
  Developer(){};
  ~Developer() override {};
  int salary() const override;
private:
  bool has_bonus;
public:
  void write(std::ostream &os) const override;
  void read(std::istream &is) override;
  void writeb(std::ofstream &os) const override;
  void readb(std::ifstream &is) override;
};

class SalesManager : public Employee {
public:
  SalesManager(){};
  ~SalesManager() override {};
  int salary() const override;
private:
  int32_t sold_nm, price;
public:
  void write(std::ostream &os) const override;
  void read(std::istream &is) override;
  void writeb(std::ofstream &os) const override;
  void readb(std::ifstream &is) override;
};

class EmployeesArray {
public:
  EmployeesArray();
  ~EmployeesArray();
  void add(Employee *e);
  void load(std::ifstream &is);
  void save(std::ofstream &os) const;
  int total_salary() const;
  int size() const;
  friend std::ostream& operator<< (std::ostream& os, EmployeesArray &e);
  friend std::istream& operator>> (std::istream& is, EmployeesArray &e);
  Employee*& operator[] (int i);
private:
  Employee **employees;
  int total, sz, cap;
};

std::ostream& operator<< (std::ostream& os, EmployeesArray &e);
std::istream& operator>> (std::istream& is, EmployeesArray &e);

#endif