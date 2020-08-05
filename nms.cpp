#include "nms.h"

at::Tensor nms(
    const at::Tensor& dets,
    const at::Tensor& scores,
    const double iou_threshold) {
  if (dets.is_cuda()) {
#if defined(WITH_CUDA)
    if (dets.numel() == 0) {
      at::cuda::CUDAGuard device_guard(dets.device());
      return at::empty({0}, dets.options().dtype(at::kLong));
    }
    return nms_cuda(dets, scores, iou_threshold);
#elif defined(WITH_HIP)
    if (dets.numel() == 0) {
      at::cuda::HIPGuard device_guard(dets.device());
      return at::empty({0}, dets.options().dtype(at::kLong));
    }
    return nms_cuda(dets, scores, iou_threshold);
#else
    AT_ERROR("Not compiled with GPU support");
#endif
  }

  at::Tensor result = nms_cpu(dets, scores, iou_threshold);
  return result;
}
