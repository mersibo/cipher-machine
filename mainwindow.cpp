#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <QPalette>
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Крипто-шифратор");
    QPixmap bkgnd("C:/Users/ataev/Downloads/Appbackground.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString value = ui->comboBox->currentText(); //Считываем текст с comboBox. Это определяет режим работы.
    if (value == "Ввод из файла")
    {
        QString path = ui->lineEdit->text(); //Считываем путь к файлу
        path = QDir::fromNativeSeparators(path); //Меняем слеши
        QFile file(path); //открываем файл
        if (!file.open(QFile::ReadOnly | QFile::Text)) { // проверям открыт ли файл
            QMessageBox::warning(this, "Ошибка", "Файл не выбран");
        }
        QTextStream in(&file);
        QString line = in.readAll(); //считываем все из файла
        file.close(); //Закрываем файл

        QString key_text = ui->lineEdit_2->text();    //Задаем переменную типа QString и передаем им значение из окна ввода lineedit_2.
        int i, key;  //Задаем переменные i и key типа integer.
        string t, s;  //Задаем переменные t и s типа string.
        s = line.toStdString();
        key = key_text.toInt();  //преобразуем данные из типа QString в integer.
        for(i=0;i<s.size();i++){  //задаем цикл for по размеру файла
            t+=(s[i]-'A'+key)%26+'A';  //задаем непосредственно условие с которым преобразуется каждый символб а именно сдвиг символа вправо по алфавиту на значение переменной key, то есть ключа.
        }

        QString res = QString::fromStdString(t); //Преобразуем формат в QString
        QString path_2 = QFileDialog::getSaveFileName(this, " ", "C://", "text files (*.txt)"); //выбираем где сохранить файл
        QFile result_file(path_2); // открываем файл
        if (result_file.open(QFile::ReadWrite | QFile::Text)){ //проверям открыт ли файл
            result_file.write(res.toUtf8()); //заполняем файл
        }
        result_file.close(); //закрываем файл

        ui->label->setText("Файл зашифрован");
        ui->progressBar->setValue(100);
    }
    else if (value == "Ввод вручную")
    {
        QString text = ui->lineEdit->text();   //Задаем переменную типа QString и передаем им значение из окна ввода lineedit.
        QString key_text = ui->lineEdit_2->text();    //Задаем переменную типа QString и передаем им значение из окна ввода lineedit_2.
        int i, key;  //Задаем переменные i и key типа integer.
        string t, s;  //Задаем переменные t и s типа string.
        key = key_text.toInt();  //преобразуем данные из типа QString в integer.
        s = text.toStdString();  //преобразуем данные из типа QString в std::string.
        for(i=0;i<s.size();i++){  //задаем цикл for чтобы задать какое-то условие для каждого символа в строке.
            t+=(s[i]-'A'+key)%26+'A';  //задаем непосредственно условие с которым преобразуется каждый символб а именно сдвиг символа вправо по алфавиту на значение переменной key, то есть ключа.
        }
        ui->label->setText(QString::fromStdString(t));  //Выводим полученную строку в окно label, попутно преобразуя ее из типа std:string в QString.
        ui->progressBar->setValue(100);
    }

    //Небольшое пояснение: в qt виджеты считывают и выводят значения только в формате QString, поэтому нам нужно преобразовывать все входные и выходные данные.

}


void MainWindow::on_pushButton_2_clicked()
{
    QString value = ui->comboBox->currentText(); //Считываем текст с comboBox. Это определяет режим работы.
    if (value == "Ввод из файла")
    {
        QString path = ui->lineEdit->text(); //Считываем путь к файлу
        path = QDir::fromNativeSeparators(path); //Меняем слеши
        QFile file(path); //открываем файл
        if (!file.open(QFile::ReadOnly | QFile::Text)) { // проверям открыт ли файл
            QMessageBox::warning(this, "Ошибка", "Файл не выбран");
        }
        QTextStream in(&file);
        QString line = in.readAll(); //считываем все из файла
        file.close(); //Закрываем файл

        QString key_text = ui->lineEdit_2->text();    //Задаем переменную типа QString и передаем им значение из окна ввода lineedit_2.
        int i, key;  //Задаем переменные i и key типа integer.
        string t, s;  //Задаем переменные t и s типа string.
        key = key_text.toInt();  //преобразуем данные из типа QString в integer.
        s = line.toStdString();  //преобразуем данные из типа QString в std::string.
        for(i=0;i<s.size();i++){  //задаем цикл for чтобы задать какое-то условие для каждого символа в строке.
            t+=(s[i]-'A'-key+26)%26+'A';  //задаем непосредственно условие с которым преобразуется каждый символб а именно сдвиг символа влево по алфавиту на значение переменной key, то есть ключа.
        }

        QString res = QString::fromStdString(t); //Преобразуем формат в QString
        QString path_2 = QFileDialog::getSaveFileName(this, " ", "C://", "text files (*.txt)"); //выбираем где сохранить файл
        QFile result_file(path_2); // открываем файл
        if (result_file.open(QFile::ReadWrite | QFile::Text)){ //проверям открыт ли файл
            result_file.write(res.toUtf8()); //заполняем файл
        }
        result_file.close(); //закрываем файл

        ui->label->setText("Файл расшифрован");
        ui->progressBar->setValue(100);
    }
    else if (value == "Ввод вручную")
    {
        QString text = ui->lineEdit->text();   //Задаем переменную типа QString и передаем им значение из окна ввода lineedit.
        QString key_text = ui->lineEdit_2->text();    //Задаем переменную типа QString и передаем им значение из окна ввода lineedit_2.
        int i, key;  //Задаем переменные i и key типа integer.
        string t, s;  //Задаем переменные t и s типа string.
        key = key_text.toInt();  //преобразуем данные из типа QString в integer.
        s = text.toStdString();  //преобразуем данные из типа QString в std::string.
        for(i=0;i<s.size();i++){  //задаем цикл for чтобы задать какое-то условие для каждого символа в строке.
            t+=(s[i]-'A'-key+26)%26+'A';  //задаем непосредственно условие с которым преобразуется каждый символб а именно сдвиг символа влево по алфавиту на значение переменной key, то есть ключа.
        }
        ui->label->setText(QString::fromStdString(t));  //Выводим полученную строку в окно label, попутно преобразуя ее из типа std:string в QString.
        ui->progressBar->setValue(100);
    }

    //Небольшое пояснение: в qt виджеты считывают и выводят значения только в формате QString, поэтому нам нужно преобразовывать все входные и выходные данные.

}


void MainWindow::on_pushButton_4_clicked()
{
    QString value = ui->comboBox_2->currentText(); //Считываем текст с comboBox. Это определяет режим работы.
    if (value == "Ввод из файла")
    {
        QString path = ui->lineEdit_3->text(); //Считываем путь к файлу
        path = QDir::fromNativeSeparators(path); //Меняем слеши
        QFile file(path); //открываем файл
        if (!file.open(QFile::ReadOnly | QFile::Text)) { // проверям открыт ли файл
            QMessageBox::warning(this, "Ошибка", "Файл не выбран");
        }
        QTextStream in(&file);
        QString line = in.readAll(); //считываем все из файла
        file.close(); //Закрываем файл

        QString key_text_1 = ui->lineEdit_4->text();    //Задаем переменную типа QString и передаем им значение из окна ввода lineedit_2.
        QString key_text_2 = ui->lineEdit_5->text();    //Задаем переменную типа QString и передаем им значение из окна ввода lineedit_2.
        string cipher, s;  //Задаем переменные cipher и s типа string.
        int a, b;  //Задаем переменные a и b типа integer.

        s = line.toStdString();  //преобразуем данные из типа QString в std::string.
        a = key_text_1.toInt();  //преобразуем данные из типа QString в integer.
        b = key_text_2.toInt();  //преобразуем данные из типа QString в integer.

        for (int i = 0; i < s.length(); i++) //Задаем цикл перебора, но так чтобы длина не становилась отрицательной.
        {
            // Проверяем чтобы символ не был пробелом
            if(s[i]!=' ')

            cipher = cipher +
                     (char) ((((a * (s[i]-'A') ) + b) % 26) + 'A');  //Здесь мы применяем формулу шифрования ( a x + b ) mod m {здесь x - s[i], а m равно 26} и добавляем'A', чтобы привести ее в диапазон алфавита ascii[ 65-90 | A-Z ].
            else
                //В противном случае просто добавляем пробел.
                cipher += s[i];
        }

        QString res = QString::fromStdString(cipher); //Преобразуем формат в QString
        QString path_2 = QFileDialog::getSaveFileName(this, " ", "C://", "text files (*.txt)"); //выбираем где сохранить файл
        QFile result_file(path_2); // открываем файл
        if (result_file.open(QFile::ReadWrite | QFile::Text)){ //проверям открыт ли файл
            result_file.write(res.toUtf8()); //заполняем файл
        }
        result_file.close(); //закрываем файл

        ui->label_3->setText("Файл зашифрован");
        ui->progressBar->setValue(100);
    }
    else if (value == "Ввод вручную")
    {
        QString text = ui->lineEdit_3->text();  //Задаем переменную типа QString и передаем им значение из окна ввода lineedit.
        QString key_text_1 = ui->lineEdit_4->text();    //Задаем переменную типа QString и передаем им значение из окна ввода lineedit_2.
        QString key_text_2 = ui->lineEdit_5->text();    //Задаем переменную типа QString и передаем им значение из окна ввода lineedit_2.
        string cipher, s;  //Задаем переменные cipher и s типа string.
        int a, b;  //Задаем переменные a и b типа integer.

        s = text.toStdString();  //преобразуем данные из типа QString в std::string.
        a = key_text_1.toInt();  //преобразуем данные из типа QString в integer.
        b = key_text_2.toInt();  //преобразуем данные из типа QString в integer.

        for (int i = 0; i < s.length(); i++) //Задаем цикл перебора, но так чтобы длина не становилась отрицательной.
        {
            // Проверяем чтобы символ не был пробелом
            if(s[i]!=' ')

            cipher = cipher +
                     (char) ((((a * (s[i]-'A') ) + b) % 26) + 'A');  //Здесь мы применяем формулу шифрования ( a x + b ) mod m {здесь x - s[i], а m равно 26} и добавляем'A', чтобы привести ее в диапазон алфавита ascii[ 65-90 | A-Z ].
            else
                //В противном случае просто добавляем пробел.
                cipher += s[i];
        }
        ui->label_3->setText(QString::fromStdString(cipher));  //Выводим полученную строку в окно label_3, попутно преобразуя ее из типа std:string в QString.
        ui->progressBar->setValue(100);
    }

    //Небольшое пояснение: в qt виджеты считывают и выводят значения только в формате QString, поэтому нам нужно преобразовывать все входные и выходные данные.

}


void MainWindow::on_pushButton_3_clicked()
{
    QString value = ui->comboBox_2->currentText(); //Считываем текст с comboBox. Это определяет режим работы.
    if (value == "Ввод из файла")
    {
        QString path = ui->lineEdit_3->text(); //Считываем путь к файлу
        path = QDir::fromNativeSeparators(path); //Меняем слеши
        QFile file(path); //открываем файл
        if (!file.open(QFile::ReadOnly | QFile::Text)) { // проверям открыт ли файл
            QMessageBox::warning(this, "Ошибка", "Файл не выбран");
        }
        QTextStream in(&file);
        QString line = in.readAll(); //считываем все из файла
        file.close(); //Закрываем файл

        QString key_text_1 = ui->lineEdit_4->text();    //Задаем переменную типа QString и передаем им значение из окна ввода lineedit_2.
        QString key_text_2 = ui->lineEdit_5->text();    //Задаем переменную типа QString и передаем им значение из окна ввода lineedit_2.
        string cipher, s;  //Задаем переменные cipher и s типа string.
        int a, b;  //Задаем переменные a и b типа integer.
        cipher = line.toStdString();  //преобразуем данные из типа QString в std::string.
        a = key_text_1.toInt();  //преобразуем данные из типа QString в integer.
        b = key_text_2.toInt();  //преобразуем данные из типа QString в integer.
        int a_inv, flag;  //Задаем переменные a_inv и flag типа integer.


        for (int i = 0; i < 26; i++)  //В этом цикле мы находим a^-1, то есть обратную по модулю величину a.
        {
            flag = (a * i) % 26;

            //Проверяем выполняется ли равенство (a*i)%26 == 1, если выполняется то i действительно является обратной по модулю величиной a.
            if (flag == 1)
            {
                a_inv = i;
            }
        }
        for (int i = 0; i < cipher.length(); i++) //Задаем цикл перебора, но так чтобы длина не становилась отрицательной.
        {
            // Проверяем чтобы символ не был пробелом
            if(cipher[i]!=' ')
                s = s +
                    (char) (((a_inv * ((cipher[i]+'A' - b)) % 26)) + 'A');  //Применяем формулу дешифрования a ^-1 ( x - b ) mod m {здесь x - шифр [i], а m равно 26} и добавляем 'A', чтобы привести его в диапазон алфавита ASCII [ 65-90 | A-Z ].
            else
                //В противном случае просто добавляем пробел.
                s += cipher[i];
        }

        QString res = QString::fromStdString(s); //Преобразуем формат в QString
        QString path_2 = QFileDialog::getSaveFileName(this, " ", "C://", "text files (*.txt)"); //выбираем где сохранить файл
        QFile result_file(path_2); // открываем файл
        if (result_file.open(QFile::ReadWrite | QFile::Text)){ //проверям открыт ли файл
            result_file.write(res.toUtf8()); //заполняем файл
        }
        result_file.close(); //закрываем файл

        ui->label_3->setText("Файл расшифрован");
        ui->progressBar->setValue(100);
    }
    else if (value == "Ввод вручную")
    {
        QString text = ui->lineEdit_3->text();  //Задаем переменную типа QString и передаем им значение из окна ввода lineedit.
        QString key_text_1 = ui->lineEdit_4->text();    //Задаем переменную типа QString и передаем им значение из окна ввода lineedit_2.
        QString key_text_2 = ui->lineEdit_5->text();    //Задаем переменную типа QString и передаем им значение из окна ввода lineedit_2.
        string cipher, s;  //Задаем переменные cipher и s типа string.
        int a, b;  //Задаем переменные a и b типа integer.
        cipher = text.toStdString();  //преобразуем данные из типа QString в std::string.
        a = key_text_1.toInt();  //преобразуем данные из типа QString в integer.
        b = key_text_2.toInt();  //преобразуем данные из типа QString в integer.
        int a_inv, flag;  //Задаем переменные a_inv и flag типа integer.


        for (int i = 0; i < 26; i++)  //В этом цикле мы находим a^-1, то есть обратную по модулю величину a.
        {
            flag = (a * i) % 26;

            //Проверяем выполняется ли равенство (a*i)%26 == 1, если выполняется то i действительно является обратной по модулю величиной a.
            if (flag == 1)
            {
                a_inv = i;
            }
        }
        for (int i = 0; i < cipher.length(); i++) //Задаем цикл перебора, но так чтобы длина не становилась отрицательной.
        {
            // Проверяем чтобы символ не был пробелом
            if(cipher[i]!=' ')
                s = s +
                    (char) (((a_inv * ((cipher[i]+'A' - b)) % 26)) + 'A');  //Применяем формулу дешифрования a ^-1 ( x - b ) mod m {здесь x - шифр [i], а m равно 26} и добавляем 'A', чтобы привести его в диапазон алфавита ASCII [ 65-90 | A-Z ].
            else
                //В противном случае просто добавляем пробел.
                s += cipher[i];
        }
        ui->label_3->setText(QString::fromStdString(s));  //Выводим полученную строку в окно label_3, попутно преобразуя ее из типа std:string в QString.
        ui->progressBar->setValue(100);
    }

    //Небольшое пояснение: в qt виджеты считывают и выводят значения только в формате QString, поэтому нам нужно преобразовывать все входные и выходные данные.


}

void MainWindow::on_pushButton_5_clicked()
{
    QString value = ui->comboBox_3->currentText(); //Считываем текст с comboBox. Это определяет режим работы.
    if (value == "Ввод из файла")
        {
        QString path = ui->lineEdit_6->text(); //Считываем путь к файлу
        path = QDir::fromNativeSeparators(path); //Меняем слеши
        QFile file(path); //открываем файл
        if (!file.open(QFile::ReadOnly | QFile::Text)) { // проверям открыт ли файл
            QMessageBox::warning(this, "Ошибка", "Файл не выбран");
        }
        QTextStream in(&file);
        QString line = in.readAll(); //считываем все из файла
        file.close(); //Закрываем файл

        /*
         * Дальше происходит следующее:
         * Задаем переменные и вектора, считываем размер матрицы с поля ввода, заполняем ее введенными значениями.
         * После берем строку которую мы ранее взяли из файла и в цикле по длине этой строки расшифровываем её.
        */
        int x,y,i,j,k,n;
        QString size = ui->lineEdit_7->text();
        n = size.toInt();
        vector<vector<int> > a(n, vector<int>(n));
        vector<vector<int> > adj(n, vector<int>(n));
        vector<vector<int> > inv(n, vector<int>(n));

        QStringList lol = ui->textEdit->toPlainText().simplified().split(" ");
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){

                a[i][j] = lol[n*i+j].toInt();
            }
        }
        if(inverse(a,inv,n)){
            cout<<"Inverse exist\n";
        }
        string s;
        s = line.toStdString();
        k=0;
        string ans;
        while(k<s.size()){
            for(i=0;i<n;i++){
                int sum = 0;
                int temp = k;
                for(j=0;j<n;j++){
                    sum += ((inv[i][j] + 26)%26*(s[temp++]-'a')%26)%26;
                    sum = sum%26;
                }
                ans+=(sum+'a');
            }
            k+=n;
        }

        QString res = QString::fromStdString(ans); //Преобразуем формат в QString
        QString path_2 = QFileDialog::getSaveFileName(this, " ", "C://", "text files (*.txt)"); //выбираем где сохранить файл
        QFile result_file(path_2); // открываем файл
        if (result_file.open(QFile::ReadWrite | QFile::Text)){ //проверям открыт ли файл
            result_file.write(res.toUtf8()); //заполняем файл
        }
        result_file.close(); //закрываем файл

        ui->label_6->setText("Файл зашифрован");
        ui->progressBar->setValue(100);
    }
    else if (value == "Ввод вручную")
    {
        int x,y,i,j,k,n;
        QString text = ui->lineEdit_6->text();
        QString size = ui->lineEdit_7->text();
        n = size.toInt();
        vector<vector<int> > a(n, vector<int>(n));
        vector<vector<int> > adj(n, vector<int>(n));
        vector<vector<int> > inv(n, vector<int>(n));

        QStringList lol = ui->textEdit->toPlainText().simplified().split(" ");
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){

                a[i][j] = lol[n*i+j].toInt();
            }
        }
        if(inverse(a,inv,n)){
            cout<<"Inverse exist\n";
        }
        string s;
        s = text.toStdString();
        k=0;
        string ans;
        while(k<s.size()){
            for(i=0;i<n;i++){
                int sum = 0;
                int temp = k;
                for(j=0;j<n;j++){
                    sum += ((inv[i][j] + 26)%26*(s[temp++]-'a')%26)%26;
                    sum = sum%26;
                }
                ans+=(sum+'a');
            }
            k+=n;
        }

        ui->label_6->setText(QString::fromStdString(ans));  //Выводим полученную строку в окно label, попутно преобразуя ее из типа std:string в QString.
        ui->progressBar->setValue(100);

    }


         //Небольшое пояснение: в qt виджеты считывают и выводят значения только в формате QString, поэтому нам нужно преобразовывать все входные и выходные данные.


}


void MainWindow::on_pushButton_6_clicked()
{
    QString value = ui->comboBox_3->currentText(); //Считываем текст с comboBox. Это определяет режим работы.
    if (value == "Ввод из файла")
    {
        QString path = ui->lineEdit_6->text(); //Считываем путь к файлу
        path = QDir::fromNativeSeparators(path); //Меняем слеши
        QFile file(path); //открываем файл
        if (!file.open(QFile::ReadOnly | QFile::Text)) { // проверям открыт ли файл
            QMessageBox::warning(this, "Ошибка", "Файл не выбран");
        }
        QTextStream in(&file);
        QString line = in.readAll(); //считываем все из файла
        file.close(); //Закрываем файл

        /*
         * Дальше происходит следующее:
         * Задаем переменные и матрицы, считываем размер матрицы с поля ввода, заполняем ее введенными значениями.
         * После берем строку из поля для ввода и в цикле по длине этой строки зашифровываем её.
        */

        int x,y,i,j,k,n;
        QString size = ui->lineEdit_7->text();
        n = size.toInt();
        int a[n][n];
        QStringList lol = ui->textEdit->toPlainText().simplified().split(" ");
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){

                a[i][j] = lol[n*i+j].toInt();
            }
        }

        string s;
        s = line.toStdString();
        int temp = (n-s.size()%n)%n;
        for(i=0;i<temp;i++){
            s+='x';
        }
        k=0;
        string ans="";
        while(k<s.size()){
            for(i=0;i<n;i++){
                int sum = 0;
                int temp = k;
                for(j=0;j<n;j++){
                    sum += (a[i][j]%26*(s[temp++]-'a')%26)%26;
                    sum = sum%26;
                }
                ans+=(sum+'a');
            }
            k+=n;
        }

        QString res = QString::fromStdString(ans); //Преобразуем формат в QString
        QString path_2 = QFileDialog::getSaveFileName(this, " ", "C://", "text files (*.txt)"); //выбираем где сохранить файл
        QFile result_file(path_2); // открываем файл
        if (result_file.open(QFile::ReadWrite | QFile::Text)){ //проверям открыт ли файл
            result_file.write(res.toUtf8()); //заполняем файл
        }
        result_file.close(); //закрываем файл

        ui->label_6->setText("Файл зашифрован");
        ui->progressBar->setValue(100);
    }
    else if (value == "Ввод вручную")
    {
        QString text = ui->lineEdit_6->text();   //Задаем переменную типа QString и передаем им значение из окна ввода lineedit.
        int x,y,i,j,k,n;
        QString size = ui->lineEdit_7->text();
        n = size.toInt();
        int a[n][n];
        QStringList lol = ui->textEdit->toPlainText().simplified().split(" ");
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){

                a[i][j] = lol[n*i+j].toInt();
            }
        }
        string s;
        s = text.toStdString();
        int temp = (n-s.size()%n)%n;
        for(i=0;i<temp;i++){
            s+='x';
        }
        k=0;
        string ans="";
        while(k<s.size()){
            for(i=0;i<n;i++){
                int sum = 0;
                int temp = k;
                for(j=0;j<n;j++){
                    sum += (a[i][j]%26*(s[temp++]-'a')%26)%26;
                    sum = sum%26;
                }
                ans+=(sum+'a');
            }
            k+=n;
        }
        ui->label_6->setText(QString::fromStdString(ans));  //Выводим полученную строку в окно label, попутно преобразуя ее из типа std:string в QString.
        ui->progressBar->setValue(100);
    }

    //Небольшое пояснение: в qt виджеты считывают и выводят значения только в формате QString, поэтому нам нужно преобразовывать все входные и выходные данные.

}


void MainWindow::on_pushButton_7_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выберите файл", "C://", "text files (*.txt)"); //Выбираем исходный файл
    ui->lineEdit->setText(filename); //Передаем имя файла в lineedit

}


void MainWindow::on_pushButton_8_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выберите файл", "C://", "text files (*.txt)"); //Выбираем исходный файл
    ui->lineEdit_3->setText(filename); //Передаем имя файла в lineedit_3
}



void MainWindow::on_pushButton_9_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выберите файл", "C://", "text files (*.txt)"); //Выбираем исходный файл
    ui->lineEdit_6->setText(filename); //Передаем имя файла в lineedit_3
}

