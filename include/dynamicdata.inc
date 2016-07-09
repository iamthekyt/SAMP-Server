#if defined _dynamicdata_included
	#endinput
#endif
#define _dynamicdata_included
#pragma library dynamicdata

#define		INVALID_DYNAMIC_DATA_POS		(-1)
#define		INVALID_DYNAMIC_DATA_SIZE		(0xFFFF)


//int data
native new_dynamic_data_int();
native add_dynamic_data_int(index, value);
native get_dynamic_data_int(index, pos);
native size_dynamic_data_int(index);
native find_dynamic_data_int(index, value);
native remove_dynamic_data_int(index, value);


//float Data
native new_dynamic_data_float();
native add_dynamic_data_float(index, Float:value);
native Float:get_dynamic_data_float(index, pos);
native size_dynamic_data_float(index);
native find_dynamic_data_float(index, Float:value);
native remove_dynamic_data_float(index, Float:value);


//string Data
native new_dynamic_data_string();
native add_dynamic_data_string(index, string[]);
native get_dynamic_data_string(index, pos, string[], length);
native size_dynamic_data_string(index);
native find_dynamic_data_string(index, string[]);
native remove_dynamic_data_string(index, string[]);