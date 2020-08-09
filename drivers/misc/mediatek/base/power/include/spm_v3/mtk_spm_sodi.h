/*
 * Copyright (C) 2016 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */

#ifndef __MTK_SPM_SODI_H__
#define __MTK_SPM_SODI_H__

#include <mtk_cpuidle.h>
#include <mtk_spm_idle.h>
#include <mtk_spm_misc.h>
#include <mtk_spm_internal.h>
#include <mtk_spm_pmic_wrap.h>

#define SODI_TAG     "[SODI] "
#define SODI3_TAG    "[SODI3] "

#define sodi_pr_err(fmt, args...)     pr_err(SODI_TAG fmt, ##args)
#define sodi_pr_warn(fmt, args...)    pr_warn(SODI_TAG fmt, ##args)
#define sodi_pr_debug(fmt, args...)   pr_debug(SODI_TAG fmt, ##args)
#define sodi_pr_notice(fmt, args...)  pr_notice(SODI3_TAG fmt, ##args)
#define sodi_pr_info(fmt, args...)    pr_info(SODI3_TAG fmt, ##args)
#define sodi3_pr_err(fmt, args...)    pr_err(SODI3_TAG fmt, ##args)
#define sodi3_pr_warn(fmt, args...)   pr_warn(SODI3_TAG fmt, ##args)
#define sodi3_pr_notice(fmt, args...) pr_notice(SODI3_TAG fmt, ##args)
#define sodi3_pr_info(fmt, args...)   pr_info(SODI3_TAG fmt, ##args)
#define sodi3_pr_debug(fmt, args...)  pr_debug(SODI3_TAG fmt, ##args)

#define so_pr_err(fg, fmt, args...)     \
		((fg&SODI_FLAG_3P0)?pr_err(SODI3_TAG fmt, ##args):pr_err(SODI_TAG fmt, ##args))
#define so_pr_warn(fg, fmt, args...)    \
		((fg&SODI_FLAG_3P0)?pr_warn(SODI3_TAG fmt, ##args):pr_warn(SODI_TAG fmt, ##args))
#define so_pr_notice(fg, fmt, args...)  \
		((fg&SODI_FLAG_3P0)?pr_notice(SODI3_TAG fmt, ##args):pr_notice(SODI_TAG fmt, ##args))
#define so_pr_info(fg, fmt, args...)    \
		((fg&SODI_FLAG_3P0)?pr_info(SODI3_TAG fmt, ##args):pr_info(SODI_TAG fmt, ##args))
#define so_pr_debug(fg, fmt, args...)					\
		do {							\
			if (fg&SODI_FLAG_3P0)				\
				pr_debug(SODI3_TAG fmt, ##args);	\
			else						\
				pr_debug(SODI_TAG fmt, ##args);		\
		} while (0)

enum spm_sodi_step {
	SPM_SODI_ENTER = 0,
	SPM_SODI_ENTER_SPM_FLOW,
	SPM_SODI_ENTER_SSPM_ASYNC_IPI_BEFORE_WFI,
	SPM_SODI_ENTER_UART_SLEEP,
	SPM_SODI_B4,
	SPM_SODI_B5,
	SPM_SODI_B6,
	SPM_SODI_ENTER_WFI,
	SPM_SODI_LEAVE_WFI,
	SPM_SODI_LEAVE_SSPM_ASYNC_IPI_AFTER_WFI,
	SPM_SODI_LEAVE_SPM_FLOW,
	SPM_SODI_ENTER_UART_AWAKE,
	SPM_SODI_LEAVE,
};

enum spm_sodi_logout_reason {
	SODI_LOGOUT_NONE = 0,
	SODI_LOGOUT_ASSERT = 1,
	SODI_LOGOUT_NOT_GPT_EVENT = 2,
	SODI_LOGOUT_RESIDENCY_ABNORMAL = 3,
	SODI_LOGOUT_EMI_STATE_CHANGE = 4,
	SODI_LOGOUT_LONG_INTERVAL = 5,
	SODI_LOGOUT_CG_PD_STATE_CHANGE = 6,
	SODI_LOGOUT_UNKNOWN = -1,
};

#if SPM_AEE_RR_REC
void __attribute__((weak)) aee_rr_rec_sodi_val(u32 val)
{
}

u32 __attribute__((weak)) aee_rr_curr_sodi_val(void)
{
	return 0;
}
#endif

void __attribute__((weak)) mt_power_gs_t_dump_sodi3(int count, ...)
{
}

static inline void spm_sodi_footprint(enum spm_sodi_step step)
{
#if SPM_AEE_RR_REC
	aee_rr_rec_sodi_val(aee_rr_curr_sodi_val() | (1 << step));
#endif
}

static inline void spm_sodi_footprint_val(u32 val)
{
#if SPM_AEE_RR_REC
		aee_rr_rec_sodi_val(aee_rr_curr_sodi_val() | val);
#endif
}

static inline void spm_sodi_aee_init(void)
{
#if SPM_AEE_RR_REC
	aee_rr_rec_sodi_val(0);
#endif
}

#define spm_sodi_reset_footprint() spm_sodi_aee_init()

void spm_trigger_wfi_for_sodi(u32 pcm_flags);
unsigned int
spm_sodi_output_log(struct wake_status *wakesta, struct pcm_desc *pcmdesc, u32 sodi_flags, u32 operation_cond);

#endif /* __MTK_SPM_SODI_H__ */

