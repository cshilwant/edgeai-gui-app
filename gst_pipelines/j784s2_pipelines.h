#ifndef _J784S4_PIPELINES_H_
#define _J784S4_PIPELINES_H_

#include <string.h>

using namespace std;

// Classification Pipeline
static string j784s4_cl_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video1.h264 loop=true caps=\"video/x-h264, width=1280, height=720\" ! h264parse ! v4l2h264dec ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler name=split_01 \
                            split_01. ! queue ! video/x-raw, width=454, height=256 ! tiovxdlcolorconvert out-pool-size=4 ! video/x-raw, format=RGB ! videobox left=115 right=115 top=16 bottom=16 ! tiovxdlpreproc data-type=3 channel-order=1 tensor-format=rgb out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer model=/opt/model_zoo/TFL-CL-0000-mobileNetV1-mlperf ! post_0.tensor \
                            split_01. ! queue ! video/x-raw, width=1280, height=720 ! post_0.sink \
                            tidlpostproc name=post_0 model=/opt/model_zoo/TFL-CL-0000-mobileNetV1-mlperf alpha=0.400000 viz-threshold=0.500000 top-N=5 ! queue ! mosaic_0. \
                            tiovxmosaic target=1 name=mosaic_0 \
                            sink_0::startx=\"<320>\"  sink_0::starty=\"<180>\"  sink_0::widths=\"<1280>\"   sink_0::heights=\"<720>\"  \
                            ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Image Classification\" ! ";

// Object Detection Pipeline
static string j784s4_od_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video2.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=0 name=split_01 \
                            split_01. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_0.tensor \
                            split_01. ! queue ! video/x-raw, width=640, height=360 ! post_0.sink \
                            tidlpostproc name=post_0 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video3.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=1 name=split_11 \
                            split_11. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=2 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_1.tensor \
                            split_11. ! queue ! video/x-raw, width=640, height=360 ! post_1.sink \
                            tidlpostproc name=post_1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video4.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=2 name=split_21 \
                            split_21. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=3 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_2.tensor \
                            split_21. ! queue ! video/x-raw, width=640, height=360 ! post_2.sink \
                            tidlpostproc name=post_2 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video5.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=3 name=split_31 \
                            split_31. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=4 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_3.tensor \
                            split_31. ! queue ! video/x-raw, width=640, height=360 ! post_3.sink \
                            tidlpostproc name=post_3 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video6.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2video2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=0 name=split_41 \
                            split_41. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_4.tensor \
                            split_41. ! queue ! video/x-raw, width=640, height=360 ! post_4.sink \
                            tidlpostproc name=post_4 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video7.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2video2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=1 name=split_51 \
                            split_51. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=2 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_5.tensor \
                            split_51. ! queue ! video/x-raw, width=640, height=360 ! post_5.sink \
                            tidlpostproc name=post_5 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video8.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2video2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=2 name=split_61 \
                            split_61. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=3 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_6.tensor \
                            split_61. ! queue ! video/x-raw, width=640, height=360 ! post_6.sink \
                            tidlpostproc name=post_6 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video9.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2video2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=3 name=split_71 \
                            split_71. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=4 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_7.tensor \
                            split_71. ! queue ! video/x-raw, width=640, height=360 ! post_7.sink \
                            tidlpostproc name=post_7 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            \
                            tiovxmosaic target=1 src::pool-size=3 name=mosaic_0 \
                            sink_0::startx=\"<213>\"  sink_0::starty=\"<50>\"  sink_0::widths=\"<498>\"   sink_0::heights=\"<280>\"  \
                            sink_1::startx=\"<711>\"  sink_1::starty=\"<50>\"  sink_1::widths=\"<498>\"   sink_1::heights=\"<280>\"  \
                            sink_2::startx=\"<1209>\"  sink_2::starty=\"<50>\"  sink_2::widths=\"<498>\"   sink_2::heights=\"<280>\"  \
                            sink_3::startx=\"<213>\"  sink_3::starty=\"<330>\"  sink_3::widths=\"<498>\"   sink_3::heights=\"<280>\"  \
                            sink_4::startx=\"<711>\"  sink_4::starty=\"<330>\"  sink_4::widths=\"<498>\"   sink_4::heights=\"<280>\"  \
                            sink_5::startx=\"<1209>\"  sink_5::starty=\"<330>\"  sink_5::widths=\"<498>\"   sink_5::heights=\"<280>\"  \
                            sink_6::startx=\"<462>\"  sink_6::starty=\"<610>\"  sink_6::widths=\"<498>\"   sink_6::heights=\"<280>\"  \
                            sink_7::startx=\"<960>\"  sink_7::starty=\"<610>\"  sink_7::widths=\"<498>\"   sink_7::heights=\"<280>\"  \
                            ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Object Detection\" ! ";

//Semantic Segmentation Pipeline
static string j784s4_ss_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video10.h264 loop=true caps=\"video/x-h264, width=1280, height=720\" ! h264parse ! v4l2h264dec ! video/x-raw,format=NV12 ! \
                            tiovxmultiscaler name=split_01 \
                            split_01. ! queue ! video/x-raw, width=512, height=512 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=rgb out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer model=/opt/model_zoo/ONR-SS-8610-deeplabv3lite-mobv2-ade20k32-512x512 ! post_0.tensor \
                            split_01. ! queue ! video/x-raw, width=1280, height=720 ! post_0.sink \
                            tidlpostproc name=post_0 model=/opt/model_zoo/ONR-SS-8610-deeplabv3lite-mobv2-ade20k32-512x512 alpha=0.400000 viz-threshold=0.500000 top-N=5 ! queue ! mosaic_0. \
                            tiovxmosaic target=1 name=mosaic_0 \
                            sink_0::startx=\"<320>\"  sink_0::starty=\"<180>\"  sink_0::widths=\"<1280>\"   sink_0::heights=\"<720>\"  \
                            ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Semantic Segmentation \" ! ";

// Object Detection Pipeline
static string j784s4_multi_channel_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video2.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=0 name=split_01 \
                            split_01. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_0.tensor \
                            split_01. ! queue ! video/x-raw, width=640, height=360 ! post_0.sink \
                            tidlpostproc name=post_0 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video3.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=1 name=split_11 \
                            split_11. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=2 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_1.tensor \
                            split_11. ! queue ! video/x-raw, width=640, height=360 ! post_1.sink \
                            tidlpostproc name=post_1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video4.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=2 name=split_21 \
                            split_21. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=3 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_2.tensor \
                            split_21. ! queue ! video/x-raw, width=640, height=360 ! post_2.sink \
                            tidlpostproc name=post_2 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video5.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=3 name=split_31 \
                            split_31. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=4 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_3.tensor \
                            split_31. ! queue ! video/x-raw, width=640, height=360 ! post_3.sink \
                            tidlpostproc name=post_3 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video6.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2video2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=0 name=split_41 \
                            split_41. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_4.tensor \
                            split_41. ! queue ! video/x-raw, width=640, height=360 ! post_4.sink \
                            tidlpostproc name=post_4 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video7.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2video2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=1 name=split_51 \
                            split_51. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=2 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_5.tensor \
                            split_51. ! queue ! video/x-raw, width=640, height=360 ! post_5.sink \
                            tidlpostproc name=post_5 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video8.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2video2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=2 name=split_61 \
                            split_61. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=3 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_6.tensor \
                            split_61. ! queue ! video/x-raw, width=640, height=360 ! post_6.sink \
                            tidlpostproc name=post_6 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video9.h264 loop=true stop-index=0 caps=video/x-h264,width=1280,height=720,framerate=30/1 ! h264parse ! v4l2video2h264dec ! tiovxmemalloc pool-size=8 ! video/x-raw, format=NV12 ! \
                            tiovxmultiscaler target=3 name=split_71 \
                            split_71. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc data-type=3 channel-order=0 tensor-format=bgr out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=4 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_7.tensor \
                            split_71. ! queue ! video/x-raw, width=640, height=360 ! post_7.sink \
                            tidlpostproc name=post_7 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.450000 viz-threshold=0.450000 top-N=5 ! queue ! mosaic_0. \
                            \
                            \
                            tiovxmosaic target=1 src::pool-size=3 name=mosaic_0 \
                            sink_0::startx=\"<213>\"  sink_0::starty=\"<50>\"  sink_0::widths=\"<498>\"   sink_0::heights=\"<280>\"  \
                            sink_1::startx=\"<711>\"  sink_1::starty=\"<50>\"  sink_1::widths=\"<498>\"   sink_1::heights=\"<280>\"  \
                            sink_2::startx=\"<1209>\"  sink_2::starty=\"<50>\"  sink_2::widths=\"<498>\"   sink_2::heights=\"<280>\"  \
                            sink_3::startx=\"<213>\"  sink_3::starty=\"<330>\"  sink_3::widths=\"<498>\"   sink_3::heights=\"<280>\"  \
                            sink_4::startx=\"<711>\"  sink_4::starty=\"<330>\"  sink_4::widths=\"<498>\"   sink_4::heights=\"<280>\"  \
                            sink_5::startx=\"<1209>\"  sink_5::starty=\"<330>\"  sink_5::widths=\"<498>\"   sink_5::heights=\"<280>\"  \
                            sink_6::startx=\"<462>\"  sink_6::starty=\"<610>\"  sink_6::widths=\"<498>\"   sink_6::heights=\"<280>\"  \
                            sink_7::startx=\"<960>\"  sink_7::starty=\"<610>\"  sink_7::widths=\"<498>\"   sink_7::heights=\"<280>\"  \
                            ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Object Detection\" ! ";

#endif /* _J784S4_PIPELINES_H_ */