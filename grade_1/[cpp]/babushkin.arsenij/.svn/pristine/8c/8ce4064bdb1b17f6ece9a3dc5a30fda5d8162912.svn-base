#include "my_vector.h"
#include <algorithm>

MyVector :: MyVector() {
	this->sz = 0;
	this->cp = 2;
	this->data = new int[2];
}

MyVector :: MyVector(std::size_t init_capacity) {
	this->sz = 0;
	this->cp = 2;
	this->data = new int[init_capacity];
}

MyVector :: ~MyVector() {
	delete [] this->data;
}

void MyVector :: set(std::size_t index, int value) {
	this->data[index] = value;
}

int MyVector :: get(std::size_t index) {
	return this->data[index];
}

std::size_t MyVector :: size() {
	return this->sz;
}

std::size_t MyVector :: capacity() {
	return this->cp;
}

void MyVector :: reserve(std::size_t new_capacity) {
	if (new_capacity <= this->cp)
		return;
	int *new_data = new int[new_capacity];
	copy(this->data, new_data);
	std::swap(this->data, new_data);
	delete [] new_data;
	this->cp = new_capacity;
}

void MyVector :: resize(std::size_t new_size) {
	if (new_size <= this->cp) {
		this->sz = new_size;
		return;
	}
	reserve(std::max(new_size, 2 * this->cp));
	while (this->sz < new_size)
		this->data[this->sz++] = 0;
}


void MyVector :: push_back(int value) {
	if (this->sz == this->cp)
		reserve(2 * this->cp);
	this->data[this->sz++] = value;
}

void MyVector :: insert(std::size_t index, int value) {
	if (this->sz == this->cp)
		reserve(2 * this->cp);
	if (index != this->sz)
		rotate(index, index + 1, this->sz + 1);
	this->data[index] = value;
	this->sz++;
}

void MyVector :: erase(std::size_t index) {
	rotate(index, this->sz - 1, this->sz);
	this->sz--;
}

void MyVector :: rotate(std::size_t bg, std::size_t to, std::size_t en) {
	to = en - to;
	reverse(bg, to);
	reverse(to, en);
	reverse(bg, en);
}

void MyVector :: reverse(std::size_t bg, std::size_t en) {
	for (std::size_t it = bg; it < bg + (en - bg) / 2; it++)
		std::swap(this->data[it], this->data[en - (it - bg + 1)]);
}

void MyVector :: copy(int *src, int *dest) {
	for (std::size_t it = 0; it < this->sz; it++)
		dest[it] = src[it];
}