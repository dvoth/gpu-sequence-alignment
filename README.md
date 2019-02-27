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

Problem: Using git submodules, may not be able to keep track of changes to cudpp that allow it to work
Possible solutions:

1.) Make a bloated codebase by just cloning each dependency (since there are only really 3)
2.) Possibly fork the cudpp repo, make changes to the forked repo, and add the forked repo as a submodule
