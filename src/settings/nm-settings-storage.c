/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 * Copyright 2018 Red Hat, Inc.
 */

#include "nm-default.h"

#include "nm-settings-storage.h"

#include "nm-utils.h"
#include "nm-settings-plugin.h"

/*****************************************************************************/

NM_GOBJECT_PROPERTIES_DEFINE_BASE (
	PROP_PLUGIN,
	PROP_UUID,
);

G_DEFINE_ABSTRACT_TYPE (NMSettingsStorage, nm_settings_storage, G_TYPE_OBJECT)

/*****************************************************************************/

static void
set_property (GObject *object, guint prop_id,
              const GValue *value, GParamSpec *pspec)
{
	NMSettingsStorage *self = NM_SETTINGS_STORAGE (object);

	switch (prop_id) {
	case PROP_PLUGIN:
		/* construct-only */
		self->_plugin = g_object_ref (g_value_get_object (value));
		nm_assert (NM_IS_SETTINGS_PLUGIN (self->_plugin));
		break;
	case PROP_UUID:
		/* construct-only */
		self->_uuid = g_value_dup_string (value);
		nm_assert (nm_utils_is_uuid (self->_uuid));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

/*****************************************************************************/

static void
nm_settings_storage_init (NMSettingsStorage *self)
{
}

static void
finalize (GObject *object)
{
	NMSettingsStorage *self = NM_SETTINGS_STORAGE (object);

	g_object_unref (self->_plugin);
	g_free (self->_uuid);

	G_OBJECT_CLASS (nm_settings_storage_parent_class)->finalize (object);
}

static void
nm_settings_storage_class_init (NMSettingsStorageClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);

	object_class->set_property = set_property;
	object_class->finalize = finalize;

	obj_properties[PROP_PLUGIN] =
	    g_param_spec_object (NM_SETTINGS_STORAGE_PLUGIN, "", "",
	                         NM_TYPE_SETTINGS_PLUGIN,
	                         G_PARAM_WRITABLE |
	                         G_PARAM_CONSTRUCT_ONLY |
	                         G_PARAM_STATIC_STRINGS);

	obj_properties[PROP_UUID] =
	    g_param_spec_string (NM_SETTINGS_STORAGE_PLUGIN, "", "",
	                         NULL,
	                         G_PARAM_WRITABLE |
	                         G_PARAM_CONSTRUCT_ONLY |
	                         G_PARAM_STATIC_STRINGS);

	g_object_class_install_properties (object_class, _PROPERTY_ENUMS_LAST, obj_properties);
}
