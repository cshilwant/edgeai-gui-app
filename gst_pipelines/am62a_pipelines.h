#ifndef _AM62A_PIPELINES_H_
#define _AM62A_PIPELINES_H_

#include <string.h>

using namespace std;

// Classification Pipeline
static string am62a_cl_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video0.h264 loop=true caps=video/x-h264,width=1280,height=768,framerate=1/1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw, format=NV12 ! \
                                   tiovxmultiscaler name=split_01 src_0::roi-startx=80 src_0::roi-starty=45 src_0::roi-width=1120 src_0::roi-height=630 target=0 \
                                   \
                                   split_01. ! queue ! video/x-raw, width=672, height=428 ! tiovxmultiscaler target=1 ! video/x-raw, width=224, height=224 ! tiovxdlpreproc model=/opt/model_zoo/TFL-CL-0000-mobileNetV1-mlperf  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/TFL-CL-0000-mobileNetV1-mlperf ! post_0.tensor \
                                   split_01. ! queue ! video/x-raw, width=1280, height=720 ! post_0.sink \
                                   tidlpostproc name=post_0 model=/opt/model_zoo/TFL-CL-0000-mobileNetV1-mlperf alpha=0.2 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                   \
                                   \
                                   tiovxmosaic name=mosaic_0 target=1 src::pool-size=4 \
                                   sink_0::startx=\"<320>\" sink_0::starty=\"<150>\" sink_0::widths=\"<1280>\" sink_0::heights=\"<720>\" \
                                   ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Image Classification\" ! queue max-size-buffers=1 ! ";

// Object Detection Pipeline
static string am62a_od_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video1.h264 loop=true ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw,format=NV12 ! \
                                  tiovxmultiscaler name=split_01 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=0 \
                                  \
                                  split_01. ! queue ! video/x-raw, width=320, height=320 ! tiovxdlpreproc model=/opt/model_zoo/TFL-OD-2020-ssdLite-mobDet-DSP-coco-320x320  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/TFL-OD-2020-ssdLite-mobDet-DSP-coco-320x320 ! post_0.tensor \
                                  split_01. ! queue ! video/x-raw, width=1280, height=720 ! post_0.sink \
                                  tidlpostproc name=post_0 model=/opt/model_zoo/TFL-OD-2020-ssdLite-mobDet-DSP-coco-320x320 alpha=0.2 viz-threshold=0.600000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                  \
                                  \
                                  tiovxmosaic name=mosaic_0 target=1 src::pool-size=4 \
                                  sink_0::startx=\"<320>\" sink_0::starty=\"<150>\" sink_0::widths=\"<1280>\" sink_0::heights=\"<720>\" \
                                  ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Object Detection\" !  queue max-size-buffers=1 ! ";

// Semantic Segmentation Pipeline
static string am62a_ss_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video2.h264 loop=true ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc ! video/x-raw,format=NV12 ! \
                                   tiovxmultiscaler name=split_01 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=0 \
                                   \
                                   split_01. ! queue ! video/x-raw, width=512, height=512 ! tiovxdlpreproc model=/opt/model_zoo/ONR-SS-8610-deeplabv3lite-mobv2-ade20k32-512x512  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-SS-8610-deeplabv3lite-mobv2-ade20k32-512x512 ! post_0.tensor \
                                   split_01. ! queue ! video/x-raw, width=1280, height=720 ! post_0.sink \
                                   tidlpostproc name=post_0 model=/opt/model_zoo/ONR-SS-8610-deeplabv3lite-mobv2-ade20k32-512x512 alpha=0.2 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                   \
                                   \
                                   tiovxmosaic name=mosaic_0 target=1 src::pool-size=4 \
                                   sink_0::startx=\"<320>\" sink_0::starty=\"<150>\" sink_0::widths=\"<1280>\" sink_0::heights=\"<720>\" \
                                   ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"Semantic Segmentation\" ! queue max-size-buffers=1 ! ";
// Multi Channel Pipeline
static string am62a_multi_channel_pipeline = "multifilesrc location=/opt/oob-demo-assets/oob-gui-video3.h264 loop=true stop-index=-1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc  ! video/x-raw, format=NV12 ! \
                                              tiovxmultiscaler name=split_01 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=764 target=0 \
                                              \
                                              split_01. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_0.tensor \
                                              split_01. ! queue ! video/x-raw, width=880, height=496 ! post_0.sink \
                                              tidlpostproc name=post_0 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.2 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                              \
                                              multifilesrc location=/opt/oob-demo-assets/oob-gui-video4.h264 loop=true stop-index=-1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc  ! video/x-raw, format=NV12 ! \
                                              tiovxmultiscaler name=split_11 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=1 \
                                              \
                                              split_11. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_1.tensor \
                                              split_11. ! queue ! video/x-raw, width=880, height=496 ! post_1.sink \
                                              tidlpostproc name=post_1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.2 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                              \
                                              multifilesrc location=/opt/oob-demo-assets/oob-gui-video5.h264 loop=true stop-index=-1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc  ! video/x-raw, format=NV12 ! \
                                              tiovxmultiscaler name=split_21 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=0 \
                                              \
                                              split_21. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_2.tensor \
                                              split_21. ! queue ! video/x-raw, width=880, height=496 ! post_2.sink \
                                              tidlpostproc name=post_2 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.2 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                              \
                                              multifilesrc location=/opt/oob-demo-assets/oob-gui-video6.h264 loop=true stop-index=-1 ! h264parse ! v4l2h264dec capture-io-mode=5 ! tiovxmemalloc  ! video/x-raw, format=NV12 ! \
                                              tiovxmultiscaler name=split_31 src_0::roi-startx=0 src_0::roi-starty=0 src_0::roi-width=1280 src_0::roi-height=768 target=1 \
                                              \
                                              split_31. ! queue ! video/x-raw, width=416, height=416 ! tiovxdlpreproc model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416  out-pool-size=4 ! application/x-tensor-tiovx ! tidlinferer target=1 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 ! post_3.tensor \
                                              split_31. ! queue ! video/x-raw, width=880, height=496 ! post_3.sink \
                                              tidlpostproc name=post_3 model=/opt/model_zoo/ONR-OD-8200-yolox-nano-lite-mmdet-coco-416x416 alpha=0.2 viz-threshold=0.500000 top-N=5 display-model=true ! queue ! mosaic_0. \
                                              \
                                              \
                                              tiovxmosaic name=mosaic_0 target=1 src::pool-size=4 \
                                              sink_0::startx=\"<80>\" sink_0::starty=\"<47>\" sink_0::widths=\"<880>\" sink_0::heights=\"<496>\" \
                                              sink_1::startx=\"<960>\" sink_1::starty=\"<47>\" sink_1::widths=\"<880>\" sink_1::heights=\"<496>\" \
                                              sink_2::startx=\"<80>\" sink_2::starty=\"<543>\" sink_2::widths=\"<880>\" sink_2::heights=\"<496>\" \
                                              sink_3::startx=\"<960>\" sink_3::starty=\"<543>\" sink_3::widths=\"<880>\" sink_3::heights=\"<496>\" \
                                              ! video/x-raw,format=NV12, width=1920, height=1080 ! queue ! tiperfoverlay main-title=null title=\"\" overlay-type=text ! queue max-size-buffers=1 ! ";

#endif /* _AM62A_PIPELINES_H_ */