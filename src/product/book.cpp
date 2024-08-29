#include <string>

#include "product.h"

using namespace std;

class Book : public Product {
   private:
    string auther;
    int pages;
    int year;
    string isbn;

   public:
    Book(string name, int price, string company, string auther, int pages, int year, string isbn)
        : Product(name, price, "Book", company, 0), auther(auther), pages(pages), year(year), isbn(isbn) {}

    string getMoreDetails(int option = 0) override {

        switch (option) {
            case 0:
                return auther + "," + to_string(pages) + "," + to_string(year) + "," + isbn;
            
            case 1:
                return "Auther: " + auther + "\tPages: " + to_string(pages) + "\tYear: " + to_string(year) + "\tISBN: " + isbn;
            
            case 2:
                return "Auther: " + auther + " | Pages: " + to_string(pages) + "\nYear: " + to_string(year) + " | ISBN: " + isbn; 
        }
        
        return "";
    }

    string getAuther() {
        return auther;
    }

    int gePages() {
        return pages;
    }

    int getYear() {
        return year;
    }

    string getIsbn() {
        return isbn;
    }

    void setAuther(string auther) {
        this->auther = auther;
    }

    void setPages(int page) {
        this->pages = page;
    }

    void setYear(int year) {
        this->year = year;
    }

    void setIsbn(string isbn) {
        this->isbn = isbn;
    }
};