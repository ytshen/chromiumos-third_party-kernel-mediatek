#ifndef __IRQ_H__
#define __IRQ_H__

#define GIC_PRIVATE_SIGNALS     (32)
#define NR_GIC_SGI              (16)
#define NR_GIC_PPI              (16)
#define GIC_PPI_OFFSET          (27)
#define MT_NR_PPI           (5)
#define MT_NR_SPI           (224)
#define NR_MT_IRQ_LINE  (GIC_PPI_OFFSET + MT_NR_PPI + MT_NR_SPI)	/* 27 Private interrupt and 5 PPIs and 219 SPIs */

#define GIC_PPI_GLOBAL_TIMER                (GIC_PPI_OFFSET + 0)
#define GIC_PPI_LEGACY_FIQ                  (GIC_PPI_OFFSET + 1)
#define GIC_PPI_PRIVATE_TIMER               (GIC_PPI_OFFSET + 2)
#define GIC_PPI_NS_PRIVATE_TIMER            (GIC_PPI_OFFSET + 3)
#define GIC_PPI_LEGACY_IRQ                  (GIC_PPI_OFFSET + 4)
#define MT8135_USB0_IRQ_ID                  (GIC_PRIVATE_SIGNALS + 32)
#define MT_USB1_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 33)
#define MT_TS_IRQ_ID                        (GIC_PRIVATE_SIGNALS + 34)
#define MT_TSATCH_IRQ_ID                    (GIC_PRIVATE_SIGNALS + 35)
#define MT_LOWBATTERY_IRQ_ID                (GIC_PRIVATE_SIGNALS + 36)
#define MT_PWM_IRQ_ID                       (GIC_PRIVATE_SIGNALS + 37)
#define MT_PTP_THERM_IRQ_ID                 (GIC_PRIVATE_SIGNALS + 38)
#define MT_MSDC0_IRQ_ID                     (GIC_PRIVATE_SIGNALS + 39)
#define MT_MSDC1_IRQ_ID                     (GIC_PRIVATE_SIGNALS + 40)
#define MT_MSDC2_IRQ_ID                     (GIC_PRIVATE_SIGNALS + 41)
#define MT_MSDC3_IRQ_ID                     (GIC_PRIVATE_SIGNALS + 42)
#define MT_AP_HIF_IRQ_ID                    (GIC_PRIVATE_SIGNALS + 43)
#define MT_I2C0_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 44)
#define MT_I2C1_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 45)
#define MT_I2C2_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 46)
#define MT_I2C3_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 47)
#define MT_I2C4_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 48)
#define MT_I2C5_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 49)
#define MT_I2C6_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 50)
#define MT_UART1_IRQ_ID                     (GIC_PRIVATE_SIGNALS + 51)
#define MT_UART2_IRQ_ID                     (GIC_PRIVATE_SIGNALS + 52)
#define MT_UART3_IRQ_ID                     (GIC_PRIVATE_SIGNALS + 53)
#define MT_UART4_IRQ_ID                     (GIC_PRIVATE_SIGNALS + 54)
#define MT_NFIECC_IRQ_ID                    (GIC_PRIVATE_SIGNALS + 55)
#define MT_NFI_IRQ_ID                       (GIC_PRIVATE_SIGNALS + 56)
#define MT_GDMA1_IRQ_ID                     (GIC_PRIVATE_SIGNALS + 57)
#define MT_GDMA2_IRQ_ID                     (GIC_PRIVATE_SIGNALS + 58)
#define MT_DMA_AP_HIF_ID                    (GIC_PRIVATE_SIGNALS + 59)
#define MT_DMA_MD_HIF_ID                    (GIC_PRIVATE_SIGNALS + 60)
#define MT_DMA_IRDA_ID                      (GIC_PRIVATE_SIGNALS + 61)
#define MT_DMA_I2C1_ID                      (GIC_PRIVATE_SIGNALS + 62)
#define MT_DMA_I2C2_ID                      (GIC_PRIVATE_SIGNALS + 63)
#define MT_DMA_I2C3_ID                      (GIC_PRIVATE_SIGNALS + 64)
#define MT_DMA_I2C4_ID                      (GIC_PRIVATE_SIGNALS + 65)
#define MT_DMA_I2C5_ID                      (GIC_PRIVATE_SIGNALS + 66)
#define MT_DMA_I2C6_ID                      (GIC_PRIVATE_SIGNALS + 67)
#define MT_DMA_I2C7_ID                      (GIC_PRIVATE_SIGNALS + 68)
#define MT_DMA_UART0_TX_IRQ_ID              (GIC_PRIVATE_SIGNALS + 69)
#define MT_DMA_UART0_RX_IRQ_ID              (GIC_PRIVATE_SIGNALS + 70)
#define MT_DMA_UART1_TX_IRQ_ID              (GIC_PRIVATE_SIGNALS + 71)
#define MT_DMA_UART1_RX_IRQ_ID              (GIC_PRIVATE_SIGNALS + 72)
#define MT_DMA_UART2_TX_IRQ_ID              (GIC_PRIVATE_SIGNALS + 73)
#define MT_DMA_UART2_RX_IRQ_ID              (GIC_PRIVATE_SIGNALS + 74)
#define MT_IRDA_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 76)
#define MT_MD_HIF_IRQ_ID                    (GIC_PRIVATE_SIGNALS + 77)
#define MT8135_SPI1_IRQ_ID                  (GIC_PRIVATE_SIGNALS + 78)
#define MT_MSDC0_WAKEUP_PS_ID               (GIC_PRIVATE_SIGNALS + 79)
#define MT_MSDC1_WAKEUP_PS_ID               (GIC_PRIVATE_SIGNALS + 80)
#define MT_MSDC2_WAKEUP_PS_ID               (GIC_PRIVATE_SIGNALS + 81)
#define MT_MSDC3_WAKEUP_PS_ID               (GIC_PRIVATE_SIGNALS + 82)
#define MT_MSDC4_IRQ_ID                     (GIC_PRIVATE_SIGNALS + 83)
#define MT_MSDC4_WAKEUP_PS_ID               (GIC_PRIVATE_SIGNALS + 84)
#define MT_PTP_FSM_IRQ_ID                   (GIC_PRIVATE_SIGNALS + 85)
#define MT_GCPU_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 86)
#define MT_GCPU_DMX_IRQ_ID                  (GIC_PRIVATE_SIGNALS + 87)
#define MT_WDT_IRQ_ID                       (GIC_PRIVATE_SIGNALS + 88)
#define MT_DCC_APARM_IRQ_ID                 (GIC_PRIVATE_SIGNALS + 92)
#define MT_APARM_CTI_IRQ_ID                 (GIC_PRIVATE_SIGNALS + 93)
#define MT_APARM_DOMAIN_IRQ_ID              (GIC_PRIVATE_SIGNALS + 94)
#define MT_APARM_DECERR_IRQ_ID              (GIC_PRIVATE_SIGNALS + 95)
#define MT_DOMAIN_ABORT0_ID                 (GIC_PRIVATE_SIGNALS + 96)
#define MT_DOMAIN_ABORT1_ID                 (GIC_PRIVATE_SIGNALS + 97)
#define MT_DOMAIN_ABORT2_ID                 (GIC_PRIVATE_SIGNALS + 98)
#define MT_DOMAIN_ABORT3_ID                 (GIC_PRIVATE_SIGNALS + 99)
#define MT_MCI_ERR_IRQ_ID                   (GIC_PRIVATE_SIGNALS + 100)
#define MT_AFE_IRQ_MCU_ID                   (GIC_PRIVATE_SIGNALS + 104)
#define MT_M4U0_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 105)
#define MT_M4U1_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 106)
#define MT_M4UL2_IRQ_ID                     (GIC_PRIVATE_SIGNALS + 107)
#define MT_M4UL2_SEC_IRQ_ID                 (GIC_PRIVATE_SIGNALS + 108)
#define MT_REFRESH_RATE_INT_PULSE_ID        (GIC_PRIVATE_SIGNALS + 109)
#define MT8135_GPT_IRQ_ID                   (GIC_PRIVATE_SIGNALS + 113)
#define MT_CCIF0_AP_IRQ_ID                  (GIC_PRIVATE_SIGNALS + 114)
#define MT_CCIF1_AP_IRQ_ID                  (GIC_PRIVATE_SIGNALS + 115)
#define MT_EINT_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 116)
#define MT_EINT_IRQ_FCORE_EINT_IRQ_ID       (GIC_PRIVATE_SIGNALS + 117)
#define MT_EINT_IRQ2_ID                     (GIC_PRIVATE_SIGNALS + 118)
#define MT_EINT_DIRECT_IRQ0_ID              (GIC_PRIVATE_SIGNALS + 119)
#define MT_EINT_DIRECT_IRQ1_ID              (GIC_PRIVATE_SIGNALS + 120)
#define MT_EINT_DIRECT_IRQ2_ID              (GIC_PRIVATE_SIGNALS + 121)
#define MT_EINT_DIRECT_IRQ3_ID              (GIC_PRIVATE_SIGNALS + 122)
#define MT_EINT_DIRECT_IRQ4_ID              (GIC_PRIVATE_SIGNALS + 123)
#define MT_EINT_DIRECT_IRQ5_ID              (GIC_PRIVATE_SIGNALS + 124)
#define MT_EINT_DIRECT_IRQ6_ID              (GIC_PRIVATE_SIGNALS + 125)
#define MT_EINT_DIRECT_IRQ7_ID              (GIC_PRIVATE_SIGNALS + 126)
#define MT_EINT_EVENT_ID                    (GIC_PRIVATE_SIGNALS + 127)
#define MT8135_PMIC_WRAP_IRQ_ID             (GIC_PRIVATE_SIGNALS + 128)	/* 0x80 */
#define MT_KP_IRQ_ID                        (GIC_PRIVATE_SIGNALS + 129)
#define MT_SPM_IRQ0_ID                      (GIC_PRIVATE_SIGNALS + 130)
#define MT_SPM_IRQ1_ID                      (GIC_PRIVATE_SIGNALS + 131)
#define MT_SPM_IRQ2_ID                      (GIC_PRIVATE_SIGNALS + 132)
#define MT_SPM_IRQ3_ID                      (GIC_PRIVATE_SIGNALS + 133)
#define MT_VENC_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 136)
#define MT_SMI_LARB0_IRQ_ID                 (GIC_PRIVATE_SIGNALS + 137)
#define MT_VDEC_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 140)
#define MT_SMI_LARB1_IRQ_ID                 (GIC_PRIVATE_SIGNALS + 141)
#define CAMERA_ISP_IRQ3_ID                  (GIC_PRIVATE_SIGNALS + 144)	/* cam_irq3_b */
#define MT_COMMON_INT_ID                    (GIC_PRIVATE_SIGNALS + 145)
#define MT8135_JPEG_ENC_IRQ_ID              (GIC_PRIVATE_SIGNALS + 147)
#define MT8135_JPEG_DEC_IRQ_ID              (GIC_PRIVATE_SIGNALS + 148)
#define CAMERA_ISP_IRQ2_ID                  (GIC_PRIVATE_SIGNALS + 149)	/* cam_irq2_b */
#define CAMERA_ISP_IRQ1_ID                  (GIC_PRIVATE_SIGNALS + 150)	/* cam_irq1_b */
#define CAMERA_ISP_IRQ0_ID                  (GIC_PRIVATE_SIGNALS + 151)	/* cam_irq_b */
#define MT_SENINF_IRQ_ID                    (GIC_PRIVATE_SIGNALS + 152)
#define MT_SMI_LARB3_IRQ_ID                 (GIC_PRIVATE_SIGNALS + 154)
#define MT_SMI_LARB4_IRQ_ID                 (GIC_PRIVATE_SIGNALS + 156)
#define MT8135_DISP_MUTEX_IRQ_ID            (GIC_PRIVATE_SIGNALS + 160)
#define MT8135_DISP_ROT_IRQ_ID              (GIC_PRIVATE_SIGNALS + 161)
#define MT8135_DISP_SCL_IRQ_ID              (GIC_PRIVATE_SIGNALS + 162)
#define MT8135_DISP_OVL_IRQ_ID              (GIC_PRIVATE_SIGNALS + 163)
#define MT8135_DISP_WDMA0_IRQ_ID            (GIC_PRIVATE_SIGNALS + 164)
#define MT8135_DISP_WDMA1_IRQ_ID            (GIC_PRIVATE_SIGNALS + 165)
#define MT8135_DISP_RDMA0_IRQ_ID            (GIC_PRIVATE_SIGNALS + 166)
#define MT8135_DISP_RDMA1_IRQ_ID            (GIC_PRIVATE_SIGNALS + 167)
#define MT8135_DISP_BLS_IRQ_ID              (GIC_PRIVATE_SIGNALS + 168)
#define MT8135_DISP_COLOR_IRQ_ID            (GIC_PRIVATE_SIGNALS + 169)
#define MT8135_DISP_TDSHP_IRQ_ID            (GIC_PRIVATE_SIGNALS + 170)
#define MT8135_DISP_DBI_IRQ_ID              (GIC_PRIVATE_SIGNALS + 171)
#define MT8135_DISP_DSI_IRQ_ID              (GIC_PRIVATE_SIGNALS + 172)
#define MT8135_DISP_DPI0_IRQ_ID             (GIC_PRIVATE_SIGNALS + 173)
#define MT8135_DISP_DPI1_IRQ_ID             (GIC_PRIVATE_SIGNALS + 174)
#define MT_SMI_LARB2_IRQ_ID                 (GIC_PRIVATE_SIGNALS + 175)
#define MT8135_DISP_CMDQ_IRQ_ID             (GIC_PRIVATE_SIGNALS + 176)
#define MT_G2D_IRQ_ID                       (GIC_PRIVATE_SIGNALS + 177)
#define MT_DISP_GAMMA_IRQ_ID                (GIC_PRIVATE_SIGNALS + 178)
#define MT_DISP_CMDQ_SECURE_IRQ_ID          (GIC_PRIVATE_SIGNALS + 179)
#define MT_DISP_HDMI_IRQ_ID                 (GIC_PRIVATE_SIGNALS + 180)
#define MT_DISP_UFO_IRQ_ID                  (GIC_PRIVATE_SIGNALS + 181)
#define MT_MFG_IRQ_ID                       (GIC_PRIVATE_SIGNALS + 188)
#define MT_CA15_PTP_FSM_IRQ_ID              (GIC_PRIVATE_SIGNALS + 192)
#define MT_CA15_PTP_THERM_IRQ_ID            (GIC_PRIVATE_SIGNALS + 193)
#define MT_CIRQ_IRQ_ID                      (GIC_PRIVATE_SIGNALS + 200)
#define MT_CA15_NCTIIRQ0_ID                 (GIC_PRIVATE_SIGNALS + 201)
#define MT_CA15_NCTIIRQ1_ID                 (GIC_PRIVATE_SIGNALS + 202)
#define MT_CA15_NPMUIRQ0_ID                 (GIC_PRIVATE_SIGNALS + 203)
#define MT_CA15_NPMUIRQ1_ID                 (GIC_PRIVATE_SIGNALS + 204)
#define MT_CA15_NAXIERRIRQ_ID               (GIC_PRIVATE_SIGNALS + 205)
#define MT_CA15_NINTERRIRQ_ID               (GIC_PRIVATE_SIGNALS + 206)
#define MT_CA15_NCNTHPIRQ0_ID               (GIC_PRIVATE_SIGNALS + 207)
#define MT_CA15_NCNTHPIRQ1_ID               (GIC_PRIVATE_SIGNALS + 208)
#define MT_CA15_NCNTVIRQ0_ID                (GIC_PRIVATE_SIGNALS + 209)
#define MT_CA15_NCNTVIRQ1_ID                (GIC_PRIVATE_SIGNALS + 210)
#define MT_CA15_NCNTPSIRQ0_ID               (GIC_PRIVATE_SIGNALS + 211)
#define MT_CA15_NCNTPSIRQ1_ID               (GIC_PRIVATE_SIGNALS + 212)
#define MT_CA15_NCNTPNSIRQ0_ID              (GIC_PRIVATE_SIGNALS + 213)
#define MT_CA15_NCNTPNSIRQ1_ID              (GIC_PRIVATE_SIGNALS + 214)
#define MT_CCI_NERRIRQ_ID                   (GIC_PRIVATE_SIGNALS + 215)
#define MT_CCI_MI0_ERRMID_SET_RIRQ_ID       (GIC_PRIVATE_SIGNALS + 216)
#define MT_CCI_MI0_ERRMID_SET_BIRQ_ID       (GIC_PRIVATE_SIGNALS + 217)
#define MT_CCI_SI0_DFSLV_SET_RIRQ_ID        (GIC_PRIVATE_SIGNALS + 218)
#define MT_CCI_SI0_DFSLV_SET_WIRQ_ID        (GIC_PRIVATE_SIGNALS + 219)
#define MT_NFIQOUT0_ID                      (GIC_PRIVATE_SIGNALS + 220)
#define MT_NFIQOUT1_ID                      (GIC_PRIVATE_SIGNALS + 221)
#define MT_NFIQOUT2_ID                      (GIC_PRIVATE_SIGNALS + 222)
#define MT_NFIQOUT3_ID                      (GIC_PRIVATE_SIGNALS + 223)

#define MT8135_APARM_GPTTIMER_IRQ_LINE      MT8135_GPT_IRQ_ID	/* alias name for GPT */

/* assign a random number since it won't be used */

#endif				/*  !__IRQ_H__ */
