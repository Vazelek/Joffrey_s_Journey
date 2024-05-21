#include "include/PlayerData.h"

PlayerData::PlayerData(){
    data = new QMap<QString, QVector<QMap<QString, QString>*>*>;
    records = new QVector<QMap<QString, QString>*>;
    readDataFile();
    readRecords();
}

PlayerData::~PlayerData(){
    writeDataFile();
    writeRecords();
    for(auto vector : *data){
        delete vector;
    }
    delete data;
}

QMap<QString, QVector<QMap<QString, QString>*>*>* PlayerData::getData(){
    return data;
}

QVector<QMap<QString, QString>*>* PlayerData::getPlayerData(){
    return data->value(current_player);
}

QVector<QMap<QString, QString>*>* PlayerData::getRecords(){
    return records;
}

QString PlayerData::getCurrentPlayer(){
    return current_player;
}

void PlayerData::readDataFile(){
    std::string line = "";
    std::string player = "";
    std::string values[3] = {""};
    std::ifstream file("data/player_data.txt");
    int index = 0;
    if(file.is_open()){

        getline(file, line);

        while(line.find("$$$") == std::string::npos){
            while(line.find("{") == std::string::npos){
                getline(file, line);
            }

            player = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
            QVector<QMap<QString, QString>*>* player_data = new QVector<QMap<QString, QString>*>;

            while(line.find("}") == std::string::npos){

                // Check for extra blanks
                if(line.find("[") == std::string::npos){
                    getline(file, line);
                    continue;
                }

                QMap<QString, QString>* level_data = new QMap<QString, QString>;

                index = 0;
                while(line.find("]") == std::string::npos){
                    if(line.find("(") != std::string::npos){
                        values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                        index++;
                    }
                    getline(file, line);
                }

                level_data->insert("score", QString::fromStdString(values[0]));
                level_data->insert("star", QString::fromStdString(values[1]));
                level_data->insert("time", QString::fromStdString(values[2]));

                player_data->push_back(level_data);

                for(int i = 0; i < 3; i++){
                    values[i] = "";
                }

                getline(file, line);
            }

            data->insert(QString::fromStdString(player), player_data);

            getline(file, line);
        }
    }
    file.close();
}

void PlayerData::writeDataFile(){
    std::ofstream file ("data/player_data.txt");
    int index = 0;
    if(file.is_open()){

        for(auto player_data : *data){

            file << "(" << data->key(player_data).QString::toStdString() << "){" << std::endl;

            for(int i = 0; i < player_data->size(); i++){

                file << "    [" << std::endl;

                for(auto level_data : *player_data->value(i)){

                    file << "        " << player_data->value(i)->key(level_data).QString::toStdString() << ": (" << level_data.toStdString() << ")" << std::endl;

                }

                file << "    ]";

                if(i < player_data->size() - 1){
                    file << ",";
                }

                file << std::endl;

            }

            file << "}" << std::endl;

            index++;

            if(index != data->size()){
                file << std::endl;
            }
        }

        file << "$$$";
    }

    file.close();
}

void PlayerData::readRecords() {
    std::string line = "";
    std::string values[4] = {""};
    std::ifstream file("data/records.txt");
    int index = 0;
    if(file.is_open()){

        getline(file, line);

        for(int level = 0; level < 6; level++){
            while(line.find("{") == std::string::npos){
                getline(file, line);
            }

            QMap<QString, QString>* level_data = new QMap<QString, QString>;
            index = 0;

            while(line.find("}") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            if(exists(QString::fromStdString(values[1])) != ""){
                level_data->insert("score", QString::fromStdString(values[0]));
                level_data->insert("score_player", QString::fromStdString(values[1]));
            }
            else{
                level_data->insert("score", "0");
                level_data->insert("score_player", "");
            }

            if(exists(QString::fromStdString(values[3])) != ""){
                level_data->insert("time", QString::fromStdString(values[2]));
                level_data->insert("time_player", QString::fromStdString(values[3]));
            }
            else{
                level_data->insert("time", "00:00");
                level_data->insert("time_player", "");
            }

            records->push_back(level_data);

            for(int i = 0; i < 4; i++){
                values[i] = "";
            }

            getline(file, line);
        }
    }
    file.close();
}

void PlayerData::writeRecords() {
    std::ofstream file ("data/records.txt");
    int index = 0;
    if(file.is_open()){

        for(auto level : *records){

            file << "Level " << index << "{" << std::endl;
            file << "    score: (" << level->value("score").toStdString() << ")," << std::endl;
            file << "    score_player: (" << level->value("score_player").toStdString() << ")," << std::endl;
            file << "    time: (" << level->value("time").toStdString() << ")," << std::endl;
            file << "    time_player: (" << level->value("time_player").toStdString() << ")" << std::endl;
            file << "}\n" << std::endl;

            index++;
        }
    }

    file.close();
}

void PlayerData::setCurrentPlayer(QString p_name){
    current_player = p_name;
}

void PlayerData::addNew(QString str){
    QVector<QMap<QString, QString>*>* player_data = new QVector<QMap<QString, QString>*>;
    for(int i = 0; i < 5; i++){
        QMap<QString, QString>* level_data = new QMap<QString, QString>;
        level_data->insert("score", "0");
        level_data->insert("time", "00:00");
        level_data->insert("star", "0/0/0/0");
        player_data->push_back(level_data);
    }

    data->insert(str, player_data);
}

QString PlayerData::exists(QString player){
    for(auto player_data : *data){
        if(data->key(player_data).toLower() == player.toLower()){
            return data->key(player_data);
        }
    }
    return "";
}

void PlayerData::updatePlayerData(int level, int score, QString time){
    auto level_data = data->value(current_player)->value(level);
    if(level_data->value("score").toInt() < score){
        (*level_data)["score"] = QString::number(score);
        if(score > records->value(level)->value("score").toInt()){
            (*(records->value(level)))["score"] = QString::number(score);
            (*(records->value(level)))["score_player"] = current_player;
        }
    }

    if(level_data->value("time") == "00:00"){
        (*level_data)["time"] = time;
    }
    else if(time.left(time.indexOf(":")).toInt() < level_data->value("time").left(level_data->value("time").indexOf(":")).toInt()){
       (*level_data)["time"] = time;
    }
    else{
        if(time.left(time.indexOf(":")).toInt() == level_data->value("time").left(level_data->value("time").indexOf(":")).toInt()){
            if(time.right(time.size() - time.indexOf(":") - 1).toFloat() < level_data->value("time").right(level_data->value("time").size() - level_data->value("time").indexOf(":") - 1).toFloat()){
                (*level_data)["time"] = time;
            }
        }
    }

    if(records->value(level)->value("time") == "00:00"){
        (*records->value(level))["time"] = time;
        (*(records->value(level)))["time_player"] = current_player;
    }
    else if(time.left(time.indexOf(":")).toInt() < records->value(level)->value("time").left(records->value(level)->value("time").indexOf(":")).toInt()){
       (*records->value(level))["time"] = time;
       (*(records->value(level)))["time_player"] = current_player;
    }
    else{
        if(time.left(time.indexOf(":")).toInt() == records->value(level)->value("time").left(records->value(level)->value("time").indexOf(":")).toInt()){
            if(time.right(time.size() - time.indexOf(":") - 1).toFloat() < records->value(level)->value("time").right(records->value(level)->value("time").size() - records->value(level)->value("time").indexOf(":") - 1).toFloat()){
                (*records->value(level))["time"] = time;
                (*(records->value(level)))["time_player"] = current_player;
            }
        }
    }
}

void PlayerData::updatePlayerStars(int level, QString stars) {
    auto level_data = data->value(current_player)->value(level);
    QStringList obtained_stars = stars.split(QLatin1Char('/'));
    QStringList saved_stars = (*level_data)["star"].split(QLatin1Char('/'));
    int count_obtained_stars = 0;
    int count_saved_stars = 0;
    for(int i = 0; i < 4; i++){
        count_obtained_stars += obtained_stars[i].toInt();
        count_saved_stars += saved_stars[i].toInt();
    }

    if(count_obtained_stars >= count_saved_stars){
        (*level_data)["star"] = stars;
    }
}