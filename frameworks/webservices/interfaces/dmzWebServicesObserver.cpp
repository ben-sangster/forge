/*!

\class dmz::WebServicesObserver
\ingroup WebServices
\brief Observers webservices asyncronous 
\details A pure virtual interface for observing webservices events. This class is only an interface.

\fn dmz::WebServicesObserver::WebServicesObserver (const PluginInfo &Info)
\brief Constructor
\param[in] Info PluginInfo containing initialization data.

\fn dmz::WebServicesObserver::~WebServicesObserver ()
\brief Destructor

\fn dmz::WebServicesObserver::WebServicesObserver *dmz::WebServicesObserver::cast (
const Plugin *PluginPtr,
const String &PluginName)
\brief Casts Plugin pointer to a WebServicesObserver pointer.
\details If the Plugin object implements the WebServicesObserver interface, apointer to the
WebServicesObserver interface of the Plugin is returned.
\param[in] PluginPtr Pointer to the Plugin.
\param[in] PluginName String containing name of desired WebServicesObserver.
\return Returns a pointer to the WebServicesObserver. Returns NULL if the Plugin does not
implement the WebServicesObserver interface or the \a PluginName is not empty and not
equal to the Plugin's name.

\fn dmz::Boolean dmz::WebServicesObserver::is_valid (
const Handle ObserverHandle,
RuntimeContext *context)
\brief Tests if runtime handle belongs to a valid webservices observer interface.
\param[in] ObserverHandle Unique runtime handle.
\param[in] context Pointer to the runtime context.
\return Returns dmz::True if the runtime handle is valid and the associated Plugin
supports the webservices observer interface.

\fn dmz::Handle dmz::WebServicesObserver::get_webservices_observer_handle ()
\brief Gets webservices observers unique runtime handle.
\return Returns unique runtime handle.

\fn dmz::Handle dmz::WebServicesObserver::get_webservices_observer_name ()
\brief Gets webservices observers name.
\return Returns webservices observer name.

\fn void dmz::WebServicesObserver::receive_results (
const UInt32 EventId,
const WebServicesEventEnum EventType,
const String &AssetId,
const Boolean Succeeded,
const StringContainer &Results)
\brief Receives the results from an asyncronous webservices method call.
\param[in] EventId Events unique id.
\param[in] EventType Event type enumeration.
\param[in] AssetId Assets unique id.
\param[in] Error True if an error was encountered.
\param[in] Results One or more strings returned from the server. If Error was true then 
results will conatian a string that describes the specific error.


*/
