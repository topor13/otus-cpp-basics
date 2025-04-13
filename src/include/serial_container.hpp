#include <iostream>

template <typename T>
class SerialContainer 
{
public:
	SerialContainer() {
		m_size = 0;
		m_data = new T[m_size];
	}

	~SerialContainer() {
		if (this->m_data) {
			delete[] this->m_data;
		}
		this->m_data = nullptr;
		this->m_size = 0;
	}

	void push_back(T value) {
		T *new_region = new T[m_size + 1]; // новая область памяти
		for (size_t i = 0; i < m_size; ++i) {
			new_region[i] = m_data[i]; // копирование элементов
		}
		new_region[m_size] = value; // добавление нового элемента
		delete [] m_data; // удаление старой области
		m_data = new_region; // сохранение новой в мембер
		m_size += 1; // обновление информации о размере
	}

	void insert(T value, const size_t pos) {
		T *new_region = new T[m_size + 1]; // новая область памяти
		for (size_t i = 0; i < pos; ++i) {
			new_region[i] = m_data[i]; // копирование элементов
		}		
		new_region[pos] = value; // добавление нового элемента
		for (size_t i = (pos); i < m_size; ++i) {
			new_region[i + 1] = m_data[i]; // копирование элементов
		}
		delete[] m_data; // удаление старой области
		m_data = new_region; // сохранение новой в мембер
		m_size += 1; // обновление информации о размере
	}

	void push_front(T value) {
		this->insert(value, 0);
    }

	bool get(const size_t pos, T &out) const 
	{
		if (pos >= m_size) 
		{
			// invalid position
			return false;
		}
		out = m_data[pos];
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
		if (pos >= m_size) 
		{
			// invalid position
			return false;
		}
		// need to move all element after 'pos' to one position to the left
		for (size_t i = pos; i < m_size; ++i) 
		{
			m_data[i] = m_data[i + 1];
		}
		m_size--;
		return true;
	}

	bool pop_back() {
		return this->erase(this->m_size - 1);
	}

	bool pop_front() {
		return this->erase(0);
	}

	bool clear()
	{
		if (this->m_data)
		{
			delete[] this->m_data;
		}
		this->m_size = 0;
		this->m_data = new T[m_size];
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

	size_t size() const { return m_size; }

private:
	T *m_data;
	size_t m_size;
};
