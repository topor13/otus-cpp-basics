#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <iomanip>
#include <chrono>

#include "include/CRC32.hpp"
#include "include/IO.hpp"

std::mutex resMtx;
std::mutex printMtx;
std::atomic<bool> found{false};
size_t progress = 0;
const size_t maxVal = std::numeric_limits<uint32_t>::max();
uint threadsCount = std::thread::hardware_concurrency();
std::string addedString = "He-he-he";

/// @brief Переписывает последние 4 байта значением value
void replaceLastFourBytes(std::vector<char> &data, uint32_t value) {
  std::copy_n(reinterpret_cast<const char *>(&value), 4, data.end() - 4);
}

void printProgress(const size_t &maxVal) {
  std::lock_guard<std::mutex> lock(printMtx);
  progress += 1;
  if (progress % 10000000 == 0) {
    std::cout << "progress: "
              << std::setprecision(4)
              << 100 * static_cast<double>(progress) / static_cast<double>(maxVal)
              << "%"
              << std::endl;
  }
}

void hackCycle(const size_t startVal,
               const size_t endVal,
               const uint32_t originalCrc32,
               std::vector<char> &result) {
  std::vector<char> intermediate = result;
  for (size_t i = startVal; i < endVal && !found; ++i) {
    // Заменяем последние четыре байта на значение i
    replaceLastFourBytes(intermediate, uint32_t(i));
    // Вычисляем CRC32 текущего вектора result
    auto currentCrc32 = crc32(intermediate.data(), intermediate.size());

    /* Попытался оптимизировать код опираясь на описание метода crc32, однако, 
    * опытным путем выяснил, что
    *     auto currentCrc32 = crc32(intermediate.data() + original.size(),
    *                               intermediate.size() - original.size(),
    *                               originalCrc32);
    * не то же самое, что и 
    *     auto currentCrc32 = crc32(intermediate.data(), intermediate.size());
    */

    if (currentCrc32 == originalCrc32) {
      std::lock_guard<std::mutex> lock(resMtx);
      found = true;
      result = intermediate;
      return;
    }
    // Отображаем прогресс
    printProgress(maxVal);
  }
}

void setOptimalThreadsCount(const std::vector<char> &original,
                            const std::string &injection,
                            const uint32_t originalCrc32) {
  std::vector<std::thread> threadsCountArr;
  uint optimalThreadsCount = 1;
  std::chrono::duration<double> bestElapsedTime;
  size_t fakeMaxVal = 100000;
  size_t fakeBeginVal;
  size_t fakeFinishVal;
  std::chrono::time_point startTime = std::chrono::high_resolution_clock::now();
  std::chrono::time_point endTime = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedTime;

  std::vector<char> fake_result(original.size() + injection.size() + 4);
  auto it = std::copy(original.begin(), original.end(), fake_result.begin());
  std::copy(injection.begin(), injection.end(), it);

  for (uint i = 1; i <= threadsCount; i++)
  {
    fakeBeginVal = 0;
    fakeFinishVal = 0;
    startTime = std::chrono::high_resolution_clock::now();
    for (size_t j = 0; j < i; j++)
    {
      fakeFinishVal += fakeMaxVal / i;
      threadsCountArr.emplace_back(std::thread(hackCycle, fakeBeginVal, fakeFinishVal, originalCrc32, std::ref(fake_result)));
      fakeBeginVal = fakeFinishVal + 1;
    }

    for (size_t j = 0; j < i; j++)
    {
      threadsCountArr[j].join();
    }

    endTime = std::chrono::high_resolution_clock::now();
    elapsedTime = endTime - startTime;
    if (i == 1 || elapsedTime.count() < bestElapsedTime.count())
    {
      bestElapsedTime = elapsedTime;
      optimalThreadsCount = i;
    }

    threadsCountArr.clear();  
  }

  threadsCount = optimalThreadsCount;
  std::cout << "set threads count to optimal: " << optimalThreadsCount << std::endl;
  std::cout << "elapsed time: " << bestElapsedTime.count() << std::endl;
}

/**
 * @brief Формирует новый вектор с тем же CRC32, добавляя в конец оригинального
 * строку injection и дополнительные 4 байта
 * @details При формировании нового вектора последние 4 байта не несут полезной
 * нагрузки и подбираются таким образом, чтобы CRC32 нового и оригинального
 * вектора совпадали
 * @param original оригинальный вектор
 * @param injection произвольная строка, которая будет добавлена после данных
 * оригинального вектора
 * @return новый вектор
 */
std::vector<char> hack(const std::vector<char> &original,
                       const std::string &injection) {
  const uint32_t originalCrc32 = crc32(original.data(), original.size());
  std::vector<char> result(original.size() + injection.size() + 4);
  auto it = std::copy(original.begin(), original.end(), result.begin());
  std::copy(injection.begin(), injection.end(), it);

  /*
   * Внимание: код ниже крайне не оптимален.
   * В качестве доп. задания устраните избыточные вычисления
   */

  size_t beginVal = 0;
  size_t finishVal = 0;
  
  std::vector<std::thread> threadsArr;

  /*
  * Функция для поиска оптимального количества потоков. Замеряем время расчета для каждого количества потоков из возможных
  * и переустанавливаем количество потоков внутри нее
  */
  setOptimalThreadsCount(original, injection, originalCrc32);

  for (size_t j = 0; j < threadsCount; j++)
  {
    finishVal += maxVal / threadsCount;
    threadsArr.emplace_back(std::thread(hackCycle, beginVal, finishVal, originalCrc32, std::ref(result)));
    beginVal = finishVal + 1;
  }

  for (size_t j = 0; j < threadsCount; j++)
  {
    threadsArr[j].join();
  }

  if (found)
  {
    std::cout << "Success\n";
    return result;
  } else {
    throw std::logic_error("Can't hack");
  }
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Call with two args: " << argv[0]
              << " <input file> <output file>\n";
    return 1;
  }

  try {
    const std::vector<char> data = readFromFile(argv[1]);
    const std::vector<char> badData = hack(data, addedString);
    writeToFile(argv[2], badData);
  } catch (std::exception &ex) {
    std::cerr << ex.what() << '\n';
    return 2;
  }
  return 0;
}
