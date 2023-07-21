#pragma once

#include <stddef.h>

// Uncomment this line when using print() method.


namespace mtrn3100
{

    template <typename T, size_t N>
    class MovingAverageFilter
    {
    public:
        // Adds a data sample to the filter's history. The history only looks at the N most recent samples. If there are
        // already N samples, then older samples are discarded and replaced by new samples.
        void sample(T data)
        {
            if (isEmpty())
            {
                head = 0;
                tail = 0;
                samples[head] = data;
            }
            else
            {
                head = (head + 1) % N;
                if (head == tail)
                {
                    tail = (tail + 1) % N;
                }
                samples[head] = data;
            }
        }

        // Computes the running average value of the N most recent samples.
        template <typename U = T>
        U average() const
        {
            U sum = 0;
            size_t count = 0;
            size_t index = tail;

            while (index != empty && count < size())
            {
                sum += static_cast<U>(samples[index]);
                index = (index + 1) % N;
                count++;
            }

            U average = (sum / count);
            return average;
        }

        // History is empty if there are 0 samples.
        bool isEmpty() const { return head == empty; }

        // History is full if there are N samples.
        bool isFull() const { return ((head + 1) % N) == tail && head != empty; }

        // Current number of samples saved in history.
        size_t size() const
        {
            if (isEmpty())
            {
                return 0;
            }
            else if (head >= tail)
            {
                return head - tail + 1;
            }
            else
            {
                return N - tail + head + 1;
            }
        }

        // The max size of history.
        size_t capacity() const { return N; }

        // Delete all saved samples.
        void clear()
        {
            for (size_t i = 0; i < N; i++)
            {
                samples[i] = {};
            }
            head = empty;
            tail = empty;
        }

        // Debugging function to visualise the MAF.
        // Uncomment this if you want to debug with doctest. Remember that std::cout is not available on Arduino so
        // replace std::cout with Serial.print or keep this method commented.
        // void print() const {
        //     for (size_t i = 0; i < size(); i++) {
        //         auto sample = samples[(tail + i) % N];
        //         std::cout << sample << ", ";
        //     }
        //     std::cout << std::endl;
        // }

    private:
        T samples[N]; // Data is a circular buffer stored as [tail, ..., head].
        static constexpr size_t empty = -1;
        size_t head = empty; // Represents the index of the end of the list.
        size_t tail = empty; // Represents the index of the start of the list.
    };

} // namespace mtrn3100