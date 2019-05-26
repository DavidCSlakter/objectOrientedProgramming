#include <iostream>
#include <vector>

using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial( unsigned numPages )
        : numOfPages(numPages)
    {}
    virtual void displayNumPages() const = 0;
protected:
private:
    unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const {
  cout << numOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
    Magazine( unsigned numPages )
        : PrintedMaterial(numPages)
    {}
     void displayNumPages() const
    {
        cout << "Magazine: ";
        PrintedMaterial::displayNumPages();
    }
protected:
private:
};

class Book : public PrintedMaterial {
public:
    Book( unsigned numPages )
        : PrintedMaterial(numPages)
    {}
protected:
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages, unsigned numIndxPgs)
        : Book(numPages),
          numOfIndexPages(numIndxPgs)
    {}
    void displayNumPages() const
    {
        cout << "Pages: ";
        PrintedMaterial::displayNumPages();
        cout << " Index pages: ";
        cout << numOfIndexPages;
    }
protected:
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel( unsigned numPages )
        : Book(numPages)
    {}
    
    void displayNumPages() const
    {
        cout << "Novel: ";
        PrintedMaterial::displayNumPages();
    }
protected:
private:
};

void displayNumberOfPages(const PrintedMaterial& pm){
    pm.displayNumPages();
}

// tester/modeler code
int main()
{
    TextBook t(5430, 234);
    Novel n(213);
    Magazine m(6);

    t.displayNumPages();
    n.displayNumPages();
    m.displayNumPages();
    
    
    PrintedMaterial* pmPtr;
    pmPtr = &t;
    // instead of putting an actual PrintedMaterial
    // object into the vector, we put a pointer to
    // a PrintedMaterial object (t) into a vector
    // of pointers-to-PrintedMaterial
    // (that is, pointers to the Base class)
    // we'll be "managing" our objects by using
    // pointers to PrintedMaterial values.
    cout << "Testing pointer: ";
    pmPtr->displayNumPages();
    
    displayNumberOfPages(t);
    
    
    vector<PrintedMaterial*> printedMaterials;
    
    printedMaterials.push_back(&t);
    printedMaterials.push_back(&n);
    printedMaterials.push_back(&m);
    
    for(size_t i = 0; i < printedMaterials.size(); ++i){
        printedMaterials[i]->displayNumPages();
    }
}
