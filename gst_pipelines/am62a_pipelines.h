#ifndef _AM62A_PIPELINES_H_
#define _AM62A_PIPELINES_H_

#include <string.h>

using namespace std;

// Classification Pipeline
static string am62a_cl_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video1.h264 loop=true caps=\"video/x-h264, width=1280, height=720\" ! h264parse ! v4l2h264dec ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler name=split_01 \
                            split_01. ! queue ! video/x-raw, width=454, height=256 ! tiovxdlcolorconvert out-pool-size=4 ! video/x-raw, format=RGB ! videobox left=115 right=115 top=16 bottom=16 ! tiovxdlpreproc data-type=3 channel-order=1 tensor-format=rgb out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer model=/opt/model_zoo/TFL-CL-0000-mobileNetV1-mlperf ! post_0.tensor \
                            split_01. ! queue ! video/x-raw, width=1280, height=720 ! post_0.sink \
                            tidlpostproc name=post_0 model=/opt/model_zoo/TFL-CL-0000-mobileNetV1-mlperf alpha=0.400000 viz-threshold=0.500000 top-N=5 ! queue ! mosaic_0. \
                            tiovxmosaic target=1 name=mosaic_0 \
                            sink_0::startx=\"<320>\"  sink_0::starty=\"<180>\"  sink_0::widths=\"<1280>\"   sink_0::heights=\"<720>\"  \
                            ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Image Classification\" ! ";

// Object Detection Pipeline
static string am62a_od_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video2.h264 loop=true caps=\"video/x-h264, width=1280, height=720\" ! h264parse ! v4l2h264dec ! video/x-raw,format=NV12 ! \
                            tiovxmultiscaler name=split_01 \
                            split_01. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_0.tensor \
                            split_01. ! queue ! video/x-raw, width=1280, height=720 ! post_0.sink \
                            tidlpostproc name=post_0 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 ! queue ! mosaic_0. \
                            tiovxmosaic target=1 name=mosaic_0 \
                            sink_0::startx=\"<320>\"  sink_0::starty=\"<180>\"  sink_0::widths=\"<1280>\"   sink_0::heights=\"<720>\"  \
                            ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Object Detection\" ! ";

// Semantic Segmentation Pipeline
static string am62a_ss_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video3.h264 loop=true caps=\"video/x-h264, width=1280, height=720\" ! h264parse ! v4l2h264dec ! video/x-raw,format=NV12 ! \
                            tiovxmultiscaler name=split_01 \
                            split_01. ! queue ! video/x-raw, width=512, height=512 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=rgb out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer model=/opt/model_zoo/ONR-SS-8610-deeplabv3lite-mobv2-ade20k32-512x512 ! post_0.tensor \
                            split_01. ! queue ! video/x-raw, width=1280, height=720 ! post_0.sink \
                            tidlpostproc name=post_0 model=/opt/model_zoo/ONR-SS-8610-deeplabv3lite-mobv2-ade20k32-512x512 alpha=0.400000 viz-threshold=0.500000 top-N=5 ! queue ! mosaic_0. \
                            tiovxmosaic target=1 name=mosaic_0 \
                            sink_0::startx=\"<320>\"  sink_0::starty=\"<180>\"  sink_0::widths=\"<1280>\"   sink_0::heights=\"<720>\"  \
                            ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Semantic Segmentation \" ! ";

#endif /* _AM62A_PIPELINES_H_ */