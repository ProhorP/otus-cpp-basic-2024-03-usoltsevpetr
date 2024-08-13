// Read files and prints top k word by frequency

#include <algorithm>
#include <array>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <thread>
#include <unordered_map>
#include <vector>

const size_t TOPK = 10;
const size_t CORES = 4;

using Counter = std::unordered_map<std::string, std::size_t>;

std::string tolower(const std::string& str);

void count_words(std::istream& stream, Counter&);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

Counter* freq_dicts = NULL;

void count_words_thread(std::vector<std::string> files, size_t number) {

    Counter& freq_dict = freq_dicts[number];

    for (auto& file : files) {
        std::ifstream input{file};
        if (!input.is_open()) {
            throw std::runtime_error("Failed to open file " + file);
        }
        count_words(input, freq_dict);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();

    freq_dicts = new Counter[CORES];

    std::array<std::vector<std::string>, CORES> files_threads;

    for (int i = 1; i < argc; ++i) {
        files_threads[i % CORES].push_back(argv[i]);
    }

    std::vector<std::future<void>> wait_list;
    for (size_t i = 0; i < files_threads.size(); i++) {
        wait_list.push_back(std::async(std::launch::async, count_words_thread,
                                       files_threads[i], i));
    }

    for (auto&& res : wait_list) {
        try {
            res.get();
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
            throw;
        }
    }

    for (size_t i = 1; i < CORES; i++) {
        for (auto pair = freq_dicts[i].cbegin(); pair != freq_dicts[i].cend();
             ++pair) {
            freq_dicts[0][pair->first] += pair->second;
        }
        // //Лямбда не работает никак по хэш таблице!!!
        // std::for_each(std::begin(freq_dicts[i]), std::end(freq_dicts[i]),
        //               [](Counter::const_iterator& pair) {
        //                   freq_dicts[0][pair->first] += pair->second;
        //               });
    }

    print_topk(std::cout, freq_dicts[0], TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

std::string tolower(const std::string& str) {
    //Оптимизация: за счет выделения статического буфера и расширения его при необходимости
    static std::string lower_str;
    lower_str.clear();
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::istream& stream, Counter& counter) {
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string& s) { ++counter[tolower(s)]; });
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto& rhs) { return lhs->second > rhs->second; });

    std::for_each(std::begin(words), std::begin(words) + k,
                  [&stream](const Counter::const_iterator& pair) {
                      stream << std::setw(4) << pair->second << " "
                             << pair->first << '\n';
                  });
}