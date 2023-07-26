#ifndef _J784S4_PIPELINES_H_
#define _J784S4_PIPELINES_H_

#include <string.h>

using namespace std;

// Classification Pipeline
static string j784s4_cl_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video0.h264 loop=true caps=\"video/x-h264,width=1280,height=720,framerate=1/1\" ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                    tiovxmultiscaler name=split_01 src_0::roi-startx=80 src_0::roi-starty=45 src_0::roi-width=1120 src_0::roi-height=630 target=0 \
                                    \
                                    split_01. ! queue ! video/x-raw, width=672, height=428 ! tiovxmultiscaler target=1 ! video/x-raw, width=224, height=224 ! tiovxdlpreproc model=/opt/model_zoo/TFL-CL-0000-mobileNetV1-mlperf  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/TFL-CL-0000-mobileNetV1-mlperf ! post_0.tensor \
                                    split_01. ! queue ! video/x-raw, width=1280, height=720 ! post_0.sink \
                                    tidlpostproc name=post_0 model=/opt/model_zoo/TFL-CL-0000-mobileNetV1-mlperf alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                    \
                                    \
                                    tiovxmosaic name=mosaic_0 target=1 src::pool-size=4 \
                                    sink_0::startx=\"<320>\" sink_0::starty=\"<150>\" sink_0::widths=\"<1280>\" sink_0::heights=\"<720>\" \
                                    ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Image Classification\" ! ";

// Object Detection Pipeline
static string j784s4_od_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video1.h264 loop=true caps=\"video/x-h264,width=1280,height=720,framerate=30/1\" ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw,format=NV12 ! \
                                    tiovxmultiscaler name=split_01 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=0 \
                                    \
                                    split_01. ! queue ! video/x-raw, width=320, height=320 ! tiovxdlpreproc model=/opt/model_zoo/TFL-OD-2020-ssdLite-mobDet-DSP-coco-320x320  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/TFL-OD-2020-ssdLite-mobDet-DSP-coco-320x320 ! post_0.tensor \
                                    split_01. ! queue ! video/x-raw, width=1280, height=720 ! post_0.sink \
                                    tidlpostproc name=post_0 model=/opt/model_zoo/TFL-OD-2020-ssdLite-mobDet-DSP-coco-320x320 alpha=0.400000 viz-threshold=0.600000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                    \
                                    \
                                    tiovxmosaic name=mosaic_0 target=1 src::pool-size=4 \
                                    sink_0::startx=\"<320>\" sink_0::starty=\"<150>\" sink_0::widths=\"<1280>\" sink_0::heights=\"<720>\" \
                                    ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Object Detection\" ! ";

//Semantic Segmentation Pipeline
static string j784s4_ss_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video2.h264 loop=true caps=\"video/x-h264,width=1280,height=720,framerate=30/1\" ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw,format=NV12 ! \
                                    tiovxmultiscaler name=split_01 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=0 \
                                    \
                                    split_01. ! queue ! video/x-raw, width=512, height=512 ! tiovxdlpreproc model=/opt/model_zoo/ONR-SS-8610-deeplabv3lite-mobv2-ade20k32-512x512  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-SS-8610-deeplabv3lite-mobv2-ade20k32-512x512 ! post_0.tensor \
                                    split_01. ! queue ! video/x-raw, width=1280, height=720 ! post_0.sink \
                                    tidlpostproc name=post_0 model=/opt/model_zoo/ONR-SS-8610-deeplabv3lite-mobv2-ade20k32-512x512 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                    \
                                    \
                                    tiovxmosaic name=mosaic_0 target=1 src::pool-size=4 \
                                    sink_0::startx=\"<320>\" sink_0::starty=\"<150>\" sink_0::widths=\"<1280>\" sink_0::heights=\"<720>\" \
                                    ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Semantic Segmentation\" ! ";

// Object Detection Pipeline
static string j784s4_multi_channel_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video3.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_01 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=0 \
                                            \
                                            split_01. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_0.tensor \
                                            split_01. ! queue ! video/x-raw, width=480, height=270 ! post_0.sink \
                                            tidlpostproc name=post_0 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video4.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_11 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=1 \
                                            \
                                            split_11. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=2 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_1.tensor \
                                            split_11. ! queue ! video/x-raw, width=480, height=270 ! post_1.sink \
                                            tidlpostproc name=post_1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video5.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_21 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=2 \
                                            \
                                            split_21. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=3 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_2.tensor \
                                            split_21. ! queue ! video/x-raw, width=480, height=270 ! post_2.sink \
                                            tidlpostproc name=post_2 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video6.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_31 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=3 \
                                            \
                                            split_31. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=4 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_3.tensor \
                                            split_31. ! queue ! video/x-raw, width=480, height=270 ! post_3.sink \
                                            tidlpostproc name=post_3 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video7.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_41 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=0 \
                                            \
                                            split_41. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_4.tensor \
                                            split_41. ! queue ! video/x-raw, width=480, height=270 ! post_4.sink \
                                            tidlpostproc name=post_4 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video8.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_51 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=1 \
                                            \
                                            split_51. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=2 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_5.tensor \
                                            split_51. ! queue ! video/x-raw, width=480, height=270 ! post_5.sink \
                                            tidlpostproc name=post_5 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video9.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_61 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=2 \
                                            \
                                            split_61. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=3 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_6.tensor \
                                            split_61. ! queue ! video/x-raw, width=480, height=270 ! post_6.sink \
                                            tidlpostproc name=post_6 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video10.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_71 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=3 \
                                            \
                                            split_71. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=4 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_7.tensor \
                                            split_71. ! queue ! video/x-raw, width=480, height=270 ! post_7.sink \
                                            tidlpostproc name=post_7 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video11.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2video2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_81 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=0 \
                                            \
                                            split_81. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_8.tensor \
                                            split_81. ! queue ! video/x-raw, width=480, height=270 ! post_8.sink \
                                            tidlpostproc name=post_8 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video12.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2video2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_91 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=1 \
                                            \
                                            split_91. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=2 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_9.tensor \
                                            split_91. ! queue ! video/x-raw, width=480, height=270 ! post_9.sink \
                                            tidlpostproc name=post_9 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video13.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2video2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_101 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=2 \
                                            \
                                            split_101. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=3 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_10.tensor \
                                            split_101. ! queue ! video/x-raw, width=480, height=270 ! post_10.sink \
                                            tidlpostproc name=post_10 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video14.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2video2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_111 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=3 \
                                            \
                                            split_111. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=4 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_11.tensor \
                                            split_111. ! queue ! video/x-raw, width=480, height=270 ! post_11.sink \
                                            tidlpostproc name=post_11 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video15.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2video2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_112 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=0 \
                                            \
                                            split_112. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_12.tensor \
                                            split_112. ! queue ! video/x-raw, width=480, height=270 ! post_12.sink \
                                            tidlpostproc name=post_12 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video16.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2video2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_113 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=1 \
                                            \
                                            split_113. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=2 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_13.tensor \
                                            split_113. ! queue ! video/x-raw, width=480, height=270 ! post_13.sink \
                                            tidlpostproc name=post_13 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video17.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2video2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_114 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=2 \
                                            \
                                            split_114. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=3 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_14.tensor \
                                            split_114. ! queue ! video/x-raw, width=480, height=270 ! post_14.sink \
                                            tidlpostproc name=post_14 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video18.h264 loop=true stop-index=-1 caps=video/x-h264,width=1280,height=768,framerate=30/1 ! h264parse ! v4l2video2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_115 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=3 \
                                            \
                                            split_115. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=2 ! application/x-tensor-tiovx ! tidlinferer target=4 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_15.tensor \
                                            split_115. ! queue ! video/x-raw, width=480, height=270 ! post_15.sink \
                                            tidlpostproc name=post_15 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            \
                                            tiovxmosaic name=mosaic_0 target=1 src::pool-size=4 \
                                            sink_0::startx=\"<0>\" sink_0::starty=\"<0>\" sink_0::widths=\"<480>\" sink_0::heights=\"<270>\" \
                                            sink_1::startx=\"<480>\" sink_1::starty=\"<0>\" sink_1::widths=\"<480>\" sink_1::heights=\"<270>\" \
                                            sink_2::startx=\"<960>\" sink_2::starty=\"<0>\" sink_2::widths=\"<480>\" sink_2::heights=\"<270>\" \
                                            sink_3::startx=\"<1440>\" sink_3::starty=\"<0>\" sink_3::widths=\"<480>\" sink_3::heights=\"<270>\" \
                                            sink_4::startx=\"<0>\" sink_4::starty=\"<270>\" sink_4::widths=\"<480>\" sink_4::heights=\"<270>\" \
                                            sink_5::startx=\"<480>\" sink_5::starty=\"<270>\" sink_5::widths=\"<480>\" sink_5::heights=\"<270>\" \
                                            sink_6::startx=\"<960>\" sink_6::starty=\"<270>\" sink_6::widths=\"<480>\" sink_6::heights=\"<270>\" \
                                            sink_7::startx=\"<1440>\" sink_7::starty=\"<270>\" sink_7::widths=\"<480>\" sink_7::heights=\"<270>\" \
                                            sink_8::startx=\"<0>\" sink_8::starty=\"<540>\" sink_8::widths=\"<480>\" sink_8::heights=\"<270>\" \
                                            sink_9::startx=\"<480>\" sink_9::starty=\"<540>\" sink_9::widths=\"<480>\" sink_9::heights=\"<270>\" \
                                            sink_10::startx=\"<960>\" sink_10::starty=\"<540>\" sink_10::widths=\"<480>\" sink_10::heights=\"<270>\" \
                                            sink_11::startx=\"<1440>\" sink_11::starty=\"<540>\" sink_11::widths=\"<480>\" sink_11::heights=\"<270>\" \
                                            sink_12::startx=\"<0>\" sink_12::starty=\"<810>\" sink_12::widths=\"<480>\" sink_12::heights=\"<270>\" \
                                            sink_13::startx=\"<480>\" sink_13::starty=\"<810>\" sink_13::widths=\"<480>\" sink_13::heights=\"<270>\" \
                                            sink_14::startx=\"<960>\" sink_14::starty=\"<810>\" sink_14::widths=\"<480>\" sink_14::heights=\"<270>\" \
                                            sink_15::startx=\"<1440>\" sink_15::starty=\"<810>\" sink_15::widths=\"<480>\" sink_15::heights=\"<270>\" \
                                            ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"\" overlay-type=text ! ";

#endif /* _J784S4_PIPELINES_H_ */