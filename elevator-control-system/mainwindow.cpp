#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();

    connect(ui->normal, SIGNAL(clicked(bool)), this, SLOT(normalMode()));
    connect(ui->overload, SIGNAL(clicked(bool)), this, SLOT(overloadMode()));
    connect(ui->doorObstacle, SIGNAL(clicked(bool)), this, SLOT(doorObstacleMode()));
    connect(ui->help, SIGNAL(clicked(bool)), this, SLOT(helpMode()));
    connect(ui->fire, SIGNAL(clicked(bool)), this, SLOT(fireMode()));
    connect(ui->power_out, SIGNAL(clicked(bool)), this, SLOT(poweroutMode()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::normalMode()
{
    timer->stop();
    info.clear();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(logToSystem()));

    info.append("----------START OF NORMAL SIMULATION----------");
    info.append("Number of Passengers: 5");
    //Create Passengers
    passenger1 = new Passengers("Sean", 140.5, 0);
    passenger2 = new Passengers("Sarah", 123.6, 0);
    passenger3 = new Passengers("Donald", 200.9, 0);
    passenger4 = new Passengers("Richard", 167.4, 0);
    passenger5 = new Passengers("Lil Mike", 76.0, 0);

    //Create Floors
    info.append("Number of Floors: 6");
    floor0 = new Floor(0);
    floor1 = new Floor(1);
    floor2 = new Floor(2);
    floor3 = new Floor(3);
    floor4 = new Floor(4);
    floor5 = new Floor(5);

    //Create Elevators
    info.append("Number of Elevators: 3");
    elevator1 = new Elevator(5, "Elevator 1");
    elevator2 = new Elevator(2, "Elevator 2");
    elevator3 = new Elevator(1, "Elevator 3");
    //inUse elevators will be set to one of the three elevators above
    inUse1 = new Elevator(0, "In Use");
    inUse2 = new Elevator(0, "In Use");
    inUse3 = new Elevator(0, "In Use");

    //Create Bell
    bell = new Bell();

    //Create Elevator Control System
    elevatorControlSystem = new ECS();
    elevatorControlSystem->setElevator(elevator1);
    elevatorControlSystem->setElevator(elevator2);
    elevatorControlSystem->setElevator(elevator3);
    elevatorControlSystem->setFloor(floor0);
    elevatorControlSystem->setFloor(floor1);
    elevatorControlSystem->setFloor(floor2);
    elevatorControlSystem->setFloor(floor3);
    elevatorControlSystem->setFloor(floor4);
    elevatorControlSystem->setFloor(floor5);

    //All passengers enter the building and are on the main floor (floor 0)

    //Simulate a passenger requesting an elevator
    info.append("NEW REQUEST!");
    info.append(QString ("Floor %1 has a request to go %2...illuminating %3 button for floor 0").arg(floor0->getFloorNum()).arg(passenger1->chooseDirection("up")).arg(passenger1->chooseDirection("up")));
    floor0->setDirection(passenger1->chooseDirection("up"));

    //ECS process the request and returns an idle or closest elevator
    inUse1 = elevatorControlSystem->getElevator(passenger1->getCurrFloor(), passenger1->getDirection());
    info.append(QString ("%1 retrieved...").arg(inUse1->getName()));

    //Move the elevator
    moreInfo = elevatorControlSystem->moveElevator(inUse1, passenger1->getCurrFloor());
    //moveElevator function returns a list of QString to be printed to the console (since we cannot add stuff to GUI directly within ECS class)
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse1->openDoor());
    info.append("Cancelling illumination of up button on floor 0");

    //Load passengers
    info.append("Picking up passengers...");
    inUse1->loadPassengers(passenger1);
    inUse1->loadPassengers(passenger2);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse1->closeDoor(true));

    //Display the current state of the elevator in use
    info.append(inUse1->getInfo());

    //Move the elevator
    inUse1->setRequests(passenger1->chooseFloor(3));
    info.append(inUse1->getScreen()->displayFloor());
    moreInfo = elevatorControlSystem->moveElevator(inUse1, 3);
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse1->openDoor());

    //Unload Passengers
    info.append("Unloading passengers...");
    inUse1->unloadPassengers(passenger1);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse1->closeDoor(true));

    //New request incoming
    info.append("NEW REQUEST!");
    info.append(QString ("Floor %1 has a request to go %2...illuminating %3 button for floor 0").arg(floor0->getFloorNum()).arg(passenger3->chooseDirection("up")).arg(passenger3->chooseDirection("up")));
    floor0->setDirection(passenger3->chooseDirection("up"));

    //ECS process the request and returns an idle or closest elevator
    inUse2 = elevatorControlSystem->getElevator(passenger3->getCurrFloor(), passenger3->getDirection());
    info.append(QString ("%1 retrieved...").arg(inUse2->getName()));

    //Continue first request

    //Display the current state of the elevator in use
    info.append(inUse1->getInfo());

    //Move the elevator
    inUse1->setRequests(passenger2->chooseFloor(5));
    info.append(inUse1->getScreen()->displayFloor());
    moreInfo = elevatorControlSystem->moveElevator(inUse1, 5);
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse1->openDoor());

    //Unload Passengers
    info.append("Unloading passengers...");
    inUse1->unloadPassengers(passenger2);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse1->closeDoor(true));

    info.append(QString ("%1 is now %2").arg(inUse1->getName()).arg(inUse1->getState()));

    //Set elevator1 to the state of inUse1
    elevatorControlSystem->replaceElevator(inUse1);

    //Continue Second request

    //Move the elevator
    moreInfo = elevatorControlSystem->moveElevator(inUse2, passenger3->getCurrFloor());
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse2->openDoor());
    info.append("Cancelling illumination of up button on floor 0");

    //Load passengers
    info.append("Picking up passengers...");
    inUse2->loadPassengers(passenger3);
    inUse2->loadPassengers(passenger4);
    inUse2->loadPassengers(passenger5);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse2->closeDoor(true));

    //Display the current state of the elevator in use
    info.append(inUse2->getInfo());

    //Move the elevator
    inUse2->setRequests(passenger3->chooseFloor(2));
    info.append(inUse1->getScreen()->displayFloor());
    moreInfo = elevatorControlSystem->moveElevator(inUse2, 2);
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse2->openDoor());

    //Unload Passengers
    info.append("Unloading passengers...");
    inUse2->unloadPassengers(passenger3);
    inUse2->unloadPassengers(passenger4);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse2->closeDoor(true));

    //Display the current state of the elevator in use
    info.append(inUse2->getInfo());

    //Move the elevator
    inUse2->setRequests(passenger5->chooseFloor(5));
    info.append(inUse1->getScreen()->displayFloor());
    moreInfo = elevatorControlSystem->moveElevator(inUse2, 5);
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse2->openDoor());

    //Unload Passengers
    info.append("Unloading passengers...");
    inUse2->unloadPassengers(passenger5);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse2->closeDoor(true));

    info.append(QString ("%1 is now %2").arg(inUse2->getName()).arg(inUse2->getState()));

    //Set elevator2 to the state of inUse2
    elevatorControlSystem->replaceElevator(inUse2);

    //Bring everyone back to floor 0

    //New Request
    info.append("NEW REQUEST!");
    info.append(QString ("Floor %1 has a request to go %2...illuminating %3 button for floor 2").arg(floor2->getFloorNum()).arg(passenger3->chooseDirection("down")).arg(passenger3->chooseDirection("down")));
    floor2->setDirection(passenger3->chooseDirection("down"));

    //ECS process the request and returns an idle or closest elevator
    inUse1 = elevatorControlSystem->getElevator(passenger3->getCurrFloor(), passenger3->getDirection());
    info.append(QString ("%1 retrieved...").arg(inUse1->getName()));

    //New Request
    info.append("NEW REQUEST!");
    info.append(QString ("Floor %1 has a request to go %2...illuminating %3 button for floor 3").arg(floor3->getFloorNum()).arg(passenger1->chooseDirection("down")).arg(passenger1->chooseDirection("down")));
    floor3->setDirection(passenger1->chooseDirection("down"));

    //ECS process the request and returns an idle or closest elevator
    inUse2 = elevatorControlSystem->getElevator(passenger1->getCurrFloor(), passenger1->getDirection());
    info.append(QString ("%1 retrieved...").arg(inUse2->getName()));

    //New Request
    info.append("NEW REQUEST!");
    info.append(QString ("Floor %1 has a request to go %2...illuminating %3 button for floor 5").arg(floor5->getFloorNum()).arg(passenger2->chooseDirection("down")).arg(passenger2->chooseDirection("down")));
    floor5->setDirection(passenger2->chooseDirection("down"));

    //ECS process the request and returns an idle or closest elevator
    inUse3 = elevatorControlSystem->getElevator(passenger2->getCurrFloor(), passenger2->getDirection());
    info.append(QString ("%1 retrieved...").arg(inUse3->getName()));

    //Move the elevator: 1st request to go down
    moreInfo = elevatorControlSystem->moveElevator(inUse1, passenger3->getCurrFloor());
    //moveElevator function returns a list of QString to be printed to the console (since we cannot add stuff to GUI directly within ECS class)
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse1->openDoor());
    info.append("Cancelling illumination of down button on floor 2");

    //Load passengers
    info.append("Picking up passengers...");
    inUse1->loadPassengers(passenger3);
    inUse1->loadPassengers(passenger4);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse1->closeDoor(true));

    //Display the current state of the elevator in use
    info.append(inUse1->getInfo());

    //Move the elevator
    inUse1->setRequests(passenger3->chooseFloor(0));
    info.append(inUse1->getScreen()->displayFloor());
    moreInfo = elevatorControlSystem->moveElevator(inUse1, 0);
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse1->openDoor());

    //Unload Passengers
    info.append("Unloading passengers...");
    inUse1->unloadPassengers(passenger3);
    inUse1->unloadPassengers(passenger4);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse1->closeDoor(true));

    info.append(QString ("%1 is now %2").arg(inUse1->getName()).arg(inUse1->getState()));

    //Set elevator 1 to be inUse1
    elevatorControlSystem->replaceElevator(inUse1);

    //Move the elevator: 2nd request to go down
    moreInfo = elevatorControlSystem->moveElevator(inUse2, passenger1->getCurrFloor());
    //moveElevator function returns a list of QString to be printed to the console (since we cannot add stuff to GUI directly within ECS class)
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse2->openDoor());
    info.append("Cancelling illumination of down button on floor 3");

    //Load passengers
    info.append("Picking up passengers...");
    inUse2->loadPassengers(passenger1);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse2->closeDoor(true));

    //Display the current state of the elevator in use
    info.append(inUse2->getInfo());

    //Move the elevator
    inUse2->setRequests(passenger1->chooseFloor(0));
    info.append(inUse1->getScreen()->displayFloor());
    moreInfo = elevatorControlSystem->moveElevator(inUse2, 0);
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse2->openDoor());

    //Unload Passengers
    info.append("Unloading passengers...");
    inUse2->unloadPassengers(passenger1);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse2->closeDoor(true));

    info.append(QString ("%1 is now %2").arg(inUse2->getName()).arg(inUse2->getState()));

    //Set elevator 2 to be inUse2
    elevatorControlSystem->replaceElevator(inUse2);

    //Move the elevator: 3rd request to go down
    moreInfo = elevatorControlSystem->moveElevator(inUse3, passenger2->getCurrFloor());
    //moveElevator function returns a list of QString to be printed to the console (since we cannot add stuff to GUI directly within ECS class)
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse3->openDoor());
    info.append("Cancelling illumination of down button on floor 5");

    //Load passengers
    info.append("Picking up passengers...");
    inUse3->loadPassengers(passenger2);
    inUse3->loadPassengers(passenger5);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse3->closeDoor(true));

    //Display the current state of the elevator in use
    info.append(inUse3->getInfo());

    //Move the elevator
    inUse3->setRequests(passenger2->chooseFloor(0));
    info.append(inUse1->getScreen()->displayFloor());
    moreInfo = elevatorControlSystem->moveElevator(inUse3, 0);
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse3->openDoor());

    //Unload Passengers
    info.append("Unloading passengers...");
    inUse3->unloadPassengers(passenger2);
    inUse3->unloadPassengers(passenger5);

    //Close Elevator door
    info.append(bell->ring());
    //Simulate a fire signal being sent to the ECS
    inUse1->fireSignal(true);
    info.append(inUse3->closeDoor(true));

    info.append(QString ("%1 is now %2").arg(inUse3->getName()).arg(inUse3->getState()));

    //Set elevator 3 to be inUse3
    elevatorControlSystem->replaceElevator(inUse3);

    info.append("----------END OF NORMAL SIMULATION----------");

    //Print everything to the GUI
    connect(timer, SIGNAL(timeout()), this, SLOT(logToSystem()));
    timer->start(1000);
}

void MainWindow::overloadMode()
{
    timer->stop();
    info.clear();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(logToSystem()));

    info.append("----------START OF OVERLOAD SIMULATION----------");
    //Create Passengers
    info.append("Number of Passengers: 5");
    passenger1 = new Passengers("Sean", 140.5, 0);
    passenger2 = new Passengers("Sarah", 123.6, 0);
    passenger3 = new Passengers("Donald", 200.9, 0);
    passenger4 = new Passengers("Richard", 167.4, 0);
    passenger5 = new Passengers("Lil Mike", 76.0, 0);

    //Create Floors
    info.append("Number of Floors: 6");
    floor0 = new Floor(0);
    floor1 = new Floor(1);
    floor2 = new Floor(2);
    floor3 = new Floor(3);
    floor4 = new Floor(4);
    floor5 = new Floor(5);

    //Create Elevators
    info.append("Number of Elevators: 3");
    elevator1 = new Elevator(5, "Elevator 1");
    elevator2 = new Elevator(2, "Elevator 2");
    elevator3 = new Elevator(1, "Elevator 3");
    //inUse elevators will be set to one of the three elevators above
    inUse1 = new Elevator(0, "In Use");
    inUse2 = new Elevator(0, "In Use");
    inUse3 = new Elevator(0, "In Use");

    //Create Bell
    bell = new Bell();

    //Create Elevator Control System
    elevatorControlSystem = new ECS();
    elevatorControlSystem->setElevator(elevator1);
    elevatorControlSystem->setElevator(elevator2);
    elevatorControlSystem->setElevator(elevator3);
    elevatorControlSystem->setFloor(floor0);
    elevatorControlSystem->setFloor(floor1);
    elevatorControlSystem->setFloor(floor2);
    elevatorControlSystem->setFloor(floor3);
    elevatorControlSystem->setFloor(floor4);
    elevatorControlSystem->setFloor(floor5);

    //All passengers enter the building and are on the main floor (floor 0)

    //Simulate a passenger requesting an elevator
    info.append("NEW REQUEST!");
    info.append(QString ("Floor %1 has a request to go %2...illuminating %3 button for floor 0").arg(floor0->getFloorNum()).arg(passenger1->chooseDirection("up")).arg(passenger1->chooseDirection("up")));
    floor0->setDirection(passenger1->chooseDirection("up"));

    //ECS process the request and returns an idle or closest elevator
    inUse1 = elevatorControlSystem->getElevator(passenger1->getCurrFloor(), passenger1->getDirection());
    info.append(QString ("%1 retrieved...").arg(inUse1->getName()));

    //Move the elevator
    moreInfo = elevatorControlSystem->moveElevator(inUse1, passenger1->getCurrFloor());
    //moveElevator function returns a list of QString to be printed to the console (since we cannot add stuff to GUI directly within ECS class)
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse1->openDoor());
    info.append("Cancelling illumination of up button on floor 0");

    //Load passengers
    info.append("Picking up passengers...");
    inUse1->loadPassengers(passenger1);
    inUse1->loadPassengers(passenger2);
    inUse1->loadPassengers(passenger3);
    inUse1->loadPassengers(passenger4);
    inUse1->loadPassengers(passenger5);

    //Attempt to move elevator
    inUse1->setRequests(passenger1->chooseFloor(3));
    moreInfo = elevatorControlSystem->moveElevator(inUse1, 3);
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    info.append("----------END OF OVERLOAD SIMULATION----------");

    //print everything to the gui
    connect(timer, SIGNAL(timeout()), this, SLOT(logToSystem()));
    timer->start(1000);
}

void MainWindow::doorObstacleMode(){
    timer->stop();
    info.clear();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(logToSystem()));

    info.append("----------START OF DOOR OBSTACLE SIMULATION----------");
    //Create Passengers
    info.append("Number of Passengers: 5");
    passenger1 = new Passengers("Sean", 140.5, 0);
    passenger2 = new Passengers("Sarah", 123.6, 0);
    passenger3 = new Passengers("Donald", 200.9, 0);
    passenger4 = new Passengers("Richard", 167.4, 0);
    passenger5 = new Passengers("Lil Mike", 76.0, 0);

    //Create Floors
    info.append("Number of Floors: 6");
    floor0 = new Floor(0);
    floor1 = new Floor(1);
    floor2 = new Floor(2);
    floor3 = new Floor(3);
    floor4 = new Floor(4);
    floor5 = new Floor(5);

    //Create Elevators
    info.append("Number of Elevators: 3");
    elevator1 = new Elevator(5, "Elevator 1");
    elevator2 = new Elevator(2, "Elevator 2");
    elevator3 = new Elevator(1, "Elevator 3");
    //inUse elevators will be set to one of the three elevators above
    inUse1 = new Elevator(0, "In Use");
    inUse2 = new Elevator(0, "In Use");
    inUse3 = new Elevator(0, "In Use");

    //Create Bell
    bell = new Bell();

    //Create Elevator Control System
    elevatorControlSystem = new ECS();
    elevatorControlSystem->setElevator(elevator1);
    elevatorControlSystem->setElevator(elevator2);
    elevatorControlSystem->setElevator(elevator3);
    elevatorControlSystem->setFloor(floor0);
    elevatorControlSystem->setFloor(floor1);
    elevatorControlSystem->setFloor(floor2);
    elevatorControlSystem->setFloor(floor3);
    elevatorControlSystem->setFloor(floor4);
    elevatorControlSystem->setFloor(floor5);

    //All passengers enter the building and are on the main floor (floor 0)

    //Simulate a passenger requesting an elevator
    info.append("NEW REQUEST!");
    info.append(QString ("Floor %1 has a request to go %2...illuminating %3 button for floor 0").arg(floor0->getFloorNum()).arg(passenger1->chooseDirection("up")).arg(passenger1->chooseDirection("up")));
    floor0->setDirection(passenger1->chooseDirection("up"));

    //ECS process the request and returns an idle or closest elevator
    inUse1 = elevatorControlSystem->getElevator(passenger1->getCurrFloor(), passenger1->getDirection());
    info.append(QString ("%1 retrieved...").arg(inUse1->getName()));

    //Move the elevator
    moreInfo = elevatorControlSystem->moveElevator(inUse1, passenger1->getCurrFloor());
    //moveElevator function returns a list of QString to be printed to the console (since we cannot add stuff to GUI directly within ECS class)
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse1->openDoor());
    info.append("Cancelling illumination of up button on floor 0");

    //Load passengers
    info.append("Picking up passengers...");
    inUse1->loadPassengers(passenger1);
    inUse1->loadPassengers(passenger2);

    //Close Elevator door
    for (int i = 0; i < 10; i++){
        if (i == 5){
            info.append("Door obstacle has been interrupted multiple times...Please stop");
            info.append(inUse1->getAudio()->audioWarning());
            info.append(inUse1->getScreen()->displayWarning());
            break;
        }
        info.append(bell->ring());
        info.append(inUse1->closeDoor(false));
    }


    info.append("----------END OF DOOR OBSTACLE SIMULATION----------");

    //print everything to the gui
    connect(timer, SIGNAL(timeout()), this, SLOT(logToSystem()));
    timer->start(1000);

}

void MainWindow::helpMode(){
    timer->stop();
    info.clear();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(logToSystem()));

    info.append("----------START OF HELP MODE SIMULATION----------");
    //Create Passengers
    info.append("Number of Passengers: 5");
    passenger1 = new Passengers("Sean", 140.5, 0);
    passenger2 = new Passengers("Sarah", 123.6, 0);
    passenger3 = new Passengers("Donald", 200.9, 0);
    passenger4 = new Passengers("Richard", 167.4, 0);
    passenger5 = new Passengers("Lil Mike", 76.0, 0);

    //Create Floors
    info.append("Number of Floors: 6");
    floor0 = new Floor(0);
    floor1 = new Floor(1);
    floor2 = new Floor(2);
    floor3 = new Floor(3);
    floor4 = new Floor(4);
    floor5 = new Floor(5);

    //Create Elevators
    info.append("Number of Elevators: 3");
    elevator1 = new Elevator(5, "Elevator 1");
    elevator2 = new Elevator(2, "Elevator 2");
    elevator3 = new Elevator(1, "Elevator 3");
    //inUse elevators will be set to one of the three elevators above
    inUse1 = new Elevator(0, "In Use");
    inUse2 = new Elevator(0, "In Use");
    inUse3 = new Elevator(0, "In Use");

    //Create Bell
    bell = new Bell();

    //Create Elevator Control System
    elevatorControlSystem = new ECS();
    elevatorControlSystem->setElevator(elevator1);
    elevatorControlSystem->setElevator(elevator2);
    elevatorControlSystem->setElevator(elevator3);
    elevatorControlSystem->setFloor(floor0);
    elevatorControlSystem->setFloor(floor1);
    elevatorControlSystem->setFloor(floor2);
    elevatorControlSystem->setFloor(floor3);
    elevatorControlSystem->setFloor(floor4);
    elevatorControlSystem->setFloor(floor5);

    //All passengers enter the building and are on the main floor (floor 0)

    //Simulate a passenger requesting an elevator
    info.append("NEW REQUEST!");
    info.append(QString ("Floor %1 has a request to go %2...illuminating %3 button for floor 0").arg(floor0->getFloorNum()).arg(passenger1->chooseDirection("up")).arg(passenger1->chooseDirection("up")));
    floor0->setDirection(passenger1->chooseDirection("up"));

    //ECS process the request and returns an idle or closest elevator
    inUse1 = elevatorControlSystem->getElevator(passenger1->getCurrFloor(), passenger1->getDirection());
    info.append(QString ("%1 retrieved...").arg(inUse1->getName()));

    //Move the elevator
    moreInfo = elevatorControlSystem->moveElevator(inUse1, passenger1->getCurrFloor());
    //moveElevator function returns a list of QString to be printed to the console (since we cannot add stuff to GUI directly within ECS class)
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(bell->ring());
    info.append(inUse1->openDoor());
    info.append("Cancelling illumination of up button on floor 0");

    //Load passengers
    info.append("Picking up passengers...");
    inUse1->loadPassengers(passenger1);
    inUse1->loadPassengers(passenger2);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse1->closeDoor(true));

    //Display the current state of the elevator in use
    info.append(inUse1->getInfo());

    //Simulate a help request from a passenger from within the elevator
    //This will return more then one QString, hence the for loop to append to info
    moreInfo = elevatorControlSystem->helpRequest(passenger1, 6);
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    info.append("----------END OF HELP MODE SIMULATION----------");

    //Print everything to the GUI
    connect(timer, SIGNAL(timeout()), this, SLOT(logToSystem()));
    timer->start(1000);

}

void MainWindow::fireMode(){
    timer->stop();
    info.clear();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(logToSystem()));

    info.append("----------START OF FIRE MODE SIMULATION----------");
    //Create Passengers
    info.append("Number of Passengers: 5");
    passenger1 = new Passengers("Sean", 140.5, 0);
    passenger2 = new Passengers("Sarah", 123.6, 0);
    passenger3 = new Passengers("Donald", 200.9, 0);
    passenger4 = new Passengers("Richard", 167.4, 0);
    passenger5 = new Passengers("Lil Mike", 76.0, 0);

    //Create Floors
    info.append("Number of Floors: 6");
    floor0 = new Floor(0);
    floor1 = new Floor(1);
    floor2 = new Floor(2);
    floor3 = new Floor(3);
    floor4 = new Floor(4);
    floor5 = new Floor(5);

    //Create Elevators
    info.append("Number of Elevators: 3");
    elevator1 = new Elevator(5, "Elevator 1");
    elevator2 = new Elevator(2, "Elevator 2");
    elevator3 = new Elevator(1, "Elevator 3");
    //inUse elevators will be set to one of the three elevators above
    inUse1 = new Elevator(0, "In Use");
    inUse2 = new Elevator(0, "In Use");
    inUse3 = new Elevator(0, "In Use");

    //Create Bell
    bell = new Bell();

    //Create Elevator Control System
    elevatorControlSystem = new ECS();
    elevatorControlSystem->setElevator(elevator1);
    elevatorControlSystem->setElevator(elevator2);
    elevatorControlSystem->setElevator(elevator3);
    elevatorControlSystem->setFloor(floor0);
    elevatorControlSystem->setFloor(floor1);
    elevatorControlSystem->setFloor(floor2);
    elevatorControlSystem->setFloor(floor3);
    elevatorControlSystem->setFloor(floor4);
    elevatorControlSystem->setFloor(floor5);

    //All passengers enter the building and are on the main floor (floor 0)

    //Simulate a passenger requesting an elevator
    info.append("NEW REQUEST!");
    info.append(QString ("Floor %1 has a request to go %2...illuminating %3 button for floor 0").arg(floor0->getFloorNum()).arg(passenger1->chooseDirection("up")).arg(passenger1->chooseDirection("up")));
    floor0->setDirection(passenger1->chooseDirection("up"));

    //ECS process the request and returns an idle or closest elevator
    inUse1 = elevatorControlSystem->getElevator(passenger1->getCurrFloor(), passenger1->getDirection());
    info.append(QString ("%1 retrieved...").arg(inUse1->getName()));

    //Move the elevator
    moreInfo = elevatorControlSystem->moveElevator(inUse1, passenger1->getCurrFloor());
    //moveElevator function returns a list of QString to be printed to the console (since we cannot add stuff to GUI directly within ECS class)
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(inUse1->openDoor());

    //Load passengers
    info.append("Picking up passengers...");
    inUse1->loadPassengers(passenger1);
    inUse1->loadPassengers(passenger2);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse1->closeDoor(true));

    //Display the current state of the elevator in use
    info.append(inUse1->getInfo());

    //Simulate a fire signal being sent to the ECS
    inUse1->fireSignal(true);

    //Move the elevator
    inUse1->setRequests(passenger1->chooseFloor(3));
    info.append(inUse1->getScreen()->displayFloor());
    moreInfo = elevatorControlSystem->moveElevator(inUse1, 3);
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(inUse1->openDoor());

    //Unload Passengers
    info.append("Unloading passengers...");
    inUse1->unloadPassengers(passenger3);
    inUse1->unloadPassengers(passenger4);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse1->closeDoor(true));

    info.append("----------END OF FIRE MODE SIMULATION----------");

    //Print everything to the GUI
    connect(timer, SIGNAL(timeout()), this, SLOT(logToSystem()));
    timer->start(1000);
}

void MainWindow::poweroutMode(){
    timer->stop();
    info.clear();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(logToSystem()));

    info.append("----------START OF POWER OUT MODE SIMULATION----------");
    //Create Passengers
    info.append("Number of Passengers: 5");
    passenger1 = new Passengers("Sean", 140.5, 0);
    passenger2 = new Passengers("Sarah", 123.6, 0);
    passenger3 = new Passengers("Donald", 200.9, 0);
    passenger4 = new Passengers("Richard", 167.4, 0);
    passenger5 = new Passengers("Lil Mike", 76.0, 0);

    //Create Floors
    info.append("Number of Floors: 6");
    floor0 = new Floor(0);
    floor1 = new Floor(1);
    floor2 = new Floor(2);
    floor3 = new Floor(3);
    floor4 = new Floor(4);
    floor5 = new Floor(5);

    //Create Elevators
    info.append("Number of Elevators: 3");
    elevator1 = new Elevator(5, "Elevator 1");
    elevator2 = new Elevator(2, "Elevator 2");
    elevator3 = new Elevator(1, "Elevator 3");
    //inUse elevators will be set to one of the three elevators above
    inUse1 = new Elevator(0, "In Use");
    inUse2 = new Elevator(0, "In Use");
    inUse3 = new Elevator(0, "In Use");

    //Create Bell
    bell = new Bell();

    //Create Elevator Control System
    elevatorControlSystem = new ECS();
    elevatorControlSystem->setElevator(elevator1);
    elevatorControlSystem->setElevator(elevator2);
    elevatorControlSystem->setElevator(elevator3);
    elevatorControlSystem->setFloor(floor0);
    elevatorControlSystem->setFloor(floor1);
    elevatorControlSystem->setFloor(floor2);
    elevatorControlSystem->setFloor(floor3);
    elevatorControlSystem->setFloor(floor4);
    elevatorControlSystem->setFloor(floor5);

    //All passengers enter the building and are on the main floor (floor 0)

    //Simulate a passenger requesting an elevator
    info.append("NEW REQUEST!");
    info.append(QString ("Floor %1 has a request to go %2...illuminating %3 button for floor 0").arg(floor0->getFloorNum()).arg(passenger1->chooseDirection("up")).arg(passenger1->chooseDirection("up")));
    floor0->setDirection(passenger1->chooseDirection("up"));

    //ECS process the request and returns an idle or closest elevator
    inUse1 = elevatorControlSystem->getElevator(passenger1->getCurrFloor(), passenger1->getDirection());
    info.append(QString ("%1 retrieved...").arg(inUse1->getName()));

    //Move the elevator
    moreInfo = elevatorControlSystem->moveElevator(inUse1, passenger1->getCurrFloor());
    //moveElevator function returns a list of QString to be printed to the console (since we cannot add stuff to GUI directly within ECS class)
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(inUse1->openDoor());

    //Load passengers
    info.append("Picking up passengers...");
    inUse1->loadPassengers(passenger1);
    inUse1->loadPassengers(passenger2);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse1->closeDoor(true));

    //Display the current state of the elevator in use
    info.append(inUse1->getInfo());

    //Simulate the ECS power being turned off
    elevatorControlSystem->turnPowerOff();

    //Move the elevator
    inUse1->setRequests(passenger1->chooseFloor(3));
    info.append(inUse1->getScreen()->displayFloor());
    moreInfo = elevatorControlSystem->moveElevator(inUse1, 3);
    for (int i = 0; i < moreInfo.size(); i++){
        info.append(moreInfo.at(i));
    }

    //Open Elevator door
    info.append(inUse1->openDoor());

    //Unload Passengers
    info.append("Unloading passengers...");
    inUse1->unloadPassengers(passenger3);
    inUse1->unloadPassengers(passenger4);

    //Close Elevator door
    info.append(bell->ring());
    info.append(inUse1->closeDoor(true));

    info.append("----------END OF POWER OUT MODE SIMULATION----------");

    //Print everything to the GUI
    connect(timer, SIGNAL(timeout()), this, SLOT(logToSystem()));
    timer->start(1000);
}


void MainWindow::logToSystem()
{
    if(info.size() == 0){
        return;
    }
    QString addInfo = info.at(0);
    info.pop_front();
    ui->ecsLog->addItem(addInfo);
    return;
}
