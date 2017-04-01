#include <iostream>
#include "Communicator.h"
#include <gmp.h>
#include <gmpxx.h>
#include "Hash.h"
#include "FFS.h"

using namespace std;

bool isArgumentCorrect(char* argument){
    string arg(argument);
    return (arg == "-c" || arg == "-s");
}
bool isArgClient(string arg){
    return arg == "-c";
}

//TODO: skusit odoslat a prijat spravu
/*TODO: typedef std::basic_string <unsigned char> ustring; pouzit mozno*/

int main(int argc, char* argv[])
{
    if(argc <2 || !isArgumentCorrect(argv[1])){
        std::cerr << "Help: run either with -s or -c parameter." << std::endl;
        return 1;
    }
    string argument(argv[1]);
    std::cout << argument << std::endl;

    string clientPipeName = "fromClient";
    string serverPipeName = "fromServer";

    string message = "Mega tajna sprava!";


    FFS ffs1;
    mpz_class commonModulus("71183552285038461766113647959396358732706491637429430926545437207184125238309080283521732845130075390845656628117522464822858239853139020661108679805853177746229905002767516006612801512117052998585896447280921555208648711629997437345455618254036492687238619118038417360819908894719307131044594675256506148315721871893790592922471352116368798813460668095376709055498641058388154371624108496453083237469650211111431015970756158890041945366886657631236160844900022246123320938053062120230536865298378252895800036092900147260312150394885899649114326431821546855506303256064596753532612324481383960608160126983904724442161", base);
    ffs1.setNCommonModulus(commonModulus);
    vector<mpz_class> secretVector(kSecurityParameter);
    secretVector[0].set_str("136827859846771060061321313951253829248421754124379543570821546843405384043503947705691271975790207803393765271958550017433953723651621810741089442773919809221238474388354127362629844815263298255575172311538765764262659859831104305696498874131964419755002685636291012603720546510520537088008979729691737711014", base);
    secretVector[1].set_str("139359891237958025510083189738077776755906133660175129016509619367375595277855509652792050995038229507214895360903455883327684029715424178963193779692119246710064538950162456638588100887985040506700449770799362485515382653423820410105764890460428820448844184770817882414525812143159165140172030155769523698795", base);
    secretVector[2].set_str("165461796236407703655974303018449444837186717130299722033385928748918223286107671786275921447897583170689765785990823051520854625945901791959936267906757251509731551288744272623222660489152727531296040506294218076040302791195990136366879510598537696867551544931704008382136344158632789550553271702016227580396", base);
    secretVector[3].set_str("57022560656565110588960213982306305072627715783796028105371684293524342952643311499847625694714821661799097225001795355762246215062873184417006071696746414606958585072119500870869277758884540764516461818146021532618403395449131841221113117938391371607980590442533079489728044225541072483695630902526884845961", base);
    secretVector[4].set_str("134029172653024414137663716647901589050361529567074459847722922511106226604838382178591371463086143826416393548212773267580116363389523169317680896939930753880387129430457065779588257929879007593480671851764201489853123275894649860710707184824828192676955458182680468174385992512438833533165285477350643332467", base);
    ffs1.setSecretVector(secretVector);
    ffs1.calculatePublicVector();

    //Client generuje random bit - challenge vector kt, posle serveru
    FFS ffs2;
    ffs2.setNCommonModulus(commonModulus);
    vector<unsigned long> randBitsVect = ffs2.generateRandomBitsVector();

    //komunikacia
    ffs2.setPublicVector(ffs1.getPublicVector());
    ffs2.setRandomBitsVector(randBitsVect);
    ffs1.setRandomBitsVector(randBitsVect);
//    ffs1.calculateXForB();
//    ffs1.calculateResponse();
    ffs2.setXForB(ffs1.calculateXForB());
    bool isResponseOk = ffs2.verifyResponse(ffs1.calculateResponse());

    cout << "log debug: isResponseOk = " << isResponseOk << endl;


//    string hash = Hash::createSHA256(message);
//    string testHash("Hello world");
//    Hash::createSHA256(testHash);
//    bool hashCorretness = Hash::isHashCorrect(hash, message);
//    cout << "HASH = = " << hashCorretness << endl;


//    if(isArgClient(argument)){
//        std::cout << "HUraa klient" << std::endl;
//        Communicator client;
//        client.createIO(clientPipeName, serverPipeName, true);
//        client.readMsg();
//        client.createTunnel();
//        client.sendEncryptedMsg(message);
//    }
//    else{
//        std::cout << "HUraa server" << std::endl;
//        Communicator server;
//        server.createIO(serverPipeName, clientPipeName, false);
//        server.sendMsg("Helloooooo Woooorld!");
//        server.createTunnel();
//        string encMsg = server.readEncryptedMsg();
//    }

    printf("KONIEC PROGRAMU");
    return 0;
}