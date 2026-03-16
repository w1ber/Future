#include <iostream>
#include <string>

// Целевой интерфейс (новый ПК ожидает USB)
class USBPrinter {
public:
    virtual std::string printUSB(const std::string& data, const int& quality) = 0;
};

// Старый принтер с LPT-портом (несовместимый)
class OldLPTPrinter {
public:
    std::string printLPT(const std::string& data) {
        return "Старый принтер печатает по LPT: " + data;
    }
};

class USBScanner {
public:
    virtual std::string ScanUSB(const int& quality) = 0;
};
class OldLPTScanner{
public:
    std::string ScanLPT() {
        return "Старый сканер скантрует по LPT: ";
    }
};

// Адаптер: Оборачивает старый принтер для USB-интерфейса
class LPTToUSBAdapter : public USBPrinter, public USBScanner {
private:
    OldLPTPrinter* oldPrinter;
    OldLPTScanner* oldScanner;
public:
    LPTToUSBAdapter(OldLPTPrinter* p, OldLPTScanner* s) : oldPrinter(p), oldScanner(s) {}
    std::string printUSB(const std::string& data, const int& quality) override {
        // Адаптируем вызов
        return oldPrinter->printLPT(data + " (адаптировано для USB)"+ std::to_string(quality));
    }
    std::string ScanUSB(const int& quality) override {
        // Адаптируем вызов
        return (oldScanner->ScanLPT() + "(адаптировано для USB)"+ std::to_string(quality));
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    OldLPTPrinter oldPrinter;
    OldLPTScanner oldScanner;
    LPTToUSBAdapter* adapter = new LPTToUSBAdapter(&oldPrinter, &oldScanner);
    std::cout << adapter->printUSB("Документ",320) << std::endl;  // Вывод: Старый принтер печатает по LPT: Документ (адаптировано для USB)
    std::cout << adapter->ScanUSB(450) << std::endl;
    delete adapter;
    return 0;
}