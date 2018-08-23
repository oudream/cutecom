# crafing a new release

- Check if README.md needs an update
- Update Changelog
- Update
  - `distribution/Debian/cutecom.dsc`
  - `distribution/openSUSE/cutecom.changes`
  - `distribution/openSUSE/cutecom.spec`
- Update version information in `CMakeLists.txt`

   ```bash
    set (CuteCom_MAJOR_VERSION 0)
    set (CuteCom_MINOR_VERSION 51)
    set (CuteCom_PATCH_VERSION 0)
   ```

- git add above files
- `git commit -m "rel <version-number>" # e.g. 0.51.0`
- make dist (in build folder)
- git push (origin master)
- Create a new tag (v0.51.0) [at Gitlab](https://gitlab.com/cutecom/cutecom/tags).
- upload tar file (cutecom-0.51.0.tgz) on tag page.
