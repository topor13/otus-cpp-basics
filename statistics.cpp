#include <iostream>
#include <limits>
#include <cmath>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void init(double next) = 0;
	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	/* Здесь инициализируется минимум, но с такой инициализацией если не передать в статистику значения от нуля и меньше минимум будет посчитан неправильно
	* Можно инициализировать с помощью max(), но это тоже неправильно, ведь если передать в функцию пустой массив, то в качестве минимума вернется огромное
	* число, которое не передавалось. Здесь и далее я решил инициализировать конструкторы нулями, а при первом прогоне цикла инициализировать переменную
	* первым значением
	* (см. init())
	*
	* Бэкап того что было:
	*	Min() : m_min{std::numeric_limits<double>::min()} {
	*   }
	* 
	*/

	Min() : m_min(0) {
	}

	void init(double next) override {
		m_min = next;
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics {
public:
	Max() : m_max(0) {
	}

	void init(double next) override {
		m_max = next;
	}

	void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char * name() const override {
		return "max";
	}

private:
	double m_max;
};

class Mean : public IStatistics {
public:
	Mean() : m_mean(0), counter(0) {
	}

	void init(double next) override {
		m_mean = next;
		counter = 1;
	}

	void update(double next) override {
		m_mean += next;
		counter += 1;
	}

	double eval() const override {
		return m_mean / counter;
	}

	const char * name() const override {
		return "mean";
	}

private:
	double m_mean;
	int counter;
};

class Std : public IStatistics {
public:
	Std() : m_val(0), m_sqval(0), counter(0) {
	}

	void init(double next) override {
		m_val = next;
		m_sqval = next * next;
		counter = 1;
	}

	void update(double next) override {
		m_val += next;
		m_sqval += next * next;
		counter += 1;
	}

	double eval() const override {
		return sqrt((m_sqval - (pow(m_val, 2) / counter)) / (counter - 1));
	}

	const char * name() const override {
		return "std";
	}

private:
	double m_val;
	double m_sqval;
	int counter;
};

int main() {

	const size_t statistics_count = 4;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};

	double val = 0;
	int counter = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			if (counter == 0) {
				statistics[i]->init(val);
			} else {
				statistics[i]->update(val);
			}	
		}
		counter++;
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}