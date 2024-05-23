#include "Login.h"

Login::Login(MainWindow* main_window, QWidget* parent) : QWidget(parent), main_window(main_window){

    vlayout = new QVBoxLayout(this);
    vlayout->setAlignment(Qt::AlignCenter);

    QLabel* label = new QLabel();
    label->setText((MainWindow::isInEnglish()) ? "Enter your pseudo" : "Entrez votre pseudo");
    label->setAlignment(Qt::AlignHCenter);
    vlayout->addWidget(label);

    input = new QLineEdit();
    vlayout->addWidget(input);

    QPushButton* button = new QPushButton();
    button->setText("Let's play !");
    QObject::connect(button, SIGNAL(clicked()), this, SLOT(buttonClick()));

    vlayout->addWidget(button);

    infos = new QLabel;
    infos->setAlignment(Qt::AlignCenter);
    vlayout->addWidget(infos);

    new_connection = new QPushButton;
    new_connection->setText((MainWindow::isInEnglish()) ? "Log in" : "Se connecter");

    new_connection_button_displayed = false;
}

Login::~Login(){
    qDebug() << this;
}

void Login::buttonClick(){
    if(input->text() == ""){
        infos->setText((MainWindow::isInEnglish()) ? "This field must be filled in!" : "IL FAUT REMPLIR CE CHAMP !!!");
        if(new_connection_button_displayed){
            QObject::disconnect(new_connection, SIGNAL(clicked()), this, SLOT(newConnection()));
            new_connection_button_displayed = false;
        }
    }
    else if(input->text().indexOf("$$$") != -1 || input->text().indexOf("(") != -1 || input->text().indexOf(")") != -1 || input->text().indexOf("{") != -1 || input->text().indexOf("}") != -1 || input->text().indexOf("[") != -1 || input->text().indexOf("]") != -1){
        infos->setText(
            (MainWindow::isInEnglish()) ? 
                "Forbidden character strings : \"$$$\", \"(\", \")\", \"{\", \"}\", \"[\", \"]\"" :
                "Suite de charactères impossible : \"$$$\", \"(\", \")\", \"{\", \"}\", \"[\", \"]\""
        ); // May cause problems in player_data.txt file
        if(new_connection_button_displayed){
            QObject::disconnect(new_connection, SIGNAL(clicked()), this, SLOT(newConnection()));
            new_connection_button_displayed = false;
        }
    }
    else{
        QString login = main_window->getPlayerData()->exists(input->text());
        if(login != ""){
            main_window->getPlayerData()->setCurrentPlayer(login);
            main_window->getStackedWidget()->setCurrentIndex(1);
            main_window->getMenu()->reloadConnectName();
        }
        else{
            infos->setText(
                (MainWindow::isInEnglish()) ? 
                    "You are about to log in as \"" + input->text() + "\"\nYour scores and records will be saved under this nickname" :
                    "Vous êtes sur le point de vous connecter en tant que \"" + input->text() + "\"\nVos scores et records vont être enregistrés sous ce pseudonyme"
            );
            if(!new_connection_button_displayed){
                vlayout->addWidget(new_connection);
                QObject::connect(new_connection, SIGNAL(clicked()), this, SLOT(newConnection()));
                new_connection_button_displayed = true;
            }
        }
    }
}

void Login::newConnection() {
    main_window->getPlayerData()->addNew(input->text());
    main_window->getPlayerData()->setCurrentPlayer(input->text());
    main_window->getStackedWidget()->setCurrentIndex(1);
    main_window->getMenu()->reloadConnectName();
}