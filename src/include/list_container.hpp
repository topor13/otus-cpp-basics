#include <iostream>

template <typename T>
class ListContainer 
{
public:
	ListContainer() {
		m_size = 0;
		m_last = nullptr;
		m_first = nullptr;
	}

    void push_back(T value) {
        Node* new_node = new Node{}; // создание нового узла
        new_node->prev = m_last; // предыдущим элементом станет последний
        new_node->next = nullptr; // следующего элемента пока нет
        new_node->data = value; // сохраняем пользовательские данные
		if (m_last) {
			m_last->next = new_node; //обновляем указатель на следующий узел для предпоследнего элемента если он есть
		}
		m_last = new_node; // обновляем указатель на последний
		if (m_size == 0) {
			m_first = m_last; //сохраняем ссылку на первый элемент если это первое добавление
		}
        m_size += 1; // обновляем размер
    }

	void insert(T value, const size_t pos) {
		Node* new_node = new Node{}; // создание нового узла
		new_node->data = value; // сохраняем пользовательские данные
		if (m_size == 0) {
			new_node->prev = nullptr; // В случае если это первый элемент
			new_node->next = nullptr;
		} else {
			Node* next_node = ListContainer::get_internal(pos); // следующий узел
			Node* prev_node = ListContainer::get_internal(pos - 1); // предыдущий узел

			if (prev_node) {
				prev_node->next = new_node;
				new_node->prev = prev_node;
			} else {
				new_node->prev = nullptr; //если это первый элемент
			}

			if (next_node) {
				next_node->prev = new_node;
				new_node->next = next_node;
			} else {
				new_node->next = nullptr; //если это последний элемент
			}
		}
		m_size += 1;
	}

	bool get(const size_t pos, T &out) const 
	{
		if (pos >= m_size)
		{
			// invalid position
			return false;
		}
		Node *tmp_node = ListContainer::get_internal(pos);
		
		if (tmp_node) {
			out = tmp_node->data;
			return true;
		} else {
			return false;
		}
		
	}

	T operator[] (const size_t pos) const
    {
		Node *tmp_node = ListContainer::get_internal(pos);	
		if (tmp_node) {
			return tmp_node->data;
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
		
		// need to drop struct on 'pos' and move all element after 'pos' to one position to the left
		Node *drop_node = m_last;
		Node *next_node = nullptr;
		Node *prev_node = nullptr;
		for (size_t i = (m_size - 1); i >= 0; --i) {
			if (i == pos) {
				prev_node = drop_node->prev;
				next_node = drop_node->next;

				if (prev_node) {
					prev_node->next = next_node;
				}
				if (next_node) {
					next_node->prev = prev_node;
				}

				delete drop_node;
				break;
			}
			drop_node = drop_node->prev;
		}

		m_size--;
		return true;
	}

	void print() {
		int j = 0;
		int res;
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
	struct Node {
		Node* next; // указатель на следующий элемент Node
		Node* prev; // указатель на предыдущий элемент Node
		T data; // пользовательские данные (хранимый объект)
	};
    Node *m_last;
	Node *m_first;
	size_t m_size;

	Node* get_internal(const size_t pos) const 
	{
		if (pos >= m_size)
		{
			// invalid position
			return nullptr;
		}
		Node *tmp_node = m_last;

		for (size_t i = (m_size - 1); i >= 0; --i) {
			if (i == pos) {
				return tmp_node;
			}
			tmp_node = tmp_node->prev;
		}
	}
};