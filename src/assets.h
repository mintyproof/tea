#include <stdbool.h>

typedef struct Asset Asset;
typedef struct AssetManager AssetManager;

AssetManager* new_asset_manager();
void destroy_asset_manager(AssetManager* am);

bool load_asset(AssetManager* am, const char* name);
void unload_asset(AssetManager* am, const char* name);

bool find_asset(AssetManager* am, const char* name, uint32_t* length, const char** data);

