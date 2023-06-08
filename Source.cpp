#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class neuron { //класс, обозначающий наш нейрон
    double w = static_cast<double>(rand()) / RAND_MAX;  //значение веса,инициализированное случайным числом
public:
    double ProccesInputdata(double input) { //метод, отвечающий за вывод значения, просчитанного нейроном == вход*вес
        return (input * w);
    }
    double  RestoreInputData(double output) { //обратный метод вывода, для получения из выхода значение входа
        return (output / w);
    }
    void Train(double input, double expected, double speed) { //метод тренировки нейрона
        double actresult = input * w; //результат, полученный нерйоном на данный момент
        LastError = expected - actresult; //величина ошибки на данный момент
        double correct = (LastError / input) * speed; //величина треубемой корректировки на данный момент
        w += correct; //изменение веса на величину корректировки
    }
    double LastError; // Последняя ошибка, хранит значение ошибки после тренировки
};
int main()
{
    srand(time(0));
    double USD[10] = {1, 4, 7, 11, 14, 15, 28, 30, 36, 56 };                   //"учитель", обозначающий 
    double EU[10] = {0.93, 3.71, 6.49, 10.2, 12.99, 13.92, 25.98, 27.83, 33.40, 51.95};    //настоящее значение
    int r = rand() % 10;        // Случайное число для выбора значения из массивов USD и EU
    neuron n; //создание объекта "нейрон"
    int i = 0;  // Счетчик итераций обучения
    double speed = 0.000001;    // Скорость обучения

    while (true) {
        i++;
        n.Train(USD[r], EU[r], speed);  // Обучение нейрона на основе случайно выбранной пары значений USD и EU
        /*if (i % 10000 == 0) {
            cout << "Itertion = " << i  << "\t" << "Error = " << n.LastError << endl;
        }*/
        if (n.LastError <= speed && n.LastError >= -speed) {
            break;      // Если ошибка достаточно мала, прекращаем обучение
        }
    }
  
    //cout << r << endl;
    cout << endl << "Iterations of training: " << i << endl << endl;  // Вывод количества итераций обучения

    cout << "Do you want input dollars or euro?" << endl;
    cout << "\t" << "Press 0 if you want to exchange currency from dollars to euro" << endl;
    cout << "\t" << "Press 1 if you want to exchange currency from euro to dollars" << endl;
    cout << "\t" << "Press 2 if yo want to stop" << endl;
    cout << "Press: ";
    int number;
    cin >> number;
    double currency;
    while (number != 2) {
        if (number == 0) {
            cout << endl << "Input dollars = ";
            cin >> currency;
            cout << endl << currency << " dollars = " << n.ProccesInputdata(currency) << " euro" << endl;
        }
        else if (number == 1) {
            cout << endl << "Input euro = ";
            cin >> currency;
            cout << endl << currency << " euro = " << n.RestoreInputData(currency) << " dollars" << endl;
        }
        cout << endl << "Do you want to continue?" << endl;
        cout << "\t" << "Press 0 if you want to exchange currency from dollars to euro" << endl;
        cout << "\t" << "Press 1 if you want to exchange currency from euro to dollars" << endl;
        cout << "\t" << "Press 2 if yo want to stop" << endl;
        cout << "Press: ";
        cin >> number;
    }
    
    return 0;
}
