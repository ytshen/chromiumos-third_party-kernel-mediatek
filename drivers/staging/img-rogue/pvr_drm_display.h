/*************************************************************************/ /*!
@File
@Copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved
@License        Strictly Confidential.
*/ /**************************************************************************/

#if !defined(__PVR_DRM_DISPLAY_H__)
#define __PVR_DRM_DISPLAY_H__

#include <drm/drmP.h>

#define	PVR_DRM_MAKENAME_HELPER(x, y)	x ## y
#define	PVR_DRM_MAKENAME(x, y)		PVR_DRM_MAKENAME_HELPER(x, y)

typedef irqreturn_t (*pvr_drm_irq_handler)(void *data);

#if defined(SUPPORT_DRM_DC_MODULE)
struct pvr_drm_display_buffer;
struct pvr_drm_flip_data;

typedef void (*pvr_drm_flip_func)(struct drm_gem_object *bo, void *data, struct pvr_drm_flip_data *flip_data);

struct pvr_drm_device_funcs
{
	void *(*pvr_drm_get_display_device)(struct drm_device *dev);
	int (*pvr_drm_display_irq_install)(struct drm_device *dev, unsigned int irq, pvr_drm_irq_handler handler, void **irq_handle_out);
	int (*pvr_drm_display_irq_uninstall)(void *irq_handle);
	int (*pvr_drm_gem_create)(struct drm_device *dev, size_t size, struct drm_gem_object **bo);
	int (*pvr_drm_gem_map)(struct drm_gem_object *bo);
	int (*pvr_drm_gem_unmap)(struct drm_gem_object *bo);
	int (*pvr_drm_gem_cpu_addr)(struct drm_gem_object *bo, off_t offset, uint64_t *cpu_addr_out);
	int (*pvr_drm_gem_dev_addr)(struct drm_gem_object *bo, off_t offset, uint64_t *dev_addr_out);
	struct pvr_drm_display_buffer *(*pvr_drm_gem_buffer)(struct drm_gem_object *bo);
	int (*pvr_drm_flip_schedule)(struct drm_gem_object *bo, pvr_drm_flip_func flip_cb, void *data);
	int (*pvr_drm_flip_done)(struct pvr_drm_flip_data *flip_data);
	int (*pvr_drm_heap_acquire)(uint32_t heap_id, void **heap_out);
	void (*pvr_drm_heap_release)(void *heap);
	int (*pvr_drm_heap_info)(void *heap, uint64_t *cpu_phys_base, uint64_t *dev_phys_base, size_t *size);
};

static inline void *pvr_drm_get_display_device(struct drm_device *dev)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)dev->dev_private;

	return funcs->pvr_drm_get_display_device(dev);
}

static inline int pvr_drm_irq_install(struct drm_device *dev, unsigned int irq, pvr_drm_irq_handler handler, void **irq_handle_out)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)dev->dev_private;

	return funcs->pvr_drm_display_irq_install(dev, irq, handler, irq_handle_out);
}

static inline int pvr_drm_irq_uninstall(struct drm_device *dev, void *irq_handle)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)dev->dev_private;

	return funcs->pvr_drm_display_irq_uninstall(irq_handle);
}

static inline int pvr_drm_gem_create(struct drm_device *dev, size_t size, struct drm_gem_object **bo)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)dev->dev_private;

	return funcs->pvr_drm_gem_create(dev, size, bo);
}

static inline int pvr_drm_gem_map(struct drm_gem_object *bo)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)bo->dev->dev_private;

	return funcs->pvr_drm_gem_map(bo);
}

static inline int pvr_drm_gem_unmap(struct drm_gem_object *bo)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)bo->dev->dev_private;

	return funcs->pvr_drm_gem_unmap(bo);	
}

static inline int pvr_drm_gem_cpu_addr(struct drm_gem_object *bo, off_t offset, uint64_t *cpu_addr_out)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)bo->dev->dev_private;

	return funcs->pvr_drm_gem_cpu_addr(bo, offset, cpu_addr_out);
}

static inline int pvr_drm_gem_dev_addr(struct drm_gem_object *bo, off_t offset, uint64_t *dev_addr_out)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)bo->dev->dev_private;

	return funcs->pvr_drm_gem_dev_addr(bo, offset, dev_addr_out);
}

static inline struct pvr_drm_display_buffer *pvr_drm_gem_buffer(struct drm_gem_object *bo)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)bo->dev->dev_private;

	return funcs->pvr_drm_gem_buffer(bo);
}

static inline int pvr_drm_flip_schedule(struct drm_gem_object *bo, pvr_drm_flip_func flip_cb, void *data)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)bo->dev->dev_private;

	return funcs->pvr_drm_flip_schedule(bo, flip_cb, data);
}

static inline int pvr_drm_flip_done(struct drm_device *dev, struct pvr_drm_flip_data *flip_data)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)dev->dev_private;

	return funcs->pvr_drm_flip_done(flip_data);
}

static inline int pvr_drm_heap_acquire(struct drm_device *dev, uint32_t heap_id, void **heap_out)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)dev->dev_private;

	return funcs->pvr_drm_heap_acquire(heap_id, heap_out);
}

static inline void pvr_drm_heap_release(struct drm_device *dev, void *heap)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)dev->dev_private;

	funcs->pvr_drm_heap_release(heap);
}

static inline int pvr_drm_heap_info(struct drm_device *dev, void *heap, uint64_t *cpu_phys_base, uint64_t *dev_phys_base, size_t *size)
{
	struct pvr_drm_device_funcs *funcs = (struct pvr_drm_device_funcs *)dev->dev_private;

	return funcs->pvr_drm_heap_info(heap, cpu_phys_base, dev_phys_base, size);
}

int PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _init)(struct drm_device *dev, void **display_priv_out);
int PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _configure)(void *display_priv);
void PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _cleanup)(void *display_priv);

int PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _buffer_alloc)(void *display_priv, size_t size, struct pvr_drm_display_buffer **buffer_out);
int PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _buffer_free)(struct pvr_drm_display_buffer *buffer);
uint64_t *PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _buffer_acquire)(struct pvr_drm_display_buffer *buffer);
int PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _buffer_release)(struct pvr_drm_display_buffer *buffer, uint64_t *dev_paddr_array);
void *PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _buffer_vmap)(struct pvr_drm_display_buffer *buffer);
void PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _buffer_vunmap)(struct pvr_drm_display_buffer *buffer, void *vaddr);

u32 PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _get_vblank_counter)(void *display_priv, int crtc);
int PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _enable_vblank)(void *display_priv, int crtc);
int PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _disable_vblank)(void *display_priv, int crtc);

#elif defined(SUPPORT_DISPLAY_CLASS)

extern int PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _Init)(struct drm_device *dev);
extern void PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _Cleanup)(struct drm_device *dev);

#endif /* defined(SUPPORT_DRM_DC_MODULE) */

#endif /* !defined(__PVR_DRM_DISPLAY_H__) */
