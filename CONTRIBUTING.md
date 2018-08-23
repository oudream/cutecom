# Contributing

Merge requests are welcome.
Please do not hesitate to add yourselfs to CREDITS file!
Please do not forget to update the ChangeLog!
Please do not forget to add a licence header to each new file as well
as add yourself to the authors list of the files you have modified.
If you are looking for ideas check the TODO file.
Automated (unit) tests would be a real cool feature.

## GitLab-CI

This project uses a GitLab pipeline run on the shared runners.  
The pipeline takes under four minutes to complete which should not exceed the 2000 CI minutes gtranted by GitLab for public projects for a group each month (at the moment).
See [this projects CI documention](./CI.md) for details.

## Supported Qt Version

CuteCom Version 0.3x was the first version based on Qt5. Originally it was developed using Qt 5.3.
Reported in issue #8 there are still users relying on Qt5 in a version less then 5.3.
GitLab-CI is currently beeing setup to test the code against Qt version 5.3 as well as Qt version 5.11.

Please verify, that your merge requests don't rely on a higher Qt version.

## Consistent Formatting

CuteCom is being developed with a code styleguide in place since I
believe that a consistent coding style is important.
To achive that, clang-format is beeing used.
For a great talk on that you may want to watch this video
https://www.youtube.com/watch?v=s7JmdCfI__c

Before you create a pull request, please make sure the code adheres to the style.

```
BasedOnStyle: llvm, ColumnLimit: 120, IndentWidth: 4, Standard: Cpp11,
PointerBindsToType: false, BreakBeforeBraces: Linux,
BreakConstructorInitializersBeforeComma: true, AccessModifierOffset: -4,
BreakBeforeBinaryOperators: true
```

You may do so by using the Qt Creator beautifier or the CLI (see below)

(To get the menu entry displayed, the beautifier plugin needs to be enablde under Help -> About Plugins.)

### Qt Creator Beautifier

![](clang_format_01.png)
![](clang_format_02.png)

For __Qt Creator version 4.x__ and above the syntax is different. Each setting needs to be entered on a new line:

```
BasedOnStyle: llvm 
ColumnLimit: 120
IndentWidth: 4
Standard: Cpp11
PointerBindsToType: false
BreakBeforeBraces: Linux
BreakConstructorInitializersBeforeComma: true
AccessModifierOffset: -4
BreakBeforeBinaryOperators: true
```

### clang-format on CLI
This is based on clang-format version >= 3.8.0:

`$clang-format --version`

clang-format version 3.8.0 (tags/RELEASE_350/final 216961)  
clang-format version 6.0.0 (tags/RELEASE_600/final 326550)

```bash
> clang-format  -i -style="{BasedOnStyle: llvm, ColumnLimit: 120, IndentWidth: 4, Standard: Cpp11, PointerBindsToType: false, BreakBeforeBraces: Linux, BreakConstructorInitializersBeforeComma: true, AccessModifierOffset: -4, BreakBeforeBinaryOperators: true}" mainwindow.cpp
```

You may use the provided script `format.sh` e.g. `./format.sh mainwindow.cpp` which will apply the formating directly.

You may also use the clang format wrapper to see potential differences by `./run-clang-format.py -r .`. However, this requires Python being installed.