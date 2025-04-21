#ifndef _BACKEND_H_
#define _BACKEND_H_

#include <QObject>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <QStringListModel>
#include <gst_pipelines/am62a_pipelines.h>
#include <gst_pipelines/j721e_pipelines.h>
#include <gst_pipelines/j721s2_pipelines.h>
#include <gst_pipelines/j784s4_pipelines.h>
#include <gst_pipelines/j722s_pipelines.h>
#include <misc/content.h>
#include <gst/gst.h>
#include <QDebug>
#include <QQuickItem>

using namespace std;

class Backend : public QObject {
    Q_OBJECT

private:
    string pipeline;
    GstElement *gst_pipeline = NULL;

    void addSink(string &pipeline, int xPos, int yPos, int width, int height);
    void generateYaml(QString userInputType, QString userInputFile, QString userModel);
    string getPipelineString();

    QString ip_addr_p;

public:
    string  soc;
    QString sdk_ver;
    quint32 easter_egg_click_cnt = 0;

    explicit Backend (QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void increase_easter_egg_click_cnt();
    Q_INVOKABLE quint32 get_easter_egg_click_cnt();
    Q_INVOKABLE QString get_random_content();
    Q_INVOKABLE QString ip_addr();
    Q_INVOKABLE void leftMenuButtonPressed(int button, int x, int y, int width, int height, QObject* object);
    Q_INVOKABLE void startVideo(QObject* object, QString pipeline);
    Q_INVOKABLE void stopVideo();
    Q_INVOKABLE void popupOkPressed(QString InputType, QString Input, QString Model, int x, int y, int width, int height, QObject* object);

    Q_PROPERTY(QString ip_addr READ ip_addr WRITE set_ip_addr NOTIFY ip_addr_changed)

    void set_ip_addr(QString ip_addr_n);
    string replaceAll(string str, const string &remove, const string &insert);
    string trimString(string str);
    void getCameraInfo(map<string, map<string,string>> &cameraInfo);

signals:
    void ip_addr_changed();
};

#endif /* _BACKEND_H_ */
