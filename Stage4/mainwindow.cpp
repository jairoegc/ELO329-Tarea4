#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Imagenes Semaforos
    QPixmap sem1(":rojo.png");
    QPixmap sem2(":giroder.png");
    QPixmap sem3(":rojo.png");
    QPixmap sem4(":giroizq.png");
    QPixmap sem5(":rojo.png");
    QPixmap semA(":rojopeaton.png");
    QPixmap semB(":rojopeaton.png");
    ui->sem1->setPixmap(sem1.scaled(51,81));
    ui->sem2->setPixmap(sem2.scaled(41,41));//giro der
    ui->sem3->setPixmap(sem3.scaled(51,81));
    ui->sem4->setPixmap(sem4.scaled(41,41));//giro izq
    ui->sem5->setPixmap(sem5.scaled(51,81));
    ui->semA->setPixmap(semA.scaled(51,81));
    ui->semB->setPixmap(semB.scaled(51,81));

    //Imagenes Botones
    //-------Peatonal----
    paintbuttonOff();
    //----Inductor---
    paintIndOff();

    //Timer
    timer= new QTimer(this);
    timerpaint=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(intersection()));
    connect(timerpaint,SIGNAL(timeout()),this,SLOT(painttraffics()));

    //Semaforos peatonales
    semaforopA = SemaforoP(greenTime, blinkingTime);
    semaforopB = SemaforoP(greenTime, blinkingTime);

    //Semaforos de giro
    semaforog2 = SemaforoDeGiro(greenTime, blinkingTime);
    semaforog4 = SemaforoDeGiro(greenTime, blinkingTime);

    //Semaforos vehiculares
    semaforo1 = TrafficLight(greenTime, blinkingTime);
    semaforo3 = TrafficLight(greenTime, blinkingTime);
    semaforo5 = TrafficLight(greenTime, blinkingTime);

    //Detectores de requerimiento
    botont = new DetectorRequerimiento();
    sensorInd = new DetectorRequerimiento();

    //Controlador
     ctrl = Controlador(&semaforopA,&semaforopB,&semaforog2,&semaforog4,botont,sensorInd,&semaforo1,&semaforo3,&semaforo5);

    //INICIO Timer
     timerpaint->start(std::chrono::milliseconds(100));
     timer->start(std::chrono::milliseconds(1000));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::intersection()
{
    ctrl.manageTraffic();//Se opera el semaforo, atento a las señales del sensor
}

void MainWindow::on_botonpeaton_clicked()
{
    paintbuttonOn();
    botont->setOn();
}

void MainWindow::on_inductor_clicked()
{
    paintIndOn();
    sensorInd->setOn();
}

void MainWindow::paintbuttonOn()
{
    QPixmap Bpeaton(":OnButton.png");
    QIcon ButtonIconPeaton(Bpeaton);
    ui->botonpeaton->setIcon(ButtonIconPeaton);
    ui->botonpeaton->setIconSize(QSize(91,71));
}

void MainWindow::paintIndOn()
{
    QPixmap BInductor(":OnInductor.png");
    QIcon ButtonIconInductor(BInductor);
    ui->inductor->setIcon(ButtonIconInductor);
    ui->inductor->setIconSize(QSize(251,71));
}

void MainWindow::paintbuttonOff()
{
    QPixmap Bpeatonoff(":OffButton.png");
    QIcon ButtonIconPeatonoff(Bpeatonoff);
    ui->botonpeaton->setIcon(ButtonIconPeatonoff);
    ui->botonpeaton->setIconSize(QSize(91,71));
}

void MainWindow::paintIndOff()
{
    QPixmap BInductoroff(":OffInductor.png");
    QIcon ButtonIconInductoroff(BInductoroff);
    ui->inductor->setIcon(ButtonIconInductoroff);
    ui->inductor->setIconSize(QSize(251,71));
}


//Pinta los semaforos segun su estado
void MainWindow::painttraffics()
{
    QPixmap sem1V(":verdeizq.png");
    QPixmap sem1A(":amarillo.png");
    QPixmap sem1R(":rojo.png");
    QPixmap sem2On(":giroder.png");
    QPixmap sem2Off(":girooff.jpg");
    QPixmap sem3V(":verde.png");
    QPixmap sem3A(":amarillo.png");
    QPixmap sem3R(":rojo.png");
    QPixmap sem4On(":giroizq.png");
    QPixmap sem4Off(":girooff.jpg");
    QPixmap sem5V(":verdearriba.png");
    QPixmap sem5A(":amarillo.png");
    QPixmap sem5R(":rojo.png");
    QPixmap semAV(":verdepeaton.png");
    QPixmap semAR(":rojopeaton.png");
    QPixmap semBV(":verdepeaton.png");
    QPixmap semBR(":rojopeaton.png");
    //botones
    if(!botont->isOn()){
        paintbuttonOff();
    }
    if(!sensorInd->isOn()){
        paintIndOff();
    }

    //sem1
    if(semaforo1.getState()==0){
        ui->sem1->setPixmap(sem1R.scaled(51,81));
    }
    else if(semaforo1.getState()==1){
        ui->sem1->setPixmap(sem1A.scaled(51,81));
    }
    else {
        ui->sem1->setPixmap(sem1V.scaled(51,81));
    }
    //sem2
    if(semaforog2.getState()==0){
        ui->sem2->setPixmap(sem2On.scaled(41,41));
    }
    else if(semaforog2.getState()==1){
        if(blink){
            ui->sem2->setPixmap(sem2On.scaled(41,41));
            blink=false;
        }
        else {
            ui->sem2->setPixmap(sem2Off.scaled(41,41));
            blink=true;
        }
    }
    else {
        ui->sem2->setPixmap(sem2Off.scaled(41,41));
    }
    //sem3
    if(semaforo3.getState()==0){
        ui->sem3->setPixmap(sem3R.scaled(51,81));
    }
    else if(semaforo3.getState()==1){
        ui->sem3->setPixmap(sem3A.scaled(51,81));
    }
    else {
        ui->sem3->setPixmap(sem3V.scaled(51,81));
    }
    //sem4
    if(semaforog4.getState()==0){
        ui->sem4->setPixmap(sem4On.scaled(41,41));
    }
    else if(semaforog4.getState()==1){
        if(blink){
            ui->sem4->setPixmap(sem4On.scaled(41,41));
            blink=false;
        }
        else {
            ui->sem4->setPixmap(sem4Off.scaled(41,41));
            blink=true;
        }
    }
    else {
        ui->sem4->setPixmap(sem4Off.scaled(41,41));
    }
    //sem5
    if(semaforo5.getState()==0){
        ui->sem5->setPixmap(sem5R.scaled(51,81));
    }
    else if(semaforo5.getState()==1){
        ui->sem5->setPixmap(sem5A.scaled(51,81));
    }
    else {
        ui->sem5->setPixmap(sem5V.scaled(51,81));
    }
    //semA
    if(semaforopA.getState()==0){
        ui->semA->setPixmap(semAV.scaled(51,81));
    }
    else if(semaforopA.getState()==1){
        if(blink){
            ui->semA->setPixmap(semAV.scaled(51,81));
            blink=false;
        }
        else {
            ui->semA->setPixmap(semAR.scaled(51,81));
            blink=true;
        }
    }
    else {
        ui->semA->setPixmap(semAR.scaled(51,81));
    }
    //semB
    if(semaforopB.getState()==0){
        ui->semB->setPixmap(semBV.scaled(51,81));
    }
    else if(semaforopB.getState()==1){
        if(blink){
            ui->semB->setPixmap(semBV.scaled(51,81));
            blink=false;
        }
        else {
            ui->semB->setPixmap(semBR.scaled(51,81));
            blink=true;
        }
    }
    else {
        ui->semB->setPixmap(semBR.scaled(51,81));
    }
}


/* Para bootn
#botonpeaton{
background-color: transparent;
border-image: url(:OffButton.png);
background: none;
border: none;
background-repeat: none;
}
#botonpeaton:pressed
{
   border-image: url(:OnButton.png);
}

*/

