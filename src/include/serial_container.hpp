#include <iostream>

template <typename T>
class SerialContainer 
{
public:
	SerialContainer() {
		last_ = 0;
		data_ = new T[last_];
	}

	~SerialContainer() {}

	void push_back(T value) {
		T *new_region = new T[last_ + 1]; // новая область памяти
		for (size_t i = 0; i < last_; ++i) {
			new_region[i] = data_[i]; // копирование элементов
		}
		new_region[last_] = value; // добавление нового элемента
		delete [] data_; // удаление старой области
		data_ = new_region; // сохранение новой в мембер
		last_ += 1; // обновление информации о размере
	}

	void insert(T value, const size_t pos) {
		T *new_region = new T[last_ + 1]; // новая область памяти
		for (size_t i = 0; i < pos; ++i) {
			new_region[i] = data_[i]; // копирование элементов
		}		
		new_region[pos] = value; // добавление нового элемента
		for (size_t i = (pos); i < last_; ++i) {
			new_region[i + 1] = data_[i]; // копирование элементов
		}
		delete [] data_; // удаление старой области
		data_ = new_region; // сохранение новой в мембер
		last_ += 1; // обновление информации о размере
	}

	bool get(const size_t pos, T &out) const 
	{
		if (pos >= last_) 
		{
			// invalid position
			return false;
		}
		out = data_[pos];
		return true;
	}

	T operator[] (const size_t pos) const
    {
		T res;
		this->get(pos, res);	
		if (res) {
			return res;
		} else {
			return (T)NULL;
		}
    }

	bool erase(const size_t pos) 
	{
		if (pos >= last_) 
		{
			// invalid position
			return false;
		}
		// need to move all element after 'pos' to one position to the left
		for (size_t i = pos; i < last_; ++i) 
		{
			data_[i] = data_[i + 1];
		}
		last_--;
		return true;
	}

	void print() {
		size_t j = 0;
		T res;
		std::string delimiter = "";
		while (this->get(j, res)) {
			std::cout << delimiter << res;
			delimiter = ", ";
			j++;
		}
		std::cout << std::endl;
	}

	size_t size() const { return last_; }

private:
	T *data_;
	size_t last_;
};