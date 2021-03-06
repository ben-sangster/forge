#ifndef DMZ_WEB_SERVICES_PLUGIN_OBJECT_DOT_H
#define DMZ_WEB_SERVICES_PLUGIN_OBJECT_DOT_H

#include <dmzApplicationState.h>
#include <dmzObjectObserverUtil.h>
#include <dmzRuntimeDefinitions.h>
#include <dmzRuntimeLog.h>
#include <dmzRuntimeMessaging.h>
#include <dmzRuntimeObjectType.h>
#include <dmzRuntimePlugin.h>
#include <dmzRuntimeTimeSlice.h>
#include <dmzRuntimeTime.h>
#include <dmzTypesDeleteListTemplate.h>
#include <dmzTypesHashTableHandleTemplate.h>
#include <dmzTypesHashTableStringTemplate.h>
#include <dmzTypesHashTableUUIDTemplate.h>
#include <dmzWebServicesCallback.h>


namespace dmz {

   class WebServicesModule;

   class WebServicesPluginObject :
         public Plugin,
         public TimeSlice,
         public WebServicesCallback,
         public MessageObserver,
         public ObjectObserverUtil {

      public:
         WebServicesPluginObject (const PluginInfo &Info, Config &local);
         ~WebServicesPluginObject ();

         // Plugin Interface
         virtual void update_plugin_state (
            const PluginStateEnum State,
            const UInt32 Level);

         virtual void discover_plugin (
            const PluginDiscoverEnum Mode,
            const Plugin *PluginPtr);

         // TimeSlice Interface
         virtual void update_time_slice (const Float64 TimeDelta);

         // WebServicesCallback Interface
         virtual void handle_error (
            const Handle Database,
            const String &Id,
            const Config &Data);

         virtual void handle_publish_config (
            const Handle Database,
            const String &Id,
            const String &Rev);

         virtual void handle_fetch_config (
            const Handle Database,
            const String &Id,
            const String &Rev,
            const Config &Data);

         virtual void handle_delete_config (
            const Handle Database,
            const String &Id,
            const String &Rev);

         virtual void handle_fetch_updates (
            const Handle Database,
            const Config &Updates);

         virtual void handle_realtime_update (
            const Handle Database,
            const String &Id,
            const String &Rev,
            const Boolean &Deleted,
            const Int32 Sequence);

         // Message Observer Interface
         virtual void receive_message (
            const Message &Type,
            const UInt32 MessageSendHandle,
            const Handle TargetObserverHandle,
            const Data *InData,
            Data *outData);

         // Object Observer Interface
         virtual void create_object (
            const UUID &Identity,
            const Handle ObjectHandle,
            const ObjectType &Type,
            const ObjectLocalityEnum Locality);

         virtual void destroy_object (const UUID &Identity, const Handle ObjectHandle);

         virtual void update_object_uuid (
            const Handle ObjectHandle,
            const UUID &Identity,
            const UUID &PrevIdentity);

         virtual void remove_object_attribute (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Mask &AttrMask);

         virtual void update_object_locality (
            const UUID &Identity,
            const Handle ObjectHandle,
            const ObjectLocalityEnum Locality,
            const ObjectLocalityEnum PrevLocality);

         virtual void link_objects (
            const Handle LinkHandle,
            const Handle AttributeHandle,
            const UUID &SuperIdentity,
            const Handle SuperHandle,
            const UUID &SubIdentity,
            const Handle SubHandle);

         virtual void unlink_objects (
            const Handle LinkHandle,
            const Handle AttributeHandle,
            const UUID &SuperIdentity,
            const Handle SuperHandle,
            const UUID &SubIdentity,
            const Handle SubHandle);

         virtual void update_link_attribute_object (
            const Handle LinkHandle,
            const Handle AttributeHandle,
            const UUID &SuperIdentity,
            const Handle SuperHandle,
            const UUID &SubIdentity,
            const Handle SubHandle,
            const UUID &AttributeIdentity,
            const Handle AttributeObjectHandle,
            const UUID &PrevAttributeIdentity,
            const Handle PrevAttributeObjectHandle);

         virtual void update_object_counter (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Int64 Value,
            const Int64 *PreviousValue);

         virtual void update_object_counter_minimum (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Int64 Value,
            const Int64 *PreviousValue);

         virtual void update_object_counter_maximum (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Int64 Value,
            const Int64 *PreviousValue);

         virtual void update_object_alternate_type (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const ObjectType &Value,
            const ObjectType *PreviousValue);

         virtual void update_object_state (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Mask &Value,
            const Mask *PreviousValue);

         virtual void update_object_flag (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Boolean Value,
            const Boolean *PreviousValue);

         virtual void update_object_time_stamp (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Float64 Value,
            const Float64 *PreviousValue);

         virtual void update_object_position (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Vector &Value,
            const Vector *PreviousValue);

         virtual void update_object_orientation (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Matrix &Value,
            const Matrix *PreviousValue);

         virtual void update_object_velocity (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Vector &Value,
            const Vector *PreviousValue);

         virtual void update_object_acceleration (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Vector &Value,
            const Vector *PreviousValue);

         virtual void update_object_scale (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Vector &Value,
            const Vector *PreviousValue);

         virtual void update_object_vector (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Vector &Value,
            const Vector *PreviousValue);

         virtual void update_object_scalar (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Float64 Value,
            const Float64 *PreviousValue);

         virtual void update_object_text (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const String &Value,
            const String *PreviousValue);

         virtual void update_object_data (
            const UUID &Identity,
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Data &Value,
            const Data *PreviousValue);

      protected:
         struct FilterAttrStruct {

            const String Name;
            const Mask Attr;
            FilterAttrStruct *next;

            FilterAttrStruct (const String TheName, const Mask TheAttr) :
                  Name (TheName),
                  Attr (TheAttr),
                  next (0) {;}

            ~FilterAttrStruct () { delete_list (next);  }
         };

         struct FilterStruct {

            FilterStruct *next;
            ObjectTypeSet inTypes;
            ObjectTypeSet exTypes;
            HashTableHandleTemplate<Mask> attrTable;
            HashTableHandleTemplate<Mask> stateTable;
            FilterAttrStruct *list;

            FilterStruct () :
                  next (0),
                  list (0) {;}

            ~FilterStruct () {

               delete_list (next);
               delete_list (list);
               attrTable.empty ();
               stateTable.empty ();
            }
         };

         struct LinkStruct {

            String name;
            String attr;
            Handle handle;

            LinkStruct () : handle (0) {;}
         };

         struct LinkGroupStruct {

            const Handle AttrHandle;
            HashTableStringTemplate<LinkStruct> table;

            LinkGroupStruct (const Handle TheHandle) : AttrHandle (TheHandle) {;}
            ~LinkGroupStruct () { table.empty (); }
         };

         struct ObjectLinkStruct {

            const Handle ObjectHandle;
            HashTableHandleTemplate<LinkGroupStruct> table;

            ObjectLinkStruct (const Handle TheHandle) : ObjectHandle (TheHandle) {;}
            ~ObjectLinkStruct () { table.empty (); }
         };

         void _publish_deletes ();
         void _publish_changes ();
         void _update_links ();
         Boolean _fetch_configs ();

         void _get_ready ();
         void _get_up_to_date ();
         void _stay_up_to_date (const Float64 TimeDelta);

         Boolean _publish (const Handle ObjectHandle);
         Boolean _fetch (const String &Id);

         void _link_to_sub (const Handle SuperHandle, LinkGroupStruct &group);

         void _configs_deleted (const StringContainer &DeleteIdList);

         Config _archive_object (const Handle ObjectHandle);

         Boolean _get_attr_config (const Handle AttrHandle, Config &config);

         void _config_to_object (const Config &Data);

         void _config_to_object_attributes (
            const Handle ObjectHandle,
            const Config &Data);

         Boolean _add_sub_link (
            const Handle AttrHandle,
            const Handle SuperHandle,
            const String &SubName,
            const String &AttrObjName);

         Boolean _handle_type (const ObjectType &Type);

         Boolean _handle_attribute (
            const Handle AttrHandle,
            const Mask &AttrMask);

         Mask _filter_state (const Handle AttrHandle, const Mask &Value);

         Handle _to_handle (const String &Id);

         Boolean _store_rev (const Handle ObjectHandle, const String &Rev);
         Boolean _lookup_rev (const Handle ObjectHandle, String &rev);

         Boolean _store_flag (
            const Handle ObjectHandle,
            const Handle AttributeHandle,
            const Boolean Value);

         Boolean _lookup_flag (const Handle ObjectHandle, const Handle AttributeHandle);

         Boolean _active (const Handle ObjectHandle);
         Boolean _update (const Handle ObjectHandle);

         void _init_filter_list (Config &local);
         void _init_object_type_filter (Config &objects, FilterStruct &filter);
         void _init_attribute_filter (Config &attrConfig, FilterStruct &filter);
         void _init_state_filter (Config &stateConfig, FilterStruct &filter);
         void _init (Config &local);

         Log _log;
         Definitions _defs;
         ApplicationState _appState;
         String _appName;
         Time _time;
         Boolean _tracking;
         Boolean _online;
         WebServicesModule *_webservices;
         String _webservicesName;
         FilterStruct *_filterList;
         Handle _defaultAttrHandle;
         Handle _revAttrHandle;
         Handle _dirtyAttrHandle;
         Handle _publishAttrHandle;
         Handle _fetchAttrHandle;
         Handle _nameHandle;
         Handle _dbApp;
         Handle _dbStudent;
         Handle _dbHandle;
         HandleContainer _activeTable;
         HandleContainer _publishTable;
         StringContainer _fetchTable;
         StringContainer _deleteTable;
         StringContainer _pendingPublishTable;
         StringContainer _pendingFetchTable;
         Message _loginSuccessMsg;
         Message _loginFailedMsg;
         Message _logoutMsg;
         Message _loginSkippedMsg;
         Message _loginMsg;
         Config _currentConfig;
         HashTableHandleTemplate<Config> _configTable;
         HashTableHandleTemplate<ObjectLinkStruct> _linkTable;
         HashTableStringTemplate<String> _revisionTable;
         Int32 _lastSeq;
         Boolean _inDump;
         Boolean _inUpdate;
         Boolean _authenticationRequired;
         Float64 _publishRate;
         Float64 _publishDelta;

      private:
         WebServicesPluginObject ();
         WebServicesPluginObject (const WebServicesPluginObject &);
         WebServicesPluginObject &operator= (const WebServicesPluginObject &);
   };
};

#endif // DMZ_WEB_SERVICES_PLUGIN_OBJECT_DOT_H
