#define LINUX 
#define PVR_BUILD_DIR "mt8135_linux"
#define PVR_BUILD_TYPE "release"
#define PVRSRV_MODNAME "pvrsrvkm"
#define SUPPORT_RGX 1
#define DISPLAY_CONTROLLER dc_drmmtk
#define RELEASE 
//#define RGX_BVNC_CORE_KM_HEADER "cores/rgxcore_km_1.82.4.5.h" 
//#define RGX_BVNC_CORE_HEADER "cores/rgxcore_1.82.4.5.h"
//#define RGX_BNC_CONFIG_KM_HEADER "configs/rgxconfig_km_1.V.4.5.h" 
//#define RGX_BNC_CONFIG_HEADER "configs/rgxconfig_1.V.4.5.h"
#define RGX_BVNC_CORE_KM_HEADER "cores/rgxcore_km_1.48.2.0.h" 
#define RGX_BVNC_CORE_HEADER "cores/rgxcore_1.48.2.0.h"
#define RGX_BNC_CONFIG_KM_HEADER "configs/rgxconfig_km_1.V.2.0.h" 
#define RGX_BNC_CONFIG_HEADER "configs/rgxconfig_1.V.2.0.h"

#define SUPPORT_DBGDRV_EVENT_OBJECTS 
#define SYS_USING_INTERRUPTS 
#define CACHEFLUSH_TYPE CACHEFLUSH_GENERIC
#define SUPPORT_INSECURE_EXPORT 
#define SUPPORT_SECURE_EXPORT 
#define GPUVIRT_VALIDATION_NUM_OS 8
#define SUPPORT_LINUX_X86_WRITECOMBINE 
#define SUPPORT_LINUX_X86_PAT 
#define PVR_LINUX_USING_WORKQUEUES 
#define PVR_LINUX_MISR_USING_PRIVATE_WORKQUEUE 
#define PVR_LINUX_TIMERS_USING_WORKQUEUES 
#define PVR_LDM_DRIVER_REGISTRATION_NAME "pvrsrvkm"
#define LDM_PLATFORM 
#define PVR_MMAP_USE_VM_INSERT 
#define SUPPORT_PERCONTEXT_FREELIST 
#define PVRSRV_ENABLE_PROCESS_STATS 
#define PVR_LINUX_PHYSMEM_MAX_POOL_PAGES 10240
#define PVR_LINUX_PHYSMEM_MIN_NUM_PAGES  256 
#define PVR_LINUX_PHYSMEM_MAX_ALLOC_ORDER  2 
#define PVR_LINUX_KMALLOC_ALLOCATION_THRESHOLD  16384 
#define SUPPORT_DRM 
#define SUPPORT_AUTH 
#define SUPPORT_DRM_DC_MODULE 
#define PVR_DRM_DRIVER_NAME "pvr"
