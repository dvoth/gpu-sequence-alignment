# gpu-sequence-alignment

## Dependencies

### CUDPP

CUDPP provides hash table functionality with CUDA. However, its dependencies are out-of-date and need updated. Run these commands to install and update the dependendies.
```
git clone https://github.com/cudpp/cudpp.git
cd cudpp
git submodule deinit ext/cub
git rm -rf ext/cub
git submodule deinit ext/moderngpu
git rm -rf ext/moderngpu
git submodule add https://github.com/NVlabs/cub.git ext/cub
git submodule add https://github.com/moderngpu/moderngpu.git ext/moderngpu
```
