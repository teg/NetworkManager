/* NetworkManager -- Network link manager
 *
 * Dan Williams <dcbw@redhat.com>
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * (C) Copyright 2004 Red Hat, Inc.
 */

#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

/*
 * dbus services details
 */
#define	NM_DBUS_SERVICE			"org.freedesktop.NetworkManager"

#define	NM_DBUS_PATH				"/org/freedesktop/NetworkManager"
#define	NM_DBUS_INTERFACE			"org.freedesktop.NetworkManager"
#define	NM_DBUS_PATH_DEVICES		"/org/freedesktop/NetworkManager/Devices"
#define	NM_DBUS_INTERFACE_DEVICES	"org.freedesktop.NetworkManager.Devices"

#define	NMI_DBUS_SERVICE			"org.freedesktop.NetworkManagerInfo"
#define	NMI_DBUS_PATH				"/org/freedesktop/NetworkManagerInfo"
#define	NMI_DBUS_INTERFACE			"org.freedesktop.NetworkManagerInfo"


/*
 * Some common errors
 */
#define NM_DBUS_NO_ACTIVE_NET_ERROR	"org.freedesktop.NetworkManager.NoActiveNetwork"
#define NM_DBUS_NO_ACTIVE_DEVICE_ERROR	"org.freedesktop.NetworkManager.NoActiveDevice"
#define NM_DBUS_NO_NETWORKS_ERROR		"org.freedesktop.NetworkManager.NoNetworks"


/*
 * Types of NetworkManager devices
 */
typedef enum NMDeviceType
{
	DEVICE_TYPE_DONT_KNOW = 0,
	DEVICE_TYPE_WIRED_ETHERNET,
	DEVICE_TYPE_WIRELESS_ETHERNET
} NMDeviceType;


/*
 * Wireless network types
 */
typedef enum
{
	NETWORK_TYPE_UNKNOWN = 0,
	NETWORK_TYPE_ALLOWED,
	NETWORK_TYPE_INVALID,
	NETWORK_TYPE_DEVICE
} NMNetworkType;


/*
 * Encryption key types
 */
typedef enum NMEncKeyType
{
	NM_ENC_TYPE_UNKNOWN = 0,
	NM_ENC_TYPE_NONE,
	NM_ENC_TYPE_HEX_KEY,
	NM_ENC_TYPE_ASCII_KEY,
	NM_ENC_TYPE_128_BIT_PASSPHRASE
	/* FIXME: WPA and 802.1x support */
} NMEncKeyType;


/*
 * Driver support levels
 */
typedef enum NMDriverSupportLevel
{
	NM_DRIVER_UNSUPPORTED = 0,
	NM_DRIVER_SEMI_SUPPORTED,
	NM_DRIVER_FULLY_SUPPORTED
} NMDriverSupportLevel;


/*
 * Info-daemon specific preference locations
 */
#define NMI_GCONF_WIRELESS_NETWORKS_PATH		"/system/networking/wireless/networks"

#endif
