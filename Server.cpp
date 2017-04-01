//
// Created by archie on 4/1/17.
//

#include "Server.h"

Server::Server() {
    clientPipeName = "fromClient";
    serverPipeName = "fromServer";
}

void Server::run() {
    communicator.createIO(serverPipeName, clientPipeName, false);
    communicator.createTunnel();
    string encMsg = communicator.readEncryptedMsg();
    verifyClient();
}

void Server::verifyClient() {
    setupFFSParameters();
    int correctAnswers = 0;

    for(int i = 0; i < tSecurityParameter; i++) {
        readX();
        sendRandomBitsVector();
        readResponse();
        if(isResponseOk())
            correctAnswers++;
    }

    if(correctAnswers == tSecurityParameter)
        cout << "CLIENT VERIFIED" << endl;
    else
        cout << "ERROR: CLIENT NOT VERIFIED" << endl;
}

void Server::setupFFSParameters() {
    mpz_class commonModulus("71183552285038461766113647959396358732706491637429430926545437207184125238309080283521732845130075390845656628117522464822858239853139020661108679805853177746229905002767516006612801512117052998585896447280921555208648711629997437345455618254036492687238619118038417360819908894719307131044594675256506148315721871893790592922471352116368798813460668095376709055498641058388154371624108496453083237469650211111431015970756158890041945366886657631236160844900022246123320938053062120230536865298378252895800036092900147260312150394885899649114326431821546855506303256064596753532612324481383960608160126983904724442161", base);
    ffs.setNCommonModulus(commonModulus);
    //readPublicVector(); // namiesto toho len vygenerovat public a dat ho sem na tvrdo, potom asi to bude viac splnat poziadavky
    //ffs.setPublicVector(ffs1.getPublicVector());
}

void Server::readX() {

}

void Server::sendRandomBitsVector() {

}

void Server::readResponse() {

}

bool Server::isResponseOk() {
    return false;
}


