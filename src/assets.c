#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assets.h"

typedef struct AssetManager {
    Asset* head;
} AssetManager;

typedef struct Asset {
    const char* name;

    const char* data;
    uint32_t length;

    Asset* prev;
    Asset* next;
} Asset;

Asset* _find_asset(AssetManager* am, const char* name) {
    Asset* asset = am->head;
    while (asset != NULL) {
        if (strcmp(name, asset->name) == 0) {
            return asset;
        }
        asset = asset->next;
    }
    return NULL;
}

AssetManager* new_asset_manager() {
    AssetManager* am = (AssetManager*) malloc(sizeof(AssetManager));
    am->head = NULL;
    return am;
}

void destroy_asset_manager(AssetManager* am) {
    while (am->head) {
        unload_asset(am, am->head->name);
    }

    free(am);
}

bool load_asset(AssetManager* am, const char* name) {
    // Open the file
    FILE* fp = fopen(name, "r");
    if (fp == NULL) {
        return false;
    }

    // Find its length
    if (fseek(fp, 0, SEEK_END) != 0) return false;
    uint32_t length = ftell(fp);
    if (length == -1) return false;
    if (fseek(fp, 0, SEEK_SET) != 0) return false;

    // Read it into a buffer
    char* data = (char*) malloc(length);
    if (data == NULL) return false;
    if (fread(data, 1, length, fp) != length) return false;
    fclose(fp);

    // Add it to the asset list
    Asset* new_head = (Asset*) malloc(sizeof(Asset));
    new_head->name = strdup(name);
    new_head->data = data;
    new_head->length = length;
    new_head->prev = NULL;
    new_head->next = am->head;

    am->head = new_head;
    if (am->head->next != NULL) am->head->next->prev = am->head;

    return true;
}

void unload_asset(AssetManager* am, const char* name) {
    Asset* asset = _find_asset(am, name);
    if (asset == NULL) return;

    if (asset->prev != NULL) asset->prev->next = asset->next;
    if (asset->next != NULL) asset->next->prev = asset->prev;
    
    if (am->head == asset) am->head = asset->next;

    free(asset->name);
    free(asset->data);
    free(asset);
}

bool find_asset(AssetManager* am, const char* name, uint32_t* length, const char** data) {
    Asset* asset = _find_asset(am, name);
    if (asset == NULL) return false;

    *length = asset->length;
    *data = asset->data;
}