#include <iostream>
#include <string>

using namespace std;

class VendingMachine;

class State {
public:
    virtual ~State() = default;
    virtual void insertCoin(VendingMachine* vm) = 0;
    virtual void dispense(VendingMachine* vm) = 0;
    virtual void ejectCoin(VendingMachine* vm) = 0;
};

class NoCoinState : public State {
public:
    void insertCoin(VendingMachine* vm) override;
    void dispense(VendingMachine* vm) override { cout << "Вставьте монету!" << endl; }
    void ejectCoin(VendingMachine* vm) override { cout << "Нет монеты." << endl; }
};

class HasCoinState : public State {
public:
    void insertCoin(VendingMachine* vm) override { cout << "Уже оплачено." << endl; }
    void dispense(VendingMachine* vm) override;
    void ejectCoin(VendingMachine* vm) override;
};

class SoldOutState : public State {
public:
    void insertCoin(VendingMachine* vm) override { cout << "Нет товара." << endl; }
    void dispense(VendingMachine* vm) override { cout << "Нет товара." << endl; }
    void ejectCoin(VendingMachine* vm) override { cout << "Нет монеты." << endl; }
};

class VendingMachine {
private:
    State* state;
    int stock;
public:
    VendingMachine(int s = 2) : stock(s), state(new NoCoinState()) {}
    ~VendingMachine() { delete state; }
    void setState(State* s) { delete state; state = s; }
    void insertCoin() { state->insertCoin(this); }
    void dispense() {
        state->dispense(this);
        if (stock <= 0) {
            setState(new SoldOutState());
        }
    }
    void ejectCoin() { state->ejectCoin(this); }
    void takeItem() { if (stock > 0) stock--; }
    bool hasItem() { return stock > 0; }
    int getStock() { return stock; }
};

void NoCoinState::insertCoin(VendingMachine* vm) {
    cout << "Принято." << endl;
    vm->setState(new HasCoinState());
}

void HasCoinState::dispense(VendingMachine* vm) {
    vm->takeItem();
    cout << "Выдано." << endl;
}

void HasCoinState::ejectCoin(VendingMachine* vm) {
    cout << "Возврат." << endl;
    vm->setState(new NoCoinState());
}

int main() {
    setlocale(LC_ALL, "ru");
    VendingMachine vm1(1);
    vm1.insertCoin();
    vm1.dispense();
    vm1.insertCoin();
    vm1.ejectCoin();

    VendingMachine vm2(0);
    vm2.insertCoin();
    vm2.dispense();

    VendingMachine vm3(1);
    vm3.dispense();
}