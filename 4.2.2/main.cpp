#include <iostream>
#include <random>

class Student
{
private:
    std::pair<int, int> name;
    bool vaccinated;

public:
    Student(std::pair<int, int> n, bool v): name(n), vaccinated(v) {}

    auto get_name() { return name; }
    auto is_vaccinated() { return vaccinated; }

    bool operator ==(const Student &s) const
    {
        return this->name == s.name;
    }

    bool operator <(const Student &s) const
    {
        return this->name < s.name;
    }

    bool operator >(const Student &s) const
    {
        return this->name > s.name;
    }

    friend std::ostream& operator<<(std::ostream &out, const Student &s) {
        out << "(" << s.name.first << " " << s.name.second << ", vaccinated " << s.vaccinated << ")";
        return out;
    }

};

auto generate_random_Student(int max)
{
    std::random_device rd;
    std::mt19937 rand(rd());

    std::uniform_int_distribution<std::mt19937::result_type> uniform_dist(1, max);

    auto random_name = std::make_pair(uniform_dist(rand), uniform_dist(rand));
    bool is_vaccinated = uniform_dist(rand) % 2 != 0;

    return Student(random_name, is_vaccinated);
}

bool needs_vaccinated(Student s, std::vector<Student> &students)
{
    auto first = students.begin();
    auto last = students.end();

    std::cout << "searching " << s << std::endl;

    while(true) {
        auto range_length = std::distance(first, last);
        auto mid_idx = static_cast<int>(std::floor(range_length / 2));
        auto mid_elem = *(first + mid_idx);

        std::cout << "mid " << mid_elem << std::endl;

        if(mid_elem == s) {
            std::cout << "found " << mid_elem.is_vaccinated() << std::endl;
            return !mid_elem.is_vaccinated();
        }
        else if(mid_elem > s) {
            std::advance(last, -mid_idx);
        }
        else {
            std::advance(first, mid_idx);
        }

        if(range_length == 1)
            return true;
    }
}

void search_test(int size, Student s)
{
    std::vector<Student> students;

    for(auto i = 0; i < size; i++)
        students.push_back(generate_random_Student(size));

    std::sort(students.begin(), students.end());

    auto begin = std::chrono::steady_clock::now();
    bool search_result = needs_vaccinated(s, students);
    auto end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
    std::cout << "duration : " << diff.count() << "us" << std::endl;
    if(search_result)
        std::cout << s << ") needs vaccine" << std::endl;
    else
        std::cout << s << ") does not need vaccine" << std::endl;
}

int main() {
    auto p = generate_random_Student(1000);
    search_test(1000, p);
    search_test(10000, p);
    search_test(100000, p);
    return 0;
}
