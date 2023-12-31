#include "EntityManager.h"


void EntityManager::tick(){


    for(unsigned int i=0; i<entities.size(); i++){
        entities[0]->tick();
    }
    if(firstClient != nullptr){
        firstClient->tick();
        if(firstClient->getPatience()==0){
            clientsLeaved++;
        }
    }
    removeLeavingClients();
    if(clientsLeaved==10) {
        didilose=true;
        clientsLeaved=0;
        }
}
void EntityManager::changeLoseState(){
    if(didilose) didilose=false;
}

int EntityManager::inspectorLeaving(int money){
    if(firstClient->isInspector && (firstClient->getPatience() == 1)) {
        return money / 2;
    } else {
        return money;
    }
}

void EntityManager::removeLeavingClients(){

    // Remove all clients that are leaving
    Client* tempClient = firstClient;
    Client* prevClient = nullptr;
    
    while(tempClient != nullptr){
        if(tempClient->isLeaving){


            if(prevClient == nullptr){
                firstClient = tempClient->nextClient;
                delete tempClient;
                tempClient = firstClient;

            }else{
                prevClient->nextClient = tempClient->nextClient;
                delete tempClient;
                tempClient = prevClient->nextClient;
            }
        }else{
            prevClient = tempClient;
            tempClient = tempClient->nextClient;
        }
    }
        
}

bool EntityManager::loseGame(){
        return didilose;
    }

void EntityManager::render(){
    for(unsigned int i=0; i<entities.size(); i++){
        entities[i]->render();
    }
    if(firstClient != nullptr){
        firstClient->render();
    }
}

void EntityManager::addEntity(Entity *e){
    entities.push_back(e);
}

void EntityManager::addClient(Client* c){
    if(firstClient == nullptr){
        firstClient = c;
    }else{
        Client* tempClient = firstClient;
        tempClient->setY(tempClient->getY()+72);
        while(tempClient->nextClient!=nullptr){
            tempClient = tempClient->nextClient;
            tempClient->setY(tempClient->getY()+72);

        }
        tempClient->nextClient = c;
    }
}