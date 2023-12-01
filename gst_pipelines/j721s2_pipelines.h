#ifndef _J721S2_PIPELINES_H_
#define _J721S2_PIPELINES_H_

#include <string.h>

using namespace std;

// Classification Pipeline
static string j721s2_cl_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video0.h264 loop=true caps=video/x-h264,width=1280,height=768,framerate=1/1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
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
static string j721s2_od_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video1.h264 loop=true  ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw,format=NV12 ! \
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

static string j721s2_ss_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video2.h264 loop=true  ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw,format=NV12 ! \
                                    tiovxmultiscaler name=split_01 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=0 \
                                    \
                                    split_01. ! queue ! video/x-raw, width=512, height=512 ! tiovxdlpreproc model=/opt/model_zoo/ONR-SS-8610-deeplabv3lite-mobv2-ade20k32-512x512  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-SS-8610-deeplabv3lite-mobv2-ade20k32-512x512 ! post_0.tensor \
                                    split_01. ! queue ! video/x-raw, width=1280, height=720 ! post_0.sink \
                                    tidlpostproc name=post_0 model=/opt/model_zoo/ONR-SS-8610-deeplabv3lite-mobv2-ade20k32-512x512 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                    \
                                    \
                                    tiovxmosaic name=mosaic_0 target=1 src::pool-size=4 \
                                    sink_0::startx=\"<320>\" sink_0::starty=\"<150>\" sink_0::widths=\"<1280>\" sink_0::heights=\"<720>\" \
                                    ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Semantic Segmentation\" !";

// Multi Channel Pipeline
static string j721s2_multi_channel_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video3.h264 loop=true stop-index=-1  ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_01 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=764 target=0 \
                                            \
                                            split_01. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_0.tensor \
                                            split_01. ! queue ! video/x-raw, width=640, height=360 ! post_0.sink \
                                            tidlpostproc name=post_0 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video4.h264 loop=true stop-index=-1  ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_11 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=1 \
                                            \
                                            split_11. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_1.tensor \
                                            split_11. ! queue ! video/x-raw, width=640, height=360 ! post_1.sink \
                                            tidlpostproc name=post_1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video5.h264 loop=true stop-index=-1  ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_21 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=0 \
                                            \
                                            split_21. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_2.tensor \
                                            split_21. ! queue ! video/x-raw, width=640, height=360 ! post_2.sink \
                                            tidlpostproc name=post_2 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video6.h264 loop=true stop-index=-1  ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_31 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=1 \
                                            \
                                            split_31. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_3.tensor \
                                            split_31. ! queue ! video/x-raw, width=640, height=360 ! post_3.sink \
                                            tidlpostproc name=post_3 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video7.h264 loop=true stop-index=-1  ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_41 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=0 \
                                            \
                                            split_41. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_4.tensor \
                                            split_41. ! queue ! video/x-raw, width=640, height=360 ! post_4.sink \
                                            tidlpostproc name=post_4 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video8.h264 loop=true stop-index=-1  ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_51 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=1 \
                                            \
                                            split_51. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_5.tensor \
                                            split_51. ! queue ! video/x-raw, width=640, height=360 ! post_5.sink \
                                            tidlpostproc name=post_5 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video9.h264 loop=true stop-index=-1  ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_61 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=0 \
                                            \
                                            split_61. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_6.tensor \
                                            split_61. ! queue ! video/x-raw, width=640, height=360 ! post_6.sink \
                                            tidlpostproc name=post_6 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            multifilesrc location=/opt/oob-demo-assets/oob-gui-video10.h264 loop=true stop-index=-1  ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                            tiovxmultiscaler name=split_71 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=1 \
                                            \
                                            split_71. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_7.tensor \
                                            split_71. ! queue ! video/x-raw, width=640, height=360 ! post_7.sink \
                                            tidlpostproc name=post_7 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.400000 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                            \
                                            \
                                            tiovxmosaic name=mosaic_0 target=1 src::pool-size=4 \
                                            sink_0::startx=\"<0>\" sink_0::starty=\"<0>\" sink_0::widths=\"<640>\" sink_0::heights=\"<360>\" \
                                            sink_1::startx=\"<640>\" sink_1::starty=\"<0>\" sink_1::widths=\"<640>\" sink_1::heights=\"<360>\" \
                                            sink_2::startx=\"<1280>\" sink_2::starty=\"<0>\" sink_2::widths=\"<640>\" sink_2::heights=\"<360>\" \
                                            sink_3::startx=\"<0>\" sink_3::starty=\"<360>\" sink_3::widths=\"<640>\" sink_3::heights=\"<360>\" \
                                            sink_4::startx=\"<640>\" sink_4::starty=\"<360>\" sink_4::widths=\"<640>\" sink_4::heights=\"<360>\" \
                                            sink_5::startx=\"<1280>\" sink_5::starty=\"<360>\" sink_5::widths=\"<640>\" sink_5::heights=\"<360>\" \
                                            sink_6::startx=\"<320>\" sink_6::starty=\"<720>\" sink_6::widths=\"<640>\" sink_6::heights=\"<360>\" \
                                            sink_7::startx=\"<960>\" sink_7::starty=\"<720>\" sink_7::widths=\"<640>\" sink_7::heights=\"<360>\" \
                                            ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"\" overlay-type=text ! queue max-size-buffers=1 ! ";

#endif /* _J721S2_PIPELINES_H_ */