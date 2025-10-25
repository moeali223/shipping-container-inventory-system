#include <iostream>
#include <vector>
using namespace std;

class ShippingContainer {
protected:
    int id;
public:
    ShippingContainer() : id(-1) {}
    ShippingContainer(int id) : id(id) {}
    virtual string getManifest() { return ""; }
    int getID() const { return id; }
    void setID(int newID) { id = newID; }
    virtual ~ShippingContainer() {}
};

class ManualShippingContainer : public ShippingContainer {
    string contents;
public:
    ManualShippingContainer(int id) : ShippingContainer(id), contents("") {}
    void setManifest(string s) { contents = s; }
    string getManifest() override { return contents; }
};

class RFIDShippingContainer : public ShippingContainer {
    vector<string> contents;
    vector<int> count;
    int search(string s) {
        for (int i = 0; i < contents.size(); i++) {
            if (contents[i] == s) return i;
        }
        return -1;
    }
public:
    RFIDShippingContainer(int id) : ShippingContainer(id) {}
    void add(string s) {
        int idx = search(s);
        if (idx == -1) {
            contents.push_back(s);
            count.push_back(1);
        } else {
            count[idx]++;
        }
    }
    string getManifest() override {
        string result = "";
        for (int i = 0; i < contents.size(); i++) {
            result += contents[i] + " (" + to_string(count[i]) + ")\n";
        }
        return result;
    }
};

int main() {
    ShippingContainer* containers[6];
    containers[0] = new ManualShippingContainer(101);
    containers[1] = new ManualShippingContainer(102);
    containers[2] = new ManualShippingContainer(103);

    dynamic_cast<ManualShippingContainer*>(containers[0])->setManifest("4 crates of apples");
    dynamic_cast<ManualShippingContainer*>(containers[1])->setManifest("5 crates of oranges");
    dynamic_cast<ManualShippingContainer*>(containers[2])->setManifest("2 crates of bananas");

    containers[3] = new RFIDShippingContainer(201);
    containers[4] = new RFIDShippingContainer(202);
    containers[5] = new RFIDShippingContainer(203);

    dynamic_cast<RFIDShippingContainer*>(containers[3])->add("crate of pears");
    dynamic_cast<RFIDShippingContainer*>(containers[3])->add("crate of apples");
    dynamic_cast<RFIDShippingContainer*>(containers[3])->add("crate of pears");

    dynamic_cast<RFIDShippingContainer*>(containers[4])->add("crate of bananas");

    dynamic_cast<RFIDShippingContainer*>(containers[5])->add("crate of oranges");
    dynamic_cast<RFIDShippingContainer*>(containers[5])->add("crate of oranges");
    dynamic_cast<RFIDShippingContainer*>(containers[5])->add("crate of lemons");

    for (int i = 0; i < 6; i++) {
        cout << "Container ID: " << containers[i]->getID() << endl;
        cout << "Manifest:\n" << containers[i]->getManifest() << endl;
        delete containers[i];
    }

    return 0;
}
