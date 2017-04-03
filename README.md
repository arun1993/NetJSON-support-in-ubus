# NetJSON-support-in-ubus
Implement NetJSON output in ubus for LEDE/OpenWrt

Project goals:
1. Bring CLI support to accommodate the new parameters: DeviceConfiguration and DeviceMonitoring.
2. Write backend ubus APIs to collect the data and store the data in NetJSON objects: DeviceConfiguration and DeviceMonitoring and display them.
3. Revisit the implementation of JSON plugin in SCAL and try to extend the support for NetJSON. For the missing data models in the JSON plugin, try to write a data parser which uses the scal APIs to get data and convert that into NetJSON format and store in the DeviceConfiguration NetJSON object for outputting it.
4. Adapt the code in node-watcher agent and reuse it in SCAL as a plugin. This plugin should output the monitoring data in a NetJSON DeviceMonitoring format..
5. Writing makefile to compile the files added for supporting NetJSON in the ubus IPC/RPC system in OpenWRT/LEDE distribution.
Document the work done, installation guide and usage examples of the new CLIs.

Project Details:
1. CLI support: The CLI should be able to input the required data and display error message if entered wrongly. Generic CLI: ubus call netjson <config | monitor> <general | network | interface | none_to_display_all> <parameter | none_to_display_all> Example CLI: ubus call netjson monitor interface eth0 .The above CLI would display all the statistics related to eth0 in the DeviceMonitoring NetJSON format. CLI depth should be increased for certain commands like the interface and network entries to get the interface name.

2. ubus call netjson API support: We should register the namespace netjson in the libubus. This allows the procedures with any number of arguments.

3. DeviceConfiguration NetJSON: SCAL is an abstraction layer to push information onto the ubus from the device.  SCAL allows gathering data on the device from UCI, ubus calls, shell commands, etc and publishes it on the ubus using a different datamodel. Already available SCAL JSON plugin takes these data models and convert it into a JSON format. My work involves extension of this plugin to support the NetJSON to be done. Add features to the JSON plugin in C which is needed in order to define the full data model using the NetJSON schema. Also for data formats which doesn’t have support in the SCAL JSON plugin, parse the scal datamodel and then store in a DeviceConfiguration NetJSON object. This is SCAL plugin is created for retrieving the information directly using C. 

4. DeviceMonitoring NetJSON: node-watcher agent code is to readapted to show the monitoring data. The existing code can be taken as such or re-adapted by writing hooks in the existing code base to output the data in a NetJSON DeviceMonitoring format rather than the json_object used in node-watcher agent. These codes are to be written as a plugin in the SCAL module. 
