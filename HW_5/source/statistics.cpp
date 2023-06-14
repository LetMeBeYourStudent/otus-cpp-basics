#include <limits>
#include <math.h>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::min()} {
	}

	void update(double next) override {
		if (start_ || next < m_min) {
			m_min = next;
		}
		start_ = false;
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
	bool start_ = true;
};

class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (start_ || next > m_max) {
			m_max = next;
		}
		start_ = false;
	}

	double eval() const override {
		return m_max;
	}

	const char * name() const override {
		return "max";
	}

private:
	double m_max;
	bool start_ = true;
};

class Mean : public IStatistics {
public:
	Mean() : m_sum{0} {
	}

	void update(double next) override {
		m_sum = m_sum + next;
		++count;
	}

	double eval() const override {
		return m_sum / count;
	}

	const char * name() const override {
		return "mean";
	}

private:
	double m_sum;
	int count = 0;
};

class Std : public IStatistics {
public:
	Std() : m_sum{0} {
	}

	void update(double next) override {
		m_squere_sum = m_squere_sum + next * next;
		m_sum = m_sum + next;
		mean_.update(next);
		++count;
	}

	double eval() const override {
		return std::sqrt(
			(
				m_squere_sum -
				2 * m_sum * mean_.eval() +
				(mean_.eval() * mean_.eval()) * count
			) / (count - 1)
		);
	}

	const char * name() const override {
		return "std";
	}

private:
	double m_squere_sum;
	double m_sum;
	Mean mean_ = Mean{};
	int count = 0;
};
