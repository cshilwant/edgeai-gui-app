#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringListModel>
#include <QNetworkInterface>
#include <QDirIterator>
#include <csignal>
#include <thread>
#include <unistd.h>
#include <sys/stat.h>
#include "Backend.h"
#include <gst/gst.h>

QStringListModel cameraNamesList;
QStringListModel modelNamesList;

Backend backend;

void sigHandler(int s)
{
    std::signal(s, SIG_DFL);
    qApp->quit();
}

void GetIpAddr()
{
    // Get SDK Version
    const string SDK_VER = string(std::getenv("EDGEAI_VERSION"));
    if (SDK_VER != "")
    {
        backend.sdk_ver = "<font color=\"#FEFFFF\">Version: </font>\
                           <font color=\"#00FF00\">" +
                           QString::fromStdString(SDK_VER) +
                           "</font>";
    }
    backend.set_ip_addr("");

    QString ip;
    // Fetch IP Addr of the target to display at the bottom of the application
    for(int i = 0; i < 10; i++) {
        foreach (const QNetworkInterface &netInterface, QNetworkInterface::allInterfaces()) {
            QNetworkInterface::InterfaceFlags flags = netInterface.flags();
            if( (bool)(flags & QNetworkInterface::IsRunning) && !(bool)(flags & QNetworkInterface::IsLoopBack)){
                foreach (const QNetworkAddressEntry &address, netInterface.addressEntries()) {
                    if(address.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                        ip = "<font color=\"#FEFFFF\">IP: </font>\
                              <font color=\"#00FF00\">" +
                              address.ip().toString() +
                              "</font>";
                        backend.set_ip_addr(ip);
                        emit backend.ip_addr_changed();
                        return;
                    }
                }
            }
        }
        sleep(10);
    }
    return;
}

int main(int argc, char *argv[]) {

    gst_init (&argc, &argv);
    QStringList list = cameraNamesList.stringList();
    QStringList modelslist = modelNamesList.stringList();
    fstream modelsfile;
    struct stat sb;

    thread getIpAddrThread(GetIpAddr);
    getIpAddrThread.detach();

    QGuiApplication app(argc, argv);

    std::signal(SIGINT,  sigHandler);
    std::signal(SIGTERM, sigHandler);

    QQmlApplicationEngine engine;

    // Get SOC
    const char* SOC = std::getenv("SOC");
    backend.soc = SOC;

    // Get and Populate CameraInfo to CameraList
    map<string, map<string,string>> cameraInfo;
    backend.getCameraInfo(cameraInfo);

    for ( const auto &data : cameraInfo ) {
        for ( const auto &detailedData : data.second )
        {
            if (detailedData.first.find("device") != string::npos)
            {
                string fullName,device;
                device = backend.replaceAll(detailedData.first,"device","");
                device = backend.trimString(device);
                fullName = data.first;
                if (device.length() > 0)
                    fullName += " " + device;
                list.append(QString::fromStdString(fullName));
            }
        }
    }
    cameraNamesList.setStringList(list);

    // Get and Populate contents of /opt/oob-demo-assets/allowedModels.txt to modelNamesList
    // Add the model to list only if it's available in the filesystem
    if (strcmp(SOC, "am62a") == 0) {
        modelsfile.open("/opt/oob-demo-assets/allowedModels.txt",ios::in);
        if (modelsfile.is_open()) {
            string model;
            while(getline(modelsfile, model)) {
                string dir = "/opt/model_zoo/";
                if (stat((dir + model).c_str(), &sb) == 0)
                {
                    modelslist.append(QString::fromStdString(model));
                }
            }
            modelsfile.close();
        }
    } else {
        QDirIterator iterateFolders("/opt/model_zoo", QDir::Dirs | QDir::NoDotAndDotDot);
        while (iterateFolders.hasNext())
        {
            iterateFolders.next();
            modelslist.append(iterateFolders.fileName());
        }
    }

    modelNamesList.setStringList(modelslist);

    // set context properties to access in QML
    engine.rootContext()->setContextProperty("backend", &backend);
    engine.rootContext()->setContextProperty("cameraNamesList", &cameraNamesList);
    engine.rootContext()->setContextProperty("modelNamesList", &modelNamesList);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    int ret = app.exec();

    gst_deinit ();
    
    return ret;

}
