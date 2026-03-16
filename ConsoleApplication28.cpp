#include <iostream>
#include <string>
// Абстрактные продукты (семейство UI-элементов)
class Button {
public:
    virtual std::string render() = 0;
    virtual std::string interact() = 0;
};

class ScrollBar {
public:
    virtual std::string render() = 0;
};
class CheckBox {
public:
    virtual std::string render() = 0;
};

// Конкретные продукты для Windows
class WinButton : public Button {
public:
    std::string render() override { return "Windows Кнопка"; }
    std::string interact() override { return "Windows Копка нажата"; }
};

class WinScrollBar : public ScrollBar {
public:
    std::string render() override { return "Windows Скроллбар"; }
};
class WinCheckBox : public CheckBox {
    std::string render() override { return "Windows ЧекБокс"; }
};

// Конкретные продукты для macOS
class MacButton : public Button {
public:
    std::string render() override { return "macOS Кнопка"; }
    std::string interact() override { return "macOS Копка нажата"; }
};

class MacScrollBar : public ScrollBar {
public:
    std::string render() override { return "macOS Скроллбар"; }
};
class MacCheckBox : public CheckBox {
    std::string render() override { return "macOs ЧекБокс"; }
};
// Конкретные продукты для LinuxOS
class LinuxButton : public Button {
public:
    std::string render() override { return "LinuxOS Кнопка"; }
    std::string interact() override { return "LinuxOS Копка нажата"; }
};

class LinuxScrollBar : public ScrollBar {
public:
    std::string render() override { return "LinuxOS Скроллбар"; }
};
class LinuxCheckBox : public CheckBox {
    std::string render() override { return "LinuxOS ЧекБокс"; }
};
// Абстрактная фабрика
class UIFactory {
public:
    virtual Button* createButton() = 0;
    virtual ScrollBar* createScrollBar() = 0;
    virtual CheckBox* createCheckBox() = 0;
};

// Конкретные фабрики
class WinFactory : public UIFactory {
public:
    Button* createButton() override { return new WinButton(); }
    ScrollBar* createScrollBar() override { return new WinScrollBar(); }
    CheckBox* createCheckBox() override { return new WinCheckBox(); }
};

class MacFactory : public UIFactory {
public:
    Button* createButton() override { return new MacButton(); }
    ScrollBar* createScrollBar() override { return new MacScrollBar(); }
    CheckBox* createCheckBox() override { return new MacCheckBox(); }
};
class LinuxFactory : public UIFactory {
public:
    Button* createButton() override { return new LinuxButton(); }
    ScrollBar* createScrollBar() override { return new LinuxScrollBar(); }
    CheckBox* createCheckBox() override { return new LinuxCheckBox(); }
};

//Abstract Factory лучше отдельных factory
UIFactory* getFactory()
{
    std::string factory_user = "";
    std::cout << "Выберите OC: win/mac/linux" << std::endl;
    std::cin >> factory_user;
    if (factory_user == "win")
    {
        return new WinFactory();
    }
    else if (factory_user == "mac")
    {
        return new MacFactory();
    }
    else if (factory_user == "linux")
    {
        return new LinuxFactory();
    }
    return nullptr;
}
int main() {
    setlocale(LC_ALL, "ru");
    // Выбираем фабрику по платформе

    UIFactory* factory = getFactory();  // Или MacFactory
    if (factory != nullptr)
    {
        Button* btn = factory->createButton();
        ScrollBar* sb = factory->createScrollBar();
        std::cout << btn->render() << " и " << sb->render() << std::endl;  // Вывод: Windows Кнопка и Windows Скроллбар
        std::cout << btn->interact() << std::endl;
        delete btn; delete sb; delete factory;
    }
    
    UIFactory* factory2 = getFactory();  // Или MacFactory
    if (factory2 != nullptr)
    {
        Button* btn2 = factory2->createButton();
        ScrollBar* sb2 = factory2->createScrollBar();
        CheckBox* chb2 = factory2->createCheckBox();
        std::cout << btn2->render() << " и " << sb2->render() << " и " << chb2->render() << std::endl;
        std::cout << btn2->interact() << std::endl;
        delete btn2, delete sb2, delete chb2, delete factory2;
    }

}