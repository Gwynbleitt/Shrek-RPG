#include <iostream>
#include <vector>
class Person
{
    std::string* m_name;
    int* m_age;

public:
    Person(std::string name, int age)
    {
        m_name = new std::string(name);
        m_age = new int(age);
    }
    ~Person()
    {
        delete m_name;
        delete m_age;
        std::cout << "destructor called\n";
    }

   

    Person(Person&& move)
    {
        m_name = move.m_name;
        m_age = move.m_age;

        move.m_age = nullptr;
        move.m_name = nullptr;

        std::cout << "move\n";
    }

    void print()
    {
        std::cout << "name: " << *m_name <<  '\n'<< "age: " << *m_age << '\n';
    }
};

class vcont
{

    std::vector<Person> persons;

public:

    void prcoess_list(std::vector<std::string> names, std::vector<int>ages)
    {
        for(int i = 0; i < names.size(); i++)
        {
            persons.push_back(Person(names[persons.size()],ages[persons.size()]));
        }
    }
    Person proccess_person(std::string name, int age)
    {
        return Person(name, age);
    }

    void print()
    {
        for(int i = 0; i < persons.size(); i++)
        {
            persons[i].print();
        }
    }

};

class app
{
public:
    void run()
    {
        std::vector<std::string> a = {"stefan", "geralt", "stas", "ala"};
        std::vector<int> b = {15,80,16,27};

        vcont V_main;
        V_main.prcoess_list(a,b);
        V_main.print();
    }
};

int main()
{

    app App;

    App.run();
   
    std::cout << "end" << '\n';
    
    return 0;
}