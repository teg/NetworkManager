/* -*- Mode: C; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* NetworkManager -- Network link manager
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Copyright (C) 2009 - 2011 Red Hat, Inc.
 * Copyright (C) 2009 Novell, Inc.
 */

#ifndef NM_MODEM_H
#define NM_MODEM_H

#include <dbus/dbus-glib.h>
#include <glib-object.h>
#include "ppp-manager/nm-ppp-manager.h"
#include "nm-device.h"

G_BEGIN_DECLS

#define NM_TYPE_MODEM            (nm_modem_get_type ())
#define NM_MODEM(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), NM_TYPE_MODEM, NMModem))
#define NM_MODEM_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  NM_TYPE_MODEM, NMModemClass))
#define NM_IS_MODEM(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), NM_TYPE_MODEM))
#define NM_IS_MODEM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  NM_TYPE_MODEM))
#define NM_MODEM_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  NM_TYPE_MODEM, NMModemClass))

#define NM_MODEM_UID          "uid"
#define NM_MODEM_PATH         "path"
#define NM_MODEM_DRIVER       "driver"
#define NM_MODEM_CONTROL_PORT "control-port"
#define NM_MODEM_DATA_PORT    "data-port"
#define NM_MODEM_IP_METHOD    "ip-method"
#define NM_MODEM_IP_TIMEOUT   "ip-timeout"
#define NM_MODEM_ENABLED      "enabled"
#define NM_MODEM_CONNECTED    "connected"

#define NM_MODEM_PPP_STATS         "ppp-stats"
#define NM_MODEM_PPP_FAILED        "ppp-failed"
#define NM_MODEM_PREPARE_RESULT    "prepare-result"
#define NM_MODEM_IP4_CONFIG_RESULT "ip4-config-result"
#define NM_MODEM_AUTH_REQUESTED    "auth-requested"
#define NM_MODEM_AUTH_RESULT       "auth-result"

#define MM_MODEM_IP_METHOD_PPP    0
#define MM_MODEM_IP_METHOD_STATIC 1
#define MM_MODEM_IP_METHOD_DHCP   2

typedef enum {
	NM_MODEM_ERROR_CONNECTION_NOT_GSM,      /*< nick=ConnectionNotGsm >*/
	NM_MODEM_ERROR_CONNECTION_NOT_CDMA,     /*< nick=ConnectionNotCdma >*/
	NM_MODEM_ERROR_CONNECTION_INVALID,      /*< nick=ConnectionInvalid >*/
	NM_MODEM_ERROR_CONNECTION_INCOMPATIBLE, /*< nick=ConnectionIncompatible >*/
	NM_MODEM_ERROR_INITIALIZATION_FAILED,   /*< nick=InitializationFailed >*/
} NMModemError;

#define NM_MODEM_ERROR (nm_modem_error_quark ())
GQuark nm_modem_error_quark (void);


typedef struct {
	GObject parent;
} NMModem;

typedef struct {
	GObjectClass parent;

	void     (*get_capabilities)               (NMModem *self,
	                                            NMDeviceModemCapabilities *modem_caps,
	                                            NMDeviceModemCapabilities *current_caps);

	gboolean (*get_user_pass)                  (NMModem *modem,
	                                            NMConnection *connection,
	                                            const char **user,
	                                            const char **pass);

	gboolean (*check_connection_compatible)    (NMModem *modem,
	                                            NMConnection *connection,
	                                            GError **error);

	gboolean (*complete_connection)            (NMModem *modem,
	                                            NMConnection *connection,
	                                            const GSList *existing_connections,
	                                            GError **error);

	NMActStageReturn (*act_stage1_prepare)     (NMModem *modem,
	                                            NMConnection *connection,
	                                            NMDeviceStateReason *reason);

	NMActStageReturn (*static_stage3_ip4_config_start) (NMModem *self,
	                                                    NMActRequest *req,
	                                                    NMDeviceStateReason *reason);

	void (*set_mm_enabled)                     (NMModem *self, gboolean enabled);

	void (*disconnect)                         (NMModem *self, gboolean warn);

	void (*deactivate)                         (NMModem *self, NMDevice *device);

	gboolean (*owns_port)                      (NMModem *self, const char *iface);

	/* Signals */
	void (*ppp_stats)  (NMModem *self, guint32 in_bytes, guint32 out_bytes);
	void (*ppp_failed) (NMModem *self, NMDeviceStateReason reason);

	void (*prepare_result)    (NMModem *self, gboolean success, NMDeviceStateReason reason);
	void (*ip4_config_result) (NMModem *self, NMIP4Config *config, GError *error);

	void (*auth_requested)    (NMModem *self);
	void (*auth_result)       (NMModem *self, GError *error);
} NMModemClass;

GType nm_modem_get_type (void);

const char *nm_modem_get_path         (NMModem *modem);
const char *nm_modem_get_uid          (NMModem *modem);
const char *nm_modem_get_control_port (NMModem *modem);
const char *nm_modem_get_data_port    (NMModem *modem);
const char *nm_modem_get_driver       (NMModem *modem);

gboolean    nm_modem_owns_port        (NMModem *modem, const char *iface);

void        nm_modem_get_capabilities (NMModem *self,
                                       NMDeviceModemCapabilities *modem_caps,
                                       NMDeviceModemCapabilities *current_caps);

gboolean nm_modem_check_connection_compatible (NMModem *self,
                                               NMConnection *connection,
                                               GError **error);

gboolean nm_modem_complete_connection (NMModem *self,
                                       NMConnection *connection,
                                       const GSList *existing_connections,
                                       GError **error);

NMActStageReturn nm_modem_act_stage1_prepare (NMModem *modem,
                                              NMActRequest *req,
                                              NMDeviceStateReason *reason);

NMActStageReturn nm_modem_act_stage2_config (NMModem *modem,
                                             NMActRequest *req,
                                             NMDeviceStateReason *reason);

NMActStageReturn nm_modem_stage3_ip4_config_start (NMModem *modem,
                                                   NMDevice *device,
                                                   NMDeviceClass *device_class,
                                                   NMDeviceStateReason *reason);

NMActStageReturn nm_modem_stage3_ip6_config_start (NMModem *modem,
                                                   NMDevice *device,
                                                   NMDeviceClass *device_class,
                                                   NMDeviceStateReason *reason);

void nm_modem_ip4_pre_commit (NMModem *modem, NMDevice *device, NMIP4Config *config);

gboolean nm_modem_get_secrets (NMModem *modem,
                               const char *setting_name,
                               gboolean request_new,
                               const char *hint);

void nm_modem_deactivate (NMModem *modem, NMDevice *device);

void nm_modem_device_state_changed (NMModem *modem,
                                    NMDeviceState new_state,
                                    NMDeviceState old_state,
                                    NMDeviceStateReason reason);

gboolean      nm_modem_get_mm_enabled (NMModem *self);

void          nm_modem_set_mm_enabled (NMModem *self, gboolean enabled);

gboolean      nm_modem_get_mm_connected (NMModem *self);

G_END_DECLS

#endif /* NM_MODEM_H */
