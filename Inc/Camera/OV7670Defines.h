/*
 * OV7670Defines.h
 *
 *  Created on: 2 Oct 2020
 *      Author: SYFO
 */

#ifndef INC_CAMERA_OV7670DEFINES_H_
#define INC_CAMERA_OV7670DEFINES_H_

/**** From linux driver *****/
/* Registers */
#define REG_GAIN	0x00	/* Gain lower 8 bits (rest in vref) */
#define REG_BLUE	0x01	/* blue gain */
#define REG_RED		0x02	/* red gain */
#define REG_VREF	0x03	/* Pieces of GAIN, VSTART, VSTOP */
#define REG_COM1	0x04	/* Control 1 */
#define  COM1_CCIR656	  0x40  /* CCIR656 enable */
#define REG_BAVE	0x05	/* U/B Average level */
#define REG_GbAVE	0x06	/* Y/Gb Average level */
#define REG_AECHH	0x07	/* AEC MS 5 bits */
#define REG_RAVE	0x08	/* V/R Average level */
#define REG_COM2	0x09	/* Control 2 */
#define  COM2_SSLEEP	  0x10	/* Soft sleep mode */
#define REG_PID		0x0a	/* Product ID MSB */
#define REG_VER		0x0b	/* Product ID LSB */
#define REG_COM3	0x0c	/* Control 3 */
#define  COM3_SWAP	  0x40	  /* Byte swap */
#define  COM3_SCALEEN	  0x08	  /* Enable scaling */
#define  COM3_DCWEN	  0x04	  /* Enable downsamp/crop/window */
#define REG_COM4	0x0d	/* Control 4 */
#define REG_COM5	0x0e	/* All "reserved" */
#define REG_COM6	0x0f	/* Control 6 */
#define REG_AECH	0x10	/* More bits of AEC value */
#define REG_CLKRC	0x11	/* Clocl control */
#define   CLK_EXT	  0x40	  /* Use external clock directly */
#define   CLK_SCALE	  0x3f	  /* Mask for internal clock scale */
#define REG_COM7	0x12	/* Control 7 */
#define   COM7_RESET	  0x80	  /* Register reset */
#define   COM7_FMT_MASK	  0x38
#define   COM7_FMT_VGA	  0x00
#define	  COM7_FMT_CIF	  0x20	  /* CIF format */
#define   COM7_FMT_QVGA	  0x10	  /* QVGA format */
#define   COM7_FMT_QCIF	  0x08	  /* QCIF format */
#define	  COM7_RGB	  0x04	  /* bits 0 and 2 - RGB format */
#define	  COM7_YUV	  0x00	  /* YUV */
#define	  COM7_BAYER	  0x01	  /* Bayer format */
#define	  COM7_PBAYER	  0x05	  /* "Processed bayer" */
#define REG_COM8	0x13	/* Control 8 */
#define   COM8_FASTAEC	  0x80	  /* Enable fast AGC/AEC */
#define   COM8_AECSTEP	  0x40	  /* Unlimited AEC step size */
#define   COM8_BFILT	  0x20	  /* Band filter enable */
#define   COM8_AGC	  0x04	  /* Auto gain enable */
#define   COM8_AWB	  0x02	  /* White balance enable */
#define   COM8_AEC	  0x01	  /* Auto exposure enable */
#define REG_COM9	0x14	/* Control 9  - gain ceiling */
#define REG_COM10	0x15	/* Control 10 */
#define   COM10_HSYNC	  0x40	  /* HSYNC instead of HREF */
#define   COM10_PCLK_HB	  0x20	  /* Suppress PCLK on horiz blank */
#define   COM10_HREF_REV  0x08	  /* Reverse HREF */
#define   COM10_VS_LEAD	  0x04	  /* VSYNC on clock leading edge */
#define   COM10_VS_NEG	  0x02	  /* VSYNC negative */
#define   COM10_HS_NEG	  0x01	  /* HSYNC negative */
#define REG_HSTART	0x17	/* Horiz start high bits */
#define REG_HSTOP	0x18	/* Horiz stop high bits */
#define REG_VSTART	0x19	/* Vert start high bits */
#define REG_VSTOP	0x1a	/* Vert stop high bits */
#define REG_PSHFT	0x1b	/* Pixel delay after HREF */
#define REG_MIDH	0x1c	/* Manuf. ID high */
#define REG_MIDL	0x1d	/* Manuf. ID low */
#define REG_MVFP	0x1e	/* Mirror / vflip */
#define   MVFP_MIRROR	  0x20	  /* Mirror image */
#define   MVFP_FLIP	  0x10	  /* Vertical flip */

#define REG_AEW		0x24	/* AGC upper limit */
#define REG_AEB		0x25	/* AGC lower limit */
#define REG_VPT		0x26	/* AGC/AEC fast mode op region */
#define REG_HSYST	0x30	/* HSYNC rising edge delay */
#define REG_HSYEN	0x31	/* HSYNC falling edge delay */
#define REG_HREF	0x32	/* HREF pieces */
#define REG_TSLB	0x3a	/* lots of stuff */
#define   TSLB_YLAST	  0x04	  /* UYVY or VYUY - see com13 */
#define REG_COM11	0x3b	/* Control 11 */
#define   COM11_NIGHT	  0x80	  /* NIght mode enable */
#define   COM11_NMFR	  0x60	  /* Two bit NM frame rate */
#define   COM11_HZAUTO	  0x10	  /* Auto detect 50/60 Hz */
#define	  COM11_50HZ	  0x08	  /* Manual 50Hz select */
#define   COM11_EXP	  0x02
#define REG_COM12	0x3c	/* Control 12 */
#define   COM12_HREF	  0x80	  /* HREF always */
#define REG_COM13	0x3d	/* Control 13 */
#define   COM13_GAMMA	  0x80	  /* Gamma enable */
#define	  COM13_UVSAT	  0x40	  /* UV saturation auto adjustment */
#define   COM13_UVSWAP	  0x01	  /* V before U - w/TSLB */
#define REG_COM14	0x3e	/* Control 14 */
#define   COM14_DCWEN	  0x10	  /* DCW/PCLK-scale enable */
#define REG_EDGE	0x3f	/* Edge enhancement factor */
#define REG_COM15	0x40	/* Control 15 */
#define   COM15_R10F0	  0x00	  /* Data range 10 to F0 */
#define	  COM15_R01FE	  0x80	  /*            01 to FE */
#define   COM15_R00FF	  0xc0	  /*            00 to FF */
#define   COM15_RGB565	  0x10	  /* RGB565 output */
#define   COM15_RGB555	  0x30	  /* RGB555 output */
#define REG_COM16	0x41	/* Control 16 */
#define   COM16_AWBGAIN   0x08	  /* AWB gain enable */
#define REG_COM17	0x42	/* Control 17 */
#define   COM17_AECWIN	  0xc0	  /* AEC window - must match COM4 */
#define   COM17_CBAR	  0x08	  /* DSP Color bar */

/*
 * This matrix defines how the colors are generated, must be
 * tweaked to adjust hue and saturation.
 *
 * Order: v-red, v-green, v-blue, u-red, u-green, u-blue
 *
 * They are nine-bit signed quantities, with the sign bit
 * stored in 0x58.  Sign for v-red is bit 0, and up from there.
 */
#define	REG_CMATRIX_BASE 0x4f
#define   CMATRIX_LEN 6
#define REG_CMATRIX_SIGN 0x58


#define REG_BRIGHT	0x55	/* Brightness */
#define REG_CONTRAS	0x56	/* Contrast control */

#define REG_GFIX	0x69	/* Fix gain control */

#define REG_DBLV	0x6b	/* PLL control an debugging */
#define   DBLV_BYPASS	  0x0a	  /* Bypass PLL */
#define   DBLV_X4	  0x4a	  /* clock x4 */
#define   DBLV_X6	  0x8a	  /* clock x6 */
#define   DBLV_X8	  0xca	  /* clock x8 */

#define REG_SCALING_XSC	0x70	/* Test pattern and horizontal scale factor */
#define   TEST_PATTTERN_0 0x80
#define REG_SCALING_YSC	0x71	/* Test pattern and vertical scale factor */
#define   TEST_PATTTERN_1 0x80

#define REG_REG76	0x76	/* OV's name */
#define   R76_BLKPCOR	  0x80	  /* Black pixel correction enable */
#define   R76_WHTPCOR	  0x40	  /* White pixel correction enable */

#define REG_RGB444	0x8c	/* RGB 444 control */
#define   R444_ENABLE	  0x02	  /* Turn on RGB444, overrides 5x5 */
#define   R444_RGBX	  0x01	  /* Empty nibble at end */

#define REG_HAECC1	0x9f	/* Hist AEC/AGC control 1 */
#define REG_HAECC2	0xa0	/* Hist AEC/AGC control 2 */

#define REG_BD50MAX	0xa5	/* 50hz banding step limit */
#define REG_HAECC3	0xa6	/* Hist AEC/AGC control 3 */
#define REG_HAECC4	0xa7	/* Hist AEC/AGC control 4 */
#define REG_HAECC5	0xa8	/* Hist AEC/AGC control 5 */
#define REG_HAECC6	0xa9	/* Hist AEC/AGC control 6 */
#define REG_HAECC7	0xaa	/* Hist AEC/AGC control 7 */
#define REG_BD60MAX	0xab	/* 60hz banding step limit */


/* Default reg values */
#define DEF_GAIN 	0x00
#define DEF_BLUE 	0x80
#define DEF_RED		0x80
#define DEF_VREF	0x03
#define DEF_COM1	0x00
#define DEF_BAVE	0x00
#define DEF_GbAVE	0x00
#define DEF_ARCHH	0x00
#define DEF_RAVE	0x00
#define DEF_COM2	0x01
#define DEF_PID		0x76
#define DEF_VER		0x70
#define DEF_COM3	0x00
#define DEF_COM4	0x40
#define DEF_COM5	0x01
#define DEF_COM6	0x43
#define DEF_AECH	0x40
#define DEF_CLKRC	0x80
#define DEF_COM7	0x00
#define DEF_COM8	0x8F
#define DEF_COM9	0x4A
#define DEF_COM10	0x00
#define DEF_HSTART	0x11
#define DEF_HTOP	0x61
#define DEF_VSTRT	0x03
#define DEF_VSTOP	0x7B
#define DEF_PSHFT	0x00
#define DEF_MIDH	0x7F
#define DEF_MIDL	0xA2
#define DEF_MVFP	0x00
#define DEF_LAEC	0x00
#define DEF_ADCCTR0	0x04
#define DEF_ADCCTR1	0x02
#define DEF_ADCCTR2	0x01
#define DEF_ADCCTR3	0x80
#define DEF_AEW		0x75
#define DEF_AEB		0x63
#define DEF_VPT		0xD4
#define DEF_BBIAS	0x80
#define DEF_GbBIAS	0x80
#define DEF_EXHCH	0x00
#define DEF_EXHCL	0x00
#define DEF_RCBIAS	0x80
#define DEF_ADVFL	0x00
#define DEF_ADVFH	0x00
#define DEF_YAVE	0x00
#define DEF_HSYST	0x08
#define DEF_HREF	0x80
#define DEF_CHLF	0x08
#define DEF_ARBLM	0x03
#define DEF_ADC		0x04
#define DEF_ACOM	0x12
#define DEF_OFON	0x00
#define DEF_TSLB	0x0C
#define DEF_COM11	0x00
#define DEF_COM12	0x40
#define DEF_COM13	0x99
#define DEF_COM14	0x0E
#define DEF_EDGE	0x88
#define DEF_COM15	0xC0
#define DEF_COM16	0x10
#define DEF_COM17	0x08
#define DEF_AWBC1	0x14
#define DEF_AWBC2	0xF0
#define DEF_AWBC3	0x45
#define DEF_AWBC4	0x61
#define DEF_AWBC5	0x51
#define DEF_AWBC6	0x79
#define DEF_REG4B	0x00
#define DEF_DNSTH	0x00
#define DEF_DM_POS	0x00
#define DEF_MTX1	0x40
#define DEF_MTX2	0x34
#define DEF_MTX3	0x0C
#define DEF_MTX4	0x17
#define DEF_MTX5	0x29
#define DEF_MTX6	0x40
#define DEF_BRIGHT	0x00
#define DEF_CONTRAS	0x40
#define DEF_CONTRASCENTER	0x80
#define DEF_MTXS	0x1E
#define DEF_AWBC7	0x91
#define DEF_AWBC8	0x94
#define DEF_AWBC9	0xAA
#define DEF_AWBC10	0x71
#define DEF_AWBC11	0x8D
#define DEF_AWBC12	0x0F
#define DEF_B_LMT	0xF0
#define DEF_R_LMT	0xF0
#define DEF_G_LMT	0xF0
#define DEF_LCC1	0x00
#define DEF_LCC2	0x00
#define DEF_LCC3	0x10
#define DEF_LCC4	0x80
#define DEF_LCC5	0x00
#define DEF_MANU	0x80
#define DEF_MANV	0x80
#define DEF_GFIX	0x00
#define DEF_GGAIN	0x00
#define DEF_DBLV	0x3A
#define DEF_AWBCTR3	0x02
#define DEF_AWBCTR2	0x55
#define DEF_AWBCTR1	0x00
#define DEF_AWBCTR0	0x9A
#define DEF_SCALING_XSC	0x4A
#define DEF_SCALING_YSC	0x35
#define DEF_SCALING_DCWCTR	0x11
#define DEF_SCALING_PCLK_DIV	0x00
#define DEF_REG74	0x00
#define DEF_REG75	0x0F
#define DEF_REG76	0x01
#define DEF_REG77	0x10
#define DEF_SLOP	0x18
#define DEF_GAM1	0x02
#define DEF_GAM2	0x07
#define DEF_GAM3	0x1F
#define DEF_GAM4	0x49
#define DEF_GAM5	0x5A
#define DEF_GAM6	0x6A
#define DEF_GAM7	0x79
#define DEF_GAM8	0x87
#define DEF_GAM9	0x94
#define DEF_GAM10	0x9F
#define DEF_GAM11	0xAF
#define DEF_GAM12	0xBB
#define DEF_GAM13	0xCF
#define DEF_GAM14	0xEE
#define DEF_GAM15	0xEE
#define DEF_DM_LNL	0x00
#define DEF_DM_LNH	0x00
#define DEF_LCC6	0x50
#define DEF_LCC7	0x50
#define DEF_BD50ST	0x99
#define DEF_BD60ST	0x7F
#define DEF_HRL		0xC0
#define DEF_LRL		0x90
#define DEF_DSPC3	0x03
#define DEF_SCALING_PCLK_DELAY	0x02
#define DEF_NT_CTRL	0x00
#define DEF_AECGMAX	0x0F
#define DEF_LPH		0xF0
#define DEF_UPL		0xC1
#define DEF_TPL		0xF0
#define DEF_TPH		0xC1
#define DEF_NALG	0x14
#define DEF_STR-OPT	0x00
#define DEF_STR_R	0x80
#define DEF_STR_G	0x80
#define DEF_STR_B	0x80
#define DEF_ABLC1	0x00
#define DEF_THL_ST	0x80
#define DEF_THL_DLT	0x04
#define DEF_AD-CHB	0x00
#define DEF_AD-CHR	0x00
#define DEF_AD_CHGb	0x00
#define DEF_AD_CHGr	0x00
#define DEF_SATCTR	0xC0

#endif /* INC_CAMERA_OV7670DEFINES_H_ */
