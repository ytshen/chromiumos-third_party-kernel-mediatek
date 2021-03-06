/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2004, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************

	Module Name:
	mcu_and.h

	Abstract:

	Revision History:
	Who         When          What
	--------    ----------    ----------------------------------------------
*/

#ifndef __MCU_AND_H__
#define __MCU_AND_H__

#include "mcu.h"

#ifndef WORKQUEUE_BH
#include <linux/interrupt.h>
#endif

struct _RTMP_ADAPTER;
struct _BANK_RF_REG_PAIR;
struct _R_M_W_REG;
struct _RF_R_M_W_REG;

#define CPU_CTL					0x0704
#define CLOCK_CTL				0x0708
#define RESET_CTL				0x070C
#define INT_LEVEL				0x0718
#define COM_REG0				0x0730
#define COM_REG1				0x0734
#define COM_REG2				0x0738
#define COM_REG3				0x073C
#define PCIE_REMAP_BASE1		0x0740
#define PCIE_REMAP_BASE2		0x0744
#define PCIE_REMAP_BASE3		0x0748
#define PCIE_REMAP_BASE4		0x074C
#define LED_CTRL				0x0770
#define LED_TX_BLINK_0			0x0774
#define LED_TX_BLINK_1			0x0778
#define LED0_S0				0x077C
#define LED0_S1				0x0780
#define SEMAPHORE_00			0x07B0
#define SEMAPHORE_01			0x07B4
#define SEMAPHORE_02			0x07B8
#define SEMAPHORE_03			0x07BC

#define MCU_WAIT_ACK_CMD_THRESHOLD 0x0f
#define MCU_RX_CMD_THRESHOLD 0x0f

/*
 * Event Type ID
 */
enum EVENT_TYPE_ID {
	RSP_EVT_TYPE_FORCE_DUMP 				= 2,
	RSP_EVT_TYPE_FW_LOG 					= 3,
	RSP_EVT_TYPE_COEX_RSP_EVENT 			= 9,
	RSP_EVT_TYPE_TDLS_BACK_TO_BASE_CHANNEL 	= 12,
	RSP_EVT_TYPE_TDLS_STAY_TIME_OUT 	   	= 13,
};

#ifdef MT76XX_BTCOEX_SUPPORT
#define RSP_UpdateCOEXMode                           1
#define RSP_BT_DEVICE_LINK_STATUS             2
#endif /*MT76XX_BTCOEX_SUPPORT*/

#ifdef RTMP_MAC_PCI
#define ANDES_FIRMWARE_IMAGE_BASE     0x80000
#endif /* RTMP_MAC_PCI */

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _TXINFO_NMAC_CMD_PKT{
	UINT32 info_type:2;
	UINT32 d_port:3;
	UINT32 cmd_type:7;
	UINT32 cmd_seq:4;
	UINT32 pkt_len:16;
}TXINFO_NMAC_CMD_PKT;
#else
typedef struct GNU_PACKED _TXINFO_NMAC_CMD_PKT {
	UINT32 pkt_len:16;
	UINT32 cmd_seq:4;
	UINT32 cmd_type:7;
	UINT32 d_port:3;
	UINT32 info_type:2;
}TXINFO_NMAC_CMD_PKT;
#endif /* RT_BIG_ENDIAN */

enum cmd_msg_state {
	illegal,
	tx_start,
	tx_kickout_fail,
	tx_timeout_fail,
	tx_retransmit,
	tx_done,
	wait_cmd_out,
	wait_cmd_out_and_ack,
	wait_ack,
	rx_start,
	rx_receive_fail,
	rx_done,
};

enum {
	MCU_INIT,
	MCU_TX_HALT,
	MCU_RX_HALT,
};

enum {
	CMD_ACK,
};

enum cmd_msg_error_type {
	error_tx_kickout_fail,
	error_tx_timeout_fail,
	error_rx_receive_fail,
};

struct MCU_CTRL {
	u8 cmd_seq;
	unsigned long flags;
#ifndef WORKQUEUE_BH
	RTMP_NET_TASK_STRUCT cmd_msg_task;
#else
	struct tasklet_struct cmd_msg_task;
#endif
	NDIS_SPIN_LOCK txq_lock;
	DL_LIST txq;
	NDIS_SPIN_LOCK rxq_lock;
	DL_LIST rxq;
	NDIS_SPIN_LOCK ackq_lock;
	DL_LIST ackq;
	NDIS_SPIN_LOCK kickq_lock;
	DL_LIST kickq;
	NDIS_SPIN_LOCK tx_doneq_lock;
	DL_LIST tx_doneq;
	NDIS_SPIN_LOCK rx_doneq_lock;
	DL_LIST rx_doneq;
	unsigned long tx_kickout_fail_count;
	unsigned long tx_timeout_fail_count;
	unsigned long rx_receive_fail_count;
	unsigned long alloc_cmd_msg;
	unsigned long free_cmd_msg;
	BOOLEAN power_on;
	BOOLEAN dpd_on;
	struct _RTMP_ADAPTER *ad;
};


struct cmd_msg;
typedef void (*MSG_RSP_HANDLER)(struct cmd_msg *msg, char *payload, u16 payload_len);
typedef void (*MSG_EVENT_HANDLER)(struct _RTMP_ADAPTER *ad, char *payload, u16 payload_len);

struct cmd_msg_cb {
	struct cmd_msg *msg;
};

#define USB_END_PADDING 4
#define UPLOAD_PATCH_UNIT 2048
#define PATCH_INFO_SIZE 30
#define FW_INFO_SIZE 32
#define IV_SIZE 0x40
#define GET_SEMAPHORE_RETRY_MAX 600
#define UPLOAD_FW_UNIT 14592
#define UPLOAD_FW_TIMEOUT 1000
#define CMD_MSG_CB(pkt) ((struct cmd_msg_cb *)(GET_OS_PKT_CB(pkt)))
#define CMD_MSG_RETRANSMIT_TIMES 3
#define CMD_MSG_TIMEOUT 500

struct cmd_msg {
	DL_LIST list;
	u8 type;
	u8 seq;
	u16 timeout;
	u16 rsp_payload_len;
	BOOLEAN need_wait;
	BOOLEAN need_rsp;
	BOOLEAN need_retransmit;
#ifdef RTMP_PCI_SUPPORT
	BOOLEAN ack_done;
#endif

#ifdef RTMP_USB_SUPPORT
	RTMP_OS_COMPLETION ack_done;
#endif
	char *rsp_payload;
	MSG_RSP_HANDLER rsp_handler;
	enum cmd_msg_state state;
	void *priv;
	PNDIS_PACKET net_pkt;
#ifdef RTMP_USB_SUPPORT
	PURB urb;
#endif
	int retransmit_times;
};

/*
 * Calibration ID
 */
enum CALIBRATION_ID {
	R_CALIBRATION = 1,
	RXDCOC_CALIBRATION = 2,
	LC_CALIBRATION = 3,
	LOFT_CALIBRATION = 4,
	TXIQ_CALIBRATION = 5,
	BW_CALIBRATION = 6,
	DPD_CALIBRATION = 7,
	RXIQ_CALIBRATION = 8,
	TXDCOC_CALIBRATION = 9,
	RX_GROUP_DELAY_CALIBRATION = 10,
	TX_GROUP_DELAY_CALIBRATION = 11,
	FULL_CALIBRATION_ID = 0xFF,
};

enum CALIBRATION_ID_7662 {
	R_CALIBRATION_7662 = 1,
	TEMP_SENSOR_CALIBRATION_7662,
	RXDCOC_CALIBRATION_7662,
	RC_CALIBRATION_7662,
	SX_LOGEN_CALIBRATION_7662,
	LC_CALIBRATION_7662,
	TX_LOFT_CALIBRATION_7662,
	TXIQ_CALIBRATION_7662,
	TSSI_CALIBRATION_7662,
	TSSI_COMPENSATION_7662,
	DPD_CALIBRATION_7662,
	RXIQC_FI_CALIBRATION_7662,
	RXIQC_FD_CALIBRATION_7662,
};

enum CALIBRATION_TYPE {
	FULL_CALIBRATION,
	PARTIAL_CALIBRATION,
};

enum SWITCH_CHANNEL_STAGE {
	NORMAL_OPERATING = 0x01,
	SCANNING = 0x02,
	TEMPERATURE_CHANGE = 0x04,
};

/*
 * Function set ID
 */
enum FUN_ID {
	Q_SELECT = 1,
	USB2_SW_DISCONNECT = 2,
	USB3_SW_DISCONNECT = 3,
	LOG_FW_DEBUG_MSG = 4,
	ATOMIC_TSSI_SETTING 	= 5,
	GET_FW_VERSION 			= 7,
	TRIGGER_AUTO_RECOVERY 	= 8,
	FIXED_TX_MCS 			= 9,
	CORE_DUMP_TO_HOST 		= 10,
};
/* For Wake on Wireless LAN */
#if 0
#if (defined(WOW_SUPPORT) && defined(RTMP_MAC_USB)) || defined(NEW_WOW_SUPPORT)
typedef struct _WOW_CFG_STRUCT {
	BOOLEAN			bEnable;		/* Enable WOW function*/
	BOOLEAN			bWOWFirmware;	/* Enable WOW function, trigger to reload WOW-support firmware */
	BOOLEAN			bInBand;		/* use in-band signal to wakeup system */
	UINT8			nSelectedGPIO;	/* Side band signal to wake up system */
	UINT8			nDelay;			/* Delay number is multiple of 3 secs, and it used to postpone the WOW function */
	UINT8           nHoldTime;      /* GPIO puls hold time, unit: 10ms */
} WOW_CFG_STRUCT, *PWOW_CFG_STRUCT;
#endif /* (defined(WOW_SUPPORT) && defined(RTMP_MAC_USB)) || defined(NEW_WOW_SUPPORT) */

#ifdef NEW_WOW_SUPPORT
typedef enum {
	WOW_PKT_TO_HOST,
	WOW_PKT_TO_ANDES
} WOW_PKT_FLOW_T;

typedef enum {
	WOW_WAKEUP_BY_PCIE,
	WOW_WAKEUP_BY_USB,
	WOW_WAKEUP_BY_GPIO
} WOW_WAKEUP_METHOD_T;

typedef enum {
	WOW_ENABLE = 1,
	WOW_TRAFFIC = 3,
	WOW_WAKEUP = 4,
	WOW_AID_CHANNEL = 6
} WOW_FEATURE_T;

typedef enum {
	WOW_MASK_CFG = 1,
	WOW_SEC_CFG,
	WOW_INFRA_CFG,
	WOW_P2P_CFG,
} WOW_CONFIG_T;

enum {
	WOW_MAGIC_PKT,
	WOW_BITMAP,
	WOW_IPV4_TCP_SYNC,
	WOW_IPV6_TCP_SYNC
};

typedef struct NEW_WOW_MASK_CFG_STRUCT {
	UINT32 	Config_Type;
	UINT32 	Function_Enable;
	UINT32 	Detect_Mask;
	UINT32 	Event_Mask;
} NEW_WOW_MASK_CFG_STRUCT, PNEW_WOW_MASK_CFG_STRUCT;

typedef struct NEW_WOW_SEC_CFG_STRUCT {
	UINT32 	Config_Type;
	UINT32 	WPA_Ver;
	UCHAR 	PTK[64];
	UCHAR 	R_COUNTER[8];
	UCHAR 	Key_Id;
	UCHAR 	Cipher_Alg;
	UCHAR 	WCID;
	UCHAR 	Group_Cipher;
} NEW_WOW_SEC_CFG_STRUCT, PNEW_WOW_SEC_CFG_STRUCT;

typedef struct NEW_WOW_INFRA_CFG_STRUCT {
	UINT32 	Config_Type;
	UCHAR 	STA_MAC[6];
	UCHAR 	AP_MAC[6];
	UINT32 	AP_Status;
} NEW_WOW_INFRA_CFG_STRUCT, PNEW_WOW_INFRA_CFG_STRUCT;

typedef struct _NEW_WOW_P2P_CFG_STRUCT {
	UINT32 	Config_Type;
	UCHAR 	GO_MAC[6];
	UCHAR 	CLI_MAC[6];
	UINT32 	P2P_Status;
} NEW_WOW_P2P_CFG_STRUCT, *PNEW_WOW_P2P_CFG_STRUCT;

typedef struct _NEW_WOW_PARAM_STRUCT {
	UINT32 	Parameter;
	UINT32 	Value;
} NEW_WOW_PARAM_STRUCT, *PNEW_WOW_PARAM_STRUCT;

typedef struct _NEW_WOW_AID_CHANNEL_STRUCT {
	UINT32 	Parameter;
	UINT32 	Aid;
	UINT32 	Channel;
} NEW_WOW_AID_CHANNEL_STRUCT, *PNEW_WOW_AID_CHANNEL_STRUCT;

#endif /* NEW_WOW_SUPPORT */
#endif
/*
 * Command response RX Ring selection
 */
enum RX_RING_ID {
	RX_RING0,
	RX_RING1,
};

enum BW_SETTING {
	BW20 = 1,
	BW40 = 2,
	BW10 = 4,
	BW80 = 8,
};

/*
 * FW debug message parameters
 */
enum FW_DEBUG_SETTING {
	DISABLE_DEBUG_MSG = 0,
	DEBUG_MSG_TO_UART,
	DEBUG_MSG_TO_HOST,
};

#if 0
#ifdef MT76XX_BTCOEX_SUPPORT
typedef struct _COEX_PROTECTION_FRAME_INFO
{
	ULONG					CoexOperation;
    ULONG                   Triggernumber;
    ULONG                   Valid;
    ULONG                   NodeType;
    ULONG	            BssHashID;
    ULONG                   FrameType;
} COEX_PROTECTION_FRAME_INFO, *PCOEX_PROTECTION_FRAME_INFO;

typedef struct _COEX_AFH
{
	ULONG					CoexOperation;
    ULONG                   LinkStatus;
    ULONG                   BW;
    ULONG                   Channel;
 } COEX_AFH, *PCOEX_AFH;

typedef struct _COEX_TF_SWITCH
{
    ULONG					CoexOperation;
    ULONG                   CoexMode;

 } COEX_TF_SWITCH, *PCOEX_TF_SWITCH;


typedef struct _COEX_WLAN_STATUS
{
    ULONG		     CoexOperation;
    ULONG                   WLANStatus;
    ULONG                   PrivilegeTime;

 } COEX_WLAN_STATUS, *PCOEX_WLAN_STATUS;

#define PKT_CMD_TYPE_COEX_OP			(17)

#endif
#endif
enum CR_TYPE {
	RF_CR,
	BBP_CR,
	RF_BBP_CR,
	HL_TEMP_CR_UPDATE,
};

enum TEMPERATURE_LEVEL_7662 {
	NORMAL_TEMP_7662, /* 0~60 */
	LOW_TEMP_7662, /* < 0 */
	HIGH_TEMP_7662, /* > 60 */
};

#define LOAD_CR_MODE_MASK (0xff)
#define LOAD_CR_MODE(p) (((p) & 0xff))
#define LOAD_CR_TEMP_LEVEL_MASK (0xff << 8)
#define LOAD_CR_TEMP_LEVEL(p) (((p) & 0xff) << 8)
#define LOAD_CR_CHL_MASK (0xff << 16)
#define LOAD_CR_CHL(p) (((p) & 0xff) << 16)

#define SC_PARAM1_CHL_MASK (0xff)
#define SC_PARAM1_CHL(p) (((p) & 0xff))
#define SC_PARAM1_SCAN_MASK (0xff << 8)
#define SC_PARAM1_SCAN(p) (((p) & 0xff) << 8)
#define SC_PARAM1_BW_MASK (0xff << 16)
#define SC_PARAM1_BW(p) (((p) & 0xff) << 16)

#define SC_PARAM2_TR_SETTING_MASK (0xffff)
#define SC_PARAM2_TR_SETTING(p) (((p) & 0xffff))
#define SC_PARAM2_EXTENSION_CHL_MASK (0xff << 16)
#define SC_PARAM2_EXTENSION_CHL(p) (((p) & 0xff) << 16)

#define TSSI_PARAM2_SLOPE0_MASK (0xff)
#define TSSI_PARAM2_SLOPE0(p) (((p) & 0xff))
#define TSSI_PARAM2_SLOPE1_MASK (0xff << 8)
#define TSSI_PARAM2_SLOPE1(p) (((p) & 0xff) << 8)
#define TSSI_PARAM2_OFFSET0_MASK (0xff << 16)
#define TSSI_PARAM2_OFFSET0(p) (((p) & 0xff) << 16)
#define TSSI_PARAM2_OFFSET1_MASK (0xff << 24)
#define TSSI_PARAM2_OFFSET1(p) (((p) & 0xff) << 24)



#if 1//def CONFIG_MULTI_CHANNEL
//yiwei mcc f/w cmd

#define MCC_START1_CHL_1ST_MASK (0xff)
#define MCC_START1_CHL_1ST(p) (((p) & 0xff))

#define MCC_START1_CHL_2ND_MASK (0xff << 8)
#define MCC_START1_CHL_2ND(p) (((p) & 0xff) << 8)

#define MCC_START1_BW_1ST_MASK (0x03 << 16)
#define MCC_START1_BW_1ST(p) (((p) & 0x03) << 16)

#define MCC_START1_BW_2ND_MASK (0x03 << 18)
#define MCC_START1_BW_2ND(p) (((p) & 0x03) << 18)

#define MCC_START1_ROLE_1ST_MASK (0x03 << 20)
#define MCC_START1_ROLE_1ST(p) (((p) & 0x03) << 20)

#define MCC_START1_ROLE_2ND_MASK (0x03 << 22)
#define MCC_START1_ROLE_2ND(p) (((p) & 0x03) << 22)

#define MCC_START1_TRX_1ST_MASK (0x03 << 24)
#define MCC_START1_TRX_1ST(p) (((p) & 0x03) << 24)

#define MCC_START1_TRX_2ND_MASK (0x03 << 26)
#define MCC_START1_TRX_2ND(p) (((p) & 0x03) << 26)

#define MCC_START1_ACQ_1ST_MASK (0x03 << 28)
#define MCC_START1_ACQ_1ST(p) (((p) & 0x03) << 28)

#define MCC_START1_ACQ_2ND_MASK (0x03 << 30)
#define MCC_START1_ACQ_2ND(p) (((p) & 0x03) << 30)


#define MCC_START2_CYCLE_1ST_MASK (0xffff)
#define MCC_START2_CYCLE_1ST(p) ((p) & 0xffff)

#define MCC_START2_CYCLE_2ND_MASK (0xffff << 16)
#define MCC_START2_CYCLE_2ND(p) (((p) & 0xffff) << 16)

#define MCC_START2_WTT_MASK                         (0xffff)
#define MCC_START2_WTT(p)                  ((p) & 0xffff)

#define MCC_START2_NULL_CNT_MASK (0xffff << 16)
#define MCC_START2_NULL_CNT(p) (((p) & 0xffff) << 16)

#define MCC_START2_EXTCH_1ST_MASK (0x3 << 24)
#define MCC_START2_EXTCH_1ST(p) (((p) & 0x3) << 24)
#define MCC_START2_EXTCH_2ND_MASK (0x3 << 26)
#define MCC_START2_EXTCH_2ND(p) (((p) & 0x3) << 26)

#define MCC_STOP1_PARK_CHL_MASK (0x03)
#define MCC_STOP1_PARK_CHL(p) ((p) & 0x03)

#define MCC_STOP1_AUTO_RESUME_MODE_MASK (0x0C)
#define MCC_STOP1_AUTO_RESUME_MODE(p) ((p) & 0x0C)

#define MCC_STOP1_AUTO_RESUME_TIME_MASK (0xffff << 16)
#define MCC_STOP1_AUTO_RESUME_TIME(p) (((p) & 0xffff) << 16)

#endif


/*
 * Command type table
 */
enum CMD_TYPE {
	CMD_FUN_SET_OP = 1,
	CMD_LOAD_CR,
	CMD_INIT_GAIN_OP = 3,
#if 1//def CONFIG_MULTI_CHANNEL
	CMD_MCC_START = 4,
	CMD_MCC_STOP = 5,
#endif
#ifndef HOST_DYNAMIC_VGA_SUPPORT
	CMD_DYNC_VGA_OP = 6,
#endif /* HOST_DYNAMIC_VGA_SUPPORT */
#ifdef CFG_TDLS_SUPPORT
	CMD_TDLS_CH_SW = 7,
#endif /* CFG_TDLS_SUPPORT */
	CMD_BURST_WRITE = 8,
	CMD_READ_MODIFY_WRITE,
	CMD_RANDOM_READ,
	CMD_BURST_READ,
	CMD_RANDOM_WRITE = 12,
	CMD_LED_MODE_OP = 16,
	CMD_POWER_SAVING_OP = 20,
	CMD_WOW_CONFIG,
	CMD_WOW_QUERY,
	CMD_WOW_FEATURE = 24,
	CMD_CARRIER_DETECT_OP = 28,
	CMD_RADOR_DETECT_OP,
	CMD_SWITCH_CHANNEL_OP,
	CMD_CALIBRATION_OP,
	CMD_BEACON_OP,
	CMD_ANTENNA_OP
};

/*
 * Event type table
 */
enum EVENT_TYPE {
	CMD_DONE,
	CMD_ERROR,
	CMD_RETRY,
	EVENT_PWR_RSP,
	EVENT_WOW_RSP,
	EVENT_CARRIER_DETECT_RSP,
	EVENT_DFS_DETECT_RSP,
};

enum mcu_skb_state {
	ILLEAGAL = 0,
	MCU_CMD_START,
	MCU_CMD_DONE,
	MCU_RSP_START,
	MCU_RSP_DONE,
	MCU_RSP_CLEANUP,
	UNLINK_START,
};

struct mcu_skb_data {
	enum mcu_skb_state state;
};

typedef	union _ANDES_CALIBRATION_PARAM {
	UINT32 generic;
#ifdef MT76x2
	struct {
		UINT32 pa_mode;
		UINT32 tssi_slope_offset;
	} mt76x2_tssi_comp_param;
#endif
} ANDES_CALIBRATION_PARAM;

enum CALIBRATION_TEST_TYPE {
	CAL_ROBUST_TEST=0,

};

#ifdef RTMP_MAC_USB
int andes_usb_loadfw(struct _RTMP_ADAPTER *ad);
int andes_usb_erasefw(struct _RTMP_ADAPTER *ad);
int andes_usb_load_rom_patch(struct _RTMP_ADAPTER *ad);
int andes_usb_erase_rom_patch(struct _RTMP_ADAPTER *ad);
void andes_usb_fw_init(struct _RTMP_ADAPTER *ad);
#endif /* RTMP_MAC_USB */
#ifdef RTMP_PCI_SUPPORT
int andes_pci_load_rom_patch(struct _RTMP_ADAPTER *ad);
int andes_pci_erase_rom_patch(struct _RTMP_ADAPTER *ad);
int andes_pci_loadfw(struct _RTMP_ADAPTER *ad);
int andes_pci_erasefw(struct _RTMP_ADAPTER *ad);
void pci_rx_cmd_msg_complete(struct _RTMP_ADAPTER *ad, RXFCE_INFO *fce_info);
void andes_pci_fw_init(struct _RTMP_ADAPTER *ad);
#endif /* RTMP_PCI_SUPPORT */
void andes_ctrl_init(struct _RTMP_ADAPTER *ad);
void andes_ctrl_enable(struct _RTMP_ADAPTER *ad);
void andes_ctrl_disable(struct _RTMP_ADAPTER *ad);
void andes_ctrl_exit(struct _RTMP_ADAPTER *ad);
int andes_send_cmd_msg(struct _RTMP_ADAPTER *ad, struct cmd_msg *msg);
int andes_burst_write(struct _RTMP_ADAPTER *ad, u32 offset, u32 *data, u32 cnt);
int andes_burst_read(struct _RTMP_ADAPTER *ad, u32 offset, u32 cnt, u32 *data);
int andes_random_read(struct _RTMP_ADAPTER *ad, RTMP_REG_PAIR *reg_pair, u32 num);
int andes_rf_random_read(struct _RTMP_ADAPTER *ad, struct _BANK_RF_REG_PAIR *reg_pair, u32 num);
int andes_read_modify_write(struct _RTMP_ADAPTER *ad, struct _R_M_W_REG *reg_pair, u32 num);
int andes_rf_read_modify_write(struct _RTMP_ADAPTER *ad, struct _RF_R_M_W_REG *reg_pair, u32 num);
int andes_random_write(struct _RTMP_ADAPTER *ad, RTMP_REG_PAIR *reg_pair, u32 num);
int andes_rf_random_write(struct _RTMP_ADAPTER *ad, struct _BANK_RF_REG_PAIR *reg_pair, u32 num);
int andes_sc_random_write(struct _RTMP_ADAPTER *ad, CR_REG *table, u32 nums, u32 flags);
int andes_sc_rf_random_write(struct _RTMP_ADAPTER *ad, BANK_RF_CR_REG *table, u32 nums, u32 flags);
int andes_fun_set(struct _RTMP_ADAPTER *ad, u32 fun_id, u32 param);
int andes_pwr_saving(struct _RTMP_ADAPTER *ad, u32 op, u32 level,
					 u32 listen_interval, u32 pre_tbtt_lead_time,
					 u8 tim_byte_offset, u8 tim_byte_pattern);
int andes_calibration(struct _RTMP_ADAPTER *ad, u32 cal_id, ANDES_CALIBRATION_PARAM *param);
#ifdef NEW_WOW_SUPPORT
int andes_wow_enable(struct _RTMP_ADAPTER *ad);
int andes_wow_disable(struct _RTMP_ADAPTER *ad);
#endif
BOOLEAN is_inband_cmd_processing(struct _RTMP_ADAPTER *ad);
void andes_cmd_msg_bh(unsigned long param);
int usb_rx_cmd_msg_submit(struct _RTMP_ADAPTER *ad);
int usb_rx_cmd_msgs_receive(struct _RTMP_ADAPTER *ad);
void andes_bh_schedule(struct _RTMP_ADAPTER *ad);
void pci_kick_out_cmd_msg_complete(PNDIS_PACKET net_pkt);
int andes_load_cr(struct _RTMP_ADAPTER *ad, u32 cr_type, UINT8 temp_level, UINT8 channel);
int andes_switch_channel(struct _RTMP_ADAPTER *ad, u8 channel, BOOLEAN scan, unsigned int bw, unsigned int tx_rx_setting, u8 bbp_ch_idx);

#if 1//def CONFIG_MULTI_CHANNEL


int andes_mcc_start(struct _RTMP_ADAPTER *ad,
u8 channel_1st,
u8 channel_2nd,
unsigned int bw_1st,
unsigned int bw_2nd,
u8 extch_1st,
u8 extch_2nd,
u8 role_1st,
u8 role_2nd,
u16 cycle_time_1st,
u16 cycle_time_2nd,
u16 wait_time,
u16 null_cnt,
u32 tssi_slope_offset_1st,
u32 tssi_slope_offset_2nd,
u32 start_tsf);

int andes_mcc_stop(struct _RTMP_ADAPTER *ad, u8 parking_channel, u8 auto_resume_mode, u16 auto_resume_time, u32 auto_resume_tsf);
#endif
int andes_init_gain(struct _RTMP_ADAPTER *ad, UINT8 channel, BOOLEAN force_mode, unsigned int gain_from_e2p);
int andes_dynamic_vga(struct _RTMP_ADAPTER *ad, UINT8 channel, BOOLEAN mode, BOOLEAN ext, int rssi, unsigned int false_cca);
int andes_led_op(struct _RTMP_ADAPTER *ad, u32 led_idx, u32 link_status);
struct cmd_msg *andes_alloc_cmd_msg(struct _RTMP_ADAPTER *ad, unsigned int length);
void andes_init_cmd_msg(struct cmd_msg *msg, u8 type, BOOLEAN need_wait, u16 timeout,
							   BOOLEAN need_retransmit, BOOLEAN need_rsp, u16 rsp_payload_len,
							   char *rsp_payload, MSG_RSP_HANDLER rsp_handler);
void andes_append_cmd_msg(struct cmd_msg *msg, char *data, unsigned int len);
void andes_free_cmd_msg(struct cmd_msg *msg);
#ifdef MT7601
INT AndesBBPRandomWritePair(struct _RTMP_ADAPTER *pAd, RTMP_REG_PAIR *RegPair, UINT32 Num);
INT AndesBBPRandomWrite(struct _RTMP_ADAPTER *pAd, UINT32 Num, ...);
#endif /* MT7601 */

#define MAX_CALIBRATION_WAIT_TIME						100
#ifdef RTMP_PCI_SUPPORT
#define ANDES_CALIBRATION_START(_pAd)						\
{															\
	UINT32 _value;											\
	RTMP_IO_READ32(_pAd, COM_REG0, &_value);				\
	_value &= 0x7FFFFFFF;										\
	_RTMP_IO_WRITE32(_pAd, COM_REG0, _value);				\
}


#define ANDES_WAIT_CALIBRATION_DONE(_pAd)				\
{															\
	UINT32 _value;											\
	INT32 _i;													\
	RtmpOsMsDelay(1);										\
	for ( _i = 0 ; _i < MAX_CALIBRATION_WAIT_TIME; _i ++ ) {		\
		RTMP_IO_READ32(_pAd, COM_REG0, &_value);			\
		if ( _value & 0x80000000 )								\
			break;											\
		RtmpOsMsDelay(5);									\
	}														\
	if ( _i == MAX_CALIBRATION_WAIT_TIME )					\
		DBGPRINT(RT_DEBUG_ERROR,("ANDES_WAIT_CALIBRATION_DONE timeout!\n"));	\
	else														\
		DBGPRINT(RT_DEBUG_INFO,("ANDES_WAIT_CALIBRATION_DONE %d\n", _i));	\
}
#endif /* RTMP_PCI_SUPPORT */

#endif /* __MCU_AND_H__ */

