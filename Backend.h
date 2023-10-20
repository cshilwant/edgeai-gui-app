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
#include <misc/content.h>

using namespace std;

static string custom_template =     "title: <title>\n"
                                    "log_level: 2\n"
                                    "inputs:\n"
                                    "   input:\n"
                                    "       source: <source>\n"
                                    "       width: <width>\n"
                                    "       height: <height>\n"
                                    "       framerate: 30\n"
                                    "       format: <format>\n"
                                    "       index: 0\n"
                                    "       subdev-id: <subdev-id>\n"
                                    "       sen-id: <sen-id>\n"
                                    "       ldc: <ldc>\n"
                                    "       loop: True\n"
                                    "models:\n"
                                    "   dl_model:\n"
                                    "       model_path: <model>\n"
                                    "       viz-threshold: 0.6\n"
                                    "outputs:\n"
                                    "   output:\n"
                                    "       sink: fakesink\n"
                                    "       width: 1920\n"
                                    "       height: 1080\n"
                                    "       overlay-perf-type: graph\n"
                                    "flows:\n"
                                    "    flow0: [input,dl_model,output,[320,150,1280,720]]\n";

class Backend : public QObject {
    Q_OBJECT

private:
    string pipeline;

    void addSink(string &pipeline, int xPos, int yPos, int width, int height) {
        /* tiovxmultiscaler only supports even resolution.*/
        if (width % 2 != 0)
            width++;
        if (height % 2 != 0)
            height++;

        if (width > 1920)
            width = 1920;
        if (height > 1080)
            height = 1080;

        if (width < 1920/4 || height < 1080/4)
        {
            pipeline += "tiovxmultiscaler target=1 ! "
                        "video/x-raw, "
                        "width=480"
                        ",height=270"
                        " ! ";
        }

        if (width < 1920 || height < 1080 ) {
            pipeline += "tiovxmultiscaler ! "
                        "video/x-raw, "
                        "width=" +
                        std::to_string(width) +
                        ",height=" +
                        std::to_string(height) +
                        " ! ";
        }

        pipeline += "queue max-size-buffers=1 ! ";
        pipeline += "kmssink driver-name=tidss name=\"qtvideosink\" "
                    "render-rectangle=\""
                    "<" +
                    std::to_string(xPos) +
                    "," +
                    std::to_string(yPos) +
                    "," +
                    std::to_string(width) +
                    "," +
                    std::to_string(height) +
                    ">\"";
    }

    void generateYaml(QString userInputType, QString userInputFile, QString userModel) {
        string config;
        string title = "Custom";
        string width = "1280";
        string height = "720";
        string format = "jpeg";
        string subdev_id = "0";
        string sen_id = "null";
        string ldc = "False";
        string input = userInputFile.toStdString();
        string model = userModel.toStdString();
        string modelName = model.substr(model.find_last_of("/\\") + 1);
        if (userInputType.toStdString() == "Camera") {

            map<string, map<string,string>> cameraInfo;
            getCameraInfo(cameraInfo);

            title = input + "->" + modelName;

            string deviceKey = "device";

            if (input.find("RGB") != string::npos) {
                input = replaceAll(input,"RGB","");
                deviceKey += " RGB";
            }
            else if (input.find("IR") != string::npos) {
                input = replaceAll(input,"IR","");
                deviceKey += " IR";
            }

            input = trimString(input);
            map<string,string> cameraData = cameraInfo[input];

            if (cameraData.find("subdev_id") != cameraData.end()) {
                subdev_id = replaceAll(cameraData["subdev_id"],"/dev/v4l-subdev","");
                subdev_id = trimString(subdev_id);
            }
            if (cameraData.find("name") != cameraData.end())
                sen_id = cameraData["name"];
            if (cameraData.find("ldc_required") != cameraData.end() &&
                cameraData["ldc_required"] == "yes")
                ldc = "True";

            if (input.find("USB") != string::npos)
                format = cameraData["format"];
            else if (sen_id == "ov2312") {
                width = "1600";
                height = "1300";
                format = "bggi10";
            }
            else if (sen_id == "imx390") {
                width = "1936";
                height = "1100";
                format = "rggb12";
            }
            else if (sen_id == "imx219") {
                width = "1920";
                height = "1080";
                format = "rggb";
            }
            else
                format = "auto";

            input = cameraData[deviceKey];


        } else {
            string fileName = input.substr(input.find_last_of("/\\") + 1);
            title = fileName + "->" + modelName;

            if (userInputType.toStdString() == "Video") {
                if (input.find("h265") != string::npos)
                    format = "h265";
                else
                    format = "h264";

                //Get width and height of input file
                string command = "ffprobe -v error -select_streams v:0 -show_entries stream=width,height -of csv=s=x:p=0 " + input;

                // ffprobe is not present in am62a
                if (soc == "am62a")
                {
                    command = "w=`gst-discoverer-1.0 "+input+" -v | grep Width` && "
                              "h=`gst-discoverer-1.0 "+input+" -v | grep Height` && "
                              "echo ${w#*:} x ${h#*:}";
                }
                array<char, 128> buffer;
                string result;
                unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
                if (!pipe) {
                    throw std::runtime_error("popen() failed!");
                }
                while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
                    result += buffer.data();
                }
                char *token;
                token = strtok(&result[0],"x");
                width = trimString(token);
                token =  strtok(NULL,"x");
                height = trimString(token);
            }
        }

        config = replaceAll(custom_template,"<title>",title);
        config = replaceAll(config,"<source>",input);
        config = replaceAll(config,"<width>",width);
        config = replaceAll(config,"<height>",height);
        config = replaceAll(config,"<format>",format);
        config = replaceAll(config,"<subdev-id>",subdev_id);
        config = replaceAll(config,"<sen-id>",sen_id);
        config = replaceAll(config,"<ldc>",ldc);
        config = replaceAll(config,"<model>",model);

        ofstream custom_yaml("/tmp/custom_config.yaml");
        custom_yaml << config;
        custom_yaml.close();
    }

    string getPipelineString() {
        string command = "python3 /opt/edgeai-gst-apps/optiflow/optiflow.py /tmp/custom_config.yaml -t";
        array<char, 128> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        result = replaceAll(result,"gst-launch-1.0","gst-pipeline:");
        result = replaceAll(result,"tiperfoverlay","tiperfoverlay main-title=null");
        result = replaceAll(result,"\n","");
        return result;
    }

    QString ip_addr_p;

public:
    string  soc;
    QString sdk_ver;
    quint32 easter_egg_click_cnt = 0;

    Q_INVOKABLE void increase_easter_egg_click_cnt() {
        easter_egg_click_cnt++;
        if (easter_egg_click_cnt >= 3) {
            easter_egg_click_cnt = 0;
        }
    }

    Q_INVOKABLE quint32 get_easter_egg_click_cnt() {
        return easter_egg_click_cnt;
    }

    Q_INVOKABLE QString get_random_content() {
        int rand_idx = std::rand() % (sizeof(CONTENT)/sizeof(CONTENT[0]));
        return QString::fromStdString(CONTENT[rand_idx]);
    }

    Q_PROPERTY(QString ip_addr READ ip_addr WRITE set_ip_addr NOTIFY ip_addr_changed)

    Q_INVOKABLE QString ip_addr() {
        return ip_addr_p;
    }

    void set_ip_addr(QString ip_addr_n) {
        ip_addr_p = sdk_ver;
        if (ip_addr_n != "")
            ip_addr_p += " | " + ip_addr_n;
        emit ip_addr_changed();
    }

    explicit Backend (QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE QString leftMenuButtonPressed(int button, int x, int y, int width, int height) {
        string cl_pipeline;
        string od_pipeline;
        string ss_pipeline;
        string multi_channel_pipeline;
        if (soc == "am62a")
        {
            cl_pipeline = am62a_cl_pipeline;
            od_pipeline = am62a_od_pipeline;
            ss_pipeline = am62a_ss_pipeline;
            multi_channel_pipeline = am62a_multi_channel_pipeline;
        }
        else if (soc == "j721s2")
        {
            cl_pipeline = j721s2_cl_pipeline;
            od_pipeline = j721s2_od_pipeline;
            ss_pipeline = j721s2_ss_pipeline;
            multi_channel_pipeline = j721s2_multi_channel_pipeline;
        }
        else if (soc == "j721e")
        {
            cl_pipeline = j721e_cl_pipeline;
            od_pipeline = j721e_od_pipeline;
            ss_pipeline = j721e_ss_pipeline;
            multi_channel_pipeline = j721e_multi_channel_pipeline;
        }
        else if (soc == "j784s4")
        {
            cl_pipeline = j784s4_cl_pipeline;
            od_pipeline = j784s4_od_pipeline;
            ss_pipeline = j784s4_ss_pipeline;
            multi_channel_pipeline = j784s4_multi_channel_pipeline;
        }

        if (button == 1) {
            pipeline = "gst-pipeline: " + cl_pipeline;
            addSink(pipeline, x, y, width, height);
        } else if (button == 2) {
            pipeline = "gst-pipeline: " + od_pipeline;
            addSink(pipeline, x, y, width, height);
            pipeline += " sync=false";
        } else if (button == 3) {
            pipeline = "gst-pipeline: " + ss_pipeline;
            addSink(pipeline, x, y, width, height);
            pipeline += " sync=false";
        } else if (button == 4) {
            pipeline = "gst-pipeline: " + multi_channel_pipeline;
            addSink(pipeline, x, y, width, height);
            pipeline += " sync=false";
        }
        else {
            printf("WARNING: Invalid Button click from Left Menu!\n");
        }
        return QString().fromStdString(pipeline);
    }

    Q_INVOKABLE QString popupOkPressed(QString InputType, QString Input, QString Model, int x, int y, int width, int height) {
        cout << "Input Type = " << InputType.toStdString() << ";\nInput File = " << Input.toStdString() << ";\nModel = " << Model.toStdString() << endl;

        generateYaml(InputType, Input, Model);
        pipeline = getPipelineString();
        auto pos = pipeline.find_last_of("!");
        if ( pos != std::string::npos) {
            pipeline = pipeline.substr(0, pos);
            pipeline += " ! ";
        }

        addSink(pipeline, x, y, width, height);

        if (InputType.toStdString() != "Image")
        {
            pipeline += " sync=false";
        }

        cout << "Custom Pipeline: \n" << pipeline << endl;
        return QString().fromStdString(pipeline);
    }

    string replaceAll(string str, const string &remove, const string &insert) {
        string::size_type pos = 0;
        while ((pos = str.find(remove, pos)) != string::npos) {
            str.replace(pos, remove.size(), insert);
            pos++;
        }

        return str;
    }

    string trimString(string str)
    {
        string stripString = str;
        while(!stripString.empty() && isspace(*stripString.begin()))
            stripString.erase(stripString.begin());

        while(!stripString.empty() && isspace(*stripString.rbegin()))
            stripString.erase(stripString.length()-1);

        return stripString;
    }

    void getCameraInfo(map<string, map<string,string>> &cameraInfo)
    {
        // Get camera info from setup_camera script
        string command = "bash /opt/edgeai-gst-apps/scripts/setup_cameras.sh";
        array<char, 128> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }

        vector<string> split_string{};
        auto ss = stringstream{result};
        unsigned int i,j;

        for (string line; getline(ss, line, '\n');)
            split_string.push_back(line);

        for(i = 0; i < split_string.size(); i++) {
            if (split_string[i].find("detected") != string::npos) {
                string cameraName = replaceAll(split_string[i],"detected","");
                cameraName = replaceAll(cameraName,"\033[0;32m","");
                cameraName = replaceAll(cameraName,"\033[0m","");
                cameraName = trimString(cameraName);
                map<string, string> info{};
                for (j = i+1; j < split_string.size(); j++) {
                    if (split_string[j].find("detected") != string::npos)
                        break;

                    char *token;
                    token = strtok(&split_string[j][0], "=");
                    string key = trimString(token);
                    token =  strtok(NULL, "=");
                    string value = trimString(token);
                    info[key] = value;
                }
                if (info.size() > 0)
                    cameraInfo[cameraName] = info;
            }
        }
    }

signals:
    void ip_addr_changed();
};

#endif /* _BACKEND_H_ */