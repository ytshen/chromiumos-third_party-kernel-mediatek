/*
 * mtk drm gem buffer structure.
 *
 * @kvaddr: kernel virtual address to allocated memory region.
 * @dma_addr: bus address(accessed by dma) to allocated memory region.
 *	- this address could be physical address without IOMMU and
 *	device address with IOMMU.
 * @sgt: sg table to transfer page data.
 * @pages: contain all pages to allocated memory region.
 * @size: size of allocated memory region.
 */
struct mtk_drm_gem_buf {
	void __iomem	*kvaddr;
	dma_addr_t		dma_addr;
	struct dma_attrs	dma_attrs;
	struct sg_table	*sgt;
	struct page		**pages;
	unsigned long	size;
	unsigned int	mva_addr;
	unsigned int	paddr;
};

/*
 * mtk drm buffer structure.
 *
 * @base: a gem object.
 *	- a new handle to this gem object would be created
 *	by drm_gem_handle_create().
 * @buffer: a pointer to mtk_drm_gem_buffer object.
 *	- contain the information to memory region allocated
 *	by user request or at framebuffer creation.
 *	continuous memory region allocated by user request
 *	or at framebuffer creation.
 * @size: total memory size to physically non-continuous memory region.
 * @flags: indicate memory type to allocated buffer and cache attruibute.
 *
 * P.S. this object would be transfered to user as kms_bo.handle so
 *	user can access the buffer through kms_bo.handle.
 */
struct mtk_drm_gem_obj {
	struct drm_gem_object	base;
	struct mtk_drm_gem_buf	*buffer;
	unsigned long			size;
	unsigned int			flags;
};

#define to_mtk_gem_obj(x)	container_of(x, struct mtk_drm_gem_obj, base)

void mtk_drm_gem_free_object(struct drm_gem_object *gem);
struct mtk_drm_gem_obj *mtk_drm_gem_create(struct drm_device *dev,
				unsigned int flags,	unsigned long size);
int mtk_drm_gem_dumb_create(struct drm_file *file_priv,
		struct drm_device *dev,	struct drm_mode_create_dumb *args);
int mtk_drm_gem_dumb_map_offset(struct drm_file *file_priv,
		struct drm_device *dev, uint32_t handle, uint64_t *offset);
int mtk_drm_gem_mmap(struct file *filp, struct vm_area_struct *vma);

