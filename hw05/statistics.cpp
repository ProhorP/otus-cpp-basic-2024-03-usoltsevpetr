#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

class IStatistics {
  public:
    virtual ~IStatistics() {}

    virtual void update(double next) = 0;
    virtual double eval() const = 0;
    virtual const char* name() const = 0;
};

class Min : public IStatistics {
  public:
    Min() : m_min{0}, first{true} {}

    void update(double next) override {
        if (first || next < m_min) {
            m_min = next;
        }
        first = false;
    }

    double eval() const override {
        return m_min;
    }

    const char* name() const override {
        return "min";
    }

  private:
    double m_min;
    bool first;
};

class Max : public IStatistics {
  public:
    Max() : m_max{0}, first{true} {}

    void update(double next) override {
        if (first || next > m_max) {
            m_max = next;
        }
        first = false;
    }

    double eval() const override {
        return m_max;
    }

    const char* name() const override {
        return "max";
    }

  private:
    double m_max;
    bool first;
};

class Mean : public IStatistics {
  public:
    Mean() : cnt{0}, sum{0} {}

    void update(double next) override {
        cnt++;
        sum += next;
    }

    double eval() const override {
        if (cnt == 0)
            return 0;
        else
            return sum / cnt;
    }

    const char* name() const override {
        return "mean";
    }

  private:
    double cnt;
    double sum;
};

class Std : public IStatistics {
  public:
    Std() = default;

    void update(double next) override {
        line.push_back(next);
    }

    double eval() const override {

        Mean mean;
        for (auto& entry : line)
            mean.update(entry);
        double mean_value = mean.eval();

        Mean mean_square;
        for (auto& entry : line) {
            mean_square.update(pow(entry - mean_value, 2));
        }

        return sqrt(mean_square.eval());
    }

    const char* name() const override {
        return "std";
    }

  private:
    std::vector<double> line;
};

class pct : public IStatistics {
  public:
    pct(double percent) : percent{percent} {};

    void update(double next) override {
        line.push_back(next);
    }

    double eval() const override {

        std::vector<double> sort_line(line);
        std::sort(sort_line.begin(), sort_line.end());
        double step = 100.0 / static_cast<double>(sort_line.size());
        double cur_percent = 0;
        size_t index = 0;
        while (index != sort_line.size()) {
            cur_percent += step;
            if (cur_percent > percent)
                break;
            ++index;
        }

        return sort_line[index];
    }

    const char* name() const override {
        return "pct";
    }

  private:
    std::vector<double> line;
    double percent;
};

class pct90 : public pct {
  public:
    pct90() : pct(90.0) {};

    void update(double next) override {
        pct::update(next);
    }

    double eval() const override {
        return pct::eval();
    }

    const char* name() const override {
        return "pct90";
    }

};

class pct95 : public pct {
  public:
    pct95() : pct(95.0) {};

    void update(double next) override {
        pct::update(next);
    }

    double eval() const override {
        return pct::eval();
    }

    const char* name() const override {
        return "pct95";
    }

};

int main() {

    const size_t statistics_count = 6;
    IStatistics* statistics[statistics_count];

    statistics[0] = new Min{};
    statistics[1] = new Max{};
    statistics[2] = new Mean{};
    statistics[3] = new Std{};
    statistics[4] = new pct90();
    statistics[5] = new pct95();

    double val = 0;
    while (std::cin >> val) {
        for (auto& statistic : statistics) {
            statistic->update(val);
        }
    }

    // Handle invalid input data
    if (!std::cin.eof() && !std::cin.good()) {
        std::cerr << "Invalid input data\n";
        return 1;
    }

    // Print results if any
    for (auto& statistic : statistics) {
        std::cout << statistic->name() << " = " << statistic->eval()
                  << std::endl;
    }

    // Clear memory - delete all objects created by new
    for (auto& statistic : statistics) {
        delete statistic;
    }

    return 0;
}